#ifndef PLAYER_H
#define PLAYER_H

#include <extdll.h>
#include <meta_api.h>
#include <string.h>

void LUAMOD_PUSH_PLAYER_DATA(edict_t *player_entity, const char *pszName, const char *pszAddress);
void LUAMOD_REMOVE_PLAYER_DATA(edict_t *pEntity);
void LUAMOD_UPDATE_PLAYERDATA(edict_t *pEntity);
void LUAMOD_PUSH_PLAYER_DATA_PUTONSRV(edict_t *pEntity);
// players[]
const char *LUAMOD_GET_AUTHID_BY_EDICT(edict_t *pEntity);

#ifdef DEBUG
void LUAMOD_PRINT_DEBUG_PLAYER_DATA();
#endif

#pragma pack(0)
struct LUAMOD_PLAYER_DATA
{
    char player_name[32];
    edict_t *player_edict;
    char player_address[32];
    qboolean player_put_on_server = false;
    qboolean free = true;
};
#pragma pack()

#endif // PLAYER_H
