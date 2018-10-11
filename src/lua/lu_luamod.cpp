#include <extdll.h>
#include <meta_api.h>
#include <string>
#include <utils.h>
#include <luamod.h>
#include "lu_luamod.h"
#include "luai.h"
#include <pluginapi.h>

#include <pthread.h>

#include <unistd.h>

void loadLuaApi(lua_State *L);

LUAMOD_SET_TASK task[256];

// extern LUAMOD_PLUGIN PLUGIN[MAX_PLUGINS];

int plugins;

int tasks;

void lu_luamod::init_api(lua_State* L) {
    lua_register(L, "set_task", l_set_task);
    lua_register(L, "del_task", l_del_task);
//    lua_register(L, "load_plugin", l_load_plugin);
}

static void *set_task_thread(void *set_task_args)
{    
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    struct LUAMOD_SET_TASK *task = (struct LUAMOD_SET_TASK *) set_task_args;
    
    for(;;)
    {

    sleep(1);

    task->time_left_to_execute = task->time_left_to_execute - 1;
    
    if(task->time_left_to_execute == 0 || task->time_left_to_execute < 0) {
        
        if(task->execute_count != 0 || task->execute_count == -1) {

                    lua_getglobal(task->lua_state, task->function_name);
        
                    g_luaworker->safeCall(task->lua_state, 0, 0);
        
                    task->execute_count = task->execute_count -1;
        
                    task->time_left_to_execute = task->time_to_execute;
                } else { 
                        break;
                }
             }
    
        }
    return NULL;
}


// set_task(name, count, time, func)
// if count = -1 - loop
int lu_luamod::l_set_task(lua_State* L)
{
    tasks++;
    
    task[tasks].name = luaL_checkstring(L, 1);
    
    task[tasks].execute_count = luaL_checknumber(L, 2);
    
    task[tasks].time_left_to_execute = luaL_checknumber(L, 3);
    
    task[tasks].time_to_execute = luaL_checknumber(L, 3);
    
    task[tasks].function_name = luaL_checkstring(L, 4); 
    
    task[tasks].lua_state = L;
            
    task[tasks].execute_this = 1;
    
    lua_pushnumber(L, tasks); // return "id" of thread
    
    pthread_create(&task[tasks].task_thread, NULL, &set_task_thread, &task[tasks]);
    
    pthread_detach(task[tasks].task_thread);
        
    return 1;
}

int lu_luamod::l_del_task(lua_State* L)
{
    // check id
    int id = luaL_checknumber(L, 1);
    
    if( id < 0 || id > tasks) luaL_error(L, "task id invalid");
    
    if (pthread_cancel(task[id].task_thread) == ESRCH)
        luaL_error(L, "del_task error : no such thread");
    
    tasks--;
    
    return 1;
}

int lu_luamod::l_load_plugin(lua_State *L)
{
/*
    
    plugins++;
    
    PLUGIN[plugins].plugin_state = lua_newstate();
    
    PLUGIN[plugins].plugin_id = plugins;
    
    PLUGIN[plugins].plugin_state = luaL_newstate();
    
    loadLuaApi(PLUGIN[plugins].plugin_state);
    
    lua_getglobal(PLUGIN[plugins].plugin_state, "plugin_info");
    
    PLUGIN[plugins].plugin_name = "HIHI";
    
    pthread_create(&PLUGIN[plugins].plugin_thread, NULL, &pthread_kek, &PLUGIN[plugins]);
    
    pthread_detach(PLUGIN[plugins].plugin_thread);
*/    
    return 1;
}
