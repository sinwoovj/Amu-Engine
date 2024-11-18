#pragma once
#include "../Tile/Tile.h"
#include "../Item/Item.h"
#include "Grid.h"
#include <vector>
#include <string>

/*
Map Ŭ����
�� ��ü�� �����ϴ� Map Ŭ�����Դϴ�. 
Ÿ��, ������, ���� ��ġ �� �� ũ�� ���� �����մϴ�.
*/

class Map {
public:
    std::string mapName;
    int width;
    int height;
    float spacing;
    std::vector<std::vector<Tile>> tiles;       // 2D �迭 ������ Ÿ�� ��
    std::vector<Item> items;                    // �ʿ� ��ġ�� �����۵�
    std::vector<std::pair<float, float>> spawnPoints;  // �÷��̾� �� NPC�� ���� ��ġ��
    bool isViewGrid;
    Grid grid;

    Map() : mapName(""), width(0), height(0), spacing(0), tiles(), items(), spawnPoints(), isViewGrid(false), grid() {}

    Map(std::string mapName_, int width_, int height_, float spacing_);

    ~Map() {}

    void addItem(Item item);

    void addSpawnPoint(int x, int y);

    void setTile(int x, int y, Tile::TileType type, bool destructible);

    void Update();

    void GridUpdate();
};

/*
MapObject Ŭ���� (��: ��ź, �� ��)
�ʿ� ��ġ�Ǵ� ������Ʈ�� ���¸� �����ϴ� MapObject Ŭ�����Դϴ�. 
���� ��� ��ź�� ��ġ ��ġ�� ���� ���� ���� �����մϴ�.
*/
class MapObject {
public:
    enum MapObjectType {
        Bomb,
        Item,
        Player,
        Obstacle
    };
    MapObjectType type;
    float x, y;        // ������Ʈ�� ��ġ
    float range;       // ���� ���� (��ź�� ���)
    float remainingTime; // ���� �ð�

    MapObject(MapObjectType type_, float x_, float y_, float range_, float remainingTime_)
        : type(type_), x(x_), y(y_), range(range_), remainingTime(remainingTime_) {}
};
/*
void DemoMapInit() {
    // 10x10 �� ����
    Map gameMap("Demo", 10, 10, 5);

    // �ı� ������ �� ����
    gameMap.setTile(2, 3, TileType::DestructibleBlock, true);

    // ������ �߰�
    Item bombIncreaseItem(Data::ItemData::ItemType::Bandage, 4, 4, 0);
    gameMap.addItem(bombIncreaseItem);
    // = gameMap.addItem({...});

    // ���� ��ġ �߰�
    gameMap.addSpawnPoint(0, 0);
    gameMap.addSpawnPoint(9, 9);
}
*/