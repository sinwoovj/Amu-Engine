#pragma once
#include <iostream>
#include <string>
#include "json.hpp"

using json = nlohmann::ordered_json;

class BaseRTTI
{
public:
	virtual ~BaseRTTI() = default;

	virtual void LoadFromJson(const json&) = 0;
	virtual json SaveToJson() = 0;
};