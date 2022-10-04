#include <QuickGame.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <luaconf.h>
#include <pspdebug.h>
#include <pspctrl.h>

#ifndef AUDIO_INCLUDED_H
#define AUDIO_INCLUDED_H

void initialize_audio(lua_State* L);

#endif