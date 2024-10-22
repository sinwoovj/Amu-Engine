#include "BombComp.h"
#include "../Bomb/BombManager.h"


BOMB::BombComp::BombComp(GameObject* _owner)
{
	owner = _owner;
	BOMB::BombManager::GetInstance().AddBomb(_owner);
}

BOMB::BombComp::~BombComp()
{

}
