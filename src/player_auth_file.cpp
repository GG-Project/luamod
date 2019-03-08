#include "luamod.h"
#include "parser.h"
#include "player.h"
#include "zone_luamod_mem.h"
#include <stdio.h>
#include <string.h>

#define LUAMOD_AMXMODX_AUTH_PASSWORD_FIELD "_pw"
#define LUAMOD_LUAMOD_AUTH_PASSWORD_FIELD "_lpw"
#define LUAMOD_AUTH_FILE "%s/addons/luamod/users.ini"

#define AUTH_MODULE_BUFFER_LEN 1024

/*
; Line starting with ; is a comment

; Access flags:
; a
; b
; c
; d
; e
; f
; g
; h
; i
; j
; k
; l

; m - custom level A
; n - custom level B
; o - custom level C
; p - custom level D
; q - custom level E
; r - custom level F
; s - custom level G
; t - custom level H

; z - user (no admin)

; Account flags:
; a - disconnect player on invalid password
; c - this is steamid/wonid
; d - this is ip
; e - password is not checked (only name/ip/steamid needed)
; k - name is case sensitive.  eg: if you set it so the name "Ham"
;     is protected and case sensitive (flags "k" only), then anybody
;     can use the names "haM", "HAM", "ham", etc, but not "Ham"

; Password:
; Add to your autoexec.cfg: setinfo _pw "<password>"
; Change _pw to the value of amx_password_field

; Format of admin account:
; <name|ip|steamid> <password> <access flags> <account flags>

; Examples of admin accounts:
; "STEAM_0:0:123456" "" "abcdefghijklmnopqrstu" "ce"
; "123.45.67.89" "" "abcdefghijklmnopqrstu" "de"
; "My Name" "my_password" "abcdefghijklmnopqrstu" "a"

"loopback" "" "abcdefghijklmnopqrstu" "de"
*/

/*
STEP 1 : create parser
STEP 2 : ?
STEP 3 : ???
PROFIT
*/

typedef struct player_auth_s {
    char *users_access_flags;
    char *user_account_flags;
    char *password;
} player_auth_t;

typedef struct key_value_value_value_s {
    char *key, *value1, *value2, *value3;
    key_value_value_value_s *next;

} key_value_value_value_t;

typedef key_value_value_value_t auth_file_t;

auth_file_t *file_list;

key_value_value_value_t *parse_key_3value(const char *src)
{
    key_value_value_value_t *result = (key_value_value_value_t *)Mem_Malloc(luamod_mem_pool, sizeof(key_value_value_value_t));

    char *buff_key = (char *)Mem_Malloc(luamod_mem_pool, AUTH_MODULE_BUFFER_LEN);
    char *buff_val1 = (char *)Mem_Malloc(luamod_mem_pool, AUTH_MODULE_BUFFER_LEN);
    char *buff_val2 = (char *)Mem_Malloc(luamod_mem_pool, AUTH_MODULE_BUFFER_LEN);
    char *buff_val3 = (char *)Mem_Malloc(luamod_mem_pool, AUTH_MODULE_BUFFER_LEN);

    // total rounds : 4

    /* "key" "val1" "val2" "val3" */
    const char *key_start = strchr(src, '"');
    // "key"
    // ^
    *key_start++;
    // "key"
    //  ^
    //"key"
    //    ^
    while (*key_start != NULL && *key_start != '"') {
        *buff_key++ = *key_start++;
    }
    // "key" "val1"
    //     ^
    *key_start++;
    const char *val1_start = strchr(key_start, '"');
    // "key" "val1"
    //       ^
    *val1_start++;
    // "val1"
    //  ^
    while (*val1_start != NULL && *val1_start != '"') {
        *buff_val1++ = *val1_start++;
    }
    *val1_start++;
    // "val1" "val2"
    //       ^
    const char *val2_start = strchr(val1_start, '"');
    // "val1" "val2"
    //        ^
    *val2_start++;
    // "val1" "val2"
    //         ^
    while (*val2_start != NULL && *val2_start != '"') {
        *buff_val2++ = *val2_start++;
    }
    *val2_start++;
    // "val1" "val2"
    //             ^
    const char *val3_start = strchr(val2_start, '"');
    // "val1" "val2" "val3"
    //               ^
    *val3_start++;
    // "val1" "val2" "val3"
    //                ^
    while (*val3_start != NULL && *val3_start != '"') {
        *buff_val3++ = *val3_start++;
    }
    *val3_start++;
    // "val1" "val2" "val3"
    //                    ^

    // PROFIT!!!11

    size_t key_len = strlen(buff_key);
    size_t val1_len = strlen(buff_val1);
    size_t val2_len = strlen(buff_val2);
    size_t val3_len = strlen(buff_val3);

    result->key = (char *)Mem_Malloc(luamod_mem_pool, key_len);
    result->value1 = (char *)Mem_Malloc(luamod_mem_pool, val1_len);
    result->value2 = (char *)Mem_Malloc(luamod_mem_pool, val2_len);
    result->value3 = (char *)Mem_Malloc(luamod_mem_pool, val3_len);

    strncpy(result->key, buff_key, key_len);
    strncpy(result->value1, buff_val1, val1_len);
    strncpy(result->value2, buff_val2, val2_len);
    strncpy(result->value3, buff_val3, val3_len);

    return result;
}

