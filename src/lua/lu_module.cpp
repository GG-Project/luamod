#include "lu_module.h"
#include <utils.h>

#include <modules.h>

extern luamod_module_t *LUAMOD_MODULES;

void lu_module::init_api(lua_State *L)
{
    init_modules(L);
}

void lu_module::init_modules(lua_State *L)
{
    luamod_module_t *ptr;

    ptr = LUAMOD_MODULES;

    while (ptr != NULL) {

        if( ptr->running == 1 )
          {
            ptr->register_lua_funcs(L);
          }

        ptr = ptr->next;
        //        PRINT_CONSOLE("module %s id: %d running : %d\n",LUAMOD_MODULES[i].module_info->name, i, LUAMOD_MODULES[i].running);
    }

    //clean pointer
    ptr = NULL;
}
