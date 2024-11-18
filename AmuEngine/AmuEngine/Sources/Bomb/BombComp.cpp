#include "BombComp.h"
#include "../Bomb/BombManager.h"
#include "../Components/SpriteComp.h"
#include "../Components/PlayerComp.h"
#include "../FrameCounter/FrameCounter.h"
#include "../Data/DataManager.h"
#include "../FrameCounter/FrameCounter.h"
#include "../GameObjectManager/GameObjectManager.h"
#include <EasyImgui.h>

BOMB::BombComp::BombComp(GameObject* _owner) : LogicComponent(_owner)
{
	owner = _owner;
}

void BOMB::BombComp::SetBomb(Data::BombData::BombType type_)
{
	type = type_;
	//Set Sprite, Audio, Animation, Effects ..
	std::string bombTextureName = SpriteComp::DefaultSprite;
	playerObj->GetComponent<TransformComp>()->SetPos(playerObj->GetComponent<TransformComp>()->GetPos());

	owner->GetComponent<SpriteComp>()->SetTexture(bombTextureName);
	owner->GetComponent<SpriteComp>()->SetTextureSize({50,50});
}

void BOMB::BombComp::SetPlayer(GameObject* obj)
{
	playerObj = obj;
	SetBomb(type);
}

void BOMB::BombComp::Update()
{
	auto& bombDatas = Data::DataManager::GetInstance().gameData.BombDatas;
	switch (state)
	{
	case Data::BombData::BombCreated:// ÆøÅºÀÌ »ý¼ºµÆÀ» ¶§
		state = Data::BombData::BombIdleBeforeExplosion;
		break;
	case Data::BombData::BombIdleBeforeExplosion:// ÆøÅºÀÌ »ý¼ºµÇ°í ÅÍÁö±â Àü±îÁö
		if (bombDatas.find(type) != bombDatas.end())
		{
			if (currentTime >= bombDatas.find(type)->second.timeToExplode)
			{
				state = Data::BombData::BombExploded;
			}
		}
		break;
	case Data::BombData::BombExploded:// ÆøÅºÀÌ ÅÍÁ³À» ¶§
		state = Data::BombData::BombEffectActive;
		ResetTime();
		break;
	case Data::BombData::BombEffectActive:// ÆøÅºÀÌ ÅÍÁö°í È¿°ú°¡ ¹ßµ¿µÇ°í ÀÖÀ» ¶§
		if (currentTime >= bombDatas.find(type)->second.effectDurationAfterExplosion)
		{
			state = Data::BombData::BombDisappearing;
		}
		break;
	case Data::BombData::BombDisappearing:// ÆøÅºÀÌ »ç¶óÁú ¶§
		state = Data::BombData::BombDelete;
	case Data::BombData::BombDelete:
		playerObj->GetComponent<PlayerComp>()->SubtractCurrentBombCount();
		break;
	}
	currentTime += FrameCounter::GetInstance().getDeltaTime();
}

void BOMB::BombComp::Edit()
{
	ImGui::LabelText("label", "Value");

	ImGui::SeparatorText("Bomb");
	{

		if (ImGui::Button("Initialize"))
		{
			type = Data::BombData::BombType::Default;
		}
	}
}

void BOMB::BombComp::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");

	if (compData != data.end())
	{
		auto it = compData->find("type");
		type = it.value();
	}
}

json BOMB::BombComp::SaveToJson()
{
	json data;
	data["type"] = TypeName;

	json compData;
	compData["type"] = type;
	data["compData"] = compData;

	return data;
}

BaseRTTI* BOMB::BombComp::CreateBombComponent(GameObject* owner)
{
	BaseRTTI* p = new BombComp(owner);
	owner->AddComponent<BombComp>(static_cast<BaseComponent*>(p));
	return p;
}

