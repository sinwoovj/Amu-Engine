#include "CollisionManager.h"
#include "../Utils/Utils.h"


CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{

}

bool CollisionManager::isCollisionPointTri(ColliderComp* a, ColliderComp* b) const
{
	if (!isCollisionPointSquare(a, b)) return false;

	float aX = a->GetPos().x;
	float aY = a->GetPos().y;

	float bX = b->GetPos().x;
	float bY = b->GetPos().y;
	float bW = b->GetScale().x / 2;
	float bH = b->GetScale().y / 2;

	float grad;

	if (b->GetOwner()->type == GameObject::RightTri)
		grad = bH / bW;
	else
		grad = -bH / bW;

	if ((grad * aX) + bY - (grad * bX) < aY) return false;

	return true;
}

bool CollisionManager::isCollisionPointSquare(ColliderComp* a, ColliderComp* b) const
{
	float aX = a->GetPos().x;
	float aY = a->GetPos().y;

	float bX = b->GetPos().x;
	float bY = b->GetPos().y;
	float bW = b->GetScale().x / 2;
	float bH = b->GetScale().y / 2;

	if (aX > bX + bW) return false;
	if (aX < bX - bW) return false;
	if (aY > bY + bH) return false;
	if (aY < bY - bH) return false;

	return true;
}

bool CollisionManager::isCollisionSquareTri(ColliderComp* a, ColliderComp* b) const
{
	if (!isCollisionAABB(a, b)) return false;

	float aX = a->GetPos().x;
	float aY = a->GetPos().y;
	float aW = a->GetScale().x / 2;
	float aH = a->GetScale().y / 2;

	float bX = b->GetPos().x;
	float bY = b->GetPos().y;
	float bW = b->GetScale().x / 2;
	float bH = b->GetScale().y / 2;

	float grad;

	if (b->GetOwner()->type == GameObject::RightTri)
	{
		grad = bH / bW;
		if ((grad * (aX + aW)) + bY - (grad * bX) < (aY - aH)) return false;
	}
	else
	{
		grad = -bH / bW;
		if ((grad * (aX - aW)) + bY - (grad * bX) < (aY - aH)) return false;
	}

	return true;
}

bool CollisionManager::isCollisionOBB(ColliderComp* a, ColliderComp* b) const
{
	float minDotProducts[4];

	float minDotProduct;
	float maxDotProduct;

	// Check colA's normal vector
	for (int i = 0; i < 4; i++)
	{
		int in = (i + 1) % 4;

		glm::vec2 normal{
			a->vertices[in].x - a->vertices[i].x,
			a->vertices[in].y - a->vertices[i].y };

		minDotProduct = 1'000'000;

		for (const glm::vec3& vB : b->vertices)
		{
			glm::vec2 vecAB{
				vB.x - a->vertices[in].x, vB.y - a->vertices[in].y
			};

			float dotProduct = normal.x * vecAB.x + normal.y * vecAB.y;
			if (minDotProduct > dotProduct)
				minDotProduct = dotProduct;
		}

		minDotProducts[in] = minDotProduct;
	}

	maxDotProduct = minDotProducts[0];
	for (int i = 1; i < 4; i++)
	{
		if (maxDotProduct < minDotProducts[i])
			maxDotProduct = minDotProducts[i];
	}

	if (maxDotProduct > 0)
		return false;
	else
		return true;
}

bool CollisionManager::isCollisionAABB(ColliderComp* a, ColliderComp* b) const
{
	float aX = a->GetPos().x;
	float aY = a->GetPos().y;
	float aW = a->GetScale().x / 2;
	float aH = a->GetScale().y / 2;

	float bX = b->GetPos().x;
	float bY = b->GetPos().y;
	float bW = b->GetScale().x / 2;
	float bH = b->GetScale().y / 2;

	if (aX - aW > bX + bW) return false;
	if (bX - bW > aX + aW) return false;
	if (aY - aH > bY + bH) return false;
	if (bY - bH > aY + aH) return false;

	return true;
}

bool CollisionManager::isCollisionCircleCircle(ColliderComp* a, ColliderComp* b) const
{
	float aX = a->GetPos().x;
	float aY = a->GetPos().y;
	float aR = a->GetScale().x / 2;

	float bX = b->GetPos().x;
	float bY = b->GetPos().y;
	float bR = b->GetScale().y / 2;

	return ((aR + bR) * (aR + bR)) >= GetSqDistance(aX, aY, bX, bY);
}

bool gIsCollisionAABB(glm::vec2 aPos, glm::vec2 aScale, glm::vec2 bPos, glm::vec2 bScale)
{
	float aX = aPos.x;
	float aY = aPos.y;
	float aW = aScale.x / 2;
	float aH = aScale.y / 2;

	float bX = bPos.x;
	float bY = bPos.y;
	float bW = bScale.x / 2;
	float bH = bScale.y / 2;

	if (aX - aW > bX + bW) return false;
	if (bX - bW > aX + aW) return false;
	if (aY - aH > bY + bH) return false;
	if (bY - bH > aY + aH) return false;

	return true;
}

