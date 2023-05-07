/**
 * @file: sunxi_key.c
 * @autor: huangyixiu
 * @url: huangyixiu@allwinnertech.com
 */
/*********************
 *      INCLUDES
 *********************/
#include "sunxi_key.h"
//#include "input-event-codes.h"
#if USE_SUNXI_KEY != 0

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <pthread.h>

p_keydev_callback keydev_callback = NULL;
p_keydev_feedback keydev_callfeedback = NULL;

lv_group_t *keygroup = NULL;

/*********************
 *      DEFINES
 *********************/
#ifdef USE_SUNXI_ADC_KEY
int adckey_dev_fd = -1;
#endif
#ifdef USE_SUNXI_IR_KEY
int irkey_dev_fd = -1;
#endif
pthread_mutex_t keydev_mutex;
pthread_t keydev_pthread_id;

static uint32 last_time = 0;
static uint32 cur_time = 0;
static bool update_flag = false;
static lv_timer_t * lvgl_task=NULL;

uint32_t last_key_type;
uint32_t last_key_value;
lv_indev_state_t last_key_state = LV_INDEV_STATE_REL;

lv_indev_state_t key_state_save = LV_INDEV_STATE_REL;

static void lvgl_task_cb(lv_timer_t * tmr)
{
    static int timecnt=0;
    timecnt++;
    if(update_flag)
    {
        pthread_mutex_lock(&keydev_mutex);
        if (keydev_callback) {
            keydev_callback(last_key_type, last_key_value, last_key_state);
        }
        update_flag = false;
        last_key_value = 0;
        last_key_state = LV_INDEV_STATE_REL;
        pthread_mutex_unlock(&keydev_mutex);
    }
}

