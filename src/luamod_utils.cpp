#include "luamod_utils.hpp"
#include <extdll.h>
#include <meta_api.h>

char mod_name_utils[32];

void luamod_utils::set_mod(char buff[32])
{
	strcpy(mod_name_utils, buff);
}

void luamod_utils::get_mod(char buff[32])
{
//	char kek;
//	strcpy(kek, mod_name_utils);
	strcpy(buff, mod_name_utils);
}
