#include "EngineComponent.h"
#include "ComponentManager.h"

EngineComponent::EngineComponent(GameObject* _owner) : BaseComponent(_owner) 
{
	ComponentManager<EngineComponent>::GetInstance().AddComp(this);
}

EngineComponent::~EngineComponent()
{
	ComponentManager<EngineComponent>::GetInstance().DelComp(this);
}
