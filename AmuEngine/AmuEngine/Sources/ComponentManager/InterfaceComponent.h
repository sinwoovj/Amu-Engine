#pragma once
#include "BaseComponent.h"

class InterfaceComponent : public BaseComponent
{
private:
	InterfaceComponent() = delete;
public:
	InterfaceComponent(GameObject* _owner);
	virtual ~InterfaceComponent();
};