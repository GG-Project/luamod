#include "luai.h"
#include <extdll.h>
#include <meta_api.h>

#include "lu_sqlite.h"

#include <luamod.h>
#include <sqlite3.h>
#include <strings.h>
#include <utils.h>

#define LUAMOD_SQLITE_DB_PATH "%s/addons/luamod/data/db/%s.sqlite3"

struct LUAMOD_SQLITE3_CALLBACK {
    lua_State *L;
    const char *callback_name;
};

void lu_sqlite::init_api(lua_State *L)
{
    lua_register(L, "sqlite_db_init", sqlite_init_db);
    lua_register(L, "sqlite_db_execute", sqlite_db_execute);
    lua_register(L, "sqlite_db_close", sqlite_db_close);
}

// init_sqlite3('filename')
// without .sqlite3

static int sqlite_callback(void *data, int argc, char **argv, char **colum_name)
{

    LUAMOD_SQLITE3_CALLBACK *callback = (LUAMOD_SQLITE3_CALLBACK *)data;

    for (int i = 0; i < argc; i++) {
        ALERT(at_console, "[LM SQLITE3 CALLBACK] %s = %s\n", colum_name[i], argv[i] ? argv[i] : "NULL");
    }

    lua_newtable(callback->L);

    // push rows count in table
    lua_pushstring(callback->L, "rows");
    lua_pushnumber(callback->L, argc);
    lua_settable(callback->L, -3);

    for (int k = 0; k < argc; k++) {
        if (!strcasecmp(colum_name[k], "id")) {
            lua_pushnumber(callback->L, atoi(argv[k]));

            lua_newtable(callback->L);

            for (; k < argc && (strcasecmp(colum_name[k + 1], "id") != 0); k++) {
                lua_pushstring(callback->L, argv[k]); // value
                lua_setfield(callback->L, -2, colum_name[k]); // key
            }
            lua_settable(callback->L, -3);
        }
    }

    return 0;
}

int lu_sqlite::sqlite_init_db(lua_State *L)
{
    sqlite3 *db;

    int error_code;

    const char *db_name = luaL_checkstring(L, 1);

    if (!strncasecmp("file::memory:", db_name, 14)) {
        error_code = sqlite3_open(db_name, &db);
        ALERT(at_console, "[LM] SQLITE TRY INIT DB IN MEMORY\n");
    } else {
        error_code = sqlite3_open(va(LUAMOD_SQLITE_DB_PATH, MOD_PATH, db_name), &db);
    }

    if (error_code) {
        luaL_error(L, "[LM] SQLITE INIT DB FAILED: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        ALERT(at_console, "[LM] SQLITE DB INIT OK!\n");
    }

    lua_pushlightuserdata(L, db);

    return 1;
}

int lu_sqlite::sqlite_db_execute(lua_State *L)
{
    int error_code;

    LUAMOD_SQLITE3_CALLBACK *lua_callback = (LUAMOD_SQLITE3_CALLBACK *)malloc(sizeof(LUAMOD_SQLITE3_CALLBACK));

    lua_callback->callback_name = luaL_checkstring(L, 3);

    lua_callback->L = NULL;

    lua_callback->L = L;

    char *sqlite_errmsg;

    error_code = sqlite3_exec((sqlite3 *)lua_touserdata(L, 1), luaL_checkstring(L, 2), sqlite_callback, lua_callback, &sqlite_errmsg);

    if (error_code != SQLITE_OK) {
        luaL_error(L, "[LM] SQLITE ERROR : %s\n", sqlite_errmsg);
        sqlite3_free(sqlite_errmsg);
        return 0;
    } else {
        ALERT(at_console, "[LM] SQLITE DONE SUCCESSFUL!\n");
    }

    // clean up
    free(lua_callback);

    return 1;
}

int lu_sqlite::sqlite_db_close(lua_State *L)
{
    int error_code;

    error_code = sqlite3_close((sqlite3 *)lua_touserdata(L, 1));

    if (error_code != SQLITE_OK) {
        luaL_error(L, "[LM] ERROR WHILE CLOSING DB!\n");
        return 0;
    } else {
        ALERT(at_console, "[LM] SQLITE CLOSE DB DONE!\n");
    }

    return 0;
}
