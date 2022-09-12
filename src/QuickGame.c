#include <QuickGame.h>
#include <GraphicsContext.h>
#include <pspkernel.h>

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

s32 QuickGame_Init() {
    if(setupCallbacks() < 0){
        return -1;
    }

    // Technically this could fail
    // FIXME: Handle Fail Case
    QuickGame_Graphics_Init();

    return 0;
}

void QuickGame_Terminate() {
    QuickGame_Graphics_Terminate();
    sceKernelExitGame();
}