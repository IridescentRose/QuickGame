#include <QuickGame.h>
#include <Tilemap.h>
#include <stddef.h>
#include <gu2gl.h>

/**
 * @brief Gets texture coordinates from an atlas given a position
 * 
 * @param atlas Texture Atlas to use as reference
 * @param buf Buffer to fill with the coordinates
 * @param idx Index of the atlas to get coordinates for
 */
void QuickGame_Atlas_Index_Coords(const QGTextureAtlas atlas, f32* buf, const usize idx) {
    if(buf == NULL)
        return;
    
    float x = (f32)(idx % 16) / atlas.x;
    float y = (f32)(idx / 16) / atlas.y;
    float w = x + 1.0f / atlas.x;
    float h = y + 1.0f / atlas.y;

    buf[0] = x;
    buf[1] = y;

    buf[2] = w;
    buf[3] = y;

    buf[4] = w;
    buf[5] = h;
    
    buf[6] = x;
    buf[7] = h;
}

/**
 * @brief Create a tilemap
 * 
 * @param texture_atlas Texture Atlas size 
 * @param texture Texture to use
 * @param size Size of tile map
 * @return QGTilemap_t Created tilemap or NULL on failure
 */
QGTilemap_t QuickGame_Tilemap_Create(QGTextureAtlas texture_atlas, QGTexture_t texture, QGVector2 size) {
    QGTilemap_t tilemap = (QGTilemap*)QuickGame_Allocate(sizeof(QGTilemap));
    if(tilemap == NULL)
        return NULL;

    tilemap->tile_array = (QGTile*)QuickGame_Allocate(sizeof(QGTile) * size.x * size.y);
    if(tilemap->tile_array == NULL){
        QuickGame_Destroy(tilemap);
        return NULL;
    }
    
    tilemap->mesh = QuickGame_Graphics_Create_Mesh(QG_VERTEX_TYPE_FULL, size.x * size.y * 4, size.x * size.y * 6);
    if(tilemap->mesh == NULL){
        QuickGame_Destroy(tilemap->tile_array);
        QuickGame_Destroy(tilemap);
    }

    tilemap->atlas = texture_atlas;
    tilemap->texture = texture;
    tilemap->size = size;

    tilemap->transform.position.x = 0;
    tilemap->transform.position.y = 0;
    tilemap->transform.rotation = 0;
    tilemap->transform.scale.x = 1.0f;
    tilemap->transform.scale.y = 1.0f;

    return tilemap;
}

/**
 * @brief Adds a tile to the map
 * 
 * @param tilemap Tilemap to insert the tile into
 * @param tile Tile to insert
 */
void QuickGame_Tilemap_Add_Tile(QGTilemap_t tilemap, const QGTile tile) {
    if(!tilemap)
        return;
    
    usize idx = tile.x + tile.y * tilemap->size.x;
    
    if(idx < tilemap->size.x * tilemap->size.y){
        tilemap->tile_array[idx] = tile;
    }
}

QGFullVertex create_vert(float u, float v, unsigned int color, float x, float y, float z){
    QGFullVertex vert = {
        .u = u,
        .v = v,
        .color.color = color,
        .x = x,
        .y = y,
        .z = z
    };

    return vert;
}

/**
 * @brief Builds a tilemap to render
 * 
 * @param tilemap Tilemap
 */
void QuickGame_Tilemap_Build(QGTilemap_t tilemap) {
    if(!tilemap)
        return;
    
    for(usize y = 0; y < tilemap->size.y; y++)
    for(usize x = 0; x < tilemap->size.x; x++){
        usize idx = x + y * tilemap->size.x;

        QGTile* tile = &tilemap->tile_array[idx];

        unsigned int color = tile->color.color;

        f32 buf[8];
        QuickGame_Atlas_Index_Coords(tilemap->atlas, buf, tile->atlas_idx);

        float tx = (float)x;
        float ty = (float)y;
        float tw = x + 1.0f;
        float th = x + 1.0f;

        ((QGFullVertex*)tilemap->mesh->data)[idx * 4 + 0] = create_vert(buf[0], buf[1], color, tx, ty, 0.0f);
        ((QGFullVertex*)tilemap->mesh->data)[idx * 4 + 1] = create_vert(buf[2], buf[3], color, tw, ty, 0.0f);
        ((QGFullVertex*)tilemap->mesh->data)[idx * 4 + 2] = create_vert(buf[4], buf[5], color, tw, th, 0.0f);
        ((QGFullVertex*)tilemap->mesh->data)[idx * 4 + 3] = create_vert(buf[6], buf[7], color, tx, th, 0.0f);

        tilemap->mesh->indices[idx * 6 + 0] = (idx * 6) + 0;
        tilemap->mesh->indices[idx * 6 + 1] = (idx * 6) + 1;
        tilemap->mesh->indices[idx * 6 + 2] = (idx * 6) + 2;
        tilemap->mesh->indices[idx * 6 + 3] = (idx * 6) + 2;
        tilemap->mesh->indices[idx * 6 + 4] = (idx * 6) + 3;
        tilemap->mesh->indices[idx * 6 + 5] = (idx * 6) + 0;
    }
}

/**
 * @brief Destroy a tilemap
 * 
 * @param tilemap Tile map to destroy -- also gets set to null.
 */
void QuickGame_Tilemap_Destroy(QGTilemap_t* tilemap) {
    if(tilemap == NULL || (*tilemap) == NULL)
        return;
    
    if((*tilemap)->tile_array != NULL)
        QuickGame_Destroy((*tilemap)->tile_array);
    
    if((*tilemap)->mesh != NULL)
        QuickGame_Graphics_Destroy_Mesh(&(*tilemap)->mesh);
    
    QuickGame_Destroy((*tilemap));
}


/**
 * @brief Draws a tilemap to the screen
 * 
 * @param tilemap Tilemap
 */
void QuickGame_Tilemap_Draw(QGTilemap_t tilemap) {
    if(tilemap == NULL)
        return;
    

    glMatrixMode(GL_MODEL);
    glLoadIdentity();


    ScePspFVector3 v1 = {tilemap->transform.position.x, tilemap->transform.position.y, 0.0f};
    gluTranslate(&v1);

    gluRotateZ(tilemap->transform.rotation / 180.0f * GL_PI);

    ScePspFVector3 v = {tilemap->transform.scale.x, tilemap->transform.scale.y, 1.0f};
    gluScale(&v); 

    QuickGame_Texture_Bind(tilemap->texture);
    QuickGame_Graphics_Draw_Mesh(tilemap->mesh);
    QuickGame_Texture_Unbind(tilemap->texture);

}