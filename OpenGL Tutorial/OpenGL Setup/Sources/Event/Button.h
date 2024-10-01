#pragma once
#include "../GameObject/GameObject.h"
#include "../EventManager/EventManager.h"
#include "../Components/TransformComp.h"
#include "../Components/SpriteComp.h"
#include "ButtonClickEvent.h"

class Button : public GameObject {
public:
    Button(const std::string& texturePath, const AEVec2& position, const AEVec2& scale) {
        AddComponent<SpriteComp>();
        AddComponent<TransformComp>();

        TransformComp* transform = GetComponent<TransformComp>();
        transform->SetPos(position);
        transform->SetScale(scale);

        SpriteComp* sprite = GetComponent<SpriteComp>();
        sprite->SetTexture(texturePath);
        sprite->SetColor(255, 255, 255);
    }

    bool IsClicked(int mouseX, int mouseY) const {
        TransformComp* transform = GetComponent<TransformComp>();
        AEVec2 position = transform->GetPos();
        AEVec2 scale = transform->GetScale();

        return (mouseX > position.x - scale.x / 2 && mouseX < position.x + scale.x / 2 &&
            mouseY > position.y - scale.y / 2 && mouseY < position.y + scale.y / 2);
    }

    void OnClick() {

        //EventManager::GetInstance().AddEvent<ButtonClickEvent>(this, this);
    }

    //void OnEvent(Event* event) override {

    //    ButtonClickEvent* clickEvent = dynamic_cast<ButtonClickEvent*>(event);
    //    if (clickEvent) {
    //        std::cout << "Button clicked and event handled in OnEvent!" << std::endl;

    //    }
    //}
};
