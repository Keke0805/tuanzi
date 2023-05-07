#include "mainappstart.h"
#include "mainstart/zpclient/zpclient.h"
#include "lv_drivers/indev/evdev.h"

using namespace LVGLOPTAPI;

#define CMD_BUF_LONG 		512
#define FILE_PATH_LONG 		1024
zpc_canvas_param_t g_CanvasInfo;
int update_flag=0;
int standy_flag=0;
int backlight_flag=0;
static int init_flag=0;
static int busy_flag=0;
static int send_flag=0;
static int usb_flag=0;
static int usb_action=0;
static int update_canvas=0;
static pthread_mutex_t updatelock;
static pthread_mutex_t sendlock;
static pthread_mutex_t copylock;

enum
{
    MOUSE_KEY_LEFT = 272,
    MOUSE_KEY_RIGHT = 273,
};


static void evdev_callback(uint32_t key_type,uint32_t key_value, lv_indev_state_t state)
{
    //LV_LOG_USER("evdev_callback:(%d, %d, %d)\n", key_type, key_value, (int)state);
    if(key_type == MOUSE_KEY_LEFT)
    {

    }
    else if(key_type == MOUSE_KEY_RIGHT)
    {

    }
}


MainAPPStart::MainAPPStart(LvcppMainScreen* parent)
{
    m_screen = parent;
    m_parent = m_screen->get_obj();
    m_screen->background_color(lv_color_white());

    //m_screen->showlogo(BG_PNG, SCREEN_HOR_SIZE, SCREEN_VER_SIZE,0);
    initial();
    #if (QTSIM_PLATFORM==0)
    SSTAR_RegisterApplib(APP_NAME_IDCARD, urdevhotplug_proc);
    SSTAR_RegisterUsbListener(usbhotplug_proc);
	NetPolicy_RegisterNetPolicyCB(networkpolicy_proc);
    #endif
    start_httpserver();
	maintimer = startTimer(50,this);
    //evdev_register_hook(evdev_callback);//register mouse callback
}

//tip:new() must to do delete
MainAPPStart::~MainAPPStart(void)
{
    deinitial();
}

void MainAPPStart::deinitial(void)
{
    #if (QTSIM_PLATFORM==0)
	NetPolicy_UnRegisterNetPolicyCB(networkpolicy_proc);
	SSTAR_UnRegisterUsbListener(usbhotplug_proc);
	SSTAR_UnRegisterApplib(APP_NAME_IDCARD, urdevhotplug_proc);
    #endif
}

//User starts here
void MainAPPStart::initial(void)
{
    zp_param_initial();
    /*
    if(tileview==nullptr)
    {
        tileview = new LvcppTileView(m_parent);
    }
    tileview->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    tileview->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    if(rename==nullptr)
    {
        rename = tileview->add_tile(0,0,LV_DIR_ALL);
        renamescreen = new RenameScreen(rename);
    }
    if(singlescreen==nullptr)
    {
        singlescreen = tileview->add_tile(1,0,LV_DIR_ALL);
        Single_screen = new single_screen(singlescreen);
    }

    if(setting==nullptr)
    {
        setting = tileview->add_tile(2,0,LV_DIR_ALL);
        settingscreen = new SettingScreen(setting);
    }
    tileview->set_tile_id(1, 0, LV_ANIM_OFF);*/


    if(singlescreen==nullptr)
    {
        Single_screen = new single_screen(singlescreen);
    }
}

