#pragma once
#include "AMMtx33.h"

struct Vec3
{
	float x;
	float y;
	float z;

	friend Vec3 operator*(const Mtx33& mat, const Vec3& vec);
};