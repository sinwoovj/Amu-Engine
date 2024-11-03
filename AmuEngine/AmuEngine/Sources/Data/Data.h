#pragma once
#include "json.hpp"
#include <map>

using json = nlohmann::ordered_json;

namespace Data
{
	/* <summary>
		폭탄 관련 데이터 {상수 구조체} [
			<폭탄 종류별 설명>
				-기본 Default
					설치 후 일정 시간 뒤에 터지며, 폭발 반경 내부의 적에게 피해를 줌
				-방사능 Radioactivity
					터지면 폭발 반경 만큼의 부분에 일정시간 동안(5s) 방사능 피해가 남음. 3초 동안 폭발 반경에 노출되면 치명적인 피해를 준다.
				-마그마 Magma
					기본 폭탄 보다 더욱 빠르게 1.5초 뒤에 터지고 일정시간 동안(3s) 마그마 피해가 남는다. 피해를 입을 시 1초 간격으로 일정 데미지를 3번 받는다.(중첩 안됨)
				-얼음 Ice
					피해를 입히면 상대 플레이어가 빙결 상태가 되며 일정시간 동안 경직 된다. 또한 일정 데미지를 준다. (빙결 상태에서는 추가적인 데미지를 받지는 않으나 그 어떠한 조작도 불가능 하다.
			<열거형>
				BombType
					Default,
					Radioactivity,
					Magma,
					Ice
			<변수 종류>
				터지기 까지의 시간,
				터진 후 피해 효과가 사라지기까지의 시간,
				특정 조건 시간(방사능이나 빙결 효과와 같은 경우) [특정 조건이 없으면 0s]
				피해량 (독이나 얼음 폭탄의 경우 2~3번 맞아야해서 그럼, 일반적으로 모든 폭탄은 한방임),
				피해 횟수,
				피해 간격 시간 [0이면 즉시 피해]
			<구조체>
				Bomb
					type
					timeToExplode
					effectDurationAfterExplosion
					specialConditionDuration
					damageAmount
					damageCount
					damageInterval
			<값>
				기본 : 	  Defualt		    / 3s 	 / 1s	/ 0s / 2 / 1 / 0s
				방사능 :	Radioactivity	/ 3s 	 / 5s	/ 3s / 8 / 1 / 0s
				마그마 :	Magma		      / 1.5s / 3s	/ 0s / 2 / 3 / 1s
				얼음 :		Ice			      / 3s	 / 1s	/ 2s / 4 / 1 / 2s
		]
	< / summary> */
	class BombData
	{
	public:
		enum BombType
		{
			Default,
			Radioactivity,
			Magma,
			Ice
		};

		struct BombVar
		{
			float timeToExplode;
			float effectDurationAfterExplosion;
			float specialConditionDuration;
			int damageAmount;
			int damageCount;
			float damageInterval;
		};
		/*
			{ BombType::Default,		3.0f, 1.0f, 0.0f, 2, 1, 0.0f };
			{ BombType::Radioactivity,	3.0f, 5.0f, 3.0f, 8, 1, 0.0f };
			{ BombType::Magma,			1.5f, 3.0f, 0.0f, 2, 3, 1.0f };
			{ BombType::Ice,			3.0f, 1.0f, 2.0f, 4, 1, 2.0f };
		*/
		static void InitData(std::map <Data::BombData::BombType, Data::BombData::BombVar>& tar);
		static void LoadFromJson(const json& data);
		static json SaveToJson();
	};

