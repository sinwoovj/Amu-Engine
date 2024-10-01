#pragma once
#include <string>

class Entity;

struct Event
{
	Event(Entity* _src, Entity* _des);
	virtual ~Event() = default;

	void DispatchEvent();
	
	Entity* src;
	Entity* dst;
};