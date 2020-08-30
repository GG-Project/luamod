#include "luamod_types.h"

void lua_pushvec3_t(lua_State *L, float *vector)
{
    lua_newtable(L);
    lua_pushnumber(L, 1);
    lua_pushnumber(L, vector[0]);
    lua_pushnumber(L, 2);
    lua_pushnumber(L, vector[1]);
    lua_pushnumber(L, 3);
    lua_pushnumber(L, vector[2]);
    lua_settable(L, -3);
}

void lua_pushedict(lua_State *L, edict_t *ed)
{
    lua_pushlightuserdata(L, ed);
}

edict_t *luaL_checkedict(lua_State *L, int index, bool can_nullptr)
{
    if(!lua_islightuserdata(L, index))
    {
        luaL_argerror(L, index, "not a edict");
        return nullptr;
    }

    // maybe function allow null pointer
    if(can_nullptr && lua_touserdata(L, index) == nullptr)
    {
        return nullptr;
    } else {
        luaL_argerror(L, index, "edict pointer == nullptr");
        return nullptr;
    }

    edict_t *ed = (edict_t*)lua_touserdata(L, index);
    return ed;
}
