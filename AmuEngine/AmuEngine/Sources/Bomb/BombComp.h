#pragma once
#include "../GameObject/GameObject.h"
#include "../ComponentManager/LogicComponent.h"
#include "../Data/Data.h"

namespace BOMB
{
	class BombComp : public LogicComponent
	{
	private:
		Data::BombData::BombType type = Data::BombData::BombType::Default;

	public:
		GameObject* owner;

		BombComp(GameObject* _owner);
		~BombComp();

		void SetBomb(Data::BombData::BombType type_);
		Data::BombData::BombType GetBomb() { return type; }

		void Update() override;
		void Edit() override;

		//state
		float currentTime = 0;

		void LoadFromJson(const json&) override;
		json SaveToJson() override;

		static BaseRTTI* CreateBombComponent(GameObject* owner);
		static constexpr const char* TypeName = "BombComp";

		friend GameObject;
	};
}
