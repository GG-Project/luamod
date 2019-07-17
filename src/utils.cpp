#include "utils.h"
#include "luamod.h"
#include <extdll.h>
#include <meta_api.h>

#define MAGIC_NUMBER_FOR_BUFF 8192 // 1kb ?

char *va( const char *format, ... )
{
    va_list         argptr;
    static char     string[256][1024], *s;
    static int      stringindex = 0;

    s = string[stringindex];
    stringindex = (stringindex + 1) & 255;
    va_start( argptr, format );
    vsnprintf( s, sizeof( string[0] ), format, argptr );
    va_end( argptr );

    return s;
}

void PRINT_CONSOLE(const char *fmt, ...)
{
    va_list ap;
    char buf[1024];

    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

    SERVER_PRINT(buf);
}
