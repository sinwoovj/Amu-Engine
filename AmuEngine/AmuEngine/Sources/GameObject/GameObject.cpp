#include "GameObject.h"
#include "../Serializer/Serializer.h"
#include "../ComponentManager/BaseComponent.h"
#include "../Components/Components.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../GSM/GameStateManager.h"
#include "../Level/NormalLevel.h"

GameObject::GameObject(std::string str) : type(None)
{
	name = str;
	layer = "Default";
	tag = "Untagged";
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
		this->GetComponent<SpriteComp>()->SetTexture(this->GetComponent<SpriteComp>()->GetTexturePath());
		
		/*Serializer* sz = &Serializer::GetInstance();
		auto compData = sz->GetComponentData(sz->GetObjectData(
			sz->GetLevelData(dynamic_cast<level::NormalLevel*>(GSM::GameStateManager::GetInstance().GetCurrentLevel())->GetName()),
			this->name),
		name);
		this->GetComponent<SpriteComp>()->LoadFromJson(compData);*/
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
		this->GetComponent<ColliderComp>()->SetCollider();
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
