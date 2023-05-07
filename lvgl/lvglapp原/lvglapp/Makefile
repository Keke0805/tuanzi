include $(TOPDIR)/rules.mk

PKG_NAME:=lvglapp
PKG_VERSION:=1.0
PKG_RELEASE:=1

PKG_BUILD_DIR := $(COMPILE_DIR)/$(PKG_NAME)
CONFIGURE_BIN := mainapp

include $(BUILD_DIR)/package.mk
include ../sunxifb.mk

PKG_BUILD_DEPENDS:=PACKAGE_tslib:tslib
define Package/$(PKG_NAME)
  SECTION:=gui
  SUBMENU:=Littlevgl
  CATEGORY:=Gui
  DEPENDS:=+lvgllib +LVGL8_USE_SUNXIFB_G2D:libuapi +LVGL8_USE_SUNXIFB_G2D:kmod-sunxi-g2d \
		   +libhv +libfreetype +libstdcpp +libopenssl +libcrypto +libuuid\
		   +libcedarx +alsa-utils +wifimanager \
		   +libspeexdsp +libjpeg +libpng +libcurl +libzlib +libiconv +fftw3
  TITLE:=lvglapp demo use lvgl-8.2.0
endef

PKG_CONFIG_DEPENDS := \
	CONFIG_LVGL8_USE_SUNXIFB_DOUBLE_BUFFER \
	CONFIG_LVGL8_USE_SUNXIFB_CACHE \
	CONFIG_LVGL8_USE_SUNXIFB_G2D \
	CONFIG_LVGL8_USE_SUNXIFB_G2D_ROTATE


define Package/$(PKG_NAME)/description
  lvglapp is a gui of based lvgl.
endef

ifeq ($(TARGET_PRODUCT), c200s_F1C200s)
LOCAL_LDFLAGS += -D__SUNXI_DISPLAY__
LOCAL_LDFLAGS += -DCONFIG_C200S
LOCAL_LDFLAGS += -I$(LINUX_DIR)/include/video
endif

ifeq ($(TARGET_PRODUCT), f133_evb1)
LOCAL_LDFLAGS += -D__SUNXI_DISPLAY2__
LOCAL_LDFLAGS += -DCONFIG_F133
LOCAL_LDFLAGS += -I$(LINUX_DIR)/include/video
endif

ifeq ($(TARGET_PRODUCT), t113_evb1)
LOCAL_LDFLAGS += -D__SUNXI_DISPLAY2__
LOCAL_LDFLAGS += -DCONFIG_T113
LOCAL_LDFLAGS += -I$(LINUX_DIR)/include/video
endif

ifeq ($(TARGET_PRODUCT), t113_player_21)
LOCAL_LDFLAGS += -D__SUNXI_DISPLAY2__
LOCAL_LDFLAGS += -DCONFIG_T113
LOCAL_LDFLAGS += -I$(LINUX_DIR)/include/video
endif

ifeq ($(CONFIG_LVGL8_USE_SUNXIFB_G2D),y)
TARGET_CFLAGS+=-DLV_USE_SUNXIFB_G2D_FILL \
				-DLV_USE_SUNXIFB_G2D_BLEND \
				-DLV_USE_SUNXIFB_G2D_BLIT \
				-DLV_USE_SUNXIFB_G2D_SCALE
endif

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	mkdir -p $(PKG_BUILD_DIR)/lib-depend
	mkdir -p $(PKG_BUILD_DIR)/mainapp
	$(CP) -rf ./lib-depend/* $(PKG_BUILD_DIR)/lib-depend
	$(CP) -rf ./mainapp/* $(PKG_BUILD_DIR)/mainapp
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR)/mainapp/mainsource \
		MAKE="$(MAKE)" \
		ARCH="$(TARGET_ARCH)" \
		AR="$(TARGET_AR)" \
		CC="$(TARGET_CC)" \
		CXX="$(TARGET_CXX)" \
		CFLAGS="$(TARGET_CFLAGS)"\
		CPPFLAGS="$(TARGET_CPPFLAGS)"\
		LDFLAGS="$(TARGET_LDFLAGS)" \
		LOCAL_LDFLAGS="$(LOCAL_LDFLAGS)" \
		CONFIG_PREFIX="$(PKG_INSTALL_DIR)" \
		all
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin/
	$(INSTALL_DIR) $(1)/usr/lib/
	$(INSTALL_DIR) $(1)/usr/bin/resource/
	$(INSTALL_DIR) $(1)/usr/bin/resource/font
	$(INSTALL_DIR) $(1)/usr/bin/resource/image/main_menu
	$(INSTALL_DIR) $(1)/usr/bin/resource/image/other
	$(INSTALL_DIR) $(1)/usr/bin/resource/image/setting
	$(INSTALL_DIR) $(1)/usr/bin/resource/image/sounds
	$(INSTALL_DIR) $(1)/usr/bin/resource/image/dynamic
	$(INSTALL_DIR) $(1)/usr/bin/resource/image/static
	$(INSTALL_DIR) $(1)/usr/bin/resource/image/light
	$(INSTALL_DIR) $(1)/usr/bin/resource/image/EQ
	$(INSTALL_DIR) $(1)/usr/bin/resource/image/brightness
	$(INSTALL_DIR) $(1)/usr/bin/resource/image/volume
	$(INSTALL_DIR) $(1)/usr/bin/resource/image/wifi
	$(INSTALL_DIR) $(1)/usr/bin/resource/lyrics

	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/$(CONFIGURE_BIN) $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/lib-depend/lvgllib/lib/t113-tina/*.so $(1)/usr/lib/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/lib-depend/libhv/lib/t113-tina/*.so $(1)/usr/lib/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/font/* $(1)/usr/bin/resource/font/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/main_menu/* $(1)/usr/bin/resource/image/main_menu/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/other/* $(1)/usr/bin/resource/image/other/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/setting/* $(1)/usr/bin/resource/image/setting/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/sounds/* $(1)/usr/bin/resource/image/sounds/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/static/* $(1)/usr/bin/resource/image/static/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/light/* $(1)/usr/bin/resource/image/light/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/EQ/* $(1)/usr/bin/resource/image/EQ/	
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/dynamic/* $(1)/usr/bin/resource/image/dynamic/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/brightness/* $(1)/usr/bin/resource/image/brightness/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/volume/* $(1)/usr/bin/resource/image/volume/	
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/wifi/* $(1)/usr/bin/resource/image/wifi/	

	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/lyrics/lyrics.txt $(1)/usr/bin/resource/lyrics/	
endef

$(eval $(call BuildPackage,$(PKG_NAME)))