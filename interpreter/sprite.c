#include "sprite.h"

static int lua_qg_texture_load(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 3)
        return luaL_error(L, "Error: Texture.load() takes 3 arguments.");

    QGTexture_t* texture = lua_newuserdata(L,sizeof(QGTexture_t));

    const char* filename = luaL_checkstring(L, 1);
    bool flip  = luaL_checkint(L, 2);
    bool vram = luaL_checkint(L, 3);

    *texture = QuickGame_Texture_Load(filename, flip, vram);

    luaL_getmetatable(L, "Texture");
    lua_setmetatable(L, -2); 

    return 1;
}

QGTexture_t* getTex(lua_State* L){
    return (QGTexture_t*)luaL_checkudata(L, 1, "Texture");
}
QGTexture_t* getTexn(lua_State* L, int n){
    return (QGTexture_t*)luaL_checkudata(L, n, "Texture");
}

static int lua_qg_texture_destroy(lua_State* L) {
    QGTexture_t* tex = getTex(L);
    QuickGame_Destroy(tex);

    return 0;
}


static int lua_qg_texture_bind(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 1)
        return luaL_error(L, "Error: Texture:bind() takes 1 arguments.");

    QGTexture_t texture = *getTex(L);

    QuickGame_Texture_Bind(texture);

    return 0;
}

static int lua_qg_texture_unbind(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 1)
        return luaL_error(L, "Error: Texture:unbind() takes 1 arguments.");

    QGTexture_t texture = *getTex(L);

    QuickGame_Texture_Unbind();

    return 0;
}

static const luaL_Reg textureLib[] = {
	{"load", lua_qg_texture_load},
	{"destroy", lua_qg_texture_destroy},
	{"bind", lua_qg_texture_bind},
	{"unbind", lua_qg_texture_unbind},
	{0,0}
};

static const luaL_Reg textureMetaLib[] = {
	{"__gc", lua_qg_texture_destroy},
	{0,0}
};

void initialize_texture(lua_State* L) {
    int lib_id, meta_id;

    // new class = {}
    lua_createtable(L, 0, 0);
    lib_id = lua_gettop(L);

    // meta table = {}
    luaL_newmetatable(L, "Texture");
    meta_id = lua_gettop(L);
    luaL_setfuncs(L, textureMetaLib, 0);

    // meta table = methods
    luaL_newlib(L, textureLib);
    lua_setfield(L, meta_id, "__index");  

    // meta table.metatable = metatable
    luaL_newlib(L, textureMetaLib);
    lua_setfield(L, meta_id, "__metatable");

    // class.metatable = metatable
    lua_setmetatable(L, lib_id);

    // AudioClip
    lua_setglobal(L, "Texture");
}

static int lua_qg_sprite_create(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 5)
        return luaL_error(L, "Error: Sprite.create() takes 5 arguments.");

    QGSprite_t* sprite = lua_newuserdata(L,sizeof(QGSprite_t));

    int x = luaL_checkint(L, 1);
    int y = luaL_checkint(L, 2);
    int w = luaL_checkint(L, 3);
    int h = luaL_checkint(L, 4);

    QGTexture_t tex = *getTexn(L,5);

    *sprite = QuickGame_Sprite_Create_Alt(x, y, w, h, tex);

    luaL_getmetatable(L, "Sprite");
    lua_setmetatable(L, -2); 

    return 1;
}

QGSprite_t* getSprite(lua_State* L){
    return (QGSprite_t*)luaL_checkudata(L, 1, "Sprite");
}

QGSprite_t* getSpriten(lua_State* L, int n){
    return (QGSprite_t*)luaL_checkudata(L, n, "Sprite");
}

static int lua_qg_sprite_destroy(lua_State* L) {
    QGSprite_t* sprite = getSprite(L);
    QuickGame_Sprite_Destroy(sprite);

    return 0;
}

