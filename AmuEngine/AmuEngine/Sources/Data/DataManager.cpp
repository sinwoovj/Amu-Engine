#include "DataManager.h"
#include "../Serializer/Serializer.h"

Data::GameData Data::DataManager::gameData;
void Data::DataManager::Update()
{
}

void Data::DataManager::LoadFromJson(const json& data)
{
	if ((data.find("bombData") == data.end()) || (data.find("itemData") == data.end()) || (data.find("keyData") == data.end()))
		Serializer::GetInstance().SaveGameDataSetting();
	Data::BombData::LoadFromJson(data.find("bombData").value());
	Data::ItemData::LoadFromJson(data.find("itemData").value());
	Data::KeyData::LoadFromJson(data.find("keyData").value());
}

json Data::DataManager::SaveToJson()
{
	json data;
	data["bombData"] = Data::BombData::SaveToJson();
	data["itemData"] = Data::ItemData::SaveToJson();
	data["keyData"] = Data::KeyData::SaveToJson();
	return data;
}
