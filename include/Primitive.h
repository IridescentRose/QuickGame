/**
 * @file Primitive.h
 * @author Nathan Bourgeois (iridescentrosesfall@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2022-10-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef _QG_PRIMITIVE_INCLUDED_H_
#define _QG_PRIMITIVE_INCLUDED_H_

#include <QuickGame.h>


#if __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize Primitive Drawings
 * 
 * returns int < 0 on failure.
 */
int QuickGame_Primitive_Init();

/**
 * @brief Terminate Primitives
 * 
 */
void QuickGame_Primitive_Terminate();

/**
 * @brief Draw a rectangle with a given transform and color
 * 
 * @param transform Position, Rotation, Size
 * @param color Color to draw with
 */
void QuickGame_Primitive_Draw_Rectangle(QGTransform2D transform, QGColor color);

/**
 * @brief Draw a triangle with a given transform and color
 * 
 * @param transform Position, Rotation, Size
 * @param color Color to draw with
 */
void QuickGame_Primitive_Draw_Triangle(QGTransform2D transform, QGColor color);

/**
 * @brief Draw a circle with a given transform and color
 * 
 * @param transform Position, Rotation, Size
 * @param color Color to draw with
 */
void QuickGame_Primitive_Draw_Circle(QGTransform2D transform, QGColor color);

#if __cplusplus
};
#endif

#endif