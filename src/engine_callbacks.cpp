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

void pfnMessageBegin(int msg_dest, int msg_type, const float *pOrigin, edict_t *pEntity)
{
    if (worker_have_event(core, "pfnMessageBegin")) {
        lua_pushnumber(core, msg_dest);
        lua_pushnumber(core, msg_type);
        lua_pushvec3_t(core, pOrigin);
        lua_pushedict(core, pEntity);
        worker_pcall(core, 4, 0);
    }
    RETURN_META(MRES_HANDLED);
}

void pfnMessageEnd(void)
{
    if (worker_have_event(core, "pfnMessageEnd")) {
        worker_pcall(core, 0, 0);
    }
    RETURN_META(MRES_HANDLED);
}

void pfnWriteByte(int iValue)
{
    if (worker_have_event(core, "pfnWriteByte")) {
        lua_pushnumber(core, iValue);
        worker_pcall(core, 1, 0);
    }
    RETURN_META(MRES_HANDLED);
}

void pfnWriteChar(int iValue)
{
    if (worker_have_event(core, "pfnWriteChar")) {
        lua_pushnumber(core, iValue);
        worker_pcall(core, 1, 0);
    }
    RETURN_META(MRES_HANDLED);
}

void pfnWriteShort(int iValue)
{
    if (worker_have_event(core, "pfnWriteShort")) {
        lua_pushnumber(core, iValue);
        worker_pcall(core, 1, 0);
    }
    RETURN_META(MRES_HANDLED);
}

void pfnWriteLong(int iValue)
{
    if (worker_have_event(core, "pfnWriteLong")) {
        lua_pushnumber(core, iValue);
        worker_pcall(core, 1, 0);
    }
    RETURN_META(MRES_HANDLED);
}

void pfnWriteAngle(float iValue)
{
    if (worker_have_event(core, "pfnWriteAngle")) {
        lua_pushnumber(core, iValue);
        worker_pcall(core, 1, 0);
    }
    RETURN_META(MRES_HANDLED);
}

void pfnWriteCoord(float iValue)
{
    if (worker_have_event(core, "pfnWriteCoord")) {
        lua_pushnumber(core, iValue);
        worker_pcall(core, 1, 0);
    }
    RETURN_META(MRES_HANDLED);
}

void pfnWriteString(const char* Value)
{
    if (worker_have_event(core, "pfnWriteString")) {
        lua_pushstring(core, Value);
        worker_pcall(core, 1, 0);
    }
    RETURN_META(MRES_HANDLED);
}

void pfnWriteEntity(int iValue)
{
    if (worker_have_event(core, "pfnWriteEntity")) {
        lua_pushnumber(core, iValue);
        worker_pcall(core, 1, 0);
    }
    RETURN_META(MRES_HANDLED);
}
