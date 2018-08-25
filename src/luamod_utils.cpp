#include "luamod_utils.hpp"
#include <extdll.h>
#include <meta_api.h>

char mod_name_utils[32];

void luamod_utils::SetModName(char buff[32]) {
    strncpy(mod_name_utils, buff, strlen(mod_name_utils));
}

void luamod_utils::GetModName(char buff[32]) {
    strncpy(buff, mod_name_utils, strlen(buff));
}
