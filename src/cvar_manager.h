#ifndef CVAR_MANAGER_H
#define CVAR_MANAGER_H

#include <extdll.h>

cvar_t *Cvar_Manager_Register(const char *cvar_name, float value, const char *string);

#endif // CVAR_MANAGER_H
