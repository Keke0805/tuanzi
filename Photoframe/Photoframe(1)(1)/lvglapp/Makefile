include $(TOPDIR)/rules.mk

PKG_NAME:=lvglapp
PKG_VERSION:=1.0
PKG_RELEASE:=1

PKG_BUILD_DIR := $(COMPILE_DIR)/$(PKG_NAME)

include $(BUILD_DIR)/package.mk
include ../sunxifb.mk

PKG_BUILD_DEPENDS:=PACKAGE_tslib:tslib
define Package/lvglapp
  SECTION:=gui
  SUBMENU:=Littlevgl
  CATEGORY:=Gui
  DEPENDS:=+lvgllib +LVGL8_USE_SUNXIFB_G2D:libuapi +LVGL8_USE_SUNXIFB_G2D:kmod-sunxi-g2d \
		   +libhv +libfreetype +libstdcpp +libopenssl +libcrypto +libuuid\
		   +libcedarx +alsa-utils +wifimanager \
		   +libspeexdsp +libjpeg +libpng +libcurl +libzlib
  TITLE:=lvglapp g2d demo use lvgl-8.2.0
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

ifeq ($(CONFIG_LVGL8_USE_SUNXIFB_G2D),y)
TARGET_CFLAGS+=-DLV_USE_SUNXIFB_G2D_FILL \
				-DLV_USE_SUNXIFB_G2D_BLEND \
				-DLV_USE_SUNXIFB_G2D_BLIT \
				-DLV_USE_SUNXIFB_G2D_SCALE
endif

CONFIGURE_BIN += mainapp

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
	$(INSTALL_DIR) $(1)/usr/bin/resource/image
	$(INSTALL_DIR) $(1)/usr/bin/resource/image/alarm
	$(INSTALL_DIR) $(1)/usr/bin/resource/image/calendar
	$(INSTALL_DIR) $(1)/usr/bin/resource/image/clock
	$(INSTALL_DIR) $(1)/usr/bin/resource/image/head
	$(INSTALL_DIR) $(1)/usr/bin/resource/image/launcher
	$(INSTALL_DIR) $(1)/usr/bin/resource/image/launcher/weather_big
	$(INSTALL_DIR) $(1)/usr/bin/resource/image/launcher/weather_small
	$(INSTALL_DIR) $(1)/usr/bin/resource/image/launcher/WIFI
	$(INSTALL_DIR) $(1)/usr/bin/resource/image/list
	$(INSTALL_DIR) $(1)/usr/bin/resource/image/music
	$(INSTALL_DIR) $(1)/usr/bin/resource/image/photo
	$(INSTALL_DIR) $(1)/usr/bin/resource/image/setting
	$(INSTALL_DIR) $(1)/usr/bin/resource/image/video
	$(INSTALL_DIR) $(1)/usr/bin/resource/image/vplayer
	$(INSTALL_DIR) $(1)/usr/bin/resource/image/weather
	$(INSTALL_DIR) $(1)/usr/bin/resource/image/weathericon

	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/$(CONFIGURE_BIN) $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/lib-depend/lvgllib/lib/t113-tina/*.so $(1)/usr/lib/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/lib-depend/libhv/lib/t113-tina/*.so $(1)/usr/lib/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/font/* $(1)/usr/bin/resource/font/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/*.png $(1)/usr/bin/resource/image/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/alarm/* $(1)/usr/bin/resource/image/alarm/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/calendar/* $(1)/usr/bin/resource/image/calendar/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/clock/* $(1)/usr/bin/resource/image/clock/	
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/head/* $(1)/usr/bin/resource/image/head/		
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/launcher/*.png $(1)/usr/bin/resource/image/launcher/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/launcher/*.jpg $(1)/usr/bin/resource/image/launcher/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/launcher/WIFI/* $(1)/usr/bin/resource/image/launcher/WIFI
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/launcher/weather_big/* $(1)/usr/bin/resource/image/launcher/weather_big/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/launcher/weather_small/* $(1)/usr/bin/resource/image/launcher/weather_small/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/list/* $(1)/usr/bin/resource/image/list/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/music/* $(1)/usr/bin/resource/image/music/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/photo/* $(1)/usr/bin/resource/image/photo/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/setting/* $(1)/usr/bin/resource/image/setting/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/video/* $(1)/usr/bin/resource/image/video/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/vplayer/* $(1)/usr/bin/resource/image/vplayer/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/weather/* $(1)/usr/bin/resource/image/weather/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mainapp/mainsource/resource/image/weathericon/* $(1)/usr/bin/resource/image/weathericon/	
endef

$(eval $(call BuildPackage,lvglapp))