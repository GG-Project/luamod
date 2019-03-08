#include "zone_luamod_mem.h"
#include <extdll.h>

typedef struct cvar_manager_s {
    cvar_t *cvar;
    char registred_by[256];
    struct cvar_manager_s *next;
} cvar_manager;

cvar_manager *cvar_manager_pool;

static byte *cvar_mempool;

cvar_manager *Cvar_Manager_Alloc()
{
    cvar_manager *ptr = (cvar_manager *)Mem_Malloc(cvar_mempool, sizeof(cvar_manager));
    ptr->cvar = (cvar_t *)Mem_Malloc(cvar_mempool, sizeof(cvar_t));
    return ptr;
}

cvar_t *Cvar_Manager_Register(const char *cvar_name, float value, const char *string)
{
    cvar_manager *ptr = Cvar_Manager_Alloc();

    if (!string) {
        ptr->cvar->value = value;
    } else {
        ptr->cvar->string = string;
    }

    ptr->cvar->flags | FCVAR_SERVER;

    return ptr->cvar;
}

void Cvar_Manager_Init(void) { cvar_mempool = Mem_AllocPool("Cvar mempool"); }
