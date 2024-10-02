/******************************************************************************/
/*!
\par        Project: Amu Engine
\file       AMExport.h

\author     Shinwoo Choi
\date       Oct 30, 2024

\brief      Header file for the library settings.
*/
/******************************************************************************/

#ifndef EXPORT_H
#define EXPORT_H

#ifndef EPSILON
#define	EPSILON	0.00001f
#endif

#ifndef PI
#define	PI		3.1415926f
#endif

#define	HALF_PI	(PI * 0.5f)
#define	TWO_PI	(PI * 2.0f)


#ifdef FINAL
#define PRINT(...)
#else
#define PRINT(...)	printf(__VA_ARGS__)
#endif

#ifdef FINAL
#define PRINT_INFO(...)
#else
#define PRINT_INFO(...)	PRINT("File: %s\nLine: %d\nFunc: %s\n\n",				\
										__FILE__,__LINE__, __FUNCTION__);	
#endif


//#ifdef EXPORTS
#define API __declspec(dllexport)
//#else
//	#define API __declspec(dllimport)
	//#define API
//#endif				

#endif		// File