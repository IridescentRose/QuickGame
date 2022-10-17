#include <QuickGame.h>
#include <Audio.h>
#include "osl_sound/oslib.h"
#include "osl_sound/audio.h"

void QuickGame_Audio_Init() {
    VirtualFileInit();
    oslInitAudio();
}

void QuickGame_Audio_Terminate() {
    oslDeinitAudio();
}

QGAudioClip_t QuickGame_Audio_Load(const char* filename, bool looping, bool streaming){
    QGAudioClip_t clip = QuickGame_Allocate(sizeof(QGAudioClip));
    if(clip == NULL)
        return NULL;
    
    clip->data = oslLoadSoundFile(filename, streaming ? OSL_FMT_STREAM : OSL_FMT_NONE);
    
    if(clip->data == NULL){
        QuickGame_Destroy(&clip);
        return NULL;
    }

    oslSetSoundLoop(((OSL_SOUND*)clip->data), looping); 
    return clip;
}

void QuickGame_Audio_Destroy(QGAudioClip_t* clip){
    if(clip == NULL || (*clip) == NULL)
        return;
    
    oslDeleteSound((*clip)->data);
    QuickGame_Destroy(*clip);
    *clip = NULL;
}

void QuickGame_Audio_Set_Looping(QGAudioClip_t clip, bool looping) {
    if(clip == NULL)
        return;
    oslSetSoundLoop(((OSL_SOUND*)clip->data), looping); 
}

void QuickGame_Audio_Set_Volume(QGAudioClip_t clip, f32 volume) {
    if(clip == NULL)
        return;
    ((OSL_SOUND*)clip->data)->volumeLeft = (1.0f-volume) * 100;
    ((OSL_SOUND*)clip->data)->volumeRight = (1.0f-volume) * 100;
}

void QuickGame_Audio_Set_Pan(QGAudioClip_t clip, f32 pan) {
    if(clip == NULL)
        return;
    float left = 1.0f - pan;
    float right = pan - 1.0f;

    ((OSL_SOUND*)clip->data)->volumeLeft *= left;
    ((OSL_SOUND*)clip->data)->volumeRight *= right;
}

void QuickGame_Audio_Play(QGAudioClip_t clip, u8 channel) {
    if(clip == NULL)
        return;
    oslPlaySound(((OSL_SOUND*)clip->data), channel);
}
void QuickGame_Audio_Pause(QGAudioClip_t clip) {
    if(clip == NULL)
        return;
    oslPauseSound(((OSL_SOUND*)clip->data), -1);
}
void QuickGame_Audio_Stop(QGAudioClip_t clip) {
    if(clip == NULL)
        return;
    oslStopSound(((OSL_SOUND*)clip->data));
}
