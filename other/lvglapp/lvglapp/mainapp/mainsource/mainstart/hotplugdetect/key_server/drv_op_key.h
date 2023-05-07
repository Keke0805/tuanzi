/*
*******************************************************************************
* FileName: drv_op_key.h
* Description:
* History:
*       <author>    <time>          <version >      <desc>
*       CareyZeng    2021/08/24      1.0             ?????????
*******************************************************************************
*/

#ifndef __DRV_OP_KEY_H__
#define __DRV_OP_KEY_H__
#ifdef __cplusplus
extern "C"{
#endif

#include <stdbool.h>

#define KEY_INF(fmt, arg...) printf("[KEY-INF]%s-%d: " fmt "\n" ,__func__,__LINE__, ## arg)
#define KEY_ERR(fmt, arg...) printf("[KEY-ERROR]%s-%d: " fmt "\n" ,__func__,__LINE__, ## arg)

#define KEY_SUPPORT 1
#define GPIO_KEY_SUPPORT 1

#if (KEY_SUPPORT == 1)


typedef long long int64_t;

#define KEY_GPIO_NAME	"gpiokeys"

enum {
    KEY_GPIO,
};

extern bool s_shortcut_enable;
extern bool s_keymapping_enable;
extern bool s_key_server_enble;

/************************ extern function, ???????? ***************************/
int key_device_open(int type);
void key_device_close(int fd);
int key_device_get_msg(int fd);

#endif

#ifdef __cplusplus
}
#endif

#endif /* __DRV_OP_KEY_H__ */

