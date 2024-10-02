#pragma once
#include "Event.h"

struct CollisionEvent : public Event
{
	bool isProjectile;

	CollisionEvent(Entity* _src, Entity* _dst, bool _isProjectile = false) : Event(_src, _dst), isProjectile(_isProjectile) {}
};