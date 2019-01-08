#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

#include <luamod_api.h>
#include "luai.h"
#include "utils.h"
#include "parser.h"
#include "build.h"
#include "zone_luamod_mem.h"
#include "modules.h"
#include <luamod.h>
#include "module_api.h"

#define GetProcAddress dlsym
#define LoadLibrary(x) dlopen(x, RTLD_NOW)
typedef void* HINSTANCE;

#define MODULES_CONFIG_PATH "%s/addons/luamod/modules.ini"
#define MODULES_DIR_PATH "%s/addons/luamod/modules/%s_lm_%s.%s"
#define LIBRARY_PREFIX "so"

luamod_module_t *LUAMOD_MODULES;

luamod_funcs_t luamod_functions = {
    lua_checklstring,
    lua_checkinterger,
    lua_getuserdata,
    PRINT_CONSOLE,
    register_lua_function,
};

void List_Modules()
{
      PRINT_CONSOLE("Currently loaded modules:\n");
      PRINT_CONSOLE("      name             stat  file             version\n");

      luamod_module_t *ptr;

      ptr = LUAMOD_MODULES;

#define WIDTH_MAX_MODULES 2
#define WIDTH_MAX_NAME 10
#define WIDTH_MAX_VERSION 13

      int count = 1;

      while (ptr != NULL) {
          PRINT_CONSOLE(" [%*d] %*s      %s    %*s v%*s\n",
                        WIDTH_MAX_MODULES, count,
                        sizeof(ptr->module_info->name)-1, ptr->module_info->name,
                        ptr->running ? "OK" : "ERR",
                        strlen(ptr->filename)-1,ptr->filename,
                        strlen(ptr->module_info->version)-1,ptr->module_info->version
                        );

          ptr = ptr->next;
          count++;
      }
}

void Load_Module(const char *module_name)
{
   if(module_name[0] == 0)
        return;

    luamod_module_t *ptr, *ptr_tmp;

    ptr = (luamod_module_t*)Mem_Malloc(luamod_mem_pool, sizeof(luamod_module_t));

    //char buff[256];

    //snprintf(buff, sizeof(buff), MODULES_DIR_PATH, MOD_PATH, module_name, LM_buildarch(), LIBRARY_PREFIX);

    //void *module = dlopen(buff, RTLD_NOW);

    strncpy(ptr->filename, va("%s_lm_%s.%s", module_name, LM_buildarch(), LIBRARY_PREFIX), sizeof(ptr->filename));
    
    void *module = dlopen(va(MODULES_DIR_PATH, MOD_PATH, module_name, LM_buildarch(), LIBRARY_PREFIX), RTLD_NOW);

    void (*init_func)(luamod_funcs_t *, module_info_t **);
    
    void (*main_func)();

    void (*give_engfuncs)(enginefuncs_t *, globalvars_t *);
    
    if(!module)
    {
        ALERT(at_console, "[LM] Could not load module %s\n", dlerror());
    } else {
    
    init_func = (void (*)(luamod_funcs_t *, module_info_t **)) dlsym(module, "LuaMod_Module_Init");
    
    if(!init_func)
        ALERT(at_console, "[LM] Could not load module %s\n", dlerror());

    module_info_t *info;

    (*init_func)(&luamod_functions, &info);

    ptr->module_info = info;

    give_engfuncs = (void (*)(enginefuncs_t *, globalvars_t *)) dlsym(module, "GiveFnptrsToDll");

    if(!give_engfuncs)
        ALERT(at_console, "[LM] Could not load module %s\n", dlerror());

    (*give_engfuncs)(&g_engfuncs, gpGlobals);

    ptr->register_lua_funcs = (void (*)(lua_State *)) dlsym(module, "Register_Lua_Functions");

    if(!ptr->register_lua_funcs)
        ALERT(at_console, "[LM] Could not load module %s\n", dlerror());

    ALERT(at_console, "Author : %s Name : %s Date : %s\n", info->author, info->name, info->date);

    main_func = (void (*)()) dlsym(module, "Module_Main");

    if(!main_func)
      ALERT(at_console, "[LM] Could not load module %s\n", dlerror());

    (*main_func)();

    ptr->running = 1;

    ptr_tmp = LUAMOD_MODULES;

    ptr->next = ptr_tmp;

    LUAMOD_MODULES = ptr;

    }
}

void Parse_And_Load_Modules()
{
    char buff[256],buff2[256];

    //snprintf(buff, sizeof(buff), MODULES_CONFIG_PATH, MOD_PATH);

    FILE *config = fopen(va(MODULES_CONFIG_PATH, MOD_PATH), "r");

    if(!config) { ALERT(at_console, "[LM] Error opening module config %s\n", va(MODULES_CONFIG_PATH, MOD_PATH)); return; }

    while (!ferror(config) && fgets(buff2, sizeof(buff2), config) != NULL) {
            StripCommentary(buff, buff2, sizeof(buff2));
            Load_Module(buff);
    }

    fclose(config);
}
