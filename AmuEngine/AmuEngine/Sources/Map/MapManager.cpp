#include "MapManager.h"

MapManager::~MapManager()
{
}

void MapManager::Update()
{
	if (currentMap != nullptr)
	{
		currentMap->Update();
	}
}

void MapManager::AddMap(Map* map)
{
	maps.insert({ map->mapName, map });
}

void MapManager::RemoveMap(Map* map)
{
	auto it = maps.find(map->mapName);
	if (it != maps.end())
	{
		delete it->second;
		it->second = nullptr;
		maps.erase(it->first);
	}
}

void MapManager::RemoveMap(std::string str)
{
	auto it = maps.find(str);
	if (it != maps.end())
	{
		delete it->second;
		it->second = nullptr;
		maps.erase(it->first);
	}
}

void MapManager::RemoveAllMap()
{
	for (auto it = maps.begin(); it != maps.end(); it++)
	{
		delete it->second;
	}
	maps.clear();
}

Map* MapManager::GetMap(std::string str)
{
	if(maps.find(str)== maps.end())
		return nullptr;
	return maps.find(str)->second;
}

void MapManager::ChangeCurrentMap(std::string str)
{
	if (maps.find(str) == maps.end())
		return;
	currentMap = maps.find(str)->second;
}
