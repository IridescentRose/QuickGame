#include <QuickGame.h>
#include <GraphicsContext.h>
#include <pspkernel.h>
#include <malloc.h>
#include <string.h>

PSP_MODULE_INFO("QuickGame", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

static int exitRequest = 0;

int exitCallback()
{
	exitRequest = 1;
	return 0;
}

int callbackThread(SceSize args, void *argp)
{
    if(args){
        args = 0;
    }
    
    if(argp){
        argp = NULL;
    }

	int cbid = sceKernelCreateCallback("Exit Callback", exitCallback, NULL);
	sceKernelRegisterExitCallback(cbid);

	sceKernelSleepThreadCB();

	return 0;
}

int setupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", callbackThread, 0x11, 0xFA0, 0, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

bool QuickGame_Running() {
	return !exitRequest;
}

void QuickGame_Request_Exit() {
    exitRequest = true;
}

i32 QuickGame_Init() {
    if(setupCallbacks() < 0){
        return -1;
    }

    // Technically this could fail
    // FIXME: Handle Fail Case
    QuickGame_Graphics_Init();

    // Initialize input
    QuickGame_Input_Init();

    // Init Audio
    QuickGame_Audio_Init();

    if(QuickGame_Primitive_Init() < 0){
        return -1;
    }

    return 0;
}

void QuickGame_Terminate() {
    QuickGame_Audio_Terminate();
    QuickGame_Graphics_Terminate();
    sceKernelExitGame();
}

#ifndef QUICKGAME_CUSTOM_ALLOCATOR
anyopaque* QuickGame_Allocate(usize n) {
    anyopaque* a = malloc(n);
    if(a != NULL){
        memset(a, 0, n);
    }

    return a;
}

anyopaque* QuickGame_Allocate_Aligned(usize a, usize n) {
    anyopaque* p = memalign(a, n);
    if(p != NULL){
        memset(p, 0, n);
    }

    return p;
}

void QuickGame_Destroy(anyopaque* src) {
    if(src)
        free(src);
}
#endif