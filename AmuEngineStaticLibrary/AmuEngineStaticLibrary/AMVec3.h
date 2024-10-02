/******************************************************************************/
/*!
\par        Project: Amu Engine
\file       AMVec3.h

\author     Shinwoo Choi
\date       Oct 30, 2024

\brief      Header file for the library settings.
*/
/******************************************************************************/

#ifndef VEC3_H
#define VEC3_H

#include "AMMtx33.h"

// ---------------------------------------------------------------------------

//API typedef struct Vec3
struct Vec3
{
	float x;
	float y;
	float z;

	friend Vec3 operator*(const Mtx33& mat, const Vec3& vec);
};

// ---------------------------------------------------------------------------

#endif // VEC3_H
