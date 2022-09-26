#include <QuickGame.h>
#include <Sprite.h>
#include <Types.h>
#include <stddef.h>
#include <gu2gl.h>
#include <pspkernel.h>


QGSprite_t QuickGame_Sprite_Create_Contained(float x, float y, float w, float h, QGTexInfo tex_info){
    QGTexture_t tex = QuickGame_Texture_Load_Alt(tex_info);
    if(!tex)
        return NULL;
    
    QGSprite_t result = QuickGame_Sprite_Create_Alt(x, y, w, h, tex);

    if(!result)
        QuickGame_Texture_Destroy(&tex);
    else
        result->contained = true;

    return result;
}

QGSprite_t QuickGame_Sprite_Create_Alt(float x, float y, float w, float h, QGTexture_t texture) {
    QGVector2 position = {x, y};
    QGVector2 size = {w, h};

    return QuickGame_Sprite_Create(position, size, texture);
}

QGSprite_t QuickGame_Sprite_Create(QGVector2 position, QGVector2 size, QGTexture_t texture) {
    if(!texture)
        return NULL;

    QGSprite_t sprite = QuickGame_Allocate(sizeof(QGSprite));
    if(!sprite)
        return NULL;

    sprite->layer = 0;
    sprite->color.color = 0xFFFFFFFF;

    sprite->transform.position = position;
    sprite->transform.scale = size;
    sprite->texture = texture;

    sprite->mesh = QuickGame_Graphics_Create_Mesh(QG_VERTEX_TYPE_TEXTURED, 4, 6);
    if(!sprite->mesh) {
        QuickGame_Destroy(sprite);
        return NULL;
    }

    QGTexturedVertex* verts = sprite->mesh->data;
    verts[0].u = 0.0f;
    verts[0].v = 0.0f;
    verts[0].x = -0.5f;
    verts[0].y = -0.5f;
    verts[0].z = 0.0f;


    verts[1].u = 1.0f;
    verts[1].v = 0.0f;
    verts[1].x = 0.5f;
    verts[1].y = -0.5f;
    verts[1].z = 0.0f;


    verts[2].u = 1.0f;
    verts[2].v = 1.0f;
    verts[2].x = 0.5f;
    verts[2].y = 0.5f;
    verts[2].z = 0.0f;


    verts[3].u = 0.0f;
    verts[3].v = 1.0f;
    verts[3].x = -0.5f;
    verts[3].y = 0.5f;
    verts[3].z = 0.0f;

    u16* indices = sprite->mesh->indices;
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 2;
    indices[4] = 3;
    indices[5] = 0;

    sceKernelDcacheWritebackInvalidateAll();

    return sprite;
}

/**
 * @brief Destroy a sprite and sets it to NULL
 * 
 * @param sprite Pointer to Sprite
 */
void QuickGame_Sprite_Destroy(QGSprite_t* sprite) {
    if(sprite != NULL)
        return;
    
    QuickGame_Graphics_Destroy_Mesh(&(*sprite)->mesh);
    
    if((*sprite)->contained)
        QuickGame_Texture_Destroy(&(*sprite)->texture);
    
    QuickGame_Destroy((*sprite));
    *sprite = NULL;
}

/**
 * @brief 
 * 
 * @param sprite 
 */
void QuickGame_Sprite_Draw(QGSprite_t sprite) {
    if(!sprite)
        return;

    glMatrixMode(GL_MODEL);
    glLoadIdentity();


    ScePspFVector3 v1 = {sprite->transform.position.x, sprite->transform.position.y, sprite->layer};
    gluTranslate(&v1);

    gluRotateZ(sprite->transform.rotation / 180.0f * GL_PI);

    ScePspFVector3 v = {sprite->transform.scale.x, sprite->transform.scale.y, 1.0f};
    gluScale(&v); 
    
    glColor(sprite->color.color);

    QuickGame_Texture_Bind(sprite->texture);
    QuickGame_Graphics_Draw_Mesh(sprite->mesh);
    QuickGame_Texture_Unbind(sprite->texture);

}
