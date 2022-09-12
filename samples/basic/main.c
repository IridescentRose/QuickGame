#include <QuickGame.h>

#include <gu2gl.h>

int main(int argc, char** argv){
    if(QuickGame_Init() < 0)
        return 1;

    QGColor col;
    col.color = 0xFFFFFFFF;

    QuickGame_Graphics_Set_Clear_Color(col);

    while(QuickGame_Running()){
        QuickGame_Graphics_Start_Frame();

        QuickGame_Graphics_Clear();
        // Main Program Loop

        QuickGame_Graphics_End_Frame(true);
    }

    QuickGame_Terminate();
    return 0;
}