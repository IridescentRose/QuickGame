/**
 * @file main.c
 * @author Nathan Bourgeois (iridescentrosesfall@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <QuickGame.h>
#include "graphics.h"
#include "input.h"

static int lua_print(lua_State* L) {
    pspDebugScreenInit();
    pspDebugScreenSetXY(0, 0);

    int argc = lua_gettop(L);
    int n;
    for (n = 1; n <= argc; n++) pspDebugScreenPrintf("%s\n", lua_tostring(L, n));
    return 0;
}

lua_State *L;

static int lua_qg_running(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 0)
        return luaL_error(L, "Error: QuickGame.running() takes 0 arguments.");

    lua_pushboolean(L, QuickGame_Running());
    return 1;
}

static int lua_qg_request_exit(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 0)
        return luaL_error(L, "Error: QuickGame.request_exit() takes 0 arguments.");

    QuickGame_Request_Exit();
    return 0;
}

static const luaL_Reg quickgameLib[] = {
	{"running", lua_qg_running},
	{"request_exit", lua_qg_request_exit},
	{0, 0}
};

/**
 * @brief QuickGame API Functions
 * 
 * @param L lua_State
 */
void initialize_quickgame(lua_State* L){
    lua_getglobal(L, "QuickGame");

    if(lua_isnil(L, -1)){
        lua_pop(L, 1);
        lua_newtable(L);
    }

    luaL_setfuncs(L, quickgameLib, 0);
    lua_setglobal(L, "QuickGame");
}

/**
 * @brief Initialize Lua
 * 
 */
void qg_lua_init() {
    L = luaL_newstate();
	luaL_openlibs(L);
    lua_register(L, "print", lua_print);

    //QuickGame Lib
    initialize_quickgame(L);

    //Graphics Lib
    initialize_graphics(L);

    //Primitive Lib
    initialize_primitive(L);

    //Input Lib
    initialize_input(L);
    
    //TODO: Timer Object
    //TODO: Audio Clip Object
    //TODO: Texture Object
    //TODO: Sprite Object
    //TODO: Camera Object (&Set)
    //TODO: Tilemap Object
}

/**
 * @brief Run Lua
 * 
 * @return int Returns Status code
 */
int qg_lua_run() {
    qg_lua_start:

    // Load file
    int ret_stat = luaL_loadfile(L, "script.lua");

    // Failure
    if(ret_stat != 0) {
        lua_close(L);
        QuickGame_Terminate();
        return 1;
    }
    
    // Run Script
    ret_stat = lua_pcall(L, 0, LUA_MULTRET, 0);

    // Error!
    if(ret_stat != 0){
        pspDebugScreenInit();
		pspDebugScreenEnableBackColor(0);
        
        while(QuickGame_Running()){
            pspDebugScreenSetXY(0,0);
		
            pspDebugScreenPrintf("Lua Error:\n%s\n", lua_tostring(L, -1));
		    pspDebugScreenPrintf("Press Start to reset.\n");
            
            QuickGame_Input_Update();

            if(QuickGame_Button_Pressed(PSP_CTRL_START))
                goto qg_lua_start;
        }
    }

    // End Game
    lua_close(L);
    return ret_stat;
}

int main() {
    // Init engine
    if(QuickGame_Init() < 0)
        return 1;

    // Set Graphics 2D
    QuickGame_Graphics_Set2D();

    // Initialize Lua
    qg_lua_init();

    // Run Lua Script
    int r = qg_lua_run();
    if(r != 0)
        return r; 
    
    // Terminate engine
    QuickGame_Terminate();
    return 0;
}