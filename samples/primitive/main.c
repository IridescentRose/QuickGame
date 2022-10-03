#include <QuickGame.h>

int main(int argc, char** argv){
    if(QuickGame_Init() < 0)
        return 1;

    QuickGame_Graphics_Set2D();

    while(QuickGame_Running()){
        QuickGame_Graphics_Start_Frame();
        QuickGame_Graphics_Clear();

        QGTransform2D transform = {
            .position = {.x = 240, .y = 136},
            .rotation = 0.0f,
            .scale = {.x = 40, .y = 40}
        };
        QGColor col;

        col.color = 0xFF0000FF;
        QuickGame_Primitive_Draw_Rectangle(transform, col);

        transform.position.x = 120;
        col.color = 0xFF00FF00;
        QuickGame_Primitive_Draw_Triangle(transform, col);

        transform.position.x = 360;
        col.color = 0xFFFF0000;
        QuickGame_Primitive_Draw_Circle(transform, col);

        QuickGame_Graphics_End_Frame(true);
    }

    QuickGame_Terminate();
    return 0;
}