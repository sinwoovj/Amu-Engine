#include "Event.h"
#include "Entity.h"

Event::Event(Entity* _src, Entity* _dst) : src(_src), dst(_dst)
{

}

void Event::DispatchEvent()
{
	dst->OnEvent(this);
}
