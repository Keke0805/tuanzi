#pragma once

#include  "lvgl/lvgl.h"

#if(defined _UCHIP_SSD202)||(defined _UCHIP_T113)
#  define LVGL_DRIVER         1
#  define QTSIM_PLATFORM      0
#endif

#ifdef LVGL_DRIVER
    #include  "lv_drivers/lv_drv_conf.h"
#endif

#define   TRUE    1
#define   FALSE   0

#define  SIMULATOR_NONE_PLAT     0
#define  SIMULATOR_QTRUN_PLAT    1
#define  SIMULATOR_WIN32_PLAT    2

#ifdef QTSIM_PLATFORM
    #if QTSIM_PLATFORM
        #define  CURRENT_SIMOS SIMULATOR_QTRUN_PLAT
    #else
        #define  CURRENT_SIMOS SIMULATOR_NONE_PLAT
    #endif
#else
    #define  CURRENT_SIMOS SIMULATOR_WIN32_PLAT
#endif

// DEFAULT FONT CONFIG
#define   DEFAULT_FONT_COLOR  lv_color_black()
#if (QTSIM_PLATFORM==1)
#define   DEFAULT_FONT_NAME  "./resource/font/simhei.ttf"
#else
	#ifdef _UCHIP_T113
	#define   DEFAULT_FONT_NAME  "/usr/bin/resource/font/simhei.ttf"
	#else
	#define   DEFAULT_FONT_NAME  "/customer/resource/font/simhei.ttf"
	#endif
#endif
#define   DEFAULT_FONT_SIZE  24
#define   DEFAULT_FONT_TYPE  FT_FONT_STYLE_NORMAL
#define   DEFAULT_DOTFONT_SIZE  DOTARRAY_MONTSERRAT_24







