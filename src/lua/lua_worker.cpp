#include <exception>
#include <luamod.h>
#include "lua_worker.h"

#define CORE_MAIN_LUA "%s/addons/luamod/main.lua"

lua_State *core;

void load_lua_api(lua_State *L);

bool worker_have_event(lua_State *L, const char *event)
{
    lua_getglobal(L, "engine_events");
    lua_getfield(L, -1, event);

    if(lua_isfunction(L, -1))
    {
        lua_remove(L, -2); // remove engine_events table
        return true;
    } else
    {
        lua_pop(L, -2); // Drop engine_events and not function
    }

    return false;
}

void worker_pcall(lua_State *L, int nargs, int rets)
{
    // TODO: make stack traceback
    if (lua_pcall(core, nargs, rets, 0)) {
        ALERT(at_console, "[LM] Runtime Error : %s\n", lua_tostring(core, -1));
    }
}

int plugin_panic_catch_exceptions(lua_State *L)
{
    return 0;
}

// LuaJIT Example
static int plugin_wrap_exceptions(lua_State *L, lua_CFunction f)
{
  try {
    return f(L);
  } catch (const char *s) {
    lua_pushstring(L, s);
  } catch (std::exception& e) {
    lua_pushstring(L, e.what());
  } catch (...) {
    lua_pushliteral(L, "catch (...)");
  }
  return lua_error(L);
}

void worker_load()
{
    core = luaL_newstate();

    // in tarantool fork gdb python script detecting luajit by luaJIT_setmode
    lua_pushlightuserdata(core, (void *)plugin_wrap_exceptions);
    luaJIT_setmode(core, -1, LUAJIT_MODE_WRAPCFUNC|LUAJIT_MODE_ON);
    lua_pop(core, 1);

    lua_atpanic(core, plugin_panic_catch_exceptions);

    load_lua_api(core);

    if (luaL_dofile(core, va(CORE_MAIN_LUA, MOD_PATH))) {
        ALERT(at_console, "[LM] Error while loading core: %s\n", lua_tostring(core, -1));
        return;
    }
}

void worker_close()
{
    lua_close(core);
}

void worker_restart()
{
    worker_close();
    worker_load();
}
