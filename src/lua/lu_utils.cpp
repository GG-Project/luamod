#include "luai.h"
#include "utils.h"
#include "lu_utils.h"
#include "build.h"
#include <luamod.h>
#include <extdll.h>
#include <meta_api.h>
#include <stddef.h>

extern LUAMOD_PLAYER_DATA PLAYERS[32];

void lm_utils::init_api(lua_State *L) {
    lua_register(L, "hud_message_all", l_hud_message);
    //players[]
    lua_register(L, "get_authid_by_edict", l_get_authid_by_edict);
    lua_register(L, "is_player", l_is_player);
    lua_register(L, "get_offset", l_get_offset);
    lua_register(L, "luamod_version", l_version);
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
    int i;
    int is_player = 0;
    for (i = 0; i < 32; i++)
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