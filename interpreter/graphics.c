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

static int lua_qg_set2D(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 0)
        return luaL_error(L, "Error: Graphics.set2D() takes 0 arguments.");

    QuickGame_Graphics_Set2D();

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
    {"set2D", lua_qg_set2D},
    //TODO: {"set_camera", lua_qg_set_camera},
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

static int lua_qg_draw_rectangle(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 6)
        return luaL_error(L, "Error: Primitive.draw_rectangle(x, y, w, h, color, rotation) takes 6 arguments.");

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

    return 0;
}

static int lua_qg_draw_triangle(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 6)
        return luaL_error(L, "Error: Primitive.draw_triangle(x, y, w, h, color, rotation) takes 6 arguments.");

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

    return 0;
}

static int lua_qg_draw_circle(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 6)
        return luaL_error(L, "Error: Primitive.draw_circle(x, y, w, h, color, rotation) takes 6 arguments.");

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