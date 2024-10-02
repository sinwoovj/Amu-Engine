#pragma once
#include <AMMath.h>
#include "../ComponentManager/ComponentManager.h"
#include "../ComponentManager/EngineComponent.h"
#include "../Event/Entity.h"

class TransformComp : public EngineComponent
{
private:
	Vec2 pos;
	Vec2 scale;
	float rot;

	Mtx33 transformMatrix;

	void CalculateMatrix();

public:
	TransformComp(GameObject* _owner);
	~TransformComp();

	bool affectedByZoom = true;

	void Update() override;

	//Gettors
	const Vec2& GetPos() const { return pos; }
	const Vec2& GetScale() const { return scale; }
	const float& GetRot() const { return rot; }
	const Mtx33& GetMatrix() const { return transformMatrix; }

	//Mutators
	void SetPos(const Vec2& otherPos);
	void SetScale(const Vec2& otherScale);
	void SetRot(const float& otherRot);

	void ReverseX(int val);
	void ReverseY(int val);

	//Other Fn
	void PrintMatrix();

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreateTransformComponent(GameObject* owner);
	static constexpr const char* TypeName = "TransformComp";
};