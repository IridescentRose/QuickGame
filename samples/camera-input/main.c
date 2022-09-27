#include <QuickGame.h>
#include <pspctrl.h>

int main(int argc, char** argv){
    if(QuickGame_Init() < 0)
        return 1;

    QGTexInfo tex_info = {.filename = "circle.png", .flip = 0, .vram = 0};
    QGSprite_t sprite = QuickGame_Sprite_Create_Contained(0, 0, 256, 256, tex_info);

    QGCamera2D camera = {
        {.x = 0, .y = 120},
        .rotation = 0.0f,
    };
    QuickGame_Graphics_Set_Camera(&camera);
    QuickGame_Graphics_Set2D();

    while(QuickGame_Running()){
        QuickGame_Input_Update();

        if(QuickGame_Button_Held(PSP_CTRL_UP)) {
            camera.position.y += 1.0f;
        }
        if(QuickGame_Button_Held(PSP_CTRL_DOWN)) {
            camera.position.y -= 1.0f;
        }
        if(QuickGame_Button_Held(PSP_CTRL_LEFT)) {
            camera.position.x -= 1.0f;
        }
        if(QuickGame_Button_Held(PSP_CTRL_RIGHT)) {
            camera.position.x += 1.0f;
        }
        
        QuickGame_Graphics_Start_Frame();
        QuickGame_Graphics_Clear();

        QuickGame_Sprite_Draw(sprite);

        QuickGame_Graphics_End_Frame(true);
    }
    QuickGame_Sprite_Destroy(&sprite);

    QuickGame_Terminate();
    return 0;
}