void MainAPPStart::zp_param_initial(void)
{
    memset(&g_CanvasInfo,0,sizeof(zpc_canvas_param_t));
    g_CanvasInfo.clear_flag = 0;
    strcpy(g_CanvasInfo.username, "姓名");
    strcpy(g_CanvasInfo.company, "单位");
    strcpy(g_CanvasInfo.duty, "职务");
    strcpy(g_CanvasInfo.other, "");

    strcpy(g_CanvasInfo.layout.BgColor, "FF0000");
    strcpy(g_CanvasInfo.layout.BgImg, "");
    for(int i=0;i<MAX_DETAIL_NUM;i++)
    {
        if(i==0)
        {
            strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "username");
            g_CanvasInfo.layout.detail[i].ElePointX=0;
            g_CanvasInfo.layout.detail[i].ElePointY=200;
            g_CanvasInfo.layout.detail[i].EleWidth=1024;
            g_CanvasInfo.layout.detail[i].EleHeight=200;
            g_CanvasInfo.layout.detail[i].TextSize=200;
            strcpy(g_CanvasInfo.layout.detail[i].TextColor, "fac000");
            strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
            g_CanvasInfo.layout.detail[i].HorizontalAlign=2;
            g_CanvasInfo.layout.detail[i].TextLineSpace=0;
            g_CanvasInfo.layout.detail[i].TextLetterSpace=50;
            g_CanvasInfo.layout.detail[i].TextType=2;
        }
        else if(i==1)
        {
            strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "company");
            g_CanvasInfo.layout.detail[i].ElePointX=0;
            g_CanvasInfo.layout.detail[i].ElePointY=0;
            g_CanvasInfo.layout.detail[i].EleWidth=1024;
            g_CanvasInfo.layout.detail[i].EleHeight=80;
            g_CanvasInfo.layout.detail[i].TextSize=80;
            strcpy(g_CanvasInfo.layout.detail[i].TextColor, "000000");
            strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
            g_CanvasInfo.layout.detail[i].HorizontalAlign=1;
            g_CanvasInfo.layout.detail[i].TextLineSpace=0;
            g_CanvasInfo.layout.detail[i].TextLetterSpace=5;
            g_CanvasInfo.layout.detail[i].TextType=0;
        }
        else if(i==2)
        {
            strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "duty");
            g_CanvasInfo.layout.detail[i].ElePointX=0;
            g_CanvasInfo.layout.detail[i].ElePointY=500;
            g_CanvasInfo.layout.detail[i].EleWidth=1024;
            g_CanvasInfo.layout.detail[i].EleHeight=100;
            g_CanvasInfo.layout.detail[i].TextSize=80;
            strcpy(g_CanvasInfo.layout.detail[i].TextColor, "000000");
            strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
            g_CanvasInfo.layout.detail[i].HorizontalAlign=3;
            g_CanvasInfo.layout.detail[i].TextLineSpace=0;
            g_CanvasInfo.layout.detail[i].TextLetterSpace=5;
            g_CanvasInfo.layout.detail[i].TextType=0;
        }
        else if(i==3)
        {
            strcpy(g_CanvasInfo.layout.detail[i].ElementNo, "other");
            g_CanvasInfo.layout.detail[i].ElePointX=0;
            g_CanvasInfo.layout.detail[i].ElePointY=500;
            g_CanvasInfo.layout.detail[i].EleWidth=1024;
            g_CanvasInfo.layout.detail[i].EleHeight=100;
            g_CanvasInfo.layout.detail[i].TextSize=80;
            strcpy(g_CanvasInfo.layout.detail[i].TextColor, "000000");
            strcpy(g_CanvasInfo.layout.detail[i].TextFont, "楷体");
            g_CanvasInfo.layout.detail[i].HorizontalAlign=1;
            g_CanvasInfo.layout.detail[i].TextLineSpace=0;
            g_CanvasInfo.layout.detail[i].TextLetterSpace=5;
            g_CanvasInfo.layout.detail[i].TextType=0;
        }
    }

    memset(&g_RenameSaveInfo,0,sizeof(zpc_canvas_param_t));
    memcpy(&g_RenameSaveInfo,&g_CanvasInfo,sizeof(zpc_canvas_param_t));
}

void MainAPPStart::start_httpserver(void)
{
    if(m_pHttpServer==nullptr)
    {
        m_pHttpServer = new httpserver(SERVER_PORT);
    }
}

void MainAPPStart::stop_httpserver(void)
{
    if(m_pHttpServer!=nullptr)
    {
        delete m_pHttpServer;
        m_pHttpServer = nullptr;
    }
}

int MainAPPStart::read_battery_value()
{
	char value[4];
	int ret;
	
	FILE *fd = fopen(APP_BAT_CAPATITY_FILE,"r");
	if(fd == NULL)
	{
        LV_LOG_USER("read battery value error");
		fclose(fd);
		return -1;
	}
	memset(value,0,sizeof(value));
	ret = fread(value,1,sizeof(value),fd);
	if(ret<=0)
	{
        LV_LOG_USER("battery value is NULL");
		fclose(fd);
		return -1;
	}
	ret =atoi(value);
	fclose(fd);
	return ret;
}

int MainAPPStart::read_power_state()
{
	char value[4];
	int ret;
	
	FILE *fd = fopen(APP_POWER_STATE_FILE,"r");
	if(fd == NULL)
	{
        LV_LOG_USER("read charge state error");
		fclose(fd);
		return -1;
	}
	memset(value,0,sizeof(value));
	ret = fread(value,1,sizeof(value),fd);
	if(ret<=0)
	{
        LV_LOG_USER("charge state is NULL");
		fclose(fd);
		return -1;
	}
	ret =atoi(value);
	fclose(fd);
	return ret;
}