void *keydev_thread(void * data)
{
	(void)data;
	int ret;
	fd_set readfd;
	int max_fd = -1;
	struct timeval timeout;
	struct input_event in;
	static int press_cnt;

	while(1)
	{
		timeout.tv_sec=5;
	    timeout.tv_usec=0;

	    FD_ZERO(&readfd);
#ifdef USE_SUNXI_ADC_KEY
		max_fd = adckey_dev_fd;
	    FD_SET(adckey_dev_fd, &readfd);
#endif
#ifdef USE_SUNXI_IR_KEY
		FD_SET(irkey_dev_fd, &readfd);
		max_fd = irkey_dev_fd;
#endif

#if defined(USE_SUNXI_IR_KEY) && defined(USE_SUNXI_ADC_KEY)
		max_fd = (irkey_dev_fd > adckey_dev_fd)?irkey_dev_fd:adckey_dev_fd;
#endif
        ret = select(max_fd+1, &readfd, NULL, NULL, &timeout);
		if (ret > 0)
	    {
#ifdef USE_SUNXI_ADC_KEY
			if(FD_ISSET(adckey_dev_fd,&readfd)) {
				FD_CLR(adckey_dev_fd, &readfd);
                if(read(adckey_dev_fd, &in, sizeof(in))>0)
                {
                    //LV_LOG_USER("input info:(%d, %d, %d)\n", in.code, in.type, in.value);
                    if(!update_flag)
                    {
                        pthread_mutex_lock(&keydev_mutex);
                        last_key_type = in.type;
                        if(in.type == EV_KEY) {
							if(last_key_value != in.code)
							{
								last_time = cur_time;
                                key_state_save = LV_INDEV_STATE_REL;
							}
                            last_key_value = in.code;
                            if (in.value == 0) {
                                if(key_state_save == LV_INDEV_STATE_PR)
                                {
                                    cur_time = custom_tick_get();
                                }
                                else
                                {
                                    cur_time = custom_tick_get();
									last_time = cur_time;
                                }
                                if((cur_time - last_time) < 30)
                                {
                                    last_key_state = LV_INDEV_STATE_REL;
                                    update_flag = false;
                                }
                                else if((cur_time - last_time) >= 30 && (cur_time - last_time) < 500)
                                {
                                    last_key_state = LV_INDEV_STATE_PR;
                                    update_flag = true;
                                }
                                else if((cur_time - last_time) >= 500 && (cur_time - last_time) < 1000)
                                {
                                    last_key_state = LV_INDEV_STATE_LONG_PR;
                                    update_flag = true;
                                }
                                else
                                {
                                    last_key_state = LV_INDEV_STATE_HOLD;
                                    update_flag = true;
                                }
                                last_time = cur_time;
                                key_state_save = LV_INDEV_STATE_REL;
                            }
                            else{
                                if(key_state_save == LV_INDEV_STATE_REL)
                                {
                                    cur_time = custom_tick_get();
                                    last_time = cur_time;
                                }
                                else
                                {
                                    cur_time = custom_tick_get();
                                }
                                key_state_save = LV_INDEV_STATE_PR;
                                if((cur_time - last_time) >= 500 && (cur_time - last_time) < 1000 && last_key_state!=LV_INDEV_STATE_LONG_PR)
                                {
                                    last_key_state = LV_INDEV_STATE_LONG_PR;
                                    update_flag = true;
                                }
                                else if((cur_time - last_time) >= 1000)
                                {
                                    last_key_state = LV_INDEV_STATE_HOLD;
                                    update_flag = true;
                                }
                            }
                        }
                        else if(in.type == EV_MSC)
                        {
                        	if(last_key_value != in.code)
							{
								last_time = cur_time;
                                key_state_save = LV_INDEV_STATE_REL;
							}
                            last_key_value = in.value;
                            if (in.value == 0) {
                                if(key_state_save == LV_INDEV_STATE_PR)
                                {
                                    cur_time = custom_tick_get();
                                }
                                else
                                {
                                    cur_time = custom_tick_get();
									last_time = cur_time;
                                }
                                if((cur_time - last_time) < 30)
                                {
                                    last_key_state = LV_INDEV_STATE_REL;
                                    update_flag = false;
                                }
                                else if((cur_time - last_time) >= 30 && (cur_time - last_time) < 500)
                                {
                                    last_key_state = LV_INDEV_STATE_PR;
                                    update_flag = true;
                                }
                                else if((cur_time - last_time) >= 500 && (cur_time - last_time) < 1000)
                                {
                                    last_key_state = LV_INDEV_STATE_LONG_PR;
                                    update_flag = true;
                                }
                                else
                                {
                                    last_key_state = LV_INDEV_STATE_HOLD;
                                    update_flag = true;
                                }
                                last_time = cur_time;
                                key_state_save = LV_INDEV_STATE_REL;
                            }
                            else{
                                if(key_state_save == LV_INDEV_STATE_REL)
                                {
                                    cur_time = custom_tick_get();
                                    last_time = cur_time;
                                }
                                else
                                {
                                    cur_time = custom_tick_get();
                                }
                                key_state_save = LV_INDEV_STATE_PR;
								if((cur_time - last_time) >= 500 && (cur_time - last_time) < 1000 && last_key_state!=LV_INDEV_STATE_LONG_PR)
                                {
                                    last_key_state = LV_INDEV_STATE_LONG_PR;
                                    update_flag = true;
                                }
                                else if((cur_time - last_time) >= 1000)
                                {
                                    last_key_state = LV_INDEV_STATE_HOLD;
                                    update_flag = true;
                                }
                            }
                        }
                        else if (in.type == EV_PWR) {
                              last_key_value = in.code;
                              if(in.value == 0) {
                                  last_key_state = LV_INDEV_STATE_REL;
                              }
                              else {
                                  last_key_state = LV_INDEV_STATE_PR;
                              }
                              update_flag = true;
                        }
                        pthread_mutex_unlock(&keydev_mutex);
                    }
				}
            }
#endif
#ifdef	USE_SUNXI_IR_KEY
			if(FD_ISSET(irkey_dev_fd,&readfd)) {
				FD_CLR(irkey_dev_fd, &readfd);
                if(read(irkey_dev_fd, &in, sizeof(in))>0)
                {
                    //LV_LOG_USER("input info:(%d, %d, %d)\n", in.code, in.type, in.value);
                    if(!update_flag)
                    {
                        pthread_mutex_lock(&keydev_mutex);
                        last_key_type = in.type;
                        if(in.type == EV_KEY) {
							if(last_key_value != in.code)
							{
								last_time = cur_time;
                                key_state_save = LV_INDEV_STATE_REL;
							}
                            last_key_value = in.code;
                            if (in.value == 0) {
								if(key_state_save == LV_INDEV_STATE_PR)
                                {
                                    cur_time = custom_tick_get();
                                }
                                else
                                {
                                    cur_time = custom_tick_get();
									last_time = cur_time;
                                }
                                if((cur_time - last_time) < 30)
                                {
                                    last_key_state = LV_INDEV_STATE_REL;
                                    update_flag = false;
                                }
                                else if((cur_time - last_time) >= 30 && (cur_time - last_time) < 500)
                                {
                                    last_key_state = LV_INDEV_STATE_PR;
                                    update_flag = true;
                                }
                                else if((cur_time - last_time) >= 500 && (cur_time - last_time) < 1000)
                                {
                                    last_key_state = LV_INDEV_STATE_LONG_PR;
                                    update_flag = true;
                                }
                                else
                                {
                                    last_key_state = LV_INDEV_STATE_HOLD;
                                    update_flag = true;
                                }
                                last_time = cur_time;
                                key_state_save = LV_INDEV_STATE_REL;
                            }
                            else{
                                if(key_state_save == LV_INDEV_STATE_REL)
                                {
                                    cur_time = custom_tick_get();
                                    last_time = cur_time;
                                }
                                else
                                {
                                    cur_time = custom_tick_get();
                                }
                                key_state_save = LV_INDEV_STATE_PR;
                                if((cur_time - last_time) >= 500 && (cur_time - last_time) < 1000 && last_key_state!=LV_INDEV_STATE_LONG_PR)
                                {
                                    last_key_state = LV_INDEV_STATE_LONG_PR;
                                    update_flag = true;
                                }
                                else if((cur_time - last_time) >= 1000)
                                {
                                    last_key_state = LV_INDEV_STATE_HOLD;
                                    update_flag = true;
                                }
                            }
                        }
                        else if(in.type == EV_MSC)
                        {
                        	if(last_key_value != in.code)
							{
								last_time = cur_time;
                                key_state_save = LV_INDEV_STATE_REL;
							}
                            last_key_value = in.value;
                            if (in.value == 0) {
                                if(key_state_save == LV_INDEV_STATE_PR)
                                {
                                    cur_time = custom_tick_get();
                                }
                                else
                                {
                                    cur_time = custom_tick_get();
									last_time = cur_time;
                                }
                                if((cur_time - last_time) < 30)
                                {
                                    last_key_state = LV_INDEV_STATE_REL;
                                    update_flag = false;
                                }
                                else if((cur_time - last_time) >= 30 && (cur_time - last_time) < 500)
                                {
                                    last_key_state = LV_INDEV_STATE_PR;
                                    update_flag = true;
                                }
                                else if((cur_time - last_time) >= 500 && (cur_time - last_time) < 1000)
                                {
                                    last_key_state = LV_INDEV_STATE_LONG_PR;
                                    update_flag = true;
                                }
                                else
                                {
                                    last_key_state = LV_INDEV_STATE_HOLD;
                                    update_flag = true;
                                }
                                last_time = cur_time;
                                key_state_save = LV_INDEV_STATE_REL;
                            }
                            else{
                                if(key_state_save == LV_INDEV_STATE_REL)
                                {
                                    cur_time = custom_tick_get();
                                    last_time = cur_time;
                                }
                                else
                                {
                                    cur_time = custom_tick_get();
                                }
                                key_state_save = LV_INDEV_STATE_PR;
                                if((cur_time - last_time) >= 500 && (cur_time - last_time) < 1000 && last_key_state!=LV_INDEV_STATE_LONG_PR)
                                {
                                    last_key_state = LV_INDEV_STATE_LONG_PR;
                                    update_flag = true;
                                }
                                else if((cur_time - last_time) >= 1000)
                                {
                                    last_key_state = LV_INDEV_STATE_HOLD;
                                    update_flag = true;
                                }
                            }
                        }
                        pthread_mutex_unlock(&keydev_mutex);
                    }
				}
            }
#endif
		}

	}
}

