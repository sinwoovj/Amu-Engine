#pragma once
#include "BaseComponent.h"

class LogicComponent : public BaseComponent
{
private:
	LogicComponent() = delete;
public:
	LogicComponent(GameObject* _owner);
	~LogicComponent();
};