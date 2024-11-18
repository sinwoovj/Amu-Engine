#pragma once
#include "../Tile/Tile.h"
#include "../Item/Item.h"
#include "Grid.h"
#include <vector>
#include <string>

/*
Map 클래스
맵 전체를 관리하는 Map 클래스입니다. 
타일, 아이템, 시작 위치 및 맵 크기 등을 정의합니다.
*/

class Map {
public:
    std::string mapName;
    int width;
    int height;
    float spacing;
    std::vector<std::vector<Tile>> tiles;       // 2D 배열 형태의 타일 맵
    std::vector<Item> items;                    // 맵에 배치된 아이템들
    std::vector<std::pair<float, float>> spawnPoints;  // 플레이어 및 NPC의 시작 위치들
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
MapObject 클래스 (예: 폭탄, 방어막 등)
맵에 배치되는 오브젝트의 상태를 관리하는 MapObject 클래스입니다. 
예를 들어 폭탄의 설치 위치와 폭발 범위 등을 정의합니다.
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
    float x, y;        // 오브젝트의 위치
    float range;       // 폭발 범위 (폭탄인 경우)
    float remainingTime; // 남은 시간

    MapObject(MapObjectType type_, float x_, float y_, float range_, float remainingTime_)
        : type(type_), x(x_), y(y_), range(range_), remainingTime(remainingTime_) {}
};
/*
void DemoMapInit() {
    // 10x10 맵 생성
    Map gameMap("Demo", 10, 10, 5);

    // 파괴 가능한 벽 설정
    gameMap.setTile(2, 3, TileType::DestructibleBlock, true);

    // 아이템 추가
    Item bombIncreaseItem(Data::ItemData::ItemType::Bandage, 4, 4, 0);
    gameMap.addItem(bombIncreaseItem);
    // = gameMap.addItem({...});

    // 스폰 위치 추가
    gameMap.addSpawnPoint(0, 0);
    gameMap.addSpawnPoint(9, 9);
}
*/