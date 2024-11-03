#pragma once
#include <string>
#include "json.hpp"

#include "Data.h"

using json = nlohmann::ordered_json;	// Map. Orders the order the variables were declared in

namespace Data
{
	class DataManager
	{
		DataManager() = default;

		DataManager(const DataManager&) = delete;
		DataManager& operator =(const DataManager&) = delete;

		~DataManager() = default;

		static DataManager* ptr;
	public:
		static Data::GameData gameData;
		static DataManager& GetInstance()
		{
			static DataManager instance;
			return instance;
		}

		void Update();
		void LoadFromJson(const json& data);
		json SaveToJson();
	};
}