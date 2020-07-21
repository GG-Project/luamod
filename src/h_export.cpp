#include "commands_luamod.h"
#include "luai.h"
#include "luamod.h"
#include "utils.h"
#include <extdll.h>
#include <meta_api.h>
#include <string.h>

char MOD_PATH[64];

extern bool g_meta_init;

enginefuncs_t g_engfuncs;
globalvars_t *gpGlobals;

// Receive engine function table from engine.
// This appears to be the _first_ DLL routine called by the engine, so we
// do some setup operations here.

C_DLLEXPORT void WINAPI GiveFnptrsToDll(enginefuncs_t *pengfuncsFromEngine, globalvars_t *pGlobals)
{
    memcpy(&g_engfuncs, pengfuncsFromEngine, sizeof(enginefuncs_t));
    gpGlobals = pGlobals;

    ALERT(at_console, "[LM] LuaMod version %s\n", LUAMOD_VERSION);

    (*g_engfuncs.pfnAddServerCommand)("luamod", LuaMod_COMMAND);

    char game_dir[256];
    int pos = 0;

    (*g_engfuncs.pfnGetGameDir)(game_dir);

    if (strstr(game_dir, "/")) {
        pos = strlen(game_dir) - 1;

        // scan backwards till first directory separator...
        while ((pos > 0) && (game_dir[pos] != '/'))
            pos--;
        if (pos == 0)
            ALERT(at_console, "[LM] Error determining MOD directory name! \n");

        pos++;
    }
    strncpy(MOD_PATH, &game_dir[pos], sizeof(MOD_PATH));

    if (g_meta_init)
        ALERT(at_console, "[LM] Metamod api init\n");
}
