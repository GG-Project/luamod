#include "lu_luamod.h"
#include "build.h"

void lu_luamod::init_api(lua_State *L)
{
    lua_register(L, "luamod_version", l_version);

    lua_pushfstring(L, MOD_PATH);
    lua_setglobal(L, "MOD_PATH");
}

int lu_luamod::l_version(lua_State *L)
{
    lua_pushstring(L, LM_buildversion());
    return 1;
}
