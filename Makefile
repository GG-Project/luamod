# LuaMod makefile based on hlsdk 2.3 makefile

HLSDK = include/hlsdk
METAMOD = include/metamod

DLLNAME=luamod_mm

ARCH=i386

CC?=gcc
CXX?=g++

LUAMOD_VERSION_GIT := $(firstword $(shell git rev-parse --short=6 HEAD) unknown)

ifeq ($(DEBUG),1)
BUILD_TYPE = Debug
LUAMOD_VERSION := 0.1-dev-$(LUAMOD_VERSION_GIT)
BASE_CFLAGS = -g -DDEBUG -Dlinux -D__linux__ -D__USE_GNU -std=gnu++11 -shared -DLUAMOD_VERSION=\"$(LUAMOD_VERSION)\"
else
BUILD_TYPE = Release
LUAMOD_VERSION := 0.1-release-$(LUAMOD_VERSION_GIT)
BASE_CFLAGS = -DNDEBUG -Dlinux -D__linux__ -D__USE_GNU -std=gnu++11 -shared -DLUAMOD_VERSION=\"$(LUAMOD_VERSION)\"
endif

DLL_SRCDIR=src

DLL_OBJDIR=$(BUILD_TYPE)/obj

OPT_CFLAGS = -O3 -msse3 -flto -funroll-loops -fomit-frame-pointer -fno-stack-protector -fPIC -m32

CFLAGS = $(BASE_CFLAGS) $(OPT_CFLAGS)

ifeq ($(REHLDS_SUPPORT),1)
CFLAGS += -DREHLDS_SUPPORT
endif

INCLUDE=-I. -I./src -I$(HLSDK)/common -I$(HLSDK)/dlls -I$(HLSDK)/engine \
		-I$(HLSDK)/game_shared -I$(HLSDK)/pm_shared -I$(HLSDK)/public -I$(METAMOD)

LDFLAGS=-L ./lua -llua

SHLIBEXT=so

#DO_CC=$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<
#DO_CXX=$(CXX) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(DLL_OBJDIR)/%.o: $(DLL_SRCDIR)/%.cpp
#	$(DO_CXX)
	$(CXX) $(CFLAGS) $(INCLUDE) -o $@ -c $<

OBJ = \
$(DLL_OBJDIR)/public.o \
$(DLL_OBJDIR)/callbacks.o \
$(DLL_OBJDIR)/dllapi.o \
$(DLL_OBJDIR)/engine_api.o \
$(DLL_OBJDIR)/ex_rehlds_api.o \
$(DLL_OBJDIR)/luamod_utils.o \
$(DLL_OBJDIR)/h_export.o \
$(DLL_OBJDIR)/lua_functions.o \
$(DLL_OBJDIR)/meta_api.o \
$(DLL_OBJDIR)/lua/CLuaWorker.o \
$(DLL_OBJDIR)/lua/commands.o \
$(DLL_OBJDIR)/lua/lu_output.o \
$(DLL_OBJDIR)/lua/lu_offset.o \
$(DLL_OBJDIR)/lua/lu_engfuncs.o \
$(DLL_OBJDIR)/lua/luaapi.o

$(DLLNAME)_$(ARCH).$(SHLIBEXT) : neat $(OBJ)
	$(CXX) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(BUILD_TYPE)/$@

neat:
	-mkdir -p $(BUILD_TYPE)
	-mkdir -p $(DLL_OBJDIR)
	-mkdir -p $(DLL_OBJDIR)/lua/

clean:
	-rm -f $(OBJ)
	-rm -f $(BUILD_TYPE)/$(DLLNAME)_$(ARCH).$(SHLIBEXT)

dirclean:
	-rm -r Debug Release
