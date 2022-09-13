/**
 * @file GraphicsType.h
 * @author Nathan Bourgeois (iridescentrosesfall@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2022-09-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _GRAPHICS_TYPE_INCLUDED_H_
#define _GRAPHICS_TYPE_INCLUDED_H_

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Unsigned Types
 * 
 */
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef u32 usize;

/**
 * @brief Signed Types
 * 
 */
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef i32 isize;


/**
 * @brief Floating point types
 * 
 */
typedef float f32;
typedef double f64;

/**
 * @brief Color Union
 * 
 */
typedef union {
    struct __attribute__ ((__packed__)) RGBA {
        u8 r;
        u8 g;
        u8 b;
        u8 a;
    } rgba;
    u32 color;
} QGColor;

typedef void anyopaque;

/**
 * @brief Textures
 * 
 */
typedef struct {
    u32 width, height;
    u32 pWidth, pHeight;
    anyopaque* data;
} QGTexture;

/**
 * @brief Vector2
 */
typedef struct {
    f32 x, y;
} QGVector2;

/**
 * @brief Vector3
 * 
 */
typedef struct {
    f32 x, y, z;
} QGVector3;

/**
 * @brief Transform2D
 * 
 */
typedef struct {
    QGVector2 position;
    f32 rotation;
    QGVector2 scale;
} QGTransform2D;

/**
 * @brief Vertex with Texture, Color, and Position
 * 
 */
typedef struct {
    float u, v;
    float x, y, z;
} QGTexturedVertex;

/**
 * @brief Vertex with Color and Position
 * 
 */
typedef struct {
    QGColor color;
    float x, y, z;
} QGColoredVertex;

/**
 * @brief Vertex types
 * 
 */
typedef enum {
    QG_VERTEX_TYPE_TEXTURED = 0x00,
    QG_VERTEX_TYPE_COLORED = 0x01
} QGVType;

/**
 * @brief Basic Mesh data structure
 * 
 */
typedef struct {
    u8 type;
    usize count;

    void* data;
    u16* indices;
} QGVMesh;

#endif