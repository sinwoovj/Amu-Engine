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
			// BombDelete ������ ��� ��ü�� ����
			if (it->second->GetComponent<BOMB::BombComp>()->state == Data::BombData::BombDelete) {
				std::string own = it->second->GetName();
				it = bombs.erase(it);  // ���� ��� ���� �� ���� ��ҷ� �̵�
				GameObjectManager::GetInstance().RemoveObject(own);
			}
			else {
				++it;  // �������� ������ ���� ��ҷ� �̵�
			}
		}
	}
}

void BOMB::BombManager::AddBomb(GameObject* obj)
{
	bombs.insert({ obj->GetName(), obj });
}
