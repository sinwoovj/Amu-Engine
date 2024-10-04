#pragma once
#include "../Level/BaseLevel.h"

namespace level
{
	class Sprite : public GSM::BaseLevel
	{
	public:
		void Init() override;
		void Update() override;
		void Exit() override;
	};
}
