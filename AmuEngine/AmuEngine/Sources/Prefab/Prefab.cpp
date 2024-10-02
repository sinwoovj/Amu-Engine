#include "Prefab.h"

Prefab::Prefab(std::string _name) : data(nullptr), prefabName(_name)
{
	LoadPrefab();
}

Prefab::~Prefab()
{
	if (data)
		delete data;
}

void Prefab::SavePrefab(const std::string& _name, GameObject* obj)
{
	std::string filename = "./Assets/Prefab/" + _name + ".prefab";

	json prefab;
	prefab["entityType"] = obj->type;

	json components;
	for (auto comp : obj->component)
	{
		BaseComponent* c = comp.second;
		components.push_back(c->SaveToJson());
	}
	prefab["components"] = components;

	std::fstream file;
	file.open(filename, std::fstream::out);

	if (!file.is_open())
		throw std::invalid_argument("Prefab::SavePrefab file write error " + filename);

	file << std::setw(2) << prefab;

	file.close();
}

void Prefab::LoadPrefab()
{
	std::string filename = "./Assets/Prefab/" + prefabName + ".prefab";
	std::fstream file;

	file.open(filename, std::fstream::in);

	if (!file.is_open())
		throw std::invalid_argument("Prefab::LoadPrefab Invalid filename " + filename);

	data = new json;

	file >> *data;
}

GameObject* Prefab::NewGameObject()
{
	GameObject* obj = new GameObject();

	auto typeIt = data->find("entityType");
	if (typeIt == data->end())
		return nullptr;
	
	obj->type = typeIt.value();

	auto compIt = data->find("components");
	if (compIt == data->end())
		return nullptr;

	for (auto& comp : *compIt)
	{
		auto dataIt = comp.find("type");
		if (dataIt == comp.end())
			continue;

		std::string typeName = dataIt.value().dump();
		typeName = typeName.substr(1, typeName.size() - 2);

		BaseRTTI* p = Registry::GetInstance().FindAndCreate(typeName, obj);
		if (p != nullptr)
			p->LoadFromJson(comp);
	}

	obj->prefabName = prefabName;

	return obj;
}

GameObject* Prefab::NewGameObject(const std::string& _name)
{
	GameObject* obj = new GameObject(_name);

	auto typeIt = data->find("entityType");
	if (typeIt == data->end())
		return nullptr;

	obj->type = typeIt.value();

	auto compIt = data->find("components");
	if (compIt == data->end())
		return nullptr;

	for (auto& comp : *compIt)
	{
		auto dataIt = comp.find("type");
		if (dataIt == comp.end())
			continue;

		std::string typeName = dataIt.value().dump();
		typeName = typeName.substr(1, typeName.size() - 2);

		BaseRTTI* p = Registry::GetInstance().FindAndCreate(typeName, obj);
		if (p != nullptr)
			p->LoadFromJson(comp);
	}

	obj->prefabName = prefabName;

	return obj;
}
