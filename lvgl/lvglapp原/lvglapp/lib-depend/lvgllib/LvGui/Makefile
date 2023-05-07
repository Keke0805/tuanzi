TARGET = LvGui

LIB_BUILD_DIR ?= ${shell pwd}

LVGLINSDIRS = $(shell find $(LIB_BUILD_DIR)/lv_code -maxdepth 5 -type d)

INCPATH ?= $(foreach dir,$(LVGLINSDIRS),-I$(dir)) \
		   -I$(STAGING_DIR)/usr/include/allwinner/include \
		   -I$(STAGING_DIR)/usr/include/allwinner \
		   -I$(STAGING_DIR)/usr/include\
		   -I./ -I$(LIB_BUILD_DIR)/lv_code \
		   -I$(LIB_BUILD_DIR)/lv_code/lvgl \
		   -I$(LIB_BUILD_DIR)/lv_code/lv_drivers \
		   -I$(LIB_BUILD_DIR)/lv_cpp

STATIC_ARFLAG ?= rcs
SHARED_ARFLAG ?= -shared -fPIC

LVGL_DIR ?= $(LIB_BUILD_DIR)

LVGL_DIR_NAME ?= lv_code/lvgl
LVGL_DRIVERS_NAME ?= lv_code/lv_drivers

LVGL_CPP_DIR_NAME ?= lv_cpp

LOCAL_CFLAGS += -D_OS_UNIX -D_UCHIP_T113 -D_MEM_SIZE_32M  -DUSE_SUNXI_KEY  -DUSE_SUNXI_ADC_KEY -DUSE_SUNXI_TP_KEY -fPIC 

STATICTARGET = lib$(TARGET).a
SHAREDTARGET = lib$(TARGET).so

OBJEXT ?= .o

AOBJS = $(ASRCS:.S=$(OBJEXT))
COBJS = $(CSRCS:.c=$(OBJEXT))
CPPOBJS = $(CPPSRCS:.cpp=$(OBJEXT))
MAINOBJ = $(MAINSRC:.cpp=$(OBJEXT))

SRCS = $(ASRCS) $(CSRCS) $(CPPOBJS) $(MAINSRC)
OBJS = $(AOBJS) $(COBJS) $(CPPOBJS)

include $(LVGL_DIR)/lv_cpp/lvgl_cpp.mk
include $(LVGL_DIR)/lv_code/lv_code.mk


all: $(STATICTARGET) $(SHAREDTARGET)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCPATH) $(LOCAL_CFLAGS) $(LOCAL_LDFLAGS) -c $< -o $@
	@echo "CC $<"

%.o: %.cpp
	@$(CXX) $(CPPFLAGS) $(INCPATH) $(LOCAL_CFLAGS) $(LOCAL_LDFLAGS) -c $< -o $@
	@echo "CPP $<"

$(STATICTARGET): $(AOBJS) $(COBJS) $(CPPOBJS) $(MAINOBJ)
	$(AR) $(STATIC_ARFLAG) $(PKG_BUILD_DIR)$(STATICTARGET) $(MAINOBJ) $(AOBJS) $(COBJS) $(CPPOBJS)
	
$(SHAREDTARGET): $(AOBJS) $(COBJS) $(CPPOBJS) $(MAINOBJ)
	$(CXX) -o $(PKG_BUILD_DIR)$(SHAREDTARGET) $(COBJS) $(CPPOBJS) $(SHARED_ARFLAG)
	
clean: 
	rm -f $(PKG_BUILD_DIR)$(TARGET) $(AOBJS) $(COBJS) $(MAINOBJ) $(CPPOBJS)
