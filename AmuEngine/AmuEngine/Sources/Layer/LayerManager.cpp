#include "LayerManager.h"
#include "../GameObject/GameObject.h"

LayerManager::~LayerManager()
{
	sprite_list.clear();
}

void LayerManager::Update()
{
	for (auto& sc : sprite_list)
	{
		sc->Update();
	}
}


void LayerManager::AddSpriteList(SpriteComp* comp)
{
	sprite_list.push_back(comp);
}

void LayerManager::RemoveSpriteList(SpriteComp* comp)
{
	sprite_list.erase(
		std::remove(sprite_list.begin(), sprite_list.end(), comp),
		sprite_list.end()
	);
}

void LayerManager::ClearSpriteList()
{
	sprite_list.clear();
}

std::vector<SpriteComp*> LayerManager::GetSpriteList()
{
	return sprite_list;
}
