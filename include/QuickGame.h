/**
 * @file QuickGame.h
 * @author Nathan Bourgeois (iridescentrosesfall@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2022-09-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _QUICKGAME_INCLUDED_H_
#define _QUICKGAME_INCLUDED_H_

#include <Types.h>
#include <GraphicsContext.h>

#if __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes the game engine
 * @return < 0 on failure, 0 on success
 * 
 */
s32 QuickGame_Init();

/**
 * @brief 
 * 
 */
bool QuickGame_Running();

/**
 * @brief Terminates the game engine
 * 
 */
void QuickGame_Terminate();

/**
 * @brief Requests an exit from the game engine
 * 
 */
void QuickGame_Request_Exit();

#if __cplusplus
};
#endif

#endif