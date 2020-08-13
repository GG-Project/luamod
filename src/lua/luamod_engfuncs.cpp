#include "luamod_engfuncs.h"
#include <extdll.h>
#include <meta_api.h>
#include <utils.h>
#include <vector>

#include <luamod_types.h>
#include <cvar_manager.h>

#ifdef REHLDS_SUPPORT
#include "ex_rehlds_api.h"
#endif

/*
int		(*pfnPrecacheModel)                     (char* s);
int		(*pfnPrecacheSound)                     (char* s);
int		(*pfnPrecacheGeneric)                   (char* s);
*/

/*
void            (*pfnEmitSound)                         ( edict_t *entity, int channel, const char *sample, float volume, float attenuation, int fFlags, int pitch );
*/

/*
void		(*pfnServerCommand)			(const char* str);
void		(*pfnServerExecute)			(void);
void		(*pfnClientCommand)			(edict_t* pEdict, const char* szFmt, ...);
*/

/*
pfnSetClientKeyValue
*/

/*
void		(*pfnMessageBegin)			(int msg_dest, int msg_type, const float *pOrigin, edict_t *ed);
void		(*pfnMessageEnd)            (void);
void		(*pfnWriteByte)				(int iValue);
void		(*pfnWriteChar)				(int iValue);
void		(*pfnWriteShort)			(int iValue);
void		(*pfnWriteLong)				(int iValue);
void		(*pfnWriteAngle)			(float flValue);
void		(*pfnWriteCoord)			(float flValue);
void		(*pfnWriteString)			(const char *sz);
void		(*pfnWriteEntity)			(int iValue);
*/

/*
char*           (*pfnGetInfoKeyBuffer)                  ( edict_t *e );                   // passing in NULL gets the serverinfo
char*           (*pfnInfoKeyValue)                      ( char *infobuffer, const char *key );
void            (*pfnSetKeyValue)                       ( char *infobuffer, const char *key, const char *value );
void            (*pfnSetClientKeyValue)                 ( int clientIndex, char *infobuffer, const char *key, const char *value );
*/

/*
int             (*pfnGetPlayerUserId)                   ( edict_t *e );
unsigned int    (*pfnGetPlayerWONId)                    ( edict_t *e );
void            (*pfnGetPlayerStats)                    ( const edict_t *pClient, int *ping, int *packet_loss );
const char *    (*pfnGetPlayerAuthId)                   ( edict_t *e );
*/

/*
void		(*pfnCVarRegister)			(cvar_t *pCvar);
float		(*pfnCVarGetFloat)			(const char *szVarName);
const char*	(*pfnCVarGetString)			(const char *szVarName);
void		(*pfnCVarSetFloat)			(const char *szVarName, float flValue);
void		(*pfnCVarSetString)                     (const char *szVarName, const char *szValue);
cvar_t		(*pfnCVarGetPointer)                    (const char *szVarName);
*/

/*
int     	(*pfnRegUserMsg)                        ( const char *pszName, int iSize );
*/

/*
void		(*pfnClientPrintf)			( edict_t* pEdict, PRINT_TYPE ptype, const char *szMsg );
 */

/*
void            (*pfnQueryClientCvarValue2)             ( const edict_t *player, const char *cvarName, int requestID );
*/

