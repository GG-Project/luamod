#include "luai.h"
#include <extdll.h>
#include <meta_api.h>
#include "luamod.h"

typedef enum {
    UNKNOWN,
    EDICT,
} luamod_types;

struct luamod_type
{
    luamod_types type;
    void *pointer;
};

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

const float *luaL_check_vec3_t(lua_State *L, int index, int can_nullptr)
{
        float vector[3] = { 0.0f, 0.0f, 0.0f };

        lua_pushnil(L);

        if (lua_istable(L, index))
        {
            for ( int i = 0; lua_next(L, 3) && i < 3; i++) {
                lua_pushvalue(L, -1);
                vector[i] = luaL_checknumber(L, -1);
                lua_pop(L, 2);
            }

            return vector;
        } else if(lua_isnil(L, index) && can_nullptr)
        {
            return nullptr;
        } else {
            luaL_argerror(L, index, "not a vec3_t");
            return nullptr;
        }
}

void lua_pushedict(lua_State *L, edict_t *ed)
{
    luamod_type *type = (luamod_type*)lua_newuserdata(L, sizeof(luamod_type));
    type->type = EDICT;
    type->pointer = ed;
}

edict_t *luaL_checkedict(lua_State *L, int index, bool can_nullptr)
{
    // maybe function can pass nullptr in edict ?
    if(can_nullptr && lua_touserdata(L, index) == nullptr)
        return nullptr;

    if(!lua_isuserdata(L, index))
    {
        luaL_argerror(L, index, "not a edict");
        return nullptr;
    }

    luamod_type *type = (luamod_type*)lua_touserdata(L, index);

    if(type->type != EDICT)
    {
        luaL_argerror(L, index, "not a edict");
        return nullptr;
    }

    if(type->pointer == nullptr && !can_nullptr)
    {
        luaL_argerror(L, index, "edict pointer == nullptr");
        return nullptr;
    }

    return (edict_t*)type->pointer;
}
