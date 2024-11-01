#pragma once
#include <queue>
#include "../ComponentManager/ComponentManager.h"
#include "../ComponentManager/EngineComponent.h"
#include "../Event/Entity.h"
#include <opengl.h>

class ColliderComp : public EngineComponent, public Entity
{
private:
	glm::vec2 pos;
	glm::vec2 scale;
	float rot;

public:
	ColliderComp(GameObject* _owner);
	~ColliderComp();

	glm::vec3 vertices[4];

	int isCollision = 0;

	void Update() override;

	void OnEvent(Event* e) override;

	//Gettors
	const glm::vec2& GetPos() const { return pos; }
	const glm::vec2& GetScale() const { return scale; }
	const float& GetRot() const { return rot; }

	//Mutators
	void SetPos(const glm::vec2& otherPos);
	void SetScale(const glm::vec2& otherScale);
	void SetRot(const float& otherRot);

	void SetCollider();
	void SetCollider(float posX, float posY, float scaleX, float scaleY, float _rot);

	const glm::mat3x3& GetMatrix() const;

	void Edit() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreateColliderComponent(GameObject* owner);
	static constexpr const char* TypeName = "ColliderComp";
};