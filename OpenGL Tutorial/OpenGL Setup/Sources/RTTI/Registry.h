#pragma once
#include <string>
#include <map>
#include "BaseRTTI.h"
#include "../GameObject/GameObject.h"

class Registry
{
private:
	// map with names-function_pointers
	std::map<std::string, BaseRTTI* (*)(GameObject* owner)> rttiMap;

	Registry();
	~Registry() = default;

	Registry(const Registry&) = delete;
	const Registry& operator =(const Registry&) = delete;

	static Registry* ptr;

public:
	static Registry& GetInstance()
	{
		static Registry instance;
		return instance;
	}

	// Some interface to find inside me
	BaseRTTI* FindAndCreate(const std::string& type, GameObject* owner);
};