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

typedef QGTexture *QGTexture_t;

typedef struct {
    const char* filename;
    bool flip;
    bool vram;
} QGTexInfo;

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
 * @brief Vertex with Texture, and Position
 * 
 */
typedef struct {
    float u, v;
    float x, y, z;
} QGTexturedVertex;

/**
 * @brief Vertex with Texture, Color, and Position
 * 
 */
typedef struct {
    float u, v;
    QGColor color;
    float x, y, z;
} QGFullVertex;

/**
 * @brief Vertex with Color and Position
 * 
 */
typedef struct {
    QGColor color;
    float x, y, z;
} QGColoredVertex;

/**
 * @brief Simplest vertex
 * 
 */
typedef struct {
    float x, y, z;
} QGSimpleVertex;

/**
 * @brief Vertex types
 * 
 */
typedef enum {
    QG_VERTEX_TYPE_TEXTURED = 0x00,
    QG_VERTEX_TYPE_COLORED = 0x01,
    QG_VERTEX_TYPE_FULL = 0x02,
    QG_VERTEX_TYPE_SIMPLE = 0x03
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

typedef QGVMesh *QGVMesh_t;

/**
 * @brief Camera data structure
 * 
 */
typedef struct {
    QGVector2 position;
    f32 rotation;
} QGCamera2D;

/**
 * @brief Texture Atlas information
 * 
 */
typedef struct {
    f32 x, y;
} QGTextureAtlas;


typedef struct {
    QGVector2 position;
    QGVector2 scale;
    usize atlas_idx;
    QGColor color;
    bool collide;
} QGTile;

typedef struct {
    QGTransform2D transform;
    QGTextureAtlas atlas;
    QGTexture_t texture;
    QGVector2 size;
    QGTile* tile_array;
    QGVMesh_t mesh;
} QGTilemap;

typedef QGTilemap *QGTilemap_t;

typedef struct {
    f64 total;
    u64 last;
    u32 resolution;
} QGTimer;

typedef struct {
    void* data;
} QGAudioClip;

typedef QGAudioClip *QGAudioClip_t;

#endif