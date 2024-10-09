#pragma once
#include "BaseLevel.h"
class GameObject;

namespace level
{
	class NormalLevel : public GSM::BaseLevel
	{
		GameObject* player = nullptr;

		int level;

	public:
		NormalLevel(int _level);
		~NormalLevel() override;
		void Init() override;
		void Update() override;
		void Exit() override;
	};
}