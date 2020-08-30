HLSDK = include/hlsdk
HLSDK_XASH3D = include/hlsdk-xash3d
METAMOD = include/metamod
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

LUAMOD_VERMAIN = 0.3.6
LUAMOD_BRANCH = dev
LUAMOD_GIT_COMMIT := $(firstword $(shell git rev-parse --short=6 HEAD) unknown)

CC?=cc
CXX?=c++
# Lto enbled by default for luamod dll and luajit
LTO?=1

ARCH=$(shell uname -m)
COMPILER_VER_CC = $(shell $(CC) -dumpversion)
COMPILER_VER_CXX = $(shell $(CXX) -dumpversion)

OPT_CFLAGS = -O2 -fno-stack-protector
BASE_CFLAGS = -D__USE_GNU -std=gnu++11 -DLUAMOD_VERSION=\"$(LUAMOD_VERSION)\" -DLUAMOD_BRANCH=\"$(LUAMOD_BRANCH)\" -fPIC -Wall

ifeq ($(LTO), 1)
CFLAGS += -flto
LUA_CFLAGS += -flto
LDFLAGS += -flto
LUA_LDFLAGS += -flto
endif

ifeq ($(ARCH), x86_64)
ARCH = i686
ARCH_CFLAGS += -m32 -march=i686 -mtune=generic -msse2
LUA_CFLAGS += -m32
LUA_LDFLAGS += -m32
else ifeq ($(ARCH), aarch64)
ARCH_CFLAGS += -march=native
XASH3D = 1
else ifeq (, $(findstring arm,$(ARCH_UNAME)))
ARCH_CFLAGS += -march=native
XASH3D = 1
endif

ifeq ($(DEBUG),1)
BUILD_TYPE = debug
BUILD_TYPE_CFLAGS = -g -DDEBUG
else
BUILD_TYPE = release
BUILD_TYPE_CFLAGS = -DNDEBUG
endif

ifeq ($(XASH3D), 1)
BUILD_TYPE_CFLAGS += -DXASH3D
HLSDK = $(HLSDK_XASH3D)
endif

ifeq ($(REHLDS_SUPPORT),1)
ifeq ($(XASH3D), 1)
$(error "XASH3D does support REHLDS api")
else
BUILD_TYPE_CFLAGS += -DREHLDS_SUPPORT
endif
endif

LUAMOD_VERSION := $(LUAMOD_VERMAIN)-$(BUILD_TYPE)-$(LUAMOD_GIT_COMMIT)
DLL_OBJDIR = $(BUILD_TYPE).$(OS).$(ARCH)

CFLAGS += $(BUILD_TYPE_CFLAGS) $(BASE_CFLAGS) $(OPT_CFLAGS) $(ARCH_CFLAGS)

INCLUDE=-I. -I$(DLL_SRCDIR) -I$(DLL_SRCDIR)/lua -I$(HLSDK)/common -I$(HLSDK)/dlls -I$(HLSDK)/engine \
                -I$(HLSDK)/game_shared -I$(HLSDK)/pm_shared -I$(HLSDK)/public -I$(METAMOD) -I$(LUA)

LDFLAGS += -L $(LUA) -lluajit -shared

DO_CC=$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<
DO_CXX=$(CXX) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(DLL_OBJDIR)/%.o: $(DLL_SRCDIR)/%.cpp
	$(DO_CXX)

SRC = $(wildcard src/*.cpp) $(wildcard src/lua/*.cpp)
OBJ := $(SRC:src/%.cpp=$(DLL_OBJDIR)/%.o)

$(DLLNAME)_$(ARCH).$(SHLIBEXT) : lua neat depend $(OBJ)
	$(CXX) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(DLL_OBJDIR)/$@

neat:
	@mkdir -p $(DLL_OBJDIR)
	@mkdir -p $(DLL_OBJDIR)/lua/

$(DLL_OBJDIR): neat

clean: depend
	-rm -f $(OBJ)
	-rm -f $(DLL_OBJDIR)/$(DLLNAME)_$(ARCH).$(SHLIBEXT)
	-rm -f $(DLL_OBJDIR)/Rules.depend

lua: $(LUA)/libluajit.a

$(LUA)/libluajit.a: $(LUA)/*.h
	cd $(LUA) && $(MAKE) BUILDMODE=static CFLAGS="$(LUA_CFLAGS)" LDFLAGS="$(LUA_LDFLAGS)"

depend: $(DLL_OBJDIR)/Rules.depend

$(DLL_OBJDIR)/Rules.depend: $(SRCFILES) $(DLL_OBJDIR)
	$(CXX) -MM $(INCLUDE) $(SRC) $(CFLAGS) | sed "s;\(^[^         ]*\):\(.*\);$(DLL_OBJDIR)/\1:\2;" > $@

include $(DLL_OBJDIR)/Rules.depend
