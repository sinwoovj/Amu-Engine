#pragma once
#include <map>
#include <string>
#include "../GameObject/GameObject.h"

class GameObjectManager
{
private:
	std::map<std::string, GameObject*> objects;

	GameObjectManager();
	~GameObjectManager();

	GameObjectManager(const GameObjectManager&) = delete;
	GameObjectManager& operator =(const GameObjectManager&) = delete;

	static GameObjectManager* ptr;

public:
	std::map<std::string, GameObject*>& GetAllObjects() { return objects; }

	static GameObjectManager& GetInstance()
	{
		static GameObjectManager instance;
		return instance;
	}
	void InsertObject(const std::string& id, GameObject* obj);
	void AddObject(const std::string& id);
	GameObject* GetObj(const std::string& id);
	GameObject* GetLastObject();
	void RemoveObject(const std::string& id);
	void RemoveAllObject();
};