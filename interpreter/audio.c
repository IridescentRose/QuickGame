#include "audio.h"

static int lua_qg_audio_load(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 3)
        return luaL_error(L, "Error: AudioClip.load() takes 3 arguments.");

    QGAudioClip** audio = lua_newuserdata(L,sizeof(QGAudioClip*));

    const char* filename = luaL_checkstring(L, 1);
    bool looping  = luaL_checkint(L, 2);
    bool streaming = luaL_checkint(L, 3);

    *audio = QuickGame_Audio_Load(filename, looping, streaming);

    luaL_getmetatable(L, "AudioClip");
    lua_setmetatable(L, -2); 

    return 1;
}

QGAudioClip** getClip(lua_State* L){
    return (QGAudioClip**)luaL_checkudata(L, 1, "AudioClip");
}

static int lua_qg_audio_destroy(lua_State* L) {
    QGAudioClip** clip = getClip(L);
    QuickGame_Destroy(clip);

    return 0;
}

static int lua_qg_audio_set_volume(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 2)
        return luaL_error(L, "Error: AudioClip:set_volume() takes 2 arguments.");

    QGAudioClip_t clip = *getClip(L);
    f32 volume = luaL_checknumber(L, 2);
    QuickGame_Audio_Set_Volume(clip, volume);

    return 0;
}


static int lua_qg_audio_set_pan(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 2)
        return luaL_error(L, "Error: AudioClip:set_pan() takes 2 arguments.");

    QGAudioClip_t clip = *getClip(L);
    f32 pan = luaL_checknumber(L, 2);
    QuickGame_Audio_Set_Pan(clip, pan);

    return 0;
}


static int lua_qg_audio_set_loop(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 2)
        return luaL_error(L, "Error: AudioClip:set_loop() takes 2 arguments.");

    QGAudioClip_t clip = *getClip(L);
    int looping = lua_toboolean(L, 2);
    QuickGame_Audio_Set_Looping(clip, looping);

    return 0;
}

static int lua_qg_audio_play(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 2)
        return luaL_error(L, "Error: AudioClip:play() takes 2 arguments.");

    QGAudioClip_t clip = *getClip(L);
    int channel = luaL_checkint(L, 2);
    QuickGame_Audio_Play(clip, channel);

    return 0;
}

static int lua_qg_audio_pause(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 1)
        return luaL_error(L, "Error: AudioClip:play() takes 1 argument.");

    QGAudioClip_t clip = *getClip(L);
    QuickGame_Audio_Pause(clip);

    return 0;
}

static int lua_qg_audio_stop(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 1)
        return luaL_error(L, "Error: AudioClip:stop() takes 1 argument.");

    QGAudioClip_t clip = *getClip(L);
    QuickGame_Audio_Stop(clip);

    return 0;
}


static const luaL_Reg audioLib[] = {
	{"load", lua_qg_audio_load},
	{"destroy", lua_qg_audio_destroy},
	{"set_loop", lua_qg_audio_set_loop},
	{"set_volume", lua_qg_audio_set_pan},
	{"set_pan", lua_qg_audio_set_volume},
	{"play", lua_qg_audio_play},
	{"pause", lua_qg_audio_pause},
	{"stop", lua_qg_audio_stop},
	{0,0}
};

static const luaL_Reg audioMetaLib[] = {
	{"__gc", lua_qg_audio_destroy},
	{0,0}
};

void initialize_audio(lua_State* L) {
    int lib_id, meta_id;

    // new class = {}
    lua_createtable(L, 0, 0);
    lib_id = lua_gettop(L);

    // meta table = {}
    luaL_newmetatable(L, "AudioClip");
    meta_id = lua_gettop(L);
    luaL_setfuncs(L, audioMetaLib, 0);

    // meta table = methods
    luaL_newlib(L, audioLib);
    lua_setfield(L, meta_id, "__index");  

    // meta table.metatable = metatable
    luaL_newlib(L, audioMetaLib);
    lua_setfield(L, meta_id, "__metatable");

    // class.metatable = metatable
    lua_setmetatable(L, lib_id);

    // AudioClip
    lua_setglobal(L, "AudioClip");
}
