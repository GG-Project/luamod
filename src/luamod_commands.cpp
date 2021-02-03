#include "build.h"
#include <extdll.h>
#include <meta_api.h>
#include "utils.h"

#if 0
#include <sqlite3.h>
#endif

void cmd_luamod_usage(void)
{
    PRINT_CONSOLE("usage: luamod <command> [<arguments>]\n");
    PRINT_CONSOLE("   version          - display luamod version info\n");
    PRINT_CONSOLE("   cvars            - list cvars currently registred by luamod or plugins\n");
    PRINT_CONSOLE("   restart          - full lua restart\n");
}

void cmd_luamod_version()
{
    PRINT_CONSOLE("LuaMod\n");
    PRINT_CONSOLE("Version: " LUAMOD_VERSION "\n");
#ifdef DEBUG
    PRINT_CONSOLE("Build time: " __DATE__ ", " __TIME__ "\n");
#endif
#ifdef LUAMOD_BRANCH
    PRINT_CONSOLE("Branch: " LUAMOD_BRANCH "\n");
#endif
    PRINT_CONSOLE("OS: %s %s\n", LM_buildos(), LM_buildarch());
#ifdef DEBUG
    PRINT_CONSOLE("Compiler %s version %s\n", LM_buildcompiler(), LM_buildcompilerversion());
#endif
    PRINT_CONSOLE("Compiled with %s\n", LM_buildhlsdk());
    PRINT_CONSOLE("Compiled with %s\n", LM_buildlua());
}

void Cvar_Manager_List();
void cmd_luamod_cvarlist() { Cvar_Manager_List(); }
void worker_restart();
void cmd_luamod_restart() { worker_restart(); }

void LuaMod_COMMAND(void)
{
    const char *cmd;

    cmd = CMD_ARGV(1);

    if (!strcasecmp(cmd, "version"))
        cmd_luamod_version();
    else if(!strcasecmp(cmd, "cvars"))
      cmd_luamod_cvarlist();
    else if (!strcasecmp(cmd, "restart"))
        cmd_luamod_restart();
    else {
        PRINT_CONSOLE("Unrecognized luamod command: %s\n", cmd);
        cmd_luamod_usage();
        return;
    }
}
