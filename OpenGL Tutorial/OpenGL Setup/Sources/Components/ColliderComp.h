#pragma once
#include <queue>
#include "../ComponentManager/ComponentManager.h"
#include "../ComponentManager/EngineComponent.h"
#include "../Event/Entity.h"
#include <AMMath.h>

class ColliderComp : public EngineComponent, public Entity
{
private:
	Vec2 pos;
	Vec2 scale;
	float rot;

public:
	ColliderComp(GameObject* _owner);
	~ColliderComp();

	Vec3 vertices[4];

	int isCollision = 0;

	void Update() override;

	void OnEvent(Event* e) override;

	//Gettors
	const Vec2& GetPos() const { return pos; }
	const Vec2& GetScale() const { return scale; }
	const float& GetRot() const { return rot; }

	//Mutators
	void SetPos(const Vec2& otherPos);
	void SetScale(const Vec2& otherScale);
	void SetRot(const float& otherRot);

	void SetCollider();
	void SetCollider(float posX, float posY, float scaleX, float scaleY, float _rot);

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreateColliderComponent(GameObject* owner);
	static constexpr const char* TypeName = "ColliderComp";
};