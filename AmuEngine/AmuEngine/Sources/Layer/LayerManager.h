#pragma once
#include <vector>
#include "../Components/SpriteComp.h"

class LayerManager
{
private:
	LayerManager() = default;

	LayerManager(const LayerManager& other) = delete;
	const LayerManager& operator=(const LayerManager& other) = delete;

	~LayerManager();
public:
	static LayerManager& GetInstance()
	{
		static LayerManager instance;
		return instance;
	}
private:
	std::vector<SpriteComp*> sprite_list;
public:
	void Update();

	void AddSpriteList(SpriteComp* comp);
	void RemoveSpriteList(SpriteComp* comp);
	void ClearSpriteList();
	std::vector<SpriteComp*> GetSpriteList();
};