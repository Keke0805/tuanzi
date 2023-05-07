#include "checktimemsg.h"
checkTimeMsg *checkScene =NULL;

checkTimeMsg::checkTimeMsg()
{
    FILE *fp = NULL;
    struct stat buf;
    char *alarmBuff =NULL;
    int sizeAlarm =0;

    checkScene =this;
    fp = fopen(VA_ALARMLIST_PATH, "r");
    if(fp ==NULL)
    {
        LV_LOG_USER("%s open fail\n", VA_ALARMLIST_PATH);
        goto end;
    }
    memset(&buf, 0x00, sizeof(buf));
    stat(VA_ALARMLIST_PATH, &buf);
    if(!buf.st_size)
    {
        LV_LOG_USER("%s size = 0\n", VA_ALARMLIST_PATH);
        fclose(fp);
        fp =NULL;
    }
    sizeAlarm = buf.st_size;
    alarmBuff =(char *)malloc(sizeAlarm);
    if(alarmBuff ==NULL)
    {
        LV_LOG_USER("malloc %d fail\n", sizeAlarm);
        fclose(fp);
        fp =NULL;
        goto end;
    }
    if(fp != NULL)
    {
        fread(alarmBuff, 1, sizeAlarm, fp);
        fclose(fp);
        fp = NULL;
        cjson_alarmInfo(alarmBuff);
    }
    if(alarmBuff ==NULL)
    {
        free(alarmBuff);
        alarmBuff =NULL;
    }
end:
	SSTAR_RegisterApplib(APP_NAME_UI,funcallback);
    startTimer(1000, this);
}
checkTimeMsg::~checkTimeMsg(void)
{
    alarm_destory();
	SSTAR_UnRegisterApplib(APP_NAME_UI,funcallback);
}
void checkTimeMsg::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
	alarm_check_time();
}
void checkTimeMsg::funcallback(msg_apps_t *msg)
{
    switch(msg->type)
    {
        case UI_ALARM:
            if(msg->mode == VPLAY_STOP_CMD)
            {
                checkScene->ringSta =false;
            }
        break;
        default:
        break;
    }
}
void checkTimeMsg::cjson_alarmInfo(char*alarmBuff)
{
    cJSON *root = NULL;
    cJSON *item = NULL;
    cJSON *arrayItem = NULL;
    cJSON *child_item = NULL;
    alarm_info alarmList;
    int i=0,ArrayTotal =0;

    root = cJSON_Parse(alarmBuff);
    if(root == NULL)
    {
        return;
    }

    item = cJSON_GetObjectItem(root, "alarm_list");
    if(item !=NULL)
    {
        ArrayTotal = cJSON_GetArraySize(item);
        if(ArrayTotal >0)
        {
            for(i=0;i<ArrayTotal;i++)
            {
                memset(&alarmList,0,sizeof(alarm_info));
                memset(alarmList.name,0,sizeof(alarmList.name));
                alarmList.type =WDAY_EN;

                arrayItem = cJSON_GetArrayItem(item,i);
                if(arrayItem !=NULL)
                {
                    child_item = cJSON_GetObjectItem(arrayItem,"hours");
                    if(child_item != NULL)
                    {
                        alarmList.hours = child_item->valueint;
                    }
                    child_item = cJSON_GetObjectItem(arrayItem,"minute");
                    if(child_item != NULL)
                    {
                        alarmList.minute = child_item->valueint;
                    }
                    child_item = cJSON_GetObjectItem(arrayItem,"type");
                    if(child_item != NULL)
                    {
                        alarmList.type = child_item->valueint;
                    }
                    child_item = cJSON_GetObjectItem(arrayItem,"ring");
                    if(child_item != NULL)
                    {
                        alarmList.ring = child_item->valueint;
                    }
                    child_item = cJSON_GetObjectItem(arrayItem,"status");
                    if(child_item != NULL)
                    {
                        alarmList.status = child_item->valueint;
                    }
                    child_item = cJSON_GetObjectItem(arrayItem,"name");
                    if(child_item != NULL)
                    {
                        if(child_item->valuestring !=NULL)
                        {
                            sprintf(alarmList.name,"%s",child_item->valuestring);
                        }
                    }
                    alarm_add_list(&alarmList);
                }
            }
        }
    }
}

