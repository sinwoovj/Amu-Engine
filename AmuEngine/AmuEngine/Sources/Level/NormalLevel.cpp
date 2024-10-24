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
#include "../Player/player.h"
#include "../Serializer/Serializer.h"
#include "LevelManager.h"

level::NormalLevel::NormalLevel(std::string str) : levelName(str)
{

}

level::NormalLevel::~NormalLevel()
{

}

void level::NormalLevel::Init()
{
	Serializer::GetInstance().LoadLevel(levelName);
	Serializer::GetInstance().LoadEditorSetting();

#ifdef _DEBUG
	//std::cout << "Current Level : " << levelName << std::endl;
#endif

}

void level::NormalLevel::Update()
{
	//if go menu
	//GSM::GameStateManager::GetInstance().ChangeLevel(new Menu);
	//if go next level
	//GSM::GameStateManager::GetInstance().ChangeLevel(new NormalLevel("something"));
}

void level::NormalLevel::Exit()
{

}

std::string level::NormalLevel::GetName()
{
	return levelName;
}
