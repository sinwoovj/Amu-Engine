#include "RigidbodyComp.h"
#include "TransformComp.h"
#include <EasyImgui.h>
#include "../Utils/Direction.h"

bool RigidbodyComp::CheckEpsilon(float v, float EP)
{
	if (v < -EP || v > EP)
		return true;

	return false;
}

void RigidbodyComp::CorrectPosByAABB(ColliderComp* oc, ColliderComp* c, float& x, float& y)
{
	float dis[4] =
	{
		abs(oc->GetPos().x + oc->GetScale().x / 2 + 0.5f - (c->GetPos().x - c->GetScale().x / 2)),
		abs(oc->GetPos().x - oc->GetScale().x / 2 - 0.5f - (c->GetPos().x + c->GetScale().x / 2)),
		abs(oc->GetPos().y + oc->GetScale().y / 2 - (c->GetPos().y - c->GetScale().y / 2)),
		abs(oc->GetPos().y - oc->GetScale().y / 2 - (c->GetPos().y + c->GetScale().y / 2))
	};

	float minDis = dis[0];
	int minInd = 0;

	for (int i = 1; i < 3; i++)
	{
		if (dis[i] < minDis)
		{
			minDis = dis[i];
			minInd = i;
		}
	}

	if (minDis < 0.1f)
		return;

	switch (minInd)
	{
	case 0:
		x = oc->GetPos().x + oc->GetScale().x / 2 + c->GetScale().x / 2 + 1;
		//velocity.x = 0;
		break;
	case 1:
		x = oc->GetPos().x - oc->GetScale().x / 2 - c->GetScale().x / 2 - 1;
		//velocity.x = 0;
		break;
	case 2:
		y = oc->GetPos().y + oc->GetScale().y / 2 + c->GetScale().y / 2;
		velocity.y = 0;
		break;
	case 3:
		y = oc->GetPos().y - oc->GetScale().y / 2 - c->GetScale().y / 2;
		velocity.y = 0;
		break;
	}
}

RigidbodyComp::RigidbodyComp(GameObject* _owner) : EngineComponent(_owner), velocity(), maxVelocity()
{
	velocity.x = 0;
	velocity.y = 0;
	maxVelocity.x = 500;
	maxVelocity.y = 500;

	acceleration.x = 0;
	acceleration.y = 0;
	maxAcceleration.x = 500;
	maxAcceleration.y = 500;
}

RigidbodyComp::~RigidbodyComp()
{

}

void RigidbodyComp::AddVelocity(const glm::vec2& other)
{
	velocity.x += other.x;
	velocity.y += other.y;
}

void RigidbodyComp::AddVelocity(float x, float y)
{
	velocity.x += x;
	velocity.y += y;
}

float RigidbodyComp::GetVelocityX()
{
	return velocity.x;
}

float RigidbodyComp::GetVelocityY()
{
	return velocity.y;
}

void RigidbodyComp::SetVelocity(const glm::vec2& other)
{
	velocity.x = other.x;
	velocity.y = other.y;
}

void RigidbodyComp::SetVelocity(float x, float y)
{
	velocity.x = x;
	velocity.y = y;
}

void RigidbodyComp::SetVelocityX(float x)
{
	velocity.x = x;
}

void RigidbodyComp::SetVelocityY(float y)
{
	velocity.y = y;
}

void RigidbodyComp::ClearVelocity()
{
	velocity.x = 0;
	velocity.y = 0;
}

void RigidbodyComp::AddAcceleration(const glm::vec2& other)
{
	if (acceleration.x * other.x < 0) acceleration.x = 0;
	if (acceleration.y * other.y < 0) acceleration.y = 0;

	acceleration.x += other.x;
	acceleration.y += other.y;

	acceleration.x = glm::clamp(acceleration.x, -maxAcceleration.x, maxAcceleration.x);
	acceleration.y = glm::clamp(acceleration.y, -maxAcceleration.y, maxAcceleration.y);
}

void RigidbodyComp::AddAcceleration(float x, float y)
{
	if (acceleration.x * x < 0) acceleration.x = 0;
	if (acceleration.y * y < 0) acceleration.y = 0;

	acceleration.x += x;
	acceleration.y += y;

	acceleration.x = glm::clamp(acceleration.x, -maxAcceleration.x, maxAcceleration.x);
	acceleration.y = glm::clamp(acceleration.y, -maxAcceleration.y, maxAcceleration.y);
}

