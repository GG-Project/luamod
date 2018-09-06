#include <string.h>
#include <extdll.h>
#include <meta_api.h>
#include "luamod_utils.hpp"
#include "lua/luaconf.h"

enginefuncs_t g_engfuncs;
globalvars_t *gpGlobals;

// Receive engine function table from engine.
// This appears to be the _first_ DLL routine called by the engine, so we
// do some setup operations here.

C_DLLEXPORT void WINAPI GiveFnptrsToDll(enginefuncs_t *pengfuncsFromEngine, globalvars_t *pGlobals) {
    memcpy(&g_engfuncs, pengfuncsFromEngine, sizeof (enginefuncs_t));
    gpGlobals = pGlobals;

    char game_dir[256], mod_name[32];

    int pos = 0;

    (*g_engfuncs.pfnGetGameDir)(game_dir);
    
    ALERT(at_console, "[LM] LuaMod version %s\n", LUAMOD_VERSION);

    if (strstr(game_dir, "/")) {
        pos = strlen(game_dir) - 1;

        // scan backwards till first directory separator...
        while ((pos > 0) && (game_dir[pos] != '/'))
            pos--;
        if (pos == 0)
            ALERT(at_console, "[LM] Error determining MOD directory name! \n");

        pos++;
    }
    strncpy(mod_name, &game_dir[pos], sizeof(mod_name));
    luamod_utils::SetModName(mod_name);
}
