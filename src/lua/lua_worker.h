#pragma once
#include <lua.hpp>

extern lua_State *core;

bool worker_have_event(lua_State *L, const char *event);
void worker_pcall(lua_State *L, int nargs, int rets);
void worker_load();
void worker_close();
void worker_restart();
