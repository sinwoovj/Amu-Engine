#include "GameStateManager.h"
#include "../Level/BaseLevel.h"
#include "../ComponentManager/GraphicComponent.h"
#include "../ComponentManager/LogicComponent.h"
#include "../ComponentManager/EngineComponent.h"
#include "../ComponentManager/ComponentManager.h"
#include "../EventManager/EventManager.h"
#include "../CollisionManager/CollisionManager.h"
#include "../Bomb/BombManager.h"
#include "../Map/MapManager.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../ResourceManager/ResourceManager.h"
#include "../Serializer/Serializer.h"
#include "../Editor/MainEditor.h"
#include "../RTTI/Registry.h"
#include "../Camera/Camera.h"
#include "../Profiler/Profiler.h"
#include <Utils.h>

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
    glm::vec2 size = Utility::GetCurrentWindowSize();
    MapManager::GetInstance().SetCurrentMap(new Map("Demo", (int)size.x, (int)size.y, 100.f));
}

void GSM::GameStateManager::Update()
{
    if (editor::MainEditor::editor_data.FixedWindowSize)
    {
        if (Utility::GetStateWindowSize())
        {
            Utility::SetCurrentWindowSize({ 1600, 900 });
        }
    }

    if (currentLevel)
    {
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

        DEBUG_PROFILER_START("Camera");
        Camera::GetInstance().Update();
        DEBUG_PROFILER_END;

        DEBUG_PROFILER_START("Logic");
        ComponentManager<LogicComponent>::GetInstance().Update();
        DEBUG_PROFILER_END;
        DEBUG_PROFILER_START("Event");
        EventManager::GetInstance().DispatchAllEvents();
        DEBUG_PROFILER_END;
        if (editor::MainEditor::editorMode == editor::MainEditor::EditorMode::Play)
        {
            DEBUG_PROFILER_START("Engine");
            ComponentManager<EngineComponent>::GetInstance().Update();
            DEBUG_PROFILER_END;
            DEBUG_PROFILER_START("Bomb");
            BOMB::BombManager::GetInstance().Update();
            DEBUG_PROFILER_END;
            DEBUG_PROFILER_START("Level");
            currentLevel->Update();
            DEBUG_PROFILER_END;
        }

        DEBUG_PROFILER_START("Map");
        MapManager::GetInstance().Update();
        DEBUG_PROFILER_END;
        //grid not top viewe
        if (editor::MainEditor::editorMode == editor::MainEditor::EditorMode::Edit &&
            editor::MainEditor::editor_data.ShowGrid == true &&
            editor::MainEditor::editor_data.GridViewTop == false)
        {
            MapManager::GetInstance().GetCurrentMap()->GridUpdate();
        }

        DEBUG_PROFILER_START("Collision");
        CollisionManager::GetInstance().Update();
        DEBUG_PROFILER_END;
        DEBUG_PROFILER_START("Graphic");
        ComponentManager<GraphicComponent>::GetInstance().Update();
        DEBUG_PROFILER_END;
        DEBUG_PROFILER_START("GameObject");
        GameObjectManager::GetInstance().Update();
        DEBUG_PROFILER_END;

        //grid top view
        if (editor::MainEditor::editorMode == editor::MainEditor::EditorMode::Edit &&
            editor::MainEditor::editor_data.ShowGrid == true &&
            editor::MainEditor::editor_data.GridViewTop == true)
        {
            MapManager::GetInstance().GetCurrentMap()->GridUpdate();
        }
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
    MapManager::GetInstance().RemoveAllMap();
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
