/*
 * Copyright (C) 2018 mr0maks
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// Header for pluginapi :)

// Max Plugins
#define MAX_PLUGINS 16 // пока не больше

// "Hardcoded plugins path"
#define PLUGINS_PATH "%s/addons/luamod/plugins/%s/main.lua"

struct LUAMOD_PLUGIN
{
    int plugin_id;
    const char *plugin_name;
    const char *plugin_author;
    char plugin_dir[256];
    const char *plugin_code;
    bool work; // запущен ли сейчас плагин ?
    lua_State *plugin_state;
    pthread_t plugin_thread;
};



