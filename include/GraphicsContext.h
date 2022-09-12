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
void QuickGame_Graphics_Set_Clear_Color(Color color);

/**
 * @brief Clears the screen
 * 
 */
void QuickGame_Graphics_Clear();

#if __cplusplus
};
#endif

#endif