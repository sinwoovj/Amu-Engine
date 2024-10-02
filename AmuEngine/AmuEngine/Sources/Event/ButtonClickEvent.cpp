#include "ButtonClickEvent.h"
#include "Entity.h"

void ButtonClickEvent::DispatchEvent()
{
    std::cout << "Dispatching ButtonClickEvent for button!" << std::endl;
    if (dst) {
        dst->OnEvent(this);
    }
}
