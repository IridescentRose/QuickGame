/**
 * @file Timer.h
 * @author Nathan Bourgeois (iridescentrosesfall@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _TIMER_INCLUDED_H_
#define _TIMER_INCLUDED_H_

#include <QuickGame.h>

#if __cplusplus
extern "C" {
#endif

/**
 * @brief Start a timer
 * 
 * @param timer Timer to use
 */
void QuickGame_Timer_Start(QGTimer* timer);

/**
 * @brief Get Delta from last delta request / start
 * 
 * @param timer Timer to use
 * @return double Delta Time
 */
double QuickGame_Timer_Delta(QGTimer* timer);

/**
 * @brief Elapsed total time since start
 * 
 * @param timer Timer to use
 * @return double Elapsed Time
 */
double QuickGame_Timer_Elapsed(QGTimer* timer);

/**
 * @brief Resets a timer
 * 
 * @param timer Timer to use
 */
void QuickGame_Timer_Reset(QGTimer* timer);

#if __cplusplus
};
#endif

#endif