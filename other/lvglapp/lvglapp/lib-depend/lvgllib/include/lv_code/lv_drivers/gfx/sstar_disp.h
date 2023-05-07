/*
 * sstar_disp.h
 */

#ifndef _SSTAR_DISP_H_
#define _SSTAR_DISP_H_

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
#include "../lv_drv_conf.h"
#endif
#endif


#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

int sstar_disp_init(unsigned int dev, const char *interface, unsigned int width, unsigned int height);
void sstar_disp_deinit(unsigned int dev, const char *interface);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _SSTAR_DISP_H_ */
