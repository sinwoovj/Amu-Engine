#pragma once
#include "../ComponentManager/LogicComponent.h"
#include "../Bomb/BombManager.h"
#include "../Bomb/BombComp.h"
#include "../Data/Data.h"
#include "../ComponentManager/EngineComponent.h"
#include "../GameObject/GameObject.h"
#include <opengl.h>

class PlayerComp : public EngineComponent
{
private:
	int id;
	float speed;
	bool focusMe;
	Data::PlayerData* data;

	int LastFrameKey = GLFW_RELEASE;
public:
	GameObject* owner;
	PlayerComp(GameObject* _owner);
	~PlayerComp();

	void SetCamera(bool isfocus);
	void CreateBomb(Data::BombData::BombType type);

	void Update() override;
	void Edit() override;

	static int _playerId;

	static int GetPlayerId()
	{
		return _playerId++;
	}

	static void InitPlayerId() // 게임 시작 시 플레이어 생성 전 실행할 것
	{
		_playerId = 0; 
	}

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreatePlayerComponent(GameObject* owner);
	static constexpr const char* TypeName = "PlayerComp";

	friend GameObject;
};