void keydev_init(void)
{
	int ret;
	pthread_attr_t attr;

#ifdef USE_SUNXI_ADC_KEY
    adckey_dev_fd = open(ADCKEY_DEV_NAME,  O_RDONLY | O_NONBLOCK);
    if(adckey_dev_fd == -1) {
        perror("unable open evdev interface:");
        return;
    }
#endif

#ifdef USE_SUNXI_IR_KEY
	irkey_dev_fd = open(IRKEY_DEV_NAME,  O_RDONLY | O_NONBLOCK);
	if(irkey_dev_fd == -1) {
		perror("unable open evdev interface:");
		return;
	}
#endif
	last_key_type = 0;
	last_key_value = 0;
	last_key_state = LV_INDEV_STATE_REL;
	pthread_mutex_init (&keydev_mutex, NULL);
	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr, 0x4000);

	ret = pthread_create(&keydev_pthread_id, &attr, keydev_thread, NULL);
	pthread_attr_destroy(&attr);
	if (ret == -1) {
		printf("create thread fail\n");
		return ;
	}
    //lvgl_task = lv_timer_create(lvgl_task_cb, 50, 0);

}

void keydev_uninit(void)
{
    if(lvgl_task)
    {
        lv_timer_del(lvgl_task);
        lvgl_task = NULL;
    }

	pthread_join(keydev_pthread_id, NULL);
	pthread_mutex_destroy(&keydev_mutex);

	last_key_type = 0;
	last_key_value = 0;
	last_key_state = LV_INDEV_STATE_REL;
#ifdef USE_SUNXI_ADC_KEY
	if (adckey_dev_fd != -1){
		close(adckey_dev_fd);
	}
#endif
#ifdef USE_SUNXI_IR_KEY
	if (irkey_dev_fd != -1){
		close(irkey_dev_fd);
	}
#endif
}

