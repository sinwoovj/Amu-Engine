#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include "../Event/Event.h"
#include "../Event/Entity.h"
#include "../GameObject/GameObject.h"

class EventManager
{
private:
	//A container for all my events* (queue)
	std::queue<Event*> allEvents;
	std::vector<Entity*> entityList;

	//Make singleton
	EventManager();

	//	Remove the compiler defined Copy Constructor and Assignment operator
	EventManager(const EventManager& other) = delete;
	const EventManager& operator=(const EventManager& other) = delete;

	//	Prevent others destroying me
	~EventManager();

	//	Pointer to the exisiting Singleton can be accessed without an obj and from me only
	static EventManager* ptr;

public:
	static EventManager& GetInstance()
	{
		static EventManager instance;
		return instance;
	}

	// Add an event (event*) this are pointers to dynamic memory, called as the following: AddEvent(new Event);
	template <typename T>
	void AddEvent(Entity* src, Entity* dst);

	template <typename T>
	void AddEvent(Entity* src, Entity* dst, bool b);

	void AddEntity(Entity* entity);
	void DelEntity(Entity* entity);

	// DispatchAllEvents
	void DispatchAllEvents();

	// delete undispatched events if any on destructor
	void DeleteUndispahchEvent();
};

#include "EventManager.inl"
