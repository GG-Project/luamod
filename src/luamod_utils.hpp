#pragma once
#include <extdll.h>
#include <meta_api.h>
#include <string.h>

//#define LM_ALERT ,ALERT_TYPE alerttype ,const char *msg ALERT(alerttype,"[LM] %s", msg)
//#define LM_ALERT_CONSOLE (*g_engfuncs.pfnAlertMessage)(at_console);
//#define LM_ALERT_WARNING const char *msg ALERT(at_warning,"[LM] %s", msg)
//#define LM_ALERT_ERROR const char *msg ALERT(at_error,"[LM] %s", msg)
//#define LM_ALERT_LOGGED const char *msg ALERT(at_logged,"[LM] %s", msg)

namespace luamod_utils {
    void SetModName(char buff[32]);
    void GetModName(char buff[32]);
}

// void LM_ALERT(const char *msg);
