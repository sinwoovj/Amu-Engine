#pragma once
#include <queue>
#include <AMType.h>
#include "../ComponentManager/EngineComponent.h"
#include "ColliderComp.h"

#define	EPSILON	0.00001f

class RigidbodyComp : public EngineComponent
{
private:	
	float drag = 1.01f;
	float targetRot = 0;

	Vec2 velocity;
	Vec2 maxVelocity;
	Vec2 acceleration;
	Vec2 maxAcceleration;
	
	bool CheckEpsilon(float v, float EP = EPSILON);
	void CorrectPosByAABB(ColliderComp*, ColliderComp*, float&, float&);

public:
	bool useGravity = false;

	std::queue<ColliderComp*> oppoCollider;
	bool colliderType[20] = { 0 };

	RigidbodyComp(GameObject* _owner);
	~RigidbodyComp();

	void AddVelocity(const Vec2& otherVec);
	void AddVelocity(float x, float y);
	float GetVelocityX();
	float GetVelocityY();
	void SetVelocity(const Vec2& otherVec);
	void SetVelocity(float x, float y);
	void SetVelocityX(float x);
	void SetVelocityY(float y);
	void ClearVelocity();

	void AddAcceleration(const Vec2& otherVec);
	void AddAcceleration(float x, float y);
	void SetAcceleration(const Vec2& otherVec);
	void SetAcceleration(float x, float y);
	void ClearAcceleration();

	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreateRigidBodyComponent(GameObject* owner);
	static constexpr const char* TypeName = "RigidbodyComp";
};