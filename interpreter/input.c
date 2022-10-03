#include "input.h"

static int lua_qg_input_update(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 0)
        return luaL_error(L, "Error: Input.update() takes 0 arguments.");

    QuickGame_Input_Update();

    return 0;
}

static int lua_qg_button_pressed(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 1)
        return luaL_error(L, "Error: Input.button_pressed() takes 1 arguments.");

    int button = luaL_checkinteger(L, 1);
    bool b = QuickGame_Button_Pressed(button);

    lua_pushboolean(L, b);
    return 1;
}

static int lua_qg_button_released(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 1)
        return luaL_error(L, "Error: Input.button_released() takes 1 arguments.");

    int button = luaL_checkinteger(L, 1);
    bool b = QuickGame_Button_Released(button);

    lua_pushboolean(L, b);
    return 1;
}

static int lua_qg_button_held(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 1)
        return luaL_error(L, "Error: Input.button_held() takes 1 arguments.");

    int button = luaL_checkinteger(L, 1);
    bool b = QuickGame_Button_Held(button);

    lua_pushboolean(L, b);
    return 1;
}

static int lua_qg_analogx(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 0)
        return luaL_error(L, "Error: Input.analog_x() takes 0 arguments.");

    f32 x = QuickGame_Analog_X();

    lua_pushnumber(L, x);
    return 1;
}

static int lua_qg_analogy(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 0)
        return luaL_error(L, "Error: Input.analog_y() takes 0 arguments.");

    f32 y = QuickGame_Analog_Y();

    lua_pushnumber(L, y);
    return 1;
}

static const luaL_Reg inputLib[] = {
	{"update", lua_qg_input_update},
	{"button_pressed", lua_qg_button_pressed},
	{"button_released", lua_qg_button_released},
	{"button_held", lua_qg_button_held},
	{"analog_x", lua_qg_analogx},
	{"analog_y", lua_qg_analogy},
	{0, 0}
};

void initialize_input(lua_State* L) {
    lua_getglobal(L, "Input");

    if(lua_isnil(L, -1)){
        lua_pop(L, 1);
        lua_newtable(L);
    }

    luaL_setfuncs(L, inputLib, 0);
    lua_setglobal(L, "Input");

    lua_pushinteger(L, PSP_CTRL_CROSS);
    lua_setglobal(L, "PSP_CROSS");
    lua_pushinteger(L, PSP_CTRL_CIRCLE);
    lua_setglobal(L, "PSP_CIRCLE");
    lua_pushinteger(L, PSP_CTRL_SQUARE);
    lua_setglobal(L, "PSP_SQUARE");
    lua_pushinteger(L, PSP_CTRL_TRIANGLE);
    lua_setglobal(L, "PSP_TRIANGLE");

    lua_pushinteger(L, PSP_CTRL_LEFT);
    lua_setglobal(L, "PSP_LEFT");
    lua_pushinteger(L, PSP_CTRL_RIGHT);
    lua_setglobal(L, "PSP_RIGHT");
    lua_pushinteger(L, PSP_CTRL_UP);
    lua_setglobal(L, "PSP_UP");
    lua_pushinteger(L, PSP_CTRL_DOWN);
    lua_setglobal(L, "PSP_DOWN");


    lua_pushinteger(L, PSP_CTRL_LTRIGGER);
    lua_setglobal(L, "PSP_LTRIGGER");
    lua_pushinteger(L, PSP_CTRL_RTRIGGER);
    lua_setglobal(L, "PSP_RTRIGGER");
    lua_pushinteger(L, PSP_CTRL_SELECT);
    lua_setglobal(L, "PSP_SELECT");
    lua_pushinteger(L, PSP_CTRL_START);
    lua_setglobal(L, "PSP_START");
    
}