void MainAPPStart::screen_standby()
{
    #if (QTSIM_PLATFORM==0)
	msg_apps_t msg;
	memset(&msg,0,sizeof(msg_apps_t));
	msg.type = MSG_STANDBY;
	SSTAR_SendAsyncMsg(APP_NAME_BROADCAST, &msg);
    #endif
}

void MainAPPStart::screen_resume()
{
    #if (QTSIM_PLATFORM==0)
	msg_apps_t msg;
	memset(&msg,0,sizeof(msg_apps_t));
	msg.type = MSG_RESUME;
	SSTAR_SendAsyncMsg(APP_NAME_BROADCAST, &msg);
    #endif
}

void MainAPPStart::btn_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    MainAPPStart* opt = (MainAPPStart*)event->user_data;
	lv_obj_t* target = lv_event_get_target(event);
}


//loop run(must achieve)
void MainAPPStart::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    static int timecnt = 0;//static variable once assign
    if(update_canvas)
    {
        tileview->set_tile_id(1, 0, LV_ANIM_OFF);
        update_canvas = 0;
    }
    #if (QTSIM_PLATFORM==0)
    msg_apps_t msg;
	if(update_flag)
    {
    	pthread_mutex_lock(&updatelock);
        update_flag=0;
        pthread_mutex_unlock(&updatelock);
    }
	if(usb_flag)
	{
		pthread_mutex_lock(&copylock);
		usb_flag=0;
		if(usb_action)
		{
			memset(&msg,0,sizeof(msg_apps_t));
			msg.type = MSG_COPY_FILE_START;
			SSTAR_SendAsyncMsg(APP_NAME_IDCARD, &msg);
		}
		else
		{
			memset(&msg,0,sizeof(msg_apps_t));
			msg.type = MSG_COPY_FILE_FINISH;
			SSTAR_SendAsyncMsg(APP_NAME_IDCARD, &msg);
		}
		pthread_mutex_unlock(&copylock);
	}
    if(init_flag && !busy_flag)
	{
		if(send_flag)
		{
			if(access(UR_SEND_BMP_PATH,F_OK) == 0)
			{
				pthread_mutex_lock(&sendlock);
                send_flag=0;
                busy_flag=1;
                pthread_mutex_unlock(&sendlock);
				msg_apps_t msg;
				urdev_param_t urcmd;
				urcmd.cmd_or_file = 1;
				urcmd.cmd_index = 1;
				urcmd.cur_cmd = 1;
				memset(&msg, 0, sizeof(msg_apps_t));
				msg.type = MSG_SEND_ID_TO_FRONTLCD;
                memcpy(msg.content, &urcmd, sizeof(urdev_param_t));
				SSTAR_SendAsyncMsg(APP_NAME_URDEV, &msg);
			}
		}
		else
		{
			if(!standy_flag)
			{
				standy_flag = 1;
				if(read_power_state()==2)
				{
					memset(&msg,0,sizeof(msg_apps_t));
					msg.type = MSG_STANDBY;
					SSTAR_SendAsyncMsg(APP_NAME_BROADCAST, &msg);
                    backlight_enable(0);
                    g_zpcInfo.status =1;
				}
                else
                {
                    g_zpcInfo.status =2;
                }
			}
            if(standy_flag && !backlight_flag)
            {
                timecnt++;
                if(timecnt>20)
                {
                    timecnt = 0;
                    backlight_flag = 1;
                    memset(&msg,0,sizeof(msg_apps_t));
                    urdev_param_t urcmd;
                    urcmd.cmd_or_file = 2;
                    urcmd.cmd_index = 7;
                    urcmd.cur_cmd = 9;
                    memset(&msg, 0, sizeof(msg_apps_t));
                    msg.type = MSG_SEND_CMD_TO_R2;
                    memcpy(msg.content, &urcmd, sizeof(urdev_param_t));
                    SSTAR_SendAsyncMsg(APP_NAME_URDEV, &msg);
                }
            }
		}
	}
    #if 1
    else
    {
        if(!standy_flag)
        {
            standy_flag = 1;
            if(read_power_state()==2)
            {
                memset(&msg,0,sizeof(msg_apps_t));
                msg.type = MSG_STANDBY;
                SSTAR_SendAsyncMsg(APP_NAME_BROADCAST, &msg);
                backlight_enable(0);
                g_zpcInfo.status =1;
            }
            else
            {
                g_zpcInfo.status =2;
            }
        }
    }
    #endif
    #endif
}

