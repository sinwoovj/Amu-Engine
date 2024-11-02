/*
 Tile Ŭ����
�� Ÿ���� ������ ��Ÿ���� Tile Ŭ�����Դϴ�.
Ÿ�� ����, �ı� ���� ����, ��ġ �� ������ �����մϴ�.
*/

enum class TileType {
    Empty,
    Wall,
    DestructibleBlock,
    SpawnPoint,
    PowerUp
};

/*
�÷��� �� ���� ����
�÷��׸� ��Ʈ ����ũ�� �����Ͽ� Ÿ���̳� 
������Ʈ�� �پ��� ���¸� ������ �� �ֽ��ϴ�.
*/
enum TileFlags {
    HasBomb = 1 << 0,     // Ÿ�Ͽ� ��ź�� �ִ��� ����
    HasItem = 1 << 1,     // Ÿ�Ͽ� �������� �ִ��� ����
    IsOccupied = 1 << 2   // Ÿ�Ͽ� ĳ���Ͱ� �ִ��� ����
};

class Tile {
public:
    TileType type;
    bool destructible;
    int x, y;  // Ÿ�� ��ǥ

    Tile(TileType type, bool destructible, int x, int y)
        : type(type), destructible(destructible), x(x), y(y) {}
};
