#include <GraphicsContext.h>
#include <QuickGame.h>
#define GUGL_IMPLEMENTATION
#include <gu2gl.h>

static u32 __attribute__((aligned(16))) list[262144];
static QGColor clearColor;
static QGCamera2D* cam_ptr;
static bool dialogMode;
static bool wireframeMode;

void QuickGame_Graphics_Init() {
    guglInit(list);
    
    QuickGame_Graphics_Start_Frame();
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
    glEnable(GL_BLEND);
    glFrontFace(GL_CCW);
    QuickGame_Graphics_End_Frame(false);

    dialogMode = false;
    cam_ptr = NULL;
    wireframeMode = false;
}

void QuickGame_Graphics_Terminate() {
    guglTerm();
}

void QuickGame_Graphics_Set_Dialog_Mode(bool mode) {
    dialogMode = mode;
}

void QuickGame_Graphics_Set_Wireframe_Mode(bool mode) {
    wireframeMode = mode;
}

void QuickGame_Graphics_Start_Frame() {
    guglStartFrame(list, dialogMode);

    if(cam_ptr) {
        // Set to location
        glMatrixMode(GL_VIEW);
        glLoadIdentity();

        ScePspFVector3 temp = {
            .x = -cam_ptr->position.x,
            .y = -cam_ptr->position.y,
            .z = 0,
        };

        gluTranslate(&temp);
        gluRotateZ(cam_ptr->rotation);

        glMatrixMode(GL_MODEL);
        glLoadIdentity();
    }
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

QGVMesh_t QuickGame_Graphics_Create_Mesh(const u8 type, const usize vcount, const usize icount) {
    QGVMesh_t mesh = (QGVMesh_t)QuickGame_Allocate(sizeof(QGVMesh));

    if(!mesh)
        return NULL;

    mesh->type = type;
    mesh->count = icount;
    if(type == QG_VERTEX_TYPE_TEXTURED) {
        mesh->data = QuickGame_Allocate_Aligned(16, sizeof(QGTexturedVertex) * vcount);
    } else if (type == QG_VERTEX_TYPE_COLORED) {
        mesh->data = QuickGame_Allocate_Aligned(16, sizeof(QGColoredVertex) * vcount);
    } else if (type == QG_VERTEX_TYPE_FULL) {
        mesh->data = QuickGame_Allocate_Aligned(16, sizeof(QGFullVertex) * vcount);
    } else if (type == QG_VERTEX_TYPE_SIMPLE) {
        mesh->data = QuickGame_Allocate_Aligned(16, sizeof(QGSimpleVertex) * vcount);
    } else {
        QuickGame_Destroy(mesh);
        return NULL;
    }
    mesh->indices = (u16*)QuickGame_Allocate_Aligned(16, sizeof(u16) * icount);

    if(!mesh->data) {
        QuickGame_Destroy(mesh);
        QuickGame_Destroy(mesh->indices);
        return NULL;
    }

    if(!mesh->indices) {
        QuickGame_Destroy(mesh->data);
        QuickGame_Destroy(mesh);
        return NULL;
    }

    return mesh;
}

void QuickGame_Graphics_Destroy_Mesh(QGVMesh_t* mesh) {
    if(!mesh)
        return;
    
    QuickGame_Destroy((*mesh)->data);
    QuickGame_Destroy((*mesh)->indices);
    QuickGame_Destroy(*mesh);
    *mesh = NULL;
}


void QuickGame_Graphics_Draw_Mesh(QGVMesh_t mesh) {
    if(!mesh || !mesh->data || !mesh->indices)
        return;
    
    usize vtype = GL_INDEX_16BIT | GL_VERTEX_32BITF | GL_TRANSFORM_3D;

    if(mesh->type == QG_VERTEX_TYPE_TEXTURED){
        glEnable(GL_TEXTURE_2D);
        vtype |= GL_TEXTURE_32BITF;
    } else if (mesh->type == QG_VERTEX_TYPE_COLORED) {
        glDisable(GL_TEXTURE_2D);
        vtype |= GL_COLOR_8888;
        QuickGame_Texture_Unbind();
    } else if (mesh->type == QG_VERTEX_TYPE_FULL) {
        glEnable(GL_TEXTURE_2D);
        vtype |= GL_TEXTURE_32BITF | GL_COLOR_8888;
    } else if (mesh->type == QG_VERTEX_TYPE_SIMPLE) {
        glDisable(GL_TEXTURE_2D);  
    } else {
        return;
    }

    int mode = GL_TRIANGLES;
    if(wireframeMode)
        mode = GL_LINE_STRIP;

    glDrawElements(mode, vtype, mesh->count, mesh->indices, mesh->data);
}

void QuickGame_Graphics_Set2D() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, 480.0f, 0.0f, 272.0f, -30.0f, 30.0f);

    glMatrixMode(GL_VIEW);
    glLoadIdentity();

    glMatrixMode(GL_MODEL);
    glLoadIdentity();
}


void QuickGame_Graphics_Set_Camera(QGCamera2D* camera) {
    cam_ptr = camera;
}

void QuickGame_Graphics_Unset_Camera() {
    cam_ptr = NULL;
}