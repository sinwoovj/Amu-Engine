#pragma once
#include "Event.h"

class Entity
{
public:
	virtual void OnEvent(Event* event) = 0;


private:

};