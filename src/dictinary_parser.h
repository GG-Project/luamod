#include "luamod.h"
#include "parser.h"
#include "zone_luamod_mem.h"
#include <stdio.h>
#include <string.h>

/*
[LANG]
KEY = "value"

[LANG2]
KEY = "value"
*/

struct key_value {
    char *key;
    char *value;
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
