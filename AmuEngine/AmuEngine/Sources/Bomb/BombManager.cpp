#include "BombManager.h"
#include "BombComp.h"
#include "../GameObjectManager/GameObjectManager.h"

BOMB::BombManager::~BombManager()
{

}
void BOMB::BombManager::Update()
{
	/*for (auto& bomb : bombs)
	{
		if (bomb.second != nullptr)
		{
			if (bomb.second->GetComponent<BOMB::BombComp>() != nullptr)
				bomb.second->GetComponent<BOMB::BombComp>()->Update();
		}
		if (!bombs.empty())
		{
			return;
		}
	}*/

	for (auto it = bombs.begin(); it != bombs.end(); ) {
		if (it->second != nullptr) {
			auto bombComp = it->second->GetComponent<BOMB::BombComp>();
			if (bombComp != nullptr) {
				bombComp->Update();
			}
			// BombDelete 상태인 경우 객체를 삭제
			if (it->second->GetComponent<BOMB::BombComp>()->state == Data::BombData::BombDelete) {
				std::string own = it->second->GetName();
				it = bombs.erase(it);  // 현재 요소 삭제 후 다음 요소로 이동
				GameObjectManager::GetInstance().RemoveObject(own);
			}
			else {
				++it;  // 삭제하지 않으면 다음 요소로 이동
			}
		}
	}
}

void BOMB::BombManager::AddBomb(GameObject* obj)
{
	bombs.insert({ obj->GetName(), obj });
}
