#include "luamod.h"
#include "zone.h"

byte *lua_alloc_mempool;

void *zone_lua_alloc(void *ud, void *ptr, size_t osize, size_t nsize)
{
    (void)ud;
    (void)osize; /* not used */

    if (nsize == 0 && Mem_IsAllocatedExt(lua_alloc_mempool, ptr)) {
        // ALERT(at_console, "[ZONE] try to free allocated mem\n");
        Mem_Free(ptr);
        return NULL;
    } else if (nsize != 0 && Mem_IsAllocatedExt(lua_alloc_mempool, ptr)) {
        // ALERT(at_console, "[ZONE] try to realloc allocated mem %d %d\n", osize,
        // nsize);
        return _Mem_Realloc(lua_alloc_mempool, ptr, nsize, false, __FILE__, __LINE__);
    } else {
        // ALERT(at_console, "[ZONE] try to alloc mem %d\n", nsize);
        return Mem_Malloc(lua_alloc_mempool, nsize);
    }
}

void Lua_Alloc_Init(void) { lua_alloc_mempool = Mem_AllocPool("Lua allocator"); }
