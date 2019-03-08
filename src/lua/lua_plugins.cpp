#include "luamod.h"
#include <extdll.h>
#include <meta_api.h>

#include "lua_plugins.h"
#include "luai.h"
#include "utils.h"

#include <zone_luamod_mem.h>

#define PLUGINS_CONFIG_PATH "%s/addons/luamod/plugins.ini"
#define PLUGINS_MAIN_LUA "%s/addons/luamod/plugins/%s/main.lua"
#define PLUGINS_MAIN_LUAC "%s/addons/luamod/plugins/%s/main.luac"

luamod_plugin *plugins_list;

void *plugins_lua_alloc(void *ud, void *ptr, size_t osize, size_t nsize)
{

    luamod_mem_debug *ptr2 = (luamod_mem_debug *)ud;

    if (nsize == 0) {
        ptr2->released = +osize;
        ptr2->used_now = -osize;
        free(ptr);
        return NULL;
    } else {
        ptr2->used_now = +(nsize - osize);
        ptr2->total_size = +(nsize - osize);
        return realloc(ptr, nsize);
    }
}

void loadLuaApi(lua_State *L);

inline void push_plugin_to_list(luamod_plugin *ptr)
{
    ptr->next = plugins_list;
    plugins_list = ptr;
}

luamod_plugin *find_plugin_by_luastate(lua_State *L)
{

    luamod_plugin *ptr = plugins_list;

    while (ptr != NULL) {

        if (ptr->L == L)
            break;

        ptr = ptr->next;
    }

    return ptr;
}

int errorHandler(lua_State *L)
{
    // stack: err
    const char *err = lua_tostring(L, 1);

    ALERT(at_console, "Error: %s\n", err);

    lua_getglobal(L, "debug"); // stack: err debug
    lua_getfield(L, -1, "traceback"); // stack: err debug debug.traceback

    // debug.traceback() возвращает 1 значение
    if (lua_pcall(L, 0, 1, 0)) {
        const char *err = lua_tostring(L, -1);

        ALERT(at_console, "Error in debug.traceback() call: %s\n", err);
    } else {
        const char *stackTrace = lua_tostring(L, -1);

        ALERT(at_console, "C++ stack traceback: %s\n", stackTrace);
    }

    return 1;
}

void plugin_stop(luamod_plugin *plugin)
{
    //  plugin->running = false;
}

int plugin_have_event(lua_State *L, const char *event)
{
    lua_getglobal(L, "engine_events");
    lua_getfield(L, -1, event);
    return lua_isnil(L, -1) ? 0 : 1;
}

void plugin_error(lua_State *L, const char *fmt, ...)
{
    char string[8192];
    va_list va;
    va_start(va, fmt);
    vsnprintf(string, 8192, fmt, va);
    va_end(va);

    luamod_plugin *plugin = find_plugin_by_luastate(L);

    plugin->running = false;
    luaL_error(plugin->L, "%s", string);
}

void plugin_safecall(lua_State *L, int nargs, int rets)
{
    // TODO: сделать stack traceback вместо 0
    if (lua_pcall(L, nargs, rets, 0)) {
        luamod_plugin *plugin = find_plugin_by_luastate(L);
        plugin->running = false;
        ALERT(at_console, "[LM] Plugin %s\nRuntime Error : %s\n", plugin->name, lua_tostring(L, -1));
    }
}

void Plugin_List()
{
    luamod_plugin *ptr = plugins_list;

    while (ptr != NULL) {
        ALERT(at_console, "[LM] Plugin %s %s %s %s\n", ptr->author, ptr->name, ptr->version, ptr->description);
        ptr = ptr->next;
    }

    ptr = NULL;
}

void Load_Plugin(const char *filename)
{
    luamod_plugin *ptr = NULL, *ptr_tmp = NULL;

    ptr = (luamod_plugin *)Mem_Calloc(luamod_mem_pool, sizeof(luamod_plugin));

    strncpy(ptr->filename, filename, sizeof(ptr->filename));

    ptr->L = lua_newstate(plugins_lua_alloc, &ptr->debug_mem);

    loadLuaApi(ptr->L);

    push_plugin_to_list(ptr);

    if (luaL_loadfile(ptr->L, va(PLUGINS_MAIN_LUA, MOD_PATH, filename))) {
        ALERT(at_console, "[LM] Error while loading plugin %s : %s\n", filename, lua_tostring(ptr->L, -1));
        ptr->running = false;
        return;
    }

    if (lua_pcall(ptr->L, 0, 0, 0)) {
        ALERT(at_console, "[LM] Error while loading plugin %s : %s\n", filename, lua_tostring(ptr->L, -1));
        ptr->running = false;
        return;
    }

    if (ptr->registred != true) {
        ALERT(at_console, "[LM] Error while loading plugin %s : plugin not call register_plugin\n", filename);
        ptr->running = false;
        return;
    }

    ALERT(at_console, "[LM] Lua Plugin load succes! %s %s %s %s\n", ptr->author, ptr->name, ptr->description, ptr->version);

    ptr->running = true;
}

#include "parser.h"

void Parse_And_Load_Lua_Plugins(void)
{
    FILE *config = fopen(va(PLUGINS_CONFIG_PATH, MOD_PATH), "r");

    if (!config) {
        ALERT(at_console, "[LM] Error while opening plugins config %s\n", va(PLUGINS_CONFIG_PATH, MOD_PATH));
        return;
    }

    char buff[256], buff2[256];

    while (!ferror(config) && fgets(buff, sizeof(buff), config) != NULL) {
        StripCommentary(buff2, buff, sizeof(buff2));

        if (buff2[0] == 0)
            continue;

        Load_Plugin(buff2);
    }

    fclose(config);
}
