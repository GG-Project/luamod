#ifndef LUAMOD_TYPES_H
#define LUAMOD_TYPES_H

#include "luai.h"
#include <extdll.h>
#include <meta_api.h>
#include "luamod.h"

void luaL_push_vec3_t(lua_State *L, float *vector);
const float *luaL_check_vec3_t(lua_State *L, int index);
void lua_pushedict(lua_State *L, edict_t *ed);
edict_t *luaL_checkedict(lua_State *L, int index, bool can_nullptr);



#endif // LUAMOD_TYPES_H
