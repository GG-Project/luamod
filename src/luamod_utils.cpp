#include "luamod_utils.h"
#include <extdll.h>
#include <meta_api.h>

char mod_name_utils[32];

void SetModPath(char buff[32]) {
    strcpy(mod_name_utils, buff);
}

void GetModPath(char buff[32]) {
    strcpy(buff, mod_name_utils);
}

void PRINT_CONSOLE(const char *fmt, ...) {
	va_list ap;
	char buf[1024];
	unsigned int len;

	va_start(ap, fmt);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);
	len=strlen(buf);
	if(len < sizeof(buf)-2) {	// -1 null, -1 for newline
		buf[len+0] = '\n';
		buf[len+1] = 0;
	}
	else
		buf[len-1] = '\n';

	SERVER_PRINT(buf);
}