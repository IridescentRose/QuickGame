/**
 * @file Audio.h
 * @author Nathan Bourgeois (iridescentrosesfall@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2022-10-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _AUDIO_INCLUDED_H_
#define _AUDIO_INCLUDED_H_

#include <Types.h>

#if __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes the audio subsystem
 * 
 */
void QuickGame_Audio_Init();

/**
 * @brief Terminates the audio subsystem
 * 
 */
void QuickGame_Audio_Terminate();

/**
 * @brief Loads an audio clip
 * 
 * @param filename File name
 * @param looping Whether or not the audio is looping
 * @param streaming Whether or not we should stream the audio from disk
 * @return QGAudioClip_t Result audio clip or NULL on failure
 */
QGAudioClip_t QuickGame_Audio_Load(const char* filename, bool looping, bool streaming);

/**
 * @brief Audio Destroy
 * 
 * @param clip Destroys an audio clip
 */
void QuickGame_Audio_Destroy(QGAudioClip_t* clip);

/**
 * @brief Sets the clip's looping mode
 * 
 * @param clip Clip to set
 * @param looping Whether or not the clip should play in a loop
 */
void QuickGame_Audio_Set_Looping(QGAudioClip_t clip, bool looping);

/**
 * @brief Sets the clip's volume
 * 
 * @param clip Clip to set
 * @param volume Volume of the clip [0, 1]
 */
void QuickGame_Audio_Set_Volume(QGAudioClip_t clip, f32 volume);

/**
 * @brief Sets the clips' panning
 * 
 * @param clip Clip to set
 * @param pan Panning from [-1, 1]
 */
void QuickGame_Audio_Set_Pan(QGAudioClip_t clip, f32 pan);

/**
 * @brief Plays an audio clip on a channel. There are channels 0-8
 * 
 * @param clip Clip to play
 * @param channel Clip channel
 */
void QuickGame_Audio_Play(QGAudioClip_t clip, u8 channel);

/**
 * @brief Pauses an audio clip (this toggles if you call pause on a paused clip)
 * 
 * @param clip Clip to pause
 */
void QuickGame_Audio_Pause(QGAudioClip_t clip);

/**
 * @brief Stops an audio clip
 * 
 * @param clip Clip to stop
 */
void QuickGame_Audio_Stop(QGAudioClip_t clip);

#if __cplusplus
};
#endif

#endif