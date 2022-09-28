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
    QGColor color;
    QGTexture_t texture;
    QGVMesh_t mesh;
    bool contained;
} QGSprite;

typedef QGSprite *QGSprite_t;

/**
 * @brief Creates a sprite
 * 
 * @param position Position for sprite
 * @param size Size of sprite
 * @param texture Texture to use
 * @return QGSprite_t Sprite result or NULL if failed
 */
QGSprite_t QuickGame_Sprite_Create(QGVector2 position, QGVector2 size, QGTexture_t texture);

/**
 * @brief Creates a sprite
 * 
 * @param x X of sprite
 * @param y Y of sprite
 * @param w Width of Sprite
 * @param h Height of Sprite
 * @param texture Texture to use
 * @return QGSprite_t Sprite result or NULL if failed
 */
QGSprite_t QuickGame_Sprite_Create_Alt(float x, float y, float w, float h, QGTexture_t texture);

/**
 * @brief Creates a sprite and loads a texture. This texture is owned by the sprite and destroyed on sprite destroy.
 * 
 * @param x X of sprite
 * @param y Y of sprite
 * @param w Width of Sprite
 * @param h Height of Sprite
 * @param tex_info Information about the texture to load
 * @return QGSprite_t Sprite result or NULL if failed
 */
QGSprite_t QuickGame_Sprite_Create_Contained(float x, float y, float w, float h, QGTexInfo tex_info);

/**
 * @brief Destroy a sprite and sets it to NULL
 * 
 * @param sprite Pointer to Sprite
 */
void QuickGame_Sprite_Destroy(QGSprite_t* sprite);

/**
 * @brief 
 * 
 * @param sprite 
 */
void QuickGame_Sprite_Draw(QGSprite_t sprite);

enum QGDirection{
    QG_DIR_UP = 1,
    QG_DIR_DOWN = 2,
    QG_DIR_LEFT = 3,
    QG_DIR_RIGHT = 4,
};

/**
 * @brief Intersection Detection
 * 
 * @param a Sprite A
 * @param b Sprite B
 * @return true Sprites intersect
 * @return false Sprites do not intersect
 */
bool QuickGame_Sprite_Intersects(QGSprite_t a, QGSprite_t b);

/**
 * @brief Intersection Direction
 * 
 * @param a Sprite A
 * @param b Sprite B
 * @return uint8_t Direction
 */
uint8_t QuickGame_Sprite_Intersect_Direction(QGSprite_t a, QGSprite_t b);

#if __cplusplus
};
#endif

#endif