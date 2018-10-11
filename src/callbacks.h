#pragma once
#include <extdll.h>
#include <meta_api.h>

void GameDLLInit( void );
//
int pfnSpawn( edict_t *pent );
//
qboolean pfnClientConnect( edict_t *pEntity, const char *pszName, const char *pszAddress, char szRejectReason[ 128 ] );
void pfnClientDisconnect(edict_t *pEntity);
void pfnClientCommand(edict_t* ed);
void pfnClientKill(edict_t* ed);
void pfnClientPutInServer(edict_t* ed);
//
void pfnServerCommand(const char* str);
