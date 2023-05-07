/**
 * @file evdev.h
 *
 */

#ifndef EVDEV_H
#define EVDEV_H

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

#if USE_EVDEV || USE_BSD_EVDEV

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#if USE_MOUSE_DEV
extern const lv_img_dsc_t mouse;
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

//call back
typedef void (*p_evdev_callback)(uint32_t key_type,uint32_t key_value, lv_indev_state_t state);

typedef void (*p_evdev_feedback)(uint8_t event_code);

void evdev_register_hook(p_evdev_callback func);
void evdev_register_feedback(p_evdev_feedback func);

/**
 * Initialize the evdev
 */
void evdev_init(void);
/**
 * Deinitialize the evdev
 */
void evdev_deinit(void);
/**
 * reconfigure the device file for evdev
 * @param dev_name set the evdev device filename
 * @return true: the device file set complete
 *         false: the device file doesn't exist current system
 */
bool evdev_set_file(char* dev_name);
/**
 * Get the current position and state of the evdev
 * @param data store the evdev data here
 */
void evdev_read(lv_indev_drv_t * drv, lv_indev_data_t * data);

void evdev_feedback(lv_indev_drv_t * drv, uint8_t code);

#if(QTSIM_PLATFORM == 1)
void touch_write_data(int x, int y, int touch);
#endif

/**********************
 *      MACROS
 **********************/

#endif /* USE_EVDEV */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* EVDEV_H */
