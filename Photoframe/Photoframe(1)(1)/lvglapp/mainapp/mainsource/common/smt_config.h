#ifndef  _SMT_CONFIG_H_
#define  _SMT_CONFIG_H_


/* include */
#include <stdio.h>
#include <stdlib.h>
#ifdef _UCHIP_T113
#include <sys/statfs.h>
#include <alsa/asoundlib.h>
#include <poll.h>
#include <linux/input.h>
#endif
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <assert.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
#include <stdbool.h>

#include "lvgl/lvgl.h"
#include "lv_drivers/indev/sunxi_key.h"
#include "lv_drivers/indev/sunxi_ctpdev.h"
#include "lv_drivers/display/fbdev.h"

#ifdef _UCHIP_T113
/* type */
typedef __s8  s8;
typedef __u8  u8;
typedef __s16 s16;
typedef __u16 u16;
typedef __s32 s32;
typedef __u32 u32;
#endif
/* photo res */
#define LV_IMAGE_PATH	"/usr/bin/resource/image/"
#define BYTE_PER_PIXEL	4
/* page */
typedef enum
{
    PAGE_NONE = 0,
    PAGE_HOME,
    PAGE_MUSIC,
    PAGE_MOVIE,
	PAGE_CALCULATOR,
    PAGE_CALENDAR,
    PAGE_EXPLORER,
	PAGE_CAMERA,
	PAGE_SOUND,
    PAGE_FOLDER,
	PAGE_PHOTO,
    PAGE_SETTING,
    PAGE_EXAMPLE,
    PAGE_WLAN_SET1,
    PAGE_WLAN_SET2,
    PAGE_SLIDE_HOME,
    PAGE_OTA,
    PAGE_MAX
} page_id_t;

/* debug */
#define COM_ERR
#define COM_WARN
#define COM_INFO
#ifdef _UCHIP_T113
#ifdef COM_ERR
#define com_err(fmt,...) printf("\033[31merr:<%s:%d>"fmt"\033[0m\n",__func__, __LINE__, ##__VA_ARGS__)
#else
#define com_err(fmt,...)
#endif

#ifdef COM_WARN
#define com_warn(fmt,...) printf("\033[33mwarn:<%s:%d>"fmt"\033[0m\n",__func__, __LINE__, ##__VA_ARGS__)
#else
#define com_warn(fmt,...)

#endif

#ifdef COM_INFO
#define com_info(fmt,...) printf("info:<%s:%d>"fmt"\n",__func__, __LINE__, ##__VA_ARGS__)
#else
#define com_info(fmt,...)
#endif

#endif //_UCHIP_T113
#endif
