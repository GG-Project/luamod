#ifndef LU_CLCMDS_H
#define LU_CLCMDS_H

#include "lua_plugins.h"

namespace lu_clcmds {
  void init_api(lua_State *L);
  int register_clcmd(lua_State *L);
  //int unregister_clcmd(lua_State *L);
}

#endif // LU_CLCMDS_H