static int lua_qg_sprite_draw(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 1)
        return luaL_error(L, "Error: Sprite:draw() takes 1 arguments.");

    QGSprite_t sprite = *getSprite(L);

    QuickGame_Sprite_Draw(sprite);

    return 0;
}

static int lua_qg_sprite_intersects(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 2)
        return luaL_error(L, "Error: Sprite:intersects() takes 2 arguments.");

    QGSprite_t sprite1 = *getSpriten(L,1);
    QGSprite_t sprite2 = *getSpriten(L, 2);

    bool i = QuickGame_Sprite_Intersects(sprite1, sprite2);

    lua_pushboolean(L, i);
    return 1;
}


static int lua_qg_sprite_set_position(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 3)
        return luaL_error(L, "Error: Sprite:set_position() takes 3 arguments.");

    QGSprite_t sprite1 = *getSpriten(L,1);
    int x = luaL_checkint(L, 2);
    int y = luaL_checkint(L, 3);

    sprite1->transform.position.x = x;
    sprite1->transform.position.y = y;

    return 0;
}
static int lua_qg_sprite_set_scale(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 3)
        return luaL_error(L, "Error: Sprite:set_scale() takes 3 arguments.");

    QGSprite_t sprite1 = *getSpriten(L,1);
    int w = luaL_checkint(L, 2);
    int h = luaL_checkint(L, 3);

    sprite1->transform.scale.x = w;
    sprite1->transform.scale.y = h;

    return 0;
}

static int lua_qg_sprite_set_rotation(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 2)
        return luaL_error(L, "Error: Sprite:set_rotation() takes 2 arguments.");

    QGSprite_t sprite1 = *getSpriten(L,1);
    f32 rot = luaL_checknumber(L, 2);

    sprite1->transform.rotation = rot;

    return 0;
}

static int lua_qg_sprite_set_layer(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 2)
        return luaL_error(L, "Error: Sprite:set_layer() takes 2 arguments.");

    QGSprite_t sprite1 = *getSpriten(L,1);
    int layer = luaL_checkint(L, 2);

    sprite1->layer = layer;

    return 0;
}


static int lua_qg_sprite_set_color(lua_State* L) {
    int argc = lua_gettop(L);
    if (argc != 2)
        return luaL_error(L, "Error: Sprite:set_color() takes 2 arguments.");

    QGSprite_t sprite1 = *getSpriten(L,1);
    int color = luaL_checkint(L, 2);

    sprite1->color.color = color;

    return 0;
}


static const luaL_Reg spriteLib[] = {
	{"create", lua_qg_sprite_create},
	{"destroy", lua_qg_sprite_destroy},
	{"draw", lua_qg_sprite_draw},
	{"intersects", lua_qg_sprite_intersects},
	{"set_position", lua_qg_sprite_set_position},
	{"set_rotation", lua_qg_sprite_set_rotation},
	{"set_scale", lua_qg_sprite_set_scale},
	{"set_layer", lua_qg_sprite_set_layer},
	{"set_color", lua_qg_sprite_set_color},
	{0,0}
};

static const luaL_Reg spriteMetaLib[] = {
	{"__gc", lua_qg_sprite_destroy},
	{0,0}
};

void initialize_sprite(lua_State* L) {
    int lib_id, meta_id;

    // new class = {}
    lua_createtable(L, 0, 0);
    lib_id = lua_gettop(L);

    // meta table = {}
    luaL_newmetatable(L, "Sprite");
    meta_id = lua_gettop(L);
    luaL_setfuncs(L, spriteMetaLib, 0);

    // meta table = methods
    luaL_newlib(L, spriteLib);
    lua_setfield(L, meta_id, "__index");  

    // meta table.metatable = metatable
    luaL_newlib(L, spriteMetaLib);
    lua_setfield(L, meta_id, "__metatable");

    // class.metatable = metatable
    lua_setmetatable(L, lib_id);

    // AudioClip
    lua_setglobal(L, "Sprite");
}