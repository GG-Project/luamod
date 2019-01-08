#include "luai.h"
#include "utils.h"
#include <eiface.h>
#include "lu_utils.h"
#include "build.h"
#include <luamod.h>
#include <extdll.h>
#include <meta_api.h>
#include <stddef.h>

#include "player.h"

extern LUAMOD_PLAYER_DATA PLAYERS[32];

void lm_utils::init_api(lua_State *L) {
    lua_register(L, "hud_message_all", l_hud_message);
    //players[]
    lua_register(L, "get_authid_by_edict", l_get_authid_by_edict);
    lua_register(L, "is_player", l_is_player);
    lua_register(L, "get_offset", l_get_offset);
    lua_register(L, "luamod_version", l_version);
    lua_register(L, "get_cvar", l_get_cvar);
    lua_register(L, "get_cvar2", l_get_cvar2);
    lua_register(L, "get_entity_keyvalue", l_get_entity_key_value);
    lua_register(L, "write_log", l_write_logfile);
    //
    // lua_register(L, "", );
}

int lm_utils::l_hud_message(lua_State *L)
{
     int gmsgHudText = REG_USER_MSG("HudText", -1);
     MESSAGE_BEGIN( MSG_BROADCAST, gmsgHudText);
     WRITE_STRING( luaL_checkstring(L, 1) );
     MESSAGE_END();
     return 0;
}

// string authid = get_authid_by_edict(E)
int lm_utils::l_get_authid_by_edict(lua_State *L)
{
    edict_t *edict = (edict_t*) lua_touserdata(L,1);
    lua_pushstring(L, GETPLAYERAUTHID(edict));
    return 1;
}

// is_player(E) ?
// todo : переделать если возможно
int lm_utils::l_is_player(lua_State *L)
{
    edict_t *edict = (edict_t *) lua_touserdata(L, 1);

    int is_player = 0;
    for (int i = 0; i <= 31; i++)
    {
        if(PLAYERS[i].player_edict == edict)
        {
            is_player = 1;
            break;
        }
    }
    lua_pushnumber(L, is_player);
    return 1;
}

int lm_utils::l_get_offset(lua_State *L)
{ 
    ALERT(at_console, "Entvars offset 0x%x\n", (int)offsetof(struct edict_s, v));
    return 0;
}

int lm_utils::l_version(lua_State* L)
{
    lua_pushstring(L, LM_buildversion());
    return 1;
}

extern NEW_DLL_FUNCTIONS g_NewDllFunctionTable_Post;

#include <utils.h>

// get_cvar(edict, "cvar") - return value from callback 
// Maybe remove this shit
int lm_utils::l_get_cvar(lua_State* L)
{
    QUERY_CLIENT_CVAR_VALUE((edict_t*)lua_touserdata(L,1), luaL_checkstring(L, 2));
    return 1;
}

// get_cvar2(edict, cvar, reqid)
int lm_utils::l_get_cvar2(lua_State* L)
{
    QUERY_CLIENT_CVAR_VALUE2((edict_t*)lua_touserdata(L,1), luaL_checkstring(L, 2), luaL_checknumber(L, 3));
    return 1;
}

int lm_utils::l_get_entity_key_value(lua_State* L)
{
    ALERT( at_console, "Hmm interesting : %s\n", g_engfuncs.pfnGetInfoKeyBuffer((edict_t *)lua_touserdata(L, 1)));

    lua_pushstring(L, ENTITY_KEYVALUE((edict_t *)lua_touserdata(L, 1), (char*)luaL_checkstring(L, 2)));
    return 1;
}

#include <stdio.h>

#define LOGFILE_PATH "%s/addons/luamod/%s"

int lm_utils::l_write_logfile(lua_State* L)
{
    FILE* file = fopen(va(LOGFILE_PATH, MOD_PATH, luaL_checkstring(L, 1)), "a");

    if(!file)
      {
        luaL_error(L, "write_log: cannot open file : %s : %s\n", va(LOGFILE_PATH, MOD_PATH, luaL_checkstring(L, 1), ferror(file)));
        return 0;
      }

    fseek(file, 0, SEEK_END);

    fprintf(file, "%s", luaL_checkstring(L, 2));

    fclose(file);

    return 1;
}
