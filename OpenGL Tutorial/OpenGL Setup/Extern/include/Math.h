/******************************************************************************/
/*!
\par        Project: Amu Engine
\file       Math.h

\author     Shinwoo Choi
\date       Oct 30, 2024

\brief      Header file for the library settings.
*/
/******************************************************************************/

#ifndef MATH_H
#define MATH_H

// ---------------------------------------------------------------------------

#include "Vec2.h"             //Vector 2D
#include "Mtx33.h"            //Matrix 3x3
#include "LineSegment2.h"     //LineSegment 2D

#include <Export.h>
#include <float.h>

#include "math.h"

// ---------------------------------------------------------------------------
#ifdef __cplusplus

extern "C"
{
#endif

    //API void MathInit();

    // ---------------------------------------------------------------------------

    /******************************************************************************/
    /*!
    \fn         float DegToRad(float x)

    \brief      Convert an angle from Degree to Radians.

    \param      [in] x
                The angle in Degree to be converted.

    \retval     float
                The angle in Radians after conversion.
    */
    /******************************************************************************/
    API float DegToRad(float x);

    /******************************************************************************/
    /*!
    \fn         float RadToDeg(float x)

    \brief      Convert an angle from Radians to Degree.

    \param      [in] x
                The angle in Radians to be converted.

    \retval     float
                The angle in Degree after conversion.
    */
    /******************************************************************************/
    API float RadToDeg(float x);

    /******************************************************************************/
    /*!
    \fn         float Sin(float x)

    \brief      Calculate the Sine value of an angle.

    \param      [in] x
                The angle in Radians.

    \retval     float
                The value of sin(x).
    */
    /******************************************************************************/
    API float Sin(float x);

    /******************************************************************************/
    /*!
    \fn         float Cos(float x)

    \brief      Calculate the Cosine value of an angle.

    \param      [in] x
                The angle in Radians.

    \retval     float
                The value of cos(x).
    */
    /******************************************************************************/
    API float Cos(float x);

    /******************************************************************************/
    /*!
    \fn         float Tan(float x)

    \brief      Calculate the Tangent value of an angle.

    \param      [in] x
                The angle in Radians.

    \retval     float
                The value of tan(x).
    */
    /******************************************************************************/
    API float Tan(float x);

    /******************************************************************************/
    /*!
    \fn         float ASin(float x)

    \brief      Calculate the ArcSine value of an angle.

    \param      [in] x
                The angle in Radians.

    \retval     float
                The value of asin(x).
    */
    /******************************************************************************/
    API float ASin(float x);

    /******************************************************************************/
    /*!
    \fn         float ACos(float x)

    \brief      Calculate the ArcCosine value of an angle.

    \param      [in] x
                The angle in Radians.

    \retval     float
                The value of acos(x).
    */
    /******************************************************************************/
    API float ACos(float x);

    /******************************************************************************/
    /*!
    \fn         float ATan(float x)

    \brief      Calculate the ArcTangent value of an angle.

    \param      [in] x
                The angle in Radians.

    \retval     float
                The value of atan(x).
    */
    /******************************************************************************/
    API float ATan(float x);

    // ---------------------------------------------------------------------------

    //@{ 
    //! Macros for the trigo functions that take input in degree
#define SinDeg(x)	Sin(DegToRad(x))
#define CosDeg(x)	Cos(DegToRad(x))
#define TanDeg(x)	Tan(DegToRad(x))
#define ASinDeg(x)	RadToDeg(ASin(x))
#define ACosDeg(x)	RadToDeg(ACos(x))
#define ATanDeg(x)	RadToDeg(ATan(x))
//@}

// ---------------------------------------------------------------------------

/******************************************************************************/
/*!
\fn         unsigned int IsPowOf2(unsigned int x)

\brief      Check if x is a power of 2.

\details    Powers of 2 are values which can be presented as 2 ^ N,
            where N is any non-negative integer.
            Examples of powers of 2 are:
                - 1     (2 ^ 0)
                - 2     (2 ^ 1)
                - 4     (2 ^ 2)
                - 256   (2 ^ 8)
                - 1024  (2 ^ 10)

\param      [in] x
            The value to be checked.

\retval     unsigned int
            Returns true (non-zero value) if x is a power of 2.
            Else return false (zero).
*/
/******************************************************************************/
    API unsigned int		IsPowOf2(unsigned int x);

    /******************************************************************************/
    /*!
    \fn         unsigned int NextPowOf2(unsigned int x)

    \brief      Calculate the next power of 2 that is greater than x.

    \details    Powers of 2 are values which can be presented as 2 ^ N,
                where N is any non-negative integer.
                Examples of powers of 2 are:
                    - 1     (2 ^ 0)
                    - 2     (2 ^ 1)
                    - 4     (2 ^ 2)
                    - 256   (2 ^ 8)
                    - 1024  (2 ^ 10)

    \param      [in] x
                The input value.

    \retval     unsigned int
                Returns the next power of 2 greater than x.
    */
    /******************************************************************************/
    API unsigned int		NextPowOf2(unsigned int x);

    /******************************************************************************/
    /*!
    \fn         unsigned int LogBase2(unsigned int x)

    \brief      Calculate the log2 of x.

    \details    Calculate the log2 of x, rounded to the lower integer.

    \param      [in] x
                The input value.

    \retval     unsigned int
                The log2 of x, rounded to lower integer.
    */
    /******************************************************************************/
    API unsigned int		LogBase2(unsigned int x);

    /******************************************************************************/
    /*!
    \fn         float Clamp(float x, float x0, float x1)

    \brief      Clamp x to between x0 and x1.

    \details    If x is lower than the minimum value (x0), return x0.
                If x is higher than the maximum value (x1), return x1.
                Else return x.

    \param      [in] x
                The input value.

    \param      [in] x0
                The minimum value.

    \param      [in] x1
                The maximum value.

    \retval     float
                The clamped value of x.
    */
    /******************************************************************************/
    API float		Clamp(float X, float Min, float Max);

    /******************************************************************************/
    /*!
    \fn         float	Wrap(float x, float x0, float x1)

    \brief      Wraparound for x with respect to range (x0 to x1).

    \details    If x is lesser than x0, return (x + range).
                If x is higher than x1, return (x - range).

    \warning    Wraparound does not work if x is lesser than (x0 - range)
                or if x is greater than (x1 + range).

    \param      [in] x
                The input value.

    \param      [in] x0
                The lower bound of range

    \param      [in] x1
                The upper bound of range.

    \retval     float
                The wraparound value of x with respect to range.
    */
    /******************************************************************************/
    API float		Wrap(float x, float x0, float x1);

    /******************************************************************************/
    /*!
    \fn         float	Min(float x, float y)

    \brief      Find which of the 2 value is lower.

    \details    If x is lower than y, return x.
                If y is lower than x, return y.

    \param      [in] x
                The first input value.

    \param      [in] y
                The second input value.

    \retval     float
                The lower of the 2 value.
    */
    /******************************************************************************/
    API float		Min(float x, float y);


    /******************************************************************************/
    /*!
    \fn         float	Max(float x, float y)

    \brief      Find which of the 2 value is higher.

    \details    If x is higher than y, return x.
                If y is higher than x, return y.

    \param      [in] x
                The first input value.

    \param      [in] y
                The second input value.

    \retval     float
                The higher of the 2 value.
    */
    /******************************************************************************/
    API float		Max(float x, float y);

    /******************************************************************************/
    /*!
    \fn         int InRange(float x, float x0, float x1)

    \brief      Find if x is in the range (x0 to x1), inclusive.

    \details    If x is more than or equal to x0 OR
                If x is less than or equal to x1, return true.
                Else return false.

    \param      [in] x
                The input value.

    \param      [in] x0
                The lower bound of range.

    \param      [in] x1
                The upper bound of range.

    \retval     int
                Returns true if x is between x0 and x1, inclusive.
                Else return false.
    */
    /******************************************************************************/
    API int		InRange(float x, float x0, float x1);

    // ---------------------------------------------------------------------------

    /******************************************************************************/
    /*!
    \fn         float CalcDistPointToCircle	(Vec2* pPos,
                                             Vec2* pCtr,
                                             float radius)

    \brief      Calculate the shortest distance from a point to
                the edge of a circle.

    \details    Given a point (pPos) and the center of a circle (pCtr)
                of size (radius), calculate the shortest distance
                from the point to the circumference of the circle.

    \warning    Radius of circle should be a non-negative value.

    \param      [in] pPos
                Pointer to Vec2 containing the positon of the point.

    \param      [in] pCtr
                Pointer to Vec2 containing the position of
                the center of the circle

    \param      [in] radius
                The radius of the circle.

    \retval     float
                Returns the shortest distance from the point to the
                edge of the circle. This value will be negative if
                the point is inside the circle.
    */
    /******************************************************************************/
    API float CalcDistPointToCircle(Vec2* pPos, Vec2* pCtr, float radius);

    /******************************************************************************/
    /*!
    \fn         float CalcDistPointToRect(Vec2* pPos,
                                          Vec2* pRect,
                                          float sizeX,
                                          float sizeY)

    \brief      Calculate the shortest distance from a point to
                the edge of a rectangle.

    \details    Given a point (pPos) and the center of a rect (pRect)
                of width (sizeX) and height (sizeY), calculate the
                shortest distance from the point to the perimeter of
                the rect.

    \warning    The width and height of the rect should be
                non-negative values.

    \warning    Function will only work if the rect is not rotated,
                i.e. the sides of the rect are parallel to the axis.

    \param      [in] pPos
                Pointer to Vec2 containing the position of the point.

    \param      [in] pRect
                Pointer to Vec2 containing the position of
                the center of the rect.

    \param      [in] sizeX
                Width of the rect, i.e. the size of the rect
                along the x-axis.

    \param      [in] sizeY
                Height of the rect, i.e. the size of the rect
                along the y-axis.

    \retval     float
                Returns the shortest distance from the point to the
                edge of the rect. This value will be negative if the
                point is inside the rect.
    */
    /******************************************************************************/
    API float CalcDistPointToRect(Vec2* pPos, Vec2* pRect, float sizeX, float sizeY);

    /******************************************************************************/
    /*!
    \fn         float CalcDistPointToLineSeg(Vec2* pPos,
                                             Vec2* pLine0,
                                             Vec2* pLine1)

    \brief      Calculate the shortest distance from a point to
                a line segment.

    \details    Given a point (pPos) and start (pLine0) and end (pLine1)
                of a line segment, calculate the shortest distance from
                the point to the line segment.

    \param      [in] pPos
                Pointer to Vec2 containing the position of the point.

    \param      [in] pLine0
                Pointer to Vec2 containing the start of the
                line segment.

    \param      [in] pLine1
                Pointer to Vec2 containing the end of the
                line segment.

    \retval     float
                Returns the shortest distance from the point to the
                line segment.
    */
    /******************************************************************************/
    API float CalcDistPointToLineSeg(Vec2* pPos, Vec2* pLine0, Vec2* pLine1);

    /******************************************************************************/
    /*!
    \fn         float CalcDistPointToConvexPoly(Vec2* pPos,
                                                Vec2* pVtx,
                                                unsigned int vtxNum)

    \brief      Calculate the shortest distance from a point to the edge
                of a convex polygon.

    \details    Given a point (pPos) and an array of vertices (pVtx)
                of size (vtxNum) making up a convex polygon, calculate
                the shortest distance from the point to the edge of the
                polygon.

    \warning    Function not implemented. Do not use.
                Currently returns -1.0f.

    \param      [in] pPos
                Pointer to Vec2 containing the position of the point.

    \param      [in] pVtx
                Pointer to an array of Vec2 containing the vertices
                of the polygon.

    \param      [in] vtxNum
                The number of vertices in the polygon

    \retval     float
                Returns the shortest distance from the point to the
                edge of the polygon. This value will be negative if the
                point is inside the polygon.
    */
    /******************************************************************************/
    API float CalcDistPointToConvexPoly(Vec2* pPos, Vec2* pVtx, unsigned int vtxNum);

    /******************************************************************************/
    /*!
    \fn         float CalcDistCircleToCircle(Vec2* pCtr0,
                                             float radius0,
                                             Vec2* pCtr1,
                                             float radius1)

    \brief      Calculate the shortest distance between the edges of
                two circles.

    \details    Given the center of circle0 (pCtr0) of size (radius0)
                and the center of circle1 (pCtr1) of size (radius1),
                calculate the shortest distance between their edges.

    \warning    radius of circles should be a non-negative value.

    \param      [in] pCtr0
                Pointer to Vec2 containing the center of circle0.

    \param      [in] radius0
                The radius of circle0.

    \param      [in] pCtr1
                Pointer to Vec2 containing the center of circle1.

    \param      [in] radius1
                The radius of circle1.

    \retval     float
                Returns the shortest distance between the edge of both
                circles. This value will be negative if the circles
                are overlapping.
    */
    /******************************************************************************/
    API float CalcDistCircleToCircle(Vec2* pCtr0, float radius0, Vec2* pCtr1, float radius1);

    /******************************************************************************/
    /*!
    \fn         float CalcDistCircleToRect(Vec2* pCtr,
                                           float radius,
                                           Vec2* pRect,
                                           float sizeX,
                                           float sizeY)

    \brief      Calculate the shortest distance between the edges of
                a circle and a rectangle.

    \details    Given the center of a circle (pCtr) of size (radius)
                and the center of a rect (pRect) of width (sizeX) and
                height (sizeY), calculate the shortest distance between
                their edges.

    \warning    radius of circles should be a non-negative value.

    \warning    The width and height of the rect should be
                non-negative values.

    \warning    Function will only work if the rect is not rotated,
                i.e. the sides of the rect are parallel to the axis.

    \param      [in] pCtr
                Pointer to Vec2 containing the center of the circle.

    \param      [in] radius
                The radius of circle.

    \param      [in] pRect
                Pointer to Vec2 containing the center of the rect.

    \param      [in] sizeX
                The width of the rect.

    \param      [in] sizeY
                The height of the rect.

    \retval     float
                Returns the shortest distance between the edges of the
                circle and the rect. This value will be negative if the
                circle and rect are overlapping.
    */
    /******************************************************************************/
    API float CalcDistCircleToRect(Vec2* pCtr, float radius, Vec2* pRect, float sizeX, float sizeY);

    /******************************************************************************/
    /*!
    \fn         float CalcDistRectToRect(Vec2* pRect0,
                                         float sizeX0,
                                         float sizeY0,
                                         Vec2* pRect1,
                                         float sizeX1,
                                         float sizeY1,
                                         Vec2* pNormal)

    \brief      Calculate the shortest distance between the edges of
                two rectangles.

    \details    Given the center of rect0 (pRect0) of width (sizeX0) and
                height (sizeY0) and the center of rect1 (pRect1) of
                width (sizeX1) and height (sizeY1), calculate the
                shortest distance between their edges.

    \warning    The width and height of the rect should be
                non-negative values.

    \warning    Function will only work if the rect is not rotated,
                i.e. the sides of the rect are parallel to the axis.

    \param      [in] pRect0
                Pointer to Vec2 containing the center of rect0.

    \param      [in] sizeX0
                The width of rect0.

    \param      [in] sizeY0
                The height of rect0.

    \param      [in] pRect1
                Pointer to Vec2 containing the center of rect1.

    \param      [in] sizeX1
                The width of rect1.

    \param      [in] sizeY1
                The height of rect1.

    \param      [out] pNormal
                Pointer to Vec2 where the direction from rect1 to rect0
                is stored. May be left null if not needed.

    \retval     float
                Returns the shortest distance between the edges of both
                rects. This value will be negative if they are
                overlapping.
    */
    /******************************************************************************/
    API float CalcDistRectToRect(Vec2* pRect0, float sizeX0, float sizeY0, Vec2* pRect1, float sizeX1, float sizeY1, Vec2* pNormal);

    /* Functions not defined
    API float CalcDistCircleToLineSeg	(Vec2* pPos, Vec2* pLine0, Vec2* pLine1);
    API float CalcDistCircleToConvexPoly	(Vec2* pPos, Vec2* pVtx, unsigned int vtxNum);
    */

    // ---------------------------------------------------------------------------

    /******************************************************************************/
    /*!
    \fn         int TestPointToCircle(Vec2* pPos,
                                        Vec2* pCtr,
                                        float radius)

    \brief      Test if a point is inside a circle.

    \details    Given a point (pPos) and the center of a circle (pCtr)
                of size (radius), check if the point is in the
                circle.

    \warning    Radius of circle should be a non-negative value.

    \param      [in] pPos
                Pointer to Vec2 containing the position of the point.

    \param      [in] pCtr
                Pointer to Vec2 containing the center of the circle.

    \param      [in] radius
                The radius of circle0.

    \retval     int
                Returns true if the point is inside the circle.
                Else return false.
    */
    /******************************************************************************/
    API int TestPointToCircle(Vec2* pPos, Vec2* pCtr, float radius);

    /******************************************************************************/
    /*!
    \fn         int TestPointToRect(Vec2* pPos,
                                      Vec2* pRect,
                                      float sizeX,
                                      float sizeY)

    \brief      Test if a point is inside a rectangle.

    \details    Given a point (pPos) and the center of a rect (pRect)
                of width (sizeX) and height (sizeY), check if the
                point is in the rect.

    \warning    The width and height of the rect should be
                non-negative values.

    \warning    Function will only work if the rect is not rotated,
                i.e. the sides of the rect are parallel to the axis.

    \param      [in] pPos
                Pointer to Vec2 containing the position of the point.

    \param      [in] pRect
                Pointer to Vec2 containing the center of the rect.

    \param      [in] sizeX
                The width of the rect.

    \param      [in] sizeY
                The height of the rect.

    \retval     int
                Returns true if the point is inside the rect.
                Else return false.
    */
    /******************************************************************************/
    API int TestPointToRect(Vec2* pPos, Vec2* pRect, float sizeX, float sizeY);

    /******************************************************************************/
    /*!
    \fn         int TestCircleToCircle(Vec2* pCtr0,
                                         float radius0,
                                         Vec2* pCtr1,
                                         float radius1)

    \brief      Test for collision between two circles.

    \details    Given the center of circle0 (pCtr0) of size (radius0)
                and the center of circle1 (pCtr1) of size (radius1),
                check if they are colliding.

    \warning    Radius of circle should be a non-negative value.

    \param      [in] pCtr0
                Pointer to Vec2 containing the center of circle0.

    \param      [in] radius0
                The radius of circle0.

    \param      [in] pCtr1
                Pointer to Vec2 containing the center of circle1.

    \param      [in] radius1
                The radius of circle1.

    \retval     int
                Returns true if the circles are colliding.
                Else return false.
    */
    /******************************************************************************/
    API int TestCircleToCircle(Vec2* pCtr0, float radius0, Vec2* pCtr1, float radius1);

    /******************************************************************************/
    /*!
    \fn         int TestCircleToRect(Vec2* pCtr,
                                       float radius,
                                       Vec2* pRect,
                                       float sizeX,
                                       float sizeY);

    \brief      Test for collision between a circle and a rectangle.

    \details    Given the center of a circle (pCtr) of size (radius)
                and the center of a rect (pRect) of width (sizeX) and
                height (sizeY), check if they are colliding.

    \warning    radius of circles should be a non-negative value.

    \warning    The width and height of the rect should be
                non-negative values.

    \warning    Function will only work if the rect is not rotated,
                i.e. the sides of the rect are parallel to the axis.

    \param      [in] pCtr
                Pointer to Vec2 containing the center of the circle.

    \param      [in] radius
                The radius of circle.

    \param      [in] pRect
                Pointer to Vec2 containing the center of the rect.

    \param      [in] sizeX
                The width of the rect.

    \param      [in] sizeY
                The height of the rect.

    \retval     int
                Returns true if the circle and the rect are colliding.
                Else return false.
    */
    /******************************************************************************/
    API int TestCircleToRect(Vec2* pCtr, float radius, Vec2* pRect, float sizeX, float sizeY);

    /******************************************************************************/
    /*!
    \fn         int TestRectToRect(Vec2* pRect0,
                                     float sizeX0,
                                     float sizeY0,
                                     Vec2* pRect1,
                                     float sizeX1,
                                     float sizeY1)

    \brief      Test for collision between two rectangles.

    \details    Given the center of rect0 (pRect0) of width (sizeX0) and
                height (sizeY0) and the center of rect1 (pRect1) of
                width (sizeX1) and height (sizeY1), check if they are
                colliding.

    \warning    The width and height of the rect should be
                non-negative values.

    \warning    Function will only work if the rect is not rotated,
                i.e. the sides of the rect are parallel to the axis.

    \param      [in] pRect0
                Pointer to Vec2 containing the center of rect0.

    \param      [in] sizeX0
                The width of rect0.

    \param      [in] sizeY0
                The height of rect0.

    \param      [in] pRect1
                Pointer to Vec2 containing the center of rect1.

    \param      [in] sizeX1
                The width of rect1.

    \param      [in] sizeY1
                The height of rect1.

    \retval     int
                Returns true if the rects are colliding.
                Else return false.
    */
    /******************************************************************************/
    API int TestRectToRect(Vec2* pRect0, float sizeX0, float sizeY0, Vec2* pRect1, float sizeX1, float sizeY1);

    // ---------------------------------------------------------------------------

    /******************************************************************************/
    /*!
    \fn         float StaticPointToStaticLineSegment(Vec2 *pPos,
                                                     LineSegment2 *pLine)

    \brief      Calculate the shortest distance from a point to a line.

    \details    Given a point (pPos) and a line (pLine), calculate the
                shortest distance from the point to the line.

    \warning    Line is assumed to stretch to infinity.

    \param      [in] pPos
                Pointer to Vec2 containing the point.

    \param      [in] pLine
                Pointer to LineSegment2 containing the line.

    \retval     float
                Returns the distance from the point to the line.
                Negative if the point is in the line's inside half plane.
                Positive if the point is in the line's outside half plane.
                Otherwise zero if the point is on the line.
    */
    /******************************************************************************/
    API float StaticPointToStaticLineSegment(Vec2* pPos, LineSegment2* pLine);

    /******************************************************************************/
    /*!
    \fn         float AnimatedPointToStaticLineSegment(Vec2 *pStart,
                                                       Vec2 *pEnd,
                                                       LineSegment2 *pLine,
                                                       Vec2 *pInter)

    \brief      Calculate the collision between a moving point with
                a line.

    \details    Given the start position (pStart) and end position (pEnd)
                of a moving point and a line (pLine), calculate the time
                and point of intersection.

    \warning    Line is assumed to stretch to infinity.

    \param      [in] pStart
                Pointer to Vec2 containing start pos of the point.

    \param      [in] pEnd
                Pointer to Vec2 containing end pos of the point.

    \param      [in] pLine
                Pointer to LineSegment2 containing the line.

    \param      [out] pInter
                Pointer to Vec2 for storing the point of intersection.
                Will not be used if there is no collision.

    \retval     float
                Returns the time of collision, if there is one.
                Else return -1.0f.
    */
    /******************************************************************************/
    API float AnimatedPointToStaticLineSegment(Vec2* pStart, Vec2* pEnd, LineSegment2* pLine, Vec2* pInter);

    /******************************************************************************/
    /*!
    \fn         float AnimatedCircleToStaticLineSegment(Vec2 *pStart,
                                                        Vec2 *pEnd,
                                                        float radius,
                                                        LineSegment2 *pLine,
                                                        Vec2 *pInter)

    \brief      Calculate the collision between a moving circle with
                a line.

    \details    Given the start position (pStart) and end position (pEnd)
                of a moving circle of size (radius) and a line (pLine),
                calculate the time and point of intersection.

    \warning    Line is assumed to stretch to infinity.

    \warning    Radius of circle should be a non-negative value.

    \param      [in] pStart
                Pointer to Vec2 containing start pos of the circle.

    \param      [in] pEnd
                Pointer to Vec2 containing end pos of the circle.

    \param      [in] radius
                The radius of the circle.

    \param      [in] pLine
                Pointer to LineSegment2 containing the line.

    \param      [out] pInter
                Pointer to Vec2 for storing the point of intersection.
                Will not be used if there is no collision.

    \retval     float
                Returns the time of collision, if there is one.
                Else return -1.0f.
    */
    /******************************************************************************/
    API float AnimatedCircleToStaticLineSegment(Vec2* pStart, Vec2* pEnd, float radius, LineSegment2* pLine, Vec2* pInter);

    /******************************************************************************/
    /*!
    \fn         float ReflectAnimatedPointOnStaticLineSegment(Vec2 *pStart,
                                                              Vec2 *pEnd,
                                                              LineSegment2 *pLine,
                                                              Vec2 *pInter,
                                                              Vec2 *pReflect)

    \brief      Calculate the collision between a moving point with
                a line and the reflected path of the point.

    \details    Given the start position (pStart) and end position (pEnd)
                of a moving point and a line (pLine), calculate the time,
                point of intersection and reflected path.

    \warning    Line is assumed to stretch to infinity.

    \param      [in] pStart
                Pointer to Vec2 containing start pos of the point.

    \param      [in] pEnd
                Pointer to Vec2 containing end pos of the point.

    \param      [in] pLine
                Pointer to LineSegment2 containing the line.

    \param      [out] pInter
                Pointer to Vec2 for storing the point of intersection.
                Will not be used if there is no collision.

    \param      [out] pReflect
                Pointer to Vec2 for storing the reflected path.
                Will not be used if there is no collision.

    \retval     float
                Returns the time of collision, if there is one.
                Else return -1.0f.
    */
    /******************************************************************************/
    API float ReflectAnimatedPointOnStaticLineSegment(Vec2* pStart, Vec2* pEnd, LineSegment2* pLine, Vec2* pInter, Vec2* pReflect);

    /******************************************************************************/
    /*!
    \fn         float ReflectAnimatedCircleOnStaticLineSegment(Vec2 *pStart,
                                                               Vec2 *pEnd,
                                                               float radius,
                                                               LineSegment2 *pLine,
                                                               Vec2 *pInter,
                                                               Vec2 *pReflect)

    \brief      Calculate the collision between a moving circle with
                a line and the reflected path of the circle.

    \details    Given the start position (pStart) and end position (pEnd)
                of a moving circle of size (radius) and a line (pLine),
                calculate the time, point of intersection and reflected
                path.

    \warning    Line is assumed to stretch to infinity.

    \warning    Radius of circle should be a non-negative value.

    \param      [in] pStart
                Pointer to Vec2 containing start pos of the circle.

    \param      [in] pEnd
                Pointer to Vec2 containing end pos of the circle.

    \param      [in] radius
                The radius of the circle.

    \param      [in] pLine
                Pointer to LineSegment2 containing the line.

    \param      [out] pInter
                Pointer to Vec2 for storing the point of intersection.
                Will not be used if there is no collision.

    \param      [out] pReflect
                Pointer to Vec2 for storing the reflected path.
                Will not be used if there is no collision.

    \retval     float
                Returns the time of collision, if there is one.
                Else return -1.0f.
    */
    /******************************************************************************/
    API float ReflectAnimatedCircleOnStaticLineSegment(Vec2* pStart, Vec2* pEnd, float radius, LineSegment2* pLine, Vec2* pInter, Vec2* pReflect);

    /******************************************************************************/
    /*!
    \fn         float AnimatedPointToStaticCircle(Vec2 *pStart,
                                                  Vec2 *pEnd,
                                                  Vec2 *pCtr,
                                                  float radius,
                                                  Vec2 *pInter)

    \brief      Calculate the collision between a moving point with
                a circle.

    \details    Given the start position (pStart) and end position (pEnd)
                of a moving point and the center of a circle (pCtr) of
                size (radius), calculate the time and point of
                intersection.

    \warning    Radius of circle should be a non-negative value.

    \param      [in] pStart
                Pointer to Vec2 containing start pos of the point.

    \param      [in] pEnd
                Pointer to Vec2 containing end pos of the point.

    \param      [in] pCtr
                Pointer to Vec2 containing the center of the circle.

    \param      [in] radius
                The radius of the circle.

    \param      [out] pInter
                Pointer to Vec2 for storing the point of intersection.
                Will not be used if there is no collision.

    \retval     float
                Returns the time of collision, if there is one.
                Else return -1.0f.
    */
    /******************************************************************************/
    API float AnimatedPointToStaticCircle(Vec2* pStart, Vec2* pEnd, Vec2* pCtr, float radius, Vec2* pInter);

    /******************************************************************************/
    /*!
    \fn         float ReflectAnimatedPointOnStaticCircle(Vec2 *pStart,
                                                         Vec2 *pEnd,
                                                         Vec2 *pCtr,
                                                         float radius,
                                                         Vec2 *pInter,
                                                         Vec2 *pReflect)

    \brief      Calculate the collision between a moving point with
                a circle and the reflected path of the point.

    \details    Given the start position (pStart) and end position (pEnd)
                of a moving point and the center of a circle (pCtr) of
                size (radius), calculate the time, point of intersection
                and reflected path.

    \warning    Radius of circle should be a non-negative value.

    \param      [in] pStart
                Pointer to Vec2 containing start pos of the point.

    \param      [in] pEnd
                Pointer to Vec2 containing end pos of the point.

    \param      [in] pCtr
                Pointer to Vec2 containing the center of the circle.

    \param      [in] radius
                The radius of the circle.

    \param      [out] pInter
                Pointer to Vec2 for storing the point of intersection.
                Will not be used if there is no collision.

    \param      [out] pReflect
                Pointer to Vec2 for storing the reflected path.
                Will not be used if there is no collision.

    \retval     float
                Returns the time of collision, if there is one.
                Else return -1.0f.
    */
    /******************************************************************************/
    API float ReflectAnimatedPointOnStaticCircle(Vec2* pStart, Vec2* pEnd, Vec2* pCtr, float radius, Vec2* pInter, Vec2* pReflect);

    /******************************************************************************/
    /*!
    \fn         float AnimatedCircleToStaticCircle(Vec2 *pCtr0s,
                                                   Vec2 *pCtr0e,
                                                   float radius0,
                                                   Vec2 *pCtr1,
                                                   float radius1,
                                                   Vec2 *pInter)

    \brief      Calculate the collision between a moving circle with
                a static circle.

    \details    Given the start position (pCtr0s) and end position
                (pCtr0e) of moving circle0 of size (radius0) and the
                center of static circle1 (pCtr1) of size (radius1),
                calculate the time and point of intersection.

    \warning    Radius of circles should be a non-negative value.

    \param      [in] pCtr0s
                Pointer to Vec2 containing start pos of circle0.

    \param      [in] pCtr0e
                Pointer to Vec2 containing end pos of the circle0.

    \param      [in] radius0
                The radius of circle0.

    \param      [in] pCtr1
                Pointer to Vec2 containing the center of circle1.

    \param      [in] radius1
                The radius of the circle1.

    \param      [out] pInter
                Pointer to Vec2 for storing the point of intersection.
                Will not be used if there is no collision.

    \retval     float
                Returns the time of collision, if there is one.
                Else return -1.0f.
    */
    /******************************************************************************/
    API float AnimatedCircleToStaticCircle(Vec2* pCtr0s, Vec2* pCtr0e, float radius0, Vec2* pCtr1, float radius1, Vec2* pInter);

    /******************************************************************************/
    /*!
    \fn         float ReflectAnimatedCircleOnStaticCircle(Vec2 *pCtr0s,
                                                          Vec2 *pCtr0e,
                                                          float radius0,
                                                          Vec2 *pCtr1,
                                                          float radius1,
                                                          Vec2 *pInter,
                                                          Vec2 *pReflect)

    \brief      Calculate the collision between a moving circle with
                a static circle and the reflected path of moving circle.

    \details    Given the start position (pCtr0s) and end position
                (pCtr0e) of moving circle0 of size (radius0) and the
                center of static circle1 (pCtr1) of size (radius1),
                calculate the time, point of intersection and reflected
                path of circle0.

    \warning    Radius of circles should be a non-negative value.

    \param      [in] pCtr0s
                Pointer to Vec2 containing start pos of circle0.

    \param      [in] pCtr0e
                Pointer to Vec2 containing end pos of the circle0.

    \param      [in] radius0
                The radius of circle0.

    \param      [in] pCtr1
                Pointer to Vec2 containing the center of circle1.

    \param      [in] radius1
                The radius of the circle1.

    \param      [out] pInter
                Pointer to Vec2 for storing the point of intersection.
                Will not be used if there is no collision.

    \param      [out] pReflect
                Pointer to Vec2 for storing the reflected path.
                Will not be used if there is no collision.

    \retval     float
                Returns the time of collision, if there is one.
                Else return -1.0f.
    */
    /******************************************************************************/
    API float ReflectAnimatedCircleOnStaticCircle(Vec2* pCtr0s, Vec2* pCtr0e, float radius0, Vec2* pCtr1, float radius1, Vec2* pInter, Vec2* pReflect);



    /*
    // sweep a circle with radius 'radius' from ctr0 -> ctr1 againts a point
    // * return -ve if circle does not touch the point at any time
    API float SweepCircleToPoint	(Vec2* pCtr0, Vec2* pCtr1, float radius, Vec2* pP);

    // sweep a circle with radius 'radius' from ctr0 -> ctr1 againts a line segment
    // * return -ve if circle does not intersect the line segment at any time
    API float SweepCircleToLineSeg	(Vec2* pCtr0, Vec2* pCtr1, float radius, Vec2* pP0, Vec2* pP1, Vec2* pN);


    //TO TEST
    //Sweeps a moving point against a static line
    API float SweepPointToLine		(Vec2 *pPos, Vec2 *pVel, Vec2 *pPnt, Vec2 *pDirection);

    //TO TEST
    //Sweeps a moving circle against a static line
    API float SweepCircleToLine		(Vec2 *pCtr, float radius, Vec2 *pVel, Vec2 *pPnt, Vec2 *pDirection);

    //TO TEST
    //Reflects a moving point on a static line. Returns 0 if there is no
    //collision between the point and the line.
    API int ReflectPointOnLine	(Vec2 *pPos, Vec2 *pVel, Vec2 *pPnt, Vec2 *pDirection, Vec2 *pNewPosition, Vec2 *pNewVelocity);


    //TO TEST
    //Reflects a moving circle on a static line. Returns 0 if there is no
    //collision between the circle and the line.
    API int ReflectCircleOnLine	(Vec2 *pCtr, float radius, Vec2 *pVel, Vec2 *pPnt, Vec2 *pDirection, Vec2 *pNewPosition, Vec2 *newVelocity);
    */
    // ---------------------------------------------------------------------------

#ifdef __cplusplus 
}
#endif

// ---------------------------------------------------------------------------

#endif // MATH_H
