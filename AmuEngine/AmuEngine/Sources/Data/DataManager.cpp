#include "DataManager.h"
#include "../Serializer/Serializer.h"

Data::GameData Data::DataManager::gameData;
void Data::DataManager::Update()
{
}

void Data::DataManager::LoadFromJson(const json& data)
{
	if ((data.find("bombData") == data.end()) || (data.find("itemData") == data.end()))
		Serializer::GetInstance().SaveGameDataSetting();
	Data::BombData::LoadFromJson(data.find("bombData").value());
	Data::ItemData::LoadFromJson(data.find("itemData").value());
}

json Data::DataManager::SaveToJson()
{
	json data;
	data.push_back(Data::BombData::SaveToJson());
	data.push_back(Data::ItemData::SaveToJson());
	return data;
}
