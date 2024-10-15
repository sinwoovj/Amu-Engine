#pragma once
#include "BaseLevel.h"
#include "../GameObject/GameObject.h"
#include "../GameObjectManager/GameObjectManager.h"

namespace level
{
	class Menu : public GSM::BaseLevel
	{
	public:
		GameObject* backGround = nullptr;

		void Init() override;
		void Update() override;
		void Exit() override;
		std::string GetName() override;
	};
}
