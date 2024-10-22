#include "BombComp.h"
#include "../Bomb/BombManager.h"
#include "../GameObject/GameObject.h"


BOMB::BombComp::BombComp(GameObject* _owner)
{
	owner = _owner;
	BOMB::BombManager::GetInstance().AddBomb(_owner);
}

BOMB::BombComp::~BombComp()
{

}
