/*
 * appmsg.c
 *
 *  Created on: 2022??07??15??
 *      Author: CareyZeng
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include "appmsg.h"
#include "common/list.h"
#include "lvgl/src/custom/cjson/cJSON.h"
#include "lvgl/lvgl.h"
#include "common/common.h"

#define APL_INF(fmt, arg...) printf("[APL-INF]%s: " fmt "\n" ,__func__, ## arg)
#define APL_ERR(fmt, arg...) printf("[APL-ERROR]%s-%d: " fmt "\n" ,__func__,__LINE__, ## arg)
#define APL_DBG(fmt, arg...) printf("[APL-DBG]%s-%d: " fmt "\n" ,__func__,__LINE__, ## arg)

typedef struct
{
    struct list_head list;
    ApplibCallback pfnCallback;
    char dst[16];
}ApplibCallbackListData_t;

typedef struct
{
    struct list_head list;
    msg_apps_t msg;
    int flag;
    char dst[16];
}msg_list_t;

typedef struct{
    pthread_t MsgProc_tid;
    pthread_mutex_t MsgProcLock;
    pthread_cond_t MsgProcCondition;
    pthread_mutex_t MsgProcDataLock;
    msg_list_t Msg_list;
    char MsgProc_start;
    int msg_total;
    int proc_num;
}applib_msg_proc_t;

static int g_registerApplibChanged = 0;
static struct list_head g_ApplibCallbackListHead;
static pthread_mutex_t g_ApplibCallbackListMutex;
static pthread_mutex_t g_ApplibParamMutex;

static int g_ApplibMsgProcThreadRun = 0;
static applib_msg_proc_t g_applibMsg;
static int applib_open_cnt=0;
cJSON * g_GlobalSettingRoot=NULL;

//applib message processing center
static void applib_proc_messages(msg_apps_t *msg)
{
	static int keytone_sw = 0;
    //LV_LOG_USER("msg.type=%d | msg.mode=%d | msg.csize=%d| msg.content=%s\n",msg->type,msg->mode,msg->csize,msg->content);
    #ifdef _UCHIP_T113
    if(msg->type == UI_VIDEOPLAY)
    {
        player_ui_t *player_ui = media_get_player_data();
        switch (msg->mode) {
            case VPLAY_DEFAULAT_CMD:
            tplayer_set_rotate(player_ui->tplayer, TPLAYER_VIDEO_ROTATE_DEGREE_90);
            break;
            case VPLAY_INIT_CMD:
            tplayer_init(player_ui->tplayer, CEDARX_PLAYER);
            break;
            case VPLAY_EXIT_CMD:
            tplayer_exit(player_ui->tplayer);
            break;
            case VPLAY_PREPARE_CMD:
            tplayer_play_url(player_ui->tplayer, "/mnt/UDISK/720p.mp4");
            break;
            case VPLAY_PLAY_CMD:
            tplayer_set_displayrect(player_ui->tplayer, 0, 0, 1280, 800);
            tplayer_play(player_ui->tplayer);
            break;
            case VPLAY_PAUSE_CMD:
            tplayer_pause(player_ui->tplayer);
            break;
            case VPLAY_STOP_CMD:
            tplayer_stop(player_ui->tplayer);
            break;
            case VPLAY_SEEK_TO:
            tplayer_seekto(player_ui->tplayer,0);
            break;
            case VPLAY_SETTING:
            tplayer_set_looping(player_ui->tplayer,true);
            break;
            default:
            break;
        }
    }
	if(msg->type ==UI_PLAY_KEYTONE)
	{
		system("aplay /usr/bin/resource/song/keytone1.wav");
	}
    #endif
}

static void *ApplibPostCallbackMsg(char *dst_name, msg_apps_t *msg)
{
    ApplibCallbackListData_t *cur = NULL;

    pthread_mutex_lock(&g_ApplibCallbackListMutex);
    list_for_each_entry(cur, &g_ApplibCallbackListHead, list)
    {
        if(strcmp(dst_name, cur->dst)==0||strcmp("broadcast", dst_name)==0)
            cur->pfnCallback(msg);
    }
    pthread_mutex_unlock(&g_ApplibCallbackListMutex);

    return NULL;
}

/*************************************
Author: Carey
*return: 0=success,-1=fail
**************************************/
int applib_start_proc_msg(applib_msg_proc_t *scene)
{
    int ret=0;

    pthread_mutex_lock(&scene->MsgProcLock);
    scene->MsgProc_start=1;
    pthread_cond_signal(&scene->MsgProcCondition);
    pthread_mutex_unlock(&scene->MsgProcLock);
    return ret;
}


