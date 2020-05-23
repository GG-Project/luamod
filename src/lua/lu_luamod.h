#pragma once

#include <extdll.h>
#include <luamod.h>
#include <meta_api.h>
#include <utils.h>

namespace lu_luamod {
void init_api(lua_State *L);
int l_version(lua_State *L);
}; // namespace lu_luamod