bool gIsCollisionSquareTri(glm::vec2 aPos, glm::vec2 aScale, GameObject::Type bType, glm::vec2 bPos, glm::vec2 bScale)
{
	if (!gIsCollisionAABB(aPos, aScale, bPos, bScale)) return false;

	float aX = aPos.x;
	float aY = aPos.y;
	float aW = aScale.x / 2;
	float aH = aScale.y / 2;

	float bX = bPos.x;
	float bY = bPos.y;
	float bW = bScale.x / 2;
	float bH = bScale.y / 2;

	float grad;

	if (bType == GameObject::RightTri)
	{
		grad = bH / bW;
		if ((grad * (aX + aW)) + bY - (grad * bX) < (aY - aH)) return false;
	}
	else
	{
		grad = -bH / bW;
		if ((grad * (aX - aW)) + bY - (grad * bX) < (aY - aH)) return false;
	}

	return true;
}

bool CollisionManager::PointTriCheck(ColliderComp* a, ColliderComp* b)
{
	EventManager& em = EventManager::GetInstance();

	if (a->GetOwner()->type == GameObject::Point && (b->GetOwner()->type == GameObject::LeftTri || b->GetOwner()->type == GameObject::RightTri))
	{
		if (isCollisionPointTri(a, b))
		{
			em.AddEvent<CollisionEvent>(a, b);
			em.AddEvent<CollisionEvent>(b, a);
		}

		return true;
	}

	else if (b->GetOwner()->type == GameObject::Point && (a->GetOwner()->type == GameObject::LeftTri || a->GetOwner()->type == GameObject::RightTri))
	{
		if (isCollisionPointTri(b, a))
		{
			em.AddEvent<CollisionEvent>(a, b);
			em.AddEvent<CollisionEvent>(b, a);
		}

		return true;
	}

	return false;
}

bool CollisionManager::PointSquareCheck(ColliderComp* a, ColliderComp* b)
{
	EventManager& em = EventManager::GetInstance();

	if (a->GetOwner()->type == GameObject::Point && b->GetOwner()->type == GameObject::Player)
	{
		if (isCollisionPointSquare(a, b))
		{
			em.AddEvent<CollisionEvent>(a, b);
			em.AddEvent<CollisionEvent>(b, a);
		}

		return true;
	}

	else if (b->GetOwner()->type == GameObject::Point && a->GetOwner()->type == GameObject::Player)
	{
		if (isCollisionPointSquare(b, a))
		{
			em.AddEvent<CollisionEvent>(a, b);
			em.AddEvent<CollisionEvent>(b, a);
		}

		return true;
	}

	return false;
}

bool CollisionManager::CheckerTriCheck(ColliderComp* a, ColliderComp* b)
{
	EventManager& em = EventManager::GetInstance();

	if (a->GetOwner()->type == GameObject::Checker && (b->GetOwner()->type == GameObject::LeftTri || b->GetOwner()->type == GameObject::RightTri))
	{
		if (isCollisionSquareTri(a, b))
		{
			em.AddEvent<CollisionEvent>(a, b);
			em.AddEvent<CollisionEvent>(b, a);
		}

		return true;
	}

	else if (b->GetOwner()->type == GameObject::Checker && (a->GetOwner()->type == GameObject::LeftTri || a->GetOwner()->type == GameObject::RightTri))
	{
		if (isCollisionSquareTri(b, a))
		{
			em.AddEvent<CollisionEvent>(a, b);
			em.AddEvent<CollisionEvent>(b, a);
		}

		return true;
	}

	return false;
}

bool CollisionManager::CheckerSquareCheck(ColliderComp*a , ColliderComp* b)
{
	EventManager& em = EventManager::GetInstance();

	if (a->GetOwner()->type == GameObject::Checker && b->GetOwner()->type == GameObject::Square)
	{
		if (isCollisionAABB(a, b))
		{
			em.AddEvent<CollisionEvent>(a, b);
			em.AddEvent<CollisionEvent>(b, a);
		}

		return true;
	}

	else if (b->GetOwner()->type == GameObject::Checker && a->GetOwner()->type == GameObject::Square)
	{
		if (isCollisionAABB(b, a))
		{
			em.AddEvent<CollisionEvent>(a, b);
			em.AddEvent<CollisionEvent>(b, a);
		}

		return true;
	}

	return false;
}

//a : type, pos, scale - b : type, pos, scale
bool CollisionManager::isCollision(GameObject::Type aType, glm::vec2 aPos, glm::vec2 aScale, GameObject::Type bType, glm::vec2 bPos, glm::vec2 bScale)
{
	switch (aType)
	{
	case GameObject::Square:
		if (bType == GameObject::Square)
		{
			return gIsCollisionAABB(aPos, aScale, bPos, bScale);
		}
		else if (bType == GameObject::LeftTri || bType == GameObject::RightTri)
		{
			return gIsCollisionSquareTri(aPos, aScale, bType, bPos, bScale);
		}
		break;

	case GameObject::LeftTri:
	case GameObject::RightTri:
		if (bType == GameObject::Square)
		{
			return gIsCollisionSquareTri(bPos, bScale, aType, aPos, aScale);
		}
		break;
	}

	return false;
}

void CollisionManager::AddCollider(ColliderComp* trans)
{
	colliderList.push_back(trans);
}

void CollisionManager::DelCollider(ColliderComp* trans)
{
	for (auto it = colliderList.begin(); it != colliderList.end(); it++)
	{
		if (*it == trans)
		{
			colliderList.erase(it);
			break;
		}
	}
}

void CollisionManager::Update()
{
	if (colliderList.empty())
		return;

	EventManager& em = EventManager::GetInstance();

	for (unsigned int i = 0; i < colliderList.size() - 1; i++)
	{
		for (unsigned int j = i + 1; j < colliderList.size(); j++)
		{
			ColliderComp* a = colliderList[i];
			ColliderComp* b = colliderList[j];
		}
	}
}
