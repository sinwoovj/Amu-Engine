#pragma once
#include "BaseLevel.h"
#include "../GameObject/GameObject.h"
#include "../GameObjectManager/GameObjectManager.h"

namespace level
{
	class Menu : public GSM::BaseLevel
	{
		int c = 0;
	public:
		GameObject* backGround = nullptr;

		void Init() override;
		void Update() override;
		void Exit() override;
	};
}
