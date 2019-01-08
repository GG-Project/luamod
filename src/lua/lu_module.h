#pragma once
#include "luai.h"

namespace lu_module {
    void init_api(lua_State *L);
    void init_modules(lua_State *L);
}
