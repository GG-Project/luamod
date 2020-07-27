#include "callbacks.h"
#include "luamod.h"
#include "lua/lua_plugins.h"
#include "luamod_types.h"

extern luamod_plugin_t *plugins_list;

void GameDLLInit(void)
{
    RETURN_META(MRES_HANDLED);
}

int pfnSpawn(edict_t *pEntity)
{
    luamod_plugin_t *ptr = plugins_list;

    while (ptr != nullptr) {

        if (plugin_have_event(ptr->L, "pfnSpawn")) {
            lua_pushedict(ptr->L, pEntity);
            plugin_pcall(ptr->L, 1, 0);
        }

        ptr = ptr->m_next;
    }
    RETURN_META_VALUE(MRES_HANDLED, 0);
}

void pfnThink(edict_t *pEntity)
{
    luamod_plugin_t *ptr = plugins_list;

    while (ptr != nullptr) {

        if (plugin_have_event(ptr->L, "pfnThink")) {
            lua_pushedict(ptr->L, pEntity);
            plugin_pcall(ptr->L, 1, 0);
        }

        ptr = ptr->m_next;
    }
    RETURN_META(MRES_HANDLED);
}

void pfnUse(edict_t *pEntity_Used, edict_t *pEntity_Other)
{
    luamod_plugin_t *ptr = plugins_list;

    while (ptr != nullptr) {

        if (plugin_have_event(ptr->L, "pfnUse")) {
            lua_pushedict(ptr->L, pEntity_Used);
            lua_pushedict(ptr->L, pEntity_Other);
            plugin_pcall(ptr->L, 2, 0);
        }

        ptr = ptr->m_next;
    }
    RETURN_META(MRES_HANDLED);
}

void pfnTouch(edict_t *pEntity_Used, edict_t *pEntity_Other)
{
    luamod_plugin_t *ptr = plugins_list;

    while (ptr != nullptr) {

        if (plugin_have_event(ptr->L, "pfnTouch")) {
            lua_pushedict(ptr->L, pEntity_Used);
            lua_pushedict(ptr->L, pEntity_Other);
            plugin_pcall(ptr->L, 2, 0);
        }

        ptr = ptr->m_next;
    }
    RETURN_META(MRES_HANDLED);
}

void pfnBlocked(edict_t *pEntity_Used, edict_t *pEntity_Other)
{
    luamod_plugin_t *ptr = plugins_list;

    while (ptr != nullptr) {

        if (plugin_have_event(ptr->L, "pfnBlocked")) {
            lua_pushedict(ptr->L, pEntity_Used);
            lua_pushedict(ptr->L, pEntity_Other);
            plugin_pcall(ptr->L, 2, 0);
        }

        ptr = ptr->m_next;
    }
    RETURN_META(MRES_HANDLED);
}

void pfnKeyValue(edict_t *pEntity, KeyValueData *pkvd)
{
    luamod_plugin_t *ptr = plugins_list;

    while (ptr != nullptr) {

        if (plugin_have_event(ptr->L, "pfnKeyValue")) {
            lua_pushedict(ptr->L, pEntity);
            lua_pushlightuserdata(ptr->L, (void*)pkvd);
            plugin_pcall(ptr->L, 2, 0);
        }

        ptr = ptr->m_next;
    }
    RETURN_META(MRES_HANDLED);
}

#include "utils.h"

qboolean pfnClientConnect(edict_t *pEntity, const char *pszName, const char *pszAddress, char szRejectReason[128])
{
    const char *pszName_fix = ENTITY_KEYVALUE(pEntity, "name");
    const char *pszAddress_fix = ENTITY_KEYVALUE(pEntity, "ip");

    luamod_plugin_t *ptr = plugins_list;

    while (ptr != nullptr) {

        if (plugin_have_event(ptr->L, "pfnClientConnect")) {
            lua_pushedict(ptr->L, pEntity);
            /*
           lua_pushstring(L, pszName);
           lua_pushstring(L, pszAddress);
           */
            lua_pushstring(ptr->L, pszName_fix);
            lua_pushstring(ptr->L, pszAddress_fix);
            plugin_pcall(ptr->L, 3, 0);
        }

        ptr = ptr->m_next;
    }
    RETURN_META_VALUE(MRES_HANDLED, 0);
}

void pfnClientDisconnect(edict_t *pEntity)
{
    luamod_plugin_t *ptr = plugins_list;

    while (ptr != nullptr) {

        if (plugin_have_event(ptr->L, "pfnClientDisconnect")) {
            lua_pushedict(ptr->L, pEntity);
            plugin_pcall(ptr->L, 1, 0);
        }

        ptr = ptr->m_next;
    }

    RETURN_META(MRES_HANDLED);
}

void pfnClientKill(edict_t *pEntity)
{
    luamod_plugin_t *ptr = plugins_list;

    while (ptr != nullptr) {

        if (plugin_have_event(ptr->L, "pfnClientKill")) {
            lua_pushedict(ptr->L, pEntity);
            plugin_pcall(ptr->L, 1, 0);
        }

        ptr = ptr->m_next;
    }

    RETURN_META(MRES_HANDLED);
}

