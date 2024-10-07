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

	backGroundtf->SetScale({ 300, 300 });
	backGroundtf->SetRot(glm::radians(45.0f));
	backGroundsp->SetTexture("Sources/Assets/Exam.png");
	//backGroundsp->SetAlpha(1);
}

void level::Menu::Update() 
{ 
	if(c % 1000 == 500)
		backGround->GetComponent<SpriteComp>()->SetTexture("Sources/Assets/A.png");
	else if(c % 1000 == 0)
		backGround->GetComponent<SpriteComp>()->SetTexture("Sources/Assets/Exam.png");

	c++;
}

void level::Menu::Exit() 
{
	
}
