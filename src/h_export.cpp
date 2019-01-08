#include <string.h>
#include <extdll.h>
#include <meta_api.h>
#include "luamod.h"
#include "utils.h"
#include "commands_luamod.h"
#include "luai.h"

#include "zone.h"
#include "zone_luamod_mem.h"

void Parse_And_Load_Modules();

char MOD_PATH[64];

extern bool g_meta_init;

#ifdef XASH3D
#include "port.h"
#endif

enginefuncs_t g_engfuncs;
globalvars_t *gpGlobals;

#if 0
GETENTITYAPI other_GetEntityAPI;
GIVEFNPTRSTODLL other_GiveFnptrsToDll;
GETNEWDLLFUNCTIONS other_GetNewDLLFunctions;
HINSTANCE h_Library = NULL;
#endif

// Receive engine function table from engine.
// This appears to be the _first_ DLL routine called by the engine, so we
// do some setup operations here.

C_DLLEXPORT void WINAPI GiveFnptrsToDll(enginefuncs_t *pengfuncsFromEngine, globalvars_t *pGlobals) {
    memcpy(&g_engfuncs, pengfuncsFromEngine, sizeof (enginefuncs_t));
    gpGlobals = pGlobals;

    char game_dir[256];

    int pos = 0;

    (*g_engfuncs.pfnGetGameDir)(game_dir);
    
    ALERT(at_console, "[LM] LuaMod version %s\n", LUAMOD_VERSION);
    
    (*g_engfuncs.pfnAddServerCommand)("luamod", LuaMod_COMMAND);

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

    if(g_meta_init)
       ALERT(at_console, "[LM] Metamod api init\n"); 

    ALERT(at_console, "[LM] Init zone memory allocation\n");

    Memory_Init();

    Memory_Pools_Init();

    Parse_And_Load_Modules();
    
#if 0
                const char *filePath = "valve/dlls/hl.so";
                TEST other_pfnGetGameDescription = NULL;
                h_Library = LoadLibrary( filePath );

                if (h_Library == NULL) {        // Directory error or Unsupported MOD!
                        ALERT(at_console, "MOD Dll not found (or unsupported MOD)!" );
                        // debugFile( "Library = 0\n" );
                }

                other_GetEntityAPI = (GETENTITYAPI)GetProcAddress( h_Library, "GetEntityAPI" );
                if (other_GetEntityAPI == NULL) ALERT(at_console, "[LM] Can't get MOD's GetEntityAPI!\n" );

                other_GiveFnptrsToDll = (GIVEFNPTRSTODLL)GetProcAddress(h_Library, "GiveFnptrsToDll");
                if (other_GiveFnptrsToDll == NULL) ALERT(at_console, "[LM] Can't get MOD's GiveFnptrsToDll!\n" );

                (*other_GiveFnptrsToDll)(pengfuncsFromEngine, pGlobals);
                
                //ALERT(at_console, "[LM] LuaMod Mod %s", other_pfnGetGameDescription);
#endif
}
