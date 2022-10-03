/**
 * @file Input.h
 * @author Nathan Bourgeois (iridescentrosesfall@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2022-09-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef _QUICKGAME_INPUT_INCLUDED_H_
#define _QUICKGAME_INPUT_INCLUDED_H_

#include <Types.h>

#if __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the input system -- does not need termination
 * 
 */
void QuickGame_Input_Init();

/**
 * @brief Update the input system
 * 
 */
void QuickGame_Input_Update();

/**
 * @brief Is Button Pressed? This will only return true on the very FIRST time the button (combination) is pressed until it is released
 * 
 * @param buttons Button or button combination from PSP CTRL
 * @return true Button is pressed
 * @return false Button is not pressed
 */
bool QuickGame_Button_Pressed(u32 buttons);

/**
 * @brief Is Button Held? This will return true on the subsequent times the button  (combination) is held until it is released
 * 
 * @param buttons Button or button combination from PSP CTRL
 * @return true Button is held
 * @return false Button is not held
 */
bool QuickGame_Button_Held(u32 buttons);

/**
 * @brief Is Button Released? Only returns true if this is the EXACT moment of release. This only trigger when a button (combination) stops being pressed.
 * 
 * @param buttons Button or button combination from PSP CTRL
 * @return true 
 * @return false 
 */
bool QuickGame_Button_Released(u32 buttons);

/**
 * @brief Gets the current analog X position, scaled to [-1, 1]
 * 
 * @return f32 X position
 */
f32 QuickGame_Analog_X();

/**
 * @brief Gets the current analog Y position, scaled to [-1, 1]
 * 
 * @return f32 Y position
 */
f32 QuickGame_Analog_Y();

#if __cplusplus
};
#endif

#endif