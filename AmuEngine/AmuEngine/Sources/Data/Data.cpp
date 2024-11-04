#include "Data.h"
#include "DataManager.h"
#include <iostream>

void Data::PlayerData::PrintPlayerData(Data::PlayerData data)
{
	std::cout << "Player BoubCount : "				<< data.bombCount				<< std::endl;
	std::cout << "Player ExplosionRadius : "		<< data.explosionRadius			<< std::endl;
	std::cout << "Player MoveSpeed : "				<< data.moveSpeed				<< std::endl;
	std::cout << "Player HP : "						<< data.hp						<< std::endl;
	std::cout << "Player CurrentBombType : "		<< data.currentBombType			<< std::endl;
	std::cout << "Player ItemVitalizationFlag : "	<< data.itemVitalizationFlag	<< std::endl;
	PrintSeparator();
}

void Data::PrintSeparator()
{
	std::cout << "---------------------------" << std::endl;
}

// Json Save&Load

void Data::BombData::InitData(std::map<Data::BombData::BombType, Data::BombData::BombVar>& tar)
{
	tar.clear();
	tar =
	{
		{ BombType::Default,		{ 3.0f, 1.0f, 0.0f, 2, 1, 0.0f} },
		{ BombType::Radioactivity,	{ 3.0f, 5.0f, 3.0f, 8, 1, 0.0f} },
		{ BombType::Magma,			{ 1.5f, 3.0f, 0.0f, 2, 3, 1.0f} },
		{ BombType::Ice,			{ 3.0f, 1.0f, 2.0f, 4, 1, 2.0f} }
	};
}

void Data::BombData::LoadFromJson(const json& data)
{
	auto& datas = Data::DataManager::GetInstance().gameData.BombDatas;
	for (auto& it : data)
	{
		Data::BombData::BombType type = it.find("type").value();
		auto& value = it.find("value").value();
		if (datas.find(type) != datas.end())
		{
			datas.find(type)->second.timeToExplode = 
				value.find("timeToExplode").value();
			datas.find(type)->second.effectDurationAfterExplosion =
				value.find("effectDurationAfterExplosion").value();
			datas.find(type)->second.specialConditionDuration =
				value.find("specialConditionDuration").value();
			datas.find(type)->second.damageAmount =
				value.find("damageAmount").value();
			datas.find(type)->second.damageCount =
				value.find("damageCount").value();
			datas.find(type)->second.damageInterval =
				value.find("damageInterval").value();
		}
		else
		{
			datas.insert({
				type,
				{
					value.find("timeToExplode").value(),
					value.find("effectDurationAfterExplosion").value(),
					value.find("specialConditionDuration").value(),
					value.find("damageAmount").value(),
					value.find("damageCount").value(),
					value.find("damageInterval").value()
				}
			});
		}
	}
}

json Data::BombData::SaveToJson()
{
	json data;

	auto& bombDatas = Data::DataManager::GetInstance().gameData.BombDatas;

	if (bombDatas.empty())
		Data::BombData::InitData(bombDatas);

	for (auto& it : bombDatas)
	{
		json bombData;

		bombData["type"] = it.first;

		json value;

		value["timeToExplode"] = it.second.timeToExplode;
		value["effectDurationAfterExplosion"] = it.second.effectDurationAfterExplosion;
		value["specialConditionDuration"] = it.second.specialConditionDuration;
		value["damageAmount"] = it.second.damageAmount;
		value["damageCount"] = it.second.damageCount;
		value["damageInterval"] = it.second.damageInterval;

		bombData["value"] = value;

		data.push_back(bombData);
	}

	return data;
}

void Data::ItemData::InitData(std::map<Data::ItemData::ItemType, Data::ItemData::ItemVar>& tar)
{
	tar.clear();
	tar =
	{
		{ ItemType::WaterBalloonIncrease,	{0.0f,	 1 }},
		{ ItemType::WaterStreamIncrease,	{0.0f,	 1 }},
		{ ItemType::Shoes,					{0.0f,	 1 }},
		{ ItemType::Medicine,				{0.0f,   10}},
		{ ItemType::BombItem,				{15.0f,	 0 }},
		{ ItemType::Shield,					{15.0f,	 0 }},
		{ ItemType::InvisibilityCape,		{15.0f,	 0 }},
		{ ItemType::Bandage,				{3.0f,	 5 }}
	};
}

void Data::ItemData::LoadFromJson(const json& data)
{
	auto& datas = Data::DataManager::GetInstance().gameData.ItemDatas;
	for (auto& it : data)
	{
		Data::ItemData::ItemType type = it.find("type").value();
		auto& value = it.find("value").value();
		if (datas.find(type) != datas.end())
		{
			datas.find(type)->second.duration =
				value.find("duration").value();
			datas.find(type)->second.effectStrength =
				value.find("effectStrength").value();
		}
		else
		{
			datas.insert({
				type,
				{
					value.find("duration").value(),
					value.find("effectStrength").value()
				}
			});
		}
	}
}

json Data::ItemData::SaveToJson()
{
	json data;

	auto& ItemDatas = Data::DataManager::GetInstance().gameData.ItemDatas;

	if (ItemDatas.empty())
		Data::ItemData::InitData(ItemDatas);


	for (auto& it : ItemDatas)
	{
		json itemData;

		itemData["type"] = it.first;

		json value;

		value["duration"] = it.second.duration;
		value["effectStrength"] = it.second.effectStrength;

		itemData["value"] = value;

		data.push_back(itemData);
	}

	return data;
}

void Data::PlayerData::LoadFromJson(const json& data)
{

}

json Data::PlayerData::SaveToJson()
{
	return json();
}
