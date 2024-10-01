/******************************************************************************/
/*!
\par        Project: Amu Engine
\file       Input.h

\author     Shinwoo Choi
\date       Oct 30, 2024

\brief      Header file for the library settings.
*/
/******************************************************************************/

#include <Export.h>

#ifndef INPUT_H
#define INPUT_H

// ---------------------------------------------------------------------------
// Defines/Enums

// These defines don't match the direct input defines and you should be using these
// defines instead of the ones in "dinput.h"
// For more key codes go to http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

#define VK_LBUTTON		 VK_LBUTTON	    //!< Left mouse button
#define VK_RBUTTON		 VK_RBUTTON	    //!< Right mouse button
#define VK_MBUTTON		 VK_MBUTTON	    //!< Middle mouse button

#define VK_BACK           VK_BACK         //!< Backspace
#define VK_TAB            VK_TAB      
#define VK_RETURN		    VK_RETURN		
#define VK_LSHIFT		    VK_LSHIFT		
#define VK_RSHIFT		    VK_RSHIFT		
#define VK_LCTRL		    VK_LCONTROL		
#define VK_RCTRL		    VK_RCONTROL		
#define VK_LALT		    VK_LMENU		
#define VK_RALT		    VK_RMENU		
#define VK_PRINTSCREEN    VK_SNAPSHOT
#define VK_SCROLLLOCK	    VK_SCROLL
#define VK_PAUSE		    VK_PAUSE		
#define VK_CAPSLOCK	    VK_CAPITAL

#define VK_ESCAPE         VK_ESCAPE   

#define VK_SPACE		    VK_SPACE		
#define VK_PAGEUP		    VK_PRIOR		
#define VK_PAGEDOWN	    VK_NEXT
#define VK_END		    VK_END		
#define VK_HOME		    VK_HOME		
#define VK_LEFT		    VK_LEFT		
#define VK_UP			    VK_UP			
#define VK_RIGHT		    VK_RIGHT		
#define VK_DOWN		    VK_DOWN		
#define VK_INSERT		    VK_INSERT		
#define VK_DELETE		    VK_DELETE		

#define VK_0              0x30        
#define VK_1              0x31        
#define VK_2              0x32        
#define VK_3              0x33        
#define VK_4              0x34        
#define VK_5              0x35        
#define VK_6              0x36        
#define VK_7              0x37        
#define VK_8              0x38        
#define VK_9              0x39        

#define VK_A              0x41        
#define VK_B              0x42        
#define VK_C              0x43        
#define VK_D              0x44        
#define VK_E              0x45        
#define VK_F              0x46        
#define VK_G              0x47        
#define VK_H              0x48        
#define VK_I              0x49        
#define VK_J              0x4A        
#define VK_K              0x4B        
#define VK_L              0x4C        
#define VK_M              0x4D        
#define VK_N              0x4E        
#define VK_O              0x4F        
#define VK_P              0x50        
#define VK_Q              0x51        
#define VK_R              0x52        
#define VK_S              0x53        
#define VK_T              0x54        
#define VK_U              0x55        
#define VK_V              0x56        
#define VK_W              0x57        
#define VK_X              0x58        
#define VK_Y              0x59        
#define VK_Z              0x5A        

#define VK_NUMPAD0	    VK_NUMPAD0	
#define VK_NUMPAD1	    VK_NUMPAD1	
#define VK_NUMPAD2	    VK_NUMPAD2	
#define VK_NUMPAD3	    VK_NUMPAD3	
#define VK_NUMPAD4	    VK_NUMPAD4	
#define VK_NUMPAD5	    VK_NUMPAD5	
#define VK_NUMPAD6	    VK_NUMPAD6	
#define VK_NUMPAD7	    VK_NUMPAD7	
#define VK_NUMPAD8	    VK_NUMPAD8	
#define VK_NUMPAD9	    VK_NUMPAD9	

#define VK_NUM_MULTIPLY   VK_MULTIPLY
#define VK_NUM_PLUS	    VK_ADD
#define VK_NUM_MINUS	    VK_SUBTRACT
#define VK_NUM_PERIOD	    VK_DECIMAL
#define VK_NUM_DIVIDE	    VK_DIVIDE
#define VK_NUMLOCK	    VK_NUMLOCK	

#define VK_F1			    VK_F1			
#define VK_F2			    VK_F2			
#define VK_F3			    VK_F3			
#define VK_F4			    VK_F4			
#define VK_F5			    VK_F5			
#define VK_F6			    VK_F6			
#define VK_F7			    VK_F7			
#define VK_F8			    VK_F8			
#define VK_F9			    VK_F9			
#define VK_F10		    VK_F10		
#define VK_F11		    VK_F11		
#define VK_F12		    VK_F12		

#define VK_SEMICOLON	    VK_OEM_1        //!< ; :
#define VK_SLASH		    VK_OEM_2		//!< / ?
#define VK_BACKQUOTE		VK_OEM_3        //!< ` ~
#define VK_LBRACKET	    VK_OEM_4        //!< [ {
#define VK_BACKSLASH	    VK_OEM_5        //!< \ |
#define VK_RBRACKET	    VK_OEM_6        //!< ] }
#define VK_QUOTE		    VK_OEM_7	    //!< ' "

