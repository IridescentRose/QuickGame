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
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <luaconf.h>
#include <pspdebug.h>
#include <pspctrl.h>

static int lua_print(lua_State* L) {
    pspDebugScreenInit();
    pspDebugScreenSetXY(0, 0);

    int argc = lua_gettop(L);
    int n;
    for (n = 1; n <= argc; n++) pspDebugScreenPrintf("%s\n", lua_tostring(L, n));
    return 0;
}

lua_State *L;

/**
 * @brief Initialize Lua
 * 
 */
void qg_lua_init() {
    L = luaL_newstate();
	luaL_openlibs(L);
    lua_register(L, "print", lua_print);

    //TODO: Register Libraries
    //TODO: QuickGame Lib
    //TODO: Graphics Lib
    //TODO: Primitive Lib
    //TODO: Input Lib
    //TODO:     Camera Object
    //TODO:     Mesh Object?
    //TODO:     Texture Object
    //TODO:     Sprite Object
    //TODO:     Tilemap Object
    //TODO: Timer Object
    //TODO: Audio Clip Object
}

/**
 * @brief Run Lua
 * 
 * @return int Returns Status code
 */
int qg_lua_run() {
    qg_lua_start:
    int ret_stat = luaL_loadfile(L, "script.lua");

    if(ret_stat != 0) {
        lua_close(L);
        QuickGame_Terminate();
        return 1;
    }

    ret_stat = lua_pcall(L, 0, LUA_MULTRET, 0);

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

    lua_close(L);
    return ret_stat;
}

int main() {
    if(QuickGame_Init() < 0)
        return 1;

    QuickGame_Graphics_Set2D();

    qg_lua_init();

    int r = qg_lua_run();
    if(r != 0)
        return r; 
    
    QuickGame_Terminate();
    return 0;
}