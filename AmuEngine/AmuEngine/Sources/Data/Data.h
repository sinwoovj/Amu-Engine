#pragma once
#include "json.hpp"

using json = nlohmann::ordered_json;

namespace Data
{
	/* <summary>
		��ź ���� ������ {��� ����ü} [
			<��ź ������ ����>
				-�⺻ Default
					��ġ �� ���� �ð� �ڿ� ������, ���� �ݰ� ������ ������ ���ظ� ��
				-���� Radioactivity
					������ ���� �ݰ� ��ŭ�� �κп� �����ð� ����(5s) ���� ���ذ� ����. 3�� ���� ���� �ݰ濡 ����Ǹ� ġ������ ���ظ� �ش�.
				-���׸� Magma
					�⺻ ��ź ���� ���� ������ 1.5�� �ڿ� ������ �����ð� ����(3s) ���׸� ���ذ� ���´�. ���ظ� ���� �� 1�� �������� ���� �������� 3�� �޴´�.(��ø �ȵ�)
				-���� Ice
					���ظ� ������ ��� �÷��̾ ���� ���°� �Ǹ� �����ð� ���� ���� �ȴ�. ���� ���� �������� �ش�. (���� ���¿����� �߰����� �������� ������ ������ �� ��� ���۵� �Ұ��� �ϴ�.
			<������>
				BombType
					Default,
					Radioactivity,
					Magma,
					Ice
			<���� ����>
				������ ������ �ð�,
				���� �� ���� ȿ���� ������������ �ð�,
				Ư�� ���� �ð�(�����̳� ���� ȿ���� ���� ���) [Ư�� ������ ������ 0s]
				���ط� (���̳� ���� ��ź�� ��� 2~3�� �¾ƾ��ؼ� �׷�, �Ϲ������� ��� ��ź�� �ѹ���),
				���� Ƚ��,
				���� ���� �ð� [0�̸� ��� ����]
			<����ü>
				Bomb
					type
					timeToExplode
					effectDurationAfterExplosion
					specialConditionDuration
					damageAmount
					damageCount
					damageInterval
			<��>
				�⺻ : 	  Defualt		    / 3s 	 / 1s	/ 0s / 2 / 1 / 0s
				���� :	Radioactivity	/ 3s 	 / 5s	/ 3s / 8 / 1 / 0s
				���׸� :	Magma		      / 1.5s / 3s	/ 0s / 2 / 3 / 1s
				���� :		Ice			      / 3s	 / 1s	/ 2s / 4 / 1 / 2s
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

		struct Bomb
		{
			BombType type;
			float timeToExplode;
			float effectDurationAfterExplosion;
			float specialConditionDuration;
			int damageAmount;
			int damageCount;
			float damageInterval;
		};

		BombData() {};

		static Bomb GetBombData(BombType type)
		{
			switch (type)
			{
			case Default:
				return { BombType::Default,		  3.0f, 1.0f, 0.0f, 2, 1, 0.0f };
			case Radioactivity:
				return { BombType::Radioactivity, 3.0f, 5.0f, 3.0f, 8, 1, 0.0f };
			case Magma:
				return { BombType::Magma,	      1.5f, 3.0f, 0.0f, 2, 3, 1.0f };
			case Ice:
				return { BombType::Ice,			  3.0f, 1.0f, 2.0f, 4, 1, 2.0f };
			}
		}
	};

	/* <summary>
		�÷��̾� ���� ������ {���� ����ü} [
			<���� ����>
				-��ź ����
				-���� �ݰ� ����
				-�̵� �ӵ� Move Speed
				-ü�� HP
				-���� ��ź ����
				-������ �÷��� Item Flags
				{
					�� Shield = 1 << 0
					������� Invisibility Cape = 1 << 1
					�ش� Bandage = 1 << 2
				}
			<������>
				bombCount
				explosionRadius
				moveSpeed
				hp
				currentBombType
				itemVitalizationFlag
			<��>
				�ʱ� :	 1 / 1 / 1 / 10 / BombType::Default / 0
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
	};

	/* <summary>
		������ ���� ������ {��� ����ü} [
			<������ ������ ����>
				-��ź ���� Water Balloon Increase
					ĳ���Ͱ� ���ÿ� ��ġ�� �� �ִ� ��ź�� ������ �÷��ݴϴ�. �� �������� ���� ������ ��ź�� ��ġ�ϰ� ���� �й��� �� �ֽ��ϴ�.
				-���� �ݰ� ���� Water Stream Increase
					��ǳ���� ������ �� ���� �ݰ��� �÷��ݴϴ�. �� �� ������ ���� ������ �� �ְ� �Ͽ� ������ �����մϴ�.
				-�Ź� Shoes
					�̵� �ӵ��� ���� �� ������ ���ݴϴ�.
				-ȸ���� Medicine
					�� �״�� �÷��̾��� ü���� ���� ȸ���Ѵ�.
				-��ź ������ Bomb Item
					���� ��ź ���� �߿��� ������ ��ź�� ȿ���� ���� �ð� 15�� ���� ����ϴ�.
				-�� Shield
					15�� ���� ���� ��ź�� �¾Ƶ� �� �� �ߵ� �� �ִ� ���� �����մϴ�. ���� ��Ȳ���� �������� �����ִ� �߿��� �������Դϴ�.
				-���� ���� Invisibility Cape
					15�� ���� ĳ���Ͱ� ������ �ʰ� ����� ��밡 ��ġ�� �ľ��ϱ� ��ư� �մϴ�. ���� �þ߸� ���� �� �־� ���������� �����մϴ�.
				-�ش� Bandage
					ü���� 0 ������ �� 3�ʰ� ���� ���°� �Ǵ� ���ÿ� ü���� 5 ��ŭ ȸ���Ѵ�.
			<������>
				ItemType
					WaterBalloonIncrease,
					WaterStreamIncrease,
					Shoes,
					Medicine,
					BombItem,
					Shield,
					InvisibilityCape,
					Bandage
			<���� ����>
				������ ����,
				������ ���� �ð�,
				ȿ�� ����	
			<����ü>
				Item
					type
					duration
					effectStrength
			<��>
				��ź ���� :		WaterBalloonIncrease	/ 0s	/ 1
				���� �ݰ� ���� :	WaterStreamIncrease	/ 0s	/ 1
				�Ź� :			Shoes			/ 0s	/ 1
				ȸ���� :		Medicine			/ 0s	/ 10
				��ź ������ :	BombItem			/ 15s	/ rand(0~2)
				�� :		Shield			/ 15s	/ 0
				���� ���� :		Shield			/ 15s	/ 0
				�ش� :			InvisibilityCape		/ 3s	/ 5
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

		struct Item
		{
			ItemType type;
			float duration;
			int effectStrength;
		};

		ItemData() {};

		static Item GetItemData(ItemType type)
		{
			switch (type)
			{
			case WaterBalloonIncrease:
				return { ItemType::WaterBalloonIncrease,	0.0f,	 1};
			case WaterStreamIncrease:
				return { ItemType::WaterStreamIncrease,		0.0f,	 1};
			case Shoes:
				return { ItemType::Shoes,					0.0f,	 1};
			case Medicine:
				return { ItemType::Medicine,				0.0f,   10};
			case BombItem:
				return { ItemType::BombItem,				15.0f,	 0};
			case Shield:
				return { ItemType::Shield,					15.0f,	 0};
			case InvisibilityCape:									 
				return { ItemType::InvisibilityCape,		15.0f,	 0};
			case Bandage:											 
				return { ItemType::Bandage,					3.0f,	 5};
			}
		}
	};

	static void PrintPlayerData(Data::PlayerData data);
	static void PrintSeparator();
};