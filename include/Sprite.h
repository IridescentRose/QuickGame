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
    QGVector2 aabb_size;
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
 * @brief Creates a sprite
 * 
 * @param position Position of sprite
 * @param size Size of sprite
 * @param u1 top left image x cord
 * @param v1 top left image y cord
 * @param w width of the selected rect
 * @param h height of the selected rect
 * @param texture Texture to use
 * @return QGSprite_t Sprite result or NULL if failed
 */
QGSprite_t QuickGame_Sprite_Create_Drakonchik(QGVector2 position, QGVector2 size, float u1, float v1, float w, float h, QGTexture_t texture);


/**
 * @brief Destroy a sprite and sets it to NULL
 * 
 * @param sprite Pointer to Sprite
 */
void QuickGame_Sprite_Destroy(QGSprite_t* sprite);

/**
 * @brief Draws a sprite to the screen
 * 
 * @param sprite Sprite to draw
 */
void QuickGame_Sprite_Draw(QGSprite_t sprite);

enum QGDirection{
    QG_DIR_UP = 1,
    QG_DIR_DOWN = 2,
    QG_DIR_LEFT = 3,
    QG_DIR_RIGHT = 4,
};

enum QGFlip {
    QG_FLIP_NONE        = 0x00,
    QG_FLIP_VERTICAL    = 0x01,
    QG_FLIP_HORIZONTAL  = 0x02,
    QG_FLIP_BOTH        = 0x03
};

/**
 * @brief Draws a sprite to the screen
 * 
 * @param sprite Sprite to draw
 * @param flip Flip type
 */
void QuickGame_Sprite_Draw_Flipped(QGSprite_t sprite, uint8_t flip);

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
 * @brief Intersection Detection
 * 
 * @param a Transform A
 * @param b Transform B
 * @return true Transforms intersect
 * @return false Transforms do not intersect
 */
bool QuickGame_Intersect_Transform(QGTransform2D a, QGTransform2D b);

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