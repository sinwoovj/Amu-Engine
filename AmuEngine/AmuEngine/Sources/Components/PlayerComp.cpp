#include "PlayerComp.h"
#include <string>
#include "Components.h"
#include "../Event/CollisionEvent.h"
#include "../Utils/Utils.h"
#include "../GSM/GameStateManager.h"
#include "../Prefab/Prefab.h"
#include "../GameObjectManager/GameObjectManager.h"
#include <EasyImgui.h>

int PlayerComp::_playerId = 0;

PlayerComp::PlayerComp(GameObject* _owner) : EngineComponent(_owner)
{
	owner = _owner;

	id = GetPlayerId();
	focusMe = false;
	data = new Data::PlayerData(1, 1, 1, 10, Data::BombData::BombType::Default, 0);
}

PlayerComp::~PlayerComp()
{
	delete data;
}	

void PlayerComp::SetCamera(bool isfocus)
{

}

void PlayerComp::CreateBomb(Data::BombData::BombType type)
{
	std::string bombName = "Bomb" + std::to_string(BOMB::BombManager::GetInstance().GetAllBombs().size());
	GameObjectManager::GetInstance().AddObject(bombName);
	GameObject* bombObj = GameObjectManager::GetInstance().GetObj(bombName);
	bombObj->AddComponent<TransformComp>();
	bombObj->GetComponent<TransformComp>()->SetPos(owner->GetComponent<TransformComp>()->GetPos());
	bombObj->AddComponent<SpriteComp>();
	bombObj->AddComponent<ColliderComp>();
	bombObj->AddComponent<RigidbodyComp>();
	bombObj->AddComponent<BOMB::BombComp>();
	bombObj->GetComponent<BOMB::BombComp>()->SetBomb(type);
}

void PlayerComp::Update()
{
	TransformComp* t = owner->GetComponent<TransformComp>();
	if (!t) return;
	
	RigidbodyComp* r = owner->GetComponent<RigidbodyComp>();
	if (!r) return;
	
	/*AnimatorComp* am = owner->GetComponent<AnimatorComp>();
	if (!am) return;*/
	
	/*AudioComp* ad = owner->GetComponent<AudioComp>();
	if (!ad) return;*/
	
	//if smooth step
	r->SetVelocityX(0);
	r->SetVelocityY(0);

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS)
	{
		//t->ReverseX(0);
		r->SetVelocityX(-speed);
	}

	else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS)
	{
		//t->ReverseX(1);
		r->SetVelocityX(speed);
	}
	
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS)
	{
		//t->ReverseX(0);
		r->SetVelocityY(-speed);
	}

	else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS)
	{
		//t->ReverseX(1);
		r->SetVelocityY(speed);
	}

	int currentFrameKey = glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE);


	if (currentFrameKey == GLFW_PRESS && currentFrameKey != LastFrameKey)
	{
		CreateBomb(Data::BombData::BombType::Default);
	}

	LastFrameKey = currentFrameKey;
	
	SetCamera(focusMe);
}

void PlayerComp::Edit()
{
	ImGui::LabelText("label", "Value");

	//Speed
	ImGui::SeparatorText("Speed");
	{
		ImGui::DragFloat("Speed", &speed, 1, 0.0000001f);
		if (ImGui::Button("Initialize"))
		{
			speed = 100;
		}
	}
	ImGui::SeparatorText("Camera");
	{
		ImGui::Checkbox("Focus Me", &focusMe);
	}
}

void PlayerComp::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");

	if (compData != data.end())
	{
		auto it = compData->find("speed");
		speed = it.value();
		it = compData->find("focusMe");
		focusMe = it.value();
	}
}

json PlayerComp::SaveToJson()
{
	json data;
	data["type"] = TypeName;

	json compData;
	compData["speed"] = speed;
	compData["focusMe"] = focusMe;
	data["compData"] = compData;

	return data;
}

BaseRTTI* PlayerComp::CreatePlayerComponent(GameObject* owner)
{
	BaseRTTI* p = new PlayerComp(owner);
	owner->AddComponent<PlayerComp>(static_cast<BaseComponent*>(p));
	return p;
}