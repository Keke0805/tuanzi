/*
*******************************************************************************
* FileName: drv_op_key.c
* Description:
* History:
*       <author>    <time>          <version >      <desc>
*       CareyZeng    2021/08/24      1.0             ?????????
*******************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/bitypes.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <termios.h>
#include "applib.h"
#include "app_key.h"
#include "app_config.h"
#include "drv_op_key.h"
#include "plugin_input.h"
#include "mi_panel.h"
#include "mi_panel_datatype.h"

#define INPUT_LOCK_SUPPORT    0
#define ENTER_STANDBY_SUPPORT 1

#if (KEY_SUPPORT == 1)

static int s_key_device_fd = -1;
bool s_shortcut_enable = true;
bool s_keymapping_enable = true;
bool s_key_server_enble = true;
static int s_key_tone_auto_play = 0;

static int s_input_time_id = -1;
#define LOCK_INPUT_TIME     (5*1000)

bool plugin_input_in_screen_saver = false;

static void backlight_enable(int enable)
{
	if(enable)
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

static int plugin_input_get_charge_state()
{
	FILE *fps;
	char str2[32];
	int charge_state=-1;

	fps = fopen("/sys/class/power_supply/cw-bat/status","r");
	if(fps == NULL)
	{
		perror("fopen()");
		return -1;
	}
	fread(&str2,sizeof(str2),1,fps);
	fclose(fps);

	if(strstr(str2,"Unknown"))
	{
		charge_state = 0;
	}
	else if(strstr(str2,"Charging"))
	{
		charge_state = 1;
	}
	else if(strstr(str2,"Discharging"))
	{
		charge_state = 0;
	}
	else if(strstr(str2,"Notcharging"))
	{
		charge_state = 0;
	}
	else if(strstr(str2,"Full"))
	{
		charge_state = 1;
	}
	return charge_state;
}

/******************************************************************************/
/*!
* \par  Description:
*       ��������Ϣ���͵���Ϣ������
* \param[in]    mqd_t: ��Ҫ���͵���Ϣ����
* \param[in]    input_msg_t: ��Ҫ���͵���Ϣ
* \param[in]    int: 1
* \retval
*******************************************************************************/
bool post_key_msg(int mq_fd, input_msg_t * input_msg, int force)
{
    int result;
	msg_apps_t msg;

	memset(&msg, 0, sizeof(msg_apps_t));
	msg.type = MSG_KEY_INPUT;
	memcpy(&msg.content, input_msg, sizeof(input_msg_t));
	SSTAR_SendAsyncMsg(APP_NAME_BROADCAST, &msg);

    return true;
}

static bool check_key_saving(key_type_e cur_type, key_type_e map_type)
{
    bool result = false;

    switch( cur_type )
    {
    case KEY_TYPE_DOWN:
        switch( map_type )
        {
        case KEY_TYPE_LONG:
        case KEY_TYPE_HOLD:
        case KEY_TYPE_SHORT_UP:
        case KEY_TYPE_LONG_UP:
        case KEY_TYPE_HOLD_UP:
            result = true;
            break;

        default:
            break;
        }
        break;

    case KEY_TYPE_LONG:
        switch( map_type )
        {
        case KEY_TYPE_HOLD:
        case KEY_TYPE_LONG_UP:
        case KEY_TYPE_HOLD_UP:
            result = true;
            break;

        default:
            break;
        }
        break;

    case KEY_TYPE_HOLD:
        switch( map_type )
        {
        case KEY_TYPE_HOLD_UP:
            result = true;
            break;

        default:
            break;
        }
        break;

    default:
        break;
    }

    return result;
}

/******************************************************************************/
/*!
 * \par  Description:
 *      
 * \param[in]    unsigned int: 
 * \param[out]   input_gui_msg_t *: 
 * \retval
 *******************************************************************************/
