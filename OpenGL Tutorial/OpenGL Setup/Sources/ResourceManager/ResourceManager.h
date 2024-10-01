#pragma once
#include <iostream>
#include <map>
#include <string>
#include "../Resource/TextureResource.h"
#include "../Resource/AudioResource.h"

class ResourceManager
{
private:
	ResourceManager() = default;

	ResourceManager(const ResourceManager& other) = delete;
	const ResourceManager& operator=(const ResourceManager& other) = delete;

	~ResourceManager();

	std::map<std::string, Resource*> resources;

	enum fileExt
	{
		unvalid,
		png,
		jpg,
		wav,
		mp3
	};

	std::map<std::string, fileExt> stringToEnum =
	{
		{"png", png},
		{"jpg", jpg},
		{"wav", wav},
		{"mp3", mp3}
	};

public:
	static ResourceManager& GetInstance()
	{
		static ResourceManager instance;
		return instance;
	}

	//Get<T>(name) fn that returns a T* to the data allocated in the resource with that name
	template <typename T>
	T* GetResource(const std::string& filename);

	//Unload(name) fn that removes 1 from the counter of the resource.
		//If the counter is 0, unload the resource, delete it, and remove from map
	void UnloadResource(const std::string& filename);
	
	//Fn to unload ALL resources
	void UnloadAllResource();
};

#include "ResourceManager.inl"