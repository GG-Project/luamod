#include "lu_offset.h"

void lu_offset::init_api(lua_State *L) {
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

int lu_offset::l_get_offset_data(lua_State *L) {
    char* obj = (char*) lua_touserdata(L, 1);
    int offset = luaL_checkinteger(L, 2);
    lua_pushlightuserdata(L, obj + offset);
    return 1;
}

int lu_offset::l_get_offset_char(lua_State *L) {
    char* obj = (char*) lua_touserdata(L, 1);
    int offset = luaL_checkinteger(L, 2);
    lua_pushstring(L, obj + offset);
    return 1;
}

int lu_offset::l_set_offset_char(lua_State *L) {
    //   char* obj = (char*)lua_touserdata(L, 1);
    //   int offset = luaL_checkinteger(L, 2);
    //   const char* value = luaL_checkstring(L, 3);
    //   (const char*)(obj + offset) = luaL_checkstring(L, 3);
    return 0;
}

int lu_offset::l_get_offset_float(lua_State *L) {
    char* obj = (char*) lua_touserdata(L, 1);
    int offset = luaL_checkinteger(L, 2);
    ALERT(at_console, "l_get_offset_float : %d\n", obj + offset);
    lua_pushnumber(L, *(float*) obj + offset);
    return 1;
}

int lu_offset::l_set_offset_float(lua_State *L) {
    char* obj = (char*) lua_touserdata(L, 1);
    int offset = luaL_checkinteger(L, 2);
    float value = luaL_checknumber(L, 3);
    *(float*) (obj + offset) = value;
    return 0;
}

int lu_offset::l_get_offset_int(lua_State *L) {
    char* obj = (char*) lua_touserdata(L, 1);
    int offset = luaL_checkinteger(L, 2);
    //    lua_pushlightuserdata(L, obj + offset);
    lua_pushnumber(L, *(int*) obj + offset);
    return 1;
}

int lu_offset::l_set_offset_int(lua_State *L) {
    char* obj = (char*) lua_touserdata(L, 1);
    int offset = luaL_checkinteger(L, 2);
    int value = luaL_checknumber(L, 3);
    *(int*) (obj + offset) = value;
    return 0;
}

int lu_offset::l_get_offset_qboolean(lua_State *L) {
    char* obj = (char*) lua_touserdata(L, 1);
    int offset = luaL_checkinteger(L, 2);
    //    lua_pushlightuserdata(L, obj + offset);
    lua_pushnumber(L, *(qboolean*) obj + offset);
    return 1;
}

int lu_offset::l_set_offset_qboolean(lua_State *L) {
    char* obj = (char*) lua_touserdata(L, 1);
    int offset = luaL_checkinteger(L, 2);
    //	char value = luaL_checkstring(L, 3);
    int value = luaL_checknumber(L, 3);
    *(qboolean*) (obj + offset) = value;
    return 0;
}
