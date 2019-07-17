#pragma once
#include "luamod.h"
#include <extdll.h>
#include <meta_api.h>

#include "luai.h"

#define MAX_LEN 128

#pragma pack(0)

struct luamod_mem_debug {
    size_t total_size;
    size_t used_now;
    size_t released;
};

typedef struct luamod_client_callback_s {
    char client_command[MAX_LEN];
    char client_function[MAX_LEN];
    struct luamod_client_callback_s *next;
} luamod_client_callback_t;

typedef struct luamod_plugin_callback_s {
    struct luamod_plugin_callback_s *next;
} luamod_plugin_callback_t;

typedef struct LUAMOD_SET_TASK_S {
    int taskid;
    qboolean loop;
    const char *name;
    const char *function_name;
    lua_State *L;
    pthread_t task_thread;
    unsigned int time_to_execute;
    int execute_count;
    struct LUAMOD_SET_TASK_S *next;
} LUAMOD_SET_TASK;

typedef struct luamod_plugin_s {
    char author[MAX_LEN];
    char name[MAX_LEN];
    char description[MAX_LEN];
    char version[MAX_LEN];
    char filename[MAX_LEN];

    lua_State *L;

    qboolean running; // plugin is running or not ?
    qboolean registred; // hack for check register_plugin
    luamod_client_callback_t *client_commands_callbacks;
    luamod_mem_debug debug_mem; // maybe store plugin used mem ?
    struct luamod_plugin_s *next;
} luamod_plugin_t;
#pragma pack(0)

#undef MAX_LEN

luamod_plugin_t *find_plugin_by_luastate(lua_State *L);
void plugin_safecall(lua_State *L, int nargs, int rets);
int plugin_have_event(lua_State *L, const char *event);
int plugin_clcmd_handler(luamod_plugin_t *ptr, edict_t *ed);
