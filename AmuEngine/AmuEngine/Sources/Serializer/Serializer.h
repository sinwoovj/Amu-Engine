#pragma once
#include <string>
#include "json.hpp"

using json = nlohmann::ordered_json;	// Map. Orders the order the variables were declared in

class Serializer
{
private:
	Serializer() = default;

	Serializer(const Serializer&) = delete;
	Serializer& operator =(const Serializer&) = delete;

	~Serializer() = default;

	static Serializer* ptr;

public:
	static Serializer& GetInstance()
	{
		static Serializer instance;
		return instance;
	}

	json GetLevelData(const std::string& str);
	json GetObjectData(json level, const std::string& str);
	json GetComponentData(json Object, const std::string& str);
	bool LoadLevel(const std::string& str);
	bool ExistChangePoint(const std::string& str);
	bool SaveLevel(const std::string& str);
	void LoadEditorSetting();
	void SaveEditorSetting();
	void LoadGameDataSetting();;
	void SaveGameDataSetting();
};