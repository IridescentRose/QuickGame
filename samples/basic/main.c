#include <QuickGame.h>
#include <gu2gl.h>

int main(int argc, char** argv){
    if(QuickGame_Init() < 0)
        return 1;

    QGColor col;
    col.color = 0xFF000000;

    QuickGame_Graphics_Set_Clear_Color(col);

    QGTexture* tex = QuickGame_Texture_Load("circle.png", 0, 0);
    QGVector2 position = {240, 136};
    QGVector2 size = {256, 256};
    QGSprite* sprite = QuickGame_Sprite_Create(position, size, tex);
    sprite->color.color = 0xFF00FF00;

    while(QuickGame_Running()){
        QuickGame_Graphics_Start_Frame();
        QuickGame_Graphics_Set2D();
        QuickGame_Graphics_Clear();

        QuickGame_Sprite_Draw(sprite);

        QuickGame_Graphics_End_Frame(true);
    }

    QuickGame_Sprite_Destroy(&sprite);
    QuickGame_Texture_Destroy(&tex);

    QuickGame_Terminate();
    return 0;
}