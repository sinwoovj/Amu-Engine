#include "GameStateManager.h"
#include "../Level/BaseLevel.h"
#include "../ComponentManager/GraphicComponent.h"
#include "../ComponentManager/LogicComponent.h"
#include "../ComponentManager/ComponentManager.h"
#include "../EventManager/EventManager.h"
#include "../CollisionManager/CollisionManager.h"
#include "../Bomb/BombManager.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../ResourceManager/ResourceManager.h"
#include "../Serializer/Serializer.h"
#include "../Editor/MainEditor.h"
#include "../RTTI/Registry.h"
#include "../Camera/Camera.h"
#include "../Profiler/Profiler.h"

GSM::GameStateManager::GameStateManager() : previousLevel(nullptr), currentLevel(nullptr) {}

GSM::GameStateManager::~GameStateManager()
{
    if (previousLevel)
        delete previousLevel;

    if (currentLevel)
        delete currentLevel;
}

void GSM::GameStateManager::Init()
{
    if (currentLevel)
    {
        currentLevel->Init();
    }
}

void GSM::GameStateManager::Update()
{
    if (currentLevel)
    {
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

        DEBUG_PROFILER_START("Camera");
        Camera::GetInstance().Update();
        DEBUG_PROFILER_END;

        DEBUG_PROFILER_START("Logic");
        ComponentManager<LogicComponent>::GetInstance().Update();
        DEBUG_PROFILER_END;
        if (editor::MainEditor::editorMode == editor::MainEditor::EditorMode::Play)
        {
            DEBUG_PROFILER_START("Engine");
            ComponentManager<EngineComponent>::GetInstance().Update();
            DEBUG_PROFILER_END;
            DEBUG_PROFILER_START("Bomb");
            BOMB::BombManager::GetInstance().Update();
            DEBUG_PROFILER_END;
            DEBUG_PROFILER_START("Collision");
            CollisionManager::GetInstance().Update();
            DEBUG_PROFILER_END;
            DEBUG_PROFILER_START("Event");
            EventManager::GetInstance().DispatchAllEvents();
            DEBUG_PROFILER_END;
            DEBUG_PROFILER_START("Level");
            currentLevel->Update();
            DEBUG_PROFILER_END;
        }


        DEBUG_PROFILER_START("Graphic");
        ComponentManager<GraphicComponent>::GetInstance().Update();
        DEBUG_PROFILER_END;
        DEBUG_PROFILER_START("GameObject");
        GameObjectManager::GetInstance().Update();
        DEBUG_PROFILER_END;
    }
}

void GSM::GameStateManager::Exit()
{
    if (currentLevel)
    {
        currentLevel->Exit();
    }
    EventManager::GetInstance().DeleteUndispahchEvent();
    GameObjectManager::GetInstance().RemoveAllObject();
    ResourceManager::GetInstance().UnloadAllResource();
}

void GSM::GameStateManager::ChangeLevel(BaseLevel* newLvl)
{
    delete previousLevel;
    previousLevel = currentLevel;

    //Exit the current level
    Exit();

    //Current level is now the "next" level
    currentLevel = newLvl;

    //initialize the level
    Init();
}

bool GSM::GameStateManager::ShouldExit()
{
    return currentLevel == nullptr;
}