static const luaL_Reg enginefuncs_lib[] =
{
        {"precache_model", lu_engfuncs::l_pfnPrecacheModel},
        {"precache_sound", lu_engfuncs::l_pfnPrecacheSound},

        {"server_command", lu_engfuncs::l_pfnServerCommand},
        {"server_execute", lu_engfuncs::l_pfnServerExecute},
        {"client_command", lu_engfuncs::l_pfnClientCommand},

        {"set_client_key_value", lu_engfuncs::l_pfnSetClientKeyValue},
        {"info_key_value", lu_engfuncs::l_pfnInfoKeyValue},
        {"get_info_key_buffer", lu_engfuncs::l_pfnGetInfoKeyBuffer},

        {"message_begin", lu_engfuncs::l_pfnMessageBegin},
        {"message_end", lu_engfuncs::l_pfnMessageEnd},
        {"write_byte", lu_engfuncs::l_pfnWriteByte},
        {"write_char", lu_engfuncs::l_pfnWriteChar},
        {"write_short", lu_engfuncs::l_pfnWriteShort},
        {"write_long", lu_engfuncs::l_pfnWriteLong},
        {"write_angle", lu_engfuncs::l_pfnWriteAngle},
        {"write_coord", lu_engfuncs::l_pfnWriteCoord},
        {"write_string", lu_engfuncs::l_pfnWriteString},
        {"write_entity", lu_engfuncs::l_pfnWriteEntity},

        {"get_player_userid", lu_engfuncs::l_pfnGetPlayerUserId},
        {"get_player_stats", lu_engfuncs::l_pfnGetPlayerStats},
        {"get_player_authid", lu_engfuncs::l_pfnGetPlayerAuthId},

        {"cvar_register", lu_engfuncs::l_pfnRegister_Cvar},
        {"cvar_get_float", lu_engfuncs::l_pfnCVarGetFloat},
        {"cvar_get_string", lu_engfuncs::l_pfnCVarGetString},
        {"cvar_set_float", lu_engfuncs::l_pfnCVarSetFloat},
        {"cvar_set_string", lu_engfuncs::l_pfnCVarSetString},

        {"index_of_edict", lu_engfuncs::l_pfnIndexOfEdict},

        {"reg_user_msg", lu_engfuncs::l_pfnRegUserMsg},

        {"client_printf", lu_engfuncs::l_pfnClientPrintf},

        {"query_client_cvar_value2", lu_engfuncs::l_pfnQueryClientCvarValue2},

        #ifdef REHLDS_SUPPORT
        // REHLDS
        #endif

        {NULL,NULL}
};

void lu_engfuncs::init_api(lua_State *L)
{
    luaL_register(L, "engine", enginefuncs_lib);
}

