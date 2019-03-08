#include "callbacks.h"
#include "luamod.h"
#include "player.h"

#include "lua/lua_plugins.h"

void GameDLLInit(void)
{
    // ALERT(at_console, "[LM] GameDllInit\n");
    RETURN_META(MRES_IGNORED);
}

int pfnSpawn(edict_t *pent)
{
    // lua_State* L = nullptr; //g_luaworker->getToEvent("pfnSpawn");
    // if (L)
    //{
    // lua_pushlightuserdata(L, pent);
    // plugin_safecall(L, 1, 0);
    // }
    //   RETURN_META_VALUE(MRES_IGNORED, 0);
}

#include "utils.h"

qboolean pfnClientConnect(edict_t *pEntity, const char *pszName, const char *pszAddress, char szRejectReason[128])
{
    const char *pszName_fix = ENTITY_KEYVALUE(pEntity, "name");
    const char *pszAddress_fix = ENTITY_KEYVALUE(pEntity, "ip");

    LUAMOD_PUSH_PLAYER_DATA(pEntity, pszName_fix, pszAddress_fix);

#ifdef DEBUG
    ALERT(at_console, "[LM] Player %s Connected!!\n", pszName_fix);
#endif

    luamod_plugin *ptr = plugins_list;

    while (ptr != NULL) {

        if (plugin_have_event(ptr->L, "pfnClientConnect")) {
            lua_pushlightuserdata(ptr->L, pEntity);
            /*
           lua_pushstring(L, pszName);
           lua_pushstring(L, pszAddress);
           */
            lua_pushstring(ptr->L, pszName_fix);
            lua_pushstring(ptr->L, pszAddress_fix);
            plugin_safecall(ptr->L, 3, 0);
        }

        ptr = ptr->next;
    }
    RETURN_META_VALUE(MRES_HANDLED, 0);
}

void pfnClientDisconnect(edict_t *ed)
{

    luamod_plugin *ptr = plugins_list;

    while (ptr != NULL) {

        if (plugin_have_event(ptr->L, "pfnClientDisconnect")) {
            lua_pushlightuserdata(ptr->L, ed);
            plugin_safecall(ptr->L, 1, 0);
        }

        ptr = ptr->next;
    }

    LUAMOD_REMOVE_PLAYER_DATA(ed);

    RETURN_META(MRES_HANDLED);
}

void pfnClientKill(edict_t *ed)
{
    luamod_plugin *ptr = plugins_list;

    while (ptr != NULL) {

        if (plugin_have_event(ptr->L, "pfnClientKill")) {
            lua_pushlightuserdata(ptr->L, ed);
            plugin_safecall(ptr->L, 1, 0);
        }

        ptr = ptr->next;
    }

    RETURN_META(MRES_HANDLED);
}

void pfnClientPutInServer(edict_t *ed)
{
    LUAMOD_PUSH_PLAYER_DATA_PUTONSRV(ed);

    luamod_plugin *ptr = plugins_list;

    while (ptr != NULL) {

        if (plugin_have_event(ptr->L, "pfnClientPutInServer")) {
            lua_pushlightuserdata(ptr->L, ed);
            plugin_safecall(ptr->L, 1, 0);
        }

        ptr = ptr->next;
    }

    RETURN_META(MRES_IGNORED);
}

void pfnClientUserInfoChanged(edict_t *pEntity, char *pszInfoBuffer)
{
    // lua_State* L = nullptr;
    // //g_luaworker->getToEvent("pfnClientUserInfoChanged"); if (L)
    //{
    //    lua_pushlightuserdata(L, pEntity);
    //  plugin_safecall(L, 1, 0);
    //}
    // LUAMOD_UPDATE_PLAYERDATA(pEntity);
}

void pfnClientCommand(edict_t *ed)
{
    luamod_plugin *ptr = plugins_list;

    while (ptr != NULL) {

        if (plugin_have_event(ptr->L, "pfnClientCommand")) {
            lua_pushlightuserdata(ptr->L, ed);
            // Push table
            lua_newtable(ptr->L);
            for (int i = 0; i < CMD_ARGC(); i++) {
                lua_pushnumber(ptr->L, i + 1); // Key
                lua_pushstring(ptr->L, CMD_ARGV(i)); // Value
                lua_settable(ptr->L, -3);
            }
            lua_pushstring(ptr->L, CMD_ARGS());
            plugin_safecall(ptr->L, 3, 0);
        }

        ptr = ptr->next;
    }

    RETURN_META(MRES_HANDLED);
}

void pfnServerCommand(const char *str)
{
    /*ALERT(at_console, "[LM] Server command %s\n", str);
    auto states = eventServerCommand->states;
    for (int i = 0; i < states.size(); i++) {
      lua_getglobal(states[i], "event");
      lua_pcall(states[i], 0, 0, 0);
  }*/
    // RETURN_META_VALUE(MRES_IGNORED, 0);
}

void pfnCvarValue2(const edict_t *pEnt, int requestID, const char *pszCvarName, const char *pszValue)
{
    luamod_plugin *ptr = plugins_list;

    while (ptr != NULL) {

        if (plugin_have_event(ptr->L, "pfnCvarValue2")) {
            lua_pushlightuserdata(ptr->L, (edict_t *)pEnt);
            lua_pushnumber(ptr->L, requestID);
            lua_pushstring(ptr->L, pszCvarName);
            lua_pushstring(ptr->L, pszValue);
            plugin_safecall(ptr->L, 4, 0);
        }

        ptr = ptr->next;
    }

    RETURN_META(MRES_HANDLED);
}
