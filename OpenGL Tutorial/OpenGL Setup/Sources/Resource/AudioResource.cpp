#include "AudioResource.h"

AudioResource::~AudioResource()
{
	UnloadData();
}

void AudioResource::LoadData(const std::string& name)
{
	audio = AudioLoadMusic(name.c_str());
	data = &audio;
}

void AudioResource::UnloadData()
{
	AudioUnloadAudio(audio);
	data = nullptr;
}
