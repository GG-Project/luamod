#pragma once
#include <extdll.h>
#include <meta_api.h>
#include <string.h>

void SetModPath(char buff[32]);
void GetModPath(char buff[32]);

#define UTIL_SET_MOD_PATH (*SetModPath)
#define UTIL_GET_MOD_PATH (*GetModPath)

void PRINT_CONSOLE(const char *fmt, ...);
