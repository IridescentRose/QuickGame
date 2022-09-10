#include <QuickGame.h>
#include <pspkernel.h>

PSP_MODULE_INFO("QuickGame", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int QuickGame_Init() {

    return 0;
}

void QuickGame_Terminate() {

}