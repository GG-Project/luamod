#pragma once
#include <extdll.h>
#include <meta_api.h>
#include <const.h>
#include "luai.h"

namespace lu_offset {
  void init_api(lua_State *L);
    int l_get_offset_char(lua_State *L);
    int l_set_offset_char(lua_State *L);
	int l_get_offset_data(lua_State *L);
	int l_get_offset_float(lua_State *L);
	int l_set_offset_float(lua_State *L);
	int l_get_offset_int(lua_State *L);
	int l_set_offset_int(lua_State *L);
	int l_get_offset_qboolean(lua_State *L);
	int l_set_offset_qboolean(lua_State *L);
};
