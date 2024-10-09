#include "NormalLevel.h"
#include <iostream>
#include "../GSM/GameStateManager.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../ComponentManager/ComponentManager.h"
#include "../Components/Components.h"
#include "../EventManager/EventManager.h"
#include "../Prefab/Prefab.h"
#include "../Utils/Utils.h"
#include "../Level/Menu.h"
#include "../Background/Background.h"
#include "../Serializer/Serializer.h"

level::NormalLevel::NormalLevel(int _level) : level(_level)
{

}

level::NormalLevel::~NormalLevel()
{

}

void level::NormalLevel::Init()
{
	Serializer::GetInstance().LoadLevel("./Sources/Assets/Level/test" + std::to_string(level) + ".lvl");
	InitBackground();

#ifdef _DEBUG
	std::cout << "Current Level : " << level << std::endl;
#endif

}

void level::NormalLevel::Update()
{
	UpdateBackground();

	//if go menu
	//GSM::GameStateManager::GetInstance().ChangeLevel(new Menu);
	//if go next level
	//GSM::GameStateManager::GetInstance().ChangeLevel(new NormalLevel(level + 1));
}

void level::NormalLevel::Exit()
{
	//Clear
}
