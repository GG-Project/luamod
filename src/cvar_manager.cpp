#include <extdll.h>
#include <assert.h>
#include "luamod_meta_api.h"
#include "utils.h"
/*
typedef struct cvar_manager_s {
    cvar_t *cvar;
    char registred_by[256];
    struct cvar_manager_s *next;
} cvar_manager;

cvar_manager *cvar_manager_pool;
*/
void Cvar_Manager_List()
{
/*
  cvar_manager *ptr = cvar_manager_pool;

  PRINT_CONSOLE("Cvar list:\n");
  PRINT_CONSOLE("      name          value          string\n");

#define WIDTH_MAX_CVAR 2

  int count = 1;

  while(ptr != NULL)
    {
      PRINT_CONSOLE(" [%*d] %s          %f          %s\n", WIDTH_MAX_CVAR, count, ptr->cvar->name, ptr->cvar->value, ptr->cvar->string ? "NULL" : ptr->cvar->string);

      count++;
      ptr = ptr->next;
    }
*/
}
/*
cvar_manager *Cvar_Manager_Alloc()
{
    cvar_manager *ptr = (cvar_manager *)malloc(sizeof(cvar_manager));
    return ptr;
}
*/
void Cvar_Manager_Register(const char *cvar_name, float value, const char *string)
{
    assert(cvar_name);
    // Metamod overload function pfnCVarRegister and pfnCvar_RegisterVariable (cvar allocated in metamod DLL)
    // We need use pfnCVarGet* pfnCVarSet*
    //cvar_manager *ptr = Cvar_Manager_Alloc();

    cvar_t stack_cvar = {cvar_name, string ? NULL : (char*)string, 0, value, NULL};

    //ptr->next = cvar_manager_pool;
    //cvar_manager_pool = ptr;

    CVAR_REGISTER(&stack_cvar);
}
