/**
 * @file evdev.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "evdev.h"
#if USE_EVDEV != 0 || USE_BSD_EVDEV

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#if USE_BSD_EVDEV
#include <dev/evdev/input.h>
#else
#if(QTSIM_PLATFORM == 0)
#include <linux/input.h>
#endif
#endif

#if USE_XKB
#include "xkb.h"
#endif /* USE_XKB */

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
int map(int x, int in_min, int in_max, int out_min, int out_max);

/**********************
 *  STATIC VARIABLES
 **********************/
int evdev_fd = -1;
int evdev_root_x;
int evdev_root_y;
int evdev_button;

int evdev_key_val;

#if USE_MOUSE_DEV
#define MOUSE_HIDE_TIME     50
static int mouse_state = 0;
static bool mouse_flag = false;
static lv_obj_t* mouse_ptr=NULL;
#endif

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Initialize the evdev interface
 */
void evdev_init(void)
{
#if USE_MOUSE_DEV
    int i = 0;
    char devname[128]={0};
    if(access(MOUSE_DEV_FLAG,F_OK)==0)
    {
        while (1) {
            memset(devname,0,sizeof(devname));
            sprintf(devname,"/dev/input/event%d",i);
            if(access(devname,F_OK)==0)
            {
                i++;
                if(i>3)
                {
                    memset(devname,0,sizeof(devname));
                    sprintf(devname,"/dev/input/event%d",i-1);
                    break;
                }
            }
            else
            {
                memset(devname,0,sizeof(devname));
                sprintf(devname,"/dev/input/event%d",i-1);
                break;
            }
        }
        if (!evdev_set_file(devname))
        {
            return;
        }
        else {
            if(mouse_ptr==NULL)
            {
                mouse_ptr = lv_img_create(lv_layer_sys());
                lv_obj_set_pos(mouse_ptr,0,0);
                lv_obj_set_size(mouse_ptr,24,35);
                lv_obj_set_style_radius(mouse_ptr, 0, LV_PART_MAIN);
                lv_obj_set_style_pad_all(mouse_ptr, 0, LV_PART_MAIN);
                lv_obj_set_scrollbar_mode(mouse_ptr,LV_SCROLLBAR_MODE_OFF);
                lv_obj_set_style_bg_opa(mouse_ptr,LV_OPA_0,LV_PART_MAIN);
                lv_obj_set_style_bg_img_src(mouse_ptr,&mouse,LV_PART_MAIN);
                lv_obj_set_style_border_width(mouse_ptr, 0, LV_PART_MAIN);
                lv_obj_set_style_shadow_width(mouse_ptr, 0, LV_PART_MAIN);
            }
        }
    }
    else
    {
        return;
    }

#else
    if (!evdev_set_file(EVDEV_NAME))
    {
        return;
    }
#endif
#if USE_XKB
    xkb_init();
#endif
}

void evdev_deinit(void)
{
#if USE_MOUSE_DEV
    if(mouse_ptr!=NULL)
    {
        lv_obj_del(mouse_ptr);
        mouse_ptr = NULL;
    }
#endif
    if(evdev_fd != -1)
    {
       close(evdev_fd);
       evdev_fd=-1;
    }
    evdev_root_x = 0;
    evdev_root_y = 0;
    evdev_key_val = 0;
    evdev_button = LV_INDEV_STATE_REL;
}
/**
 * reconfigure the device file for evdev
 * @param dev_name set the evdev device filename
 * @return true: the device file set complete
 *         false: the device file doesn't exist current system
 */
bool evdev_set_file(char* dev_name)
{ 
     if(evdev_fd != -1)
     {
        close(evdev_fd);
        evdev_fd=-1;
     }

#if(QTSIM_PLATFORM == 0)

  #if USE_BSD_EVDEV
     evdev_fd = open(dev_name, O_RDWR | O_NOCTTY);
  #else
     evdev_fd = open(dev_name, O_RDWR | O_NOCTTY | O_NDELAY);
  #endif

     if(evdev_fd == -1) {
        perror("unable to open evdev interface:");
        return false;
     }

  #if USE_BSD_EVDEV
     fcntl(evdev_fd, F_SETFL, O_NONBLOCK);
  #else
     fcntl(evdev_fd, F_SETFL, O_ASYNC | O_NONBLOCK);
  #endif

#endif

     evdev_root_x = 0;
     evdev_root_y = 0;
     evdev_key_val = 0;
     evdev_button = LV_INDEV_STATE_REL;

     return true;
}

#if(QTSIM_PLATFORM == 1)
void touch_write_data(int x, int y, int touch)
{
    evdev_root_x = x;
    evdev_root_y = y;
    evdev_button = touch;
}

#endif
/**
 * Get the current position and state of the evdev
 * @param data store the evdev data here
 */
