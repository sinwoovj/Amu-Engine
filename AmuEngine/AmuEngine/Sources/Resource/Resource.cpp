#include "Resource.h"

void* Resource::GetData()
{
    return data;
}

const int& Resource::GetCounter() const
{
    return counter;
}

void Resource::SetCounter(const int& _counter)
{
    counter = _counter;
}