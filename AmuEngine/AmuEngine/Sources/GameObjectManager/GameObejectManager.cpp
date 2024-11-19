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
	std::list<SpriteComp*> objectList;
	for (auto& layer : Layer)
	{
		std::list<SpriteComp*> orderinlayer;
		for (auto& obj : objects)
		{
			GameObject* o = obj.second;
			if (o->GetComponent<SpriteComp>() != nullptr)
			{
				objectList.push_back(o->GetComponent<SpriteComp>());
				if (o->GetLayer() == layer)
				{
					//other component update

					//sorting objects for orderinlayer of spriteComp
					orderinlayer.push_back(o->GetComponent<SpriteComp>());
				}
			}
		}
		//order in layer update
		orderinlayer.sort(Comp);
		for (auto& obj : orderinlayer)
		{
			obj->SpriteUpdate();
		}
	}
	for (auto& obj : objectList)
	{
		obj->SpriteDebugUpdate();
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

bool GameObjectManager::AddObjectLayer(const std::string& str)
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

bool GameObjectManager::RemoveObjectLayer(const std::string& str)
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

bool GameObjectManager::ExistDefaultLayer(const std::string& str)
{
	for (auto& it : DefaultLayer)
	{
		if (it == str)
			return true;
	}
	return false;
}

bool GameObjectManager::ExistObjectLayer(const std::string& str)
{
	for (auto& it : Layer)
	{
		if (it == str)
			return true;
	}
	return false;
}

void GameObjectManager::SetObjectLayer(const std::string& obj, const std::string& layer)
{
	if(objects.find(obj) != objects.end())
		objects.find(obj)->second->SetLayer(layer);
}

std::string GameObjectManager::GetObjectLayer(const std::string& obj)
{
	if (objects.find(obj) != objects.end())
		return objects.find(obj)->second->GetLayer();
	return "";
}

std::vector<GameObject*> GameObjectManager::ExtractGOToLayer(const std::string& str)
{
	std::vector<GameObject*> res;
	for (auto& obj : objects)
	{
		if (obj.second->GetLayer() == str)
			res.push_back(obj.second);
	}
	return res;
}

void GameObjectManager::ChangeNameLayer(const std::string& oldstr, const std::string& newstr)
{
	for (auto& it : Layer)
	{
		if (it == oldstr)
			it = newstr;
	}
}

void GameObjectManager::OrderUpLayer(const std::string& str)
{
	for (auto it = Layer.begin(); it != Layer.end(); it++)
	{
		if (*it == str)
		{
			std::iter_swap(it - 1, it);
			return;
		}
	}
}

void GameObjectManager::OrderDownLayer(const std::string& str)
{
	for (auto it = Layer.begin(); it != Layer.end(); it++)
	{
		if (*it == str)
		{
			std::iter_swap(it + 1, it);
			return;
		}
	}
}

bool GameObjectManager::AddObjectTag(const std::string& str)
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

bool GameObjectManager::RemoveObjectTag(const std::string& str)
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

bool GameObjectManager::ExistDefaultTag(const std::string& str)
{
	for (auto& it : DefaultTag)
	{
		if (it == str)
			return true;
	}
	return false;
}

bool GameObjectManager::ExistObjectTag(const std::string& str)
{
	for (auto& it : Tag)
	{
		if (it == str)
			return true;
	}
	return false;
}

void GameObjectManager::SetObjectTag(const std::string& obj, const std::string& tag)
{
	if (objects.find(obj) != objects.end())
		objects.find(obj)->second->SetTag(tag);
}

std::string GameObjectManager::GetObjectTag(const std::string& obj)
{
	if (objects.find(obj) != objects.end())
		return objects.find(obj)->second->GetTag();
	return "";
}

std::vector<GameObject*> GameObjectManager::ExtractGOToTag(const std::string& str)
{
	std::vector<GameObject*> res;
	for (auto& obj : objects)
	{
		if (obj.second->GetTag() == str)
			res.push_back(obj.second);
	}
	return res;
}

void GameObjectManager::ChangeNameTag(const std::string& oldstr, const std::string& newstr)
{
	for (auto& it : Tag)
	{
		if (it == oldstr)
			it = newstr;
	}
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