#include <extdll.h>
#include <meta_api.h>
#include "luai.h"

#include "lu_luamod.h"
#include "lu_module.h"
#include "lu_utils.h"
#include "lu_output.h"
#include "lu_offset.h"
#include "lu_engfuncs.hpp"
#include "lu_sqlite.h"

void loadLuaApi(lua_State *L) {
    lua_createtable(L, 0, 1);
    lua_setglobal(L, "engine_events");

    luaL_openlibs(L);
    lu_luamod::init_api(L);
    lu_module::init_api(L);
    lm_utils::init_api(L);
    lu_offset::init_api(L);
    lu_output::init_api(L);
    lu_engfuncs::init_api(L);
    lu_sqlite::init_api(L);
}
