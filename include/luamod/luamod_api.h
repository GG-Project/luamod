#pragma once

#define LUAMOD_API_VER 0.1

#include "luai.h"

struct module_info_t
{
    const char*     ifvers;     // interface version
    const char*     name;       // full name of plugin
    const char*     version;    // version
    const char*     date;       // date
    const char*     author;     // author name/email
    const char*     url;        // URL
    const char*     logtag;     // LogTag
};

extern module_info_t Module_info;

struct luamod_funcs_t
{
    const char* (*luaL_checklstring)(lua_State* L, int arg);
    int (*luaL_checkinterger)(lua_State* L, int arg);
    void *(*lua_getuserdata) (lua_State *L, int arg);
    void (*luamod_print)(const char *fmt, ...);
    void (*register_function)(lua_State *L, char *name, lua_CFunction fn);
};

typedef struct luamod_module_s
{
    module_info_t *module_info;
    int running;
    void (*register_lua_funcs)(lua_State *);
    char filename[32];
    luamod_module_s *next;
} luamod_module_t;
