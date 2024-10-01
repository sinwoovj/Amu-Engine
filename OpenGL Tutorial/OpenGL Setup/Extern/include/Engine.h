/******************************************************************************/
/*!
\par        Project: Amu Engine
\file       Engine.h

\author     Shinwoo Choi
\date       Oct 30, 2024

\brief      Header file for the Amu Engine.

\details    The Amu Engine consist of the following header files:
				- Engine.h
				- Type.h
				- Math.h
					- Vec2.h
					- Mtx33.h
					- LineSegment2.h
				- Util.h
				- FrameRateController.h (pending)
				- System.h
				- Graphcs.h
				- Input.h
*/
/******************************************************************************/

#ifndef ENGINE_H
#define ENGINE_H

// ---------------------------------------------------------------------------
// Includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <windows.h>

#include <Export.h>


// ---------------------------------------------------------------------------
// assert defines

#ifndef FINAL    //User should define FINAL to remove asserts

// ---------------------------------------------------------------------------

#define ASSERT(x)															\
{																			\
	if((x) == 0)															\
	{																		\
		PRINT("ASSERT: %s\nLine: %d\nFunc: %s\nFile: %s\n",					\
			#x, __LINE__, __FUNCTION__, __FILE__); 							\
		MessageBox(NULL, "Program Must Exit!", "Program Error", MB_OK);		\
		exit(1);															\
	}																		\
}

// ---------------------------------------------------------------------------

#define ASSERT_MESG(x, ...)													\
{																			\
	if((x) == 0)															\
	{																		\
		PRINT("ASSERT_MESG: %s\nLine: %d\nFunc: %s\nFile: %s\n",			\
			#x, __LINE__, __FUNCTION__, __FILE__);							\
		PRINT("Mesg: ");													\
		PRINT(__VA_ARGS__);													\
		PRINT("\n");														\
		MessageBox(NULL, "Program Must Exit!", "Program Error", MB_OK);		\
		exit(1);															\
	}																		\
}

// ---------------------------------------------------------------------------

#define ASSERT_PARM(x)														\
{																			\
	if((x) == 0)															\
	{																		\
		PRINT("ASSERT_PARM: %s\nLine: %d\nFunc: %s\nFile: %s\n",			\
			#x, __LINE__, __FUNCTION__, __FILE__);							\
		MessageBox(NULL, "Program Must Exit!", "Program Error", MB_OK);		\
		exit(1);															\
	}																		\
}

// ---------------------------------------------------------------------------

#define ASSERT_ALLOC(x)														\
{																			\
	if((x) == 0)															\
	{																		\
		PRINT("ASSERT_ALLOC: %s\nLine: %d\nFunc: %s\nFile: %s\n",			\
			#x, __LINE__, __FUNCTION__, __FILE__);							\
		MessageBox(NULL, "Program Must Exit!", "Program Error", MB_OK);		\
		exit(1);															\
	}																		\
}


// ---------------------------------------------------------------------------

#define WARNING(x)												\
{																\
	if((x) == 0)												\
	{															\
		PRINT("WARNING: %s\nLine: %d\nFunc: %s\nFile: %s\n",	\
			#x, __LINE__, __FUNCTION__, __FILE__); 				\
	}															\
}

// ---------------------------------------------------------------------------

#define WARNING_MESG(x, ...)											\
{																		\
	if((x) == 0)														\
	{																	\
		PRINT("WARNING_MESG: %s\nLine: %d\nFunc: %s\nFile: %s\n",		\
			#x, __LINE__, __FUNCTION__, __FILE__);						\
		PRINT("Mesg: ");												\
		PRINT(__VA_ARGS__);												\
		PRINT("\n");													\
	}																	\
}

// ---------------------------------------------------------------------------

#define WARNING_PARM(x)													\
{																		\
	if((x) == 0)														\
	{																	\
		PRINT("WARNING_PARM: %s\nLine: %d\nFunc: %s\nFile: %s\n",		\
			#x, __LINE__, __FUNCTION__, __FILE__);						\
	}																	\
}

// ---------------------------------------------------------------------------

#else // FINAL

// ---------------------------------------------------------------------------

#define ASSERT(x)
#define ASSERT_MESG(x, ...)
#define ASSERT_PARM(x)
#define ASSERT_ALLOC(x)

#define WARNING(x)
#define WARNING_MESG(x, ...)
#define WARNING_PARM(x)
#define WARNING_ALLOC(x)

// ---------------------------------------------------------------------------

#endif // FINAL

// ---------------------------------------------------------------------------

#define FATAL_ERROR(...)												\
{																		\
	PRINT("FATAL_ERROR: ");												\
	PRINT(__VA_ARGS__);													\
	MessageBox(NULL, "Program Must Exit!", "Program Error", MB_OK);		\
	exit(1);															\
}

// ---------------------------------------------------------------------------
// engine includes

#include <Type.h>						//Typedefs
#include <Math.h>						//Maths libraray
#include <Util.h>						//Utility library
//#include "FrameRateController.h"      //Frame controller
#include <System.h>						//System library
#include <Graphics.h>					//Graphics library
#include <Input.h>						//Input library
#include <Audio.h>						//Audio library

// ---------------------------------------------------------------------------

#endif // ENGINE_H

