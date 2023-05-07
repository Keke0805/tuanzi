PWD:=
ROOT:=
PWD=$(shell pwd)
ROOT=$(PWD)/../../../../../../..
include $(ROOT)/prepare.mk
include $(ROOT)/project/configs/current.configs

PKG_NAME := mainapp
LVGL_VERSION := 8.2.0
APP_BUILD_DIR := $(shell pwd)
PKG_BIN_DIR := $(APP_BUILD_DIR)/out
ROOTFS_DIR := $(PWD)/../../..
PKG_INSTALL_DIR:=$(PWD)/../../../bin
LIBS_INSTALL_DIR:=$(PWD)/../../../lib

BINDIR_TEST := $(shell if [ -d "$(PKG_BIN_DIR)" ]; then echo "exist"; else echo "noexist"; fi)
$(info $(BINDIR_TEST))

CC = $(TOOLCHAINDIR)/bin/$(CROSS_COMPILE)gcc
CXX = $(TOOLCHAINDIR)/bin/$(CROSS_COMPILE)g++
LINKER = $(TOOLCHAINDIR)/bin/$(CROSS_COMPILE)g++
SDK_INCS=$(PROJ_ROOT)/release/include
UAPI_INCS=$(PROJ_ROOT)/kbuild/4.9.84/i2m/include/uapi/mstar

SRCDIRS = $(shell find . -maxdepth 5 -type d)

DEFINES = -D_OS_UNIX -D_UCHIP_SSD202 -static -g
INCPATH = $(foreach dir,$(SRCDIRS),-I$(dir)) \
	  -I./ -I$(APP_BUILD_DIR)/../../lib-depend/lvgllib/include \
	  -I$(APP_BUILD_DIR)/../../lib-depend/lvgllib/include/lv_code \
	  -I$(APP_BUILD_DIR)/../../lib-depend/lvgllib/include/lv_cpp \
	  -I$(APP_BUILD_DIR)/../../lib-depend/freetype/include/freetype2 \
	  -I$(APP_BUILD_DIR)/../../lib-depend/libhv/include \
	  -I$(ROOTFS_DIR)/include \
	  -I$(ROOTFS_DIR)/include/platform
CFLAGS ?= -g0 -Wall  $(DEFINES)
CPPFLAGS ?= -g0 -std=c++11 -Wall  $(DEFINES)
LDLAGS = -lm


LIBS += -L$(APP_BUILD_DIR)/../../lib-depend/lvgllib/lib/ssd20x -lLvGui 
LIBS += -L$(APP_BUILD_DIR)/../../lib-depend/freetype/lib/ssd20x -lfreetype
LIBS += -L$(APP_BUILD_DIR)/../../lib-depend/libhv/lib/ssd20x -lhv

LIBS += -L$(ROOTFS_DIR)/lib -lmi_common -lmi_wlan -lmi_gfx -lmi_disp -lmi_panel -lmi_sys -ldl -lpthread \
							-lcjson -lapplib -lzhttp -ldl_service -lconfpart -lnetd -lcrypto -lcurl \

APPNAME = mainapp
LVGL_DIR ?= $(APP_BUILD_DIR)

#Collect the files to compile
VPATH = 
ASRCS =
CSRCS = 
CPPSRCS =
MAINSRC = $(LVGL_DIR)/main.cpp

include $(LVGL_DIR)/machine/machine.mk
include $(LVGL_DIR)/mainstart/mainstart.mk
include $(LVGL_DIR)/stbimage/stbimage.mk

OBJEXT ?= .o

AOBJS = $(ASRCS:.S=$(OBJEXT))
COBJS = $(CSRCS:.c=$(OBJEXT))
CPPOBJS = $(CPPSRCS:.cpp=$(OBJEXT))
MAINOBJ = $(MAINSRC:.cpp=$(OBJEXT))

SRCS = $(ASRCS) $(CSRCS) $(CPPOBJS) $(MAINSRC)
OBJS = $(AOBJS) $(COBJS) $(CPPOBJS)

## MAINOBJ -> OBJFILES

all: initdir default

%.o: %.c
	@$(CC) $(CFLAGS) $(INCPATH) -c $< -o $@
	@echo "CC $<"

%.o: %.cpp
	@$(CXX) $(CPPFLAGS) $(INCPATH) -c $< -o $@
	@echo "CPP $<"

initdir:
    ifeq ("$(BINDIR_TEST)", "noexist")
	   mkdir -p $(PKG_BIN_DIR)
    endif
        
default: $(AOBJS) $(COBJS) $(CPPOBJS) $(MAINOBJ)
	$(LINKER) $(MAINOBJ) $(AOBJS) $(COBJS) $(CPPOBJS) $(LDFLAGS) $(LIBS) -o $(APPNAME)
	cp -d -rf ./$(APPNAME) $(PKG_BIN_DIR)
	cp -d -rf $(APP_BUILD_DIR)/resource/* $(ROOTFS_DIR)/resource/
	cp -f ./$(APPNAME) $(PKG_INSTALL_DIR)
	cp -f $(APP_BUILD_DIR)/../../lib-depend/lvgllib/lib/ssd20x/libLvGui.so $(LIBS_INSTALL_DIR)
	cp -f $(APP_BUILD_DIR)/../../lib-depend/libhv/lib/ssd20x/libhv.so $(LIBS_INSTALL_DIR)
	rm $(AOBJS) $(COBJS) $(MAINOBJ) $(CPPOBJS)
	rm -rf $(APPNAME)
clean: 
	rm -f $(APPNAME) $(AOBJS) $(COBJS) $(MAINOBJ) $(CPPOBJS)

