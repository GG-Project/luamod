#pragma once
#include <lua.hpp>

namespace lm_utils {
void init_api(lua_State *L);
int l_get_entity_key_value(lua_State *L);
} // namespace lm_utils
