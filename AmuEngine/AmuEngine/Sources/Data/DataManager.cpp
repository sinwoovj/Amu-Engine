#include "DataManager.h"

Data::GameData Data::DataManager::gameData;
void Data::DataManager::Update()
{
}

void Data::DataManager::LoadFromJson(const json& data)
{
	if (data.find("bombData") != data.end())
		Data::BombData::LoadFromJson(data.find("bombData").value());
	if (data.find("itemData") != data.end())
		Data::ItemData::LoadFromJson(data.find("itemData").value());
}

json Data::DataManager::SaveToJson()
{
	json data;
	if(!gameData.BombDatas.empty())
		data.push_back(Data::BombData::SaveToJson());
	if(!gameData.ItemDatas.empty())
		data.push_back(Data::ItemData::SaveToJson());
	return data;
}
