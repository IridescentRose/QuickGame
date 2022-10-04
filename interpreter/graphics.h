#include <QuickGame.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <luaconf.h>
#include <pspdebug.h>
#include <pspctrl.h>

#ifndef GRAPHICS_INCLUDED_H
#define GRAPHICS_INCLUDED_H

void initialize_graphics(lua_State* L);
void initialize_primitive(lua_State* L);
void initialize_camera(lua_State* L);
void initialize_transform(lua_State* L);

#endif