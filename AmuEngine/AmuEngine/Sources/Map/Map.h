/*
Map 클래스
맵 전체를 관리하는 Map 클래스입니다. 
타일, 아이템, 시작 위치 및 맵 크기 등을 정의합니다.
*/

#include "../Tile/Tile.h"
#include "../Item/Item.h"
#include "../Data/Data.h"
#include <vector>

class Map {
public:
    int width;
    int height;
    std::vector<std::vector<Tile>> tiles;       // 2D 배열 형태의 타일 맵
    std::vector<Item> items;                    // 맵에 배치된 아이템들
    std::vector<std::pair<int, int>> spawnPoints;  // 플레이어 및 NPC의 시작 위치들

    Map(int width, int height) : width(width), height(height) {
        // 맵 크기에 맞게 빈 타일로 초기화
        tiles = std::vector<std::vector<Tile>>(height, std::vector<Tile>(width, Tile(TileType::Empty, false, 0, 0)));
    }

    void addItem(Item item) {
        items.push_back(item);
    }

    void addSpawnPoint(int x, int y) {
        spawnPoints.push_back({ x, y });
    }

    void setTile(int x, int y, TileType type, bool destructible) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            tiles[y][x] = Tile(type, destructible, x, y);
        }
    }
};

/*
MapObject 클래스 (예: 폭탄, 방어막 등)
맵에 배치되는 오브젝트의 상태를 관리하는 MapObject 클래스입니다. 
예를 들어 폭탄의 설치 위치와 폭발 범위 등을 정의합니다.
*/

enum class MapObjectType {
    Bomb,
    Shield,
    Obstacle
};

class MapObject {
public:
    MapObjectType type;
    int x, y;        // 오브젝트의 위치
    int range;       // 폭발 범위 (폭탄인 경우)
    int remainingTime; // 남은 시간

    MapObject(MapObjectType type, int x, int y, int range, int remainingTime)
        : type(type), x(x), y(y), range(range), remainingTime(remainingTime) {}
};

/*
int main() {
    // 10x10 맵 생성
    Map gameMap(10, 10);

    // 파괴 가능한 벽 설정
    gameMap.setTile(2, 3, TileType::DestructibleBlock, true);

    // 아이템 추가
    Item bombIncreaseItem(ItemType::BombIncrease, 4, 4, 0);
    gameMap.addItem(bombIncreaseItem);

    // 스폰 위치 추가
    gameMap.addSpawnPoint(0, 0);
    gameMap.addSpawnPoint(9, 9);

    return 0;
}
*/