void RigidbodyComp::SetAcceleration(const glm::vec2& other)
{
	acceleration.x = other.x;
	acceleration.y = other.y;
}

void RigidbodyComp::SetAcceleration(float x, float y)
{
	acceleration.x = x;
	acceleration.y = y;
}

void RigidbodyComp::ClearAcceleration()
{
	acceleration.x = 0;
	acceleration.y = 0;
}

void RigidbodyComp::Update()
{
	float dt = (float)1 / 60; //Framerate 수정 필요
	
	//Get the transform
	TransformComp* t = owner->GetComponent<TransformComp>();
	if (!t)	return;

	float tx = t->GetPos().x;
	float ty = t->GetPos().y;

	float tw = t->GetScale().x;
	float th = t->GetScale().y;

	velocity.x += acceleration.x * dt;
	velocity.y += acceleration.y * dt + (useGravity ? -500.f * dt : 0.f);

	velocity.x = glm::clamp(velocity.x, -maxVelocity.x, maxVelocity.x);
	velocity.y = glm::clamp(velocity.y, -maxVelocity.y, maxVelocity.y);

	float x = t->GetPos().x + velocity.x * dt;
	float y = t->GetPos().y + velocity.y * dt;

	velocity.x /= drag;
	velocity.y /= drag;

	////If im too low, just set to 0
	if (CheckEpsilon(velocity.x) == false)
		velocity.x = 0;

	if (CheckEpsilon(velocity.y) == false)
		velocity.y = 0;

	//ColliderComp* c = owner->GetComponent<ColliderComp>();
	//if (c != nullptr)
	//{
	//	if (t->GetRot() < targetRot)
	//	{
	//		t->SetRot(t->GetRot() + dt * 10);
	//	}

	//	if (t->GetRot() > targetRot)
	//	{
	//		t->SetRot(t->GetRot() - dt * 10);
	//	}

	//	if (abs(t->GetRot() - targetRot) < 0.2f)
	//	{
	//		t->SetRot(targetRot);
	//	}

	//	/*if (AERadToDeg(targetRot) > 40)
	//		velocity.x = -10;
	//	if (AERadToDeg(targetRot) < -40)
	//		velocity.x = 10;*/

	//	if (oppoCollider.size() > 1)
	//		c->SetPos({ c->GetPos().x, c->GetPos().y + 1.f });

	//	while (!oppoCollider.empty())
	//	{
	//		ColliderComp* oc = oppoCollider.front();
	//		oppoCollider.pop();

	//		GameObject::Type type = oc->GetOwner()->type;

	//		if (type == GameObject::Square && !colliderType[GameObject::LeftTri] && !colliderType[GameObject::RightTri])
	//		{
	//			CorrectPosByAABB(oc, c, x, y);
	//			targetRot = glm::radians<float>(0);
	//		}

	//		else if (type == GameObject::RightTri)
	//		{
	//			if (colliderType[GameObject::Square] && c->GetPos().x > oc->GetPos().x)
	//			{
	//				CorrectPosByAABB(oc, c, x, y);
	//				targetRot = glm::radians<float>(0);
	//			}
	//			else
	//			{
	//				targetRot = glm::atan(oc->GetScale().y / oc->GetScale().x);
	//				y = oc->GetPos().y +
	//					(c->GetPos().x + (c->GetScale().x / 2 * (abs(glm::sin(targetRot) * 0.5f))) - oc->GetPos().x) *
	//					(oc->GetScale().y / oc->GetScale().x) +
	//					c->GetScale().y / 2;
	//			}
	//		}

	//		else if (type == GameObject::LeftTri)
	//		{
	//			if (colliderType[GameObject::Square] && c->GetPos().x < oc->GetPos().x)
	//			{
	//				CorrectPosByAABB(oc, c, x, y);
	//				targetRot = glm::radians<float>(0);
	//			}
	//			else
	//			{
	//				targetRot = glm::atan(-oc->GetScale().y / oc->GetScale().x);
	//				y = oc->GetPos().y +
	//					(c->GetPos().x - (c->GetScale().x / 2 * (abs(glm::sin(targetRot) * 0.5f))) - oc->GetPos().x) *
	//					(-oc->GetScale().y / oc->GetScale().x) +
	//					c->GetScale().y / 2;
	//			}
	//		}
	//	}

	//	for (auto& i : colliderType)
	//		i = false;

	//	c->SetPos({ x, y });
	//}

	t->SetPos({ x, y });
}

