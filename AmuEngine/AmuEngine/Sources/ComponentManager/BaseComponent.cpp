#include "BaseComponent.h"
#include <sstream>
#include <iostream>
static void ShowComponents(std::string compname, GameObject* own)
{
	#ifdef _DEBUG
	std::ostringstream msg;
	msg << own->GetName() << " : 아직 해당 오브젝트의 컴포넌트는 BaseCompoenent::Init() 함수가 구현되어 있지 않습니다.\n"
		<< "\t예상 컴포넌트 ㄱ" << std::endl;
	for (auto it : own->GetComponents())
	{
		msg << "\t\t" << it.first << std::endl;
	}
	std::string strmsg = msg.str();
	#pragma warning(1 : 4996) // 특정 경고를 활성화하거나 수준 변경
	std::cerr << strmsg << std::endl; // 런타임에 경고 출력
	#endif
}
void BaseComponent::Init()
{
	ShowComponents("Init", owner);
}

void BaseComponent::Update()
{
	ShowComponents("Update", owner);
}

void BaseComponent::Exit()
{
	ShowComponents("Exit", owner);
}

void BaseComponent::Edit()
{
	ShowComponents("Edit", owner);
}