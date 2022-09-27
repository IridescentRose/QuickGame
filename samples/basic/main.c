#include <QuickGame.h>

int main(int argc, char** argv){
    if(QuickGame_Init() < 0)
        return 1;

    QGTexture_t tex = QuickGame_Texture_Load("circle.png", 0, 0);
    QGSprite_t sprite = QuickGame_Sprite_Create_Alt(240, 136, 256, 256, tex);

    QuickGame_Graphics_Set2D();

    while(QuickGame_Running()){
        QuickGame_Graphics_Start_Frame();

        QuickGame_Graphics_Clear();

        QuickGame_Sprite_Draw(sprite);

        QuickGame_Graphics_End_Frame(true);
    }

    QuickGame_Sprite_Destroy(&sprite);
    QuickGame_Texture_Destroy(&tex);

    QuickGame_Terminate();
    return 0;
}