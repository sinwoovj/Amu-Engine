#pragma once
#include "Resource.h"
#include <string>

class TextureResource : public Resource
{
	std::string fileExtension = "";
public:
	TextureResource(std::string str)
	{
		fileExtension = str;
	};
	~TextureResource();
	void LoadData(const std::string& filename) override;
	void UnloadData() override;
};