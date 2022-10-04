#include "graphics.h"

static int lua_qg_start_frame(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 0)
        return luaL_error(L, "Error: Graphics.start_frame() takes 0 arguments.");

    QuickGame_Graphics_Start_Frame();

    return 0;
}

static int lua_qg_clear(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 0)
        return luaL_error(L, "Error: Graphics.clear() takes 0 arguments.");

    QuickGame_Graphics_Clear();

    return 0;
}

static int lua_qg_set_clear_color(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 1)
        return luaL_error(L, "Error: Graphics.set_clear_color() takes 1 argument.");

    int color = luaL_checkint(L, 1);

    QGColor col;
    col.color = color;

    QuickGame_Graphics_Set_Clear_Color(col);

    return 0;
}

static int lua_qg_end_frame(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 1)
        return luaL_error(L, "Error: Graphics.end_frame() takes 1 argument.");

    bool b = lua_toboolean(L, 1);

    QuickGame_Graphics_End_Frame(b);

    return 0;
}

static int lua_qg_set_dialog_mode(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 1)
        return luaL_error(L, "Error: Graphics.set_dialog_mode() takes 1 argument.");

    bool b = lua_toboolean(L, 1);

    QuickGame_Graphics_Set_Dialog_Mode(b);

    return 0;
}

static int lua_qg_set_wireframe_mode(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 1)
        return luaL_error(L, "Error: Graphics.set_wireframe_mode() takes 1 argument.");

    bool b = lua_toboolean(L, 1);

    QuickGame_Graphics_Set_Wireframe_Mode(b);

    return 0;
}

static int lua_qg_set2D(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 0)
        return luaL_error(L, "Error: Graphics.set2D() takes 0 arguments.");

    QuickGame_Graphics_Set2D();

    return 0;
}

static int lua_qg_set_camera(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 1)
        return luaL_error(L, "Error: Graphics.set_camera() takes 1 argument.");

    QuickGame_Graphics_Set_Camera(luaL_checkudata(L, 1, "Camera"));

    return 0;
}

static int lua_qg_unset_camera(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 0)
        return luaL_error(L, "Error: Graphics.unset_camera() takes 0 arguments.");

    QuickGame_Graphics_Unset_Camera();

    return 0;
}

static const luaL_Reg graphicsLib[] = {
	{"start_frame", lua_qg_start_frame},
    {"set_clear_color", lua_qg_set_clear_color},
    {"clear", lua_qg_clear},
	{"end_frame", lua_qg_end_frame},
	{"set_dialog_mode", lua_qg_set_dialog_mode},
	{"set_wireframe_mode", lua_qg_set_wireframe_mode},
    {"set2D", lua_qg_set2D},
    {"set_camera", lua_qg_set_camera},
    {"unset_camera", lua_qg_unset_camera},
	{0, 0}
};


static int lua_qg_color_create(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 4)
        return luaL_error(L, "Error: Color.create() takes 4 arguments.");

    int r = luaL_checkint(L, 1);
    int g = luaL_checkint(L, 2);
    int b = luaL_checkint(L, 3);
    int a = luaL_checkint(L, 4);

    QGColor color;
    color.rgba.r = r;
    color.rgba.g = g;
    color.rgba.b = b;
    color.rgba.a = a;

    lua_pushinteger(L, color.color);

    return 1;
}

static const luaL_Reg colorLib[] = {
	{"create", lua_qg_color_create},
	{0, 0}
};

void initialize_graphics(lua_State* L){
    lua_getglobal(L, "Color");

    if(lua_isnil(L, -1)){
        lua_pop(L, 1);
        lua_newtable(L);
    }

    luaL_setfuncs(L, colorLib, 0);
    lua_setglobal(L, "Color");

    lua_getglobal(L, "Graphics");

    if(lua_isnil(L, -1)){
        lua_pop(L, 1);
        lua_newtable(L);
    }

    luaL_setfuncs(L, graphicsLib, 0);
    lua_setglobal(L, "Graphics");
}

QGTransform2D* getQGTransform(lua_State* L){
    return (QGTransform2D*)luaL_checkudata(L, 1, "Transform");
}
QGTransform2D* getQGTransformn(lua_State* L, int n){
    return (QGTransform2D*)luaL_checkudata(L, n, "Transform");
}

