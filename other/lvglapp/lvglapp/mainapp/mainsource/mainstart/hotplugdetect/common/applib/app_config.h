/*******************************************************************************!
 * \file            app_config.h
 * \brief           Ӧ�ö���
 *
 * \description     
 *
 * \note            
 *
 * \author   CareyZeng
 * \version 1.0
 * \date  2021/08/24
 *******************************************************************************/
#ifndef __APP_CONFIG_H__
#define __APP_CONFIG_H__

#ifdef __cplusplus
extern "C"{
#endif

#define UR_SEND_BMP_PATH		"./resource/image/idcard/idcard.bmp"

#define APP_NAME_BROADCAST	"broadcast"		//use for send broadcast msg
#define APP_NAME_DLSERVICE	"dlservice"		
#define APP_NAME_ZPCLIENT	"zpclient"
#define APP_NAME_NETD		"netd"
#define APP_NAME_URDEV		"urdev"
#define APP_NAME_SET		"set"
#define APP_NAME_IDCARD		"idcard"
#define APP_NAME_VOTE       "vote"

#define CFG_SOFTVER				"SOFTVER"
#define CFG_HWVER				"HWVER"
#define CFG_UIVER				"UIVER"
#define CFG_R2VER				"R2VER"
#define CFG_BACKLIGHT			"BACKLIGHT"
#define CFG_LANGUAGE            "LANGUAGE"
#define CFG_BGTOPIC             "BGTOPIC"
#define CFG_BACKLIGHTPRO		"BACKLIGHTPRO"

#ifdef __cplusplus
}
#endif

#endif//__APP_CONFIG_H__
