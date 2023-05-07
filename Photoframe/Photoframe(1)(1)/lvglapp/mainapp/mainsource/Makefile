APPNAME ?= mainapp

APP_BUILD_DIR ?= ${shell pwd}
DEPEND_LIB_DIR ?= $(APP_BUILD_DIR)/../../lib-depend

SRCDIRS = $(shell find . -maxdepth 5 -type d)
		  
INCPATH ?= $(foreach dir,$(SRCDIRS),-I$(dir)) \
		   -I$(STAGING_DIR)/usr/include/allwinner/include \
		   -I$(STAGING_DIR)/usr/include/allwinner \
		   -I$(STAGING_DIR)/usr/include \
		   -I$(APP_BUILD_DIR)/../../lib-depend/lvgllib/include\
		   -I$(APP_BUILD_DIR)/../../lib-depend/lvgllib/include/lv_code\
		   -I$(APP_BUILD_DIR)/../../lib-depend/lvgllib/include/lv_cpp\
		   -I$(APP_BUILD_DIR)/../../lib-depend/lvgllib/include/lv_code/lvgl\
		   -I$(APP_BUILD_DIR)/../../lib-depend/lvgllib/include/lv_code/lvgl/src/core\
		   -I$(APP_BUILD_DIR)/../../lib-depend/lvgllib/include/lv_code/lvgl/src/custom\
		   -I$(APP_BUILD_DIR)/../../lib-depend/lvgllib/include/lv_code/lvgl/src/draw\
		   -I$(APP_BUILD_DIR)/../../lib-depend/lvgllib/include/lv_code/lvgl/src/extra\
		   -I$(APP_BUILD_DIR)/../../lib-depend/lvgllib/include/lv_code/lvgl/src/font\
		   -I$(APP_BUILD_DIR)/../../lib-depend/lvgllib/include/lv_code/lvgl/src/gpu\
		   -I$(APP_BUILD_DIR)/../../lib-depend/lvgllib/include/lv_code/lvgl/src/hal\
		   -I$(APP_BUILD_DIR)/../../lib-depend/lvgllib/include/lv_code/lvgl/src/misc\
		   -I$(APP_BUILD_DIR)/../../lib-depend/lvgllib/include/lv_code/lvgl/src/widgets\
		   -I$(APP_BUILD_DIR)/../../lib-depend/lvgllib/include/lv_code/lv_drivers\
		   -I$(APP_BUILD_DIR)/../../lib-depend/libhv/include\
		   -I$(APP_BUILD_DIR)/../../lib-depend/libhv/include/hv\
		   -I$(APP_BUILD_DIR)/../../lib-depend/freetype/include/freetype2\
		   -I$(APP_BUILD_DIR)/../../lib-depend/openssl/include\
		   -I$(APP_BUILD_DIR)/../../lib-depend/openssl/include/openssl\
		   -I$(APP_BUILD_DIR)/../../lib-depend/ffmpeg/include\
		   -I$(APP_BUILD_DIR)/../../lib-depend/azure-iot-sdk-c/include

LIBS += -L$(DEPEND_LIB_DIR)/lvgllib/lib/t113-tina -lLvGui \
	    -L$(DEPEND_LIB_DIR)/libhv/lib/t113-tina -lhv \
		-L$(DEPEND_LIB_DIR)/azure-iot-sdk-c/lib -liothub_client -liothub_client_http_transport \
		-L$(DEPEND_LIB_DIR)/azure-iot-sdk-c/lib -liothub_client_amqp_transport -liothub_client_amqp_ws_transport \
		-L$(DEPEND_LIB_DIR)/azure-iot-sdk-c/lib -liothub_client_mqtt_transport -liothub_client_mqtt_ws_transport \
		-L$(DEPEND_LIB_DIR)/azure-iot-sdk-c/lib -liothub_service_client  -luamqp -lumqtt -lserializer \
		-L$(DEPEND_LIB_DIR)/azure-iot-sdk-c/lib -lparson -luhttp -lumock_c -laziotsharedutil \
		-L$(DEPEND_LIB_DIR)/openssl/lib/t113-tina -lssl -lcrypto -luuid \
		-ltrecorder -lpthread -ldl \
		-ltplayer -lxplayer -lvdecoder -ladecoder -lsubdecoder -lcdc_base \
		-lVE -lMemAdapter -lvideoengine \
		-lcdx_parser  -lcdx_playback -lcdx_stream -lcdx_base \
		-luapi -lrt -lc  -lasound -lspeexdsp \
		-lawrecorder -lvencoder -laencoder -ljpeg -lpng \
		-lcdx_muxer -ljpegdecode  -ltmetadataretriever -lcdx_common \
		-lwifimg -lm -lfreetype -lcurl -lz \
		-Os
		
LOCAL_CFLAGS += -D_OS_UNIX -D_UCHIP_T113 -D__CTP_USE__ -DUSE_SUNXI_KEY -DUSE_SUNXI_ADC_KEY -DUSE_SUNXI_IR_KEY -DIMAGE_DECODE

FPIC_CFLAGS += -shared -fPIC 

LVGL_DIR ?= $(APP_BUILD_DIR)

#Collect the files to compile
VPATH = 
ASRCS = 
CSRCS += $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.c))
CSRCS += $(SRCPATH)
CPPSRCS += $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.cpp))
CPPSRCS += $(SRCPATH)

#MAINSRC = $(LVGL_DIR)/main.cpp


OBJEXT ?= .o

AOBJS = $(ASRCS:.S=$(OBJEXT))
COBJS = $(CSRCS:.c=$(OBJEXT))
CPPOBJS = $(CPPSRCS:.cpp=$(OBJEXT))
MAINOBJ = $(MAINSRC:.cpp=$(OBJEXT))

SRCS = $(ASRCS) $(CSRCS) $(CPPOBJS) $(MAINSRC)
OBJS = $(AOBJS) $(COBJS) $(CPPOBJS)


all: default

%.o: %.c
	@$(CC) $(CFLAGS) $(INCPATH) $(SDKPATH) $(LOCAL_CFLAGS) $(LOCAL_LDFLAGS) $(FPIC_CFLAGS) -c $< -o $@
	@echo "CC $<"

%.o: %.cpp
	@$(CXX) $(CPPFLAGS) $(INCPATH) $(SDKPATH) $(LOCAL_CFLAGS) $(LOCAL_LDFLAGS) $(FPIC_CFLAGS) -c $< -o $@
	@echo "CPP $<"

default: $(AOBJS) $(COBJS) $(CPPOBJS) $(MAINOBJ)
	$(CXX) -o $(INSTALL_BIN)$(APPNAME) $(MAINOBJ) $(AOBJS) $(COBJS) $(CPPOBJS) $(LDFLAGS) $(LOCAL_LDFLAGS) $(LIBS)
clean: 
	rm -f $(INSTALL_BIN)$(APPNAME) $(AOBJS) $(COBJS) $(MAINOBJ) $(CPPOBJS)

