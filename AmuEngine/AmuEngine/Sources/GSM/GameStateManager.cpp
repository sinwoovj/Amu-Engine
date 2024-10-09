#include "GameStateManager.h"
#include "../Level/BaseLevel.h"
#include "../ComponentManager/GraphicComponent.h"
#include "../ComponentManager/LogicComponent.h"
#include "../ComponentManager/ComponentManager.h"
#include "../EventManager/EventManager.h"
#include "../CollisionManager/CollisionManager.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../ResourceManager/ResourceManager.h"
#include "../Serializer/Serializer.h"
#include "../RTTI/Registry.h"
#include "../Camera/Camera.h"

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
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        Camera::GetInstance().Update();

        ComponentManager<LogicComponent>::GetInstance().Update();
        ComponentManager<EngineComponent>::GetInstance().Update();

        CollisionManager::GetInstance().Update();
        EventManager::GetInstance().DispatchAllEvents();

        currentLevel->Update();

        ComponentManager<GraphicComponent>::GetInstance().Update();
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
