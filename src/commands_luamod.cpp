#include <utils.h>
#include <extdll.h>
#include <meta_api.h>
#include "build.h"

#include <sqlite3.h>

#include "zone.h"

void cmd_luamod_version()
{
    PRINT_CONSOLE("LuaMod\n");
    PRINT_CONSOLE("Version : %s\n", LUAMOD_VERSION);
#ifdef DEBUG
    PRINT_CONSOLE("Build time : %s\n", __DATE__);
#endif
#ifdef LUAMOD_PATCH
    PRINT_CONSOLE("Patch : %s\n", LUAMOD_PATCH);
#endif
    PRINT_CONSOLE("OS : %s %s\n", LM_buildos(), LM_buildarch());
#ifdef DEBUG
    PRINT_CONSOLE("Compiler %s version %s\n", LM_buildcompiler(), LM_buildcompilerversion());
#endif
    PRINT_CONSOLE("Compiled with %s\n", LM_buildhlsdk());
    PRINT_CONSOLE("Compiled with %s\n", LM_buildlua());
    PRINT_CONSOLE("Compiled with libsqlite3 %s\n", sqlite3_version);
}

void cmd_luamod_pluginlist()
{
    
}

void List_Modules();

void cmd_luamod_modules()
{
  List_Modules();
}

void cmd_luamod_sqlite3()
{
    sqlite3_config(SQLITE_CONFIG_MEMSTATUS, 1);
    sqlite3_config(SQLITE_CONFIG_SERIALIZED);
    sqlite3_initialize();

    unsigned long long used = sqlite3_memory_used();
    unsigned long long peak = sqlite3_memory_highwater(0);

    PRINT_CONSOLE("Sqlite3 memory ^1%s\n", Q_memprint(used));
    PRINT_CONSOLE("Sqlite3 memory peak ^1%s\n", Q_memprint(peak));
}

void cmd_luamod_load()
{
    
}

void cmd_luamod_runlua()
{
    
}

void cmd_luamod_usage(void) {
	PRINT_CONSOLE("usage: luamod <command> [<arguments>]\n");
	PRINT_CONSOLE("   version          - display luamod version info\n");
    //PRINT_CONSOLE("   list             - list plugins currently loaded\n");
    PRINT_CONSOLE("   modules          - list modules \n");
    PRINT_CONSOLE("   memlist          - zone memory allocator statistic\n");
    PRINT_CONSOLE("   sqlite3          - sqlite memory info\n");
    //PRINT_CONSOLE("   load <name>      - load a plugin with the given name\n");
    //PRINT_CONSOLE("   run <script>     - run lua script\n");
#ifdef DEBUG
	PRINT_CONSOLE("   debug_info       - more info\n");
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
	else if(!strcasecmp(cmd, "modules"))
		cmd_luamod_modules();
	else if(!strcasecmp(cmd, "memlist"))
	  {
		Mem_PrintList(1<<30);
		Mem_PrintStats();
	  }
    else if(!strcasecmp(cmd, "sqlite3"))
        cmd_luamod_sqlite3();
	else if(!strcasecmp(cmd, "load"))
		cmd_luamod_load();
        else if(!strcasecmp(cmd, "run"))
		cmd_luamod_runlua();
        #ifdef DEBUG
        //else if(!strcasecmp(cmd, "debug_info"))
                //cmd_luamod_debug_info();
        #endif
	else {
		PRINT_CONSOLE("Unrecognized luamod command: %s\n", cmd);
		cmd_luamod_usage();
		return;
	}
}
