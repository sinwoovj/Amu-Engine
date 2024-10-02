#pragma once
#include <string>
#include <fstream>
#include <list>
#include "json.hpp"
#include "../GameObject/GameObject.h"
#include "../ComponentManager/BaseComponent.h"
#include "../RTTI/Registry.h"

using json = nlohmann::ordered_json;

class Prefab
{
private:
	std::string prefabName;
	json* data;

	void LoadPrefab();

public:
	Prefab(std::string _name);
	~Prefab();

	static void SavePrefab(const std::string& _name, GameObject* obj);
	
	GameObject* NewGameObject();
	GameObject* NewGameObject(const std::string& _name);
};