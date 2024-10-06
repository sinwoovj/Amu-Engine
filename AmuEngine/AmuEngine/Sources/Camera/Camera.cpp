#include "Camera.h"
#include "../GameObjectManager/GameObjectManager.h"

#define PADDING 20

Camera::Camera() : world_to_ndc_xform()
{
}

Camera::~Camera()
{

}

void Camera::Update()
{
	world_to_ndc_xform[0] = glm::mat3(1.0f);
	world_to_ndc_xform[1] = glm::mat3(1.0f);

	// �����ϸ� ���� (x�� 2 / height��, y�� 2 / height��)
	glm::mat3 scaleMatrix = glm::mat3(1.0f);
	scaleMatrix[0][0] = 2 / height;  // x�� ������
	scaleMatrix[1][1] = 2 / height;  // y�� ������

	// ������ ����� �� ��Ŀ� ���ϱ�
	world_to_ndc_xform[0] = world_to_ndc_xform[0] * scaleMatrix;

	// �����ϸ� ���� (x�� 0.1f / height��, y�� 0.1f / height��)
	scaleMatrix[0][0] = 0.1f / height;  // x�� ������
	scaleMatrix[1][1] = 0.1f / height;  // y�� ������

	// ������ ����� �� ��Ŀ� ���ϱ�
	world_to_ndc_xform[1] = world_to_ndc_xform[0] * scaleMatrix;
}

void Camera::GetPos(float* px, float* py)
{
	if (fix)
	{
		*px = srcX;
		*py = srcY;
	}
	else
	{
		*px = x;
		*py = y;
	}
}

void Camera::SetHeight(float value)
{
	height = glm::clamp(value, 0.5f, 4.f);
}

void Camera::SetPos(float _x, float _y)
{
	srcX = _x;
	srcY = _y;

	srcX = glm::clamp(srcX, minX, maxX);
	srcY = glm::clamp(srcY, minY, maxY);
}

