#include <QuickGame.h>

int main(int argc, char** argv){
    if(QuickGame_Init() < 0)
        return 1;

    QGTexture_t tex = QuickGame_Texture_Load("terrain.png", 0, 0);
    QGTextureAtlas atlas = {.x = 16, .y = 16};
    QGVector2 size = {.x = 8, .y = 8};
    QGTilemap_t tilemap = QuickGame_Tilemap_Create(atlas, tex, size);

    for(int i = 0; i < 64; i++){
        QGTile t = {
            .position = {.x = 16 * (i % 8), .y = 16 * (i / 8)},
            .scale = {.x = 16.0f, .y = 16.0f},
            .collide = false,
            .atlas_idx = i,
            .color.color = 0xFFFFFFFF,
        };
        tilemap->tile_array[i] = t;
    }
    QuickGame_Tilemap_Build(tilemap);

    QuickGame_Graphics_Set2D();

    while(QuickGame_Running()){
        QuickGame_Graphics_Start_Frame();

        QuickGame_Graphics_Clear();

        QuickGame_Tilemap_Draw(tilemap);

        QuickGame_Graphics_End_Frame(true);
    }

    QuickGame_Tilemap_Destroy(&tilemap);
    QuickGame_Texture_Destroy(&tex);

    QuickGame_Terminate();
    return 0;
}