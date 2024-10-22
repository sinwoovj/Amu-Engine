#pragma once
#include "../GameObject/GameObject.h"
#include "../ComponentManager/LogicComponent.h"

namespace BOMB
{
	enum KindOfBomb
	{
		Default,
		Poison,
		Magma,
		Ice
	};

	class BombComp : public LogicComponent
	{
	private:
		//after carry to data
	
		KindOfBomb kindOfBomb = Default;
	public:
		GameObject* owner;

		BombComp(GameObject* _owner);
		~BombComp();

		void SetBomb(KindOfBomb kindofbomb);
		KindOfBomb GetBomb() { return kindOfBomb; }

		void Update() override;
		void Edit() override;

		void LoadFromJson(const json&) override;
		json SaveToJson() override;

		static BaseRTTI* CreateBombComponent(GameObject* owner);
		static constexpr const char* TypeName = "BombComp";

		friend GameObject;
	};
}
