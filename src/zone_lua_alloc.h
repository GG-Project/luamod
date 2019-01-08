#ifndef ZONE_LUA_ALLOC_H
#define ZONE_LUA_ALLOC_H

#include <stddef.h>

void *zone_lua_alloc (void *ud, void *ptr, size_t osize, size_t nsize);

#endif // ZONE_LUA_ALLOC_H