/*************************************
Author: Carey
*return: 0=success,-1=fail
**************************************/
int applib_free_msg_list_res(applib_msg_proc_t *scene)
{
    msg_list_t *cur=NULL;
    msg_list_t *next=NULL;

    list_for_each_entry_safe(cur, next, &scene->Msg_list.list, list)
    {
        list_del(&cur->list);
        cur = NULL;
    }
    scene->msg_total = 0;
    scene->proc_num = 0;
    return 0;
}

/*************************************
Author: Carey
*return: 0=success,-1=fail
**************************************/
int applib_msg_list_append_one(const char * app_name, const msg_apps_t *msg, applib_msg_proc_t *scene)
{
    msg_list_t *cur=NULL;
    int ret=-1;
    int len=0;
    pthread_mutex_lock(&scene->MsgProcDataLock);
    cur = (msg_list_t*)malloc(sizeof(msg_list_t));
    if(cur==NULL)
    {
        APL_ERR("malloc error");
        ret=-1;
        goto err_exit;
    }
    memset(cur,0,sizeof(msg_list_t));
    memcpy(&cur->msg, msg, sizeof(msg_apps_t));
    cur->flag = 1;
    len = strlen(app_name)>sizeof(cur->dst)?sizeof(cur->dst):strlen(app_name);
    memcpy(cur->dst, app_name, len);
    list_add_tail(&cur->list, &scene->Msg_list.list);
    scene->msg_total++;
    scene->proc_num++;
    ret = 0;
err_exit:
    pthread_mutex_unlock(&scene->MsgProcDataLock);
    return ret;
}

static void *ApplibMsgProc(void *pdata)
{
    int ret=-1;
    msg_list_t *cur=NULL;
    msg_list_t *next=NULL;

    while (g_ApplibMsgProcThreadRun)
    {
        pthread_mutex_lock(&g_applibMsg.MsgProcLock);
        while(!g_applibMsg.MsgProc_start)
        {
            pthread_cond_wait(&g_applibMsg.MsgProcCondition, &g_applibMsg.MsgProcLock);
        }

        if(g_applibMsg.proc_num>0)
        {
            list_for_each_entry_safe(cur, next, &g_applibMsg.Msg_list.list, list)
            {
                if(cur->flag==1)
                {
                    ApplibPostCallbackMsg(cur->dst, &cur->msg);
                    applib_proc_messages(&cur->msg);
                    cur->flag = 0;
                    g_applibMsg.proc_num--;
                    if(g_applibMsg.proc_num<=0)
                    {
                        g_applibMsg.proc_num = 0;
                        break;
                    }
                }
                pthread_mutex_lock(&g_applibMsg.MsgProcDataLock);
                list_del(&cur->list);
                cur = NULL;
                pthread_mutex_unlock(&g_applibMsg.MsgProcDataLock);
            }//list_for_each_entry_safe
        }
        g_applibMsg.MsgProc_start=0;
        pthread_mutex_unlock(&g_applibMsg.MsgProcLock);
        pthread_testcancel();
        usleep(10000);
    }
    //printf("exit ApplibMsgProc\n");
    return NULL;
}

static int SSTAR_StartApplib(void)
{
    if(applib_open_cnt==0)
    {
        pthread_mutex_init(&g_ApplibParamMutex, NULL);
        pthread_mutex_init(&g_ApplibCallbackListMutex, NULL);
        INIT_LIST_HEAD(&g_ApplibCallbackListHead);

        pthread_mutex_init(&g_applibMsg.MsgProcLock, NULL);
        pthread_cond_init(&g_applibMsg.MsgProcCondition, NULL);
        pthread_mutex_init(&g_applibMsg.MsgProcDataLock, NULL);
        INIT_LIST_HEAD(&g_applibMsg.Msg_list.list);
        g_ApplibMsgProcThreadRun = 1;
        pthread_create(&g_applibMsg.MsgProc_tid, NULL, ApplibMsgProc, &g_applibMsg);
        if (!g_applibMsg.MsgProc_tid)
        {
            printf("create Applib thread failed\n");
            g_ApplibMsgProcThreadRun=0;
            return 0;
        }
    }
    applib_open_cnt++;
    return 0;
}