bool process_key_event( struct input_event key_val_app, input_msg_t *input_msg )
{
    static key_type_e   saved_key_type = KEY_TYPE_NULL;
    static int saved_hold_key = -1;

    input_msg->data.kmsg.val = key_val_app.code;

   // printf("%s %d---key code=%d val=%d\n",__func__,__LINE__,key_val_app.code,key_val_app.value);
    switch ( key_val_app.value)
    {
        case 2 :
        {
            if(saved_key_type == KEY_TYPE_DOWN){
                input_msg->data.kmsg.type = KEY_TYPE_LONG;
                saved_key_type = KEY_TYPE_LONG;
            }
            else //if(saved_key_type == KEY_TYPE_LONG)
            {
                input_msg->data.kmsg.type = KEY_TYPE_HOLD;
                saved_key_type = KEY_TYPE_HOLD;
                saved_hold_key = key_val_app.code;
            }
        }
        break;
        case 1 :
        {
            input_msg->data.kmsg.type = KEY_TYPE_DOWN;
            saved_key_type = KEY_TYPE_DOWN;
            break;
        }
        case 0 :
        {

            if(saved_key_type == KEY_TYPE_LONG)
            {
                input_msg->data.kmsg.type = KEY_TYPE_LONG_UP;
                saved_key_type = KEY_TYPE_NULL;
            }
            else if(saved_key_type == KEY_TYPE_DOWN)
            {
            	if (saved_hold_key != -1 && saved_hold_key == key_val_app.code)
            	{
            		input_msg->data.kmsg.type = KEY_TYPE_HOLD_UP;
            	}
            	else
            	{
            		input_msg->data.kmsg.type = KEY_TYPE_SHORT_UP;
            	}
                saved_key_type = KEY_TYPE_NULL;
            	saved_hold_key = -1;
            }
            else if(saved_key_type == KEY_TYPE_HOLD)
            {
                input_msg->data.kmsg.type = KEY_TYPE_HOLD_UP;
                saved_key_type = KEY_TYPE_NULL;
                saved_hold_key = -1;
            }
            else
            {
                input_msg->data.kmsg.type = KEY_TYPE_NULL;
                saved_key_type = KEY_TYPE_NULL;
                printf("\n can not recognize key type\n");
                return false;
            }
        }
        break;
        default :
        {
            return false;
            break;
        }

    }
    return true;
}


#if (ENTER_STANDBY_SUPPORT == 1)

