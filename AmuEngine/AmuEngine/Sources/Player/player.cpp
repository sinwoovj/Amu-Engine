#include "player.h"

#include "../Components/Components.h"
#include "../Prefab/Prefab.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../GSM/GameStateManager.h"
#include "../Camera/Camera.h"
#include "../Level/NormalLevel.h"

GameObject* player = nullptr;
void InitPlayer()
{
	if (dynamic_cast<level::NormalLevel*>(GSM::GameStateManager::GetInstance().GetCurrentLevel()) != nullptr)
	{
		Prefab b("Player");
		player = b.NewGameObject("Player");
	}
	else
	{
		player = GameObjectManager::GetInstance().GetObj("Player");
	}

	SpriteComp* s = player->GetComponent<SpriteComp>();
	TransformComp* t = player->GetComponent<TransformComp>();

}

void UpdatePlayer()
{
	SpriteComp* s = player->GetComponent<SpriteComp>();
	TransformComp* t = player->GetComponent<TransformComp>();
	/*t->SetRot(glm::radians(2.0f) * c);
	c++;*/
}

void ExitPlayer()
{

}