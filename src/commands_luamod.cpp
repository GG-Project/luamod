#include <luamod_utils.h>
#include <extdll.h>
#include <meta_api.h>

void cmd_luamod_version()
{
    PRINT_CONSOLE("LuaMod");
    PRINT_CONSOLE("Version : %s", LUAMOD_VERSION);
    PRINT_CONSOLE("Os : Linux %s", LUAMOD_ARCH);
#ifdef LUAMOD_PATCH
    PRINT_CONSOLE("Patch : %s", LUAMOD_PATCH);
#else
    PRINT_CONSOLE("Patch : none");
#endif
}

void cmd_luamod_pluginlist()
{
    
}

void cmd_luamod_load()
{
    
}

void cmd_luamod_usage(void) {
	PRINT_CONSOLE("usage: luamod <command> [<arguments>]");
	PRINT_CONSOLE("   version          - display luamod version info");
	PRINT_CONSOLE("   list             - list plugins currently loaded");
	PRINT_CONSOLE("   load <name>      - load a plugin with the given name");
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
	else {
		PRINT_CONSOLE("Unrecognized luamod command: %s", cmd);
		cmd_luamod_usage();
		return;
	}
}