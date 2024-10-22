#include "Registry.h"
#include "../Components/Components.h"

Registry::Registry()
{
    // Register ALL the functions
    //rttiMap.insert({ AudioComp::TypeName, &AudioComp::CreateAudioComponent });
    rttiMap.insert({ TransformComp::TypeName, &TransformComp::CreateTransformComponent });
    rttiMap.insert({ SpriteComp::TypeName, &SpriteComp::CreateSpriteComponent });
    rttiMap.insert({ RigidbodyComp::TypeName, &RigidbodyComp::CreateRigidBodyComponent });
    rttiMap.insert({ ColliderComp::TypeName, &ColliderComp::CreateColliderComponent });
    rttiMap.insert({ PlayerComp::TypeName, &PlayerComp::CreatePlayerComponent });
}

BaseRTTI* Registry::FindAndCreate(const std::string& type, GameObject* owner)
{
    BaseRTTI* ptr = nullptr;
    if (rttiMap.find(type) != rttiMap.end())
        ptr = rttiMap[type](owner);
    else
        throw std::invalid_argument("Registry FindAndCreate Invalid typeName " + type);

    return ptr;
}
