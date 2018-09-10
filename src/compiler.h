#pragma once

//Just to use to standart GOLDSRC Headers
#ifndef GOLDSRC_PRIVATE
#define GOLDSRC_PRIVATE
#endif

#ifdef XASH3D
#undef GOLDSRC_PRIVATE
#endif

//OS
#ifdef __ANDROID__
#error Android not supported!!!!
#endif

#ifdef __CYGWIN__
#error "Cygwin not supported!!!!"
#endif

//ARCH
#ifdef __arm__
#ifdef __ARM_ARCH_7__ || __ARM_ARCH_7A__ || __ARM_ARCH_7R__ || __ARM_ARCH_7M__ || __ARM_ARCH_7S__
#undef GOLDSRC
#define ARCH "armv7"
#else
#error "This arm architecture not supported!!!!"
#endif
#endif

#ifdef __aarch64__
#undef GOLDSRC
#endif

#ifdef __amd64__ || __amd64 || __x86_64__ || _WIN64
#error "Build for amd64 not supported!!!!"
#endif
