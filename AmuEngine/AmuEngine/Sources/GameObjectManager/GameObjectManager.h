#pragma once
#include <map>
#include <vector>
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
	//after editor.json에 추가할 예정
	std::vector <std::string> Layer
	{
		"Default",
		"UI",
		"Particle"
		//etc
	};
	std::vector <std::string> Tag
	{
		"Untagged"
		//etc
	};
	const std::vector <std::string> DefaultLayer
	{
		"Default",
		"UI",
		"Particle"
		//etc
	};
	const std::vector <std::string> DefaultTag
	{
		"Untagged"
		//etc
	};

	void Update();

	std::map<std::string, GameObject*>& GetAllObjects() { return objects; }

	static GameObjectManager& GetInstance()
	{
		static GameObjectManager instance;
		return instance;
	}

	std::vector <std::string> GetLayers();
	std::vector <std::string> GetTags();

	bool AddObjectLayer(std::string str);
	bool RemoveObjectLayer(std::string str);
	bool ExistObjectLayer(std::string str);
	void SetObjectLayer(std::string obj, std::string layer);
	std::string GetObjectLayer(std::string obj);

	bool AddObjectTag(std::string str);
	bool RemoveObjectTag(std::string str);
	bool ExistObjectTag(std::string str);
	void SetObjectTag(std::string obj, std::string tag);
	std::string GetObjectTag(std::string obj);

	void InsertObject(const std::string& id, GameObject* obj);
	bool AddObject(const std::string& id);
	GameObject* GetObj(const std::string& id);
	GameObject* GetLastObject();
	void RemoveObject(const std::string& id);
	void RemoveAllObject();
};