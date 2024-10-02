/******************************************************************************/
/*!
\par        Project: Amu Engine
\file       AMGraphics.h

\author     Shinwoo Choi
\date       Oct 30, 2024

\brief      Header file for the library settings.
*/
/******************************************************************************/
#include <AMExport.h>
#ifndef GRAPHICS_H
#define GRAPHICS_H

// ---------------------------------------------------------------------------
// Defines

/*! Engine render option */
typedef	enum
{
    GFX_RM_NONE,         //!< No render
    GFX_RM_COLOR,        //!< Color rendering
    GFX_RM_TEXTURE,      //!< Texture rendering

    GFX_RM_NUM
}GfxRenderMode;


// ---------------------------------------------------------------------------

/*! Engine blend option */
typedef enum
{
    GFX_BM_NONE = 0,     //!< No blending
    GFX_BM_BLEND,        //!< Color blending
    GFX_BM_ADD,          //!< Additive blending

    GFX_BM_NUM
}GfxBlendMode;

// ---------------------------------------------------------------------------

typedef enum
{
    GFX_TM_PRECISE = 0,
    GFX_TM_AVERAGE
} GfxTextureMode;

// ---------------------------------------------------------------------------

typedef enum
{
    GFX_MDM_POINTS = 0,
    GFX_MDM_LINES,
    GFX_MDM_LINES_STRIP,
    GFX_MDM_TRIANGLES,

    // Keep this one last
    GFX_MDM_NUM
}GfxMeshDrawMode;

// ---------------------------------------------------------------------------
// Struct/Class definitions

typedef struct GfxVertexBuffer GfxVertexBuffer;

typedef struct GfxVertexList
{
    GfxVertexBuffer* mpVtxBuffer;
    unsigned int		vtxNum;
}GfxVertexList;

// ---------------------------------------------------------------------------

typedef struct GfxSurface GfxSurface;

typedef struct GfxTexture
{
    GfxSurface* mpSurface;
    char mpName[256];
}GfxTexture;



// ---------------------------------------------------------------------------
// Function prototypes
// ---------------------------------------------------------------------------

#ifdef __cplusplus

