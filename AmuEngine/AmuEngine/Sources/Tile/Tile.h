#pragma once
#include "../Components/SpriteComp.h"
/*
 Tile 클래스
각 타일의 정보를 나타내는 Tile 클래스입니다.
타일 유형, 파괴 가능 여부, 위치 등 정보를 포함합니다.
*/
class Tile {
public:
    enum TileType {
        Empty,
        Wall,
        DestructibleBlock
    };
    /*
    플래그 및 상태 관리
    플래그를 비트 마스크로 정의하여 타일이나
    오브젝트의 다양한 상태를 관리할 수 있습니다.
    */
    enum TileFlags {
        HasBomb = 1 << 0,     // 타일에 폭탄이 있는지 여부
         HasItem = 1 << 1,     // 타일에 아이템이 있는지 여부
        IsOccupied = 1 << 2,   // 타일에 캐릭터가 있는지 여부
        IsSpawnpoint = 1 << 3  // 타일에 스폰포인트가 있는지 여부
    };
    TileType type;
    int x, y;  // 타일 좌표
    std::string spritePath;

    Tile(TileType type, int x, int y)
        : type(type), x(x), y(y), spritePath(SpriteComp::DefaultSprite) {}
};
