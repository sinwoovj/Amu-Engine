#include <fstream>
#include "Serializer.h"
#include "json.hpp"
#include "../ComponentManager/BaseComponent.h"
#include "../ComponentManager/ComponentManager.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Components/Components.h"
#include "../RTTI/Registry.h"
#include "../Prefab/Prefab.h"
#include "../Level/LevelManager.h"

using json = nlohmann::ordered_json;	// Map. Orders the order the variables were declared in

bool Serializer::LoadLevel(const std::string& str)
{
	// Open file
	std::fstream file;
	std::string filename = LevelManager::GetInstance().GetDirectory() + str + LevelManager::GetInstance().GetFilenameExtension();
	file.open(filename, std::fstream::in);

	// Check the file is valid
	if (!file.is_open())
		return false;
		//throw std::invalid_argument("Serializer::LoadLevel Invalid filename " + filename);

	json allData;
	file >> allData;	// the json has all the file data

	json objects;
	objects = allData.find("objects").value();

	for (auto& item : objects)
	{
		auto objIt = item.find("object");
		Prefab p(objIt.value());
		GameObject* go = p.NewGameObject(objIt.value());

		if (objIt != item.end())
		{
			auto compIt = item.find("components");
			if (compIt == item.end())
				continue;

			// iterate on the json on cmp for each component, add it
			for (auto& comp : *compIt)
			{
				auto dataIt = comp.find("type");
				if (dataIt == comp.end())	// not found
					continue;

				std::string typeName = dataIt.value().dump();	// convert to string
				typeName = typeName.substr(1, typeName.size() - 2);

				go->GetBase(typeName)->LoadFromJson(comp);
			}
		}

		if (go->GetComponent<ColliderComp>() != nullptr)
			go->GetComponent<ColliderComp>()->SetCollider();
	}
	return true;
}

bool Serializer::ExistChangePoint(const std::string& str)
{
	json allData;

	// Counter instead of name as I do not have one
	int i = 0;

	for (auto go : GameObjectManager::GetInstance().GetAllObjects())
	{
		if (go.first->prefabName.compare("") == 0)
			continue;

		json obj;
		obj["object"] = go.first->prefabName;

		json components;

		TransformComp* t = go.first->GetComponent<TransformComp>();
		if (t != nullptr)
			components.push_back(t->SaveToJson());

		SpriteComp* s = go.first->GetComponent<SpriteComp>();
		if (s != nullptr)
			components.push_back(s->SaveToJson());

		obj["components"] = components;

		if (go.first->name.size() > 0)
		{
			allData[go.first->name] = obj;
		}
		else
			allData["objects"].push_back(obj);
	}

	// Open file
	std::string filename = LevelManager::GetInstance().GetDirectory() + str + LevelManager::GetInstance().GetFilenameExtension();
	std::fstream file;
	file.open(filename, std::fstream::in);
	std::ifstream ifile(filename, std::ios::binary | std::ios::ate);
	
	if (!file.is_open())
		 throw std::invalid_argument("Serializer::SaveLevel file write error " + filename);
	if (ifile.tellg() == 0)
		return false;

	json j;
	file >> j;

	if (j == allData)
		return false;
	else
		return true;
}

bool Serializer::SaveLevel(const std::string& str)
{
	json allData;

	// Counter instead of name as I do not have one
	int i = 0;

	for (auto go : GameObjectManager::GetInstance().GetAllObjects())
	{
		if (go.first->prefabName.compare("") == 0)
			continue;

		json obj;
		obj["object"] = go.first->prefabName;

		json components;

		TransformComp* t = go.first->GetComponent<TransformComp>();
		if (t != nullptr)
			components.push_back(t->SaveToJson());

		SpriteComp* s = go.first->GetComponent<SpriteComp>();
		if (s != nullptr)
			components.push_back(s->SaveToJson());
		
		obj["components"] = components;

		if (go.first->name.size() > 0)
		{
			allData[go.first->name] = obj;
		}
		else
			allData["objects"].push_back(obj);
	}

	// Open file
	std::fstream file;
	std::string filename = LevelManager::GetInstance().GetDirectory() + str + LevelManager::GetInstance().GetFilenameExtension();
	file.open(filename, std::fstream::out);	// Open as write mode. Create it if it does not exist!

	if (!file.is_open())
		return false;
		//throw std::invalid_argument("Serializer::SaveLevel file write error " + str);

	file << std::setw(2) << allData;	// Separates in lines and each section

	file.close();
	return true;
}
