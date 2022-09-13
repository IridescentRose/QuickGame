/**
 * @file Texture.h
 * @author Nathan Bourgeois (iridescentrosesfall@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2022-09-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef _TEXTURE_INCLUDED_H_
#define _TEXTURE_INCLUDED_H_

#include <Types.h>

#if __cplusplus
extern "C" {
#endif

/**
 * @brief Load a texture from disk
 * 
 * @param filename File to load
 * @param vram Whether the texture should be stored in VRAM
 * @return QGTexture_t Texture loaded or NULL if failed
 */
QGTexture_t QuickGame_Texture_Load(const char* filename, const unsigned int flip, const unsigned int vram);

/**
 * @brief Destroys a texture pointer
 * 
 * @param texture Texture to destroy, also sets the texture pointer to null.
 */
void QuickGame_Texture_Destroy(QGTexture_t* texture);

/**
 * @brief Texture to bind to the graphics engine
 * 
 * @param texture Texture to bind
 */
void QuickGame_Texture_Bind(const QGTexture_t texture);

/**
 * @brief Texture to unbind from the graphics engine
 * 
 */
void QuickGame_Texture_Unbind();

#if __cplusplus
};
#endif

#endif