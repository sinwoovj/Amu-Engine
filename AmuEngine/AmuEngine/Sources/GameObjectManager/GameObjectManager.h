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

	bool AddObjectLayer(const std::string& str);
	bool RemoveObjectLayer(const std::string& str);
	bool ExistDefaultLayer(const std::string& str);
	bool ExistObjectLayer(const std::string& str);
	void SetObjectLayer(const std::string& obj, const std::string& layer);
	std::string GetObjectLayer(const std::string& obj);
	std::vector<GameObject*> ExtractGOToLayer(const std::string& str);
	void ChangeNameLayer(const std::string& oldstr, const std::string& newstr);
	void OrderUpLayer(const std::string& str);
	void OrderDownLayer(const std::string& str);

	bool AddObjectTag(const std::string& str);
	bool RemoveObjectTag(const std::string& str);
	bool ExistDefaultTag(const std::string& str);
	bool ExistObjectTag(const std::string& str);
	void SetObjectTag(const std::string& obj, const std::string& tag);
	std::string GetObjectTag(const std::string& obj);
	std::vector<GameObject*> ExtractGOToTag(const std::string& str);
	void ChangeNameTag(const std::string& oldstr, const std::string& newstr);

	void InsertObject(const std::string& id, GameObject* obj);
	bool AddObject(const std::string& id);
	GameObject* GetObj(const std::string& id);
	GameObject* GetLastObject();
	void RemoveObject(const std::string& id);
	void RemoveAllObject();
	bool ExistObject(const std::string& id);
	void ChangeNameObject(const std::string& oldstr, const std::string& newstr);
};