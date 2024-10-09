#include "Menu.h"
#include <iostream> 
#include "../Components/SpriteComp.h"
#include "../Components/TransformComp.h"
#include "../Camera/Camera.h"


void level::Menu::Init() 
{
	Camera::GetInstance().SetPos(0, 0);

	// 배경 초기화
	backGround = new GameObject("backGround");

	backGround->AddComponent<SpriteComp>();
	backGround->AddComponent<TransformComp>();
	
	SpriteComp* backGroundsp = backGround->GetComponent<SpriteComp>();
	TransformComp* backGroundtf = backGround->GetComponent<TransformComp>();

	
	backGroundsp->SetTexture("Sources/Assets/Exam.png");
}

void level::Menu::Update() 
{
	TransformComp* backGroundtf = backGround->GetComponent<TransformComp>();
	backGroundtf->SetRot(glm::radians(1.0f) * c);

	backGroundtf->SetPos({ 0.01 * c , 0.01 * c });
	c++;
}

void level::Menu::Exit() 
{
	
}
