#include "luai.h"
#include <extdll.h>

void luaL_push_vec3_t(lua_State *L, float *vector)
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

edict_t *lua_checkedict(lua_State *L, int index, bool can_nullptr)
{
    // maybe function can pass nullptr in edict ?
    if(can_nullptr && lua_touserdata(L, index) == nullptr)
        return nullptr;

    if(!lua_islightuserdata(L, index))
    {
        luaL_argerror(L, index, "not a edict");
        return nullptr;
    }

    edict_t *ed = (edict_t*)lua_touserdata(L, index);

    if(ed == nullptr && !can_nullptr)
    {
        luaL_argerror(L, index, "edict pointer == nullptr");
        return nullptr;
    }

    return ed;
}
