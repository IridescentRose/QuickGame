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

#include <Audio.h>
#include <GraphicsContext.h>
#include <Input.h>
#include <Primitive.h>
#include <Sprite.h>
#include <Texture.h>
#include <Tilemap.h>
#include <Timer.h>
#include <Types.h>

#if __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes the game engine
 * @return < 0 on failure, 0 on success
 * 
 */
i32 QuickGame_Init();

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

/**
 * MEMORY ALLOCATION
 * TO OVERRIDE THESE FUNCTIONS
 * #define QUICKGAME_CUSTOM_ALLOCATOR
 */

/**
 * @brief Allocates memory of size n
 * 
 * @param n Size in bytes to allocate
 * @return anyopaque* Result or NULL if failed
 */
anyopaque* QuickGame_Allocate(usize n);

/**
 * @brief Allocates memory of size n and aligned to a bytes
 * 
 * @param a 
 * @param n 
 * @return anyopaque* 
 */
anyopaque* QuickGame_Allocate_Aligned(usize a, usize n);

/**
 * @brief Destroyes memory allocation
 * 
 * @param src Memory allocation to destroy
 */
void QuickGame_Destroy(anyopaque* src);

#if __cplusplus
};
#endif

#endif