static void _power_key_proc(input_msg_t input_msg)
{
    key_event_t key_event;
    key_event = input_msg.data.kmsg;
    int ret=0;

	msg_apps_t msg;
	MI_PANEL_BackLightConfig_t BackLightCfg;
#if 0
	static int power_sta=1;
    if((KEY_POWER == key_event.val) && (KEY_TYPE_SHORT_UP == key_event.type))
    {        
    	if(power_sta==1)
    	{
    		printf("enter standby\n");
        	power_sta = 0;
        	backlight_enable(0);
        	msg.type = MSG_STANDBY;
        	SSTAR_SendAsyncMsg(APP_NAME_BROADCAST, &msg);
    	}
    	else
    	{
    		printf("exit standby\n");
    		power_sta = 1;
    		backlight_enable(1);
    		msg.type = MSG_RESUME;
    		SSTAR_SendAsyncMsg(APP_NAME_BROADCAST, &msg);

    	}
    }
#else
    static int power_sta=-1;
    static char power_val[4];
    if(power_sta==-1)
    {
		FILE *fd = fopen("/sys/class/power_supply/ats3609-usb/device/power_state","r");
		if(NULL!=fd)
		{
			fread(&power_val,sizeof(power_val),1,fd);
			power_sta=atoi(power_val);
			printf("power_status:%d\n",power_sta);
		}
		fclose(fd);
    }
    //printf("key_event.type = %x\n",key_event.type);
    if((KEY_POWER == key_event.val))
	{
    	/*if(power_sta==-1)
    	{
    		if(key_event.type==KEY_TYPE_DOWN||key_event.type==KEY_TYPE_HOLD)
    		{
    			printf("power key first down\n");
    			power_sta = 1;
    		}
    	}
    	else */
    	if(power_sta==1)
		{
    		if(key_event.type==KEY_TYPE_HOLD_UP || key_event.type==KEY_TYPE_SHORT_DOWN)//||key_event.type==KEY_TYPE_SHORT_UP
    		{
				printf("power key up,enter standby\n");
				power_sta = 0;
				ret = plugin_input_get_charge_state();
				if(ret==1)
				{
					msg.type = MSG_STANDBY;
					backlight_enable(0);
    			}
				else
					msg.type = MSG_POWER_OFF;
				SSTAR_SendAsyncMsg(APP_NAME_BROADCAST, &msg);
    		}
		}
		else
		{
			if(key_event.type==KEY_TYPE_HOLD)
			{
				printf("exit standby\n");
				system("echo 1 > /sys/class/power_supply/ats3609-usb/device/power_state");
				power_sta = 1;
				backlight_enable(1);
				msg.type = MSG_RESUME;
				SSTAR_SendAsyncMsg(APP_NAME_BROADCAST, &msg);
			}
		}
	}
    else
    {
    	if(power_sta==1)
		{
    		if(key_event.type==KEY_TYPE_HOLD_UP)//||key_event.type==KEY_TYPE_SHORT_UP
    		{
				printf("power key up,enter standby\n");
				power_sta = 0;
				ret = plugin_input_get_charge_state();
				if(ret==1)
				{
					msg.type = MSG_STANDBY;
					backlight_enable(0);
    			}
				else
					msg.type = MSG_POWER_OFF;
				SSTAR_SendAsyncMsg(APP_NAME_BROADCAST, &msg);
    		}
		}
		else
		{
			if(key_event.type==KEY_TYPE_HOLD)
			{
				printf("exit standby\n");
				system("echo 1 > /sys/class/power_supply/ats3609-usb/device/power_state");
				power_sta = 1;
				backlight_enable(1);
				msg.type = MSG_RESUME;
				SSTAR_SendAsyncMsg(APP_NAME_BROADCAST, &msg);
			}
		}
    }
#endif
}

#endif

int get_device_name(char *driver_name, char *device_name)
{
    int fd;
    int ret;
    char buffer[1024];
    char key[100];
    char *p1, *p2, *p3;

    fd = open("/proc/bus/input/devices", O_RDONLY);
    if(fd < 0)
    {
        KEY_ERR("open file fail: /proc/bus/input/devices\n");
        return -1;
    }

    ret = read(fd, buffer, 1023);
    if(ret < 0)
    {
        KEY_ERR("read fail\n");
        close(fd);
        return -1;
    }

    buffer[ret] = 0;
    close(fd);

    sprintf(key, "N: Name=\"%s", driver_name);
    p1 = strstr(buffer, key);
    if(NULL == p1) return -1;


    p3 = strstr(p1, "H: Handlers=kbd ");
    if(NULL == p3)
    {
	    p3 = strstr(p1, "H: Handlers=");
	    if(NULL == p3) return -1;
        p1 = p3;
	    p1 += strlen("H: Handlers=");
	    while(*p1 == ' ') p1++;
    }
    else
    {
        p1 = p3;
 	    p1 += strlen("H: Handlers=kbd ");
	    while(*p1 == ' ') p1++;
    }

    p2 = p1;
    while((*p2 != ' ') && (*p2 != '\n') && (*p2 != 0)) p2++;

    *p2 = 0;
    sprintf(device_name, "/dev/input/%s", p1);
    printf("find %s device: %s\n", driver_name, device_name);
    return 0;
}

int key_device_open(int type)
{
    int ret;
    char deviceName[30];
	int key_fd;
    char driverName[30] = {0};

    if(type == KEY_GPIO)
    {       
        memset(driverName, 0, sizeof(driverName));
        strcpy(driverName, KEY_GPIO_NAME);  
    }
    else
        return -1;

    ret = get_device_name(driverName, deviceName);
    if(ret < 0)
    {
        //print_err("can no find key device\n");
        return -1;
    }

    key_fd = open(deviceName, O_RDWR | O_NONBLOCK);
    if (key_fd < 0)
    {
        //print_err("Error: open key device\n\n");
        return key_fd;
    }
   
    return key_fd;
}

