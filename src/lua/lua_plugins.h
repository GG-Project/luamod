#pragma once
#include <luamod.h>
#include <extdll.h>
#include <meta_api.h>

#include <luai.h>

#define MAX_LEN 128

struct luamod_plugin_s {
    char author[MAX_LEN];
    char name[MAX_LEN];
    char description[MAX_LEN];
    char version[MAX_LEN];
    char filename[MAX_LEN];

    lua_State *L;

    qboolean running; // plugin is running or not ?
    qboolean registred; // check register_plugin
    luamod_plugin_s *m_next;
};

typedef luamod_plugin_s luamod_plugin_t;

#undef MAX_LEN

luamod_plugin_t *find_plugin_by_luastate(lua_State *L);
void plugin_pcall(lua_State *L, int nargs, int rets);
bool plugin_have_event(lua_State *L, const char *event);
