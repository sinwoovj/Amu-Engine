#include "LogicComponent.h"
#include "ComponentManager.h"

LogicComponent::LogicComponent(GameObject* _owner) : BaseComponent(_owner)
{
	ComponentManager<LogicComponent>::GetInstance().AddComp(this);
}

LogicComponent::~LogicComponent()
{
	ComponentManager<LogicComponent>::GetInstance().DelComp(this);
}
