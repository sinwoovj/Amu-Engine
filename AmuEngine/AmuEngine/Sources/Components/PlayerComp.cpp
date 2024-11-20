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
#include "../Data/DataManager.h"
int PlayerComp::_playerId = 0;
int PlayerComp::keyBindIndex[5] = { 0,0,0,0,0 };

PlayerComp::PlayerComp(GameObject* _owner) : EngineComponent(_owner)
{
	owner = _owner;

	id = GetPlayerId();
	focusMe = false;
	data = new Data::PlayerData(1, 1, 1, 10, Data::BombData::BombType::Default, 0);
}

PlayerComp::~PlayerComp()
{
	_playerId--;
	delete data;
}	

void PlayerComp::SetCamera(bool isfocus)
{

}

void PlayerComp::CreateBomb(Data::BombData::BombType type)
{
	if (currentBombCount < data->bombCount)
	{
		std::string bombName = "Bomb" + std::to_string(BOMB::BombManager::BombCount++);
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
		std::cout << currentBombCount << std::endl;
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

	auto kData = Data::DataManager::GetInstance().gameData.KeyDatas.find(id)->second;

	int currentFrameKey = glfwGetKey(glfwGetCurrentContext(), kData.plant);

	if (editor::MainEditor::editorMode == editor::MainEditor::EditorMode::Play)
	{
		if (currentFrameKey == GLFW_PRESS && currentFrameKey != LastFrameKey)
		{
			CreateBomb(Data::BombData::BombType::Default);
		}
	}

	LastFrameKey = currentFrameKey;

	//if smooth step
	r->SetVelocityX(0);
	r->SetVelocityY(0);

	// 초기 속도 설정
	float velocityX = 0.0f;
	float velocityY = 0.0f;

	// 상하 이동 처리
	if (glfwGetKey(glfwGetCurrentContext(), kData.moveU) == GLFW_PRESS) {
		velocityY = speed; // 위로 이동
	}
	else if (glfwGetKey(glfwGetCurrentContext(), kData.moveD) == GLFW_PRESS) {
		velocityY = -speed; // 아래로 이동
	}

	// 좌우 이동 처리
	if (glfwGetKey(glfwGetCurrentContext(), kData.moveL) == GLFW_PRESS) {
		velocityX = -speed; // 왼쪽으로 이동
	}
	else if (glfwGetKey(glfwGetCurrentContext(), kData.moveR) == GLFW_PRESS) {
		velocityX = speed; // 오른쪽으로 이동
	}

	// 대각선 이동 방지: 하나의 방향만 허용
	if (velocityX != 0.0f && velocityY != 0.0f) {
		velocityX = 0.0f; // 우선순위에 따라 좌우 이동 무효화
	}

	// 최종 속도 설정
	r->SetVelocityX(velocityX);
	r->SetVelocityY(velocityY);
	
	SetCamera(focusMe);

	//std::cout << "P, fc : " << FrameCounter::GetInstance().getFrameCount() << "x : " << GetOwner()->GetComponent<TransformComp>()->GetPos().x << std::endl;
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
		auto kData = Data::DataManager::GetInstance().gameData.KeyDatas.find(id)->second;
		PlayerComp::keyBindIndex[0] = Utility::getKeyIndex(kData.moveU);
		PlayerComp::keyBindIndex[1] = Utility::getKeyIndex(kData.moveL);
		PlayerComp::keyBindIndex[2] = Utility::getKeyIndex(kData.moveD);
		PlayerComp::keyBindIndex[3] = Utility::getKeyIndex(kData.moveR);
		PlayerComp::keyBindIndex[4] = Utility::getKeyIndex(kData.plant);

		ImGui::SeparatorText("Key Data");
		{
			ImGui::Combo("Up",	&PlayerComp::keyBindIndex[0], Utility::keyTypes, IM_ARRAYSIZE(Utility::keyTypes));
			ImGui::Combo("Left", &PlayerComp::keyBindIndex[1], Utility::keyTypes, IM_ARRAYSIZE(Utility::keyTypes));
			ImGui::Combo("Down", &PlayerComp::keyBindIndex[2], Utility::keyTypes, IM_ARRAYSIZE(Utility::keyTypes));
			ImGui::Combo("Right", &PlayerComp::keyBindIndex[3], Utility::keyTypes, IM_ARRAYSIZE(Utility::keyTypes));
			ImGui::Combo("Plant", &PlayerComp::keyBindIndex[4], Utility::keyTypes, IM_ARRAYSIZE(Utility::keyTypes));
		}

		kData.moveU = Utility::getKeyValue(PlayerComp::keyBindIndex[0]);
		kData.moveL = Utility::getKeyValue(PlayerComp::keyBindIndex[1]);
		kData.moveD = Utility::getKeyValue(PlayerComp::keyBindIndex[2]);
		kData.moveR = Utility::getKeyValue(PlayerComp::keyBindIndex[3]);
		kData.plant = Utility::getKeyValue(PlayerComp::keyBindIndex[4]);
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