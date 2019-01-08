#include "CLuaWorker.hpp"
#include <extdll.h>
#include <meta_api.h>
#include <string.h>
#include <utils.h>
#include <luamod.h>
#include "lu_luamod.h"
#include <pthread.h>
#include <unistd.h>

#include <zone_luamod_mem.h>

typedef struct LUAMOD_SET_TASK_S
{
    int taskid;
    qboolean loop;
    const char *name;
    const char *function_name;
    lua_State *L;
    pthread_t task_thread;
    int time_to_execute;
    int execute_count;
    struct LUAMOD_SET_TASK_S *next;
} LUAMOD_SET_TASK;

LUAMOD_SET_TASK *task_list = NULL;

static int tasks = 0;

void lu_luamod::init_api(lua_State* L) {
    lua_register(L, "set_task", l_set_task);
    lua_register(L, "del_task", l_del_task);
    //lua_register(L, "include", l_include);

    lua_pushfstring(L, MOD_PATH);
    lua_setglobal(L, "MOD_PATH");
}

static void *set_task_thread(void *set_task_args)
{    
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    LUAMOD_SET_TASK *task = (LUAMOD_SET_TASK*)set_task_args;
    
    ALERT(at_console, "THREAD EXECUTED!!\n");

    while (task) {
        sleep((unsigned int)task->time_to_execute);
        ALERT(at_console, "Sleep ok. Execute Lua function\n");
        lua_getglobal(task->L, task->function_name);
        g_luaworker->safeCall(task->L, 0, 0);
        task->execute_count--;
        }

    return NULL;
}


// set_task(name, count, time, func)
// if count = -1 - loop
int lu_luamod::l_set_task(lua_State* L)
{
    tasks++;

    LUAMOD_SET_TASK *ptr, *ptr_tmp;

    ptr = (LUAMOD_SET_TASK*)Mem_Malloc(luamod_mem_pool, sizeof(LUAMOD_SET_TASK));

    ptr->taskid = tasks;
    ptr->name = luaL_checkstring(L, 1);
    ptr->execute_count = luaL_checknumber(L, 2);

    if(ptr->execute_count == -1)
        ptr->loop = true;

    ptr->time_to_execute = luaL_checknumber(L, 3);
    ptr->function_name = luaL_checkstring(L, 4);
    ptr->L = L;

    ptr_tmp = task_list;
    ptr->next = ptr_tmp;
    task_list = ptr;

    lua_pushnumber(L, tasks); // return "id" of thread

    pthread_create(&ptr->task_thread, NULL, &set_task_thread, ptr);
//  pthread_detach(&ptr->task_thread);
    return 1;
}

int lu_luamod::l_del_task(lua_State* L)
{
    int id = luaL_checknumber(L, 1);

    if( id < 0 || id > tasks)
    {
        luaL_error(L, "task id invalid");
        return 0;
    }

    LUAMOD_SET_TASK *ptr, *ptr_tmp, *ptr_task;

    ptr = task_list;

    while (ptr != NULL) {
        if(ptr->next->taskid == id)
        {
            ptr_task = ptr->next;
            ptr_tmp = ptr_task->next;
            break;
        }
        ptr = ptr->next;
    }

    if(pthread_cancel(ptr_task->task_thread) == ESRCH)
    {
        luaL_error(L, "del_task error : no such thread");
        return 0;
    }

    Mem_Free(ptr_task);

    ptr->next = ptr_tmp;

    tasks--;
    return 1;
}

int lu_luamod::l_include(lua_State *L)
{
}
