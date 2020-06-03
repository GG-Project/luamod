#include "lu_utils.h"
#include "luai.h"
#include "utils.h"
#include <eiface.h>
#include <extdll.h>
#include <luamod.h>
#include <meta_api.h>
#include <stddef.h>
#include <luamod_types.h>
#include <player.h>

extern LUAMOD_PLAYER_DATA PLAYERS[32];

void lm_utils::init_api(lua_State *L)
{
    // players[]
    lua_register(L, "is_player", l_is_player);
    lua_register(L, "get_entity_keyvalue", l_get_entity_key_value);
}

// is_player(E) ?
// todo : переделать если возможно
int lm_utils::l_is_player(lua_State *L)
{
    edict_t *edict = (edict_t *)lua_touserdata(L, 1);

    int is_player = 0;
    for (int i = 0; i <= 31; i++) {
        if (PLAYERS[i].player_edict == edict) {
            is_player = 1;
            break;
        }
    }
    lua_pushnumber(L, is_player);
    return 1;
}

#include <utils.h>

int lm_utils::l_get_entity_key_value(lua_State *L)
{
    // g_engfuncs.pfnGetInfoKeyBuffer((edict_t *)lua_touserdata(L, 1)));
    lua_pushstring(L, ENTITY_KEYVALUE(luaL_checkedict(L, 1, 0), (char *)luaL_checkstring(L, 2)));
    return 1;
}
