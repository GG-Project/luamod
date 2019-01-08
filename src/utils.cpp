#include "utils.h"
#include "luamod.h"
#include <extdll.h>
#include <meta_api.h>

#define MAGIC_NUMBER_FOR_BUFF 8192 //1kb ?

char* va(const char *fmt, ...)
{
  va_list ap;
  char* buf = (char*)malloc(MAGIC_NUMBER_FOR_BUFF);

  va_start(ap, fmt);
  vsnprintf(buf, MAGIC_NUMBER_FOR_BUFF, fmt, ap);
  va_end(ap);

  return buf;
}

void PRINT_CONSOLE(const char *fmt, ...) {
	va_list ap;
	char buf[1024];
	unsigned int len;

	va_start(ap, fmt);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	len = strlen(buf);

/*	if(buf[len] != '\n' || buf[len-1] != '\n')
	  {

	if(len < sizeof(buf)-2) {	// -1 null, -1 for newline
		buf[len+0] = '\n';
		buf[len+1] = 0;
	}
	else
	    buf[len-1] = '\n';

	  }
*/
	SERVER_PRINT(buf);
}