void pfnClientPutInServer(edict_t *pEntity)
{
    luamod_plugin_t *ptr = plugins_list;

    while (ptr != nullptr) {

        if (plugin_have_event(ptr->L, "pfnClientPutInServer")) {
            lua_pushedict(ptr->L, pEntity);
            plugin_pcall(ptr->L, 1, 0);
        }

        ptr = ptr->m_next;
    }

    RETURN_META(MRES_HANDLED);
}

void pfnClientUserInfoChanged(edict_t *pEntity, char *pszInfoBuffer)
{
  luamod_plugin_t *ptr = plugins_list;

  while (ptr != nullptr) {

      if (plugin_have_event(ptr->L, "pfnClientUserInfoChanged")) {
          lua_pushedict(ptr->L, pEntity);
	  lua_pushstring(ptr->L, pszInfoBuffer);
          plugin_pcall(ptr->L, 2, 0);
      }

      ptr = ptr->m_next;
  }

  RETURN_META(MRES_HANDLED);
}

void pfnClientCommand(edict_t *pEntity)
{
    luamod_plugin_t *ptr = plugins_list;

    gpMetaGlobals->mres = MRES_HANDLED;

    while (ptr != nullptr) {

        //if(!strncasecmp("say", CMD_ARGV(0), 4) || !strncasecmp("say_team", CMD_ARGV(0), 9))
        //  {
        //      gpMetaGlobals->mres = MRES_SUPERCEDE;
        //  } else {
        //      gpMetaGlobals->mres = MRES_HANDLED;
        //  }

        if (plugin_have_event(ptr->L, "pfnClientCommand")) {
            lua_pushedict(ptr->L, pEntity);
            // Push table
            lua_newtable(ptr->L);
            for (int i = 0; i < CMD_ARGC(); i++) {
                lua_pushnumber(ptr->L, i + 1); // Key
                lua_pushstring(ptr->L, CMD_ARGV(i)); // Value
                lua_settable(ptr->L, -3);
            }
            lua_pushstring(ptr->L, CMD_ARGS());
            plugin_pcall(ptr->L, 3, 0);
        }

        ptr = ptr->m_next;
    }

    RETURN_META(MRES_HANDLED);
    return;
}

void pfnPlayerPreThink(edict_t *pEntity)
{
  luamod_plugin_t *ptr = plugins_list;

  while (ptr != nullptr) {

      if (plugin_have_event(ptr->L, "pfnPlayerPreThink")) {
          lua_pushedict(ptr->L, pEntity);
          plugin_pcall(ptr->L, 1, 0);
      }

      ptr = ptr->m_next;
  }

  RETURN_META(MRES_HANDLED);
}

void pfnPlayerPostThink(edict_t *pEntity)
{
  luamod_plugin_t *ptr = plugins_list;

  while (ptr != nullptr) {

      if (plugin_have_event(ptr->L, "pfnPlayerPostThink")) {
          lua_pushedict(ptr->L, pEntity);
          plugin_pcall(ptr->L, 1, 0);
      }

      ptr = ptr->m_next;
  }

  RETURN_META(MRES_HANDLED);
}

void pfnStartFrame( void )
{
    luamod_plugin_t *ptr = plugins_list;

    while (ptr != nullptr) {

        if (plugin_have_event(ptr->L, "pfnStartFrame")) {
            plugin_pcall(ptr->L, 0, 0);
        }

        ptr = ptr->m_next;
    }

    RETURN_META(MRES_HANDLED);
}

void pfnParmsNewLevel( void )
{
    luamod_plugin_t *ptr = plugins_list;

    while (ptr != nullptr) {

        if (plugin_have_event(ptr->L, "pfnParmsNewLevel")) {
            plugin_pcall(ptr->L, 0, 0);
        }

        ptr = ptr->m_next;
    }

    RETURN_META(MRES_HANDLED);
}

void pfnParmsChangeLevel( void )
{
    luamod_plugin_t *ptr = plugins_list;

    while (ptr != nullptr) {

        if (plugin_have_event(ptr->L, "pfnParmsChangeLevel")) {
            plugin_pcall(ptr->L, 0, 0);
        }

        ptr = ptr->m_next;
    }

    RETURN_META(MRES_HANDLED);
}

void pfnServerCommand(const char *str)
{
    luamod_plugin_t *ptr = plugins_list;

    while (ptr != nullptr) {

        if (plugin_have_event(ptr->L, "pfnServerCommand")) {
            lua_pushstring(ptr->L, str);
            plugin_pcall(ptr->L, 1, 0);
        }

        ptr = ptr->m_next;
    }
}

void pfnCvarValue2(const edict_t *pEntity, int requestID, const char *pszCvarName, const char *pszValue)
{
    luamod_plugin_t *ptr = plugins_list;

    while (ptr != nullptr) {

        if (plugin_have_event(ptr->L, "pfnCvarValue2")) {
            lua_pushedict(ptr->L, (edict_t *)pEntity);
            lua_pushnumber(ptr->L, requestID);
            lua_pushstring(ptr->L, pszCvarName);
            lua_pushstring(ptr->L, pszValue);
            plugin_pcall(ptr->L, 4, 0);
        }

        ptr = ptr->m_next;
    }

    RETURN_META(MRES_HANDLED);
}
