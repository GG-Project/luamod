#include "luamod_utils.hpp"
#include <extdll.h>
#include <meta_api.h>

char mod_name_utils[32];

void luamod_utils::SetModName(char buff[32]) {
    strncpy(mod_name_utils, buff, strlen(buff));
}

void luamod_utils::GetModName(char buff[32]) {
    strncpy(buff, mod_name_utils, strlen(mod_name_utils));
}

void UTIL_HUDMessage(const char* msg) {

#define MSG_BROADCAST   0
#define SVC_TEMPENTITY  23

MESSAGE_BEGIN(MSG_BROADCAST, SVC_TEMPENTITY);

        WRITE_BYTE(29);
        WRITE_BYTE(-1 & 0xFF);
        WRITE_SHORT(-1.0 * (1<<13) );
        WRITE_SHORT(0.20 * (1<<13) );
        WRITE_BYTE(0);
        WRITE_BYTE(200);
        WRITE_BYTE(100);
        WRITE_BYTE(0);
        WRITE_BYTE(0);
        WRITE_BYTE(255);
        WRITE_BYTE(255);
        WRITE_BYTE(250);
        WRITE_BYTE(0);
        WRITE_SHORT(2.0 * (1<<8) );
        WRITE_SHORT(2.0 * (1<<8) );
        WRITE_SHORT(12.0 * (1<<8) );

/*      if (textparms.effect == 2)
                WRITE_SHORT(FixedUnsigned16(textparms.fxTime, (1<<8)));
*/
        WRITE_STRING(msg);
        MESSAGE_END();
}