#include "luai.h"
#include <luamod_api.h>
#include "utils.h"

const char* lua_checklstring(lua_State* L, int arg)
{
    return luaL_checkstring(L, arg);
}

int lua_checkinterger(lua_State* L, int arg)
{
    return luaL_checkinteger(L, arg);
}

void *lua_getuserdata(lua_State *L, int arg)
{
    return lua_touserdata(L, arg);
}

void register_lua_function(lua_State *L, char *name, lua_CFunction fn)
{
    lua_pushcclosure(L, fn, 0);
    lua_setglobal(L, name);
}

void log_console_module(module_info_t *module, const char *fmt, ...)
{
    va_list ap;
    char buff[1024];

    va_start(ap, fmt);
    vsnprintf(buff, sizeof(buff),va("%s: %s", module->logtag, fmt), ap);
    va_end(ap);

    SERVER_PRINT(buff);
}
