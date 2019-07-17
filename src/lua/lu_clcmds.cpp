#include <extdll.h>
#include "lua_plugins.h"
#include "lu_clcmds.h"

#include <zone_luamod_mem.h>


void lu_clcmds::init_api(lua_State *L)
{
  lua_register(L, "register_clcmd", register_clcmd);
}

int lu_clcmds::register_clcmd(lua_State *L)
{
  
  //luamod_plugin_t *ptr = find_plugin_by_luastate(L);
  
  //if(lua_isstring(L, 1) && lua_isstring(L, 2))
    //{
      
     // luamod_client_callback_t *ptr2 = (luamod_client_callback_t*)Mem_Malloc(luamod_mem_pool, sizeof (luamod_client_callback_t));
      
     // strncpy(ptr2->client_command, luaL_checkstring(L, 1), sizeof(ptr2->client_command));
     // strncpy(ptr2->client_function, luaL_checkstring(L, 2), sizeof(ptr2->client_function));
      
     // ptr2->next = ptr->client_commands_callbacks;
     // ptr->client_commands_callbacks = ptr2;

    //}
}
