#include "GameObjectManager.h"
#include "../Components/SpriteComp.h"
#include <algorithm>

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

bool Comp(SpriteComp* first, SpriteComp* second)
{
	if (first->GetOrderInlayer() < second->GetOrderInlayer())
		return true;
	else
		return false;
}

void GameObjectManager::Update()
{
	//sorting objects for layer (Default, UI, Particle, ETC..)
	for (auto& layer : Layer)
	{
		std::list<SpriteComp*> orderinlayer;
		for (auto& obj : objects)
		{
			GameObject* o = obj.second;
			if (o->GetLayer() == layer)
			{
				//other component update
				
				//sorting objects for orderinlayer of spriteComp
				if (o->GetComponent<SpriteComp>() != nullptr)
					orderinlayer.push_back(o->GetComponent<SpriteComp>());
			}
		}
		//order in layer update
		orderinlayer.sort(Comp);
		for (auto& obj : orderinlayer)
		{
			obj->Update();
		}
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
	for (auto& it : DefaultLayer)
	{
		if (it == str)
			return false;
	}
	if (!ExistObjectLayer(str)) {
		Layer.push_back(str);
		return true;
	}
	return false;
}

bool GameObjectManager::RemoveObjectLayer(std::string str)
{
	for (auto& it : DefaultLayer)
	{
		if (it == str)
			return false;
	}
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
	return "";
}

void GameObjectManager::ChangeNameLayer(const std::string& oldstr, const std::string& newstr)
{
}

bool GameObjectManager::AddObjectTag(std::string str)
{
	for (auto& it : DefaultTag)
	{
		if (it == str)
			return false;
	}
	if (!ExistObjectTag(str)){
		Tag.push_back(str);
		return true;
	}
	return false;
}

bool GameObjectManager::RemoveObjectTag(std::string str)
{
	for (auto& it : DefaultTag)
	{
		if (it == str)
			return false;
	}
	if (ExistObjectTag(str)){
		Tag.erase(remove(Tag.begin(), Tag.end(), str), Tag.end());
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
	return "";
}

void GameObjectManager::ChangeNameTag(const std::string& oldstr, const std::string& newstr)
{
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

bool GameObjectManager::ExistObject(const std::string& id)
{
	for (auto it = objects.begin(); it != objects.end(); it++)
	{
		if (it->second->GetName() == id)
		{
			return true;
		}
	}
	return false;
}

void GameObjectManager::ChangeNameObject(const std::string& oldstr, const std::string& newstr)
{
	for(auto& it : objects)
	{
		if (it.second->GetName() == oldstr)
		{
			it.second->SetName(newstr);
			InsertObject(newstr, it.second);
		}
	}
	auto it = objects.find(oldstr);
	if (it != objects.end())
		objects.erase(it);
}