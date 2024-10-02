#pragma once
#include "BaseComponent.h"

class EngineComponent : public BaseComponent
{
private:
	EngineComponent() = delete;
public:
	EngineComponent(GameObject* _owner);
	~EngineComponent();
};