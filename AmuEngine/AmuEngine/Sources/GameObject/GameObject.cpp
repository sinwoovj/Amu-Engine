#include "GameObject.h"
#include "../ComponentManager/BaseComponent.h"
#include "../Components/Components.h"
#include "../GameObjectManager/GameObjectManager.h"


GameObject::GameObject(std::string str) : type(None)
{
	name = str;
	GameObjectManager::GetInstance().InsertObject(str, this);
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
		if (!this->ExistComponent("TransformComp"))
			this->AddComponent("TransformComp");
		this->AddComponent<SpriteComp>();
	}
	else if (name == compName[1])
	{
		this->AddComponent<TransformComp>();
	}
	else if (name == compName[2])
	{
		if (!this->ExistComponent("TransformComp"))
			this->AddComponent("TransformComp");
		this->AddComponent<ColliderComp>();
	}
	else if (name == compName[3])
	{

		if (!this->ExistComponent("ColliderComp"))
			this->AddComponent("ColliderComp");
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

void GameObject::LoadFromJson(std::string name, json& comp)
{
	if (name == compName[0])
	{
		this->GetComponent<SpriteComp>()->LoadFromJson(comp);
	}
	else if (name == compName[1])
	{
		this->GetComponent<TransformComp>()->LoadFromJson(comp);
	}
	else if (name == compName[2])
	{
		this->GetComponent<ColliderComp>()->LoadFromJson(comp);
	}
	else if (name == compName[3])
	{
		this->GetComponent<RigidbodyComp>()->LoadFromJson(comp);
	}
}

void GameObject::RemoveComponent(std::string name)
{
	if (name == compName[0])
	{
		this->DeleteComponent<SpriteComp>();
	}
	else if (name == compName[1])
	{
		if (this->ExistComponent("SpriteComp"))
			this->DeleteComponent<SpriteComp>();
		if (this->ExistComponent("RigidbodyComp"))
			this->DeleteComponent<RigidbodyComp>();
		if (this->ExistComponent("ColliderComp"))
			this->DeleteComponent<ColliderComp>();
		this->DeleteComponent<TransformComp>();
	}
	else if (name == compName[2])
	{
		if (this->ExistComponent("RigidbodyComp"))
			this->DeleteComponent<RigidbodyComp>();
		this->DeleteComponent<ColliderComp>();
	}
	else if (name == compName[3])
	{
		this->DeleteComponent<RigidbodyComp>();
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
