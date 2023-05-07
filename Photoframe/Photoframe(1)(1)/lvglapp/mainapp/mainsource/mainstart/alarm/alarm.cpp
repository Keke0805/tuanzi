#include  "../mainappstart.h"
#include "alarm.h"
#include  "lvgl/src/extra/lv_extra.h"
#include  "mainstart/include/ui_config.h"
#include  "mainstart/include/str_config.h"
#include  "lv_code/lv_drivers/indev/sunxi_key.h"
alarmScene* ALARMList =NULL;
static const void *SongName[4]={STR_PLATINUM,STR_ARGON,STR_CLASSIC,STR_HELIUM};

void alarmScene::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    HEAD_RETURN_PNG=(void*)parse_image_from_file(HEAD_RETURN_PNG_PATH);
    HEAD_RETURN_SEL_PNG=(void*)parse_image_from_file(HEAD_RETURN_SEL_PNG_PATH);
    HEAD_ICON_ALARM_PNG=(void*)parse_image_from_file(HEAD_ICON_ALARM_PNG_PATH);
    LISTBG_PNG=(void*)parse_image_from_file(LISTBG_PNG_PATH);
    ALARM_SCENE_PNG=(void*)parse_image_from_file(ALARM_SCENE_PNG_PATH);
    ALARM_HOURS_PNG=(void*)parse_image_from_file(ALARM_HOURS_PNG_PATH);
    ALARM_MINUTE_PNG=(void*)parse_image_from_file(ALARM_MINUTE_PNG_PATH);
    ALARM_SECOND_PNG=(void*)parse_image_from_file(ALARM_SECOND_PNG_PATH);
    ALARM_DOT_PNG=(void*)parse_image_from_file(ALARM_DOT_PNG_PATH);       
#endif
}

