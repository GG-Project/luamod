#ifndef MODULES_API_H
#define MODULES_API_H

#include "luai.h"

const char* lua_checklstring(lua_State* L, int arg);
int lua_checkinterger(lua_State* L, int arg);
void *lua_getuserdata(lua_State *L, int arg);
void register_lua_function(lua_State *L, char *name, lua_CFunction fn);



#endif // MODULES_API_H
