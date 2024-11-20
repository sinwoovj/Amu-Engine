#pragma once
#include <vector>
#include "../Components/ColliderComp.h"
#include "../Components/RigidbodyComp.h"
#include "../Components/TransformComp.h"
#include "../EventManager/EventManager.h"
#include "../Event/CollisionEvent.h"
#include <opengl.h>

class CollisionManager
{
private:
	CollisionManager();

	CollisionManager(const CollisionManager& other) = delete;
	const CollisionManager& operator=(const CollisionManager& other) = delete;
	~CollisionManager();

	static CollisionManager* ptr;
	std::vector<ColliderComp*> colliderList;
	std::vector<RigidbodyComp*> rigidbodyList;
	bool isCollisionPointTri(ColliderComp*, ColliderComp*) const;
	bool isCollisionPointSquare(ColliderComp*, ColliderComp*) const;
	bool isCollisionSquareTri(ColliderComp*, ColliderComp*) const;
	bool isCollisionOBB(ColliderComp*, ColliderComp*) const;
	bool isCollisionAABB(ColliderComp*, ColliderComp*) const;
	bool isCollisionCircleCircle(ColliderComp*, ColliderComp*) const;

	bool PointTriCheck(ColliderComp*, ColliderComp*);
	bool PointSquareCheck(ColliderComp*, ColliderComp*);

	bool CheckerTriCheck(ColliderComp*, ColliderComp*);
	bool CheckerSquareCheck(ColliderComp*, ColliderComp*);
public:
	static bool isCollision(GameObject::Type, glm::vec2, glm::vec2, GameObject::Type, glm::vec2, glm::vec2);

	static CollisionManager& GetInstance()
	{
		static CollisionManager instance;
		return instance;
	}

	void AddCollider(ColliderComp* trans);
	void DelCollider(ColliderComp* trans);
	void AddRigidbody(RigidbodyComp* rigid);
	void DelRigidbody(RigidbodyComp* rigid);

	void Update();
};