static int lua_qg_draw_rectangle(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc == 6){
        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        float w = luaL_checknumber(L, 3);
        float h = luaL_checknumber(L, 4);

        int color = luaL_checkint(L, 5);
        QGColor col;
        col.color = color;

        float rotation = luaL_checknumber(L, 6);

        QGTransform2D transform = {
            .position = {.x = x, .y = y},
            .scale = {.x = w, .y = h},
            .rotation = rotation
        };

        QuickGame_Primitive_Draw_Rectangle(transform, col);
    } else if(argc == 2) {
        QGTransform2D transform = *getQGTransformn(L, 1);

        int color = luaL_checkint(L, 2);
        QGColor col;
        col.color = color;

        QuickGame_Primitive_Draw_Rectangle(transform, col);
    } else {
        return luaL_error(L, "Error: Primitive.draw_rectangle(x, y, w, h, color, rotation) takes 6 arguments.");
    }

    return 0;
}

static int lua_qg_draw_triangle(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc == 6){
        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        float w = luaL_checknumber(L, 3);
        float h = luaL_checknumber(L, 4);

        int color = luaL_checkint(L, 5);
        QGColor col;
        col.color = color;

        float rotation = luaL_checknumber(L, 6);

        QGTransform2D transform = {
            .position = {.x = x, .y = y},
            .scale = {.x = w, .y = h},
            .rotation = rotation
        };

        QuickGame_Primitive_Draw_Triangle(transform, col);
    } else if(argc == 2) {
        QGTransform2D transform = *getQGTransformn(L, 1);

        int color = luaL_checkint(L, 2);
        QGColor col;
        col.color = color;

        QuickGame_Primitive_Draw_Triangle(transform, col);
    } else {
        return luaL_error(L, "Error: Primitive.draw_triangle(x, y, w, h, color, rotation) takes 6 arguments.");
    }

    return 0;
}

static int lua_qg_draw_circle(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc == 6){
        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        float w = luaL_checknumber(L, 3);
        float h = luaL_checknumber(L, 4);

        int color = luaL_checkint(L, 5);
        QGColor col;
        col.color = color;

        float rotation = luaL_checknumber(L, 6);

        QGTransform2D transform = {
            .position = {.x = x, .y = y},
            .scale = {.x = w, .y = h},
            .rotation = rotation
        };

        QuickGame_Primitive_Draw_Circle(transform, col);
    } else if(argc == 2) {
        QGTransform2D transform = *getQGTransformn(L, 1);

        int color = luaL_checkint(L, 2);
        QGColor col;
        col.color = color;

        QuickGame_Primitive_Draw_Circle(transform, col);
    } else {
        return luaL_error(L, "Error: Primitive.draw_circle(x, y, w, h, color, rotation) takes 6 arguments.");
    }

    return 0;
}

static const luaL_Reg primitiveLib[] = {
	{"draw_rectangle", lua_qg_draw_rectangle},
	{"draw_triangle", lua_qg_draw_triangle},
	{"draw_circle", lua_qg_draw_circle},
	{0, 0}
};

void initialize_primitive(lua_State* L) {
    lua_getglobal(L, "Primitive");

    if(lua_isnil(L, -1)){
        lua_pop(L, 1);
        lua_newtable(L);
    }

    luaL_setfuncs(L, primitiveLib, 0);
    lua_setglobal(L, "Primitive");
}

static int lua_qg_camera_create(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 0)
        return luaL_error(L, "Error: Camera.create() takes 0 arguments.");

    QGCamera2D* cam = lua_newuserdata(L,sizeof(QGCamera2D));
    cam->position.x = 0;
    cam->position.y = 0;
    cam->rotation = 0.0f;

    luaL_getmetatable(L, "Camera");
    lua_setmetatable(L, -2); 

    return 1;
}

QGCamera2D* getQGCamera(lua_State* L){
    return (QGCamera2D*)luaL_checkudata(L, 1, "Camera");
}

static int lua_qg_camera_destroy(lua_State* L) {
    QGCamera2D* camera = getQGCamera(L);
    QuickGame_Destroy(&camera);

    return 0;
}

static int lua_qg_camera_set_pos(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 3)
        return luaL_error(L, "Error: Camera:set_position() takes 3 arguments.");

    QGCamera2D* camera = getQGCamera(L);
    camera->position.x = luaL_checknumber(L, 2);
    camera->position.y = luaL_checknumber(L, 3);

    return 0;
}

static int lua_qg_camera_set_rot(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 2)
        return luaL_error(L, "Error: Camera:set_rotation() takes 2 arguments.");

    QGCamera2D* camera = getQGCamera(L);
    camera->rotation = luaL_checknumber(L, 2) / 180.0f * 3.14159f;

    return 0;
}


