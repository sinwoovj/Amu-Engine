#pragma once
#include "../ComponentManager/ComponentManager.h"
#include "../ComponentManager/EngineComponent.h"
#include "../Event/Entity.h"

#include <opengl.h>

class TransformComp : public EngineComponent
{
private:
	
	glm::vec2 pos;
	glm::vec2 scale;
	float rot;

	glm::mat3x3 transformMatrix;

	void CalculateMatrix();

public:
	TransformComp(GameObject* _owner);
	~TransformComp();

	bool affectedByZoom = true;

	void Update() override;

	//Gettors
	const glm::vec2& GetPos() const { return pos; }
	const glm::vec2& GetScale() const { return scale; }
	const float& GetRot() const { return rot; }
	const glm::mat3x3& GetMatrix() const { return transformMatrix; }

	//Mutators
	void SetPos(const glm::vec2& otherPos);
	void SetScale(const glm::vec2& otherScale);
	void SetRot(const float& otherRot);

	void ReverseX(int val);
	void ReverseY(int val);

	//Other Fn
	void PrintMatrix();

	void Edit() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreateTransformComponent(GameObject* owner);
	static constexpr const char* TypeName = "TransformComp";
};