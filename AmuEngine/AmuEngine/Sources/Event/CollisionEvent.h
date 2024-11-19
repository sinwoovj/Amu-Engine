#pragma once
#include "Event.h"

struct CollisionEvent : public Event
{
	CollisionEvent(Entity* _src, Entity* _dst) : Event(_src, _dst) {}
};