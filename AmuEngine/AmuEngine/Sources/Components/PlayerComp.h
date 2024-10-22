#pragma once
#include "../ComponentManager/LogicComponent.h"
#include "../Bomb/BombManager.h"
#include "../Bomb/BombComp.h"
#include <opengl.h>

class PlayerComp : public LogicComponent
{
private:
	int LastFrameKey = GLFW_RELEASE;

	float speed;
	bool focusMe;
public:
	PlayerComp(GameObject* _owner);
	~PlayerComp();

	void SetCamera(bool isfocus);
	void CreateBomb(BOMB::KindOfBomb kindofbomb);

	void Update() override;
	void Edit() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreatePlayerComponent(GameObject* owner);
	static constexpr const char* TypeName = "PlayerComp";

	friend GameObject;
};