#pragma once
#include "luai.h"
#include <extdll.h> //мб будет полезно
#include <signal.h>
#include <pthread.h>

struct LUAMOD_SET_TASK
{
    const char *name;
    const char *function_name;
    pthread_t task_thread;
    lua_State *lua_state;
    float time_left_to_execute;
    float time_to_execute;
    float execute_count;
    byte execute_this;
};

struct LUAMOD_PLAYER_DATA
{
    char player_name[32];
    edict_t *player_edict;
//    char player_authid[64];
    char player_address[32];
    qboolean player_put_on_server = false;
    qboolean free = true;
};
