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
	Mtx33Identity(&world_to_ndc_xform[0]);
	Mtx33Identity(&world_to_ndc_xform[1]);

	Mtx33ScaleApply(&world_to_ndc_xform[0], &world_to_ndc_xform[0], 2 / height, 2 / height);
	Mtx33ScaleApply(&world_to_ndc_xform[1], &world_to_ndc_xform[1], 0.1f / height, 0.1f / height);
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
	height = Clamp(value, 0.5, 4);
}

void Camera::SetPos(float _x, float _y)
{
	srcX = _x;
	srcY = _y;

	srcX = Clamp(srcX, minX, maxX);
	srcY = Clamp(srcY, minY, maxY);
}

