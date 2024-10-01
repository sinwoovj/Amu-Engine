/******************************************************************************/
/*!
\par        Project: Amu Engine
\file       System.h

\author     Shinwoo Choi
\date       Oct 30, 2024

\brief      Header file for the library settings.
*/
/******************************************************************************/

#ifndef SYSTEM_H
#define SYSTEM_H


// ---------------------------------------------------------------------------
#ifdef __cplusplus 
extern "C"
{
#endif

    /******************************************************************************/
    /*!
    \fn         int SysInit (HINSTANCE hAppInstance,
                               int show,
                               int WinWidth,
                               int WinHeight,
                               int CreateConsole,
                               unsigned int FrameRateMax,
                               LRESULT (*pWinCallBack)(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp))

    \brief      Initialize the Alpha Engine.

    \details    Call this function once at the start of the program
                to initialize the system.

    \param      [in] hAppInstance
                Handle to the current instance of the application.

    \param      [in] show
                Set how the the window is to be shown.

    \param      [in] WinWidth
                Set the width of the window.

    \param      [in] WinHeight
                Set the height of the window.

    \param      [in] CreateConsole
                Input 1 if a console window should be created.
                Else input 0.

    \param      [in] FrameRateMax
                Set the maximum frames per second.

    \param      [in] vsync
                enables/disables VSync

    \param      [in] pWinCallBack
                Pointer to a callback function.
                May be left null if not needed.

    */
    /******************************************************************************/
    API int  SysInit(HINSTANCE hAppInstance, int show, int WinWidth, int WinHeight, int CreateConsole, unsigned int FrameRateMax, bool vsync, LRESULT(CALLBACK* pWinCallBack)(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp));

    /******************************************************************************/
    /*!
    \fn         void SysReset()

    \brief      Reset the Alpha Engine.

    \details    Call this function when changing gamestates to reset
                the system.

    */
    /******************************************************************************/
    API void SysReset();

    // Already called in SysFrameEnd
    //API void SysUpdate				();

    /******************************************************************************/
    /*!
    \fn         void SysExit()

    \brief      Free the Alpha Engine.

    \details    Call this function once at the end of the program
                to free the system.

    */
    /******************************************************************************/
    API void SysExit();

    /******************************************************************************/
    /*!
    \fn         void SysFrameStart()

    \brief      Start of frame.

    \details    Call this function once at the start of the frame to
                inform the system a new frame is starting.

    */
    /******************************************************************************/
    API void SysFrameStart();

    /******************************************************************************/
    /*!
    \fn         void SysFrameEnd()

    \brief      End of frame.

    \details    Call this function once at the end of the frame to
                inform the system the current frame is ending.

    */
    /******************************************************************************/
    API void SysFrameEnd();

    /******************************************************************************/
    /*!
    \fn         void SysIsFullScreen()

    \brief      Returns whether we are in full screen mode.

    \retval     int
                Returns 1 if we are in full screen mode.
                Otherwise, it will return 0.

    */
    /******************************************************************************/
    API int SysIsFullScreen();

    /******************************************************************************/
    /*!
    \fn         void SysIsFocus()

    \brief      Returns whether the application window is currently the focused
                window of the operating system.

    \retval     int
                Returns 1 if we are being foscued.
                Otherwise, it will return 0.

    */
    /******************************************************************************/
    API int SysIsFocus();

    /******************************************************************************/
    /*!
    \fn         void SysSetFullScreen()

    \brief      Toggles fullscreen.

    \param      [in] fullScreen
                If 0, sets the window to windowed mode.
                Otherwise, sets the window to full screen mode.
    */
    /******************************************************************************/
    API void SysSetFullScreen(int fullScreen);


    /******************************************************************************/
    /*!
    \fn         HWND SysGetWindowHandle()

    \brief      Get the handle to the window.

    \retval     HWND
                Returns the handle to the window.
    */
    /******************************************************************************/
    API HWND SysGetWindowHandle();


    /******************************************************************************/
    /*!
    \fn         void SysSetWindowTitle (const s8 *pTitle)

    \brief      Set the title of the window.

    \param      [in] pTitle
                Pointer to a null-terminated string to set as the title
                of the window.

    */
    /******************************************************************************/
    API void SysSetWindowTitle(const char* pTitle);

    /******************************************************************************/
    /*!
    \fn         int SysDoesWindowExist()

    \brief      Check if the window has been closed.

    \retval     int
                Return 1 if the window exist.
                Else return 0.
    */
    /******************************************************************************/
    API int SysDoesWindowExist();

    // ---------------------------------------------------------------------------



    // ---------------------------------------------------------------------------


#ifdef __cplusplus 
}
#endif

#endif // SYSTEM_H

