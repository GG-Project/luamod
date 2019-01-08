//
//  CLuaWorker.cpp
//  luamod
//
//  Created by Elektro-Volk on 24/07/2018.
//
//

#include "CLuaWorker.hpp"
#include <extdll.h>
#include <meta_api.h>
#include <string>
#include <stdexcept>
#include <utils.h>

#include <zone_lua_alloc.h>

#include <luamod.h>

CLuaWorker *g_luaworker;

void loadLuaApi(lua_State *L);

CLuaWorker::CLuaWorker() {
    try {

        //lua_setallocf(state, zone_lua_alloc, NULL);

        state = lua_newstate(zone_lua_alloc, NULL);
        loadLuaApi(state);
        char filename[260];
        ALERT(at_console, "[LM] Mod path : %s\n", MOD_PATH);
        snprintf(filename, sizeof(filename), "%s/addons/luamod/core/init.lua", MOD_PATH);
        if (luaL_loadfile(state, filename)) throw std::runtime_error(lua_tostring(state, -1));
        if (lua_pcall(state, 0, LUA_MULTRET, 0)) throw std::runtime_error(lua_tostring(state, -1));
    } catch (std::runtime_error &err) {
        ALERT(at_console, "[LM] %s\n", err.what());
    }
}

lua_State *CLuaWorker::getState() {
    return state;
}

void CLuaWorker::call(lua_State *L, int args, int rets) {
    if (lua_pcall(L, args, rets, 0)) throw std::runtime_error(lua_tostring(L, -1));
}

void CLuaWorker::safeCall(lua_State *L, int args, int rets) {
    try {
        call(L, args, rets);
    } catch (std::runtime_error &err) {
        ALERT(at_console, "[LM] %s\n", err.what());
    }
}

lua_State *CLuaWorker::getToEvent(const char* event) {
    lua_State* L = g_luaworker->getState();
    lua_getglobal(L, "engine_events");
    lua_getfield(L, -1, event);

    return lua_isnil(L, -1) ? nullptr : L;
}

CLuaWorker::~CLuaWorker() {

}
