#pragma once
#include <extdll.h>
#include <meta_api.h>
#include <string.h>

// yes its from sdk_util.h (metamod)
// Thanks Will Day
#define GET_INFOKEYBUFFER (*g_engfuncs.pfnGetInfoKeyBuffer)
#define INFOKEY_VALUE (*g_engfuncs.pfnInfoKeyValue)
#define SET_CLIENT_KEYVALUE (*g_engfuncs.pfnSetClientKeyValue)
#define REG_SVR_COMMAND (*g_engfuncs.pfnAddServerCommand)
//#define SERVER_PRINT		(*g_engfuncs.pfnServerPrint)
#define SET_SERVER_KEYVALUE (*g_engfuncs.pfnSetKeyValue)
#define QUERY_CLIENT_CVAR_VALUE (*g_engfuncs.pfnQueryClientCvarValue)
#define QUERY_CLIENT_CVAR_VALUE2 (*g_engfuncs.pfnQueryClientCvarValue2)

// Add overloaded ENTINDEX() version for const edict_t pointer.
// The pfnIndexOfEdict() function takes a const edict_t pointer
// as parameter anyway, so there is no reason why ENTINDEX()
// shouldn't.
inline int ENTINDEX(const edict_t *pEdict) { return ((*g_engfuncs.pfnIndexOfEdict)(pEdict)); }

// Also, create some nice inlines for engine callback combos.

// Get a setinfo value from a player entity.
inline char *ENTITY_KEYVALUE(edict_t *entity, char *key) { return (INFOKEY_VALUE(GET_INFOKEYBUFFER(entity), key)); }

// Set a setinfo value for a player entity.
inline void ENTITY_SET_KEYVALUE(edict_t *entity, char *key, char *value) { SET_CLIENT_KEYVALUE(ENTINDEX(entity), GET_INFOKEYBUFFER(entity), key, value); }

// Get a "serverinfo" value.
inline char *SERVERINFO(char *key) { return (ENTITY_KEYVALUE(INDEXENT(0), key)); }

// Set a "serverinfo" value.
inline void SET_SERVERINFO(char *key, char *value) { SET_SERVER_KEYVALUE(GET_INFOKEYBUFFER(INDEXENT(0)), key, value); }

// Get a "localinfo" value.
inline char *LOCALINFO(char *key) { return (ENTITY_KEYVALUE(NULL, key)); }

// Set a "localinfo" value.
inline void SET_LOCALINFO(char *key, char *value) { SET_SERVER_KEYVALUE(GET_INFOKEYBUFFER(NULL), key, value); }

inline int fast_FNullEnt(const edict_t *pent) { return (!pent || !(*g_engfuncs.pfnEntOffsetOfPEntity)(pent)); }

char *va(const char *fmt, ...);

void PRINT_CONSOLE(const char *fmt, ...);
