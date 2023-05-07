/*******************************************************************************!
 * \file            appmsg.h
 * \brief           appmsg接口定义
 *
 * \description     
 *
 * \note            
 *
 * \author   CareyZeng
 * \version 1.0
 * \date  2022/07/15
 *******************************************************************************/

#ifndef JNI_APPLIB_H_
#define JNI_APPLIB_H_
#ifdef  __cplusplus
	extern "C"
	{
#endif

//app_name
#define APP_NAME_UI	        "UI"

#define MSG_CONTENT_ENTER	      "enter"
#define MSG_CONTENT_QUIT          "quit"

typedef enum{
    UI_MAINAPP=0,
    UI_PHOTOLIST,
    UI_PHOTOPLAY,
    UI_MUSIC,
    UI_VIDEOLIST,
    UI_VIDEOPLAY,
    UI_CALENDAR,
    UI_WEATHER,
    UI_ALARM,
    UI_CLOCK,
    UI_SETTING,
    UI_LAUNCHER,
    UI_DISK,
}msg_type_e;


typedef enum{
    MODE_HOME=0,
    MODE_RETURN,
    MODE_NEXTSCENE,
    MODE_COMEBACK,
    MODE_UPDATA,
    MODE_DEVCODE,
    MODE_DEVUSER,
    VPLAY_DEFAULAT_CMD,
    VPLAY_INIT_CMD,
    VPLAY_EXIT_CMD,
    VPLAY_PREPARE_CMD,
    VPLAY_PLAY_CMD,
    VPLAY_PAUSE_CMD,
    VPLAY_STOP_CMD,
    VPLAY_SEEK_TO,
    VPLAY_SETTING,
    DISK_ENTER,
    DISK_SD_ENTER,
    DISK_SD_OUT,
    DISK_U_ENTER,
    DISK_U_OUT,
}msg_mode_e;

typedef struct{
    msg_type_e type;
    msg_mode_e mode;
    int csize;
    char content[1024];
}msg_apps_t;

typedef void (*ApplibCallback)(msg_apps_t *msg);

//when app start transfer once
int SSTAR_Applib_Init();
//when app finish transfer once
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

#ifdef  __cplusplus
}
#endif

#endif /* JNI_APPLIB_H_ */
