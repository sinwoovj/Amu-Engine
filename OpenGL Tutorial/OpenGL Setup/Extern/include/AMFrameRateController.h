/******************************************************************************/
/*!
\par        Project: Amu Engine
\file       AMFrameRateController.h

\author     Shinwoo Choi
\date       Oct 30, 2024

\brief      Header file for the frame rate controller
*/
/******************************************************************************/

#ifndef FRAME_RATE_CONTROLLER_H
#define FRAME_RATE_CONTROLLER_H

// ---------------------------------------------------------------------------
// Externs

// ---------------------------------------------------------------------------
// Function prototypes
// ---------------------------------------------------------------------------

#include "AMExport.h"

#ifdef __cplusplus

extern "C"
{
#endif

    // ---------------------------------------------------------------------------

    // Frame management

    /******************************************************************************/
    /*!
    \fn         bool FrameRateControllerInit(unsigned int FrameRateMax)

    \brief      Initialize the frame rate controller.

    \warning    This function is already called in SysInit.

    \param      [in] FrameRateMax
                The maximum number of frames per second.

    */
    /******************************************************************************/
    API void	FrameRateControllerInit(unsigned int FrameRateMax);

    /******************************************************************************/
    /*!
    \fn         void FrameRateControllerReset()

    \brief      Reset the frame rate controller.

    \warning    This function is already called in SysReset.

    */
    /******************************************************************************/
    API void	FrameRateControllerReset();

    /******************************************************************************/
    /*!
    \fn         void FrameRateControllerStart()

    \brief      Tell the frame rate controller that a new frame
                is starting.

    \warning    This function is already called in SysFrameStart.

    */
    /******************************************************************************/
    API void	FrameRateControllerStart();

    /******************************************************************************/
    /*!
    \fn         void FrameRateControllerEnd()

    \brief      Tell the frame rate controller that the current frame
                is ending.

    \warning    This function is already called in SysFrameEnd.

    */
    /******************************************************************************/
    API void	FrameRateControllerEnd();

    /******************************************************************************/
    /*!
    \fn         double FrameRateControllerGetFrameTime()

    \brief      Get the time for the previous frame, in seconds.

    \retval     double
                Return the time for the previous frame, in seconds.
    */
    /******************************************************************************/
    API double FrameRateControllerGetFrameTime();

    /******************************************************************************/
    /*!
    \fn         unsigned int FrameRateControllerGetFrameCount()

    \brief      Get the total number of frames elapsed.

    \retval     unsigned int
                Return the total number of frames elapsed.
    */
    /******************************************************************************/
    API unsigned int FrameRateControllerGetFrameCount();


    /******************************************************************************/
    /*!
    \fn         unsigned int FrameRateControllerGetFrameRate()

    \brief      Get the current fps.

    \retval     double
                Return the total number of frames elapsed.
    */
    /******************************************************************************/
    API double FrameRateControllerGetFrameRate();

    // ---------------------------------------------------------------------------

#ifdef __cplusplus 
}
#endif

// ---------------------------------------------------------------------------

#endif // FRAME_RATE_CONTROLLER_H

