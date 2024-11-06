#pragma once
#include "../Data/Data.h"
/*
Item 클래스
맵에 배치되는 아이템의 종류와 효과를 정의하는 Item 클래스입니다.
*/
class Item {
public:
    Data::ItemData::ItemType type;
    float x, y;     // 아이템의 위치
    float duration; // 지속 시간

    Item(Data::ItemData::ItemType type_, float x_, float y_, float duration_)
        : type(type_), x(x_), y(y_), duration(duration_) {}
};
