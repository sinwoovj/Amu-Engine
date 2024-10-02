#include "EventManager.h"
template<typename T>
inline void EventManager::AddEvent(Entity* _src, Entity* _dst)
{
	if (_dst != nullptr)
	{
		Event* event = new T(_src, _dst);
		allEvents.push(event);
	}
	else
	{
		for (auto& it : entityList)
		{
			Event* event = new T(_src, it);
			allEvents.push(event);
		}
	}
}

template<typename T>
inline void EventManager::AddEvent(Entity* _src, Entity* _dst, bool b)
{
	if (_dst != nullptr)
	{
		Event* event = new T(_src, _dst, b);
		allEvents.push(event);
	}
	else
	{
		for (auto& it : entityList)
		{
			Event* event = new T(_src, it, b);
			allEvents.push(event);
		}
	}
}
