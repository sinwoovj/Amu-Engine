/*
Item 클래스
맵에 배치되는 아이템의 종류와 효과를 정의하는 Item 클래스입니다.
*/
#include "../Data/Data.h"

class Item {
public:
    Data::ItemData::ItemType type;
    int x, y;     // 아이템의 위치
    int duration; // 지속 시간

    Item(Data::ItemData::ItemType type, int x, int y, int duration)
        : type(type), x(x), y(y), duration(duration) {}
};
