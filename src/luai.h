#pragma once

#if defined(_WIN32) && defined(_MSC_VER)
#pragma comment(lib,"lua.lib")
#endif

#include "lua/lua.hpp"
extern "C" {
#include "lua/lualib.h"
#include "lua/lauxlib.h"
#include "lua/lstate.h"
#include "lua/luaconf.h"
#include "lua/lgc.h"
#include "lua/lua.h"
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