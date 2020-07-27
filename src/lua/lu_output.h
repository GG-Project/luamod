#pragma once
#include "luai.h"
#include <extdll.h>
#include <meta_api.h>

namespace lu_output {
void init_api(lua_State *L);
//
int print(lua_State *L); // msg
int log_console(lua_State *L); // msg
int log_message(lua_State *L); // msg
int log_error(lua_State *L); // msg
int log_developer(lua_State *L); // msg
}; // namespace lu_output
