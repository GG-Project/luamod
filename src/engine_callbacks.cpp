#include "callbacks.h"
#include "luamod.h"
#include "lua/lua_plugins.h"
#include "luamod_types.h"

extern luamod_plugin_t *plugins_list;

#undef RETURN_META
#undef RETURN_META_VALUE

#define RETURN_META(x) \
    do { if(gpMetaGlobals->mres != MRES_SUPERCEDE && gpMetaGlobals->mres != MRES_OVERRIDE) { gpMetaGlobals->mres = x; } return; } while(0)

#define RETURN_META_VALUE(x, x2) \
    do { if(gpMetaGlobals->mres != MRES_SUPERCEDE && gpMetaGlobals->mres != MRES_OVERRIDE) { gpMetaGlobals->mres = x; } return x2; } while(0)

void pfnMessageBegin(int msg_dest, int msg_type, const float *pOrigin, edict_t *pEntity)
{
    luamod_plugin_t *ptr = plugins_list;

    while (ptr != nullptr) {

        if (plugin_have_event(ptr->L, "pfnMessageBegin")) {
            lua_pushnumber(ptr->L, msg_dest);
            lua_pushnumber(ptr->L, msg_type);
            lua_pushvec3_t(ptr->L, pOrigin);
            lua_pushedict(ptr->L, pEntity);
            plugin_pcall(ptr->L, 4, 0);
        }

        ptr = ptr->m_next;
    }

    RETURN_META(MRES_HANDLED);
}

void pfnMessageEnd(void)
{
    luamod_plugin_t *ptr = plugins_list;

    while (ptr != nullptr) {

        if (plugin_have_event(ptr->L, "pfnMessageEnd")) {
            plugin_pcall(ptr->L, 0, 0);
        }

        ptr = ptr->m_next;
    }

    RETURN_META(MRES_HANDLED);
}

void pfnWriteByte(int iValue)
{
    luamod_plugin_t *ptr = plugins_list;

    while (ptr != nullptr) {

        if (plugin_have_event(ptr->L, "pfnWriteByte")) {
            lua_pushnumber(ptr->L, iValue);
            plugin_pcall(ptr->L, 1, 0);
        }

        ptr = ptr->m_next;
    }

    RETURN_META(MRES_HANDLED);
}

void pfnWriteChar(int iValue)
{
    luamod_plugin_t *ptr = plugins_list;

    while (ptr != nullptr) {

        if (plugin_have_event(ptr->L, "pfnWriteChar")) {
            lua_pushnumber(ptr->L, iValue);
            plugin_pcall(ptr->L, 1, 0);
        }

        ptr = ptr->m_next;
    }

    RETURN_META(MRES_HANDLED);
}

void pfnWriteShort(int iValue)
{
    luamod_plugin_t *ptr = plugins_list;

    while (ptr != nullptr) {

        if (plugin_have_event(ptr->L, "pfnWriteShort")) {
            lua_pushnumber(ptr->L, iValue);
            plugin_pcall(ptr->L, 1, 0);
        }

        ptr = ptr->m_next;
    }

    RETURN_META(MRES_HANDLED);
}

void pfnWriteLong(int iValue)
{
    luamod_plugin_t *ptr = plugins_list;

    while (ptr != nullptr) {

        if (plugin_have_event(ptr->L, "pfnWriteLong")) {
            lua_pushnumber(ptr->L, iValue);
            plugin_pcall(ptr->L, 1, 0);
        }

        ptr = ptr->m_next;
    }

    RETURN_META(MRES_HANDLED);
}

void pfnWriteAngle(float iValue)
{
    luamod_plugin_t *ptr = plugins_list;

    while (ptr != nullptr) {

        if (plugin_have_event(ptr->L, "pfnWriteAngle")) {
            lua_pushnumber(ptr->L, iValue);
            plugin_pcall(ptr->L, 1, 0);
        }

        ptr = ptr->m_next;
    }

    RETURN_META(MRES_HANDLED);
}

void pfnWriteCoord(float iValue)
{
    luamod_plugin_t *ptr = plugins_list;

    while (ptr != nullptr) {

        if (plugin_have_event(ptr->L, "pfnWriteCoord")) {
            lua_pushnumber(ptr->L, iValue);
            plugin_pcall(ptr->L, 1, 0);
        }

        ptr = ptr->m_next;
    }

    RETURN_META(MRES_HANDLED);
}

void pfnWriteString(const char* Value)
{
    luamod_plugin_t *ptr = plugins_list;

    while (ptr != nullptr) {

        if (plugin_have_event(ptr->L, "pfnWriteString")) {
            lua_pushstring(ptr->L, Value);
            plugin_pcall(ptr->L, 1, 0);
        }

        ptr = ptr->m_next;
    }

    RETURN_META(MRES_HANDLED);
}

void pfnWriteEntity(int iValue)
{
    luamod_plugin_t *ptr = plugins_list;

    while (ptr != nullptr) {

        if (plugin_have_event(ptr->L, "pfnWriteEntity")) {
            lua_pushnumber(ptr->L, iValue);
            plugin_pcall(ptr->L, 1, 0);
        }

        ptr = ptr->m_next;
    }

    RETURN_META(MRES_HANDLED);
}
