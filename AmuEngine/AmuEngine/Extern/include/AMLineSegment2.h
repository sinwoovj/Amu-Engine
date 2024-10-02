/******************************************************************************/
/*!
\par        Project: Amu Engine
\file       AMLineSegment2.h

\author     Shinwoo Choi
\date       Oct 30, 2024

\brief      Header file for the library settings.
*/
/******************************************************************************/

#ifndef LS2_H
#define LS2_H

// ---------------------------------------------------------------------------

typedef struct LineSegment2
{
    Vec2 mP0;		//!< Point on the line
    Vec2 mP1;		//!< Point on the line
    Vec2 mN;		//!< Line's normal
    float mNdotP0;	//!< To avoid computing it every time it's needed
}LineSegment2;


// ---------------------------------------------------------------------------
#ifdef __cplusplus 
extern "C"
{
#endif

    /******************************************************************************/
    /*!
    \fn         int BuildLineSegment2(LineSegment2 *pLS,
                                        Vec2 *pPt0,
                                        Vec2 *pPt1)

    \brief      Initalize pLS using pPt0 and pPt1. Also computes the
                normal (unit vector) and the dot product of the normal
                with one of the points.

    \warning    The distance between pPt0 and pPt1 should be greater
                than EPSILON.

    \param      [out] pLS
                Pointer to LineSegment2 to be set.

    \param      [in] pPt0
                Pointer to Vec2 for input.

    \param      [in] pPt1
                Pointer to Vec2 for input.

    \retval     int
                Returns 1 if pLS is successfully intialized.
                Else returns 0.
    */
    /******************************************************************************/
    API int BuildLineSegment2(LineSegment2* pLS, Vec2* pPt0, Vec2* pPt1);

#ifdef __cplusplus 
}
#endif

// ---------------------------------------------------------------------------

#endif // VEC2_H