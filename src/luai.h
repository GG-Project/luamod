#pragma once

#if defined(_WIN32) && defined(_MSC_VER)
#pragma comment(lib,"lua.lib")
#endif

#ifdef FULL_PATH_TO_LUA_INCLUDE
#include "lua/lua.hpp"
#else
#include <lua.hpp>
#endif

extern "C" {
#ifdef FULL_PATH_TO_LUA_INCLUDE
#include "lua/lualib.h"
#include "lua/lauxlib.h"
#include "lua/lstate.h"
#include "lua/luaconf.h"
#include "lua/lgc.h"
#include "lua/lua.h"
#else
#include <lualib.h>
#include <lauxlib.h>
#include <lstate.h>
#include <luaconf.h>
#include <lua.h>
#endif
}

/*
#include "luajit/src/lua.hpp"
extern "C" {
#include "luajit/src/lualib.h"
#include "luajit/src/lauxlib.h"
#include "luajit/src/luaconf.h"
#include "luajit/src/luajit.h"
#include "luajit/src/lua.h"
}
*/
