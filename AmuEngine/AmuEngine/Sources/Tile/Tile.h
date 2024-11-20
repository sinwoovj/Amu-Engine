#pragma once
#include "../Components/SpriteComp.h"
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
        DestructibleBlock
    };
    /*
    �÷��� �� ���� ����
    �÷��׸� ��Ʈ ����ũ�� �����Ͽ� Ÿ���̳�
    ������Ʈ�� �پ��� ���¸� ������ �� �ֽ��ϴ�.
    */
    enum TileFlags {
        HasBomb = 1 << 0,     // Ÿ�Ͽ� ��ź�� �ִ��� ����
         HasItem = 1 << 1,     // Ÿ�Ͽ� �������� �ִ��� ����
        IsOccupied = 1 << 2,   // Ÿ�Ͽ� ĳ���Ͱ� �ִ��� ����
        IsSpawnpoint = 1 << 3  // Ÿ�Ͽ� ��������Ʈ�� �ִ��� ����
    };
    TileType type;
    int x, y;  // Ÿ�� ��ǥ
    std::string spritePath;

    Tile(TileType type, int x, int y)
        : type(type), x(x), y(y), spritePath(SpriteComp::DefaultSprite) {}
};
