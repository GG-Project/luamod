/*
 * Copyright (C) 2018 mr0maks
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

// Plugin api for luamod :)

#include <stdexcept>

#include <extdll.h>
#include <meta_api.h>

#include "luai.h"
#include "pluginapi.h"
#include "lua/CLuaWorker.hpp"

#include <pthread.h>

LUAMOD_PLUGIN PLUGIN[MAX_PLUGINS];

extern char MOD_PATH[32];

int PLUGINS;

void loadLuaApi(lua_State *L); // ага

/* Я считаю что хватит простого запуска с помощью luamod load 
  а потом уже можно будет прикрутить что нибдь посерьёзнее */

int remove_plugin()
{
    return 0;
}

static void *plugin_thread(void *plugin_args)
{    
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    struct LUAMOD_PLUGIN *plugin = (struct LUAMOD_PLUGIN *) plugin_args;
    
    loadLuaApi(plugin->plugin_state);
            
        try {
        if(plugin->plugin_dir == NULL) {
        if(luaL_loadstring(plugin->plugin_state, plugin->plugin_code)) throw std::runtime_error(lua_tostring(plugin->plugin_state, -1));
        } else {
        if(luaL_loadfile(plugin->plugin_state, plugin->plugin_dir)) throw std::runtime_error(lua_tostring(plugin->plugin_state, -1));
        }
        g_luaworker->call(plugin->plugin_state, 0, LUA_MULTRET);
        } catch (std::runtime_error &err) {
        ALERT(at_console, "[LM] Plugin %s Error : %s\n", plugin->plugin_name, err.what());
        }
    
        //    if (luaL_loadfile(state, filename)) throw std::runtime_error(lua_tostring(state, -1));
        //if (lua_pcall(state, 0, LUA_MULTRET, 0)) throw std::runtime_error(lua_tostring(state, -1));

    return NULL;
}

//есть ли плагин в структуре ?
int plugin_in_struct(const char *name)
{
    int i;
    for (i = 0; i < MAX_PLUGINS; i++)
    {
        if(PLUGIN[i].plugin_name == name)
        {
                return 1;
        } else {
            if(i == MAX_PLUGINS)
                return 0;
        }
    }
    return 0;
}

int get_plugin_id_by_name(const char *name)
{
    int i;
    for (i = 0; i < MAX_PLUGINS; i++)
    {
        if(PLUGIN[i].plugin_name == name)
        {
            return i;
        } else {
            if(i == MAX_PLUGINS)
                return 0;
        }
    }
    return 0;
}

int load_lua_code_from_string(const char *plugin_code)
{
    
    
    return 0;
}

int load_lua_plugin(char name[64])
{
    if (plugin_in_struct(name) == 0)
    {
        PLUGINS++;
        
        snprintf(PLUGIN[PLUGINS].plugin_dir, sizeof(PLUGIN[PLUGINS].plugin_dir), PLUGINS_PATH, MOD_PATH, name);
        
        PLUGIN[PLUGINS].plugin_author = "TEST";
        
        PLUGIN[PLUGINS].plugin_id = PLUGINS;
        
        PLUGIN[PLUGINS].plugin_name = name;
        
        pthread_create(&PLUGIN[PLUGINS].plugin_thread, NULL, &plugin_thread, &PLUGIN[PLUGINS]);
        pthread_detach(PLUGIN[PLUGINS].plugin_thread);
    }
    
    return 0;
}

int reload_plugin_by_name(const char *name)
{
    LUAMOD_PLUGIN plugin;
        if (plugin_in_struct(name) != 0)
//                pthread_create(&task[tasks].task_thread, NULL, &plugin_thread, &task[tasks]);
//                pthread_detach(task[tasks].task_thread);
                PLUGINS++;
            return 0;
}