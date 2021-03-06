#include "luamod_types.h"

void lua_pushvec3_t(lua_State *L, const float *vector)
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

float *luaL_checkvec3_t(lua_State *L, int index)
{
    static float vector[3] = { 0.0f };

    if( !lua_istable(L, index) )
        luaL_argerror(L, 3, "not a vec3_t");

    if( lua_objlen(L, index) > 3 )
        luaL_argerror(L, 3, "not a vec3_t");

    lua_pushnil(L);
    for( size_t i = 0; lua_next(L, index); i++) {
        lua_pushvalue(L, -1);
        vector[i] = luaL_checknumber(L, -1);
        lua_pop(L, 2);
    }

    return vector;
}

void lua_pushedict(lua_State *L, edict_t *ed)
{
    if (ed)
    {
        lua_pushlightuserdata(L, ed);
    } else {
        lua_pushnil(L);
    }
}

edict_t *luaL_checkedict(lua_State *L, int index, bool can_nullptr)
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
