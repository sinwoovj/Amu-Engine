#include "RigidbodyComp.h"
#include "TransformComp.h"
#include <EasyImgui.h>
#include "../Utils/Direction.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../CollisionManager/CollisionManager.h"
#include "PlayerComp.h"
#include "SpriteComp.h"
bool RigidbodyComp::CheckEpsilon(float v, float EP)
{
	if (v < -EP || v > EP)
		return true;

	return false;
}

void RigidbodyComp::CorrectPosByAABB(ColliderComp* oc, ColliderComp* c, float& x, float& y)
{
	struct Rect {
		float x, y, width, height;
	};

	auto cp = c->GetOwner()->GetComponent<PlayerComp>();
	glm::vec2 octp = oc->GetOwner()->GetComponent<TransformComp>()->GetPos() + oc->GetPos();
	glm::vec2 ocsts = oc->GetOwner()->GetComponent<SpriteComp>()->GetTextureSize();
	glm::vec2 octs = oc->GetOwner()->GetComponent<TransformComp>()->GetScale() * oc->GetScale() * ocsts;
	glm::vec2 ctp = c->GetOwner()->GetComponent<TransformComp>()->GetPos() + c->GetPos();
	glm::vec2 csts = c->GetOwner()->GetComponent<SpriteComp>()->GetTextureSize();
	glm::vec2 cts = c->GetOwner()->GetComponent<TransformComp>()->GetScale() * c->GetScale() * csts;

	if (!CollisionManager::GetInstance().isCollision(GameObject::Type::Square, octp, octs, GameObject::Type::Square, ctp, cts))
	{
		return;
	}

	Rect a = { octp.x, octp.y, octs.x, octs.y };
	Rect b = { ctp.x, ctp.y, cts.x, cts.y };

	float overlapX = std::min(a.x + a.width, b.x + b.width) - std::max(a.x, b.x);
	float overlapY = std::min(a.y + a.height, b.y + b.height) - std::max(a.y, b.y);
	float offset = 2;
	// X 또는 Y 방향으로 더 적게 겹친 방향으로 이동
	if (overlapX < overlapY) {
		if (a.x < b.x) {
			a.x -= overlapX + offset;  // 왼쪽으로 이동
		}
		else {
			a.x += overlapX + offset;  // 오른쪽으로 이동
		}
	}
	else {
		if (a.y < b.y) {
			a.y -= overlapY + offset;  // 위쪽으로 이동
		}
		else {
			a.y += overlapY + offset;  // 아래쪽으로 이동
		}
	}

	x = a.x;
	y = a.y;
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

	ColliderComp* c = owner->GetComponent<ColliderComp>();
	if (c != nullptr && c->isTrigger)
	{
		//화이트 리스트에 해당하는 레이어에 해당하는 오브젝트들 중 콜라이더 컴포넌트가 있는 오브젝트 중 isTriger가 켜져 있는 오브젝트들만 oppoCollider에 넣고 검사
		for (auto layer : c->triggerLayer)
		{
			for (GameObject* obj : GameObjectManager::GetInstance().ExtractGOToLayer(layer.first))
			{
				if (obj != owner && obj->ExistComponent("ColliderComp"))
				{
					oppoCollider.push(obj->GetComponent<ColliderComp>());
				}
			}
		}
		if (oppoCollider.size() > 1)
		{
			while (!oppoCollider.empty())
			{
				ColliderComp* oc = oppoCollider.front();
				oppoCollider.pop();
				CorrectPosByAABB(oc, c, x, y);
			}
		}
	}

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