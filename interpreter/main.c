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

int main() {
    if(QuickGame_Init() < 0)
        return 1;

    QuickGame_Graphics_Set2D();

    lua_State *L = luaL_newstate();
	luaL_openlibs(L);

    lua_register(L, "print", lua_print);

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

    QuickGame_Terminate();
    return 0;
}