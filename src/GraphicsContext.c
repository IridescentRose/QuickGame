#include <GraphicsContext.h>
#define GUGL_IMPLEMENTATION
#include <gu2gl.h>

static u32 __attribute__((aligned(16))) list[262144];
static QGColor clearColor;

static bool dialogMode;

void QuickGame_Graphics_Init() {
    guglInit(list);
    dialogMode = false;
}

void QuickGame_Graphics_Terminate(){
    guglTerm();
}

void QuickGame_Graphics_Set_Dialog_Mode(bool mode) {
    dialogMode = mode;
}

void QuickGame_Graphics_Start_Frame() {
    guglStartFrame(list, dialogMode);
}

void QuickGame_Graphics_End_Frame(bool vsync){
    guglSwapBuffers(vsync, dialogMode);
}

void QuickGame_Graphics_Set_Clear_Color(QGColor color) {
    clearColor = color;
    glClearColor(clearColor.color);
}

void QuickGame_Graphics_Clear(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}