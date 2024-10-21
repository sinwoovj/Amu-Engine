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
		o->GetComponent<SpriteComp>()->Update();
	}
}

void GameObjectManager::InsertObject(const std::string& id, GameObject* obj)
{
	objects.insert({ id, obj });
}

void GameObjectManager::AddObject(const std::string& id)
{
	objects.insert({ id, new GameObject(id)});
}

GameObject* GameObjectManager::GetObj(const std::string& id) {
	// my_Obj�� ��� ��Ҹ� ��ȸ�ϸ� ID�� ã��
	for (const auto& pair : objects) {
		if (pair.first == id) {
			return pair.second;
		}
	}
	// ��ġ�ϴ� ID�� ���� ��� nullptr ��ȯ
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
