#include "lu_offset.h"



typedef struct
{
    char error_handle[32];
    size_t offset;

} luamod_pev_offset_t;

#define EDICT_OFFS(v,o) ((char *)v + o)

luamod_pev_offset_t offsets[] = {
    { "pev_classname", offsetof(entvars_t, classname) },
    { "pev_globalname", offsetof(entvars_t, globalname) },
    { "pev_origin", offsetof(entvars_t, origin) },
    { "pev_oldorigin", offsetof(entvars_t, oldorigin) },
    { "pev_velocity", offsetof(entvars_t, velocity) },
    { "pev_basevelocity", offsetof(entvars_t, basevelocity) },
    { "pev_movedir", offsetof(entvars_t, movedir) },
    { "pev_angles", offsetof(entvars_t, angles) },
    { "pev_avelocity", offsetof(entvars_t, avelocity) },
    { "pev_punchangle", offsetof(entvars_t, punchangle) },
    { "pev_v_angle", offsetof(entvars_t, v_angle) },
    { "pev_endpos", offsetof(entvars_t, endpos) },
    { "pev_startpos", offsetof(entvars_t, startpos) },
    { "pev_impacttime", offsetof(entvars_t, impacttime) },
    { "pev_starttime", offsetof(entvars_t, starttime) },
    { "pev_fixangle", offsetof(entvars_t, fixangle) },
    { "pev_idealpitch", offsetof(entvars_t, idealpitch) },
    { "pev_pitch_speed", offsetof(entvars_t, pitch_speed) },
    { "pev_ideal_yaw", offsetof(entvars_t, ideal_yaw) },
    { "pev_yaw_speed", offsetof(entvars_t, yaw_speed) },
    { "pev_modelindex", offsetof(entvars_t, modelindex) },
    { "pev_model", offsetof(entvars_t, model) },
    { "pev_viewmodel", offsetof(entvars_t, viewmodel) },
    { "pev_weaponmodel", offsetof(entvars_t, weaponmodel) },
    { "pev_absmin", offsetof(entvars_t, absmin) },
    { "pev_absmax", offsetof(entvars_t, absmax) },
    { "pev_size", offsetof(entvars_t, size) },
    { "pev_ltime", offsetof(entvars_t, ltime) },
    { "pev_nextthink", offsetof(entvars_t, nextthink) },
    { "pev_movetype", offsetof(entvars_t, movetype) },
    { "pev_solid", offsetof(entvars_t, solid) },
    { "pev_skin", offsetof(entvars_t, skin) },
    { "pev_body", offsetof(entvars_t, body) },
    { "pev_effects", offsetof(entvars_t, effects) },
    { "pev_gravity", offsetof(entvars_t, gravity) },
    { "pev_friction", offsetof(entvars_t, friction) },
    { "pev_light_level", offsetof(entvars_t, light_level) },
    { "pev_sequence", offsetof(entvars_t, sequence) },
    { "pev_gaitsequence", offsetof(entvars_t, gaitsequence) },
    { "pev_frame", offsetof(entvars_t, frame) },
    { "pev_animtime", offsetof(entvars_t, animtime) },
    { "pev_framerate", offsetof(entvars_t, framerate) },
    //{ "pev_controller", offsetof(entvars_t, controller) },
    //{ "pev_blending", offsetof(entvars_t, blending) },
    { "pev_scale", offsetof(entvars_t, scale) },
    { "pev_rendermode", offsetof(entvars_t, rendermode) },
    { "pev_renderamt", offsetof(entvars_t, renderamt) },
    { "pev_rendercolor", offsetof(entvars_t, rendercolor) },
    { "pev_renderfx", offsetof(entvars_t, renderfx) },
    //{ "pev_scalehealth", offsetof(entvars_t, scalehealth) }
    { "pev_frags", offsetof(entvars_t, frags) },
    { "pev_weapons", offsetof(entvars_t, weapons) },
    { "pev_takedamage", offsetof(entvars_t, takedamage) },
    { "pev_deadflag", offsetof(entvars_t, deadflag) },
    { "pev_view_ofs", offsetof(entvars_t, view_ofs) },
    { "pev_", offsetof(entvars_t, ) }
};



void lu_offset::init_api(lua_State *L)
{
    // Functions
    lua_register(L, "get_offset_data", lu_offset::l_get_offset_data);
    lua_register(L, "get_offset_char", lu_offset::l_get_offset_char);
    lua_register(L, "set_offset_char", lu_offset::l_set_offset_char);
    lua_register(L, "get_offset_float", lu_offset::l_get_offset_float);
    lua_register(L, "set_offset_float", lu_offset::l_set_offset_float);
    lua_register(L, "get_offset_int", lu_offset::l_get_offset_int);
    lua_register(L, "set_offset_int", lu_offset::l_set_offset_int);
    lua_register(L, "get_offset_qboolean", lu_offset::l_get_offset_qboolean);
    lua_register(L, "set_offset_qboolean", lu_offset::l_set_offset_qboolean);
}

int lu_offset::l_get_offset_data(lua_State *L)
{
    char *obj = (char *)lua_touserdata(L, 1);
    int offset = luaL_checkinteger(L, 2);
    lua_pushlightuserdata(L, obj + offset);
    return 1;
}

int lu_offset::l_get_offset_char(lua_State *L)
{
    char *obj = (char *)lua_touserdata(L, 1);
    int offset = luaL_checkinteger(L, 2);
    lua_pushstring(L, obj + offset);
    return 1;
}

int lu_offset::l_set_offset_char(lua_State *L)
{
    //   char* obj = (char*)lua_touserdata(L, 1);
    //   int offset = luaL_checkinteger(L, 2);
    //   const char* value = luaL_checkstring(L, 3);
    //   (char*)(obj + offset) = luaL_checkstring(L, 3);
    return 0;
}

int lu_offset::l_get_offset_float(lua_State *L)
{
    char *obj = (char *)lua_touserdata(L, 1);
    int offset = luaL_checkinteger(L, 2);
    lua_pushnumber(L, *(float *)(obj + offset));
    return 1;
}

int lu_offset::l_set_offset_float(lua_State *L)
{
    char *obj = (char *)lua_touserdata(L, 1);
    int offset = luaL_checkinteger(L, 2);
    float value = luaL_checknumber(L, 3);
    *(float *)(obj + offset) = value;
    return 0;
}

int lu_offset::l_get_offset_int(lua_State *L)
{
    char *obj = (char *)lua_touserdata(L, 1);
    int offset = luaL_checkinteger(L, 2);
    lua_pushnumber(L, *(int *)(obj + offset));
    return 1;
}

int lu_offset::l_set_offset_int(lua_State *L)
{
    char *obj = (char *)lua_touserdata(L, 1);
    int offset = luaL_checkinteger(L, 2);
    int value = luaL_checknumber(L, 3);
    *(int *)(obj + offset) = value;
    return 0;
}

int lu_offset::l_get_offset_qboolean(lua_State *L)
{
    char *obj = (char *)lua_touserdata(L, 1);
    int offset = luaL_checkinteger(L, 2);
    lua_pushnumber(L, *(qboolean *)(obj + offset));
    return 1;
}

int lu_offset::l_set_offset_qboolean(lua_State *L)
{
    char *obj = (char *)lua_touserdata(L, 1);
    int offset = luaL_checkinteger(L, 2);
    int value = luaL_checknumber(L, 3);
    *(qboolean *)(obj + offset) = value;
    return 0;
}
