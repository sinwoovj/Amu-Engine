#pragma once
#include "../Data/Data.h"
/*
Item Ŭ����
�ʿ� ��ġ�Ǵ� �������� ������ ȿ���� �����ϴ� Item Ŭ�����Դϴ�.
*/
class Item {
public:
    Data::ItemData::ItemType type;
    float x, y;     // �������� ��ġ
    float duration; // ���� �ð�

    Item(Data::ItemData::ItemType type_, float x_, float y_, float duration_)
        : type(type_), x(x_), y(y_), duration(duration_) {}
};
