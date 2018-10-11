#include "callbacks.h"
#include "utils.h"
#include "luamod.h"
#include "lua/CLuaWorker.hpp"

LUAMOD_PLAYER_DATA PLAYERS[32];

void GameDLLInit( void )
{
        //здесь нужно что нибудь сделать
        //ALERT(at_console, "[LM] GameDllInit\n");
        RETURN_META(MRES_IGNORED);
}

int pfnSpawn( edict_t *pent )
{
    lua_State* L = g_luaworker->getToEvent("pfnSpawn");
    if (!L) return 0;

    lua_pushlightuserdata(L, pent);
    g_luaworker->safeCall(L, 1, 0);
    
    RETURN_META_VALUE(MRES_IGNORED, 0);
}

qboolean pfnClientConnect( edict_t* pEntity, const char *pszName, const char *pszAddress, char szRejectReason[ 128 ] ) 
{
    bool connected;

    connected = MDLL_ClientConnect(pEntity, pszName, pszAddress, szRejectReason);
    //if(connected == true) {

    int i;
    for (i = 0; i < 32; i++) {
        if (PLAYERS[i].free == true) {
            strncpy(PLAYERS[i].player_name, pszName, sizeof(PLAYERS[i].player_name));
            PLAYERS[i].player_edict = pEntity;
            //strncpy(PLAYERS[i].player_authid, GETPLAYERAUTHID(pEntity), sizeof(PLAYERS[i].player_authid));
            strncpy(PLAYERS[i].player_address, pszAddress, sizeof(PLAYERS[i].player_address));
            PLAYERS[i].player_put_on_server = false;
            PLAYERS[i].free = false;
            break;
        }
    }

    #ifdef DEBUG
    void LUAMOD_PRINT_DEBUG_PLAYER_DATA();
    
    
    ALERT(at_console, "[LM] Player %s Connected!!\n", PLAYERS[i].player_name);
    #endif
//}
    RETURN_META_VALUE(MRES_SUPERCEDE, connected);
}

void pfnClientDisconnect( edict_t* ed ) {
//    lua_State* L = g_luaworker->getToEvent("pfnClientDisconnect");
//    if (!L) return;

    LUAMOD_REMOVE_PLAYERDATA(ed);
    
//    lua_pushlightuserdata(L, ed);
//    g_luaworker->safeCall(L, 1, 0);
}

void pfnClientKill( edict_t* ed )
{
    lua_State* L = g_luaworker->getToEvent("pfnClientKill");
    if (!L) return;

    lua_pushlightuserdata(L, ed);
    g_luaworker->safeCall(L, 1, 0);
}

void pfnClientPutInServer( edict_t* ed ) {
//    lua_State* L = g_luaworker->getToEvent("pfnClientPutInServer");
//    if (!L) return;
        
    LUAMOD_PUSH_PLAYER_DATA_PUTONSRV(ed);
    
//    lua_pushlightuserdata(L, ed);
//    g_luaworker->safeCall(L, 1, 0);
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
