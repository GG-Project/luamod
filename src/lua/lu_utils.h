#pragma once
#include "luai.h"

namespace lm_utils {
    void init_api(lua_State *L);
    int l_hud_message(lua_State *L);
    int l_get_authid_by_edict(lua_State *L);
    int l_is_player(lua_State *L);
    int l_get_offset(lua_State *L);
    int l_version(lua_State *L);
    int l_get_cvar(lua_State *L);
    int l_get_cvar2(lua_State* L);
    int l_get_entity_key_value(lua_State *L);
    int l_write_logfile(lua_State *L);
}
