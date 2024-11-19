#pragma once
#include <queue>
#include "../ComponentManager/ComponentManager.h"
#include "../ComponentManager/LogicComponent.h"
#include "../Event/Entity.h"
#include <opengl.h>
#include <string>

class ColliderComp : public LogicComponent, public Entity
{
private:
	glm::vec2 pos;
	float rot;
	glm::vec2 scale;

	glm::mat3x3 colliderMatrix;
	std::vector<bool> col_selected;
public:
	ColliderComp(GameObject* _owner);
	~ColliderComp();

	glm::vec3 vertices[4];

	bool isTrigger = false;
	std::list<std::string> triggerLayer;
	int isCollision = 0;

	void Update() override;

	void OnEvent(Event* e) override;

	//Gettors
	const glm::vec2& GetPos() const { return pos; }
	const glm::vec2& GetScale() const { return scale; }
	const float& GetRot() const { return rot; }
	const glm::mat3x3& GetMatrix() const;

	//Mutators
	void SetPos(const glm::vec2& otherPos);
	void SetScale(const glm::vec2& otherScale);
	void SetRot(const float& otherRot);

	void SetCollider();
	void SetCollider(float posX, float posY, float scaleX, float scaleY, float _rot);


	void Edit() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreateColliderComponent(GameObject* owner);
	static constexpr const char* TypeName = "ColliderComp";
};