/*******************************************************************************!
 * \file            applib.h
 * \brief           applib接口定义
 *
 * \description     
 *
 * \note            
 *
 * \author   CareyZeng
 * \version 1.0
 * \date  2021/08/24
 *******************************************************************************/


#ifndef JNI_APPLIB_H_
#define JNI_APPLIB_H_
#ifdef  __cplusplus
	extern "C"
	{
#endif

#include "app_msg.h"


typedef void (*ApplibCallback)(msg_apps_t *msg);

//path: full path of GlobalSetting.cfg
int SSTAR_Applib_Init(const char *path);

void SSTAR_Applib_Deinit();

/************************************************************
breif: app register to applib
param: 
	app_name: app name
	pfnCallback: system messages process function
return:
	0=success, -1=failed
*************************************************************/
int SSTAR_RegisterApplib(const char * app_name, ApplibCallback pfnCallback);

/************************************************************
breif: app unregister frome applib
param: 
	app_name: app name
	pfnCallback: system messages process function
return:
	0=success, -1=failed
*************************************************************/
void SSTAR_UnRegisterApplib(const char * app_name, ApplibCallback pfnCallback);

/************************************************************
breif: Send a async msg to "app_name"
param: 
	app_name: name of receiver 
	msg:
return:
	0=success, -1=failed
*************************************************************/
int SSTAR_SendAsyncMsg(const char * app_name, msg_apps_t *msg);

/************************************************************
breif: Get current system time stamp
param: null
return:
	time(ms)
*************************************************************/
int64_t get_tick_time_ms();
int64_t get_tick_time_us();

/************************************************************
breif: Modify a key&val item,if key not exsit will create it.
param:
	name: name
	buf: val
	type: 0=int, 1=string
return:
	0=success, -1=failed
*************************************************************/
int apl_set_config(const char *key, char *buf, int type);
int al_set_config(const char *key, char *buf, int type);

/************************************************************
breif: Get a key&val item
param:
	name: config name
	buf: buffer
	size: buffer size
return:
	0=success, -1=failed
*************************************************************/
int apl_get_config(const char *key, char *buf, int size);
int al_get_config(const char *key, char *buf, int size);

/************************************************************
breif: Sync configure to flash
return:
	0=success, -1=failed
*************************************************************/
int apl_sync_config();
int al_sync_config();

//0=success, -1=failed
int apl_burn_sn(char *udisk_path);



#ifdef  __cplusplus
}
#endif

#endif /* JNI_APPLIB_H_ */
