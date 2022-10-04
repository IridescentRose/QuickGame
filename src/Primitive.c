#include <Primitive.h>
#include <stddef.h>
#include <gu2gl.h>
#include <math.h>
#include <pspkernel.h>

QGVMesh_t _quickgame_rect;
QGVMesh_t _quickgame_tri;
QGVMesh_t _quickgame_circle;

QGSimpleVertex create_simple_vert(float x, float y, float z){
    QGSimpleVertex vert = {
        .x = x,
        .y = y,
        .z = z
    };

    return vert;
}

/**
 * @brief Initialize Primitive Drawings
 * 
 * returns int < 0 on failure.
 */
int QuickGame_Primitive_Init() {
    _quickgame_rect = QuickGame_Graphics_Create_Mesh(QG_VERTEX_TYPE_SIMPLE, 4, 6);
    _quickgame_tri = QuickGame_Graphics_Create_Mesh(QG_VERTEX_TYPE_SIMPLE, 3, 4);
    _quickgame_circle = QuickGame_Graphics_Create_Mesh(QG_VERTEX_TYPE_SIMPLE, 22, 63);

    if(_quickgame_rect == NULL || _quickgame_tri == NULL || _quickgame_circle == NULL)
        return 0;

    ((QGSimpleVertex*)_quickgame_rect->data)[0] = create_simple_vert(-0.5f, -0.5f, 0.0f);
    ((QGSimpleVertex*)_quickgame_rect->data)[1] = create_simple_vert( 0.5f, -0.5f, 0.0f);
    ((QGSimpleVertex*)_quickgame_rect->data)[2] = create_simple_vert( 0.5f,  0.5f, 0.0f);
    ((QGSimpleVertex*)_quickgame_rect->data)[3] = create_simple_vert(-0.5f,  0.5f, 0.0f);

    _quickgame_rect->indices[0] = 0;
    _quickgame_rect->indices[1] = 1;
    _quickgame_rect->indices[2] = 2;
    _quickgame_rect->indices[3] = 2;
    _quickgame_rect->indices[4] = 3;
    _quickgame_rect->indices[5] = 0;


    ((QGSimpleVertex*)_quickgame_tri->data)[0] = create_simple_vert( 0, 0.5f, 0.0f);
    ((QGSimpleVertex*)_quickgame_tri->data)[1] = create_simple_vert( 0.70f, -0.5f, 0.0f);
    ((QGSimpleVertex*)_quickgame_tri->data)[2] = create_simple_vert( -0.70f, -0.5f, 0.0f);

    _quickgame_tri->indices[0] = 0;
    _quickgame_tri->indices[1] = 2;
    _quickgame_tri->indices[2] = 1;
    _quickgame_tri->indices[3] = 0;


    ((QGSimpleVertex*)_quickgame_circle->data)[0] = create_simple_vert(0.0f, 0.0f, 0.0f);

    for(int i = 0; i < 21; i++){
        float angle = 2.0f * 3.14159f / 20.0f * (float)i;

        float x = sinf(angle) * 0.5f;
        float y = cosf(angle) * 0.5f;

        ((QGSimpleVertex*)_quickgame_circle->data)[i+1] = create_simple_vert(x, y, 0.0f);

        _quickgame_circle->indices[i * 3 + 0] = 0;

        _quickgame_circle->indices[i * 3 + 1] = i + 1;

        _quickgame_circle->indices[i * 3 + 2] = i;
    }

    sceKernelDcacheWritebackInvalidateAll();

    return 0;
}

void QuickGame_Primitive_Terminate() {
    QuickGame_Graphics_Destroy_Mesh(&_quickgame_circle);
    QuickGame_Graphics_Destroy_Mesh(&_quickgame_rect);
    QuickGame_Graphics_Destroy_Mesh(&_quickgame_tri);
}

void QuickGame_Primitive_Draw_Rectangle(QGTransform2D transform, QGColor color) {
    glMatrixMode(GL_MODEL);
    glLoadIdentity();

    ScePspFVector3 v1 = {transform.position.x, transform.position.y, 0.0f};
    gluTranslate(&v1);

    gluRotateZ(transform.rotation / 180.0f * GL_PI);

    ScePspFVector3 v = {transform.scale.x, transform.scale.y, 1.0f};
    gluScale(&v); 
    
    glColor(color.color);

    QuickGame_Graphics_Draw_Mesh(_quickgame_rect);
}

void QuickGame_Primitive_Draw_Triangle(QGTransform2D transform, QGColor color) {
    glMatrixMode(GL_MODEL);
    glLoadIdentity();

    ScePspFVector3 v1 = {transform.position.x, transform.position.y, 0.0f};
    gluTranslate(&v1);

    gluRotateZ(transform.rotation / 180.0f * GL_PI);

    ScePspFVector3 v = {transform.scale.x, transform.scale.y, 1.0f};
    gluScale(&v); 
    
    glColor(color.color);

    QuickGame_Graphics_Draw_Mesh(_quickgame_tri);
}

void QuickGame_Primitive_Draw_Circle(QGTransform2D transform, QGColor color) {
    glMatrixMode(GL_MODEL);
    glLoadIdentity();

    ScePspFVector3 v1 = {transform.position.x, transform.position.y, 0.0f};
    gluTranslate(&v1);

    gluRotateZ(transform.rotation / 180.0f * GL_PI);

    ScePspFVector3 v = {transform.scale.x, transform.scale.y, 1.0f};
    gluScale(&v); 
    
    glColor(color.color);

    QuickGame_Graphics_Draw_Mesh(_quickgame_circle);
}