/**
 * @file: sunxi_key.h
 * @autor: huangyixiu
 * @url: huangyixiu@allwinnertech.com
 */
#ifndef SUNXI_KEY_H
#define SUNXI_KEY_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef LV_DRV_NO_CONF
#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lv_drv_conf.h"
#else
#include "lv_drivers/lv_drv_conf.h"
#endif
#endif

#if USE_SUNXI_KEY

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

typedef void (*p_keydev_callback)(uint32_t key_type,uint32_t key_value, lv_indev_state_t state);
void keydev_init(void);
void keydev_uninit(void);
void keydev_read(lv_indev_drv_t * drv, lv_indev_data_t * data);
void keydev_register_hook(p_keydev_callback func);

lv_group_t* key_group_create(void);
lv_group_t* get_key_group(void);
void key_group_del(void);

#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
