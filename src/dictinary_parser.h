#include "luamod.h"
#include "parser.h"
#include "zone_luamod_mem.h"
#include <stdio.h>
#include <string.h>

#define DICT_BUFF_LEN 512

/*
[LANG]
KEY = "value"

[LANG2]
KEY = "value"
*/

struct key_value {
    char key[DICT_BUFF_LEN];
    char value[DICT_BUFF_LEN];
    struct key_value *next;
};

struct lang_list {
    char lang_code[2]; // for 2 lang code
    key_value *keyvalue;
    struct lang_list *next;
};

struct dictionary {
    lang_list *lang;
};

dictionary *dictionary_init(const char *filename);
const char *dictionary_find_value(dictionary *dict, const char *lang_code, const char *key);
