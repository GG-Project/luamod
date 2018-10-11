#pragma once
#include <extdll.h>
#include <meta_api.h>
#include <string.h>

void LUAMOD_PUSH_PLAYER_DATA(edict_t *player_entity, const char *pszName, const char *pszAddress);
void LUAMOD_REMOVE_PLAYERDATA(edict_t *pEntity);
void LUAMOD_PUSH_PLAYER_DATA_PUTONSRV(edict_t *pEntity);
// players[]
const char *LUAMOD_GET_AUTHID_BY_EDICT(edict_t *pEntity);

#ifdef DEBUG
void LUAMOD_PRINT_DEBUG_PLAYER_DATA();
#endif

void PRINT_CONSOLE(const char *fmt, ...);
