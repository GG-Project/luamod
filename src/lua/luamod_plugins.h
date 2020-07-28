#pragma once
#include "luai.h"

namespace lu_plugin_api {
void init(lua_State *L);
int l_register_plugin(lua_State *L);
} // namespace lu_plugin_api
