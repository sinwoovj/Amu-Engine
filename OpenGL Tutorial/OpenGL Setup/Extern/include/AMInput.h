/******************************************************************************/
/*!
\par        Project: Amu Engine
\file       AMInput.h

\author     Shinwoo Choi
\date       Oct 30, 2024

\brief      Header file for the library settings.
*/
/******************************************************************************/

#include <AMExport.h>

#ifndef INPUT_H
#define INPUT_H

// ---------------------------------------------------------------------------
// Defines/Enums

// These defines don't match the direct input defines and you should be using these
// defines instead of the ones in "dinput.h"
// For more key codes go to http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

#define AMVK_LBUTTON		VK_LBUTTON	    //!< Left mouse button
#define AMVK_RBUTTON		VK_RBUTTON	    //!< Right mouse button
#define AMVK_MBUTTON		VK_MBUTTON	    //!< Middle mouse button

#define AMVK_BACK           VK_BACK         //!< Backspace
#define AMVK_TAB            VK_TAB      
#define AMVK_RETURN		    VK_RETURN		
#define AMVK_LSHIFT		    VK_LSHIFT		
#define AMVK_RSHIFT		    VK_RSHIFT		
#define AMVK_LCTRL		    VK_LCONTROL		
#define AMVK_RCTRL		    VK_RCONTROL		
#define AMVK_LALT		    VK_LMENU		
#define AMVK_RALT		    VK_RMENU		
#define AMVK_PRINTSCREEN    VK_SNAPSHOT
#define AMVK_SCROLLLOCK	    VK_SCROLL
#define AMVK_PAUSE		    VK_PAUSE		
#define AMVK_CAPSLOCK	    VK_CAPITAL

#define AMVK_ESCAPE         VK_ESCAPE   

#define AMVK_SPACE		    VK_SPACE		
#define AMVK_PAGEUP		    VK_PRIOR		
#define AMVK_PAGEDOWN	    VK_NEXT
#define AMVK_END		    VK_END		
#define AMVK_HOME		    VK_HOME		
#define AMVK_LEFT		    VK_LEFT		
#define AMVK_UP			    VK_UP			
#define AMVK_RIGHT		    VK_RIGHT		
#define AMVK_DOWN		    VK_DOWN		
#define AMVK_INSERT		    VK_INSERT		
#define AMVK_DELETE		    VK_DELETE		

#define AMVK_0              0x30        
#define AMVK_1              0x31        
#define AMVK_2              0x32        
#define AMVK_3              0x33        
#define AMVK_4              0x34        
#define AMVK_5              0x35        
#define AMVK_6              0x36        
#define AMVK_7              0x37        
#define AMVK_8              0x38        
#define AMVK_9              0x39        

#define AMVK_A              0x41        
#define AMVK_B              0x42        
#define AMVK_C              0x43        
#define AMVK_D              0x44        
#define AMVK_E              0x45        
#define AMVK_F              0x46        
#define AMVK_G              0x47        
#define AMVK_H              0x48        
#define AMVK_I              0x49        
#define AMVK_J              0x4A        
#define AMVK_K              0x4B        
#define AMVK_L              0x4C        
#define AMVK_M              0x4D        
#define AMVK_N              0x4E        
#define AMVK_O              0x4F        
#define AMVK_P              0x50        
#define AMVK_Q              0x51        
#define AMVK_R              0x52        
#define AMVK_S              0x53        
#define AMVK_T              0x54        
#define AMVK_U              0x55        
#define AMVK_V              0x56        
#define AMVK_W              0x57        
#define AMVK_X              0x58        
#define AMVK_Y              0x59        
#define AMVK_Z              0x5A        

#define AMVK_NUMPAD0	    VK_NUMPAD0	
#define AMVK_NUMPAD1	    VK_NUMPAD1	
#define AMVK_NUMPAD2	    VK_NUMPAD2	
#define AMVK_NUMPAD3	    VK_NUMPAD3	
#define AMVK_NUMPAD4	    VK_NUMPAD4	
#define AMVK_NUMPAD5	    VK_NUMPAD5	
#define AMVK_NUMPAD6	    VK_NUMPAD6	
#define AMVK_NUMPAD7	    VK_NUMPAD7	
#define AMVK_NUMPAD8	    VK_NUMPAD8	
#define AMVK_NUMPAD9	    VK_NUMPAD9	

#define AMVK_NUM_MULTIPLY   VK_MULTIPLY
#define AMVK_NUM_PLUS	    VK_ADD
#define AMVK_NUM_MINUS	    VK_SUBTRACT
#define AMVK_NUM_PERIOD	    VK_DECIMAL
#define AMVK_NUM_DIVIDE	    VK_DIVIDE
#define AMVK_NUMLOCK	    VK_NUMLOCK	

#define AMVK_F1			    VK_F1			
#define AMVK_F2			    VK_F2			
#define AMVK_F3			    VK_F3			
#define AMVK_F4			    VK_F4			
#define AMVK_F5			    VK_F5			
#define AMVK_F6			    VK_F6			
#define AMVK_F7			    VK_F7			
#define AMVK_F8			    VK_F8			
#define AMVK_F9			    VK_F9			
#define AMVK_F10		    VK_F10		
#define AMVK_F11		    VK_F11		
#define AMVK_F12		    VK_F12		

#define AMVK_SEMICOLON	    VK_OEM_1        //!< ; :
#define AMVK_SLASH		    VK_OEM_2		//!< / ?
#define AMVK_BACKQUOTE		VK_OEM_3        //!< ` ~
#define AMVK_LBRACKET	    VK_OEM_4        //!< [ {
#define AMVK_BACKSLASH	    VK_OEM_5        //!< \ |
#define AMVK_RBRACKET	    VK_OEM_6        //!< ] }
#define AMVK_QUOTE		    VK_OEM_7	    //!< ' "

#define AMVK_EQUAL		    VK_OEM_PLUS     //!< = +		
#define AMVK_MINUS		    VK_OEM_MINUS    //!< - _		
#define AMVK_PERIOD		    VK_OEM_PERIOD   //!< . >		
#define AMVK_COMMA		    VK_OEM_COMMA    //!< , <		

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

