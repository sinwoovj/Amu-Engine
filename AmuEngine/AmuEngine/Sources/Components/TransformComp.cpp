#include "TransformComp.h"
#include "../Camera/Camera.h"

void TransformComp::CalculateMatrix()
{
	//Create a translate matrix
	Mtx33 translateMtx;
	Mtx33Trans(&translateMtx, pos.x, pos.y);

	//Create a rotation matrix
	Mtx33 rotationMtx;
	Mtx33Rot(&rotationMtx, rot);

	//Create a scale matrix
	Mtx33 scaleMtx;
	if (affectedByZoom)
	{
		Mtx33Scale(&scaleMtx, scale.x, scale.y);
	}
	else
	{
		Mtx33Scale(&scaleMtx, scale.x * 40, scale.y * 40);
	}

	//Concatenate them
	Mtx33Concat(&transformMatrix, &rotationMtx, &scaleMtx);
	Mtx33Concat(&transformMatrix, &translateMtx, &transformMatrix);

	if (affectedByZoom)
	{
		Mtx33Concat(&transformMatrix, &Camera::GetInstance().GetMatrix(), &transformMatrix);
	}
	else
	{
		Mtx33Concat(&transformMatrix, &Camera::GetInstance().GetMatrix2(), &transformMatrix);
	}
}

TransformComp::TransformComp(GameObject* _owner) : EngineComponent(_owner), pos(), scale(), rot(0), transformMatrix()
{
	pos.x = 0;
	pos.y = 0;

	scale.x = 1;
	scale.y = 1;

	CalculateMatrix();
}

TransformComp::~TransformComp()
{

}

void TransformComp::Update()
{
	CalculateMatrix();
}

void TransformComp::SetPos(const Vec2& otherPos)
{
	this->pos = otherPos;

	//CalculateMatrix();
}

void TransformComp::SetScale(const Vec2& otherScale)
{
	this->scale = otherScale;

	//CalculateMatrix();
}

void TransformComp::SetRot(const float& otherRot)
{
	this->rot = otherRot;

	//CalculateMatrix();
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
			std::cout << " " << transformMatrix.m[i][x];
		}

		std::cout << " |";
		std::cout << std::endl;
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
