#pragma once
#include "Event.h"
#include <iostream>

class ButtonClickEvent : public Event {
public:
    // 두 개의 인수를 받는 생성자 추가
    ButtonClickEvent(Entity* src, Entity* dst) : Event(src, dst) {}

    void DispatchEvent();
};
