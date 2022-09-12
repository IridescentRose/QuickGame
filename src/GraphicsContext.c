#include <GraphicsContext.h>
#include <QuickGame.h>
#define GUGL_IMPLEMENTATION
#include <gu2gl.h>

static u32 __attribute__((aligned(16))) list[262144];
static QGColor clearColor;

static bool dialogMode;

void QuickGame_Graphics_Init() {
    guglInit(list);
    dialogMode = false;
}

void QuickGame_Graphics_Terminate() {
    guglTerm();
}

void QuickGame_Graphics_Set_Dialog_Mode(bool mode) {
    dialogMode = mode;
}

void QuickGame_Graphics_Start_Frame() {
    guglStartFrame(list, dialogMode);
}

void QuickGame_Graphics_End_Frame(bool vsync) {
    guglSwapBuffers(vsync, dialogMode);
}

void QuickGame_Graphics_Set_Clear_Color(QGColor color) {
    clearColor = color;
    glClearColor(clearColor.color);
}

void QuickGame_Graphics_Clear(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

QGVMesh* QuickGame_Graphics_Create_Mesh(const u8 type, const usize vcount, const usize icount) {
    QGVMesh* mesh = (QGVMesh*)QuickGame_Allocate(sizeof(QGVMesh));

    if(!mesh)
        return NULL;

    mesh->type = type;
    mesh->count = icount;
    if(type == QG_VERTEX_TYPE_TEXTURED) {
        mesh->data = QuickGame_Allocate_Aligned(16, sizeof(QGTexturedVertex) * vcount);
        mesh->indices = (u16*)QuickGame_Allocate_Aligned(16, sizeof(u16) * icount);
    } else if (type == QG_VERTEX_TYPE_COLORED) {
        mesh->data = QuickGame_Allocate_Aligned(16, sizeof(QGColoredVertex) * vcount);
        mesh->indices = (u16*)QuickGame_Allocate_Aligned(16, sizeof(u16) * icount);
    } else {
        QuickGame_Destroy(mesh);
        return NULL;
    }

    return mesh;
}

void QuickGame_Graphics_Destroy_Mesh(QGVMesh** mesh) {
    if(!mesh)
        return;
    
    QuickGame_Destroy((*mesh)->data);
    QuickGame_Destroy((*mesh)->indices);
    QuickGame_Destroy(*mesh);
    *mesh = NULL;
}


void QuickGame_Graphics_Draw_Mesh(QGVMesh* mesh) {
    if(!mesh || !mesh->data || !mesh->indices)
        return;
    
    usize vtype = GL_INDEX_16BIT | GL_COLOR_8888 | GL_VERTEX_32BITF | GL_TRANSFORM_3D;

    if(mesh->type == QG_VERTEX_TYPE_TEXTURED){
        glEnable(GL_TEXTURE_2D);
        vtype |= GL_TEXTURE_32BITF;
    } else if (mesh->type == QG_VERTEX_TYPE_COLORED) {
        glDisable(GL_TEXTURE_2D);
        QuickGame_Texture_Unbind();
    } else {
        return;
    }
    glDrawElements(GL_TRIANGLES, vtype, mesh->count, mesh->indices, mesh->data);
}

void QuickGame_Graphics_Set2D() {
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
    glEnable(GL_BLEND);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 480, 0, 272, -30, 30);

    glMatrixMode(GL_VIEW);
    glLoadIdentity();

    glMatrixMode(GL_MODEL);
    glLoadIdentity();
}