void checkTimeMsg::alarm_add_node(alarm_list_t *node)
{
    alarm_list_t *tmp_list;

    tmp_list = AlarmInfoList;
    if(AlarmInfoList == NULL)
    {
        AlarmInfoList = node;
        AlarmInfoList->next_list = NULL;
    }
    else
    {
        while(tmp_list->next_list != NULL)
        {
            tmp_list = tmp_list->next_list;
        }
        tmp_list->next_list = node;
        tmp_list->next_list->next_list = NULL;
    }
}
void checkTimeMsg::alarm_destory(void)
{
    alarm_list_t *tmp_list_prev;
    alarm_list_t *tmp_list_last;

    tmp_list_prev = AlarmInfoList;
    while(tmp_list_prev != NULL)
    {
        tmp_list_last = tmp_list_prev->next_list;
        free(tmp_list_prev);
        tmp_list_prev = tmp_list_last;
    }
    AlarmInfoList = NULL;
}
void checkTimeMsg::alarm_add_list(alarm_info *alarnInfo)
{
    alarm_list_t *tmp_list;

    tmp_list = (alarm_list_t*)malloc(sizeof(alarm_list_t));
    memset(tmp_list,0,sizeof(alarm_list_t));
    memset(&tmp_list->AlarmInfo,0,sizeof(alarm_info));
    memset(tmp_list->AlarmInfo.name,0,sizeof(tmp_list->AlarmInfo.name));

    tmp_list->AlarmInfo.hours = alarnInfo->hours;
    tmp_list->AlarmInfo.minute = alarnInfo->minute;
    tmp_list->AlarmInfo.type = alarnInfo->type;
    tmp_list->AlarmInfo.ring  = alarnInfo->ring;
    tmp_list->AlarmInfo.status  = alarnInfo->status;
    sprintf(tmp_list->AlarmInfo.name,"%s",alarnInfo->name);
    alarm_add_node(tmp_list);
	alarm_save_file();
}
void checkTimeMsg::alarm_check_time(void)
{
    SYSDateTime gettime;
    lvcpp_sys_datetime_t user_time;
    alarm_list_t *tmp_list;
    int cur_hours =8, cur_mintes =30,cur_week=0;
    int cur_year =2022,cur_month =1,cur_day =1;
	int curTime =0;

    if(AlarmInfoList ==NULL)
        return;

    tmp_list = AlarmInfoList;
    user_time = gettime.current_datetime();
    cur_year = user_time.year;
    cur_month = user_time.month;
    cur_day = user_time.day;
    cur_hours = user_time.hour;
    cur_mintes = user_time.minute;
    cur_week =(cur_day+1+2*cur_month+3*(cur_month+1)/5+cur_year+cur_year/4-cur_year/100+cur_year/400)%7;
	curTime =cur_year*100000000+cur_month*1000000+cur_day*10000+cur_hours*100+cur_mintes;
	while(tmp_list != NULL)
    {
        if(tmp_list->AlarmInfo.status)
        {
            if(tmp_list->AlarmInfo.type ==WDAY_EN)
            {
                if((tmp_list->AlarmInfo.hours == cur_hours)&&(tmp_list->AlarmInfo.minute == cur_mintes))
                {
                    ringSta =true;
                    tmp_list->AlarmInfo.status =0;
					if(curTime !=saveTime)
					{
						saveTime = curTime;
	                    msg_apps_t msg;
	                    memset(&msg,0,sizeof(msg));
	                    msg.type = UI_ALARM;
	                    msg.mode = VPLAY_PLAY_CMD;
						memset(msg.content,0,sizeof(msg.content));
						sprintf(msg.content,"%.2d%.2d",tmp_list->AlarmInfo.hours,tmp_list->AlarmInfo.minute);
						msg.csize =strlen(msg.content);
						SSTAR_SendAsyncMsg(APP_NAME_UI,&msg);
						alarm_save_file();
					}
                    return;
                }
            }
            else if((tmp_list->AlarmInfo.type&(1<<cur_week)))
            {
                if((tmp_list->AlarmInfo.hours == cur_hours)&&(tmp_list->AlarmInfo.minute == cur_mintes))
                {
                    if(!ringSta)
                    {
                    	if(curTime !=saveTime)
                    	{
                    		saveTime =curTime;
	                        ringSta =true;
	                        msg_apps_t msg;
	                        memset(&msg,0,sizeof(msg));
	                        msg.type = UI_ALARM;
	                        msg.mode = VPLAY_PLAY_CMD;
	                        SSTAR_SendAsyncMsg(APP_NAME_UI,&msg);
                    	}
                    }
                    return;
                }
            }
        }
        tmp_list = tmp_list->next_list;
    }
}
static bool check_curlist(alarm_info *CurAlarnInfo,alarm_info *alarnInfo)
{
    bool ret =true;
    if(CurAlarnInfo->hours != alarnInfo->hours)
    {
        ret =false;
    }
    if(CurAlarnInfo->minute != alarnInfo->minute)
    {
        ret =false;
    }
    if(CurAlarnInfo->type != alarnInfo->type)
    {
        ret =false;
    }
    if(CurAlarnInfo->ring != alarnInfo->ring)
    {
        ret =false;
    }
    if(CurAlarnInfo->status != alarnInfo->status)
    {
        ret =false;
    }
    if(strcmp(CurAlarnInfo->name, alarnInfo->name)!=0)
    {
        ret =false;
    }
    return ret;
}
static alarm_list_t *_del_alarm_head(alarm_list_t *head_list)
{
    alarm_list_t *tmp_list;

    if(head_list ==NULL)
    {
        return NULL;
    }
    tmp_list = head_list->next_list;
    free(head_list);
    if(tmp_list ==NULL)
    {
        return NULL;
    }
    head_list = tmp_list;
    return head_list;
}
void checkTimeMsg::alarm_rm_node(alarm_info *alarnInfo)
{
    alarm_list_t* tmp_list_prev;
    alarm_list_t* tmp_list_last;

    if(AlarmInfoList ==NULL)
        return;
    if(check_curlist(&AlarmInfoList->AlarmInfo,alarnInfo))
    {
        AlarmInfoList =_del_alarm_head(AlarmInfoList);
        return;
    }
    else
    {
        tmp_list_prev = AlarmInfoList;
        tmp_list_last = AlarmInfoList->next_list;
        while(tmp_list_last != NULL)
        {
            if(check_curlist(&tmp_list_prev->AlarmInfo,alarnInfo))
            {
                tmp_list_prev->next_list = tmp_list_last->next_list;
                free(tmp_list_last);
                return;
            }
            else
            {
                tmp_list_prev =tmp_list_last;
                tmp_list_last = tmp_list_last->next_list;
            }
        }
    }
}