extern "C"
{
#endif


    // ---------------------------------------------------------------------------

    /******************************************************************************/
    /*!
    \fn		    int GfxInit(int Width,
                              int Height)

    \brief      Initialize Graphics.

    \warning    This function is already called in SysInit.

    \param      [in] Width
                Set the width of the window.

    \param      [in] Height
                Set the height of the window.

    \retval     int
                Return 1 if initialization is successful.
                Else return 0.
    */
    /******************************************************************************/
    API int GfxInit(int Width, int Height);

    /******************************************************************************/
    /*!
    \fn         void GfxSetVSync(int vsync)

    \brief      Enable/Disable VSync.
                Note that enabling VSync does not garuntee that VSync is
                enabled. VSync can be disabled by the user.

    \param      [in] vsync
                If 0 is passed, disables VSync.
                Otherwise, enables VSync.

    \warning

    */
    /******************************************************************************/
    API void GfxSetVSync(int vsync);

    /******************************************************************************/
    /*!
    \fn         void GfxReset()

    \brief      Reset Graphics.

    \warning    This function is already called in SysReset.

    */
    /******************************************************************************/
    API void GfxReset();

    /******************************************************************************/
    /*!
    \fn         void GfxExit()

    \brief      Free Graphics.

    \warning    This function is already called in SysExit.

    */
    /******************************************************************************/
    API void GfxExit();

    /******************************************************************************/
    /*!
    \fn         void GfxStart()

    \brief      Tell Graphics that a new frame is starting.

    \warning    This function is already called in SysFrameStart.

    */
    /******************************************************************************/
    API void GfxStart();

    /******************************************************************************/
    /*!
    \fn         void GfxEnd()

    \brief      Tell Graphics that the current frame is ending.

    \warning    This function is already called in SysFrameEnd.

    */
    /******************************************************************************/
    API void GfxEnd();

    /******************************************************************************/
    /*!
    \fn         void GfxSetBackgroundColor(float Red,
                                             float Green,
                                             float Blue)

    \brief      Set the background colour to selected RGB values.

    \param      [in] Red
                Percentage of red. Range from 0.0f to 1.0f.

    \param      [in] Green
                Percentage of green. Range from 0.0f to 1.0f.

    \param      [in] Blue
                Percentage of blue. Range from 0.0f to 1.0f.

    */
    /******************************************************************************/
    API void GfxSetBackgroundColor(float Red, float Green, float Blue);

    /******************************************************************************/
    /*!
    \fn         void GfxSetRenderMode(GfxRenderMode RenderMode)

    \brief      Set the render mode.

    \warning    This function should be called at least once per frame,
                before any rendering is done.

    \param      [in] RenderMode
                The GfxRenderMode to set.

    */
    /******************************************************************************/
    API void GfxSetRenderMode(GfxRenderMode RenderMode);

    /******************************************************************************/
    /*!
    \fn         void GfxSetBlendMode(GfxBlendMode BlendMode)

    \brief      Set the blend mode.

    \param      [in] BlendMode
                The GfxBlendMode to set.

    */
    /******************************************************************************/
    API void	GfxSetBlendMode(GfxBlendMode BlendMode);


    /******************************************************************************/
    /*!
    \fn         void GfxGetWindowWidth()

    \brief      Get the window's width

    \retval     int
                Returns the window's width

    */
    /******************************************************************************/
    API int GfxGetWindowWidth();

    /******************************************************************************/
    /*!
    \fn         void GfxGetWindowHeight()

    \brief      Get the window's height

    \retval     int
                Returns the window's height

    */
    /******************************************************************************/
    API int GfxGetWindowHeight();



    /******************************************************************************/
    /*!
    \fn         float GfxGetWinMinX(void)

    \brief      Get the minimum X world coordinate.

    \retval     float
                Returns the minimum X world coordinate.
    */
    /******************************************************************************/
    API float GfxGetWinMinX(void);

    /******************************************************************************/
    /*!
    \fn         float GfxGetWinMaxX(void)

    \brief      Get the maximum X world coordinate.

    \retval     float
                Returns the maximum X world coordinate.
    */
    /******************************************************************************/
    API float GfxGetWinMaxX(void);

    /******************************************************************************/
    /*!
    \fn         float GfxGetWinMinY(void)

    \brief      Get the minimum Y world coordinate.

    \retval     float
                Returns the minimum Y world coordinate.
    */
    /******************************************************************************/
    API float GfxGetWinMinY(void);

    /******************************************************************************/
    /*!
    \fn         float GfxGetWinMaxY(void)

    \brief      Get the maximum Y world coordinate.

    \retval     float
                Returns the maximum Y world coordinate.
    */
    /******************************************************************************/
    API float GfxGetWinMaxY(void);

    /******************************************************************************/
    /*!
    \fn         void GfxSetCamPosition(float X, float Y)

    \brief      Set the camera's X and Y position.

    \param      [in] X
                X position to set camera to.

    \param      [in] Y
                Y position to set camera to.

    */
    /******************************************************************************/
    API void GfxSetCamPosition(float X, float Y);

    /******************************************************************************/
    /*!
    \fn         void GfxGetCamPosition(float *pX, float *pY)

    \brief      Get the camera's X and Y position.

    \param      [out] pX
                Pointer to float to store the X position in.

    \param      [out] pY
                Pointer to float to store the Y position in.

    */
    /******************************************************************************/
    API void GfxGetCamPosition(float* pX, float* pY);

    // Sets/Gets the camera distance, used to zoom in/out
    API void GfxSetCamZoom(float Distance);
    API float GfxGetCamZoom();

    /******************************************************************************/
    /*!
    \fn		    void GfxSetTransform(float pTransform[3][3])

    \brief      Set the new global transformation matrix.

    \details    The new matrix will be applied to all object drawn
                after this function was called.

    \param      [in] pTransform
                Pointer to a 3x3 matrix to set with.
                User may pass in a Mtx33.m.

    */
    /******************************************************************************/
    API void GfxSetTransform(float pTransform[3][3]);

    /******************************************************************************/
    /*!
    \fn		    void GfxSetTransform3D(float pTransform[4][4])

    \brief      Set the new global transformation matrix.

    \details    The new matrix will be applied to all object drawn
                after this function was called.

    \param      [in] pTransform
                Pointer to a 4x4 matrix to set with.

    */
    /******************************************************************************/
    API void GfxSetTransform3D(float pTransform[4][4]);

    /******************************************************************************/
    /*!
    \fn		    void GfxSetTransparency(float Alpha)

    \brief      Set the new global transparency value.

    \details    The new transparency value will be applied to all object
                drawn after this function was called.

    \param      [in] Alpha
                Percentage of alpha (transparency).
                Range from 0.0f (clear) to 1.0f (opaque).

    */
    /******************************************************************************/
    API void GfxSetTransparency(float Alpha);

    /******************************************************************************/
    /*!
    \fn		    void GfxSetBlendColor(float Red,
                                        float Green,
                                        float Blue,
                                        float Alpha)

    \brief      Sets a color (RGBA) that will be used to blend with the
                original material.

    \param      [in] Red
                Percentage of red. Range from 0.0f to 1.0f.

    \param      [in] Green
                Percentage of green. Range from 0.0f to 1.0f.

    \param      [in] Blue
                Percentage of blue. Range from 0.0f to 1.0f.

    \param      [in] Alpha
                Percentage of alpha (transparency).
                Range from 0.0f (clear) to 1.0f (opaque).

    */
    /******************************************************************************/
    API void GfxSetBlendColor(float Red, float Green, float Blue, float Alpha);



    /******************************************************************************/
    /*!
    \fn		    void GfxSetColorToMultiply(float Red,
                                             float Green,
                                             float Blue,
                                             float Alpha)

    \brief      Sets a color (RGBA) that will be used to multiply with
                the original material.

    \param      [in] Red
                Percentage of red. Range from 0.0f to 1.0f.

    \param      [in] Green
                Percentage of green. Range from 0.0f to 1.0f.

    \param      [in] Blue
                Percentage of blue. Range from 0.0f to 1.0f.

    \param      [in] Alpha
                Percentage of alpha (transparency).
                Range from 0.0f (clear) to 1.0f (opaque).

    */
    /******************************************************************************/
    API void GfxSetColorToMultiply(float Red, float Green, float Blue, float Alpha);

    /******************************************************************************/
    /*!
    \fn		    void GfxSetColorToAdd(float Red,
                                        float Green,
                                        float Blue,
                                        float Alpha)

    \brief      Sets a color (RGBA) that will be used to add with
                the original material.

    \param      [in] Red
                Percentage of red. Range from 0.0f to 1.0f.

    \param      [in] Green
                Percentage of green. Range from 0.0f to 1.0f.

    \param      [in] Blue
                Percentage of blue. Range from 0.0f to 1.0f.

    \param      [in] Alpha
                Percentage of alpha (transparency).
                Range from 0.0f (clear) to 1.0f (opaque).

    */
    /******************************************************************************/
    API void GfxSetColorToAdd(float Red, float Green, float Blue, float Alpha);

    /******************************************************************************/
    /*!
    \fn		    void GfxMeshStart()

    \brief      Instruct Graphics to start creating a new mesh.

    \details    Call this function once before adding any points
                to the mesh.

    */
    /******************************************************************************/
    API void		    	GfxMeshStart();

    /******************************************************************************/
    /*!
    \fn		    void GfxTriAdd(float x0, float y0, unsigned int c0, float tu0, float tv0,
                                 float x1, float y1, unsigned int c1, float tu1, float tv1,
                                 float x2, float y2, unsigned int c2, float tu2, float tv2)

    \brief      Add a new triangle to the mesh.

    \details    The triangle is defined by 3 points: pt0, pt1 and pt2.
                The points are listed in a counter-clockwise order.
                The Z-value of the points are set to default 0.

    \param      [in] x0
                X coordinate of pt0.

    \param      [in] y0
                Y coordinate of pt0.

    \param      [in] c0
                Color value of pt0.

    \param      [in] tu0
                Texture translation of pt0.

    \param      [in] tv0
                Texture translation of pt0.

    \param      [in] x1
                X coordinate of pt1.

    \param      [in] y1
                Y coordinate of pt1.

    \param      [in] c1
                Color value of pt1.

    \param      [in] tu1
                Texture translation of pt1.

    \param      [in] tv1
                Texture translation of pt1.

    \param      [in] x2
                X coordinate of pt2.

    \param      [in] y2
                Y coordinate of pt2.

    \param      [in] c2
                Color value of pt2.

    \param      [in] tu2
                Texture translation of pt2.

    \param      [in] tv2
                Texture translation of pt2.

    */
    /******************************************************************************/
    API void			    GfxTriAdd(float x0, float y0, unsigned int c0, float tu0, float tv0,
        float x1, float y1, unsigned int c1, float tu1, float tv1,
        float x2, float y2, unsigned int c2, float tu2, float tv2);

    /******************************************************************************/
    /*!
    \fn		    void GfxVertexAdd(float x0,
                                    float y0,
                                    unsigned int c0,
                                    float tu0,
                                    float tv0)

    \brief      Add a new point to the mesh.

    \details    The Z-value of the point are set to default 0.

    \param      [in] x0
                X coordinate of the point.

    \param      [in] y0
                Y coordinate of the point.

    \param      [in] c0
                Color value of the point.

    \param      [in] tu0
                Texture translation of the point.

    \param      [in] tv0
                Texture translation of the point.

    */
    /******************************************************************************/
    API void			    GfxVertexAdd(float x0, float y0, unsigned int c0, float tu0, float tv0);

    /******************************************************************************/
    /*!
    \fn		    GfxVertexList* GfxMeshEnd()

    \brief      Instruct Graphics to end creating of new mesh.

    \details    Call this function once after all the points have
                been added to the mesh.

    \retval     GfxVertexList*
                Returns a GfxVertexList pointer to the new mesh.
    */
    /******************************************************************************/
    API GfxVertexList* GfxMeshEnd();

    /******************************************************************************/
    /*!
    \fn		    void GfxMeshDraw(GfxVertexList* pVertexList,
                                   GfxMeshDrawMode MeshDrawMode)

    \brief      Draw the mesh on screen.

    \details    Render the mesh onto the screen using the MeshDrawMode
                stated.

    \param      [in] pVertexList
                Pointer to the GfxVertexList to be rendered.

    \param      [in] MeshDrawMode
                The GfxMeshDrawMode to use for rendering the mesh.

    */
    /******************************************************************************/
    API void				GfxMeshDraw(GfxVertexList* pVertexList, GfxMeshDrawMode MeshDrawMode);

    /******************************************************************************/
    /*!
    \fn		    void GfxMeshFree(GfxVertexList* pVertexList)

    \brief      Free the mesh.

    \details    Release the mesh from Graphics memory.
                The mesh is destroyed and can no longer be used.

    \param      [in] pVertexList
                Pointer to the GfxVertexList to be free.

    */
    /******************************************************************************/
    API void				GfxMeshFree(GfxVertexList* pVertexList);

    /******************************************************************************/
    /*!
    \fn		    GfxTexture* GfxTextureLoad(const char *pFileName)

    \brief      Load a texture file into memory.

    \param      [in] pFileName
                Pointer to a null-terminated string containing the
                relative path of the file to be loaded.

    \retval     GfxTexture*
                Returns a GfxTexture pointer to the loaded texture.
    */
    /******************************************************************************/
    API GfxTexture* GfxTextureLoad(const char* pFileName);

    /******************************************************************************/
    /*!
    \fn		    void GfxTextureSet(GfxTexture *pTexture,
                                     float offset_x,
                                     float offset_y)

    \brief      Set a texture to be used for rendering.

    \param      [in] pTexture
                Pointer to the GfxTexture to be used.
                Set to null if not using texture.

    \param      [in] offset_x
                X offset for the texture. Range from 0.0f to 1.0f.

    \param      [in] offset_y
                Y offset for the texture. Range from 0.0f to 1.0f.

    */
    /******************************************************************************/
    API void				GfxTextureSet(GfxTexture* pTexture, float offset_x, float offset_y);

    /******************************************************************************/
    /*!
    \fn		    void GfxTextureUnload(GfxTexture *pTexture)

    \brief      Unload a texture file from memory.

    \param      [in] pTexture
                Pointer to GfxTexture to be unloaded.

    */
    /******************************************************************************/
    API void				GfxTextureUnload(GfxTexture* pTexture);

    /******************************************************************************/
    /*!
    \fn		    GfxTexture* GfxTextureLoadFromMemory(u8 *pColors,
                                                         unsigned int Width,
                                                         unsigned int Height)

    \brief      Load a texture from data in memory.

    \param      [in] pColors
                Pointer to an array containing the data.

    \param      [in] Width
                The width of the texture.

    \param      [in] Height
                The height of the texture.

    \retval     GfxTexture*
                Returns a GfxTexture pointer to the loaded texture.
    */
    /******************************************************************************/
    API GfxTexture* GfxTextureLoadFromMemory(unsigned char* pColors, unsigned int Width, unsigned int Height);

    /******************************************************************************/
    /*!
    \fn		    void GfxSaveTextureToFile(GfxTexture* pTexture,
                                            signed char *pFileName)

    \brief      Save a texture from memory to file.

    \param      [in] pTexture
                Pointer to GfxTexture to be saved.

    \param      [in] pFileName
                Pointer to a null-terminated string containing the
                relative path of the file.

    */
    /******************************************************************************/
    API void				GfxSaveTextureToFile(GfxTexture* pTexture, signed char* pFileName);

    /******************************************************************************/
    /*!
    \fn         void GfxSetTextureMode(GfxTextureMode TextureMode)

    \brief      Set the texture mode.

    \param      [in] TextureMode
                The GfxTextureMode to set.

    */
    /******************************************************************************/
    API void				GfxSetTextureMode(GfxTextureMode TextureMode);

    /******************************************************************************/
    /*!
    \fn         unsigned int	GfxColInterp(unsigned int c0, unsigned int c1, float t)

    \brief      Get the interpolation between two colours (c0 and c1)
                at time interval t.

    \warning    t should be between 0.0f to 1.0f.

    \param      [in] c0
                The first colour.

    \param      [in] c1
                The second colour.

    \param      [in] t
                The time interval to calculate the interpolation at.
                At t = 0.0f, the result will be c0.
                At t = 1.0f, the result will be c1.

    */
    /******************************************************************************/
    API unsigned int				GfxColInterp(unsigned int c0, unsigned int c1, float t);



    // ---------------------------------------------------------------------------
    //                            FONT SYSTEM


    /******************************************************************************/
    /*!
    \fn         signed char  GfxCreateFont(const char * fontName, int fontHeight);

    \brief      Load a Font in memory, and prepares it for usage in the Alphngine

    \param      [in] fontName
                Full Path to the font ( accept .ttf, .ttc, .cff, .otf, .otc, .fnt ...)

    \param      [in] fontHeight
                Initial height of the font glyphs (a glyph is the texture of a single character).

    \retval     signed char
                ID of the font, returns -1 if unsuccessful.
    */
    /******************************************************************************/
    API signed char  GfxCreateFont(const char* fontName, int sizeF);

    /******************************************************************************/
    /*!
    \fn		    void GfxPrint(signed char fontId, const char* str,
                                float x, float y,
                                float scale,
                                float red, float green, float blue, float alpha)

    \brief      Prints a text on screen

    \warning	Be sure to set GfxSetBlendMode(GFX_BM_BLEND) mode before
                calling this function.

                Uses Screen percent as Coordinates to Handle multi-resolution. You
                still have to manage the proper scaling yourself, according to the
                initial size of the font you have chosen.

                Keep scale close to 1.0f to avoid glyph visual artifact.

    \param      [in] fontId
                ID of a font created with GfxCreateFont.

    \param      [in] str
                String to Display.

    \param      [in] x
                X position in Normalized Coordinates. Range from -1.0f to 1.0f.

    \param      [in] y
                Y position in Normalized Coordinates. Range from -1.0f to 1.0f.

    \param      [in] scale
                Applied scale to the original Font size created with GfxCreateFont

    \param      [in] red
                Percentage of red. Range from 0.0f to 1.0f.

    \param      [in] green
                Percentage of green. Range from 0.0f to 1.0f.

    \param      [in] blue
                Percentage of blue. Range from 0.0f to 1.0f.

    \param      [in] alpha
                Percentage of alpha. Range from 0.0f to 1.0f.

    */
    /******************************************************************************/
    API void GfxPrint(signed char fontId, const char* str, float x, float y, float scale, float red, float green, float blue, float alpha);


    /******************************************************************************/
    /*!
    \fn		    void GfxGetPrintSize(signed char fontId, const char* pStr, float scale, float* width, float* height)

    \brief      Gets the size of a Text in the specified font.

    \param      [in] fontId
                ID of a font created with GfxCreateFont.

    \param      [in] pStr
                String to Measure.

    \param      [in] scale
                Applied scale to the original Font size created with GfxCreateFont.

    \param      [out] width
                width of the text. In Screen Percent ( 0 = empty, to 2 = full screen).

    \param      [out] height
                height of the text. In screen Percent ( 0 = empty, to 2 = full screen).

    */
    /******************************************************************************/
    API void GfxGetPrintSize(signed char fontId, const char* pStr, float scale, float* width, float* height);


    /******************************************************************************/
    /*!
    \fn         void GfxDestroyFont(signed char fontId);

    \brief      Deletes a Font from memory

    \param      [in] fontId
                ID returned from the GfxCreateFont(...) function

    */
    /******************************************************************************/
    API void GfxDestroyFont(signed char fontId);

    /******************************************************************************/
    /*!
    \fn         void  GfxFontSystemStart( );

    \brief      Initializes the Font system.

    \warning   	This function is already called in SysInit. Do not call it

    */
    /******************************************************************************/
    API void GfxFontSystemStart();

    /******************************************************************************/
    /*!
    \fn         void  GfxFontSystemEnd( );

    \brief      Ends the Font system. And clear all Fonts from memory

    \warning    This function is already called in SysExit. Do not call it

    */
    /******************************************************************************/
    API void GfxFontSystemEnd();

    // ---------------------------------------------------------------------------


#ifdef __cplusplus 
}
#endif

// ---------------------------------------------------------------------------

#endif // GRAPHICS_H

