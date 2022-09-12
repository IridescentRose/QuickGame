/**
 * @file Sprite.h
 * @author Nathan Bourgeois (iridescentrosesfall@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2022-09-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _SPRITE_INCLUDED_H_
#define _SPRITE_INCLUDED_H_

#include <Types.h>

#if __cplusplus
extern "C" {
#endif

typedef struct {
    QGTransform2D transform;
    i32 layer;
    QGTexture* texture;
    QGVMesh* mesh;
} QGSprite;

/**
 * @brief Creates a sprite
 * 
 * @param position Position for sprite
 * @param size Size of sprite
 * @param texture Texture to use
 * @return QGSprite* Sprite result or NULL if failed
 */
QGSprite* QuickGame_Sprite_Create(QGVector2 position, QGVector2 size, QGTexture* texture);

/**
 * @brief Destroy a sprite and sets it to NULL
 * 
 * @param sprite Pointer to Sprite
 */
void QuickGame_Sprite_Destroy(QGSprite** sprite);

/**
 * @brief 
 * 
 * @param sprite 
 */
void QuickGame_Sprite_Draw(QGSprite* sprite);

#if __cplusplus
};
#endif

#endif