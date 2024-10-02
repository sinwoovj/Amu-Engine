#include "EventManager.h"
#include <iostream>

EventManager::EventManager() {}

EventManager::~EventManager() 
{
    DeleteUndispahchEvent();
}

void EventManager::AddEntity(Entity* entity)
{
    entityList.push_back(entity);
}

void EventManager::DelEntity(Entity* entity)
{
    for (auto it = entityList.begin(); it != entityList.end(); it++)
    {
        if (*it == entity)
        {
            entityList.erase(it);
            return;
        }
    }
}

void EventManager::DispatchAllEvents()
{
    while (!allEvents.empty())
    {
        allEvents.front()->DispatchEvent();

        if (allEvents.empty())
            break;

        delete allEvents.front();
        allEvents.pop();
    }
}

void EventManager::DeleteUndispahchEvent()
{
    while (!allEvents.empty())
    {
        delete allEvents.front();
        allEvents.pop();
    }
}
