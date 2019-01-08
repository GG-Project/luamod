#include "luamod.h"
#include <extdll.h>
#include <meta_api.h>

#include "player.h"

extern globalvars_t *gpGlobals;

LUAMOD_PLAYER_DATA PLAYERS[32];

#ifdef DEBUG
void LUAMOD_PRINT_DEBUG_PLAYER_DATA()
{
    for(int i = 0; i < gpGlobals->maxClients; i++)
    {
            //ALERT(at_console, "[LM] Name : %s Address : %s AuthID = %s PutInServer %d\n", PLAYERS[i].player_name, PLAYERS[i].player_address, PLAYERS[i].player_authid, PLAYERS[i].player_put_on_server);
            ALERT(at_console, "[LM] Name : %s AUTHID : %s Address : %s PutInServer %d\n", PLAYERS[i].player_name, GETPLAYERAUTHID(PLAYERS[i].player_edict), PLAYERS[i].player_address, PLAYERS[i].player_put_on_server);
    }
}
#endif

//HACK HACK: amxmodx break pfnClienConnect need get names from ENTITY_KEYVALUE
//TODO: need to find not hack hack fix
#include "utils.h"

void LUAMOD_PUSH_PLAYER_DATA(edict_t *pEntity, const char *pszName, const char *pszAddress)
{  
  for (int i = 0; i < 32; i++) {

      if(PLAYERS[i].free == true)
        {
          /*
          strncpy(PLAYERS[i].player_name, pszName, sizeof(PLAYERS[i].player_name));
          strncpy(PLAYERS[i].player_address, pszAddress, sizeof(PLAYERS[i].player_address));
          strncpy(PLAYERS[i].player_authid, GETPLAYERAUTHID(pEntity), sizeof(PLAYERS[i].player_authid));
          */

          strncpy(PLAYERS[i].player_name, ENTITY_KEYVALUE(pEntity, "name"), sizeof(PLAYERS[i].player_name));
          strncpy(PLAYERS[i].player_address, ENTITY_KEYVALUE(pEntity, "ip"), sizeof(PLAYERS[i].player_address));

          PLAYERS[i].player_edict = pEntity;
          PLAYERS[i].player_put_on_server = false;
          PLAYERS[i].free = false;
          break;
          }
  }

  #ifdef DEBUG
  void LUAMOD_PRINT_DEBUG_PLAYER_DATA();
  #endif
}

void LUAMOD_UPDATE_PLAYERDATA(edict_t *pEntity)
{

    for(int i = 0; i < 32; i++)
    {
        //if(PLAYERS[i].player_edict == pEntity)
        //  {
        //    memset(PLAYERS[i].player_name, 0, sizeof(PLAYERS[i].player_name));
        //    strncpy(PLAYERS[i].player_name, ENTITY_KEYVALUE(pEntity, "name"), sizeof(PLAYERS[i].player_name));
            break;
        //  }
    }

#ifdef DEBUG
LUAMOD_PRINT_DEBUG_PLAYER_DATA();
#endif
}

void LUAMOD_REMOVE_PLAYER_DATA(edict_t *pEntity)
{
    for(int i = 0; i < 32; i++)
    {
        if( PLAYERS[i].player_edict == pEntity )
          {
            PLAYERS[i].player_edict = NULL;
            memset(PLAYERS[i].player_name, 0, sizeof(PLAYERS[i].player_name));
            memset(PLAYERS[i].player_address, 0, sizeof(PLAYERS[i].player_address));
            PLAYERS[i].player_put_on_server = false;
            PLAYERS[i].free = true;
            break;
          }
    }

    #ifdef DEBUG
    LUAMOD_PRINT_DEBUG_PLAYER_DATA();
    #endif
}

void LUAMOD_PUSH_PLAYER_DATA_PUTONSRV(edict_t *pEntity)
{
    for(int i = 0; i < 32; i++)
    {
        if(PLAYERS[i].player_edict == pEntity)
          {
            PLAYERS[i].player_put_on_server = true;
            break;
          }
    }
#ifdef DEBUG
    LUAMOD_PRINT_DEBUG_PLAYER_DATA();
#endif
}
