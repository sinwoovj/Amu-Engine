#pragma once
#include "../ComponentManager/BaseComponent.h"
#include "../ComponentManager/LogicComponent.h"
#include "../ComponentManager/EngineComponent.h"
#include "../ComponentManager/GraphicComponent.h"
//#include "../Components/AudioComp.h"
#include "../Components/SpriteComp.h"
#include "../Components/TransformComp.h"
#include "../Components/ColliderComp.h"
#include "../Components/RigidBodyComp.h"
#include "../Components/PlayerComp.h"
#include "../Bomb/BombComp.h"
#include <string>
#include <vector>

static const std::vector<std::string> compName =
{
	SpriteComp::TypeName,
	TransformComp::TypeName,
	ColliderComp::TypeName,
	RigidbodyComp::TypeName,
	PlayerComp::TypeName,
	BOMB::BombComp::TypeName
};