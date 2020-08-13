#pragma once
#include <extdll.h>
#include <meta_api.h>

void GameDLLInit(void);
//
int pfnSpawn(edict_t *pEntity);
void pfnThink(edict_t *pEntity);
void pfnUse(edict_t *pEntity_Used, edict_t *pEntity_Other);
void pfnTouch(edict_t *pEntity_Used, edict_t *pEntity_Other);
void pfnBlocked(edict_t *pEntity_Used, edict_t *pEntity_Other);
void pfnKeyValue(edict_t *pEntity, KeyValueData *pkvd);
//
qboolean pfnClientConnect(edict_t *pEntity, const char *pszName, const char *pszAddress, char szRejectReason[128]);
void pfnClientDisconnect(edict_t *pEntity);
void pfnClientCommand(edict_t *pEntity);
void pfnClientKill(edict_t *pEntity);
void pfnClientPutInServer(edict_t *pEntity);
void pfnClientUserInfoChanged(edict_t *pEntity, char *pszInfoBuffer);
//
void pfnPlayerPreThink( edict_t *pEntity );
void pfnPlayerPostThink( edict_t *pEntity );
//
void pfnStartFrame(void);
//
void pfnParmsNewLevel(void);
void pfnParmsChangeLevel(void);
//
void pfnServerCommand(const char *str);

// new api
void pfnCvarValue2(const edict_t *pEntity, int requestID, const char *pszCvarName, const char *pszValue);
