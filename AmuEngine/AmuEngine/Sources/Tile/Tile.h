#pragma once
/*
 Tile Ŭ����
�� Ÿ���� ������ ��Ÿ���� Tile Ŭ�����Դϴ�.
Ÿ�� ����, �ı� ���� ����, ��ġ �� ������ �����մϴ�.
*/
class Tile {
public:
    enum TileType {
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
    TileType type;
    bool destructible;
    float x, y;  // Ÿ�� ��ǥ

    Tile(TileType type, bool destructible, float x, float y)
        : type(type), destructible(destructible), x(x), y(y) {}
};
