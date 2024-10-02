#include "AMVec3.h"

Vec3 operator*(const Mtx33& mat, const Vec3& vec)
{
	Vec3 ret;
	ret.x = mat.m[0][0] * vec.x + mat.m[0][1] * vec.y + mat.m[0][2] * vec.z;
	ret.y = mat.m[1][0] * vec.x + mat.m[1][1] * vec.y + mat.m[1][2] * vec.z;
	ret.z = mat.m[2][0] * vec.x + mat.m[2][1] * vec.y + mat.m[2][2] * vec.z;
	return ret;
}
