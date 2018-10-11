#pragma once

const char *LM_buildarch(void);
const char *LM_buildos(void);
const char *LM_buildhlsdk(void);
const char *LM_buildversion(void);

// пусть пока тут полежит
#if defined XASH3D
#else
#define GOLDSRC_PRIVATE
#endif