	/* <summary>
		아이템 관련 데이터 {상수 구조체} [
			<아이템 종류별 설명>
				-폭탄 증가 Water Balloon Increase
					캐릭터가 동시에 설치할 수 있는 폭탄의 개수를 늘려줍니다. 이 아이템을 통해 빠르게 폭탄을 설치하고 적을 압박할 수 있습니다.
				-폭발 반경 증가 Water Stream Increase
					물풍선이 터졌을 때 폭발 반경을 늘려줍니다. 더 긴 범위로 적을 공격할 수 있게 하여 전투에 유리합니다.
				-신발 Shoes
					이동 속도를 조금 더 빠르게 해줍니다.
				-회복약 Medicine
					말 그대로 플레이어의 체력을 전부 회복한다.
				-폭탄 아이템 Bomb Item
					여러 폭탄 종류 중에서 임의의 폭탄의 효과를 일정 시간 15초 동안 얻습니다.
				-방어막 Shield
					15초 동안 적의 폭탄에 맞아도 한 번 견딜 수 있는 방어막을 제공합니다. 위기 상황에서 생존율을 높여주는 중요한 아이템입니다.
				-투명 망토 Invisibility Cape
					15초 동안 캐릭터가 보이지 않게 만들어 상대가 위치를 파악하기 어렵게 합니다. 적의 시야를 속일 수 있어 전략적으로 유용합니다.
				-붕대 Bandage
					체력이 0 이하일 때 3초간 무적 상태가 되는 동시에 체력을 5 만큼 회복한다.
			<열거형>
				ItemType
					WaterBalloonIncrease,
					WaterStreamIncrease,
					Shoes,
					Medicine,
					BombItem,
					Shield,
					InvisibilityCape,
					Bandage
			<변수 종류>
				아이템 종류,
				아이템 지속 시간,
				효과 강도	
			<구조체>
				Item
					type
					duration
					effectStrength
			<값>
				폭탄 증가 :		WaterBalloonIncrease	/ 0s	/ 1
				폭발 반경 증가 :	WaterStreamIncrease	/ 0s	/ 1
				신발 :			Shoes			/ 0s	/ 1
				회복약 :		Medicine			/ 0s	/ 10
				폭탄 아이템 :	BombItem			/ 15s	/ rand(0~2)
				방어막 :		Shield			/ 15s	/ 0
				투명 망토 :		Shield			/ 15s	/ 0
				붕대 :			InvisibilityCape		/ 3s	/ 5
		]
	</summary> */
	class ItemData
	{
	public:
		enum ItemType
		{
			WaterBalloonIncrease,
			WaterStreamIncrease,
			Shoes,
			Medicine,
			BombItem,
			Shield,
			InvisibilityCape,
			Bandage
		};

		struct ItemVar
		{
			float duration;
			int effectStrength;
		};
		/*
			{ ItemType::WaterBalloonIncrease,	0.0f,	 1};
			{ ItemType::WaterStreamIncrease,	0.0f,	 1};
			{ ItemType::Shoes,					0.0f,	 1};
			{ ItemType::Medicine,				0.0f,   10};
			{ ItemType::BombItem,				15.0f,	 0};
			{ ItemType::Shield,					15.0f,	 0};
			{ ItemType::InvisibilityCape,		15.0f,	 0};
			{ ItemType::Bandage,				3.0f,	 5};
		*/
		static void InitData(std::map <Data::ItemData::ItemType, Data::ItemData::ItemVar>& tar);
		static void LoadFromJson(const json& data);
		static json SaveToJson();
	};

	/* <summary>
		플레이어 관련 데이터 {비상수 구조체} [
			<변수 종류>
				-폭탄 갯수
				-폭발 반경 길이
				-이동 속도 Move Speed
				-체력 HP
				-현재 폭탄 종류
				-아이템 플래그 Item Flags
				{
					방어막 Shield = 1 << 0
					투명망토 Invisibility Cape = 1 << 1
					붕대 Bandage = 1 << 2
				}
			<변수명>
				bombCount
				explosionRadius
				moveSpeed
				hp
				currentBombType
				itemVitalizationFlag
			<값>
				초기 :	 1 / 1 / 1 / 10 / BombType::Default / 0
		]
	< / summary> */
	class PlayerData
	{
	public:
		PlayerData(int bombCountV, int explosionRadiusV, float moveSpeedV, int hpV, Data::BombData::BombType currentBombTypeV, int itemVitalizationFlagV)
		{
			bombCount = bombCountV;
			explosionRadius = explosionRadiusV;
			moveSpeed = moveSpeedV;
			hp = hpV;
			currentBombType = currentBombTypeV;
			itemVitalizationFlag = itemVitalizationFlagV;
		}

		int bombCount;
		int explosionRadius;
		float moveSpeed;
		int hp;
		Data::BombData::BombType currentBombType;
		int itemVitalizationFlag;

		void InitData(int bombCountV, int explosionRadiusV, float moveSpeedV, int hpV, Data::BombData::BombType currentBombTypeV, int itemVitalizationFlagV)
		{
			bombCount = bombCountV;							// 1
			explosionRadius = explosionRadiusV;				// 1
			moveSpeed = moveSpeedV;							// 1
			hp = hpV;										// 10
			currentBombType = currentBombTypeV;				// BombData::BombType::Default
			itemVitalizationFlag = itemVitalizationFlagV;	// 0
		};

		void PrintPlayerData(Data::PlayerData data);
		void LoadFromJson(const json& data);
		json SaveToJson();
	};

	struct GameData {
		//std::map<type, value>
		std::map <Data::BombData::BombType, Data::BombData::BombVar> BombDatas;
		std::map <Data::ItemData::ItemType, Data::ItemData::ItemVar> ItemDatas;
		~GameData() { BombDatas.clear(); ItemDatas.clear(); }
	};
	
	const static std::string gameDataFileName = "./Sources/Data/gameData.json";

	// static function
	static void PrintSeparator();
};