#if (QTSIM_PLATFORM==0)
void MainAPPStart::urdevhotplug_proc(msg_apps_t *msg)
{
	char copyCmd[CMD_BUF_LONG] = {0};
	char SrcPath[FILE_PATH_LONG] = {0};
	char DstPath[FILE_PATH_LONG] = {0};
	switch(msg->type)
	{
		case MSG_R2_INIT_FINISH:
		{
			LV_LOG_USER("!!!! MSG_R2_INIT_FINISH !!!!\n");
			init_flag = 1;
            if(access(IDCARD_PATH,F_OK) == 0)
			{
				pthread_mutex_lock(&sendlock);
				send_flag=1;
				pthread_mutex_unlock(&sendlock);
			}
			else
			{
				pthread_mutex_lock(&sendlock);
				send_flag=0;
				pthread_mutex_unlock(&sendlock);
            }
			break;
		}
        case MSG_UPDATE_IDCARD:
        {
            LV_LOG_USER("MSG_UPDATE_IDCARD\n");
            update_canvas = 1;
            pthread_mutex_lock(&sendlock);
            send_flag=1;
            pthread_mutex_unlock(&sendlock);
            break;
        }
        case MSG_STANDBY:
        {
            LV_LOG_USER("MSG_STANDBY\n");
            backlight_enable(0);
            break;
        }
        case MSG_RESUME:
        {
            LV_LOG_USER("MSG_RESUME\n");
            backlight_enable(1);
            break;
        }
		case MSG_R2_SEND_FINISH:
		{
			LV_LOG_USER("!!!! MSG_R2_SEND_FINISH !!!!\n");
			pthread_mutex_lock(&sendlock);
			busy_flag = 0;
			pthread_mutex_unlock(&sendlock);
			break;
		}
		case MSG_COPY_FILE_START:
		{
			LV_LOG_USER("!!!! MSG_COPY_FILE_START !!!!\n");
			memset(SrcPath, 0, FILE_PATH_LONG);
			sprintf(SrcPath, "%s/font.zip",stUsbParam.udisk_path);
			if(access(SrcPath,F_OK) == 0)
			{
				memset(copyCmd, 0, CMD_BUF_LONG);
				sprintf(copyCmd, "unzip -o %s -d %s",SrcPath,USB_COPY_FONT_PATH);
				system(copyCmd);
				LV_LOG_USER("!!!! USB COPY FONT FINISH !!!!");
			}
			memset(SrcPath, 0, FILE_PATH_LONG);
			sprintf(SrcPath, "%s/bg.zip",stUsbParam.udisk_path);
			if(access(SrcPath,F_OK) == 0)
			{
				memset(copyCmd, 0, CMD_BUF_LONG);
				sprintf(copyCmd, "unzip -o %s -d %s",SrcPath,USB_COPY_IMAGE_PATH);
				system(copyCmd);
				LV_LOG_USER("!!!! USB COPY IMAGE FINISH !!!!");
			}
			break;
		}
		case MSG_COPY_FILE_FINISH:
		{
			LV_LOG_USER("!!!! MSG_COPY_FILE_FINISH !!!!\n");
			break;
		}
        case MSG_UPDATE_CANVAS:
        {
            LV_LOG_USER("!!!! MSG_UPDATE_CANVAS !!!!\n");
            update_canvas = 1;
            break;
        }
		default:
		{
			LV_LOG_USER("!!!! msg->type=%d !!!!\n",msg->type);	
			break;
		}
	}
}
void MainAPPStart::usbhotplug_proc(UsbParam_t *pUsbParam)
{
    //LV_LOG_USER("!!!! pUsbParam->action=%d !!!!\n",pUsbParam->action);
    //LV_LOG_USER("!!!! pUsbParam->udisk_path=%s !!!!\n",pUsbParam->udisk_path);
	if(pUsbParam->action)
	{
        LV_LOG_USER("!!!! USB INSERT!!!!");
		usb_action = 1;
	}
	else
	{
        LV_LOG_USER("!!!! USB OUTPLUG!!!!");
		usb_action = 0;
	}
	pthread_mutex_lock(&copylock);
	usb_flag = 1;
	pthread_mutex_unlock(&copylock);
}

void MainAPPStart::networkpolicy_proc(NetPolicy_cbmsg_t *msg)
{
	NetConfig_t *NetParam;
	LV_LOG_USER("<----!!!!!! msg->type=%d, msg->content=%s !!!!!!!---->",msg->type,msg->content);
}

void MainAPPStart::backlight_enable(int enable)
{
    LV_LOG_USER("<----!!!!!! enable =%d !!!!!!!---->",enable);
    if(enable==1)
    {
        system("echo 1 > /sys/class/pwm/pwmchip0/pwm0/enable");
        system("echo 1 > /sys/class/pwm/pwmchip0/pwm1/enable");
    }
    else
    {
        system("echo 0 > /sys/class/pwm/pwmchip0/pwm0/enable");
        system("echo 0 > /sys/class/pwm/pwmchip0/pwm1/enable");
    }
}
#endif

