/******************************************************************************/
/*!
\par        Project: Amu Engine
\file       AMEngine.h

\author     Shinwoo Choi
\date       Oct 30, 2024

\brief      Header file for the Amu Engine.

\details    The Amu Engine consist of the following header files:
				- AMEngine.h
				- AMType.h
				- AMMath.h
					- AMVec2.h
					- AMMtx33.h
					- AMLineSegment2.h
				- AMUtil.h
				- AMFrameRateController.h (pending)
				- AMSystem.h
				- AMGraphcs.h
				- AMInput.h
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

#include <AMExport.h>


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

#include <AMType.h>						//Typedefs
#include <AMMath.h>						//Maths libraray
#include <AMUtil.h>						//Utility library
//#include "FrameRateController.h"      //Frame controller
#include <AMSystem.h>						//System library
#include <AMGraphics.h>					//Graphics library
#include <AMInput.h>						//Input library
#include <AMAudio.h>						//Audio library

// ---------------------------------------------------------------------------

#endif // ENGINE_H

