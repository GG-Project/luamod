#include "callbacks.h"
#include "player.h"
#include "luamod.h"
#include "lua/CLuaWorker.hpp"

void GameDLLInit( void )
{
        //ALERT(at_console, "[LM] GameDllInit\n");
        RETURN_META(MRES_IGNORED);
}

int pfnSpawn( edict_t *pent )
{
    lua_State* L = g_luaworker->getToEvent("pfnSpawn");

    if (L)
    {
        lua_pushlightuserdata(L, pent);
        g_luaworker->safeCall(L, 1, 0);
    }

    RETURN_META_VALUE(MRES_IGNORED, 0);
}

//HACK HACK
//
#include "utils.h"

qboolean pfnClientConnect( edict_t* pEntity, const char *pszName, const char *pszAddress, char szRejectReason[ 128 ] ) 
{
    //qboolean connected;

    //connected = MDLL_ClientConnect(pEntity, pszName, pszAddress, szRejectReason);

    LUAMOD_PUSH_PLAYER_DATA(pEntity, pszName, pszAddress);

#ifdef DEBUG
      ALERT(at_console, "[LM] Player %s Connected!!\n", pszName);
#endif

    lua_State* L = g_luaworker->getToEvent("pfnClientConnect");

    if (L)
    {
        lua_pushlightuserdata(L, pEntity);
        /*
        lua_pushstring(L, pszName);
        lua_pushstring(L, pszAddress);
        */
        lua_pushstring(L, ENTITY_KEYVALUE(pEntity, "name"));
        lua_pushstring(L, ENTITY_KEYVALUE(pEntity, "ip"));
        g_luaworker->safeCall(L, 3, 0);
    }

    //RETURN_META_VALUE(MRES_IGNORED, connected);
    RETURN_META_VALUE(MRES_IGNORED, 0);
}

void pfnClientDisconnect( edict_t* ed ) {
    lua_State* L = g_luaworker->getToEvent("pfnClientDisconnect");

    if (L)
      {
        lua_pushlightuserdata(L, ed);
        g_luaworker->safeCall(L, 1, 0);
      }

    LUAMOD_REMOVE_PLAYER_DATA(ed);

    RETURN_META(MRES_IGNORED);
}

void pfnClientKill( edict_t* ed )
{
    lua_State* L = g_luaworker->getToEvent("pfnClientKill");
    if (!L) return;

    lua_pushlightuserdata(L, ed);
    g_luaworker->safeCall(L, 1, 0);

    RETURN_META(MRES_IGNORED);
}

void pfnClientPutInServer( edict_t* ed ) {
    lua_State* L = g_luaworker->getToEvent("pfnClientPutInServer");

     LUAMOD_PUSH_PLAYER_DATA_PUTONSRV(ed);

    if (L)
      {
            lua_pushlightuserdata(L, ed);
            g_luaworker->safeCall(L, 1, 0);
      }

      RETURN_META(MRES_IGNORED);
}

void pfnClientUserInfoChanged(edict_t *pEntity, char *pszInfoBuffer)
{

  lua_State* L = g_luaworker->getToEvent("pfnClientUserInfoChanged");

  if (L)
    {
          lua_pushlightuserdata(L, pEntity);
          g_luaworker->safeCall(L, 1, 0);
    }

    //LUAMOD_UPDATE_PLAYERDATA(pEntity);
}


void pfnClientCommand( edict_t* ed ) {
    lua_State* L = g_luaworker->getToEvent("pfnClientCommand");
    if (!L) return;

    lua_pushlightuserdata(L, ed);
    // Push table
    lua_newtable(L);
    for (int i = 0; i < CMD_ARGC(); i++) {
        lua_pushnumber(L, i + 1); // Key
        lua_pushstring(L, CMD_ARGV(i)); // Value
        lua_settable(L, -3);
    }
    lua_pushstring(L, CMD_ARGS());
    g_luaworker->safeCall(L, 3, 0);

    RETURN_META(MRES_IGNORED);
}

void pfnServerCommand( const char* str ) {
    /*ALERT(at_console, "[LM] Server command %s\n", str);
    auto states = eventServerCommand->states;
    for (int i = 0; i < states.size(); i++) {
      lua_getglobal(states[i], "event");
      lua_pcall(states[i], 0, 0, 0);
  }*/
    //RETURN_META_VALUE(MRES_IGNORED, 0);
}

void pfnCvarValue(const edict_t *pEnt, const char *pszValue)
{
  lua_State* L = g_luaworker->getToEvent("pfnCvarValue");

  if (!L) return;

  lua_pushlightuserdata(L, (edict_t*)pEnt);
  lua_pushstring(L, CMD_ARGS());
  g_luaworker->safeCall(L, 2, 0);

  RETURN_META(MRES_IGNORED);
}

void pfnCvarValue2(const edict_t *pEnt, int requestID, const char *pszCvarName, const char *pszValue)
{
    ALERT( at_console, "cvar_name : %s cvar_value : %s requestid : %d\n", pszCvarName, pszValue, requestID );

    lua_State* L = g_luaworker->getToEvent("pfnCvarValue2");

    if (!L) return;

    lua_pushlightuserdata(L, (edict_t*)pEnt);
    lua_pushnumber(L, requestID);
    lua_pushstring(L, pszCvarName);
    lua_pushstring(L, pszValue);
    g_luaworker->safeCall(L, 4, 0);

    RETURN_META(MRES_IGNORED);
}
