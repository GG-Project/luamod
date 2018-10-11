/* TODO: заставить работать
   Точнее просто перестроить :) */

#pragma once

#include <eiface.h>

// #include <exportdef.h>

#ifdef _WIN32
#define ARCH_SUFFIX
#define OS_LIB_EXT "dll"
#undef CreateDirectory
#define CreateDirectory(p, n) CreateDirectoryA(p, n)
#else
#ifdef __APPLE__
#define ARCH_SUFFIX
#define OS_LIB_EXT "dylib"
#else
	#if defined(__amd64__) || defined(_M_X64)
	#define ARCH_SUFFIX "_amd64"
	#elif defined(__i386__) || defined(_X86_) || defined(_M_IX86)
	#define ARCH_SUFFIX "_i386"
	#else
	#define ARCH_SUFFIX
	#endif
#define OS_LIB_EXT "so"
#endif
#include <dlfcn.h>
#include <unistd.h>
#include <sys/stat.h>
#define CreateDirectory(p, n) mkdir(p, 0777)
#define GetProcAddress dlsym
#define LoadLibrary(x) dlopen(x, RTLD_NOW)
#define Sleep(x) usleep(x * 1000)
//typedef void* HINSTANCE;
#define stricmp strcasecmp
#define _stricmp strcasecmp
#define strnicmp strncasecmp
#define _strnicmp strncasecmp
//#define FAR
//#define WINAPI
#endif

//typedef int (FAR *GETENTITYAPI)(DLL_FUNCTIONS *, int);
//typedef int (FAR *GETNEWDLLFUNCTIONS)(NEW_DLL_FUNCTIONS *, int *); 

//typedef void (*GIVEFNPTRSTODLL)(enginefuncs_t *, globalvars_t *);
//typedef void (FAR *LINK_ENTITY_FUNC)(entvars_t *);
