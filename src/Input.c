#include <pspctrl.h>
#include <Input.h>

static struct SceCtrlData padData;
static struct SceCtrlData oldData;

void QuickGame_Input_Init() {
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
}

void QuickGame_Input_Update() {
    oldData = padData;
    sceCtrlReadBufferPositive(&padData,1);
}

bool QuickGame_Button_Pressed(u32 buttons) {
    bool current = (padData.Buttons & buttons) == buttons;
    bool last = (oldData.Buttons & buttons) == buttons;
    return current && !last; // Currently pressed, not pressed last time
}

bool QuickGame_Button_Held(u32 buttons) {
    bool current = (padData.Buttons & buttons) == buttons;
    bool last = (oldData.Buttons & buttons) == buttons;
    return current && last; // Currently pressed, and pressed last time
}

bool QuickGame_Button_Released(u32 buttons) {
    bool current = (padData.Buttons & buttons) == buttons;
    bool last = (oldData.Buttons & buttons) == buttons;
    return !current && last; // Currently not pressed, and pressed last time
}

f32 QuickGame_Analog_X() {
    float v = ((float)(padData.Lx - 127)) / 255.0f;
    v -= 0.5f;
    v *= 2.0f;

    return v;
}

f32 QuickGame_Analog_Y() {
    float v = ((float)(padData.Ly - 127)) / 255.0f;
    v -= 0.5f;
    v *= 2.0f;

    return v;
}