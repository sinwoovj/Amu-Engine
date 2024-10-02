#include "ColliderComp.h"
#include "TransformComp.h"
#include "RigidbodyComp.h"
#include "../CollisionManager/CollisionManager.h"
#include "../EventManager/EventManager.h"

#include <AMMath.h>

ColliderComp::ColliderComp(GameObject* _owner) : EngineComponent(_owner), pos(), scale(), rot(0), vertices()
{
	CollisionManager::GetInstance().AddCollider(this);
	EventManager::GetInstance().AddEntity(this);

	SetCollider();
}

ColliderComp::~ColliderComp()
{
	CollisionManager::GetInstance().DelCollider(this);
	EventManager::GetInstance().DelEntity(this);
}

void ColliderComp::Update()
{
	vertices[0] = { -0.5f, 0.5f, 1.f };
	vertices[1] = { 0.5f, 0.5f, 1.f };
	vertices[2] = { 0.5f, -0.5f, 1.f };
	vertices[3] = {	-0.5f, -0.5f, 1.f };

	const Mtx33& mat = owner->GetComponent<TransformComp>()->GetMatrix();

	for (int i = 0; i < 4; i++)
	{
		vertices[i] = mat * vertices[i];
	}

	if (isCollision == 2)
	{
		isCollision = 0;
	}
	else if (isCollision == 1)
	{
		isCollision++;
	}
}

void ColliderComp::OnEvent(Event* e)
{
	CollisionEvent* ce = dynamic_cast<CollisionEvent*>(e);

	if (ce != nullptr)
	{
		RigidbodyComp* r = owner->GetComponent<RigidbodyComp>();

		isCollision = 1;
	}
}

void ColliderComp::SetPos(const Vec2& otherPos)
{
	this->pos = otherPos;
}

void ColliderComp::SetScale(const Vec2& otherScale)
{
	this->scale = otherScale;
}

void ColliderComp::SetRot(const float& otherRot)
{
	this->rot = otherRot;
}

void ColliderComp::SetCollider()
{
	TransformComp* t = owner->GetComponent<TransformComp>();
	if (!t) return;

	pos.x = t->GetPos().x;
	pos.y = t->GetPos().y;

	scale.x = abs(t->GetScale().x);
	scale.y = abs(t->GetScale().y);

	rot = t->GetRot();
}

void ColliderComp::SetCollider(float posX, float posY, float scaleX, float scaleY, float _rot)
{
	pos.x = posX;
	pos.y = posY;

	scale.x = scaleX;
	scale.y = scaleY;

	rot = _rot;
}

void ColliderComp::LoadFromJson(const json& data)
{
	// Check how you saved, load from there
	auto compData = data.find("compData");

	if (compData != data.end())
	{
		auto p = compData->find("position");
		pos.x = p->begin().value();
		pos.y = (p->begin() + 1).value();

		auto s = compData->find("scale");
		scale.x = s->begin().value();
		scale.y = (s->begin() + 1).value();

		auto r = compData->find("rotation");
		rot = r.value();
	}
}

json ColliderComp::SaveToJson()
{
	json data;

	data["type"] = TypeName;

	json compData;
	compData["position"] = { pos.x, pos.y };
	compData["scale"] = { scale.x, scale.y };
	compData["rotation"] = rot;

	data["compData"] = compData;
	return data;
}

BaseRTTI* ColliderComp::CreateColliderComponent(GameObject* owner)
{
	BaseRTTI* p = new ColliderComp(owner);

	owner->AddComponent<ColliderComp>(static_cast<BaseComponent*>(p));

	return p;
}

