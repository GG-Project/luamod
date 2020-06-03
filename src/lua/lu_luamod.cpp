#include "lu_luamod.h"
#include "build.h"

void lu_luamod::init_api(lua_State *L)
{
    lua_pushstring(L, LM_buildversion());
    lua_setglobal(L, "LUAMOD_VERSION");

    lua_pushfstring(L, MOD_PATH);
    lua_setglobal(L, "MOD_PATH");
}
