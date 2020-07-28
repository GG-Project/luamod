#pragma once
#include "luai.h"
#include <extdll.h>
#include <meta_api.h>

namespace lu_output {
void init_api(lua_State *L);
//
int print(lua_State *L); // msg
}; // namespace lu_output