void key_device_close( int fd )
{
    if (-1 != fd)
    {
        close(fd);
        //fd = -1;
    }
}

/******************************************************************************/
/*!
* \par  Description:
*       ????????????, ????????��???????????, ?????????????????
* \param[out]   unsigned int:
* \retval
*******************************************************************************/
bool key_get_input_event_drv_keyval(int fd, struct input_event *key_val_drv)
{
    int tmp;
    struct input_event tmp_key_drv = {0};

    if (-1 == fd)
    {
        KEY_ERR("key device isn't open\n");
        return false;
    }

    tmp = read(fd, &tmp_key_drv, sizeof(tmp_key_drv));
    if ((unsigned int)tmp != sizeof(tmp_key_drv))
    {
        return false;
    }
    if(tmp_key_drv.type != EV_KEY)
    {
    	return false;
    }
    *key_val_drv = tmp_key_drv;
    //memcpy(key_val_drv,&tmp_key_drv,sizeof(struct input_event));
    return true;
}


/******************************************************************************/
/*!
* \par  Description:
*       
* \param[in]   int: 
* \param[out]   unsigned int: 
* \retval       int: 
* \note :
*******************************************************************************/
int get_input_event_keyval(int fd, int num, struct input_event *p_keyval)
{
    static int position_save_key = 0;
    int result = 0;
    bool tmp;
    struct input_event keyval_drv_jitter = {0};
    while(1)
    {
        tmp = key_get_input_event_drv_keyval(fd, &keyval_drv_jitter );
        if( false == tmp )
        {
            break;
        }

        *(p_keyval + result) = keyval_drv_jitter;
        result++;
        if ( result >= num )
        {
            break;
        }
    }

    return result;
}

/******************************************************************************/
/*!
 * \par  Description:
 *       
 *       read key value from key driver,
 *       play key tone, detect weather keylock, search map key, search shortcut key,
 *       and finally send key message to ucGUI
 * \param[in]
 * \retval
 *******************************************************************************/
int key_device_get_msg(int fd)
{
    static bool is_just_exit_screensaver = false;
    static bool is_in_screensaver = false;
    static struct input_event buffer_keyval[10];
    bool result = true;
    input_msg_t input_msg;
    int i;
    int key_num;
    key_event_t *key_msg;
    int64_t t1;

    memset(&buffer_keyval, 0x00, sizeof(buffer_keyval));
    memset(&input_msg, 0x00, sizeof(input_msg));
    input_msg.type = INPUT_MSG_KEY;

    key_num = get_input_event_keyval(fd, sizeof(buffer_keyval)/sizeof(struct input_event),buffer_keyval);
    for( i=0; i<key_num; i++ )
    {
        result = process_key_event( buffer_keyval[i], &input_msg );

        if ( false == result )
        {
            continue;
        }

        key_msg = &input_msg.data.kmsg;
        is_in_screensaver = plugin_input_in_screen_saver;

		_power_key_proc(input_msg);
		
        if((0 != (key_msg->type & KEY_TYPE_DOWN)) && (plugin_input_in_screen_saver == true))
        {
         
            plugin_input_in_screen_saver = false;
            is_just_exit_screensaver = true;
            continue;
        }
        else if ( true == is_just_exit_screensaver )
        {
            if ( KEY_TYPE_DOWN == input_msg.data.kmsg.type )
                is_just_exit_screensaver = false;
            else
            {
                if((key_msg->val == KEY_POWER) && (key_msg->type & KEY_TYPE_LONG))
                    printf("--power key long down, deal it--\n");
                else
                    continue;
            }
        }        

        //if (true == result)
        //{
            //if ( KEY_TYPE_HOLD_UP == input_msg.data.kmsg.type )
            //    result = post_key_msg(0, &input_msg, 1);
            //else
            //    result = post_key_msg(0, &input_msg, 0);
        //}
  
    }

    return 0;
}
#endif



