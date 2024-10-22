#pragma once
#include "../ComponentManager/LogicComponent.h"

class PlayerComp : public LogicComponent
{
private:
	float speed;
	bool focusMe;
public:
	PlayerComp(GameObject* _owner);
	~PlayerComp();

	void SetCamera(bool isfocus);
	void CreateBomb();

	void Update() override;
	void Edit() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreatePlayerComponent(GameObject* owner);
	static constexpr const char* TypeName = "PlayerComp";

	friend GameObject;
};