#include "BombManager.h"
#include "BombComp.h"

BOMB::BombManager::~BombManager()
{

}
void BOMB::BombManager::Update()
{
	for (auto& bomb : bombs)
	{
		bomb.second->GetComponent<BOMB::BombComp>()->Update();
	}
}

void BOMB::BombManager::AddBomb(GameObject* obj)
{
	bombs.insert({ obj->GetName(), obj });
}

void BOMB::BombManager::RemoveBomb(GameObject* obj)
{
	auto it = bombs.find(obj->GetName());
	if (it != bombs.end()) 
	{
		bombs.erase(it);
	}
}
