#include "luamod.h"
#include <extdll.h>
#include <meta_api.h>

#include <exception>

#include "lua_plugins.h"
#include "luai.h"
#include "utils.h"

#define PLUGINS_CONFIG_PATH "%s/addons/luamod/plugins.ini"
#define PLUGINS_MAIN_LUA "%s/addons/luamod/plugins/%s/main.lua"
#define PLUGINS_MAIN_LUAC "%s/addons/luamod/plugins/%s/main.luac"

luamod_plugin_t *plugins_list = nullptr;

void loadLuaApi(lua_State *L);

inline void push_plugin_to_list(luamod_plugin_t *plugin)
{
    plugin->m_next = plugins_list;
    plugins_list = plugin;
}

inline void remove_plugin_from_list( luamod_plugin_t *plugin )
{
    luamod_plugin_t *ptr = plugins_list, *ptr_t1 = nullptr;
    if(ptr->L == plugin->L)
    {
        plugins_list = ptr->m_next;
        return;
    }
    
    ptr_t1 = ptr->m_next;
    
    while(ptr_t1)
    {

        if( ptr_t1->L == plugin->L )
        {
            ptr->m_next = ptr_t1->m_next;
            return;
        }
        ptr = ptr_t1;
        ptr_t1 = ptr_t1->m_next;
    }
}

luamod_plugin_t *find_plugin_by_luastate(lua_State *L)
{
    luamod_plugin_t *ptr = plugins_list;

    while (ptr != NULL) {

        if (ptr->L == L)
            break;

        ptr = ptr->m_next;
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

void plugin_stop(luamod_plugin_t *plugin)
{
    //  plugin->running = false;
}

int plugin_have_event(lua_State *L, const char *event)
{
    lua_getglobal(L, "engine_events");
    lua_getfield(L, -1, event);

    if(lua_isfunction(L, -1))
        return 1;
    else {
        lua_pop(L, -1);
        return 0;
    }
}

void plugin_error(lua_State *L, const char *fmt, ...)
{
    char string[8192];
    va_list va;
    va_start(va, fmt);
    vsnprintf(string, 8192, fmt, va);
    va_end(va);

    luamod_plugin_t *plugin = find_plugin_by_luastate(L);

    plugin->running = false;
    luaL_error(plugin->L, "%s", string);
}

void plugin_pcall(lua_State *L, int nargs, int rets)
{
    // TODO: сделать stack traceback вместо 0
    if (lua_pcall(L, nargs, rets, 0)) {
        luamod_plugin_t *plugin = find_plugin_by_luastate(L);
        plugin->running = false;
        ALERT(at_console, "[LM] Plugin %s\nRuntime Error : %s\n", plugin->name, lua_tostring(L, -1));
    }
}

void Plugin_List()
{
    luamod_plugin_t *ptr = plugins_list;

    while (ptr != nullptr) {
        ALERT(at_console, "[LM] Plugin %s %s %s %s\n", ptr->author, ptr->name, ptr->version, ptr->description);
        ptr = ptr->m_next;
    }

    ptr = nullptr;
}

int plugin_panic_catch_exceptions(lua_State *L)
{
    return 0;
}

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

luamod_plugin_t *find_plugin_by_name(const char *filename)
{
  luamod_plugin_t *ptr = plugins_list;

  while( ptr )
    {
      if(!strcasecmp(ptr->filename, filename))
	{
	return ptr;
	}

    ptr = ptr->m_next;
    }
  return NULL;
}

void Plugin_Load(const char *filename)
{
    luamod_plugin_t *ptr = NULL;

    if( find_plugin_by_name( filename ) )
      {
	ALERT(at_console, "[LM] Error while loading plugin %s : already load\n", filename);
	return;
      }

    ptr = (luamod_plugin_t *)malloc(sizeof(luamod_plugin_t));

    strncpy(ptr->filename, filename, sizeof(ptr->filename));

    ptr->L = luaL_newstate();

    lua_pushlightuserdata(ptr->L, (void *)plugin_wrap_exceptions);
    luaJIT_setmode(ptr->L, -1, LUAJIT_MODE_WRAPCFUNC|LUAJIT_MODE_ON);
    lua_pop(ptr->L, 1);

    lua_atpanic(ptr->L, plugin_panic_catch_exceptions);

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

void Plugin_Close( const char *filename )
{
    if(!find_plugin_by_name(filename))
    {
        ALERT(at_console, "[LM] Error while close plugin %s : plugin not loaded\n", filename);
        return;
    }

    luamod_plugin_t *ptr_main = find_plugin_by_name(filename);

    remove_plugin_from_list(ptr_main);

    lua_close(ptr_main->L);

    free(ptr_main);
}

void Plugin_Restart( const char *filename )
{
    Plugin_Close( filename );
    Plugin_Load( filename );
}

#include "parser.h"

void Load_Plugins_From_Config(void)
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

        Plugin_Load(buff2);
    }

    fclose(config);
}
