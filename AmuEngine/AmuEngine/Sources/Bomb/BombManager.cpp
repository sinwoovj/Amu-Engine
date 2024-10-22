#include "BombManager.h"

BOMB::BombManager::~BombManager()
{

}
void BOMB::BombManager::Update()
{

}

void BOMB::BombManager::AddBomb(GameObject* obj)
{
	bombs.insert({ obj->GetName(), obj });
}
