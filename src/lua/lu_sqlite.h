#pragma once
#include <extdll.h>
#include <meta_api.h>
#include "luai.h"

namespace lu_sqlite {
        void init_api(lua_State *L);
        int sqlite_init_db(lua_State *L);
        int sqlite_db_execute(lua_State *L);
        int sqlite_db_close(lua_State *L);
}
