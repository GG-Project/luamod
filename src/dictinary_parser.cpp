#include "luamod.h"
#include "parser.h"
#include "zone_luamod_mem.h"
#include <stdio.h>
#include <string.h>

#include "dictinary_parser.h"

#define DICT_FILE_EXTENSION "txt"
#define DICT_PATH "%s/addons/luamod/data/lang/%s.%s"

inline int is_string(const char *src)
{
    if (!src || !*src)
        return 0;
    return 1;
}

inline void strncpy0(char *dest, const char *src, size_t n)
{
    strncpy(dest, src, n);
    dest[n] = '\0';
}

void read_from_to_symbol(char *dest, const char *src, int smb_start, int smb_end, size_t n)
{
    size_t i = 0;
    const char *ptr = strchr(src, smb_start);
    ptr++;

    while ((*ptr != NULL && *ptr != '\0' && *ptr != smb_end && *ptr != '\n') && i < n) {
        i++;
        *dest++ = *ptr++;
    }

    dest[i] = '\0';
    dest[i + 1] = '\0';
}

void read_to_symbol(char *dest, const char *src, int smb, size_t n)
{
    size_t i;

    for (i = 0; i <= n && src[i] != '\0' && src[i] != smb; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

int count_symbols_in_string(const char *src, int smb)
{
    int result = 0;

    if (!is_string(src))
        return result;

    for (int i = 0; src[i] != '\0'; i++) {
        if (src[i] == smb)
            result++;
    }

    return result;
}

int string_is_key_value(const char *src)
{
    if (!is_string(src))
        return 0;

    if ((count_symbols_in_string(src, '=') >= 1) && (count_symbols_in_string(src, ' ') >= 2) && (count_symbols_in_string(src, '"') >= 2))
        return 1;

    return 0;
}

int string_is_lang_comment(const char *src)
{
    if (!is_string(src))
        return 0;

    if ((src[0] != '[' && src[strlen(src)] != ']') && (count_symbols_in_string(src, ' ') == 0)) // no spaces okay ?
        return 0;
    else
        return 1;
}

// HACK HACK
// TODO: fix
// я хз но откуда то появляется 0xdf в конце
// это нужно исправить а пока будет хак strncpy0 в котором последний символ ставится в 0
key_value *parse_keyvalue(const char *src)
{
    key_value *ptr = (key_value *)Mem_Malloc(luamod_mem_pool, sizeof(key_value));

    read_to_symbol(ptr->key, src, ' ', DICT_BUFF_LEN);
    read_from_to_symbol(ptr->value, src, '"', '"', DICT_BUFF_LEN);

    ptr->next = NULL;
    
    ALERT(at_console, "KEY : %s VALUE : %s\n", ptr->key, ptr->value);

    return ptr;
}

lang_list *parse_lang_list(const char *src)
{
    lang_list *tmp;

    tmp = (lang_list *)Mem_Malloc(luamod_mem_pool, sizeof(lang_list));
    tmp->next = NULL;

    read_from_to_symbol(tmp->lang_code, src, '[', ']', 2);

    return tmp;
}

dictionary *dictionary_init(const char *filename)
{

    FILE *file = fopen(va(DICT_PATH, MOD_PATH, filename, DICT_FILE_EXTENSION), "r");

    if (!file) {
        ALERT(at_console, "[LM] Cannot open dictionary %s \n", va(DICT_PATH, MOD_PATH, "lang", DICT_FILE_EXTENSION));
        return NULL;
    }

    int lines_parsed = 0;

    dictionary *dict = (dictionary *)Mem_Malloc(luamod_mem_pool, sizeof(dictionary));

    char *buff = (char *)Mem_Malloc(luamod_mem_pool, DICT_BUFF_LEN);

    while (!ferror(file) && fgets(buff, DICT_BUFF_LEN, file) != NULL) {

        lines_parsed++;

        if (string_is_lang_comment(buff)) {

            // need here to parse lang ([LANG])

            struct lang_list *ptr, *ptr_tmp;

            ptr_tmp = dict->lang;
            ptr = parse_lang_list(buff);
            ptr->next = ptr_tmp;
            dict->lang = ptr;
            ptr_tmp = NULL;

            // in next while need parse key value (KEY = "VALUE")

            while (!ferror(file)) {

                char *buff2 = (char *)Mem_Malloc(luamod_mem_pool, DICT_BUFF_LEN);

                if (fgets(buff2, DICT_BUFF_LEN, file) == NULL)
                    break;
                else
                    lines_parsed++;

                if (string_is_key_value(buff2)) {
                    // PARSE KEY VALUE HERE!!!
                    struct key_value *ptr2, *ptr2_tmp;

                    ptr2_tmp = ptr->keyvalue;
                    ptr2 = parse_keyvalue(buff2);

                    if (ptr2 == NULL) {
                        ALERT(at_console, "[LM] dictionary PARSE ERROR!!!\nLine : %d\n%s\n", lines_parsed, buff2);
                        Mem_Free(buff2);
                        break;
                    }

                    ptr2->next = ptr2_tmp;
                    ptr->keyvalue = ptr2;
                    ptr2 = NULL;
                    ptr2_tmp = NULL;

                    Mem_Free(buff2);

                } else if (buff2[0] == '\n') {
                    Mem_Free(buff2);
                    break;
                } else if (buff2[0] != '\0') {
                    ALERT(at_console, "[LM] dictionary PARSE ERROR!!!\nLine : %d\n%s\n", lines_parsed, buff2);
                    Mem_Free(buff2);
                    break;
                } else {
                    Mem_Free(buff2);
                    break;
                }
            }
        } else if (string_is_key_value(buff)) {
            ALERT(at_console, "[LM] dictionary PARSE ERROR!!!\nLine : %d\n%s\n", lines_parsed, buff);
            break;
        } else {
            // ERROR HERE ?
            break;
        }
    }

    Mem_Free(buff);

    ALERT(at_console, "TOTAL PARSED LINES: %i\n", lines_parsed);

    struct lang_list *ptr3;
    struct key_value *ptr4;

    ptr3 = dict->lang;

    while (ptr3 != NULL) {
        ALERT(at_console, "LANG CODE %s\n", ptr3->lang_code);
        ptr4 = ptr3->keyvalue;
        while (ptr4 != NULL) {
            ALERT(at_console, "KEY : %s  VALUE : %s\n", ptr4->key, ptr4->value);
            ptr4 = ptr4->next;
        }
        ptr3 = ptr3->next;
    }

    fclose(file);
    return dict;
}

const char *dictionary_find_value(dictionary *dict, const char *lang_code, const char *key)
{
    const char *not_found = "VALUE_NOT_FOUND_OR_ERROR";

    if (!dict)
        return NULL;

    lang_list *ptr;
    key_value *ptr2;

    ptr = dict->lang;

    for (; ptr != NULL && strncasecmp(ptr->lang_code, lang_code, strlen(ptr->lang_code)) != 0;) {
        ptr = ptr->next;
    }

    if (ptr == NULL) {
        return not_found;
    }

    ptr2 = ptr->keyvalue;

    for (; ptr2 != NULL && strncasecmp(ptr2->key, key, strlen(ptr2->key)) != 0;) {
        ptr2 = ptr2->next;
    }

    if (ptr2 == NULL) {
        return not_found;
    } else {
        return ptr2->value;
    }
}

void dictionary_deinit( dictionary *dict )
{
    if( !dict )
        return;
    
    lang_list *lang_list_ptr = nullptr, *lang_list_ptr_tmp = nullptr;
    
    key_value *keyvalue_ptr = nullptr, *keyvalue_ptr_tmp = nullptr;

    lang_list_ptr = dict->lang;
    
    while( lang_list_ptr )
    {
        
        lang_list_ptr_tmp = lang_list_ptr;

        keyvalue_ptr = lang_list_ptr_tmp->keyvalue;

        while ( keyvalue_ptr )
        {
            keyvalue_ptr_tmp = keyvalue_ptr;
            keyvalue_ptr = keyvalue_ptr->next;
            Mem_Free( keyvalue_ptr_tmp );
        }

        lang_list_ptr = lang_list_ptr->next;
        Mem_Free( lang_list_ptr_tmp );
        
    }

    Mem_Free( dict );

    dict = nullptr;
}
