#include "InterfaceComponent.h"
#include "ComponentManager.h"
InterfaceComponent::InterfaceComponent(GameObject* _owner) : BaseComponent(_owner)
{
ComponentManager<InterfaceComponent>::GetInstance().AddComp(this);
}

InterfaceComponent::~InterfaceComponent()
{
	ComponentManager<InterfaceComponent>::GetInstance().DelComp(this);
}
