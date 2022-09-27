#include <QuickGame.h>

int main(int argc, char** argv){
    if(QuickGame_Init() < 0)
        return 1;

    QGTexInfo tex_info = {.filename = "circle.png", .flip = 0, .vram = 0};
    QGSprite_t sprite = QuickGame_Sprite_Create_Contained(240, 136, 256, 256, tex_info);

    QuickGame_Graphics_Set2D();

    while(QuickGame_Running()){
        QuickGame_Graphics_Start_Frame();
        QuickGame_Graphics_Clear();

        QuickGame_Sprite_Draw(sprite);

        QuickGame_Graphics_End_Frame(true);
    }
    QuickGame_Sprite_Destroy(&sprite);

    QuickGame_Terminate();
    return 0;
}