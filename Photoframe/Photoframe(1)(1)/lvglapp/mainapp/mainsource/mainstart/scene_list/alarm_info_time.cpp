#include "alarm_info_time.h"

Alarminfo_Time::Alarminfo_Time(int Hours,int Minute,int Hours24,lv_obj_t* parent)
{
	char buff_s[6]={0};
	char buff[512]={0};
	int apmStatus =0,i=0;
	
	if(Hours24 ==24)
		Type24Time =true;
	else
	{
		if(Hours>12)
		{
			Hours -=13;
			apmStatus =1;
		}
		else if(Hours ==0)
		{
			Hours =11;
		}
		else if(Hours ==12)
		{
			Hours =11;
			apmStatus =1;
		}
		else
		{
			Hours --;
		}
	}
    alarm_frame_label = new LvcppScreen(parent);
    alarm_frame_label->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    alarm_frame_label->align(LV_ALIGN_TOP_MID,0,0);
    alarm_frame_label->set_main_bg_color(lv_color_black(),LV_OPA_60);
    alarmscreen = alarm_frame_label->myobj;

    alarm_info = new LvcppButton(alarmscreen);
    alarm_info->set_size(650,280);
    alarm_info->center_align();
    alarm_info->set_main_pad_all(0);
    alarm_info->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    alarm_info->set_style_radius(10,0);
    alarm_info->clear_flag(LV_OBJ_FLAG_CLICKABLE);
    alarm_info_frame = alarm_info->myobj;

    cancel = new LvcppButton(alarm_info_frame);
    cancel->set_size(300,50);
    cancel->set_main_pad_all(0);
    cancel->align(LV_ALIGN_TOP_LEFT,10,210);
    cancel->set_main_bg_color(lv_color_hex(0x00a7d4),LV_OPA_100);
    cancel->set_style_radius(10,0);
    cancel->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    cancel->add_txt(STR_CANCEL);
    cancel->txt_center();

    confirm = new LvcppButton(alarm_info_frame);
    confirm->set_size(300,50);
    confirm->align(LV_ALIGN_TOP_RIGHT,-10,210);
    confirm->set_main_bg_color(lv_color_hex(0x00a7d4),LV_OPA_100);
    confirm->set_style_radius(10,0);
    confirm->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    confirm->add_txt(STR_OK);
    confirm->txt_center();
	if(!Type24Time)
	{
	    roller1 = new LvcppRoller(alarm_info_frame);
	    roller1->set_size(80,50);
	    roller1->align(LV_ALIGN_TOP_LEFT,100,50);
	    roller1->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_0);
		memset(buff,0,sizeof(buff));
		sprintf(buff,"%s\n%s",STR_AM,STR_PM);
	    roller1->set_options(buff,0);
	    roller1->set_main_border(0,lv_color_hex(0xffffff),LV_OPA_0);
	    roller1->set_visible_row_count(3);
		roller1->set_selected(apmStatus,LV_ANIM_OFF);
	}

    roller2 = new LvcppRoller(alarm_info_frame);
    roller2->set_size(80,50);
	roller2->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_0);
	if(!Type24Time)
	{
    	roller2->align(LV_ALIGN_TOP_LEFT,280,50);
		memset(buff,0,sizeof(buff));
		for(i=0;i<12;i++)
		{
			memset(buff_s,0,sizeof(buff_s));
			if(i==0)
				sprintf(buff_s,"%.2d",i+1);
			else
				sprintf(buff_s,"\n%.2d",i+1);
			strcat(buff,buff_s);
		}
	}
	else
	{
		roller2->align(LV_ALIGN_TOP_LEFT,195,50);
		memset(buff,0,sizeof(buff));
		for(i=0;i<24;i++)
		{
			memset(buff_s,0,sizeof(buff_s));
			if(i==0)
				sprintf(buff_s,"%.2d",i);
			else
				sprintf(buff_s,"\n%.2d",i);
			strcat(buff,buff_s);
		}
	}
	roller2->set_options(buff,0);
    roller2->set_main_border(0,lv_color_hex(0xffffff),LV_OPA_0);
    roller2->set_visible_row_count(3);
	roller2->set_selected(Hours,LV_ANIM_OFF);

    roller3 = new LvcppRoller(alarm_info_frame);
    roller3->set_size(80,50);
	if(!Type24Time)
    	roller3->align(LV_ALIGN_TOP_LEFT,460,50);
	else
		roller3->align(LV_ALIGN_TOP_LEFT,375,50);
    roller3->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_0);
	memset(buff,0,sizeof(buff));
	for(i=0;i<60;i++)
	{
		memset(buff_s,0,sizeof(buff_s));
		if(i==0)
			sprintf(buff_s,"%.2d",i);
		else
			sprintf(buff_s,"\n%.2d",i);
		strcat(buff,buff_s);
	}
    roller3->set_options(buff,0);
    roller3->set_main_border(0,lv_color_hex(0xffffff),LV_OPA_0);
    roller3->set_visible_row_count(3);
	roller3->set_selected(Minute,LV_ANIM_OFF);
}

int Alarminfo_Time::get_info(void)
{
    int timeSet =0;

    roller2->get_selected_str(hour, 8);
    roller3->get_selected_str(minute, 8);
	if(!Type24Time)
	{
		roller1->get_selected_str(apm, 8);
		if(strcmp(apm,STR_PM)==0)
		{
            if(atoi(hour) ==12)
                timeSet =(int)(atoi(hour)*100 + atoi(minute));
            else
                timeSet =(int)((atoi(hour)+12)*100 + atoi(minute));
        }
        else
        {
            if(atoi(hour) ==12)
                timeSet =(int)(atoi(minute));
            else
                timeSet =(int)(atoi(hour)*100 + atoi(minute));
        }
	}
	else
		timeSet =(int)(atoi(hour)*100 + atoi(minute));
    return timeSet;
}
void Alarminfo_Time::Alarminfo_Time_delete(void)
{
    if(roller3 != nullptr)
    {
        delete roller3;
        roller3= nullptr;
    }

    if(roller2 != nullptr)
    {
        delete roller2;
        roller2= nullptr;
    }
  	if(!Type24Time)
  	{
	    if(roller1 != nullptr)
	    {
	        delete roller1;
	        roller1= nullptr;
	    }
  	}
    if(confirm != nullptr)
    {
        delete confirm;
        confirm= nullptr;
    }

    if(cancel != nullptr)
    {
        delete cancel;
        cancel= nullptr;
    }

    if(alarm_info != nullptr)
    {
        delete alarm_info;
        alarm_info= nullptr;
    }

    if(alarm_frame_label != nullptr)
    {
        delete alarm_frame_label;
        alarm_frame_label= nullptr;
    }

}

Alarminfo_Time::~Alarminfo_Time(void)
{
    if(roller3 != nullptr)
    {
        delete roller3;
        roller3= nullptr;
    }

    if(roller2 != nullptr)
    {
        delete roller2;
        roller2= nullptr;
    }

    if(roller1 != nullptr)
    {
        delete roller1;
        roller1= nullptr;
    }

    if(confirm != nullptr)
    {
        delete confirm;
        confirm= nullptr;
    }

    if(cancel != nullptr)
    {
        delete cancel;
        cancel= nullptr;
    }

    if(alarm_info != nullptr)
    {
        delete alarm_info;
        alarm_info= nullptr;
    }

    if(alarm_frame_label != nullptr)
    {
        delete alarm_frame_label;
        alarm_frame_label= nullptr;
    }

}



