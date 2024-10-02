/******************************************************************************/
/*!
\par        Project: Amu Engine
\file       AMVec2.h

\author     Shinwoo Choi
\date       Oct 30, 2024

\brief      Header file for the library settings.
*/
/******************************************************************************/

#ifndef VEC2_H
#define VEC2_H

#include "AMExport.h"
#include "AMType.h"

// ---------------------------------------------------------------------------

//API typedef struct Vec2
typedef struct Vec2
{
    float x; ///< x component of a 2D vector
    float y; ///< y component of a 2D vector
}Vec2;

// ---------------------------------------------------------------------------
#ifdef __cplusplus 
extern "C"
{
#endif

    /******************************************************************************/
    /*!
    \fn         void Vec2Zero(Vec2* pResult)

    \brief      Set pResult to zero.

    \param      [out] pResult
                Pointer to Vec2 to be set.

    */
    /******************************************************************************/
    API void	Vec2Zero(Vec2* pResult);

    /******************************************************************************/
    /*!
    \fn         void Vec2Set(Vec2* pResult,
                               float x,
                               float y)

    \brief      Set pResult to (x, y).

    \param      [out] pResult
                Pointer to Vec2 to be set.

    \param      [in] x
                X value to set with.

    \param      [in] y
                Y value to set with.

    */
    /******************************************************************************/
    API void	Vec2Set(Vec2* pResult, float x, float y);

    /******************************************************************************/
    /*!
    \fn         void Vec2Neg(Vec2* pResult,
                               Vec2* pVec0)

    \brief      Set pResult to the negative of pVec0.

    \param      [out] pResult
                Pointer to Vec2 to be set.

    \param      [in] pVec0
                Pointer to Vec2 for input.

    */
    /******************************************************************************/
    API void	Vec2Neg(Vec2* pResult, Vec2* pVec0);

    /******************************************************************************/
    /*!
    \fn         void Vec2Add(Vec2* pResult,
                               Vec2* pVec0,
                               Vec2* pVec1)

    \brief      Set pResult to (pVec0 + pVec1).

    \param      [out] pResult
                Pointer to Vec2 to be set.

    \param      [in] pVec0
                Pointer to Vec2 for input.

    \param      [in] pVec1
                Pointer to Vec2 for input.

    */
    /******************************************************************************/
    API void	Vec2Add(Vec2* pResult, Vec2* pVec0, Vec2* pVec1);

    /******************************************************************************/
    /*!
    \fn         void Vec2Sub(Vec2* pResult,
                               Vec2* pVec0,
                               Vec2* pVec1)

    \brief      Set pResult to (pVec0 - pVec1).

    \param      [out] pResult
                Pointer to Vec2 to be set.

    \param      [in] pVec0
                Pointer to Vec2 for input.

    \param      [in] pVec1
                Pointer to Vec2 for input.

    */
    /******************************************************************************/
    API void	Vec2Sub(Vec2* pResult, Vec2* pVec0, Vec2* pVec1);

    /******************************************************************************/
    /*!
    \fn         void Vec2Normalize(Vec2* pResult,
                                     Vec2* pVec0)

    \brief      Set pResult to the normalized of pVec0.

    \param      [out] pResult
                Pointer to Vec2 to be set.

    \param      [in] pVec0
                Pointer to Vec2 for input.

    */
    /******************************************************************************/
    API void	Vec2Normalize(Vec2* pResult, Vec2* pVec0);

    /******************************************************************************/
    /*!
    \fn         void Vec2Scale(Vec2* pResult,
                                 Vec2* pVec0,
                                 float s)

    \brief      Set pResult to (pVec0 * s).

    \param      [out] pResult
                Pointer to Vec2 to be set.

    \param      [in] pVec0
                Pointer to Vec2 for input.

    \param      [in] s
                Value to scale with.

    */
    /******************************************************************************/
    API void	Vec2Scale(Vec2* pResult, Vec2* pVec0, float s);

    /******************************************************************************/
    /*!
    \fn         void Vec2ScaleAdd(Vec2* pResult,
                                    Vec2* pVec0,
                                    Vec2* pVec1,
                                    float s)

    \brief      Set pResult to ((pVec0 + pVec1) * s).

    \warning    Purpose unclear or error in implementation.

    \param      [out] pResult
                Pointer to Vec2 to be set.

    \param      [in] pVec0
                Pointer to Vec2 for input.

    \param      [in] pVec1
                Pointer to Vec2 for input.

    \param      [in] s
                Value to scale with.

    */
    /******************************************************************************/
    API void	Vec2ScaleAdd(Vec2* pResult, Vec2* pVec0, Vec2* pVec1, float s);

    /******************************************************************************/
    /*!
    \fn         void Vec2ScaleSub(Vec2* pResult,
                                    Vec2* pVec0,
                                    Vec2* pVec1,
                                    float s)

    \brief      Set pResult to ((pVec0 - pVec1) * s).

    \warning    Purpose unclear or error in implementation.

    \param      [out] pResult
                Pointer to Vec2 to be set.

    \param      [in] pVec0
                Pointer to Vec2 for input.

    \param      [in] pVec1
                Pointer to Vec2 for input.

    \param      [in] s
                Value to scale with.

    */
    /******************************************************************************/
    API void	Vec2ScaleSub(Vec2* pResult, Vec2* pVec0, Vec2* pVec1, float s);

    /******************************************************************************/
    /*!
    \fn         void Vec2Project(Vec2* pResult,
                                   Vec2* pVec0,
                                   Vec2* pVec1)

    \brief      Set pResult to the projection of pVec0 onto pVec1.

    \param      [out] pResult
                Pointer to Vec2 to be set.

    \param      [in] pVec0
                Pointer to Vec2 for input.

    \param      [in] pVec1
                Pointer to Vec2 for input.

    */
    /******************************************************************************/
    API void	Vec2Project(Vec2* pResult, Vec2* pVec0, Vec2* pVec1);

    /******************************************************************************/
    /*!
    \fn         void Vec2ProjectPerp(Vec2* pResult,
                                       Vec2* pVec0,
                                       Vec2* pVec1)

    \brief      Set pResult to the perpendicular projection (rejection)
                of pVec0 onto pVec1.

    \param      [out] pResult
                Pointer to Vec2 to be set.

    \param      [in] pVec0
                Pointer to Vec2 for input.

    \param      [in] pVec1
                Pointer to Vec2 for input.

    */
    /******************************************************************************/
    API void	Vec2ProjectPerp(Vec2* pResult, Vec2* pVec0, Vec2* pVec1);

    /******************************************************************************/
    /*!
    \fn         void Vec2Lerp(Vec2* pResult,
                                Vec2* pVec0,
                                Vec2* pVec1,
                                float t)

    \brief      Set pResult to the linear interpolation between pVec0 and
                pVec1 at time interval t.

    \warning    t should be between 0.0f to 1.0f.

    \param      [out] pResult
                Pointer to Vec2 to be set.

    \param      [in] pVec0
                Pointer to Vec2 for input.

    \param      [in] pVec1
                Pointer to Vec2 for input.

    \param      [in] t
                The time interval to calculate the linear interpolation at.
                At t = 0.0f, the result will be pVec0.
                At t = 1.0f, the result will be pVec1.

    */
    /******************************************************************************/
    API void	Vec2Lerp(Vec2* pResult, Vec2* pVec0, Vec2* pVec1, float t);

    /******************************************************************************/
    /*!
    \fn         float Vec2Length(Vec2* pVec0)

    \brief      Calculate the length of pVec0.

    \param      [in] pVec0
                Pointer to Vec2 for input

    \retval     float
                Returns the length of pVec0.
    */
    /******************************************************************************/
    API float	Vec2Length(Vec2* pVec0);

    /******************************************************************************/
    /*!
    \fn         float Vec2SquareLength(Vec2* pVec0)

    \brief      Calculate the squared length of pVec0.

    \param      [in] pVec0
                Pointer to Vec2 for input

    \retval     float
                Returns the squared length of pVec0.
    */
    /******************************************************************************/
    API float	Vec2SquareLength(Vec2* pVec0);

    /******************************************************************************/
    /*!
    \fn         float	Vec2Distance(Vec2* pVec0,
                                   Vec2* pVec1)

    \brief      Calculate the distance between 2 points.

    \param      [in] pVec0
                Pointer to Vec2 of first point.

    \param      [in] pVec1
                Pointer to Vec2 of second point.

    \retval     float
                Returns the distance between pVec0 and pVec1.
    */
    /******************************************************************************/
    API float	Vec2Distance(Vec2* pVec0, Vec2* pVec1);

    /******************************************************************************/
    /*!
    \fn         float Vec2SquareDistance(Vec2* pVec0,
                                         Vec2* pVec1)

    \brief      Calculate the squared distance between 2 points.

    \param      [in] pVec0
                Pointer to Vec2 of first point.

    \param      [in] pVec1
                Pointer to Vec2 of second point.

    \retval     float
                Returns the squared distance between pVec0 and pVec1.
    */
    /******************************************************************************/
    API float	Vec2SquareDistance(Vec2* pVec0, Vec2* pVec1);

    /******************************************************************************/
    /*!
    \fn         float	Vec2DotProduct(Vec2* pVec0,
                                     Vec2* pVec1)

    \brief      Calculate the dot product of 2 vectors.

    \param      [in] pVec0
                Pointer to Vec2 of first vector.

    \param      [in] pVec1
                Pointer to Vec2 of second vector.

    \retval     float
                Returns the dot product of pVec0 and pVec1.
    */
    /******************************************************************************/
    API float	Vec2DotProduct(Vec2* pVec0, Vec2* pVec1);

    /******************************************************************************/
    /*!
    \fn         float	Vec2CrossProductMag(Vec2* pVec0,
                                          Vec2* pVec1)

    \brief      Calculate the magnitude of the cross product of 2 vectors.

    \param      [in] pVec0
                Pointer to Vec2 of first vector.

    \param      [in] pVec1
                Pointer to Vec2 of second vector.

    \retval     float
                Returns the magnitude of the cross product of pVec0
                and pVec1.
    */
    /******************************************************************************/
    API float	Vec2CrossProductMag(Vec2* pVec0, Vec2* pVec1);

    /******************************************************************************/
    /*!
    \fn         void Vec2FromAngle(Vec2* pResult,
                                     float angle)

    \brief      Set pResult to unit vector of angle.

    \param      [out] pResult
                Pointer to Vec2 to be set.

    \param      [in] angle
                Angle of the unit vector.

    */
    /******************************************************************************/
    API void	Vec2FromAngle(Vec2* pResult, float angle);

#ifdef __cplusplus 
}
#endif

// ---------------------------------------------------------------------------

#endif // VEC2_H