#define VK_EQUAL		    VK_OEM_PLUS     //!< = +		
#define VK_MINUS		    VK_OEM_MINUS    //!< - _		
#define VK_PERIOD		    VK_OEM_PERIOD   //!< . >		
#define VK_COMMA		    VK_OEM_COMMA    //!< , <		

// ---------------------------------------------------------------------------
// Function prototypes

#ifdef __cplusplus

extern "C"
{
#endif

    // ---------------------------------------------------------------------------

    /******************************************************************************/
    /*!
    \fn		    int InputInit()

    \brief      Initialize Input.

    \warning    This function is already called in SysInit.

    \retval     int
                Return 1 if initialization is successful.
                Else return 0.
    */
    /******************************************************************************/
    API int  InputInit();

    /******************************************************************************/
    /*!
    \fn         void InputReset()

    \brief      Reset Input.

    \warning    This function is already called in SysReset.

    */
    /******************************************************************************/
    API void InputReset();

    /******************************************************************************/
    /*!
    \fn         void InputUpdate()

    \brief      Update Input.

    \warning    Already called in SysFrameStart, so users shouldn't need to call this.

    */
    /******************************************************************************/
    API void InputUpdate();

    /******************************************************************************/
    /*!
    \fn         void InputExit()

    \brief      Free Input.

    \warning    This function is already called in SysExit.

    */
    /******************************************************************************/
    API void InputExit();

    /******************************************************************************/
    /*!
    \fn         unsigned char InputCheckCurr(unsigned char key)

    \brief      Check if a keyboard button is being pressed.

    \details    Check if keyboard button given by key is currently
                being pressed.

    \param      [in] key
                Value corresponding to the keyboard button that is being
                checked for.

    \retval     unsigned char
                Returns 1 if keyboard button is being pressed.
                Else return 0.
    */
    /******************************************************************************/
    API unsigned char InputCheckCurr(unsigned char key);

    /******************************************************************************/
    /*!
    \fn         unsigned char InputCheckPrev(unsigned char key)

    \brief      Check if a keyboard button was pressed recently.

    \details    Check if keyboard button given by key was pressed in
                the previous update.

    \param      [in] key
                Value corresponding to the keyboard button that is being
                checked for.

    \retval     unsigned char
                Returns 1 if keyboard button was pressed.
                Else return 0.
    */
    /******************************************************************************/
    API unsigned char InputCheckPrev(unsigned char key);

    /******************************************************************************/
    /*!
    \fn         unsigned char InputCheckTriggered(unsigned char key)

    \brief      Check if a keyboard button was triggered.

    \details    Check if the keyboard button given by key was recently
                triggerd (pressed and then quickly released).

    \param      [in] key
                Value corresponding to the keyboard button that is being
                checked for.

    \retval     unsigned char
                Return 1 if keyboard button was pressed.
                Else return 0.
    */
    /******************************************************************************/
    API unsigned char InputCheckTriggered(unsigned char key);

    /******************************************************************************/
    /*!
    \fn         unsigned char InputCheckReleased(unsigned char key)

    \brief      Check if a keyboard button was released.

    \details    Check if the keyboard button given by key was recently
                released.

    \param      [in] key
                Value corresponding to the keyboard button that is being
                checked for.

    \retval     unsigned char
                Return 1 if keyboard button was pressed.
                Else return 0.
    */
    /******************************************************************************/
    API unsigned char InputCheckReleased(unsigned char key);

    /******************************************************************************/
    /*!
    \fn         void InputGetCursorPosition(int *pX,
                                              int *pY)

    \brief      Get the current position of the cursor,
                in screen coordinates.

    \param      [out] pX
                Pointer to int where the X value will be stored.

    \param      [out] pY
                Pointer to int where the Y value will be stored.

    */
    /******************************************************************************/
    API void InputGetCursorPosition(int* pX, int* pY);

    /******************************************************************************/
    /*!
    \fn         void InputGetCursorPositionDelta(int *pDeltaX,
                                                   int *pDeltaY)

    \brief      Get the change in position of the cursor since the last
                update, in screen coordinates.

    \param      [out] pDeltaX
                Pointer to int where the X value will be stored.

    \param      [out] pDeltaY
                Pointer to int where the Y value will be stored.

    */
    /******************************************************************************/
    API void InputGetCursorPositionDelta(int* pDeltaX, int* pDeltaY);

    /******************************************************************************/
    /*!
    \fn         void InputShowCursor(int show)

    \brief      Set if mouse cursor is showned.

    \details    Setting true will allow mouse cursor to be rendered
                on screen. Setting false will hide the mouse cursor.

    \param      [in] show
                If set to a non-zero value, it will show the mouse cursor.
                Otherwise, it will show the mouse cursor.

    */
    /******************************************************************************/
    API void InputShowCursor(int show);

    // ---------------------------------------------------------------------------

#ifdef __cplusplus 
}
#endif

// ---------------------------------------------------------------------------

#endif // INPUT_H

