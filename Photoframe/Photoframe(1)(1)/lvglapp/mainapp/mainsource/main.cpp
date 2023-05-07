/**
 * @file main app
 *
 */
#include  "stdio.h"
#include  "lv_drivers/lv_drv_conf.h"

#if QTSIM_PLATFORM
#include  <QApplication>
#include  "simulator/LvglSimulator.h"
#else
#include "machine/LvglMachine.h"
#include "common/common.h"
#endif

#ifdef _UCHIP_T113
static hotplug_message_focus_win_t *RegisterInfo = NULL;
static void main_diskhotplugcallback(DiskInfo_t *DiskInfo) 
{ 
	msg_apps_t msg;
	msg_mode_e DiskMode =DISK_ENTER;
	bool sendType =false;
	printf("<*o*>MediaType:%d  operate:%d\n",DiskInfo->MediaType,DiskInfo->operate);
	if(DiskInfo->MediaType ==MEDIUM_SD_CARD)
	{
		if(DiskInfo->operate ==MEDIUM_PLUGIN)
		{
			DiskMode =DISK_SD_ENTER;
			sendType =true;
		}
		else if(DiskInfo->operate ==MEDIUM_PLUGOUT)
		{
			DiskMode =DISK_SD_OUT;
			sendType =true;
		}
	}
	else if(DiskInfo->MediaType ==MEDIUM_USB_MASSSTORAGE)
	{
		if(DiskInfo->operate ==MEDIUM_PLUGIN)
		{
			DiskMode =DISK_U_ENTER;
			sendType =true;
		}
		else if(DiskInfo->operate ==MEDIUM_PLUGOUT)
		{
			DiskMode =DISK_U_OUT;
			sendType =true;
		}
	}
	if(sendType)
	{
	    memset(&msg,0,sizeof(msg));
	    msg.type = UI_DISK;
	    msg.mode = DiskMode;
	    SSTAR_SendAsyncMsg(APP_NAME_UI,&msg);
	}
}
#endif

static void machine_driver_init(void)
{
#ifdef _UCHIP_SSD202
	
#endif
	
#ifdef _UCHIP_T113
	app_config_param_init(0);;
	rat_init();
	DiskManager_Init();
	va_audio_init();
	va_audio_play_init();
	message_sys_init();
	RegisterInfo = (hotplug_message_focus_win_t *)malloc(sizeof(hotplug_message_focus_win_t)); 
	if (RegisterInfo != NULL) 
	{
		memset(RegisterInfo, 0x00, sizeof(hotplug_message_focus_win_t));  
		strcpy(RegisterInfo->Cur_Win, "main");	
		RegisterInfo->CallBackFunction = main_diskhotplugcallback;	
		DiskManager_Register(RegisterInfo); 
	}
	media_init();
	wifi_data_init();
	DiskManager_detect();
#endif
}

int main(int argc, char *argv[])
{
    SSTAR_Applib_Init();
#if QTSIM_PLATFORM
    QApplication deskapp(argc, argv);
    printf("QT application start\n");

    LvglSimulator simulator;
    simulator.start_serialtool();
    simulator.show();

    return deskapp.exec();
#else
    printf("application start\n");
    lv_disp_rot_t rotated=LV_DISP_ROT_NONE;
    if(argc >= 2)
    {
        if(atoi(argv[1]) == 90){
            rotated = LV_DISP_ROT_90;
        }
        else if(atoi(argv[1]) == 180){
            rotated = LV_DISP_ROT_180;
        }
        else if(atoi(argv[1]) == 270){
            rotated = LV_DISP_ROT_270;
        }
        else{
            rotated = LV_DISP_ROT_NONE;
        }
    }
    else
    {
        rotated = LV_DISP_ROT_270;
    }

    LvglMachine machine;
    machine.sysInitial(rotated);
	machine_driver_init();
    machine.start_app();
    return 0;
#endif

}










