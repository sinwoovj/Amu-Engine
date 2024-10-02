#pragma once
#include <vector>
#include "../Components/ColliderComp.h"
#include "../Components/TransformComp.h"
#include "../EventManager/EventManager.h"
#include "../Event/CollisionEvent.h"
#include <AMType.h>

class CollisionManager
{
private:
	CollisionManager();

	CollisionManager(const CollisionManager& other) = delete;
	const CollisionManager& operator=(const CollisionManager& other) = delete;
	~CollisionManager();

	static CollisionManager* ptr;

	std::vector<ColliderComp*> colliderList;

	bool isCollisionPointTri(ColliderComp*, ColliderComp*) const;
	bool isCollisionPointSquare(ColliderComp*, ColliderComp*) const;
	bool isCollisionSquareTri(ColliderComp*, ColliderComp*) const;
	bool isCollisionOBB(ColliderComp*, ColliderComp*) const;
	bool isCollisionAABB(ColliderComp*, ColliderComp*) const;
	bool isCollisionCircleCircle(ColliderComp*, ColliderComp*) const;

	bool PointTriCheck(ColliderComp*, ColliderComp*);
	bool PointSquareCheck(ColliderComp*, ColliderComp*);

	bool PlayerTriCheck(ColliderComp*, ColliderComp*);
	bool PlayerSquareCheck(ColliderComp*, ColliderComp*);

	bool EnemyTriCheck(ColliderComp*, ColliderComp*);
	bool EnemySquareCheck(ColliderComp*, ColliderComp*);

	bool CheckerTriCheck(ColliderComp*, ColliderComp*);
	bool CheckerSquareCheck(ColliderComp*, ColliderComp*);

	bool ProjectileEnemyCheck(ColliderComp*, ColliderComp*);
	bool ProjectilePlayerCheck(ColliderComp*, ColliderComp*);
	bool ProjectileTriCheck(ColliderComp*, ColliderComp*);
	bool ProjectileSquareCheck(ColliderComp*, ColliderComp*);

public:
	static bool isCollision(GameObject::Type, Vec2, Vec2, GameObject::Type, Vec2, Vec2);

	static CollisionManager& GetInstance()
	{
		static CollisionManager instance;
		return instance;
	}

	void AddCollider(ColliderComp* trans);
	void DelCollider(ColliderComp* trans);

	void Update();
};