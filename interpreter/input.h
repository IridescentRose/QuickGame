#include <QuickGame.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <luaconf.h>
#include <pspdebug.h>
#include <pspctrl.h>

#ifndef INPUT_INCLUDED_H
#define INPUT_INCLUDED_H

void initialize_input(lua_State* L);

#endif