#include "BombComp.h"
#include "../Bomb/BombManager.h"
#include "../Components/SpriteComp.h"
#include "../FrameCounter/FrameCounter.h"
#include <EasyImgui.h>

BOMB::BombComp::BombComp(GameObject* _owner) : LogicComponent(_owner)
{
	owner = _owner;
	BOMB::BombManager::GetInstance().AddBomb(owner);
}

BOMB::BombComp::~BombComp()
{
	BOMB::BombManager::GetInstance().RemoveBomb(owner);
}

void BOMB::BombComp::SetBomb(Data::BombData::BombType type_)
{
	type = type_;
	//Set Sprite, Audio, Animation, Effects ..
	std::string bombTextureName = SpriteComp::DefaultSprite;

	owner->GetComponent<SpriteComp>()->SetTexture(bombTextureName);
	owner->GetComponent<SpriteComp>()->SetTextureSize({50,50});
}

void BOMB::BombComp::Update()
{

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

