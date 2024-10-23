#include "GameObjectManager.h"
#include "../Components/SpriteComp.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	for (auto it : objects)
	{
		if (it.second)
			delete it.second;
	}
}

void GameObjectManager::Update()
{
	//sorting objects for layer

	//update objects
	for (auto& obj : objects)
	{
		GameObject* o = obj.second;
		//sorting objects for orderinlayer of spriteComp
		if(o->GetComponent<SpriteComp>() != nullptr)
			o->GetComponent<SpriteComp>()->Update();
	}
}

std::vector<std::string> GameObjectManager::GetLayers()
{
	return Layer;
}

std::vector<std::string> GameObjectManager::GetTags()
{
	return Tag;
}

bool GameObjectManager::AddObjectLayer(std::string str)
{
	if (!ExistObjectLayer(str)) {
		Layer.push_back(str);
		return true;
	}
	return false;
}

bool GameObjectManager::RemoveObjectLayer(std::string str)
{
	if (ExistObjectLayer(str)){
		Layer.erase(remove(Layer.begin(), Layer.end(), str), Layer.end());
		return true;
	}
	return false;
}

bool GameObjectManager::ExistObjectLayer(std::string str)
{
	for (auto& it : Layer)
	{
		if (it == str)
			return true;
	}
	return false;
}

void GameObjectManager::SetObjectLayer(std::string obj, std::string layer)
{
	if(objects.find(obj) != objects.end())
		objects.find(obj)->second->SetLayer(layer);
}

std::string GameObjectManager::GetObjectLayer(std::string obj)
{
	if (objects.find(obj) != objects.end())
		return objects.find(obj)->second->GetLayer();
}

bool GameObjectManager::AddObjectTag(std::string str)
{
	if (!ExistObjectTag(str)){
		Tag.push_back(str);
		return true;
	}
	return false;
}

bool GameObjectManager::RemoveObjectTag(std::string str)
{
	if (ExistObjectTag(str)){
		Tag.erase(remove(Layer.begin(), Layer.end(), str), Layer.end());
		return true;
	}
	return false;
}

bool GameObjectManager::ExistObjectTag(std::string str)
{
	for (auto& it : Tag)
	{
		if (it == str)
			return true;
	}
	return false;
}

void GameObjectManager::SetObjectTag(std::string obj, std::string tag)
{
	if (objects.find(obj) != objects.end())
		objects.find(obj)->second->SetTag(tag);
}

std::string GameObjectManager::GetObjectTag(std::string obj)
{
	if (objects.find(obj) != objects.end())
		return objects.find(obj)->second->GetTag();
}

void GameObjectManager::InsertObject(const std::string& id, GameObject* obj)
{
	objects.insert({ id, obj });
}

bool GameObjectManager::AddObject(const std::string& id)
{
	if (objects.find(id) != objects.end())
		return false;
	objects.insert({ id, new GameObject(id)});
	return true;
}

GameObject* GameObjectManager::GetObj(const std::string& id) {
	// my_Obj의 모든 요소를 순회하며 ID를 찾음
	for (const auto& pair : objects) {
		if (pair.first == id) {
			return pair.second;
		}
	}
	// 일치하는 ID가 없을 경우 nullptr 반환
	return nullptr;
}

GameObject* GameObjectManager::GetLastObject()
{
	if (!objects.empty())
	{
		auto it = objects.end();
		--it;
		auto value = it->second;
		return value;
	}
	return nullptr;
}

void GameObjectManager::RemoveObject(const std::string& id)
{
	for (auto it = objects.begin(); it != objects.end(); it++)
	{
		if (it->first == id)
		{
			delete it->second;
			it = objects.erase(it);
			return;
		}
	}
}

void GameObjectManager::RemoveAllObject()
{
	for (auto it = objects.begin(); it != objects.end(); it++)	
	{
		delete it->second;
	}

	objects.clear();
}
