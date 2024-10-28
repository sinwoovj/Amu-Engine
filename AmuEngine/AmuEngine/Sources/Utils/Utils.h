#pragma once
#include "Size.h"
#include <string>

void AESleep(long long t);
float GetMouseCursorPositionX();
float GetMouseCursorPositionY();
float GetCamPositionX();
float GetCamPositionY();
int PosToMapX(float x);
int PosToMapY(float y);
float MapToPosX(float ind);
float MapToPosY(float ind);
float GetSqDistance(float ax, float ay, float bx, float by);

namespace Utility {
	std::string FileDialog();
}