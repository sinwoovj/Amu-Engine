/*
Item Ŭ����
�ʿ� ��ġ�Ǵ� �������� ������ ȿ���� �����ϴ� Item Ŭ�����Դϴ�.
*/
#include "../Data/Data.h"

class Item {
public:
    Data::ItemData::ItemType type;
    int x, y;     // �������� ��ġ
    int duration; // ���� �ð�

    Item(Data::ItemData::ItemType type, int x, int y, int duration)
        : type(type), x(x), y(y), duration(duration) {}
};
