#include "GameObject.h"
#include "../ComponentManager/BaseComponent.h"
#include "../Components/Components.h"
#include "../GameObjectManager/GameObjectManager.h"


GameObject::GameObject(std::string str) : type(None)
{
	name = str;
	GameObjectManager::GetInstance().InsertObject(str , this);
}

GameObject::~GameObject()
{
	auto objects = GameObjectManager::GetInstance().GetAllObjects();
	for (auto it = objects.begin(); it != objects.end(); it++)
	{
		if (it->second == this)
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

void GameObject::AddComponent(std::string name)
{
	if (name == compName[0])
	{
		this->AddComponent<SpriteComp>();
	}
	else if (name == compName[1])
	{
		this->AddComponent<TransformComp>();
	}
	else if (name == compName[2])
	{
		this->AddComponent<ColliderComp>();
	}
	else if (name == compName[3])
	{
		this->AddComponent<RigidbodyComp>();
	}
}

bool GameObject::ExistComponent(std::string name)
{
	auto it = component.find(name);
	if (it != component.end())
	{
		return true;
	}
	return false;
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
