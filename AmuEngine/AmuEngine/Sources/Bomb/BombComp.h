#pragma once
#include "../GameObject/GameObject.h"
#include "../ComponentManager/LogicComponent.h"
#include "../Data/Data.h"

/*
	1. 생성된 시점 이후로 Update에서 currnetTime에 deltaTime을 계속 더해줌.
	2. 터지기 까지의 시간보다 currentTime값이 크면 bombExplode()를 실행함

*/

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

		void BombExplode();

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
