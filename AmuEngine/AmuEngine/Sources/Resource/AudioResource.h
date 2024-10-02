#pragma once
#include "Resource.h"
#include <AMAudio.h>

class AudioResource : public Resource
{
private:
	Audio audio;

public:
	AudioResource() : audio(Audio()) {}
	~AudioResource();
	void LoadData(const std::string& filename) override;
	void UnloadData() override;
};