static const luaL_Reg cameraLib[] = { // Timer methods
	{"create", lua_qg_camera_create},
	{"destroy", lua_qg_camera_destroy},
	{"set_rotation", lua_qg_camera_set_rot},
	{"set_position", lua_qg_camera_set_pos},
	{0,0}
};

static const luaL_Reg cameraMetaLib[] = {
	{"__gc", lua_qg_camera_destroy},
	{0,0}
};

void initialize_camera(lua_State* L){
    int lib_id, meta_id;

    // new class = {}
    lua_createtable(L, 0, 0);
    lib_id = lua_gettop(L);

    // meta table = {}
    luaL_newmetatable(L, "Camera");
    meta_id = lua_gettop(L);
    luaL_setfuncs(L, cameraMetaLib, 0);

    // meta table = methods
    luaL_newlib(L, cameraLib);
    lua_setfield(L, meta_id, "__index");  

    // meta table.metatable = metatable
    luaL_newlib(L, cameraMetaLib);
    lua_setfield(L, meta_id, "__metatable");

    // class.metatable = metatable
    lua_setmetatable(L, lib_id);

    // Camera
    lua_setglobal(L, "Camera");
}


static int lua_qg_transform_create(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 0)
        return luaL_error(L, "Error: Transform.create() takes 0 arguments.");

    QGTransform2D* t = lua_newuserdata(L,sizeof(QGTransform2D));
    t->position.x = 0;
    t->position.y = 0;
    t->rotation = 0.0f;
    t->scale.x = 0;
    t->scale.y = 0;

    luaL_getmetatable(L, "Transform");
    lua_setmetatable(L, -2); 

    return 1;
}

static int lua_qg_transform_destroy(lua_State* L) {
    QGTransform2D* t = getQGTransform(L);
    QuickGame_Destroy(&t);

    return 0;
}

static int lua_qg_transform_set_position(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 3)
        return luaL_error(L, "Error: Transform:set_position() takes 3 arguments.");

    QGTransform2D* t = getQGTransform(L);
    t->position.x = luaL_checknumber(L, 2);
    t->position.y = luaL_checknumber(L, 3);

    return 0;
}

static int lua_qg_transform_set_scale(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 3)
        return luaL_error(L, "Error: Transform:set_scale() takes 3 arguments.");

    QGTransform2D* t = getQGTransform(L);
    t->scale.x = luaL_checknumber(L, 2);
    t->scale.y = luaL_checknumber(L, 3);

    return 0;
}

static int lua_qg_transform_set_rotation(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 2)
        return luaL_error(L, "Error: Transform:set_rotation() takes 2 arguments.");

    QGTransform2D* t = getQGTransform(L);
    t->rotation = luaL_checknumber(L, 2) / 180.0f * 3.14159f;

    return 0;
}
static int lua_qg_transform_intersects(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 2)
        return luaL_error(L, "Error: Transform:intersects() takes 2 arguments.");

    QGTransform2D* t1 = getQGTransformn(L, 1);
    QGTransform2D* t2 = getQGTransformn(L, 2);

    bool b = QuickGame_Intersect_Transform(*t1, *t2);

    lua_pushboolean(L, b);
    return 1;
}

static const luaL_Reg transformLib[] = { // Timer methods
	{"create", lua_qg_transform_create},
	{"destroy", lua_qg_transform_destroy},
	{"set_rotation", lua_qg_transform_set_rotation},
	{"set_position", lua_qg_transform_set_position},
	{"set_scale", lua_qg_transform_set_scale},
    {"intersects", lua_qg_transform_intersects},
	{0,0}
};

static const luaL_Reg transformMetaLib[] = {
	{"__gc", lua_qg_transform_destroy},
	{0,0}
};

void initialize_transform(lua_State* L){
    int lib_id, meta_id;

    // new class = {}
    lua_createtable(L, 0, 0);
    lib_id = lua_gettop(L);

    // meta table = {}
    luaL_newmetatable(L, "Transform");
    meta_id = lua_gettop(L);
    luaL_setfuncs(L, transformMetaLib, 0);

    // meta table = methods
    luaL_newlib(L, transformLib);
    lua_setfield(L, meta_id, "__index");  

    // meta table.metatable = metatable
    luaL_newlib(L, transformMetaLib);
    lua_setfield(L, meta_id, "__metatable");

    // class.metatable = metatable
    lua_setmetatable(L, lib_id);

    // Transform
    lua_setglobal(L, "Transform");
}