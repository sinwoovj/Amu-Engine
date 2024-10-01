#include "GameObject.h"
#include "../ComponentManager/BaseComponent.h"
#include "../GameObjectManager/GameObjectManager.h"

GameObject::GameObject() : type(None)
{
	name = "";
	GameObjectManager::GetInstance().AddObject(this);
}

GameObject::GameObject(std::string str) : type(None)
{
	name = str;
	GameObjectManager::GetInstance().InsertObject(this, str);
}

GameObject::~GameObject()
{
	auto objects = GameObjectManager::GetInstance().GetAllObjects();
	for (auto it = objects.begin(); it != objects.end(); it++)
	{
		if (it->first == this)
		{
			it = objects.erase(it);
			break;
		}
	}

	for (auto& it : component)
	{
		if (it.second)
			delete it.second;	
	}
	component.clear();
}

BaseComponent* GameObject::GetBase(std::string typeName)
{
	auto it = component.find(typeName);
	if (it != component.end())
	{
		return it->second;
	}

	return nullptr;
}

void GameObject::RemoveComponent(std::string name)
{
	auto it = component.find(name);
	if (it != component.end())
	{
		delete it->second;
		component.erase(name);
	}
}

void GameObject::clear()
{
	for (auto& it : component)
	{
		if (it.second)
			delete it.second;
	}
}
