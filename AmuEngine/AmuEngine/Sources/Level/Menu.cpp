#include "Menu.h"
#include <iostream> 
#include "../Components/SpriteComp.h"
#include "../Components/TransformComp.h"
#include "../GSM/GameStateManager.h"
#include "../Level/NormalLevel.h"

void level::Menu::Init() 
{
	
}

void level::Menu::Update()
{
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_0) == GLFW_PRESS)
		GSM::GameStateManager::GetInstance().ChangeLevel(new level::NormalLevel(0));
}

void level::Menu::Exit() 
{
	
}