void keydev_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    (void) indev_drv;      /*Unused*/

    pthread_mutex_lock(&keydev_mutex);
#ifdef USE_SUNXI_TP_KEY
    static bool but_flag = true;
    lv_indev_state_t encoder_act= LV_INDEV_STATE_REL;
    uint32_t act_key=0;
    int32_t encoder_diff=0;

    if(last_key_value==KEY_ENTER)	//编码器的按键
    {
        act_key = LV_KEY_ENTER;
        encoder_act = last_key_state;
    }
    if((last_key_value==KEY_LEFT)&&but_flag)	//编码器左转
    {
        act_key = LV_KEY_LEFT;
        encoder_diff--;
        encoder_act = LV_INDEV_STATE_REL;
        but_flag = false;
    }
    else if((last_key_value==KEY_RIGHT)&&but_flag)//编码器右转
    {
        act_key = LV_KEY_RIGHT;
        encoder_diff++;
        encoder_act = LV_INDEV_STATE_REL;
        but_flag = false;
    }
    else {but_flag = true;}

    data->key = act_key;
    data->enc_diff = encoder_diff;
    data->state = encoder_act;
    encoder_diff = 0;

    if(update_flag)
    {
        if (keydev_callback) {
            keydev_callback(last_key_type, last_key_value, last_key_state);
        }
        update_flag = false;
        last_key_value = 0;
        last_key_state = LV_INDEV_STATE_REL;
    }
#else
    data->state = last_key_state;
    data->key = last_key_value;
#endif
    pthread_mutex_unlock(&keydev_mutex);
}

void keydev_feedback(lv_indev_drv_t * drv, uint8_t code)
{
    if (keydev_callfeedback) {
        keydev_callfeedback(code);
    }
}

void keydev_register_feedback(p_keydev_feedback func)
{
    keydev_callfeedback = func;
}

void keydev_register_hook(p_keydev_callback func)
{
	keydev_callback = func;
}

lv_group_t* key_group_create(void)
{
	if(keygroup==NULL)
	{
		keygroup = lv_group_create();
	}
	return keygroup;
}

void key_group_del()
{
	if(keygroup) {
		lv_group_del(keygroup);
		keygroup = NULL;
	}
}

lv_group_t* get_key_group(void)
{
	return keygroup;
}

#endif