const char *strip_port(const char *src)
{
    char result[15]; // strlen(255.255.255.255) = 15
    while (*src && *src != ':')
        *result = *src++;

    return result;
}

#include <ctype.h>

void parse_file()
{

    FILE *file = fopen(va(LUAMOD_AUTH_FILE, MOD_PATH), "r");

    if (!file) {
        ALERT(at_console, "[LM] Error while reading %s\n", va(LUAMOD_AUTH_FILE, MOD_PATH));
        return;
    }

    char *buff = (char *)Mem_Malloc(luamod_mem_pool, AUTH_MODULE_BUFFER_LEN);

    auth_file_t *parse_result, *ptr_tmp, *ptr_tmp2;

    int i;

    while (fgets(buff, AUTH_MODULE_BUFFER_LEN, file) != NULL) {

        i = 0;
        while (buff[i] && isspace(buff[i]))
            i++;

        if (!buff[i])
            continue;

        if (buff[i] == ';' || !isalpha(buff[i]))
            continue;

        /*
      while (buff[i] && isspace(buff[i]))
        i++;

      if(!buff[i])
        continue;
      */

        parse_result = parse_key_3value(buff);

        if (parse_result == NULL)
            continue;

        ptr_tmp = file_list;

        parse_result->next = ptr_tmp;

        file_list = parse_result;

        ptr_tmp = NULL;
        parse_result = NULL;
    }

    Mem_Free(buff);
}

#include "utils.h"

inline qboolean have_flag(const char *src, int c)
{
    const char *flag = strchr(src, c);
    if (!flag || flag == NULL)
        return false;
    else
        return true;
}

void auth_player(edict_t *player)
{
    const char *key_authid = GETPLAYERAUTHID(player);
    const char *key_name = ENTITY_KEYVALUE(player, "name");
    const char *key_address = strip_port(ENTITY_KEYVALUE(player, "ip"));

    auth_file_t *ptr = file_list;

    while (ptr != NULL && (strcasecmp(ptr->key, key_authid) != 0 && strcasecmp(ptr->key, key_name) != 0 && strcasecmp(ptr->key, key_address) != 0))
        ptr = ptr->next;

    if (ptr == NULL)
        // player not auth

        if (!have_flag(ptr->value3, 'd') && !have_flag(ptr->value3, 'c'))

            //
            if (have_flag(ptr->value3, 'k')) {
            }
}

auth_file_t *get_auth_by(const char key) {}

qboolean have_access_flag() {}
