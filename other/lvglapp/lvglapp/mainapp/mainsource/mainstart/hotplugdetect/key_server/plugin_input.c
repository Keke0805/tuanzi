/*
*******************************************************************************
* FileName: plugin_input.c
* Description:
* History:
*       <author>    <time>          <version >      <desc>
*       CareyZeng    2021/08/24      1.0             ?????????
*******************************************************************************
*/

#ifdef __cplusplus
extern "C"
{
#endif


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/bitypes.h>
#include <ctype.h>
#include <errno.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include <fcntl.h>
#include "applib.h"
#include "app_config.h"
#include "drv_op_key.h"





typedef struct
{
    pthread_t mTid;
    //pthread_mutex_t mLock;
    int mRunning;
    int mGpiokeyFd;
}plugin_input_t;

int64_t last_load_ir_time=0;
plugin_input_t *g_input;


static void *_plugin_input_loop(void *param)
{
    int ret;
    fd_set rs;
    int maxFd;
    struct timeval tv;
    char buffer[4];
    int64_t wait_time;
    plugin_input_t *input = (plugin_input_t*)param;

	maxFd = input->mGpiokeyFd;
	
    while(input->mRunning == 1)
    {       
		if(input->mGpiokeyFd < 0)
        {
#if (GPIO_KEY_SUPPORT == 1)
            int64_t cur_time;

            cur_time = get_tick_time_ms();
            if(((cur_time - last_load_ir_time) > 1000) || ((cur_time - last_load_ir_time) < 0))
            {
                input->mGpiokeyFd = key_device_open(KEY_GPIO);
                maxFd = (maxFd > input->mGpiokeyFd) ? maxFd : input->mGpiokeyFd;
                last_load_ir_time = cur_time;
            }
#endif
        }

        FD_ZERO(&rs);
        if(input->mGpiokeyFd >= 0)
            FD_SET(input->mGpiokeyFd, &rs);
            
        wait_time = 1000;      
        tv.tv_sec = wait_time / 1000;
        tv.tv_usec = (wait_time % 1000) * 1000;

        ret = select(maxFd + 1, &rs, NULL, NULL, &tv);
        if(ret <= 0)
            continue;

#if(GPIO_KEY_SUPPORT==1)
		if(input->mGpiokeyFd >= 0)
		{
			if(FD_ISSET(input->mGpiokeyFd, &rs))
				key_device_get_msg(input->mGpiokeyFd);
		}
#endif
        //pthread_mutex_unlock(&input->mLock);
    }

    return NULL;
}

/*-----------------------------------------------------------------------------------------*/

static void plugin_input_start(void *handle)
{
    int ret;
    plugin_input_t *input = (plugin_input_t*)handle;

    if(handle == NULL)
        return;

    input->mRunning = 1;
    ret = pthread_create(&input->mTid, NULL, _plugin_input_loop, (void *)input);
    if(ret != 0)
    {
        KEY_ERR("create thread fail, ret=%d\n", ret);
        input->mRunning = 0;
    }
}

static void plugin_input_close(plugin_input_t *handle)
{
    plugin_input_t *input = (plugin_input_t*)handle;

    if(handle == NULL)
        return;

    if(input->mRunning == 1)
    {
        input->mRunning = 0;
        pthread_join(input->mTid, NULL);
    }

#if (GPIO_KEY_SUPPORT==1)
	if(input->mGpiokeyFd >= 0)
	{
		key_device_close(input->mGpiokeyFd);
		input->mGpiokeyFd = -1;
	}
#endif

    //pthread_mutex_destroy(&input->mLock);
    free(input);
}

static plugin_input_t* plugin_input_open(void)
{
    plugin_input_t *input;
    int ret;

    input = (plugin_input_t*)malloc(sizeof(plugin_input_t));
    if(input == NULL)
        return NULL;

    memset(input, 0, sizeof(plugin_input_t));
	input->mGpiokeyFd = -1;

#if (GPIO_KEY_SUPPORT == 1)
	last_load_ir_time = get_tick_time_ms();
	input->mGpiokeyFd = key_device_open(KEY_GPIO);
#endif
	plugin_input_start(input);
    return input;

ERROUT:
    plugin_input_close(input);
    return NULL;
}

void sstar_plugin_input_close(void)
{
	plugin_input_close(g_input);
}
void sstar_plugin_input_open(void)
{
	g_input = plugin_input_open();
}

#ifdef __cplusplus
}
#endif

