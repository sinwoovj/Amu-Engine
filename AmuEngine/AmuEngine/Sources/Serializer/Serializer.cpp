#include <fstream>
#include "Serializer.h"
#include "../ComponentManager/BaseComponent.h"
#include "../ComponentManager/ComponentManager.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Components/Components.h"
#include "../RTTI/Registry.h"
#include "../Prefab/Prefab.h"
#include "../Level/LevelManager.h"
#include "../Editor/MainEditor.h"
#include "../Data/Data.h"
#include "../Data/DataManager.h"
#include <Utils.h>

json Serializer::GetLevelData(const std::string& str)
{
	auto lvls = LevelManager::GetInstance().GetLevels();
	if (std::find(lvls.begin(),	lvls.end(), str) ==	lvls.end()) //levels 벡터 안에 str에 해당하는 값이 없을 경우
		return nullptr;

	// Open file
	std::fstream file;
	std::string filename = LevelManager::GetInstance().GetDirectory() + str + LevelManager::GetInstance().GetFilenameExtension();
	file.open(filename, std::fstream::in);

	// Check the file is valid
	if (!file.is_open())
		return nullptr;
	//throw std::invalid_argument("Serializer::LoadLevel Invalid filename " + filename);

	json allData;
	file >> allData;	// the json has all the file data

	return allData;
}

json Serializer::GetObjectData(json level, const std::string& str)
{
	json objects;
	objects = level.find("objects").value();

	for (auto& item : objects)
	{
		auto objIt = item.find("object");
		
		if (objIt.value() == str)
			return item;
	}
	return nullptr;
}

json Serializer::GetComponentData(json Object, const std::string& str)
{

	auto compIt = Object.find("components");
	if (compIt == Object.end())
		return nullptr;

	// iterate on the json on cmp for each component, add it
	for (auto& comp : *compIt)
	{
		auto dataIt = comp.find("type");
		if (dataIt == comp.end())	// not found
			continue;

		std::string typeName = dataIt.value().dump();	// convert to string
		typeName = typeName.substr(1, typeName.size() - 2);

		if (typeName == str)
			return comp;
	}
	return nullptr;
}

bool Serializer::LoadLevel(const std::string& str)
{
	if (str == "") //초기값일 경우
		return true;

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

	file.close();

	json objects;
	objects = allData.find("objects").value();

	for (auto& item : objects)
	{
		auto objIt = item.find("object");

		GameObject* go;
		//prefab setting
		Prefab p(objIt.value());
		if (p.GetData() == nullptr) go = new GameObject(objIt.value());
		else go = p.NewGameObject(objIt.value());

		if (objIt != item.end())
		{
			// layer
			std::string layerName = item.find("layer").value().dump();
			layerName = layerName.substr(1, layerName.size() - 2);
			go->SetLayer(layerName);
			// tag
			std::string tagName = item.find("tag").value().dump();
			tagName = tagName.substr(1, tagName.size() - 2);
			go->SetTag(tagName);

			// component
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

				if (p.GetData() == nullptr)
				{
					go->AddComponent(typeName);
				}
				go->LoadFromJson(typeName, comp);
			}
		}
	}
	return true;
}

bool Serializer::ExistChangePoint(const std::string& str)
{

	//Set json
	json currData;

	if (GameObjectManager::GetInstance().GetAllObjects().size() <= 0)
	{
		std::string defaultLvlFilename = "./Sources/default.lvl";

		// Open file
		std::fstream defaultLvlFile;
		defaultLvlFile.open(defaultLvlFilename, std::fstream::in);

		// Check the file is valid
		if (!defaultLvlFile.is_open())
			throw std::invalid_argument("defaultLvlFile Invalid filename " + defaultLvlFilename);

		json allData;
		defaultLvlFile >> allData;	// the json has all the file data
		currData = allData;
	}
	else
	{
		for (auto go : GameObjectManager::GetInstance().GetAllObjects())
		{
			if (go.second->prefabName.compare("") == 0)
				continue;

			json obj;
			obj["object"] = go.second->prefabName;

			json components;

			TransformComp* t = go.second->GetComponent<TransformComp>();
			if (t != nullptr)
				components.push_back(t->SaveToJson());

			SpriteComp* s = go.second->GetComponent<SpriteComp>();
			if (s != nullptr)
				components.push_back(s->SaveToJson());

			//Rigidbody, ColliderComp 추가 예정

			obj["components"] = components;

			currData["objects"].push_back(obj);
		}
	}

	// Open file
	//std::fstream currfile;
	//std::string tmpfilename = "./Sources/tmp.lvl";
	//currfile.open(tmpfilename, std::fstream::out);	// Open as write mode. Create it if it does not exist!

	//if (!currfile.is_open())
	//	throw std::invalid_argument("Serializer::SaveLevel file write error " + str);

	//currfile << std::setw(2) << currData;	// Separates in lines and each section

	//currfile.close();

	// Get Data in File
	// Open file
	std::fstream file;
	std::string filename = LevelManager::GetInstance().GetDirectory() + str + LevelManager::GetInstance().GetFilenameExtension();
	file.open(filename, std::fstream::in);

	// Check the file is valid
	if (!file.is_open())
		throw std::invalid_argument("Serializer::LoadLevel Invalid filename " + filename);

	json fileData;
	file >> fileData;	// the json has all the file data

	if (fileData == currData)
		return false;
	else
		return true;
}