void checkTimeMsg::alarm_change_status(alarm_info *alarnInfo,int status)
{
    alarm_list_t* tmp_list;

    if(AlarmInfoList ==NULL)
        return;
    tmp_list = AlarmInfoList;
    while(tmp_list != NULL)
    {
        if(check_curlist(&tmp_list->AlarmInfo,alarnInfo))
        {
            tmp_list->AlarmInfo.status =status;
			alarm_save_file();
            return;
        }
        tmp_list = tmp_list->next_list;
    }
}

void checkTimeMsg::alarm_save_file(void)
{
    FILE *fp = NULL;
    alarm_list_t* tmp_list;
    cJSON *root = NULL;
    cJSON *item = NULL;
    cJSON *arrayItem = NULL;
    char *text=NULL;
    int ret=0,sizeAlarm =0;

    if(AlarmInfoList ==NULL)
        return;

    root = cJSON_CreateObject();
    arrayItem = cJSON_CreateArray();
    cJSON_AddItemToObject(root, "alarm_list", arrayItem);
    tmp_list = AlarmInfoList;
    while(tmp_list != NULL)
    {
        item = cJSON_CreateObject();
        cJSON_AddItemToArray(arrayItem,item);
        cJSON_AddNumberToObject(item, "hours", tmp_list->AlarmInfo.hours);
        cJSON_AddNumberToObject(item, "minute", tmp_list->AlarmInfo.minute);
        cJSON_AddNumberToObject(item, "type", tmp_list->AlarmInfo.type);
        cJSON_AddNumberToObject(item, "ring", tmp_list->AlarmInfo.ring);
        cJSON_AddNumberToObject(item, "status", tmp_list->AlarmInfo.status);
        cJSON_AddStringToObject(item, "name", tmp_list->AlarmInfo.name);
        tmp_list = tmp_list->next_list;
    }
    text = cJSON_Print(root);

    if(root!=NULL)
    {
        cJSON_Delete(root);
        root =NULL;
    }
    fp = fopen(VA_ALARMLIST_PATH, "w+");
    if(fp ==NULL)
    {
        LV_LOG_USER("%s open fail\n", VA_ALARMLIST_PATH);
        goto end;
    }
    sizeAlarm = strlen(text);
    ret = fwrite(text, 1, sizeAlarm, fp);
end:
    if(fp !=NULL)
    {
        fsync(fileno(fp));
        fclose(fp);
    }
    if(text !=NULL)
    {
        free(text);
        text =NULL;
    }
}
