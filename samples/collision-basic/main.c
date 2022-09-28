#include <QuickGame.h>
#include <pspctrl.h>

int main(int argc, char** argv){
    if(QuickGame_Init() < 0)
        return 1;

    QGTexInfo tex_info = {.filename = "circle.png", .flip = 0, .vram = 0};
    QGSprite_t sprite = QuickGame_Sprite_Create_Contained(360, 136, 64, 64, tex_info);

    QGTexInfo tex_info2 = {.filename = "container.jpg", .flip = 0, .vram = 0};
    QGSprite_t sprite2 = QuickGame_Sprite_Create_Contained(120, 136, 64, 64, tex_info2);

    QuickGame_Graphics_Set2D();

    while(QuickGame_Running()){
        QuickGame_Input_Update();

        if(QuickGame_Button_Held(PSP_CTRL_UP)) {
            sprite2->transform.position.y += 1.0f;
        }
        if(QuickGame_Button_Held(PSP_CTRL_DOWN)) {
            sprite2->transform.position.y -= 1.0f;
        }
        if(QuickGame_Button_Held(PSP_CTRL_LEFT)) {
            sprite2->transform.position.x -= 1.0f;
        }
        if(QuickGame_Button_Held(PSP_CTRL_RIGHT)) {
            sprite2->transform.position.x += 1.0f;
        }

        if(QuickGame_Sprite_Intersects(sprite, sprite2)) {
            sprite2->color.color = 0xFF00FF00;
            sprite->color.color = 0xFF0000FF;
        } else {
            sprite2->color.color = 0xFFFFFFFF;
            sprite->color.color = 0xFFFFFFFF;
        }

        QuickGame_Graphics_Start_Frame();
        QuickGame_Graphics_Clear();

        QuickGame_Sprite_Draw(sprite);
        QuickGame_Sprite_Draw(sprite2);

        QuickGame_Graphics_End_Frame(true);
    }
    QuickGame_Sprite_Destroy(&sprite);

    QuickGame_Terminate();
    return 0;
}