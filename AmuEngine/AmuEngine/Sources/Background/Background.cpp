#include "Background.h"
#include "../Components/Components.h"
#include "../Prefab/Prefab.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../GSM/GameStateManager.h"
#include "../Camera/Camera.h"
#include "../Level/Menu.h"

GameObject* background = nullptr;
int c = 0;
void InitBackground()
{
	if (dynamic_cast<level::Menu*>(GSM::GameStateManager::GetInstance().GetCurrentLevel()) != nullptr)
	{
		Prefab b("Background");
		background = b.NewGameObject("Background");
	}
	else
	{
		background = GameObjectManager::GetInstance().GetObj("Background");
	}

	//background->GetComponent<AudioComp>()->playAudio(-1, "./Assets/Audio/BGM.mp3", 0.3f);
	SpriteComp* s = background->GetComponent<SpriteComp>();
	TransformComp* t = background->GetComponent<TransformComp>();

	//add camera setting
}

void UpdateBackground()
{

	SpriteComp* s = background->GetComponent<SpriteComp>();
	TransformComp* t = background->GetComponent<TransformComp>();
	t->SetRot(glm::radians(2.0f) * c);
	c++;
}

void ExitBackground()
{

}