#include "lu_utils.h"
#include <luamod_types.h>
#include <utils.h>

void lm_utils::init_api(lua_State *L)
{
    lua_register(L, "get_entity_keyvalue", l_get_entity_key_value);
}

int lm_utils::l_get_entity_key_value(lua_State *L)
{
    // g_engfuncs.pfnGetInfoKeyBuffer((edict_t *)lua_touserdata(L, 1)));
    lua_pushstring(L, ENTITY_KEYVALUE(lua_checkedict(L, 1, 0), (char *)luaL_checkstring(L, 2)));
    return 1;
}
