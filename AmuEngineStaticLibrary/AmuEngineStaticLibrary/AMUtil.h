/******************************************************************************/
/*!
\par        Project: Amu Engine
\file       AMUtil.h

\author     Shinwoo Choi
\date       Oct 30, 2024

\brief      Header file for the utility library.
*/
/******************************************************************************/
#ifndef UTIL_H
#define UTIL_H

// ---------------------------------------------------------------------------
#ifdef __cplusplus 
extern "C"
{
#endif

    /******************************************************************************/
    /*!
    \fn         double GetTime(double* pTime)

    \brief      Get the current time in seconds.

    \param      [out] pTime
                Pointer to double to store the current time.
                May be left null if not needed.

    \retval     double
                Returns the current time in seconds.
    */
    /******************************************************************************/
    API double		GetTime(double* pTime);

    /******************************************************************************/
    /*!
    \fn         float RandFloat()

    \brief      Get a random real number between 0.0f to 1.0f.

    \retval     float
                Returns a random real number between 0.0f to 1.0f.
    */
    /******************************************************************************/
    API float		RandFloat();


    /******************************************************************************/
    /*!
    \fn         int IsfloatZero(float x)

    \brief      Checks if x is either 0 or so close to 0 that it can be considered 0.

    \param      [in] x
                float value to check.

    \retval     int
                Returns 1 if x is or close to 0.
                Otherwise, it will return 0.
    */
    /******************************************************************************/
    API int       IsfloatZero(float x);

    /******************************************************************************/
    /*!
    \fn         int IsfloatEqual(float a, float b)

    \brief      Checks whether a is equal to OR so close to b that they can
                be considered equal.

    \param      [in] a
                float value to check

    \param      [in] b
                float value to check

    \retval     int
                Returns 1 if a is or close to b.
                Otherwise, it will return 0.
    */
    /******************************************************************************/
    API int       IsfloatEqual(float a, float b);

    /******************************************************************************/
    /*!
    \fn         int IsdoubleNearZero(double x)

    \brief      Checks if x is either 0 or so close to 0 that it can be considered 0.

    \param      [in] x
                double value to check.

    \retval     int
                Returns 1 if x is or close to 0.
                Otherwise, it will return 0.
    */
    /******************************************************************************/
    API int       IsdoubleNearZero(double x);

    /******************************************************************************/
    /*!
    \fn         int IsdoubleEqual(double a, double b)

    \brief      Checks whether a is equal to OR so close to b that they can
                be considered equal.

    \param      [in] a
                double value to check

    \param      [in] b
                double value to check

    \retval     int
                Returns 1 if a is or close to b.
                Otherwise, it will return 0.
    */
    /******************************************************************************/
    API int       IsdoubleEqual(double a, double b);



#ifdef __cplusplus 
}
#endif


// ---------------------------------------------------------------------------

#endif // UTIL_H