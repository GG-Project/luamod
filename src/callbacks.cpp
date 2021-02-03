#include "callbacks.h"
#include "luamod.h"
#include "lua/lua_worker.h"
#include "luamod_types.h"

#undef RETURN_META
#undef RETURN_META_VALUE

#define RETURN_META(x) \
    do { if(gpMetaGlobals->mres != MRES_SUPERCEDE && gpMetaGlobals->mres != MRES_OVERRIDE) { gpMetaGlobals->mres = x; } return; } while(0)

#define RETURN_META_VALUE(x, x2) \
    do { if(gpMetaGlobals->mres != MRES_SUPERCEDE && gpMetaGlobals->mres != MRES_OVERRIDE) { gpMetaGlobals->mres = x; } return x2; } while(0)

void GameDLLInit(void)
{
    RETURN_META(MRES_HANDLED);
}

int pfnSpawn(edict_t *pEntity)
{
    if (worker_have_event(core, "pfnSpawn")) {
        lua_pushedict(core, pEntity);
        worker_pcall(core, 1, 0);
    }
    RETURN_META_VALUE(MRES_HANDLED, 0);
}

void pfnThink(edict_t *pEntity)
{
    if (worker_have_event(core, "pfnThink")) {
        lua_pushedict(core, pEntity);
        worker_pcall(core, 1, 0);
    }
    RETURN_META(MRES_HANDLED);
}

void pfnUse(edict_t *pEntity_Used, edict_t *pEntity_Other)
{
    if (worker_have_event(core, "pfnUse")) {
        lua_pushedict(core, pEntity_Used);
        lua_pushedict(core, pEntity_Other);
        worker_pcall(core, 2, 0);
    }
    RETURN_META(MRES_HANDLED);
}

void pfnTouch(edict_t *pEntity_Used, edict_t *pEntity_Other)
{
    if (worker_have_event(core, "pfnTouch")) {
        lua_pushedict(core, pEntity_Used);
        lua_pushedict(core, pEntity_Other);
        worker_pcall(core, 2, 0);
    }
    RETURN_META(MRES_HANDLED);
}

void pfnBlocked(edict_t *pEntity_Used, edict_t *pEntity_Other)
{
    if (worker_have_event(core, "pfnBlocked")) {
        lua_pushedict(core, pEntity_Used);
        lua_pushedict(core, pEntity_Other);
        worker_pcall(core, 2, 0);
    }
    RETURN_META(MRES_HANDLED);
}

void pfnKeyValue(edict_t *pEntity, KeyValueData *pkvd)
{
    if (worker_have_event(core, "pfnKeyValue")) {
        lua_pushedict(core, pEntity);
        lua_pushlightuserdata(core, (void*)pkvd);
        worker_pcall(core, 2, 0);
    }
    RETURN_META(MRES_HANDLED);
}

#include "utils.h"

qboolean pfnClientConnect(edict_t *pEntity, const char *pszName, const char *pszAddress, char szRejectReason[128])
{
    const char *pszName_fix = ENTITY_KEYVALUE(pEntity, "name");
    const char *pszAddress_fix = ENTITY_KEYVALUE(pEntity, "ip");

    if (worker_have_event(core, "pfnClientConnect")) {
        lua_pushedict(core, pEntity);
/*
           lua_pushstring(L, pszName);
           lua_pushstring(L, pszAddress);
*/
        lua_pushstring(core, pszName_fix);
        lua_pushstring(core, pszAddress_fix);
        worker_pcall(core, 3, 0);
    }
    RETURN_META_VALUE(MRES_HANDLED, 0);
}

void pfnClientDisconnect(edict_t *pEntity)
{
    if (worker_have_event(core, "pfnClientDisconnect")) {
        lua_pushedict(core, pEntity);
        worker_pcall(core, 1, 0);
    }
    RETURN_META(MRES_HANDLED);
}

void pfnClientKill(edict_t *pEntity)
{
    if (worker_have_event(core, "pfnClientKill")) {
        lua_pushedict(core, pEntity);
        worker_pcall(core, 1, 0);
    }
    RETURN_META(MRES_HANDLED);
}

void pfnClientPutInServer(edict_t *pEntity)
{
    if (worker_have_event(core, "pfnClientPutInServer")) {
        lua_pushedict(core, pEntity);
        worker_pcall(core, 1, 0);
    }
    RETURN_META(MRES_HANDLED);
}

void pfnClientUserInfoChanged(edict_t *pEntity, char *pszInfoBuffer)
{
    if (worker_have_event(core, "pfnClientUserInfoChanged")) {
        lua_pushedict(core, pEntity);
        lua_pushstring(core, pszInfoBuffer);
        worker_pcall(core, 2, 0);
    }
    RETURN_META(MRES_HANDLED);
}

void pfnClientCommand(edict_t *pEntity)
{
    if (worker_have_event(core, "pfnClientCommand")) {
        lua_pushedict(core, pEntity);
        // Push table
        lua_newtable(core);
        for (int i = 0; i < CMD_ARGC(); i++) {
            lua_pushnumber(core, i + 1); // Key
            lua_pushstring(core, CMD_ARGV(i)); // Value
            lua_settable(core, -3);
        }
        lua_pushstring(core, CMD_ARGS());
        worker_pcall(core, 3, 0);
    }
    RETURN_META(MRES_HANDLED);
}

void pfnPlayerPreThink(edict_t *pEntity)
{
    if (worker_have_event(core, "pfnPlayerPreThink")) {
        lua_pushedict(core, pEntity);
        worker_pcall(core, 1, 0);
    }
    RETURN_META(MRES_HANDLED);
}

void pfnPlayerPostThink(edict_t *pEntity)
{
    if (worker_have_event(core, "pfnPlayerPostThink")) {
        lua_pushedict(core, pEntity);
        worker_pcall(core, 1, 0);
    }
    RETURN_META(MRES_HANDLED);
}

void pfnStartFrame( void )
{
    if (worker_have_event(core, "pfnStartFrame")) {
        worker_pcall(core, 0, 0);
    }
    RETURN_META(MRES_HANDLED);
}

void pfnParmsNewLevel( void )
{
    if (worker_have_event(core, "pfnParmsNewLevel")) {
        worker_pcall(core, 0, 0);
    }
    RETURN_META(MRES_HANDLED);
}

void pfnParmsChangeLevel( void )
{
    if (worker_have_event(core, "pfnParmsChangeLevel")) {
        worker_pcall(core, 0, 0);
    }
    RETURN_META(MRES_HANDLED);
}

void pfnServerCommand(const char *str)
{
    if (worker_have_event(core, "pfnServerCommand")) {
        lua_pushstring(core, str);
        worker_pcall(core, 1, 0);
    }
    RETURN_META(MRES_HANDLED);
}

void pfnCvarValue2(const edict_t *pEntity, int requestID, const char *pszCvarName, const char *pszValue)
{
    if (worker_have_event(core, "pfnCvarValue2")) {
        lua_pushedict(core, (edict_t *)pEntity);
        lua_pushnumber(core, requestID);
        lua_pushstring(core, pszCvarName);
        lua_pushstring(core, pszValue);
        worker_pcall(core, 4, 0);
    }
    RETURN_META(MRES_HANDLED);
}