int lu_engfuncs::l_pfnPrecacheModel(lua_State *L)
{
    PRECACHE_MODEL(luaL_checkstring(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnPrecacheSound(lua_State *L)
{
    PRECACHE_SOUND(luaL_checkstring(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnServerCommand(lua_State *L)
{
    SERVER_COMMAND(va("%s\n", luaL_checkstring(L, 1)));
    return 0;
}

int lu_engfuncs::l_pfnServerExecute(lua_State *L)
{
    SERVER_EXECUTE();
    return 0;
}

int lu_engfuncs::l_pfnClientCommand(lua_State *L)
{
    CLIENT_COMMAND(luaL_checkedict(L, 1, 0), "%s\n", luaL_checkstring(L, 2));
    return 0;
}

int lu_engfuncs::l_pfnMessageBegin(lua_State *L)
{
    // luaL_checktable(L, 3); // Origin
    std::vector<float> origin;

    lua_pushnil(L);
    while (lua_next(L, 3)) {
        lua_pushvalue(L, -1);
        origin.push_back(luaL_checknumber(L, -1));
        lua_pop(L, 2);
    }

    MESSAGE_BEGIN(luaL_checkinteger(L, 1), // DEST
        luaL_checkinteger(L, 2), // TYPE
//      luaL_checkvec3_t(L, 3),
        origin.data(),
        luaL_checkedict(L, 4, 1) // PLAYER
    );

    return 0;
}

int lu_engfuncs::l_pfnMessageEnd(lua_State *L)
{
    MESSAGE_END();
    return 0;
}

int lu_engfuncs::l_pfnWriteByte(lua_State *L)
{
    WRITE_BYTE(luaL_checkinteger(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnWriteChar(lua_State *L)
{
    WRITE_CHAR(luaL_checkinteger(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnWriteShort(lua_State *L)
{
    WRITE_SHORT(luaL_checkinteger(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnWriteLong(lua_State *L)
{
    WRITE_LONG(luaL_checkinteger(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnWriteAngle(lua_State *L)
{
    WRITE_ANGLE(luaL_checknumber(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnWriteCoord(lua_State *L)
{
    WRITE_COORD(luaL_checknumber(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnWriteString(lua_State *L)
{
    WRITE_STRING(luaL_checkstring(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnWriteEntity(lua_State *L)
{
    WRITE_ENTITY(luaL_checkinteger(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnGetInfoKeyBuffer(lua_State *L)
{
    lua_pushlightuserdata(L, GET_INFOKEYBUFFER(luaL_checkedict(L, 1, 1)));
    return 1;
}

int lu_engfuncs::l_pfnInfoKeyValue(lua_State *L)
{
    lua_pushstring(L, INFOKEY_VALUE((char*)lua_touserdata(L, 1), luaL_checkstring(L, 2)));
    return 1;
}

int lu_engfuncs::l_pfnSetKeyValue(lua_State *L)
{
    g_engfuncs.pfnSetKeyValue((char*)lua_touserdata(L, 1), luaL_checkstring(L, 2), luaL_checkstring(L, 3));
    return 0;
}

int lu_engfuncs::l_pfnSetClientKeyValue(lua_State *L)
{
    g_engfuncs.pfnSetClientKeyValue(luaL_checkinteger(L, 1), (char*)lua_touserdata(L, 2), luaL_checkstring(L, 3), luaL_checkstring(L, 4));
    return 0;
}

int lu_engfuncs::l_pfnGetPlayerUserId(lua_State *L)
{
    lua_pushinteger(L, GETPLAYERUSERID(luaL_checkedict(L, 1, 0)));
    return 1;
}

/*
int lu_engfuncs::l_pfnGetPlayerWONId(lua_State *L)
{
    lua_pushinteger(L, g_engfuncs.pfnGetPlayerWONId())
}
*/

int lu_engfuncs::l_pfnGetPlayerStats(lua_State *L)
{
    int ping = 0;
    int packet_lost = 0;
    g_engfuncs.pfnGetPlayerStats(luaL_checkedict(L, 1, 0), &ping, &packet_lost);

    lua_newtable(L);
    lua_pushnumber(L, ping);
    lua_setfield(L, -2, "ping");
    lua_pushnumber(L, packet_lost);
    lua_setfield(L, -2, "packet_lost");
    return 1;
}

int lu_engfuncs::l_pfnGetPlayerAuthId(lua_State *L)
{
    lua_pushstring(L, GETPLAYERAUTHID(luaL_checkedict(L, 1, 0)));
    return 1;
}

int lu_engfuncs::l_pfnRegister_Cvar(lua_State *L)
{

    if(lua_isnumber(L, 2))
      {
          Cvar_Manager_Register(luaL_checkstring(L, 1), luaL_checknumber(L, 2), NULL);
      } else if(lua_isstring(L, 2))
      {
          Cvar_Manager_Register(luaL_checkstring(L, 1), 0, luaL_checkstring(L, 2));
      } else
      {
          luaL_argerror(L, 2, "Not a number or string");
      }

    return 0;
}

int lu_engfuncs::l_pfnCVarGetFloat(lua_State *L)
{
    lua_pushnumber(L, CVAR_GET_FLOAT(luaL_checkstring(L, 1)));
    return 1;
}

int lu_engfuncs::l_pfnCVarGetString(lua_State *L)
{
    lua_pushstring(L, CVAR_GET_STRING(luaL_checkstring(L, 1)));
    return 1;
}

int lu_engfuncs::l_pfnCVarSetFloat(lua_State *L)
{
    CVAR_SET_FLOAT(luaL_checkstring(L, 1), luaL_checknumber(L, 2));
    return 0;
}

int lu_engfuncs::l_pfnCVarSetString(lua_State *L)
{
    CVAR_SET_STRING(luaL_checkstring(L, 1), luaL_checkstring(L, 2));
    return 0;
}

int lu_engfuncs::l_pfnIndexOfEdict(lua_State *L)
{
    lua_pushinteger(L, g_engfuncs.pfnIndexOfEdict(luaL_checkedict(L, 1, 1)));
    return 1;
}

int lu_engfuncs::l_pfnRegUserMsg(lua_State *L)
{
    lua_pushinteger(L, REG_USER_MSG(luaL_checkstring(L, 1), luaL_checkinteger(L, 2)));
    return 1;
}

int lu_engfuncs::l_pfnClientPrintf(lua_State *L)
{
    int print_type = (int)luaL_checkinteger(L, 2);
    if (print_type < 0 || print_type > 3)
        luaL_argerror(L, 2, "unknown print type");
    CLIENT_PRINTF(luaL_checkedict(L, 1, 0), (PRINT_TYPE)print_type, luaL_checkstring(L, 3));
    return 0;
}

int lu_engfuncs::l_pfnQueryClientCvarValue2(lua_State *L)
{
    QUERY_CLIENT_CVAR_VALUE2(luaL_checkedict(L, 1, 0), luaL_checkstring(L, 2), (int)luaL_checkinteger(L, 3));
    return 0;
}
