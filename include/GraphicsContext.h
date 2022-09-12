/**
 * @file GraphicsContext.h
 * @author Nathan Bourgeois (iridescentrosesfall@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2022-09-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _GRAPHICS_CONTEXT_INCLUDED_H_
#define _GRAPHICS_CONTEXT_INCLUDED_H_

#include <Types.h>

#if __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes the graphics context
 * 
 */
void QuickGame_Graphics_Init();

/**
 * @brief Terminates the graphics context
 * 
 */
void QuickGame_Graphics_Terminate();

/**
 * @brief Sets a dialog mode
 * 
 * @param mode Are we inside a dialog mode?
 */
void QuickGame_Graphics_Set_Dialog_Mode(bool mode);

/**
 * @brief Starts a new frame
 * 
 */
void QuickGame_Graphics_Start_Frame();

/**
 * @brief Ends the frame and draws to screen
 * 
 * @param vsync Whether or not to VSync?
 */
void QuickGame_Graphics_End_Frame(bool vsync);

/**
 * @brief Sets the clear color of the screen
 * 
 * @param color Background color
 */
void QuickGame_Graphics_Set_Clear_Color(QGColor color);

/**
 * @brief Clears the screen
 * 
 */
void QuickGame_Graphics_Clear();

/**
 * @brief Sets rendering for 2D -- must be called inside of StartFrame() EndFrame()
 * 
 */
void QuickGame_Graphics_Set2D();

/**
 * @brief Creates a mesh with the select mesh type and number of elements
 * 
 * @param type Type of Mesh
 * @param vcount Vertex Count
 * @param icount Index Count
 * @return QGVMesh* Result Mesh or NULL on failure.
 */
QGVMesh* QuickGame_Graphics_Create_Mesh(const u8 type, const usize vcount, const usize icount);

/**
 * @brief Destroys a Graphics Mesh and sets pointer to NULL.
 * 
 * @param mesh Pointer to Mesh to destroy
 */
void QuickGame_Graphics_Destroy_Mesh(QGVMesh** mesh);

/**
 * @brief Draws a Graphics Mesh
 * 
 * @param mesh Mesh to draw
 */
void QuickGame_Graphics_Draw_Mesh(QGVMesh* mesh);

#if __cplusplus
};
#endif

#endif