bool Serializer::SaveLevel(const std::string& str)
{
	json allData;

	if (GameObjectManager::GetInstance().GetAllObjects().size() <= 0)
	{
		std::string defaultLvlFilename = "./Sources/default.lvl";

		// Open file
		std::fstream defaultLvlFile;
		defaultLvlFile.open(defaultLvlFilename, std::fstream::in);

		// Check the file is valid
		if (!defaultLvlFile.is_open())
			throw std::invalid_argument("defaultLvlFile Invalid filename " + defaultLvlFilename);

		defaultLvlFile >> allData;	// the json has all the file data
	}
	else
	{
		for (auto go : GameObjectManager::GetInstance().GetAllObjects())
		{
			/*if (go.second->prefabName.compare("") == 0)
				continue;*/

			json obj;
			obj["object"] = go.first;

			// Layer
			obj["layer"] = go.second->layer;
			// Tag
			obj["tag"] = go.second->tag;
			
			// Component
			json components;

			if (!go.second->GetComponents().empty())
			{
				TransformComp* t = go.second->GetComponent<TransformComp>();
				if (t != nullptr)
					components.push_back(t->SaveToJson());

				SpriteComp* s = go.second->GetComponent<SpriteComp>();
				if (s != nullptr)
					components.push_back(s->SaveToJson());
				
				RigidbodyComp* r = go.second->GetComponent<RigidbodyComp>();
				if (r != nullptr)
					components.push_back(r->SaveToJson());
				
				ColliderComp* c = go.second->GetComponent<ColliderComp>();
				if (c != nullptr)
					components.push_back(c->SaveToJson());

				PlayerComp* p = go.second->GetComponent<PlayerComp>();
				if (p != nullptr)
					components.push_back(p->SaveToJson());

				BOMB::BombComp* b = go.second->GetComponent<BOMB::BombComp>();
				if (b != nullptr)
					components.push_back(b->SaveToJson());
			}
			else
			{
				components = "";
			}
			obj["components"] = components;

			allData["objects"].push_back(obj);
		}
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

void Serializer::LoadEditorSetting()
{
	// Open file
	std::fstream file;
	std::string editorFileName = editor::MainEditor::editor_data.editorFileName;
	file.open(editorFileName, std::fstream::in);

	// Check the file is valid
	if (!file.is_open())
	{
		file.close();
		SaveEditorSetting();
		file.open(editorFileName, std::fstream::in);
	}

	json allData;
	file >> allData;	// the json has all the file data

	file.close();

	json layers;
	layers = allData.find("layers").value();

	for (auto& layer : layers)
	{
		std::string layerName = layer.dump();	// convert to string
		layerName = layerName.substr(1, layerName.size() - 2);
		GameObjectManager::GetInstance().AddObjectLayer(layerName);
	}

	json tags;
	tags = allData.find("tags").value();

	for (auto& tag : tags)
	{
		std::string tagName = tag.dump();	// convert to string
		tagName = tagName.substr(1, tagName.size() - 2);
		GameObjectManager::GetInstance().AddObjectTag(tagName);
	}
}

void Serializer::SaveEditorSetting()
{
	json allData;
	
	std::string editorFileName = editor::MainEditor::editor_data.editorFileName;

	std::ofstream editorFile(editorFileName);

	if (!editorFile.is_open())
	{
		std::cout << "editor file open fail" << std::endl;
		throw std::invalid_argument("defaultEditorFile Invalid filename " + editorFileName);
	}

	allData["layers"] = GameObjectManager::GetInstance().GetLayers();
	allData["tags"] = GameObjectManager::GetInstance().GetTags();

	editorFile << std::setw(2) << allData;	// Separates in lines and each section

	editorFile.close();
}

void Serializer::LoadGameDataSetting()
{
	// Open file
	std::fstream file;
	std::string gameDataFileName = Data::gameDataFileName;
	file.open(gameDataFileName, std::fstream::in);

	// Check the file is valid
	if (!file.is_open())
	{
		file.close();
		SaveGameDataSetting();
		file.open(gameDataFileName, std::fstream::in);
	}

	json allData;
	file >> allData;	// the json has all the file data

	file.close();

	Data::DataManager::GetInstance().LoadFromJson(allData);
}

void Serializer::SaveGameDataSetting()
{
	json allData;

	std::string gameDataFileName = Data::gameDataFileName;

	std::ofstream gameDataFile(gameDataFileName);

	if (!gameDataFile.is_open())
	{
		std::cout << "gameData file open fail" << std::endl;
		throw std::invalid_argument("defaultGameDataFile Invalid filename " + gameDataFileName);
	}
	
	allData = Data::DataManager::GetInstance().SaveToJson();

	gameDataFile << std::setw(2) << allData;	// Separates in lines and each section

	gameDataFile.close();
}
