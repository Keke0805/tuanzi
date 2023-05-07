/**
 * @file: sunxi_ctpdev.h
 * @autor: huangyixiu
 * @url: huangyixiu@allwinnertech.com
 */
#ifndef SUNXI_CTPDEV_H
#define SUNXI_CTPDEV_H

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

#ifdef __CTP_USE__

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

typedef void (*p_ctpdev_callback)(uint32_t key_type,uint32_t key_value, lv_indev_state_t state);
typedef void (*p_ctpdev_feedback)(uint8_t event_code);

void ctpdev_register_feedback(p_ctpdev_feedback func);
void ctpdev_register_hook(p_ctpdev_callback func);

/**
 * Initialize the ctpdev interface
 */
void ctpdev_init(void);

/**
 * unitialize the ctpdev interface
 */
void ctpdev_uninit(void);

/**
 * Get the current position and state of the evdev
 * @param data store the evdev data here
 * @return false: because the points are not buffered, so no more data to be read
 */
void ctpdev_read(lv_indev_drv_t * drv, lv_indev_data_t * data);

void ctpdev_feedback(lv_indev_drv_t * drv, uint8_t code);

#endif /* __CTP_USE__ */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SUNXI_CTPDEV_H */
