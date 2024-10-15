#pragma once
#include "BaseLevel.h"
#include <string>
class GameObject;

namespace level
{
	class NormalLevel : public GSM::BaseLevel
	{
		GameObject* player = nullptr;

		std::string levelName = "";

	public:
		NormalLevel(std::string str);
		~NormalLevel() override;
		void Init() override;
		void Update() override;
		void Exit() override;
		std::string GetName() override;
	};
}