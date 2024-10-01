#pragma once
#include <map>
#include <string>
#include "../GameObject/GameObject.h"

class GameObjectManager
{
private:
	std::map<GameObject*, std::string> objects;

	GameObjectManager();
	~GameObjectManager();

	GameObjectManager(const GameObjectManager&) = delete;
	GameObjectManager& operator =(const GameObjectManager&) = delete;

	static GameObjectManager* ptr;

public:
	std::map<GameObject*, std::string>& GetAllObjects() { return objects; }

	static GameObjectManager& GetInstance()
	{
		static GameObjectManager instance;
		return instance;
	}
	void InsertObject(GameObject* obj, std::string str);
	void AddObject(GameObject* obj);
	GameObject* GetObj(const std::string& id);
	GameObject* GetLastObject();
	void RemoveObject(GameObject* obj);
	void RemoveAllObject();
};