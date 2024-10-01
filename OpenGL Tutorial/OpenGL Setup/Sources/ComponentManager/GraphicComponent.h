#pragma once
#include "BaseComponent.h"

class GraphicComponent : public BaseComponent
{
private:
	GraphicComponent() = delete;
public:
	GraphicComponent(GameObject* _owner);
	~GraphicComponent();
};