static void SSTAR_StopApplib()
{
    applib_open_cnt--;
    if(applib_open_cnt==0)
    {
        g_ApplibMsgProcThreadRun = 0;

        applib_free_msg_list_res(&g_applibMsg);
        if(g_applibMsg.MsgProc_tid)
        {
            //printf("ApplibMsgProc thread is exiting\n");
            pthread_cancel(g_applibMsg.MsgProc_tid);
            pthread_join(g_applibMsg.MsgProc_tid, NULL);
            g_applibMsg.MsgProc_tid = 0;
            //printf("ApplibMsgProc thread exit\n");
        }

        pthread_mutex_destroy(&g_ApplibCallbackListMutex);
        pthread_mutex_destroy(&g_ApplibParamMutex);

        pthread_mutex_destroy(&g_applibMsg.MsgProcLock);
        pthread_cond_destroy(&g_applibMsg.MsgProcCondition);
        pthread_mutex_destroy(&g_applibMsg.MsgProcDataLock);
    }

}

int SSTAR_RegisterApplibCallback(const char * app_name, ApplibCallback pfnCallback)
{
    ApplibCallbackListData_t *pstApplibCallbackData = NULL;
    int len=0;

    if (!pfnCallback||app_name==NULL)
        return -1;
    printf("applib register: %s\n", app_name);

    pstApplibCallbackData = (ApplibCallbackListData_t*)malloc(sizeof(ApplibCallbackListData_t));
    memset(pstApplibCallbackData, 0, sizeof(ApplibCallbackListData_t));
    pstApplibCallbackData->pfnCallback = pfnCallback;

    len = strlen(app_name)>sizeof(pstApplibCallbackData->dst)?sizeof(pstApplibCallbackData->dst):strlen(app_name);
    memcpy(pstApplibCallbackData->dst, app_name, len);

    pthread_mutex_lock(&g_ApplibCallbackListMutex);
    ApplibCallbackListData_t *pos = NULL;

    list_for_each_entry(pos, &g_ApplibCallbackListHead, list)
    {
        if(pos->pfnCallback == pfnCallback)
        {
            pthread_mutex_unlock(&g_ApplibCallbackListMutex);
            return 0;
        }
    }

    list_add_tail(&pstApplibCallbackData->list, &g_ApplibCallbackListHead);
    pthread_mutex_unlock(&g_ApplibCallbackListMutex);

    pthread_mutex_lock(&g_ApplibParamMutex);
    g_registerApplibChanged = 1;
    pthread_mutex_unlock(&g_ApplibParamMutex);
    return 0;
}

void SSTAR_UnRegisterApplibCallback(const char * app_name, ApplibCallback pfnCallback)
{
    ApplibCallbackListData_t *cur = NULL;
    ApplibCallbackListData_t *next = NULL;

    if (!pfnCallback||app_name==NULL)
            return;
    printf("applib unregister: %s\n", app_name);

    pthread_mutex_lock(&g_ApplibParamMutex);
    g_registerApplibChanged = 0;
    pthread_mutex_unlock(&g_ApplibParamMutex);

    pthread_mutex_lock(&g_ApplibCallbackListMutex);
    list_for_each_entry_safe(cur, next, &g_ApplibCallbackListHead, list)
    {
        if (cur->pfnCallback == pfnCallback)
        {
            list_del(&cur->list);
            free(cur);
        }
    }
    pthread_mutex_unlock(&g_ApplibCallbackListMutex);
}

int SSTAR_Applib_Init(void)
{
    SSTAR_StartApplib();
    return 0;
}

void SSTAR_Applib_Deinit()
{
    SSTAR_StopApplib();
}

/************************************************************
breif: app register to applib
param:
    app_name: app name
    pfnCallback: system messages process function
return:
    0=success, -1=failed
*************************************************************/
int SSTAR_RegisterApplib(const char * app_name, ApplibCallback pfnCallback)
{
    return SSTAR_RegisterApplibCallback(app_name, pfnCallback);
}

/************************************************************
breif: app unregister frome applib
param:
    app_name: app name
    pfnCallback: system messages process function
return:
    0=success, -1=failed
*************************************************************/
void SSTAR_UnRegisterApplib(const char * app_name, ApplibCallback pfnCallback)
{
    SSTAR_UnRegisterApplibCallback(app_name, pfnCallback);
}

/************************************************************
breif: Send a async msg to "app_name"
param:
    app_name: name of receiver
    msg:
return:
    0=success, -1=failed
*************************************************************/
int SSTAR_SendAsyncMsg(const char * app_name, msg_apps_t *msg)
{
    if(msg!=NULL)
    {
        applib_msg_list_append_one(app_name, msg, &g_applibMsg);
        applib_start_proc_msg(&g_applibMsg);
    }
    return 0;
}