void evdev_read(lv_indev_drv_t * drv, lv_indev_data_t * data)
{
#if(QTSIM_PLATFORM == 0)
    static uint32 timecnt=0;
    struct input_event in;
    while(read(evdev_fd, &in, sizeof(struct input_event)) > 0)
    {
        #ifdef MOUSE_DEV_CHECK
        timecnt = 0;
        if(mouse_flag == false)
        {
            mouse_flag = true;
            if(mouse_ptr!=NULL)
            {
                lv_obj_clear_flag(mouse_ptr,LV_OBJ_FLAG_HIDDEN);
            }
        }
        #endif
        //LV_LOG_USER("input info:(%d, %d, %d)\n", in.code, in.type, in.value);
        if(in.type == EV_REL)
        {
            if(in.code == REL_X)
				#if EVDEV_SWAP_AXES
					evdev_root_y += in.value;
				#else
					evdev_root_x += in.value;
				#endif
            else if(in.code == REL_Y)
				#if EVDEV_SWAP_AXES
					evdev_root_x += in.value;
				#else
					evdev_root_y += in.value;
				#endif
        }
        else if(in.type == EV_ABS)
        {
            if(in.code == ABS_X)
				#if EVDEV_SWAP_AXES
					evdev_root_y = in.value;
				#else
					evdev_root_x = in.value;
				#endif
            else if(in.code == ABS_Y)
				#if EVDEV_SWAP_AXES
					evdev_root_x = in.value;
				#else
					evdev_root_y = in.value;
				#endif
            else if(in.code == ABS_MT_POSITION_X)
                                #if EVDEV_SWAP_AXES
                                        evdev_root_y = in.value;
                                #else
                                        evdev_root_x = in.value;
                                #endif
            else if(in.code == ABS_MT_POSITION_Y)
                                #if EVDEV_SWAP_AXES
                                        evdev_root_x = in.value;
                                #else
                                        evdev_root_y = in.value;
                                #endif
            else if(in.code == ABS_MT_TRACKING_ID)
                                if(in.value == -1)
                                    evdev_button = LV_INDEV_STATE_REL;
                                else //if(in.value == 0)
                                    evdev_button = LV_INDEV_STATE_PR;
        }
        else if(in.type == EV_KEY)
        {
            if(in.code == BTN_MOUSE || in.code == BTN_RIGHT || in.code == BTN_TOUCH)
            {
                if(in.value == 0)
                    evdev_button = LV_INDEV_STATE_REL;
                else if(in.value == 1)
                    evdev_button = LV_INDEV_STATE_PR;
            }
            else if(drv->type == LV_INDEV_TYPE_KEYPAD)
            {
              #if USE_XKB
                data->key = xkb_process_key(in.code, in.value != 0);
              #else
                switch(in.code)
                {
                    case KEY_BACKSPACE:
                        data->key = LV_KEY_BACKSPACE;
                        break;
                    case KEY_ENTER:
                        data->key = LV_KEY_ENTER;
                        break;
                    case KEY_PREVIOUS:
                        data->key = LV_KEY_PREV;
                        break;
                    case KEY_NEXT:
                        data->key = LV_KEY_NEXT;
                        break;
                    case KEY_UP:
                        data->key = LV_KEY_UP;
                        break;
                    case KEY_LEFT:
                        data->key = LV_KEY_LEFT;
                        break;
                    case KEY_RIGHT:
                        data->key = LV_KEY_RIGHT;
                        break;
                    case KEY_DOWN:
                        data->key = LV_KEY_DOWN;
                        break;
                    case KEY_TAB:
                        data->key = LV_KEY_NEXT;
                        break;
                    default:
                        data->key = 0;
                        break;
                }
            #endif /* USE_XKB */
               if (data->key != 0)
               {
                    /* Only record button state when actual output is produced to prevent widgets from refreshing */
                    data->state = (in.value) ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
                }
                evdev_key_val = data->key;
                evdev_button = data->state;
                return;
            }
        }
    }
    #ifdef MOUSE_DEV_CHECK
    if(access(MOUSE_DEV_FLAG,F_OK)==0)
    {
        if(mouse_state==0)
        {
            mouse_state = 1;
            mouse_flag = true;
            evdev_init();
        }
        timecnt++;
        if(timecnt>MOUSE_HIDE_TIME)
        {
            timecnt = 0;
            mouse_flag = false;
            if(mouse_ptr!=NULL)
            {
                lv_obj_add_flag(mouse_ptr,LV_OBJ_FLAG_HIDDEN);
            }
        }
    }
    else
    {
        if(mouse_state==1)
        {
            mouse_state = 0;
            mouse_flag = false;
            evdev_deinit();
        }
    }
    #endif

#else


#endif
    if(drv->type == LV_INDEV_TYPE_KEYPAD)
    {
        /* No data retrieved */
        data->key = evdev_key_val;
        data->state = evdev_button;
        return;
    }

    if(drv->type != LV_INDEV_TYPE_POINTER) return ;

    /*Store the collected data*/
#if EVDEV_CALIBRATE
    data->point.x = map(evdev_root_x, EVDEV_HOR_MIN, EVDEV_HOR_MAX, 0, drv->disp->driver->hor_res);
    data->point.y = map(evdev_root_y, EVDEV_VER_MIN, EVDEV_VER_MAX, 0, drv->disp->driver->ver_res);
#else
    data->point.x = evdev_root_x;
    data->point.y = evdev_root_y;
#endif

    data->state = evdev_button;
    if(data->point.x < 0) data->point.x = 0;
    if(data->point.y < 0) data->point.y = 0;
    if(data->point.x >= drv->disp->driver->hor_res) data->point.x = drv->disp->driver->hor_res - 1;
    if(data->point.y >= drv->disp->driver->ver_res) data->point.y = drv->disp->driver->ver_res - 1;
#if USE_MOUSE_DEV
    if(mouse_ptr!=NULL)
    {
        lv_obj_set_pos(mouse_ptr,data->point.x,data->point.y);
    }
#endif

    return ;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
int map(int x, int in_min, int in_max, int out_min, int out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#endif
