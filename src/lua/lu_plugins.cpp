#include <extdll.h>
#include <meta_api.h>

#include "lu_plugins.h"
#include "lua_plugins.h"

#include "utils.h"

void lu_plugin_api::init(lua_State *L)
{
    lua_register(L, "register_plugin", l_register_plugin);
    lua_register(L, "include", l_include);
}

int lu_plugin_api::l_register_plugin(lua_State *L)
{
    luamod_plugin *plugin_ptr = find_plugin_by_luastate(L);

    if (plugin_ptr == NULL) {
        luaL_error(L, "Error while finding plugin struct in list\n");
        return 0;
    }

    if (plugin_ptr->registred == true) {
        luaL_error(L, "Error: plugin try to register again!!\n");
        return 0;
    }

    const char *author = luaL_checkstring(L, 1);
    const char *name = luaL_checkstring(L, 2);
    const char *version = luaL_checkstring(L, 3);
    const char *description = luaL_checkstring(L, 4);

    strncpy(plugin_ptr->author, author, sizeof(plugin_ptr->author));
    strncpy(plugin_ptr->name, name, sizeof(plugin_ptr->version));
    strncpy(plugin_ptr->version, version, sizeof(plugin_ptr->version));
    strncpy(plugin_ptr->description, description, sizeof(plugin_ptr->description));

    plugin_ptr->registred = true;

    return 0;
}

#define INCLUDE_PATH "%s/addons/luamod/includes/%s"

int lu_plugin_api::l_include(lua_State *L)
{
    const char *filename = luaL_checkstring(L, 1);
    if (luaL_dofile(L, va(INCLUDE_PATH, MOD_PATH, filename))) {
        luaL_error(L, "Error while loading include %s.lua : %s\n", lua_tostring(L, -1));
    }

    return 0;
}
