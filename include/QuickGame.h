
#ifndef _QUICKGAME_INCLUDED_H_
#define _QUICKGAME_INCLUDED_H_

#if __cplusplus
extern "C" {
#endif

/// @brief Initializes the game engine
/// @return < 0 on failure, 0 on success
int QuickGame_Init();

/// @brief Terminates the game engine
void QuickGame_Terminate();

#if __cplusplus
};
#endif

#endif