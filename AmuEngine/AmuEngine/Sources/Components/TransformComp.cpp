#include "TransformComp.h"
#include "../Camera/Camera.h"
#include "SpriteComp.h"
#include <Size.h>
#include <EasyImgui.h>

void TransformComp::CalculateMatrix()
{
	//Create a translate matrix
	glm::mat3 translateMtx = glm::identity<glm::mat3x3>();
	Mtx33Trans(&translateMtx, pos.x, pos.y);

	//Create a rotation matrix
	glm::mat3 rotationMtx = glm::identity<glm::mat3x3>();
	Mtx33Rot(&rotationMtx, rot);

	//Create a scale matrix
	glm::mat3 scaleMtx = glm::identity<glm::mat3x3>();
	Mtx33Scale(&scaleMtx, scale.x, scale.y);

	//Concatenate them
	Mtx33Concat(&transformMatrix , &scaleMtx, &rotationMtx);
	Mtx33Concat(&transformMatrix , &translateMtx, &transformMatrix);

}

TransformComp::TransformComp(GameObject* _owner) : LogicComponent(_owner), pos({ 0,0 }), scale({ 1,1 }), rot(0), transformMatrix(glm::identity<glm::mat3>())
{
	pos.x = 0;
	pos.y = 0;

	scale.x = 1;
	scale.y = 1;

	rot = 0;

	CalculateMatrix();
}

TransformComp::~TransformComp()
{

}

void TransformComp::Update()
{
	CalculateMatrix();
}

void TransformComp::SetPos(const glm::vec2& otherPos)
{
	this->pos = otherPos;
}

void TransformComp::SetScale(const glm::vec2& otherScale)
{
	this->scale = otherScale;
}

void TransformComp::SetRot(const float& otherRot)
{
	this->rot = otherRot;
}

void TransformComp::ReverseX(int val)
{
	switch (val)
	{
	case 0:
		scale.x = -abs(scale.x);
		break;
	case 1:
		scale.x = abs(scale.x);
		break;
	}
}

void TransformComp::ReverseY(int val)
{
	switch (val)
	{
	case 0:
		scale.y = -abs(scale.y);
		break;
	case 1:
		scale.y = abs(scale.y);
		break;
	}
}

void TransformComp::PrintMatrix()
{
	std::cout << "Printing Transform Comp. With this values: " << std::endl;
	std::cout << "Translate : " << pos.x << " " << pos.y << std::endl;
	std::cout << "Rotation : " << rot << std::endl;
	std::cout << "Scale : " << scale.x << " " << scale.y << std::endl;

	for (int i = 0; i < 3; i++)
	{
		std::cout << "|";
		for (int x = 0; x < 3; x++)
		{
			std::cout << " " << transformMatrix[i][x];
		}

		std::cout << " |";
		std::cout << std::endl;
	}
}

void TransformComp::Edit()
{
	ImGui::LabelText("label", "Value");

	//Pos
	ImGui::SeparatorText("Position");
	{
		ImGui::DragFloat("Pos X", &pos.x, 1);
		ImGui::DragFloat("Pos Y", &pos.y, 1);
		ImGui::PushID(1);
		if (ImGui::Button("Initialize"))
		{
			pos = { 0 , 0 };
		}
		ImGui::PopID();
	}
	
	//Scale
	static float scaleSize;
	ImGui::SeparatorText("Scale");
	{
		static bool fixedRatio = false;
		ImGui::Checkbox("Fixed Ratio", &fixedRatio);
		if (fixedRatio)
		{
			scaleSize = scale.x;
			ImGui::DragFloat("Size", &scaleSize, 0.01f, 0.0000001f);
			scale = { scaleSize, scaleSize };
		}
		else
		{
			ImGui::DragFloat("Width", &scale.x, 0.01f, 0.0000001f);
			ImGui::DragFloat("Height", &scale.y, 0.01f, 0.0000001f);
		}
		ImGui::PushID(2);
		if (ImGui::Button("Initialize"))
		{
			scaleSize = 1;
			scale = { 1 , 1 };
		}
		ImGui::PopID();
	}
	
	//Rot
	ImGui::SeparatorText("Rotation");
	{
		ImGui::SliderAngle("Angle (Degrees)", &rot);
		ImGui::PushID(3);
		if (ImGui::Button("Initialize"))
		{
			rot = 0;
		}
		ImGui::PopID();
	}
}

void TransformComp::LoadFromJson(const json& data)
{
	// Check how you saved, load from there
	auto compData = data.find("compData");

	if (compData != data.end())
	{
		auto p = compData->find("position");
		pos.x = p->begin().value();
		pos.y = (p->begin() + 1).value();

		auto s = compData->find("scale");
		scale.x = s->begin().value();
		scale.y = (s->begin() + 1).value();

		auto r = compData->find("rotation");
		rot = r.value();
	}

	// Data is loaded

	// Utilize the data
	CalculateMatrix();
}

json TransformComp::SaveToJson()
{
	json data;

	data["type"] = TypeName;

	json compData;
	compData["position"] = { pos.x, pos.y };
	compData["scale"] = { scale.x, scale.y };
	compData["rotation"] = rot;

	data["compData"] = compData;
	return data;
}

BaseRTTI* TransformComp::CreateTransformComponent(GameObject* owner)
{
	BaseRTTI* p = new TransformComp(owner);

	owner->AddComponent<TransformComp>(static_cast<BaseComponent*>(p));

	return p;
}

