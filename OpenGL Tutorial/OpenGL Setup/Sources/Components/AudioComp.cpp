#include "AudioComp.h"
#include "../ComponentManager/ComponentManager.h"
#include "../ResourceManager/ResourceManager.h"

AudioComp::AudioComp(GameObject* owner) : BaseComponent(owner), group(), current("")
{
	ComponentManager<AudioComp>::GetInstance().AddComp(this);
	group = AudioCreateGroup();
}

AudioComp::~AudioComp()  
{	
	for (auto& it : audio)
	{
		ResourceManager::GetInstance().UnloadResource(it.first);
	}
	
	AudioStopGroup(group);
	AudioUnloadAudioGroup(group);
	ComponentManager<AudioComp>::GetInstance().DelComp(this);
}

void AudioComp::Update()
{
	if (flag != 0)
	{
		if (preFlag == flag)
		{
			preFlag = 0;
			flag = 0;
		}

		preFlag = flag;
	}
}

void AudioComp::playAudio(int loops, std::string name)
{
	if (flag == 0 || current.compare(name) != 0)
	{
		auto it = audio.find(name);
		if (it != audio.end())
			AudioPlay(it->second, group, volume, pitch, loops);

		flag = 1;
		current = name;
	}
	else
	{
		flag = 3 - flag;
	}
}

void AudioComp::playAudio(int loops, std::string name, float _volume)
{
	if (flag == 0 || current.compare(name) != 0)
	{
		auto it = audio.find(name);
		if (it != audio.end())
			AudioPlay(it->second, group, _volume, pitch, loops);

		flag = 1;
		current = name;
	}
	else
	{
		flag = 3 - flag;
	}
}

void AudioComp::playAudio(int loops, std::string name, float _volume, float _pitch)
{
	if (flag == 0 || current.compare(name) != 0)
	{
		auto it = audio.find(name);
		if (it != audio.end())
			AudioPlay(it->second, group, _volume, _pitch, loops);

		flag = 1;
		current = name;
	}
	else
	{
		flag = 3 - flag;
	}
}

void AudioComp::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");

	if (compData != data.end())
	{
		auto it = compData->find("audio");
		for (auto& audioIt : *it)
		{
			SetAudio(audioIt);
		}

		it = compData->find("volume");
		volume = it.value();

		it = compData->find("pitch");
		pitch = it.value();
	}
}

json AudioComp::SaveToJson()
{
	json data;
	data["type"] = TypeName;

	json compData;

	json audioList;
	for (auto& it : audio)
	{
		audioList.push_back(it.first);
	}

	compData["audio"] = audioList;
	compData["volume"] = volume;
	compData["pitch"] = pitch;
	data["compData"] = compData;

	return data;
}

void AudioComp::SetAudio(std::string name)
{
	audio.insert({ name, *ResourceManager::GetInstance().GetResource<Audio>(name) });
}

void AudioComp::UnloadAudio()
{
}

BaseRTTI* AudioComp::CreateAudioComponent(GameObject* owner)
{
	BaseRTTI* p = new AudioComp(owner);

	owner->AddComponent<AudioComp>(static_cast<BaseComponent*>(p));

	return p;
}