void alarmScene::ui_image_free(void)
{
#ifdef IMAGE_DECODE	
    free_image(HEAD_RETURN_PNG);
    free_image(HEAD_RETURN_SEL_PNG);
    free_image(HEAD_ICON_ALARM_PNG);
    free_image(LISTBG_PNG);
    free_image(ALARM_SCENE_PNG);
    free_image(ALARM_HOURS_PNG);
    free_image(ALARM_MINUTE_PNG);
    free_image(ALARM_SECOND_PNG);
    free_image(ALARM_DOT_PNG);	
#endif
}
void alarmScene::selalarm_add_node(alarm_info_t *node)
{
    alarm_info_t *tmp_list;

    tmp_list = AlarmInfo;

    if(AlarmInfo == NULL)
    {
        AlarmInfo = node;
        AlarmInfo->next_list = NULL;
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
	alarm_sort();
}
void alarmScene::alarm_sort(void)
{
	alarm_info_t* tmp_list;
	alarm_info infoAlarm_prev;
	alarm_info infoAlarm_next;
	int numTotal = get_alarm_total();
	int i=0,j=0,time_prev=0,time_next=0;
	
	if(AlarmInfo ==NULL)
		return;
	
    for(i=0;i<(numTotal-1);i++)
    {
		for(j=i+1;j<numTotal;j++)
		{
			memset(&infoAlarm_prev,0,(sizeof(alarm_info)));
			memset(&infoAlarm_next,0,(sizeof(alarm_info)));
			get_alarm_info(i,&infoAlarm_prev);
			time_prev =(int)(infoAlarm_prev.hours*10000 + infoAlarm_prev.minute*100 + infoAlarm_prev.second);
			get_alarm_info(j,&infoAlarm_next);
			time_next =(int)(infoAlarm_next.hours*10000 + infoAlarm_next.minute*100 + infoAlarm_next.second);
			if(time_next < time_prev)
			{
				set_alarm_info(i,&infoAlarm_next);
				set_alarm_info(j,&infoAlarm_prev);
			}
		}
	}
}
int alarmScene::get_alarm_total(void)
{
	alarm_info_t* tmp_list;
    int numTotal =0;

	if(AlarmInfo ==NULL)
		return 0;
    tmp_list = AlarmInfo;

    while(tmp_list != NULL)
    {
        numTotal ++;
        tmp_list = tmp_list->next_list;
    }
    return numTotal;
}
int alarmScene::get_alarm_info(int index,alarm_info *infoAlarm)
{
	alarm_info_t* tmp_list;
	
	if(AlarmInfo ==NULL)
		return -1;
    tmp_list = AlarmInfo;
    while(tmp_list != NULL)
    {
    	if(tmp_list->index ==index)
    	{	
			infoAlarm->hours = tmp_list->AlarmInfo.hours;
			infoAlarm->minute = tmp_list->AlarmInfo.minute;
			infoAlarm->second = tmp_list->AlarmInfo.second;
			infoAlarm->type = tmp_list->AlarmInfo.type;
			infoAlarm->ring  = tmp_list->AlarmInfo.ring;
			infoAlarm->status  = tmp_list->AlarmInfo.status;
			sprintf(infoAlarm->name,"%s",tmp_list->AlarmInfo.name);
			return 0;
		}
        tmp_list = tmp_list->next_list;
    }
	return -1;
}
void alarmScene::set_alarm_info(int index,alarm_info *infoAlarm)
{
	alarm_info_t* tmp_list;
	
	if(AlarmInfo ==NULL)
		return;

    tmp_list = AlarmInfo;
    while(tmp_list != NULL)
    {
    	if(tmp_list->index ==index)
    	{	
    		CheckAlarmList->alarm_rm_node(&tmp_list->AlarmInfo);
            CheckAlarmList->alarm_add_list(infoAlarm);
			tmp_list->AlarmInfo.hours = infoAlarm->hours;
			tmp_list->AlarmInfo.minute = infoAlarm->minute;
			tmp_list->AlarmInfo.second = infoAlarm->second;
			tmp_list->AlarmInfo.type = infoAlarm->type;
			tmp_list->AlarmInfo.ring  = infoAlarm->ring;
			tmp_list->AlarmInfo.status  = infoAlarm->status;
			memset(tmp_list->AlarmInfo.name,0,sizeof(tmp_list->AlarmInfo.name));
			sprintf(tmp_list->AlarmInfo.name,"%s",infoAlarm->name);
			return;
		}
        tmp_list = tmp_list->next_list;
    }
}
void alarmScene::set_alarm_CurStatus(int index,int status)
{
    alarm_info_t* tmp_list;

    if(AlarmInfo ==NULL)
        return;

    tmp_list = AlarmInfo;
    while(tmp_list != NULL)
    {
        if(tmp_list->index ==index)
        {
        	CheckAlarmList->alarm_change_status(&tmp_list->AlarmInfo,status);
            tmp_list->AlarmInfo.status  = status;
			return;
        }
        tmp_list = tmp_list->next_list;
    }
}
int alarmScene::set_alarm_off_CurStatus(int hours,int minutes,int status)
{
    alarm_info_t* tmp_list;

    if(AlarmInfo ==NULL)
        return -1;

    tmp_list = AlarmInfo;
    while(tmp_list != NULL)
    {
        if((tmp_list->AlarmInfo.type==WDAY_EN)&&(tmp_list->AlarmInfo.hours==hours)&&(tmp_list->AlarmInfo.minute==minutes))
        {
        	CheckAlarmList->alarm_change_status(&tmp_list->AlarmInfo,status);
            tmp_list->AlarmInfo.status  = status;
			return tmp_list->index;
        }
        tmp_list = tmp_list->next_list;
    }
	return -1;
}
int alarmScene::get_alarm_CurStatus(int index)
{
    alarm_info_t* tmp_list;

    if(AlarmInfo ==NULL)
        return 0;

    tmp_list = AlarmInfo;
    while(tmp_list != NULL)
    {
        if(tmp_list->index ==index)
        {
            return tmp_list->AlarmInfo.status;
        }
        tmp_list = tmp_list->next_list;
    }
    return 0;
}
bool alarmScene::check_alarm_Cur(alarm_info *infoAlarm)
{
    alarm_info_t* tmp_list;

    if(AlarmInfo ==NULL)
        return true;

    tmp_list = AlarmInfo;
    while(tmp_list != NULL)
    {
        if((tmp_list->AlarmInfo.hours ==infoAlarm->hours)&&(tmp_list->AlarmInfo.minute ==infoAlarm->minute)&&(tmp_list->AlarmInfo.type ==infoAlarm->type))
        {
            if(tmp_list->AlarmInfo.status !=infoAlarm->status)
            {
                tmp_list->AlarmInfo.status =infoAlarm->status;
            }
            if(strcmp(tmp_list->AlarmInfo.name,infoAlarm->name)!=0)
            {
                strcpy(tmp_list->AlarmInfo.name,infoAlarm->name);
            }
            return false;
        }
        tmp_list = tmp_list->next_list;
    }
    return true;
}
static alarm_info_t *_del_alarm_head(alarm_info_t *head_list)
{
	alarm_info_t *tmp_list;
	
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
void alarmScene::del_alarm_CurStatus(int index)
{
	alarm_info_t* tmp_list;
    alarm_info_t* tmp_list_prev;
	alarm_info_t* tmp_list_last;
	int numIndex=0;

    if(AlarmInfo ==NULL)
        return;

	if(AlarmInfo->index == index)
	{
		AlarmInfo =_del_alarm_head(AlarmInfo);
		return;
	}
    else
    {
        tmp_list_prev = AlarmInfo;
		tmp_list_last = AlarmInfo->next_list;
		while(tmp_list_last != NULL)
		{
			if(tmp_list_last->index==index)
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
	tmp_list = AlarmInfo;
    while(tmp_list != NULL)
    {
    	tmp_list->index =numIndex;
        tmp_list = tmp_list->next_list;
		numIndex ++;
    }
}
void alarmScene::selalarm_destory(void)
{
	alarm_info_t *tmp_list_prev;
    alarm_info_t *tmp_list_last;

    tmp_list_prev = AlarmInfo;
    while(tmp_list_prev != NULL)
    {
        tmp_list_last = tmp_list_prev->next_list;
        free(tmp_list_prev);
        tmp_list_prev = tmp_list_last;
    }
	alarnNum =0;
	alarmIndex =0;
	alarmListIndex =0;
    AlarmInfo = NULL;
}
void alarmScene::alarm_add_info(alarm_info *alarnInfo)
{
	alarm_info_t *tmp_list;

	if(!check_alarm_Cur(alarnInfo))
        return;
	
	tmp_list = (alarm_info_t*)malloc(sizeof(alarm_info_t));
	memset(tmp_list,0,sizeof(alarm_info_t));
	tmp_list->index =alarmListIndex;
	tmp_list->AlarmInfo.hours = alarnInfo->hours;
	tmp_list->AlarmInfo.minute = alarnInfo->minute;
	tmp_list->AlarmInfo.second = alarnInfo->second;
	tmp_list->AlarmInfo.type = alarnInfo->type;
	tmp_list->AlarmInfo.ring  = alarnInfo->ring;
	tmp_list->AlarmInfo.status  = alarnInfo->status;
	sprintf(tmp_list->AlarmInfo.name,"%s",alarnInfo->name);
	selalarm_add_node(tmp_list);
	alarmListIndex ++;
}
alarmScene::alarmScene(lv_obj_t* parent,checkTimeMsg* alarmList)
{
    ui_image_decode();
    frame = new LvcppScreen(parent);
    frame->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    frame->set_main_bg_color(lv_color_black(),LV_OPA_0);
    frame->set_main_bg_img_src(LISTBG_PNG);
    mainscreen = frame->myobj;
	CheckAlarmList = alarmList;
	ALARMList =this;
	SSTAR_RegisterApplib(APP_NAME_UI,funcallback);
}
alarmScene::~alarmScene(void)
{
    StartTimerShow =false;
	delete_Alarminfo();
	delete_Alarminfo_Bell();
	delete_Alarminfo_Label();
	delete_Alarminfo_Time();
	alarm_setlist_del();
	alarmScene_head_dele();
    alarmScene_sence_delete();
	selalarm_destory();
	SSTAR_UnRegisterApplib(APP_NAME_UI,funcallback);
    if(frame !=NULL)
    {
        delete frame;
        frame =NULL;
        lv_obj_clear_flag(lv_scr_act(), LV_OBJ_FLAG_CLICKABLE);
    }
    ui_image_free();
}
void alarmScene::funcallback(msg_apps_t *msg)
{
	char buff[8]={0};
	int index =0;
	int hours =0;
	int minutes =0;

    switch(msg->type)
    {
    	case UI_ALARM:
			if(msg->mode ==VPLAY_PLAY_CMD)
			{
				if(msg->csize >0)
				{
					memcpy(buff,msg->content,4);
					hours =(int)(atoi(buff)/100);
					minutes =(int)(atoi(buff)%100);
					index=ALARMList->set_alarm_off_CurStatus(hours,minutes,0);
					if(index >=0)
					{
						if((ALARMList->alarm_list.item[index]!=NULL)&&(ALARMList->alarm_list.item[index]->IconClose!=NULL))
						{
							ALARMList->alarm_list.item[index]->IconClose->set_main_bg_color(lv_color_hex(0x5c5c5c),LV_OPA_100);
            				ALARMList->alarm_list.item[index]->StatusClose->align(LV_ALIGN_LEFT_MID, 0, 0);
						}
					}
				}
			}
			break;
        default:
        break;
    }
}
int alarmScene::init_parament(void)
{
	read_int_type_param(PUBLIC_SCENE, TIMETYPE, (int *)&timeType);
	get_all_alarmList();
    alarmScene_head_creat();
    alarmScene_sence_creat();
	alarm_list_creat();
    alarmSceneTimer = startTimer(300, this);
    StartTimerShow =true;
    return 0;
}

void alarmScene::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    if(StartTimerShow !=true)
        return;
    SYSDateTime gettime;
    user_time = gettime.current_datetime();
    if(plateImage!=NULL)
    {
        alarmScene_sence_draw();
    }
}

void alarmScene::alarmScene_head_creat(void)
{
    buttonReturn = new LvcppButton(mainscreen);
    buttonReturn->set_size(66,66);
    buttonReturn->align(LV_ALIGN_TOP_LEFT,30,8);
    buttonReturn->set_main_bg_opa(LV_OPA_0);
    buttonReturn->set_main_radius(0);
    buttonReturn->set_main_pad_all(0);
    buttonReturn->set_main_border_width(0);
    buttonReturn->set_main_bg_img_src(HEAD_RETURN_PNG);
    buttonReturn->add_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
    buttonReturn->add_event_cb(head_event_handler,LV_EVENT_PRESSED,this);
    buttonReturn->add_event_cb(head_event_handler,LV_EVENT_RELEASED,this);

    alarmIcon = new LvcppButton(mainscreen);
    alarmIcon->set_size(66,66);
    alarmIcon->align(LV_ALIGN_TOP_LEFT,114,8);
    alarmIcon->set_main_bg_opa(LV_OPA_0);
    alarmIcon->set_main_radius(0);
    alarmIcon->set_main_pad_all(0);
    alarmIcon->set_main_border_width(0);
    alarmIcon->set_main_bg_img_src(HEAD_ICON_ALARM_PNG);
}

void alarmScene::alarmScene_head_dele(void)
{
    if(buttonReturn != NULL)
    {
        delete buttonReturn;
        buttonReturn =NULL;
    }
    if(alarmIcon != NULL)
    {
        delete alarmIcon;
        alarmIcon =NULL;
    }
}

void alarmScene::head_event_handler(lv_event_t *event)
{
    alarmScene* opt = (alarmScene*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

	if((opt->buttonReturn !=NULL)&&(target==opt->buttonReturn->myobj))
	{
		if(event->code== LV_EVENT_PRESSED)
        {
            opt->buttonReturn->set_main_bg_img_src(opt->HEAD_RETURN_SEL_PNG);
        }
        else
        {
            opt->StartTimerShow =false;
			opt->pause(opt->alarmSceneTimer);
    		MainAPPStart::alarmScenemain_destory();
			return;
        }
	}
	else if((opt->editIcon !=NULL)&&(target==opt->editIcon->myobj))
	{
		if(event->code== LV_EVENT_RELEASED)
        {
            if(opt->editShow ==true)
            {
                opt->editIcon->add_txt(STR_EDIT);
                opt->editShow =false;
                opt->alarm_list_show(true);
            }
            else
            {
                opt->editIcon->add_txt(STR_CANCEL);
                opt->editShow =true;
                opt->alarm_list_show(false);
            }
        }
	}
	else if((opt->addIcon !=NULL)&&(target==opt->addIcon->myobj))
	{
		if(event->code== LV_EVENT_RELEASED)
        {
        	opt->editShow =false;
		    opt->editIcon->show(false);
		    opt->addIcon->show(false);
			opt->infoAlarmCur.hours = opt->user_time.hour;
			opt->infoAlarmCur.minute = opt->user_time.minute;
			opt->infoAlarmCur.second = opt->user_time.second;
			opt->infoAlarmCur.type = WDAY_EN;
			opt->infoAlarmCur.ring =0;
			opt->infoAlarmCur.status =1;
			strcpy(opt->infoAlarmCur.name,STR_ALARM);
			opt->get_dayType_str(opt->infoAlarmCur.type,opt->reData);
			sprintf(opt->tiData,"%.2d:%.2d",opt->infoAlarmCur.hours,opt->infoAlarmCur.minute);
			opt->alarm_setlist_creat();
		    opt->cancelIcon->show(true);
		    opt->okIcon->show(true);
        }
	}
	else if((opt->okIcon !=NULL)&&(target==opt->okIcon->myobj))
	{
		if(event->code== LV_EVENT_RELEASED)
        {
        	LV_LOG_USER("!!!!!!!!!!!!!!!!!!!");
        	if(opt->editShow ==true)
            {
                opt->set_alarm_info(opt->alarmIndex,&opt->infoAlarmCur);
				LV_LOG_USER("!!!!!!!!!!!!!!!!!!!");
                opt->alarm_sort();
                opt->editShow =false;
            }
            else
            {
                opt->alarm_add_info(&opt->infoAlarmCur);
				LV_LOG_USER("!!!!!!!!!!!!!!!!!!!");
				opt->CheckAlarmList->alarm_add_list(&opt->infoAlarmCur);
            }
			LV_LOG_USER("!!!!!!!!!!!!!!!!!!!");
			opt->alarm_setlist_del();
			LV_LOG_USER("!!!!!!!!!!!!!!!!!!!");
        	opt->cancelIcon->show(false);
		    opt->okIcon->show(false);
			opt->alarm_list_delete();
			LV_LOG_USER("!!!!!!!!!!!!!!!!!!!");
			usleep(2000);
		    opt->alarm_list_creat();
			LV_LOG_USER("!!!!!!!!!!!!!!!!!!!");
		    opt->editIcon->show(true);
		    opt->addIcon->show(true);
        }
	}
	else if((opt->cancelIcon !=NULL)&&(target==opt->cancelIcon->myobj))
	{
		if(event->code== LV_EVENT_RELEASED)
        {
        	if(opt->mainList !=NULL)
            {
                opt->mainList->show(true);
                if(opt->editShow ==true)
                    opt->alarm_list_show(false);
                else
                    opt->alarm_list_show(true);
            }
        	opt->cancelIcon->show(false);
		    opt->okIcon->show(false);
			opt->alarm_setlist_del();
		    opt->editIcon->show(true);
		    opt->addIcon->show(true);
        }
	}
	else if((opt->repeatLabel !=NULL)&&(target==opt->repeatLabel->myobj))
    {
        if(event->code== LV_EVENT_RELEASED)
        {
            opt->alarm_day_info_creat();
        }
    }
    else if((opt->ringLabel !=NULL)&&(target==opt->ringLabel->myobj))
    {
        if(event->code== LV_EVENT_RELEASED)
        {
            opt->alarm_bell_info_creat();
        }
    }
    else if((opt->labelLabel !=NULL)&&(target==opt->labelLabel->myobj))
    {
        if(event->code== LV_EVENT_RELEASED)
        {
           opt->alarm_label_info_creat();
        }
    }
    else if((opt->timeLabel !=NULL)&&(target==opt->timeLabel->myobj))
    {
        if(event->code== LV_EVENT_RELEASED)
        {
            opt->alarm_time_info_creat();
        }
    }
}
void alarmScene::alarm_confirm_event_handler(lv_event_t *event)
{
    alarmScene* opt = (alarmScene*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
	int curTime =0;
	
	if((opt->alarmInfo !=NULL)&&(opt->alarmInfo->confirm !=NULL)&&(target==opt->alarmInfo->confirm->myobj))
	{
		opt->infoAlarmCur.type = opt->alarmInfo->get_info();
		memset(opt->reData,0,sizeof(opt->reData));
		opt->get_dayType_str(opt->infoAlarmCur.type,opt->reData);
		opt->delete_Alarminfo();
		if(opt->repeatData !=NULL)
			opt->repeatData->set_txt(opt->reData);
	}
	else if((opt->alarmInfo !=NULL)&&(opt->alarmInfo->cancel !=NULL)&&(target==opt->alarmInfo->cancel->myobj))
	{
		opt->delete_Alarminfo();
	}
    else if((opt->alarm_info_bell !=NULL)&&(opt->alarm_info_bell->confirm !=NULL)&&(target==opt->alarm_info_bell->confirm->myobj))
	{
		opt->infoAlarmCur.ring = opt->alarm_info_bell->get_info();
    	opt->delete_Alarminfo_Bell();
		if(opt->ringData !=NULL)
			opt->ringData->set_txt((char*)SongName[opt->infoAlarmCur.ring]);
	}
	else if((opt->alarm_info_bell !=NULL)&&(opt->alarm_info_bell->cancel !=NULL)&&(target==opt->alarm_info_bell->cancel->myobj))
	{
    	opt->delete_Alarminfo_Bell();
	}
	else if((opt->alarm_info_label !=NULL)&&(opt->alarm_info_label->confirm !=NULL)&&(target==opt->alarm_info_label->confirm->myobj))
	{
		memset(opt->infoAlarmCur.name,0,sizeof(opt->infoAlarmCur.name));
		sprintf(opt->infoAlarmCur.name,"%s",opt->alarm_info_label->textarea->get_text());
    	opt->delete_Alarminfo_Label();
		if(opt->labelData!=NULL)
		{
			opt->labelData->set_txt(opt->infoAlarmCur.name);
		}
	}
	else if((opt->alarm_info_label !=NULL)&&(opt->alarm_info_label->cancel !=NULL)&&(target==opt->alarm_info_label->cancel->myobj))
	{
    	opt->delete_Alarminfo_Label();
	}
	else if((opt->alarm_info_time !=NULL)&&(opt->alarm_info_time->confirm !=NULL)&&(target==opt->alarm_info_time->confirm->myobj))
	{
		curTime = opt->alarm_info_time->get_info();
		opt->infoAlarmCur.hours = curTime/100;
		opt->infoAlarmCur.minute = curTime%100;
		opt->infoAlarmCur.second = 0;
		LV_LOG_USER("@@@@@@@@@@@@@@@@@");
    	opt->delete_Alarminfo_Time();
		LV_LOG_USER("@@@@@@@@@@@@@@@@@");
		if(opt->timeData!=NULL)
		{
			memset(opt->tiData,0,sizeof(opt->tiData));
			sprintf(opt->tiData,"%.2d:%.2d",opt->infoAlarmCur.hours,opt->infoAlarmCur.minute);
			LV_LOG_USER("@@@@@@@@@@@@@@@@@");
			opt->timeData->set_txt(opt->tiData);
			LV_LOG_USER("@@@@@@@@@@@@@@@@@");
		}
	}
	else if((opt->alarm_info_time !=NULL)&&(opt->alarm_info_time->cancel !=NULL)&&(target==opt->alarm_info_time->cancel->myobj))
	{
    	opt->delete_Alarminfo_Time();
	}
}

void alarmScene::delete_Alarminfo(void)
{
	if(alarmInfo != NULL)
    {
         delete alarmInfo;
        alarmInfo = NULL;
    }
}
void alarmScene::delete_Alarminfo_Bell(void)
{
	if(alarm_info_bell != NULL)
    {
         delete alarm_info_bell;
        alarm_info_bell = NULL;
    }
}
void alarmScene::delete_Alarminfo_Label(void)
{
	if(alarm_info_label != NULL)
    {
         delete alarm_info_label;
        alarm_info_label = NULL;
    }
}

void alarmScene::delete_Alarminfo_Time(void)
{
	if(alarm_info_time != NULL)
    {
         delete alarm_info_time;
        alarm_info_time = NULL;
    }
}

void alarmScene::alarm_day_info_creat(void)
{
    alarmInfo  = new Alarminfo(infoAlarmCur.type,mainscreen);
    alarmInfo->cancel->add_event_cb(alarm_confirm_event_handler,LV_EVENT_RELEASED,this);
	alarmInfo->confirm->add_event_cb(alarm_confirm_event_handler,LV_EVENT_RELEASED,this);
}

void alarmScene::alarm_bell_info_creat(void)
{
    alarm_info_bell  = new Alarminfo_Bell(infoAlarmCur.ring,mainscreen);
	alarm_info_bell->cancel->add_event_cb(alarm_confirm_event_handler,LV_EVENT_RELEASED,this);
    alarm_info_bell->confirm->add_event_cb(alarm_confirm_event_handler,LV_EVENT_RELEASED,this);
}

void alarmScene::alarm_label_info_creat(void)
{
    alarm_info_label  = new Alarminfo_Label(mainscreen);
	alarm_info_label->cancel->add_event_cb(alarm_confirm_event_handler,LV_EVENT_RELEASED,this);
    alarm_info_label->confirm->add_event_cb(alarm_confirm_event_handler,LV_EVENT_RELEASED,this);
}

void alarmScene::alarm_time_info_creat(void)
{
	if(alarm_info_time ==NULL)
	{
	    alarm_info_time  = new Alarminfo_Time(infoAlarmCur.hours,infoAlarmCur.minute,timeType,mainscreen);
		alarm_info_time->cancel->add_event_cb(alarm_confirm_event_handler,LV_EVENT_RELEASED,this);
	    alarm_info_time->confirm->add_event_cb(alarm_confirm_event_handler,LV_EVENT_RELEASED,this);
	}
}

void alarmScene::alarmScene_sence_creat(void)
{
    SYSDateTime gettime;
    user_time = gettime.current_datetime();
    memset(&alarm_list, 0 , sizeof(alarm_list_item_info));

    plateImage = new LvcppImage(mainscreen);
    plateImage->set_size(340,340);
    plateImage->set_src(ALARM_SCENE_PNG);
    plateImage->align(LV_ALIGN_TOP_LEFT, 125, 270);

    hoursImage = new LvcppImage(plateImage->myobj);
    hoursImage->set_src(ALARM_HOURS_PNG);
    hoursImage->align(LV_ALIGN_CENTER, 0, 0);
    uint16_t h = user_time.hour * 300 + user_time.minute / 12 % 12 * 60;
    hoursImage->set_angle(h);

    minuteImage = new LvcppImage(plateImage->myobj);
    minuteImage->set_src(ALARM_MINUTE_PNG);
    minuteImage->align(LV_ALIGN_CENTER, 0, 0);
    minuteImage->set_angle(user_time.minute*60);

    secondImage = new LvcppImage(plateImage->myobj);
    secondImage->set_src(ALARM_SECOND_PNG);
    secondImage->align(LV_ALIGN_CENTER, 0, 0);
    secondImage->set_angle(user_time.second*60);

    dotImage = new LvcppImage(plateImage->myobj);
    dotImage->set_src(ALARM_DOT_PNG);
    dotImage->align(LV_ALIGN_CENTER, 0, 0);

    alarmListFrame = new LvcppScreen(mainscreen);
    alarmListFrame->set_size(590,620);
    alarmListFrame->align(LV_ALIGN_TOP_LEFT, 640, 130);
    alarmListFrame->set_main_bg_color(lv_color_hex(0x00a7d4),LV_OPA_100);
    alarmListFrame->set_main_radius(10);

    editIcon = new LvcppButton(mainscreen);
    editIcon->set_size(170,70);
    editIcon->align(LV_ALIGN_TOP_LEFT,730,658);
    editIcon->set_main_bg_color(lv_color_hex(0x6cff),LV_OPA_100);
    editIcon->set_main_radius(50);
    editIcon->set_main_pad_all(0);
    editIcon->set_main_border_width(0);
    editIcon->txt_size(160, 40, LV_LABEL_LONG_WRAP);
    editIcon->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    editIcon->txt_center();
	editIcon->add_txt(STR_EDIT);
    editIcon->add_event_cb(head_event_handler,LV_EVENT_RELEASED,this);

    addIcon = new LvcppButton(mainscreen);
    addIcon->set_size(170,70);
    addIcon->align(LV_ALIGN_TOP_LEFT,992,658);
    addIcon->set_main_bg_color(lv_color_hex(0x6cff),LV_OPA_100);
    addIcon->set_main_radius(50);
    addIcon->set_main_pad_all(0);
    addIcon->set_main_border_width(0);
    addIcon->txt_size(160, 40, LV_LABEL_LONG_WRAP);
    addIcon->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    addIcon->txt_center();
    addIcon->add_txt(STR_ADD);
    addIcon->add_event_cb(head_event_handler,LV_EVENT_RELEASED,this);

    cancelIcon = new LvcppButton(mainscreen);
    cancelIcon->set_size(170,70);
    cancelIcon->align(LV_ALIGN_TOP_LEFT,730,658);
    cancelIcon->set_main_bg_color(lv_color_hex(0xff1818),LV_OPA_100);
    cancelIcon->set_main_radius(50);
    cancelIcon->set_main_pad_all(0);
    cancelIcon->set_main_border_width(0);
    cancelIcon->set_userdata((void*)HEAD_ICON_BALCK);
    cancelIcon->txt_size(160, 40, LV_LABEL_LONG_WRAP);
    cancelIcon->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    cancelIcon->txt_center();
    cancelIcon->add_txt(STR_CANCEL);
    cancelIcon->add_event_cb(head_event_handler,LV_EVENT_RELEASED,this);
    cancelIcon->show(false);

    okIcon = new LvcppButton(mainscreen);
    okIcon->set_size(170,70);
    okIcon->align(LV_ALIGN_TOP_LEFT,992,658);
    okIcon->set_main_bg_color(lv_color_hex(0x6cff),LV_OPA_100);
    okIcon->set_main_radius(50);
    okIcon->set_main_pad_all(0);
    okIcon->set_main_border_width(0);
    okIcon->txt_size(160, 40, LV_LABEL_LONG_WRAP);
    okIcon->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    okIcon->txt_center();
    okIcon->add_txt(STR_OK);
    okIcon->add_event_cb(head_event_handler,LV_EVENT_RELEASED,this);
    okIcon->show(false);
}

void alarmScene::alarm_list_creat(void)
{
	memset(&alarm_list, 0 , sizeof(alarm_list_item_info));
	alarnNum =0;
	alarnNum = get_alarm_total();
	LV_LOG_USER("alarnNum:%d",alarnNum);
   	if(alarnNum <=0)
		return;
	
    mainList = new LvcppList(alarmListFrame->myobj);
    mainList->set_size(590,500);
    mainList->align(LV_ALIGN_TOP_LEFT,0,0);
    mainList->set_main_bg_color(lv_color_hex(0x00a7d4),LV_OPA_100);
    mainList->set_flex_flow(LV_FLEX_FLOW_COLUMN);
    mainList->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    mainList->set_main_pad_all(1);
    mainList->set_main_pad_row(1);
    mainList->set_main_pad_column(0);
    mainList->set_main_border_width(0);
    mainList->set_main_radius(10);
    add_alarm_list_item();
}
void alarmScene::alarm_list_show(bool status)
{
    int i=0;

    if(mainList ==NULL)
        return;
    if(status)
    {
        for(i=0;i < alarm_list.count;i++)
        {
            if(alarm_list.item[i]->IconSet !=NULL)
                alarm_list.item[i]->IconSet->show(false);
            if(alarm_list.item[i]->IconDel !=NULL)
                alarm_list.item[i]->IconDel->show(false);
            if(alarm_list.item[i]->IconClose !=NULL)
                alarm_list.item[i]->IconClose->show(true);
        }
    }
    else
    {
        for(i=0;i < alarm_list.count;i++)
        {
            if(alarm_list.item[i]->IconSet !=NULL)
                alarm_list.item[i]->IconSet->show(true);
            if(alarm_list.item[i]->IconDel !=NULL)
                alarm_list.item[i]->IconDel->show(true);
            if(alarm_list.item[i]->IconClose !=NULL)
                alarm_list.item[i]->IconClose->show(false);
        }
    }
}

void alarmScene::alarm_list_delete(void)
{
    for(int i=alarm_list.count;i > 0;i--)
    {
    	if(alarm_list.item[i-1] !=NULL)
    	{
        	delete alarm_list.item[i-1];
			alarm_list.item[i-1] =NULL;
    	}
        alarm_list.count--;
    }
    if(mainList != NULL)
    {
        delete mainList;
        mainList =NULL;
    }
}

void alarmScene::add_alarm_list_item(void)
{
    char timeBuff[10]={0};
    char reData[64]={0};

    for(int i=alarm_list.count;i < alarnNum;i++)
    {
        memset(timeBuff,0,sizeof(timeBuff));
        memset(reData,0,sizeof(reData));
        get_alarm_info(i,&infoAlarmCur);
        get_dayType_str(infoAlarmCur.type,reData);
        sprintf(timeBuff,"%.2d:%.2d",infoAlarmCur.hours,infoAlarmCur.minute);
        alarm_list.item[i] = new Alarmlist(mainList->myobj);
        alarm_list.item[i]->TimeStr->set_txt(timeBuff);
        alarm_list.item[i]->IconType->set_txt(reData);
        alarm_list.item[i]->IconName->set_txt(infoAlarmCur.name);
        if(infoAlarmCur.status)
        {
            alarm_list.item[i]->IconClose->set_main_bg_color(lv_color_hex(0x00ff00),LV_OPA_100);
            alarm_list.item[i]->StatusClose->align(LV_ALIGN_RIGHT_MID, 0, 0);
        }
        else
        {
            alarm_list.item[i]->IconClose->set_main_bg_color(lv_color_hex(0x5c5c5c),LV_OPA_100);
            alarm_list.item[i]->StatusClose->align(LV_ALIGN_LEFT_MID, 0, 0);
        }
        alarm_list.item[i]->IconSet->set_userdata((void*)i);
        alarm_list.item[i]->IconSet->add_event_cb(alarm_list_event_handler,LV_EVENT_RELEASED,this);
        alarm_list.item[i]->IconDel->set_userdata((void*)i);
        alarm_list.item[i]->IconDel->add_event_cb(alarm_list_event_handler,LV_EVENT_RELEASED,this);
        alarm_list.item[i]->IconClose->set_userdata((void*)i);
        alarm_list.item[i]->IconClose->add_event_cb(alarm_list_event_handler,LV_EVENT_CLICKED,this);
        alarm_list.count++;
    }
}

void alarmScene::alarm_list_event_handler(lv_event_t *event)
{
    alarmScene* opt = (alarmScene*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    lv_obj_t* cont = lv_event_get_current_target(event);
    int sel_selete = (uintptr_t)target->user_data;
    int alarmStatus =0;

    if(cont != target)
    {
        sel_selete = (uintptr_t)cont->user_data;
    }
    if((opt->alarm_list.item[sel_selete]->IconSet !=NULL)&&(target==opt->alarm_list.item[sel_selete]->IconSet->myobj))
    {
        if(event->code== LV_EVENT_RELEASED)
        {
            memset(&opt->infoAlarmCur,0,sizeof(alarm_info));
            opt->get_alarm_info(sel_selete,&opt->infoAlarmCur);
            if(opt->mainList !=NULL)
            {
                opt->mainList->show(false);
            }
			opt->get_dayType_str(opt->infoAlarmCur.type,opt->reData);
			sprintf(opt->tiData,"%.2d:%.2d",opt->infoAlarmCur.hours,opt->infoAlarmCur.minute);
            opt->alarmIndex =sel_selete;
            opt->addIcon->show(false);
            opt->editIcon->show(false);
            opt->alarm_setlist_creat();
            opt->okIcon->show(true);
            opt->cancelIcon->show(true);
        }
    }
    else if((opt->alarm_list.item[sel_selete]->IconDel !=NULL)&&(target==opt->alarm_list.item[sel_selete]->IconDel->myobj))
    {
        if(event->code== LV_EVENT_RELEASED)
        {
			opt->alarm_setlist_del();
			opt->del_alarm_CurStatus(sel_selete);
			opt->alarm_list_delete();
			usleep(2000);
		    opt->alarm_list_creat();
			opt->alarm_list_show(false);
        }
    }
    else if((opt->alarm_list.item[sel_selete]->IconClose !=NULL)&&(target==opt->alarm_list.item[sel_selete]->IconClose->myobj))
    {
        alarmStatus = opt->get_alarm_CurStatus(sel_selete);
        alarmStatus = !alarmStatus;
        if(alarmStatus)
        {
            opt->alarm_list.item[sel_selete]->IconClose->set_main_bg_color(lv_color_hex(0x00ff00),LV_OPA_100);
            opt->alarm_list.item[sel_selete]->StatusClose->align(LV_ALIGN_RIGHT_MID, 0, 0);
        }
        else
        {
            opt->alarm_list.item[sel_selete]->IconClose->set_main_bg_color(lv_color_hex(0x5c5c5c),LV_OPA_100);
            opt->alarm_list.item[sel_selete]->StatusClose->align(LV_ALIGN_LEFT_MID, 0, 0);
        }
        opt->set_alarm_CurStatus(sel_selete,alarmStatus);
    }
}

void alarmScene::alarmScene_sence_draw(void)
{
    uint16_t h = user_time.hour * 300 + user_time.minute / 12 % 12 * 60;
    hoursImage->set_angle(h);
    minuteImage->set_angle(user_time.minute*60);
    secondImage->set_angle(user_time.second*60);
}

void alarmScene::alarmScene_sence_delete(void)
{
    if(dotImage != NULL)
    {
        delete dotImage;
        dotImage = NULL;
    }
    if(secondImage != NULL)
    {
        delete secondImage;
        secondImage = NULL;
    }
    if(minuteImage != NULL)
    {
        delete minuteImage;
        minuteImage = NULL;
    }
    if(hoursImage != NULL)
    {
        delete hoursImage;
        hoursImage = NULL;
    }
    if(plateImage != NULL)
    {
        delete plateImage;
        plateImage = NULL;
    }
    if(addIcon != NULL)
    {
        delete addIcon;
        addIcon = NULL;
    }
    if(editIcon != NULL)
    {
        delete editIcon;
        editIcon = NULL;
    }
    if(cancelIcon != NULL)
    {
        delete cancelIcon;
        cancelIcon = NULL;
    }
    if(okIcon != NULL)
    {
        delete okIcon;
        okIcon = NULL;
    }
	alarm_list_delete();
    if(alarmListFrame != NULL)
    {
        delete alarmListFrame;
        alarmListFrame = NULL;
    }
}
void alarmScene::get_dayType_str(int dayType,char *dayTypeStr)
{
	bool status =false;
	if(dayType ==WDAY_EN)
	{
		strcpy(dayTypeStr,STR_OFF);
	}
	else
	{
		if(dayType&DAY_SUN)
		{
			strcpy(dayTypeStr,STR_SUN);
			status =true;
		}
		if(dayType&DAY_MON)
		{
			if(status ==true)
				strcat(dayTypeStr,",");
			strcat(dayTypeStr,STR_MON);
			status =true;
		}
		if(dayType&DAY_TUES)
		{
			if(status ==true)
				strcat(dayTypeStr,",");
			strcat(dayTypeStr,STR_TUE);
			status =true;
		}
		if(dayType&DAY_WED)
		{
			if(status ==true)
				strcat(dayTypeStr,",");
			strcat(dayTypeStr,STR_WED);
			status =true;
		}
		if(dayType&DAY_THUR)
		{
			if(status ==true)
				strcat(dayTypeStr,",");
			strcat(dayTypeStr,STR_THU);
			status =true;
		}
		if(dayType&DAY_FRI)
		{
			if(status ==true)
				strcat(dayTypeStr,",");
			strcat(dayTypeStr,STR_FRI);
			status =true;
		}
		if(dayType&DAY_SAT)
		{
			if(status ==true)
				strcat(dayTypeStr,",");
			strcat(dayTypeStr,STR_SAT);
		}
	}
}
void alarmScene::alarm_setlist_creat(void)
{
	if(mainList !=NULL)
        mainList->show(false);
    repeatLabel = new LvcppLabel(alarmListFrame->myobj);
    repeatLabel->set_size(590,110);
    repeatLabel->align(LV_ALIGN_TOP_LEFT,0,0);
    repeatLabel->set_main_bg_color(lv_color_hex(0x00a7d4),LV_OPA_100);
    repeatLabel->set_txt("");
    repeatLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
    repeatLabel->add_event_cb(head_event_handler,LV_EVENT_RELEASED,this);
	
    repeatName = new LvcppLabel(repeatLabel->myobj);
    repeatName->set_size(150,40);
    repeatName->align(LV_ALIGN_TOP_LEFT, 10, 35);
    repeatName->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    repeatName->txt_align(LV_TEXT_ALIGN_LEFT);
    repeatName->txt_color(lv_color_white(),LV_PART_MAIN);
    repeatName->set_txt(STR_REPEAT);
	
    repeatData = new LvcppLabel(repeatLabel->myobj);
    repeatData->set_size(380,40);
    repeatData->align(LV_ALIGN_TOP_LEFT, 170, 35);
    repeatData->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    repeatData->txt_align(LV_TEXT_ALIGN_RIGHT);
    repeatData->txt_color(lv_color_hex(0x77d9f4),LV_PART_MAIN);
    repeatData->set_txt(reData);
	
    repeatDot = new LvcppLabel(repeatLabel->myobj);
    repeatDot->set_size(30,30);
    repeatDot->align(LV_ALIGN_TOP_LEFT, 550, 40);
    repeatDot->txt_font_size(30, FT_FONT_STYLE_BOLD);
    repeatDot->txt_align(LV_TEXT_ALIGN_RIGHT);
    repeatDot->txt_color(lv_color_hex(0x77d9f4),LV_PART_MAIN);
    repeatDot->set_txt(">");
	
    repeatLine = new LvcppLabel(repeatLabel->myobj);
    repeatLine->set_size(590,1);
    repeatLine->set_main_bg_color(MENU_BTN_COLOR,LV_OPA_100);
    repeatLine->align(LV_ALIGN_BOTTOM_MID, 0, 0);
    repeatLine->set_txt("");

    ringLabel = new LvcppLabel(alarmListFrame->myobj);
    ringLabel->set_size(590,110);
    ringLabel->align(LV_ALIGN_TOP_LEFT,0,110);
    ringLabel->set_main_bg_color(lv_color_hex(0x00a7d4),LV_OPA_100);
    ringLabel->set_txt("");
    ringLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
    ringLabel->add_event_cb(head_event_handler,LV_EVENT_RELEASED,this);
	
    ringName = new LvcppLabel(ringLabel->myobj);
    ringName->set_size(150,40);
    ringName->align(LV_ALIGN_TOP_LEFT, 10, 35);
    ringName->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    ringName->txt_align(LV_TEXT_ALIGN_LEFT);
    ringName->txt_color(lv_color_white(),LV_PART_MAIN);
    ringName->set_txt(STR_RINGTONE);
	
    ringData = new LvcppLabel(ringLabel->myobj);
    ringData->set_size(380,40);
    ringData->align(LV_ALIGN_TOP_LEFT, 170, 35);
    ringData->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    ringData->txt_align(LV_TEXT_ALIGN_RIGHT);
    ringData->txt_color(lv_color_hex(0x77d9f4),LV_PART_MAIN);
    ringData->set_txt((char*)SongName[infoAlarmCur.ring]);
	
    ringDot = new LvcppLabel(ringLabel->myobj);
    ringDot->set_size(30,30);
    ringDot->align(LV_ALIGN_TOP_LEFT, 550, 40);
    ringDot->txt_font_size(30, FT_FONT_STYLE_BOLD);
    ringDot->txt_align(LV_TEXT_ALIGN_RIGHT);
    ringDot->txt_color(lv_color_hex(0x77d9f4),LV_PART_MAIN);
    ringDot->set_txt(">");
	
    ringLine = new LvcppLabel(ringLabel->myobj);
    ringLine->set_size(590,1);
    ringLine->set_main_bg_color(MENU_BTN_COLOR,LV_OPA_100);
    ringLine->align(LV_ALIGN_BOTTOM_MID, 0, 0);
    ringLine->set_txt("");

    labelLabel = new LvcppLabel(alarmListFrame->myobj);
    labelLabel->set_size(590,110);
    labelLabel->align(LV_ALIGN_TOP_LEFT,0,220);
    labelLabel->set_main_bg_color(lv_color_hex(0x00a7d4),LV_OPA_100);
    labelLabel->set_txt("");
    labelLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
    labelLabel->add_event_cb(head_event_handler,LV_EVENT_RELEASED,this);
	
    labelName = new LvcppLabel(labelLabel->myobj);
    labelName->set_size(150,40);
    labelName->align(LV_ALIGN_TOP_LEFT, 10, 35);
    labelName->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    labelName->txt_align(LV_TEXT_ALIGN_LEFT);
    labelName->txt_color(lv_color_white(),LV_PART_MAIN);
    labelName->set_txt(STR_LABEL);
	
    labelData = new LvcppLabel(labelLabel->myobj);
    labelData->set_size(380,40);
    labelData->align(LV_ALIGN_TOP_LEFT, 170, 35);
    labelData->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    labelData->txt_align(LV_TEXT_ALIGN_RIGHT);
    labelData->txt_color(lv_color_hex(0x77d9f4),LV_PART_MAIN);
    labelData->set_txt(infoAlarmCur.name);
	
    labelDot = new LvcppLabel(labelLabel->myobj);
    labelDot->set_size(30,30);
    labelDot->align(LV_ALIGN_TOP_LEFT, 550, 40);
    labelDot->txt_font_size(30, FT_FONT_STYLE_BOLD);
    labelDot->txt_align(LV_TEXT_ALIGN_RIGHT);
    labelDot->txt_color(lv_color_hex(0x77d9f4),LV_PART_MAIN);
    labelDot->set_txt(">");
    labelLine = new LvcppLabel(labelLabel->myobj);
    labelLine->set_size(590,1);
    labelLine->set_main_bg_color(MENU_BTN_COLOR,LV_OPA_100);
    labelLine->align(LV_ALIGN_BOTTOM_MID, 0, 0);
    labelLine->set_txt("");

    timeLabel = new LvcppLabel(alarmListFrame->myobj);
    timeLabel->set_size(590,110);
    timeLabel->align(LV_ALIGN_TOP_LEFT,0,330);
    timeLabel->set_main_bg_color(lv_color_hex(0x00a7d4),LV_OPA_100);
    timeLabel->set_txt("");
    timeLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
    timeLabel->add_event_cb(head_event_handler,LV_EVENT_RELEASED,this);
	
    timeName = new LvcppLabel(timeLabel->myobj);
    timeName->set_size(150,40);
    timeName->align(LV_ALIGN_TOP_LEFT, 10, 35);
    timeName->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    timeName->txt_align(LV_TEXT_ALIGN_LEFT);
    timeName->txt_color(lv_color_white(),LV_PART_MAIN);
    timeName->set_txt(STR_SETTIME);
	
    timeData = new LvcppLabel(timeLabel->myobj);
    timeData->set_size(380,40);
    timeData->align(LV_ALIGN_TOP_LEFT, 170, 35);
    timeData->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    timeData->txt_align(LV_TEXT_ALIGN_RIGHT);
    timeData->txt_color(lv_color_hex(0x77d9f4),LV_PART_MAIN);
    timeData->set_txt(tiData);
	
    timeDot = new LvcppLabel(timeLabel->myobj);
    timeDot->set_size(30,30);
    timeDot->align(LV_ALIGN_TOP_LEFT, 550, 40);
    timeDot->txt_font_size(30, FT_FONT_STYLE_BOLD);
    timeDot->txt_align(LV_TEXT_ALIGN_RIGHT);
    timeDot->txt_color(lv_color_hex(0x77d9f4),LV_PART_MAIN);
    timeDot->set_txt(">");
	
    timeLine = new LvcppLabel(timeLabel->myobj);
    timeLine->set_size(590,1);
    timeLine->set_main_bg_color(MENU_BTN_COLOR,LV_OPA_100);
    timeLine->align(LV_ALIGN_BOTTOM_MID, 0, 0);
    timeLine->set_txt("");
}

void alarmScene::alarm_setlist_del(void)
{
    if(repeatLine != NULL)
    {
        delete repeatLine;
        repeatLine = NULL;
    }
    if(repeatDot != NULL)
    {
        delete repeatDot;
        repeatDot = NULL;
    }
    if(repeatData != NULL)
    {
        delete repeatData;
        repeatData = NULL;
    }
    if(repeatName != NULL)
    {
        delete repeatName;
        repeatName = NULL;
    }
    if(ringLine != NULL)
    {
        delete ringLine;
        ringLine = NULL;
    }
    if(ringDot != NULL)
    {
        delete ringDot;
        ringDot = NULL;
    }
    if(ringData != NULL)
    {
        delete ringData;
        ringData = NULL;
    }
    if(ringName != NULL)
    {
        delete ringName;
        ringName = NULL;
    }
    if(labelLine != NULL)
    {
        delete labelLine;
        labelLine = NULL;
    }
    if(labelDot != NULL)
    {
        delete labelDot;
        labelDot = NULL;
    }
    if(labelData != NULL)
    {
        delete labelData;
        labelData = NULL;
    }
    if(labelName != NULL)
    {
        delete labelName;
        labelName = NULL;
    }
    if(timeLine != NULL)
    {
        delete timeLine;
        timeLine = NULL;
    }
    if(timeDot != NULL)
    {
        delete timeDot;
        timeDot = NULL;
    }
    if(timeData != NULL)
    {
        delete timeData;
        timeData = NULL;
    }

    if(repeatLabel != NULL)
    {
        delete repeatLabel;
        repeatLabel = NULL;
    }
    if(ringLabel != NULL)
    {
        delete ringLabel;
        ringLabel = NULL;
    }
    if(labelLabel != NULL)
    {
        delete labelLabel;
        labelLabel = NULL;
    }
    if(timeLabel != NULL)
    {
        delete timeLabel;
        timeLabel = NULL;
    }
}
void alarmScene::alarm_cjson_alarmInfo(char*alarmBuff)
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
                    alarm_add_info(&alarmList);
                }
            }
        }
    }
}

void alarmScene::get_all_alarmList(void)
{
    FILE *fp = NULL;
    struct stat buf;
    char *alarmBuff =NULL;
    int sizeAlarm =0;

    fp = fopen(VA_ALARMLIST_PATH, "r");
    if(fp ==NULL)
    {
        LV_LOG_USER("%s open fail\n", VA_ALARMLIST_PATH);
        return;
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
        return;
    }
    if(fp != NULL)
    {
        fread(alarmBuff, 1, sizeAlarm, fp);
        fclose(fp);
        fp = NULL;
        alarm_cjson_alarmInfo(alarmBuff);
    }
    if(alarmBuff ==NULL)
    {
        free(alarmBuff);
        alarmBuff =NULL;
    }
}