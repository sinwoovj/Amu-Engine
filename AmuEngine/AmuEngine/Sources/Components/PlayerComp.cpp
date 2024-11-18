#include "PlayerComp.h"
#include <string>
#include "Components.h"
#include "../Event/CollisionEvent.h"
#include "../Utils/Utils.h"
#include "../GSM/GameStateManager.h"
#include "../Prefab/Prefab.h"
#include "../GameObjectManager/GameObjectManager.h"
#include <EasyImgui.h>
#include "../Editor/MainEditor.h"

int PlayerComp::_playerId = 0;

PlayerComp::PlayerComp(GameObject* _owner) : EngineComponent(_owner)
{
	owner = _owner;

	id = GetPlayerId();
	focusMe = false;
	Data::KeyData keyData;
	switch (id)
	{
	case 0: 
		keyData = { GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D, GLFW_KEY_SPACE };
		break;
	case 1: 
		keyData = { GLFW_KEY_UP, GLFW_KEY_LEFT, GLFW_KEY_DOWN, GLFW_KEY_RIGHT, GLFW_KEY_KP_0 };
		break;
	default :
		keyData = { GLFW_KEY_LAST, GLFW_KEY_LAST, GLFW_KEY_LAST, GLFW_KEY_LAST, GLFW_KEY_LAST };
	}
	data = new Data::PlayerData(1, 1, 1, 10, Data::BombData::BombType::Default, 0, keyData);
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
	if (currentBombCount < data->bombCount)
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
		bombObj->GetComponent<BOMB::BombComp>()->SetPlayer(owner);

		BOMB::BombManager::GetInstance().AddBomb(bombObj);
		currentBombCount++;
	}	
}



void PlayerComp::SubtractCurrentBombCount()
{
	if (currentBombCount > 0)
	{
		currentBombCount--;
	}
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

	if (glfwGetKey(glfwGetCurrentContext(), data->kData.moveU) == GLFW_PRESS)
	{
		//t->ReverseX(1);
		r->SetVelocityY(speed);
	}

	else if (glfwGetKey(glfwGetCurrentContext(), data->kData.moveD) == GLFW_PRESS)
	{
		//t->ReverseX(0);
		r->SetVelocityY(-speed);
	}

	if (glfwGetKey(glfwGetCurrentContext(), data->kData.moveL) == GLFW_PRESS)
	{
		//t->ReverseX(0);
		r->SetVelocityX(-speed);
	}

	else if (glfwGetKey(glfwGetCurrentContext(), data->kData.moveR) == GLFW_PRESS)
	{
		//t->ReverseX(1);
		r->SetVelocityX(speed);
	}
	int currentFrameKey = glfwGetKey(glfwGetCurrentContext(), data->kData.plant);

	if (editor::MainEditor::editorMode == editor::MainEditor::EditorMode::Play)
	{
		if (currentFrameKey == GLFW_PRESS && currentFrameKey != LastFrameKey)
		{
			CreateBomb(Data::BombData::BombType::Default);
		}
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

	//Player Data
	ImGui::SeparatorText("Player Data");
	{
		ImGui::DragInt("BombCount", &data->bombCount);
		ImGui::DragInt("ExplosionRadius", &data->explosionRadius);
		ImGui::DragFloat("MoveSpeed", &data->moveSpeed, 1, 0.0000001f);
		ImGui::DragInt("Hp", &data->hp);
		const char* bombTypes[] = { "Default", "Radioactivity", "Magma", "Ice" };
		ImGui::Combo("CurrentBombType", reinterpret_cast<int*>(&data->currentBombType), bombTypes, IM_ARRAYSIZE(bombTypes));
		ImGui::InputInt("ItemVitalizationFlag", &data->itemVitalizationFlag);
		
		//kData
		static int keyBind[5];
		keyBind[0] = Utility::getKeyIndex(data->kData.moveU);
		keyBind[1] = Utility::getKeyIndex(data->kData.moveL);
		keyBind[2] = Utility::getKeyIndex(data->kData.moveD);
		keyBind[3] = Utility::getKeyIndex(data->kData.moveR);
		keyBind[4] = Utility::getKeyIndex(data->kData.plant);

		ImGui::SeparatorText("Key Data");
		{
			ImGui::Combo("Up", &keyBind[0], Utility::keyTypes, IM_ARRAYSIZE(Utility::keyTypes));
			ImGui::Combo("Left", &keyBind[1], Utility::keyTypes, IM_ARRAYSIZE(Utility::keyTypes));
			ImGui::Combo("Down", &keyBind[2], Utility::keyTypes, IM_ARRAYSIZE(Utility::keyTypes));
			ImGui::Combo("Right", &keyBind[3], Utility::keyTypes, IM_ARRAYSIZE(Utility::keyTypes));
			ImGui::Combo("Plant", &keyBind[4], Utility::keyTypes, IM_ARRAYSIZE(Utility::keyTypes));
		}

		data->kData.moveU = Utility::getKeyValue(keyBind[0]);
		data->kData.moveL = Utility::getKeyValue(keyBind[1]);
		data->kData.moveD = Utility::getKeyValue(keyBind[2]);
		data->kData.moveR = Utility::getKeyValue(keyBind[3]);
		data->kData.plant = Utility::getKeyValue(keyBind[4]);
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