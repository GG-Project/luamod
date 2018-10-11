#include "utils.h"
#include "luamod.h"
#include <extdll.h>
#include <meta_api.h>

extern LUAMOD_PLAYER_DATA PLAYERS[32];
// static int players_count;
extern char MOD_PATH[32];

#ifdef DEBUG
void LUAMOD_PRINT_DEBUG_PLAYER_DATA()
{
    int i;
    for(i = 0; i < 32; i++)
    {
            //ALERT(at_console, "[LM] Name : %s Address : %s AuthID = %s PutInServer %d\n", PLAYERS[i].player_name, PLAYERS[i].player_address, PLAYERS[i].player_authid, PLAYERS[i].player_put_on_server);
            ALERT(at_console, "[LM] Name : %s AUTHID : %s Address : %s PutInServer %d\n", PLAYERS[i].player_name, GETPLAYERAUTHID(PLAYERS[i].player_edict), PLAYERS[i].player_address, PLAYERS[i].player_put_on_server);
    }
    //ALERT(at_console, "[LM] players on server : %d\n", players_count);
}
#endif

// REMOVE
const char *LUAMOD_GET_AUTHID_BY_EDICT(edict_t *pEntity)
{
    int i;
    for(i = 0; i < 32; i++)
    {
        if(PLAYERS[i].player_edict == pEntity)
        {
                //return PLAYERS[i].player_authid;
        }
    }
    return NULL;
}

void LUAMOD_PUSH_PLAYER_DATA(edict_t *player_entity, const char *pszName, const char *pszAddress)
{   
    /*
    int i;
    for(i = 0; i < 32; i++)
    {
        if(PLAYERS[i].free == true)
        {
            PLAYERS[i].player_edict = player_entity;
            PLAYERS[i].player_name = pszName;
            PLAYERS[i].player_address = pszAddress;
            PLAYERS[i].player_authid = GETPLAYERAUTHID(player_entity);
            PLAYERS[i].player_put_on_server = 0;
            PLAYERS[i].free = 0;
            break;
        }

        players_count++;

        LUAMOD_PRINT_DEBUG_PLAYER_DATA();
    }
*/
}

void LUAMOD_REMOVE_PLAYERDATA(edict_t *pEntity)
{
    int i;
    for(i = 0; i < 32; i++)
    {
        if(PLAYERS[i].player_edict == pEntity)
        {
            PLAYERS[i].player_edict = NULL;
            memset(PLAYERS[i].player_name, 0, sizeof(PLAYERS[i].player_name));
            memset(PLAYERS[i].player_address, 0, sizeof(PLAYERS[i].player_address));
            //memset(PLAYERS[i].player_authid, 0, sizeof(PLAYERS[i].player_authid));
            PLAYERS[i].player_put_on_server = false;
            PLAYERS[i].free = true;
            break;
        }
    }

    // players_count--;

    #ifdef DEBUG
    LUAMOD_PRINT_DEBUG_PLAYER_DATA();
    #endif
}

void LUAMOD_PUSH_PLAYER_DATA_PUTONSRV(edict_t *pEntity)
{
    int i;
    for(i = 0; i < 32; i++)
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

void PRINT_CONSOLE(const char *fmt, ...) {
	va_list ap;
	char buf[1024];
	unsigned int len;

	va_start(ap, fmt);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);
	len=strlen(buf);
	if(len < sizeof(buf)-2) {	// -1 null, -1 for newline
		buf[len+0] = '\n';
		buf[len+1] = 0;
	}
	else
		buf[len-1] = '\n';

	SERVER_PRINT(buf);
}
