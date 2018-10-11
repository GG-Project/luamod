#include <utils.h>
#include <extdll.h>
#include <meta_api.h>
#include "build.h"

void cmd_luamod_version()
{
    PRINT_CONSOLE("LuaMod");
    PRINT_CONSOLE("Version : %s", LUAMOD_VERSION);
    PRINT_CONSOLE("OS : %s %s", LM_buildos(), LM_buildarch());
    PRINT_CONSOLE("Build with %s", LM_buildhlsdk());
#ifdef LUAMOD_PATCH
    PRINT_CONSOLE("Patch : %s", LUAMOD_PATCH);
#endif
#ifdef DEBUG
    PRINT_CONSOLE("Compiler %s version %s", LUAMOD_COMPILER, LUAMOD_COMPILER_VER);
#endif
}

void cmd_luamod_pluginlist()
{
    
}

void cmd_luamod_load()
{
    
}

void cmd_luamod_runlua()
{
    
}

void cmd_luamod_egg()
{
    PRINT_CONSOLE("COW POWER 0_0 0_0");
}

void cmd_luamod_usage(void) {
	PRINT_CONSOLE("usage: luamod <command> [<arguments>]");
	PRINT_CONSOLE("   version          - display luamod version info");
	PRINT_CONSOLE("   list             - list plugins currently loaded");
	PRINT_CONSOLE("   load <name>      - load a plugin with the given name");
        PRINT_CONSOLE("   run <script>     - run lua script");
#ifdef DEBUG
        PRINT_CONSOLE("   debug_info       - more info");
#endif
}


void LuaMod_COMMAND(void)
{
    const char *cmd;

	cmd=CMD_ARGV(1);

	if(!strcasecmp(cmd, "version"))
		cmd_luamod_version();
	else if(!strcasecmp(cmd, "list"))
		cmd_luamod_pluginlist();
	else if(!strcasecmp(cmd, "load"))
		cmd_luamod_load();
        else if(!strcasecmp(cmd, "run"))
		cmd_luamod_runlua();
        else if(!strcasecmp(cmd, "egg"))
                cmd_luamod_egg();
        #ifdef DEBUG
        //else if(!strcasecmp(cmd, "debug_info"))
                //cmd_luamod_debug_info();
        #endif
	else {
		PRINT_CONSOLE("Unrecognized luamod command: %s", cmd);
		cmd_luamod_usage();
		return;
	}
}