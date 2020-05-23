#if 0
#pragma once
#include "luai.h"
#include <extdll.h>
#include <meta_api.h>

namespace lu_sqlite {
void init_api(lua_State *L);
int sqlite_init_db(lua_State *L);
int sqlite_db_execute(lua_State *L);
int sqlite_db_close(lua_State *L);
} // namespace lu_sqlite
#endif
