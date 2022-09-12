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

#endif