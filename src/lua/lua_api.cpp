#include <luamod.h>

#include "luamod_engfuncs.h"
#include "luamod_global.h"
#include "luamod_print.h"
#include "luamod_utils.h"

void load_lua_api(lua_State *L)
{
    lua_createtable(L, 0, 1);
    lua_setglobal(L, "engine_events");

    luaL_openlibs(L);
    lu_luamod::init_api(L);
    lm_utils::init_api(L);
    lu_output::init_api(L);
    lu_engfuncs::init_api(L);
}
