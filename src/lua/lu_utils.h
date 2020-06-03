#pragma once
#include "luai.h"

namespace lm_utils {
void init_api(lua_State *L);
int l_is_player(lua_State *L);
int l_get_entity_key_value(lua_State *L);
} // namespace lm_utils
