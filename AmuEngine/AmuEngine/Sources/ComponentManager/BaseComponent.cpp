#include "BaseComponent.h"
#include <sstream>
#include <iostream>
static void ShowComponents(std::string compname, GameObject* own)
{
	#ifdef _DEBUG
	std::ostringstream msg;
	msg << own->GetName() << " : ���� �ش� ������Ʈ�� ������Ʈ�� BaseCompoenent::Init() �Լ��� �����Ǿ� ���� �ʽ��ϴ�.\n"
		<< "\t���� ������Ʈ ��" << std::endl;
	for (auto it : own->GetComponents())
	{
		msg << "\t\t" << it.first << std::endl;
	}
	std::string strmsg = msg.str();
	#pragma warning(1 : 4996) // Ư�� ��� Ȱ��ȭ�ϰų� ���� ����
	std::cerr << strmsg << std::endl; // ��Ÿ�ӿ� ��� ���
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