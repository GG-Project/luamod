#include "luamod_print.h"

void lu_output::init_api(lua_State *L)
{
    lua_register(L, "print", print);
}

/* Overloading lua print to use engine alert */
int lu_output::print(lua_State *L)
{
    const char *str = luaL_checkstring(L, 1);
    ALERT(at_console, "%s\n", str);
    return 0;
}
