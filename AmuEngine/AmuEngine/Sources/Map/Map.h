/*
Map Ŭ����
�� ��ü�� �����ϴ� Map Ŭ�����Դϴ�. 
Ÿ��, ������, ���� ��ġ �� �� ũ�� ���� �����մϴ�.
*/

#include "../Tile/Tile.h"
#include "../Item/Item.h"
#include "../Data/Data.h"
#include <vector>

class Map {
public:
    int width;
    int height;
    std::vector<std::vector<Tile>> tiles;       // 2D �迭 ������ Ÿ�� ��
    std::vector<Item> items;                    // �ʿ� ��ġ�� �����۵�
    std::vector<std::pair<int, int>> spawnPoints;  // �÷��̾� �� NPC�� ���� ��ġ��

    Map(int width, int height) : width(width), height(height) {
        // �� ũ�⿡ �°� �� Ÿ�Ϸ� �ʱ�ȭ
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
MapObject Ŭ���� (��: ��ź, �� ��)
�ʿ� ��ġ�Ǵ� ������Ʈ�� ���¸� �����ϴ� MapObject Ŭ�����Դϴ�. 
���� ��� ��ź�� ��ġ ��ġ�� ���� ���� ���� �����մϴ�.
*/

enum class MapObjectType {
    Bomb,
    Shield,
    Obstacle
};

class MapObject {
public:
    MapObjectType type;
    int x, y;        // ������Ʈ�� ��ġ
    int range;       // ���� ���� (��ź�� ���)
    int remainingTime; // ���� �ð�

    MapObject(MapObjectType type, int x, int y, int range, int remainingTime)
        : type(type), x(x), y(y), range(range), remainingTime(remainingTime) {}
};

/*
int main() {
    // 10x10 �� ����
    Map gameMap(10, 10);

    // �ı� ������ �� ����
    gameMap.setTile(2, 3, TileType::DestructibleBlock, true);

    // ������ �߰�
    Item bombIncreaseItem(ItemType::BombIncrease, 4, 4, 0);
    gameMap.addItem(bombIncreaseItem);

    // ���� ��ġ �߰�
    gameMap.addSpawnPoint(0, 0);
    gameMap.addSpawnPoint(9, 9);

    return 0;
}
*/