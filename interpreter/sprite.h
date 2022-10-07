#include <QuickGame.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <luaconf.h>
#include <pspdebug.h>
#include <pspctrl.h>

#ifndef SPRITE_INCLUDED_H
#define SPRITE_INCLUDED_H

void initialize_sprite(lua_State* L);
void initialize_texture(lua_State* L);

void initialize_tilemap(lua_State* L);

#endif