void RigidbodyComp::Edit()
{
	ImGui::LabelText("label", "Value");

	//Show indicator line
	ImGui::SeparatorText("Gravity");
	{
		static bool gravity = false;
		ImGui::Checkbox("Use Gravity", &gravity);
		if (gravity)
		{
			useGravity = true;
		}
		else
		{
			useGravity = false;
		}
	}

	//Drag
	ImGui::SeparatorText("Drag");
	{
		ImGui::DragFloat("Value", &drag, 0.01f);
		ImGui::PushID(1);
		if (ImGui::Button("Initialize"))
		{
			drag = 1.01f;
		}
		ImGui::PopID();
	}
	
	//Rot
	ImGui::SeparatorText("Rotation");
	{
		ImGui::SliderAngle("Angle (Degrees)", &targetRot);
		ImGui::PushID(2);
		if (ImGui::Button("Initialize"))
		{
			targetRot = 0;
		}
		ImGui::PopID();
	}

	//Velocity
	ImGui::SeparatorText("Velocity");
	{
		ImGui::Text("X");
		ImGui::SameLine();
		ImGui::DragFloat("##VelocityX", &velocity.x, 0.01f, 0, maxVelocity.x);
		ImGui::Text("Y");
		ImGui::SameLine();
		ImGui::DragFloat("##VelocityY", &velocity.y, 0.01f, 0, maxVelocity.x);
		ImGui::Text("MAX X");
		ImGui::SameLine();
		ImGui::DragFloat("##VelocityMAX X", &maxVelocity.x, 0.01f, velocity.x);
		ImGui::Text("MAX X");
		ImGui::SameLine();
		ImGui::DragFloat("##VelocityMAX Y", &maxVelocity.y, 0.01f, velocity.y);
		ImGui::PushID(3);
		if (ImGui::Button("Initialize"))
		{
			velocity = { 0,0 };
			maxVelocity = { 500, 500 };
		}
		ImGui::PopID();
	}

	//Acceleration
	ImGui::SeparatorText("Acceleration");
	{
		ImGui::Text("X");
		ImGui::SameLine();
		ImGui::DragFloat("##AccelerationX", &acceleration.x, 0.01f, 0, maxAcceleration.x);
		ImGui::Text("Y");
		ImGui::SameLine();
		ImGui::DragFloat("##AccelerationY", &acceleration.y, 0.01f, 0, maxAcceleration.y);
		ImGui::Text("MAX X");
		ImGui::SameLine();
		ImGui::DragFloat("##AccelerationMAX X", &maxAcceleration.x, 0.01f, velocity.x);
		ImGui::Text("MAX X");
		ImGui::SameLine();
		ImGui::DragFloat("##AccelerationMAX Y", &maxAcceleration.y, 0.01f, velocity.y);
		ImGui::PushID(4);
		if (ImGui::Button("Initialize"))
		{
			acceleration = { 0,0 };
			maxAcceleration = { 500, 500 };
		}
		ImGui::PopID();
	}
}

void RigidbodyComp::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");

	if (compData != data.end())
	{
		auto it = compData->find("velocity");
		velocity.x = it->begin().value();
		velocity.y = (it->begin() + 1).value();

		it = compData->find("maxVelocity");
		maxVelocity.x = it->begin().value();
		maxVelocity.y = (it->begin() + 1).value();

		it = compData->find("useGravity");
		useGravity = it.value();
	}
}

json RigidbodyComp::SaveToJson()
{
	json data;
	data["type"] = TypeName;

	json compData;
	compData["velocity"] = { velocity.x, velocity.y };
	compData["maxVelocity"] = { maxVelocity.x, maxVelocity.y };
	compData["useGravity"] = useGravity;
	data["compData"] = compData;

	return data;
}

BaseRTTI* RigidbodyComp::CreateRigidBodyComponent(GameObject* owner)
{
	BaseRTTI* p = new RigidbodyComp(owner);
	owner->AddComponent<RigidbodyComp>(static_cast<BaseComponent*>(p));
	return p;
}