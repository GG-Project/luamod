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
  PRINT_CONSOLE("   list             - list plugins currently loaded\n");
  PRINT_CONSOLE("   cvars            - list cvars currently registred by luamod or plugins\n");
  // PRINT_CONSOLE("   sqlite3          - sqlite memory info\n");
  PRINT_CONSOLE("   load <name>      - load a plugin with the given name\n");
  PRINT_CONSOLE("   unload <name>    - unload a plugin with the given name\n");
  PRINT_CONSOLE("   restart <name>   - restart a plugin with the given name\n");
}

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
#if 0
    PRINT_CONSOLE("Compiled with libsqlite3 %s\n", sqlite3_version);
#endif
}

void Plugin_List();

void cmd_luamod_pluginlist() { Plugin_List(); }

void Cvar_Manager_List();

void cmd_luamod_cvarlist() { Cvar_Manager_List(); }

void cmd_luamod_sqlite3()
{
#if 0
    sqlite3_config(SQLITE_CONFIG_MEMSTATUS, 1);
    sqlite3_config(SQLITE_CONFIG_SERIALIZED);
    sqlite3_initialize();

    unsigned long long used = sqlite3_memory_used();
    unsigned long long peak = sqlite3_memory_highwater(0);

    PRINT_CONSOLE("Sqlite3 memory ^1%s\n", Q_memprint(used));
    PRINT_CONSOLE("Sqlite3 memory peak ^1%s\n", Q_memprint(peak));
#endif
}

void Plugin_Load(const char *filename);

void cmd_luamod_load()
{
  const char *filename = NULL;

  filename = CMD_ARGV(2);

  if(!filename)
    {
    cmd_luamod_usage();
    return;
    }

  Plugin_Load( filename );
}

void Plugin_Close( const char *filename );

void cmd_luamod_unload()
{
    const char *filename = NULL;

    filename = CMD_ARGV(2);

    if(!filename)
    {
        cmd_luamod_usage();
        return;
    }

    Plugin_Close( filename );
}

void Plugin_Restart( const char *filename );

void cmd_luamod_restart()
{
    const char *filename = NULL;

    filename = CMD_ARGV(2);

    if(!filename)
    {
        cmd_luamod_usage();
        return;
    }

    Plugin_Restart( filename );
}

void cmd_luamod_runlua() {}

void LuaMod_COMMAND(void)
{
    const char *cmd;

    cmd = CMD_ARGV(1);

    if (!strcasecmp(cmd, "version"))
        cmd_luamod_version();
    else if (!strcasecmp(cmd, "list"))
        cmd_luamod_pluginlist();
    else if(!strcasecmp(cmd, "cvars"))
      cmd_luamod_cvarlist();
    //else if (!strcasecmp(cmd, "sqlite3"))
        //cmd_luamod_sqlite3();
    else if (!strcasecmp(cmd, "load"))
        cmd_luamod_load();
    else if (!strcasecmp(cmd, "unload"))
        cmd_luamod_unload();
    else if (!strcasecmp(cmd, "restart"))
        cmd_luamod_restart();
    else {
        PRINT_CONSOLE("Unrecognized luamod command: %s\n", cmd);
        cmd_luamod_usage();
        return;
    }
}
