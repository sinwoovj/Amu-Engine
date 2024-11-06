#pragma once

#include "Map.h"
#include <map>
#include <string>

class MapManager
{
	//Singleton = Only 1 object
	//	Prevent others creating me
private:
	std::map<std::string, Map*> maps;
	Map* currentMap = nullptr;

	MapManager() = default;

	//	Remove the compiler defined Copy Constructor and Assignment operator
	MapManager(const MapManager& other) = delete;
	const MapManager& operator=(const MapManager& other) = delete;

	//	Prevent others destroying me
	~MapManager();

	//	Pointer to the exisiting Singleton can be accessed without an obj and from me only
	static MapManager* ptr;

	//	Functions that anyone can access to:
public:
	static MapManager& GetInstance()
	{
		static MapManager instance;
		return instance;
	}

	///////////////////////////////
private:


public:
	//Functions to call Init, Update, Exit
	void Update();

	void SetCurrentMap(Map* map) { currentMap = map; }

	Map* GetCurrentMap() { return currentMap; }

	void AddMap(Map* map);

	void RemoveMap(Map* map);
	
	void RemoveMap(std::string str);

	void RemoveAllMap();

	Map* GetMap(std::string str);

	void ChangeCurrentMap(std::string str);
};