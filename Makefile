HLSDK = include/hlsdk
HLSDK_XASH3D = include/hlsdk-xash3d
METAMOD = include/metamod
LUAMOD_API = include/luamod
LUA = luajit/src

ifeq "$(TARGET)" "win32"
OS=windows
SHLIBEXT=dll
else
OS=linux
SHLIBEXT=so
endif

DLL_SRCDIR=src

DLLNAME=luamod_mm

LUAMOD_PATCH = dev

LUAMOD_VERMAIN = 0.3.1

CC?=gcc
CXX?=g++

ifeq ($(CLANG), 1)
CC=clang
CXX=clang++
endif

COMPILER_VER_CC = $(shell $(CC) -dumpversion)
COMPILER_VER_CXX = $(shell $(CC) -dumpversion)

OPT_CFLAGS = -O3 -flto -funroll-loops -fomit-frame-pointer -fno-stack-protector -fPIC -Wall

BASE_CFLAGS = -D__USE_GNU -std=gnu++11 -DLUAMOD_VERSION=\"$(LUAMOD_VERSION)\" -DLUAMOD_PATCH=\"$(LUAMOD_PATCH)\"

ARCH=$(shell uname -m)

LUAMOD_COMMIT := $(firstword $(shell git rev-parse --short=6 HEAD) unknown)
	
ifeq ($(ARCH), x86_64)
ARCH = i686
ARCH_CFLAGS +=-m32 -msse3 -march=i686 -mtune=generic
else ifeq ($(ARCH), aarch64)
ARCH_CFLAGS += -march=native
#ARCH = ARCH_UNAME
XASH3D = 1
else ifeq (, $(findstring arm,$(ARCH_UNAME)))
ARCH_CFLAGS +=
#ARCH = ARCH_UNAME
XASH3D = 1
endif

ifeq ($(DEBUG),1)
BUILD_TYPE = debug
BUILD_TYPE_CFLAGS = -g -DDEBUG
else
BUILD_TYPE = release
BUILD_TYPE_CFLAGS = -DNDEBUG
endif

LUAMOD_VERSION := $(LUAMOD_VERMAIN)-$(BUILD_TYPE)-$(LUAMOD_COMMIT)
DLL_OBJDIR=$(BUILD_TYPE).$(OS).$(ARCH)

ifeq ($(XASH3D), 1)
BUILD_TYPE_CFLAGS += -DXASH3D
HLSDK = $(HLSDK_XASH3D)
endif

ifeq ($(REHLDS_SUPPORT),1)
ifeq ($(XASH3D), 1)
$(error "REHLDS not work with XASH3D headers!!!!")
else
BUILD_TYPE_CFLAGS += -DREHLDS_SUPPORT
endif
endif

CFLAGS = $(BUILD_TYPE_CFLAGS) $(BASE_CFLAGS) $(OPT_CFLAGS) $(ARCH_CFLAGS)

INCLUDE=-I. -I$(DLL_SRCDIR) -I$(HLSDK)/common -I$(HLSDK)/dlls -I$(HLSDK)/engine \
                -I$(HLSDK)/game_shared -I$(HLSDK)/pm_shared -I$(HLSDK)/public -I$(METAMOD) -I$(LUAMOD_API) -I$(LUA)
	
LDFLAGS=-L $(LUA) -lluajit -shared -lsqlite3 -lpthread

#LDFLAGS = -L./ lua - llua - lpthread - shared

DO_CC=$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

DO_CXX=$(CXX) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(DLL_OBJDIR)/%.o: $(DLL_SRCDIR)/%.cpp
	$(DO_CXX)

SRC = $(wildcard src/*.cpp) $(wildcard src/lua/*.cpp)

OBJ := $(SRC:$(DLL_SRCDIR)/%.cpp=$(DLL_OBJDIR)/%.o)

$(DLLNAME)_$(ARCH).$(SHLIBEXT) : neat depend $(OBJ)	
	$(CXX) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(DLL_OBJDIR)/$@

neat:
	@mkdir -p $(DLL_OBJDIR)
	@mkdir -p $(DLL_OBJDIR)/lua/

$(DLL_OBJDIR): neat

clean: depend
	-rm -f $(OBJ)
	-rm -f $(DLL_OBJDIR)/$(DLLNAME)_$(ARCH).$(SHLIBEXT)
	-rm -f $(DLL_OBJDIR)/Rules.depend

depend: $(DLL_OBJDIR)/Rules.depend
	
$(DLL_OBJDIR)/Rules.depend: $(SRCFILES) $(DLL_OBJDIR)
	$(CXX) -MM $(INCLUDE) $(SRC) $(CFLAGS) | sed "s;\(^[^         ]*\):\(.*\);$(DLL_OBJDIR)/\1:\2;" > $@

include $(DLL_OBJDIR)/Rules.depend
