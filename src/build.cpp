#include "build.h"
#include <lua.hpp>

const char *LM_buildarch(void)
{
    const char *arch;

#if defined(__x86_64__) || defined(_M_X64)
    arch = "amd64";
#elif defined(__i386__) || defined(_X86_) || defined(_M_IX86)
    arch = "i386";
#elif defined __aarch64__
    arch = "aarch64";
#elif defined __arm__ || defined _M_ARM
    arch = "arm";
#else
    arch = "unknown";
#endif

    return arch;
}

const char *LM_buildos(void)
{
    const char *os;

#if defined(_WIN32) && defined(_MSC_VER)
    os = "Win32";
#elif defined(_WIN32) && defined(__MINGW32__)
    os = "Win32-MinGW";
#elif defined(__ANDROID__)
    os = "Android";
#elif defined(__SAILFISH__)
    os = "SailfishOS";
#elif defined(__linux__)
    os = "Linux";
#else
    os = "unknown";
#endif
    return os;
}

const char *LM_buildhlsdk(void)
{
    const char *headers;

#if defined(XASH3D)
    headers = "hlsdk-xash3d";
#else
    headers = "hlsdk";
#endif
    return headers;
}

const char *LM_buildversion(void)
{
    const char *version = LUAMOD_VERSION;
    return version;
}

const char *LM_buildlua(void)
{

#if !defined(LUAJIT_VERSION)
    const char *version = LUA_VERSION;
#elif defined(LUAJIT_VERSION)
    const char *version = LUAJIT_VERSION " " LUA_VERSION;
#else
    const char *version = "unknown";
#endif
    return version;
}

#ifdef DEBUG
const char *LM_buildcompiler(void)
{
    const char *compiler;
#if defined(__GNUC__)
    compiler = "g++";
#elif defined(__clang__)
    compiler = "clang++";
#elif defined(_MSC_VER)
    compiler = "msvc";
#else
    compiler = "unknown";
#endif
    return compiler;
}

const char *LM_buildcompilerversion(void)
{
    const char *version;

#if defined(__GNUC__) || defined(__clang__)
    version = __VERSION__;
#else
    version = "unknown";
#endif
    return version;
}
#endif
