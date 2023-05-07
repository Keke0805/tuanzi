#include  "mainappstart.h"
#include  "include/configCustom.h"
#include  "include/ui_config.h"
#include  "include/str_config.h"
#include  "hv/requests.h"
#include  "hv/hthread.h"

#ifdef _UCHIP_T113
#include  "common/common.h"
#define WEATHER_PATCH  "/usr/bin/resource/image/weathericon/"
#else
#define WEATHER_PATCH  "S:/resource/image/weathericon/"
#endif
using namespace LVGLOPTAPI;
MainAPPStart* optMain =NULL;

void MainAPPStart::ui_image_decode(void)
{
    #ifdef IMAGE_DECODE
    SCREEN_LAUBG_PNG=(void*)parse_image_from_file(SCREEN_LAUBG_PNG_PATH);
    SCREEN_LAUPHOTO_PNG=(void*)parse_image_from_file(SCREEN_LAUPHOTO_PNG_PATH);
    SCREEN_LAUVIDEO_PNG=(void*)parse_image_from_file(SCREEN_LAUVIDEO_PNG_PATH);
    SCREEN_LAUMUSIC_PNG=(void*)parse_image_from_file(SCREEN_LAUMUSIC_PNG_PATH);
    SCREEN_LAUCALENDAR_PNG=(void*)parse_image_from_file(SCREEN_LAUCALENDAR_PNG_PATH);
    SCREEN_LAUCLOCK_PNG=(void*)parse_image_from_file(SCREEN_LAUCLOCK_PNG_PATH);
    SCREEN_LAUSETTING_PNG=(void*)parse_image_from_file(SCREEN_LAUSETTING_PNG_PATH);
    SCREEN_LAUWEATHER_PNG=(void*)parse_image_from_file(SCREEN_LAUWEATHER_PNG_PATH);
    SCREEN_LAUALARM_PNG=(void*)parse_image_from_file(SCREEN_LAUALARM_PNG_PATH);
    SCREEN_LAUWEATHER_BG_PNG=(void*)parse_image_from_file(SCREEN_LAUWEATHER_BG_PNG_PATH);
    SCREEN_LAUWEATHER_NO_BG_PNG=(void*)parse_image_from_file(SCREEN_LAUWEATHER_NO_BG_PNG_PATH);
	
    SCREEN_LAUPHOTO1_PNG=(void*)parse_image_from_file(SCREEN_LAUPHOTO1_PNG_PATH);
    SCREEN_LAUPHOTO2_PNG=(void*)parse_image_from_file(SCREEN_LAUPHOTO2_PNG_PATH);
    SCREEN_LAUPHOTO3_PNG=(void*)parse_image_from_file(SCREEN_LAUPHOTO3_PNG_PATH);
	
    HEAD_WIFI0_PNG=(void*)parse_image_from_file(HEAD_WIFI0_PNG_PATH);
    HEAD_WIFI1_PNG=(void*)parse_image_from_file(HEAD_WIFI1_PNG_PATH);
    HEAD_WIFI2_PNG=(void*)parse_image_from_file(HEAD_WIFI2_PNG_PATH);
    HEAD_WIFI3_PNG=(void*)parse_image_from_file(HEAD_WIFI3_PNG_PATH);
    HEAD_WIFI4_PNG=(void*)parse_image_from_file(HEAD_WIFI4_PNG_PATH);
    HEAD_WIFINO_PNG=(void*)parse_image_from_file(HEAD_WIFINO_PNG_PATH);
	
    #endif
}

void MainAPPStart::ui_image_free(void)
{
    #ifdef IMAGE_DECODE
	if(SCREEN_LAUBG_PNG !=NULL)
	{
    	free_image(SCREEN_LAUBG_PNG);
		SCREEN_LAUBG_PNG =NULL;
	}
	if(SCREEN_LAUPHOTO_PNG !=NULL)
	{
    	free_image(SCREEN_LAUPHOTO_PNG);
		SCREEN_LAUPHOTO_PNG =NULL;
	}
	if(SCREEN_LAUVIDEO_PNG !=NULL)
	{
    	free_image(SCREEN_LAUVIDEO_PNG);
		SCREEN_LAUVIDEO_PNG =NULL;
	}
	if(SCREEN_LAUMUSIC_PNG !=NULL)
	{
    	free_image(SCREEN_LAUMUSIC_PNG);
		SCREEN_LAUMUSIC_PNG =NULL;
	}
	if(SCREEN_LAUCALENDAR_PNG !=NULL)
	{
    	free_image(SCREEN_LAUCALENDAR_PNG);
		SCREEN_LAUCALENDAR_PNG =NULL;
	}
	if(SCREEN_LAUCLOCK_PNG !=NULL)
	{
    	free_image(SCREEN_LAUCLOCK_PNG);
		SCREEN_LAUCLOCK_PNG =NULL;
	}
	if(SCREEN_LAUSETTING_PNG !=NULL)
	{
    	free_image(SCREEN_LAUSETTING_PNG);
		SCREEN_LAUSETTING_PNG =NULL;
	}
	if(SCREEN_LAUWEATHER_PNG !=NULL)
	{
    	free_image(SCREEN_LAUWEATHER_PNG);
		SCREEN_LAUWEATHER_PNG =NULL;
	}
	if(SCREEN_LAUALARM_PNG !=NULL)
	{
    	free_image(SCREEN_LAUALARM_PNG);
		SCREEN_LAUALARM_PNG =NULL;
	}
	if(SCREEN_LAUWEATHER_BG_PNG !=NULL)
	{
    	free_image(SCREEN_LAUWEATHER_BG_PNG);
		SCREEN_LAUWEATHER_BG_PNG =NULL;
	}
	if(SCREEN_LAUWEATHER_NO_BG_PNG !=NULL)
	{
    	free_image(SCREEN_LAUWEATHER_NO_BG_PNG);
		SCREEN_LAUWEATHER_NO_BG_PNG =NULL;
	}
	if(SCREEN_LAUPHOTO1_PNG !=NULL)
	{
    	free_image(SCREEN_LAUPHOTO1_PNG);
		SCREEN_LAUPHOTO1_PNG =NULL;
	}
	if(SCREEN_LAUPHOTO2_PNG !=NULL)
	{
    	free_image(SCREEN_LAUPHOTO2_PNG);
		SCREEN_LAUPHOTO2_PNG =NULL;
	}
	if(SCREEN_LAUPHOTO3_PNG !=NULL)
	{
    	free_image(SCREEN_LAUPHOTO3_PNG);
		SCREEN_LAUPHOTO3_PNG =NULL;
	}
	if(HEAD_WIFI0_PNG !=NULL)
	{
    	free_image(HEAD_WIFI0_PNG);
		HEAD_WIFI0_PNG =NULL;
	}
	if(HEAD_WIFI1_PNG !=NULL)
	{
    	free_image(HEAD_WIFI1_PNG);
		HEAD_WIFI1_PNG =NULL;
	}
	if(HEAD_WIFI2_PNG !=NULL)
	{
    	free_image(HEAD_WIFI2_PNG);
		HEAD_WIFI2_PNG =NULL;
	}
	if(HEAD_WIFI3_PNG !=NULL)
	{
    	free_image(HEAD_WIFI3_PNG);
		HEAD_WIFI3_PNG =NULL;
	}
	if(HEAD_WIFI4_PNG !=NULL)
	{
    	free_image(HEAD_WIFI4_PNG);
		HEAD_WIFI4_PNG =NULL;
	}
	if(HEAD_WIFINO_PNG !=NULL)
	{
    	free_image(HEAD_WIFINO_PNG);
		HEAD_WIFINO_PNG =NULL;
	}
    #endif
}
static void set_dateTime(char *dateStr,char *timeStr)
{
    char buff[24]={0};
    int year=0,mon=0,day=0,hour=0,minute=0,second=0;

    memset(buff,0,24);
    strncpy(buff,dateStr+8,2);
    day = atoi(buff);

    memset(buff,0,24);
    strncpy(buff,dateStr+5,3);
    mon = atoi(buff);

    memset(buff,0,24);
    strncpy(buff,dateStr,4);
    year = atoi(buff);

    memset(buff,0,24);
    strncpy(buff,timeStr,2);
    hour = atoi(buff);

    memset(buff,0,24);
    strncpy(buff,timeStr+3,2);
    minute = atoi(buff);
	
    memset(buff,0,24);
    sprintf(buff,"date -s \"%.4d-%.2d-%.2d %.2d:%.2d:%.2d\"",year,mon,day,hour,minute,second);

    system(buff);
}

MainAPPStart::MainAPPStart(LvcppMainScreen* panel)
{
	optMain =this;
    m_panel = panel;
    m_parent = m_panel->get_obj();

#ifdef _UCHIP_T113
	if(access("/usr/bin/rc.ota", 0) !=0)
	{
		remove("rm -rf /usr/bin/rc.ota");
	}
	char dateBuff[12]={0};
	char timeBuff[12]={0};
	int	dateRet =0;
	int	timeRet =0;
	dateRet = read_string_type_param(PUBLIC_SCENE, DATE, dateBuff,sizeof(dateBuff));
	timeRet = read_string_type_param(PUBLIC_SCENE, TIME, timeBuff,sizeof(timeBuff));
	if((dateRet ==0)&&(timeRet ==0))
	{
		set_dateTime(dateBuff,timeBuff);
	}
#endif

    ui_image_decode();
    m_panel->showlogo(SCREEN_LAUBG_PNG,SCREEN_HOR_SIZE,SCREEN_VER_SIZE,0);

    httpStart = new Http();
    alarmCheckList = new checkTimeMsg();
    if(httpStart !=NULL)
    {
        httpStart->get_cur_weather(&curWeatherInfo);
        httpStart->get_first_weather(&oneWeatherInfo);
        httpStart->get_second_weather(&towWeatherInfo);
        httpStart->get_three_weather(&threeWeatherInfo);
    }
    main_initial();
    SSTAR_RegisterApplib(APP_NAME_UI,funcallback);
	LV_LOG_USER("main_initial finish");
}

MainAPPStart::~MainAPPStart(void)
{
    main_deinitial();
    ui_image_free();
    if(httpStart != NULL)
    {
        delete httpStart;
        httpStart =NULL;
    }
    if(alarmCheckList != NULL)
    {
        delete alarmCheckList;
        alarmCheckList =NULL;
    }
}

///////////////////////////////////////////////////////////////////////////////////

int MainAPPStart::main_initial(void)
{
    get_wifi_info();
    draw_scene_desktop();
    draw_calendar_scene();
    draw_weather_scene();
    show_status =true;
    if(maintimer == NULL)
    {
        maintimer = startTimer(200, this);
    }
    return 0;
}

int MainAPPStart::main_deinitial(void)
{
    show_status =false;
    delete_str();
    delete_ui_free();
    m_panel->transparent(true);
    m_panel->showlogo(NULL,SCREEN_HOR_SIZE,SCREEN_VER_SIZE,0);
    return 0;
}

void MainAPPStart::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);

    lauTimecnt++;
    if(show_status == true)
    {
        if((lauTimecnt%150)==0)
        {
            get_wifi_info();
            draw_weather_scene();
            show_weather();
        }
        draw_calendar_scene();
        if(show_time_num >5*slide_time[show_time])
        {
            show_time_num =0;
            play_next_file();
        }
        show_time_num ++;
    }
}

void MainAPPStart::get_wifi_info(void)
{
    static int timecnt = 0;
    wifi_data_t wifi;
    get_wifi_data(&wifi);
    timecnt++;
    if(wifi.is_connected)
    {
        if(wifi.rssi>=75)
        {
            cur_wifi_state =4;
        }
        else if(wifi.rssi>=50)
        {
            cur_wifi_state =3;
        }
        else if(wifi.rssi>=25)
        {
            cur_wifi_state =2;
        }
        else
        {
            cur_wifi_state =1;
        }
        if((timecnt%10)==0)
        {
            if(httpStart !=NULL)
            {
                httpStart->Http_get_weather();
            }
        }
    }
    else
    {
        cur_wifi_state =-1;
    }
}

void MainAPPStart::enter_photoList_app(void)
{
    char *patc =NULL;
    char buff[8]={0};

    show_status =false;
    if(photoScene == NULL)
    {
        strcpy(buff,"List");
        photoScene = new photoMain(m_parent,httpStart,buff,patc);
    }
}

void MainAPPStart::enter_videolist_app(void)
{
    char *patc =NULL;
    char buff[8]={0};

    show_status =false;
    if(VideoMain==NULL)
    {
        if(httpStart !=NULL)
        {
            httpStart->set_msg_type(UI_VIDEOLIST);
        }
		strcpy(buff,"List");
        VideoMain = new videoMain(m_parent,httpStart,buff,patc);
    }
}

void MainAPPStart::enter_musicScene_app(void)
{
    show_status =false;
    if(music_list==NULL)
    {
        if(httpStart !=NULL)
        {
            httpStart->set_msg_type(UI_MUSIC);
        }
        music_list = new musicList(m_parent);
        music_list->init_parament();
    }
}

void MainAPPStart::enter_calendarScene_app(void)
{
    show_status =false;
    if(calendar_main==NULL)
    {
        if(httpStart !=NULL)
        {
            httpStart->set_msg_type(UI_CALENDAR);
        }
        calendar_main = new Calendar(m_parent);
        calendar_main->init_parament();
    }
}

void MainAPPStart::enter_weatherScene_app(void)
{
    show_status =false;
    if(weather_main==NULL)
    {
        if(httpStart !=NULL)
        {
            httpStart->set_msg_type(UI_WEATHER);
        }
        weather_main = new Weather(m_parent,httpStart);
        weather_main->init_parament();
    }
}

void MainAPPStart::enter_clockScene_app(void)
{
    show_status =false;
    if(clockTime_main==NULL)
    {
        if(httpStart !=NULL)
        {
            httpStart->set_msg_type(UI_CLOCK);
        }
        clockTime_main = new ClockTime(m_parent);
        clockTime_main->init_parament();
    }
}

void MainAPPStart::enter_alarmScene_app(void)
{
    show_status =false;
    if(alarmScene_main==NULL)
    {
        if(httpStart !=NULL)
        {
            httpStart->set_msg_type(UI_ALARM);
        }
        alarmScene_main = new alarmScene(m_parent,alarmCheckList);
        alarmScene_main->init_parament();
    }
}

void MainAPPStart::enter_settingScene_app(void)
{
    show_status =false;
    if(settingScene_main==NULL)
    {
        if(httpStart !=NULL)
        {
            httpStart->set_msg_type(UI_SETTING);
        }
        settingScene_main = new settingScene(m_parent);
        settingScene_main->init_parament();
    }
}

void MainAPPStart::laufuncallback(void)
{
    LV_LOG_USER("laufuncallback");
    if(httpStart !=NULL)
    {
        httpStart->set_msg_type(UI_LAUNCHER);
    }
    show_status =true;
    optMain->m_panel->transparent(false);
    optMain->m_panel->showlogo(SCREEN_LAUBG_PNG,SCREEN_HOR_SIZE,SCREEN_VER_SIZE,0);
    optMain->main_initial();
}

void MainAPPStart::weatherMainUpdata(void)
{
    if(weather_main !=NULL)
    {
        weather_main->get_weather_scene_info();
        weather_main->Weather_scene_draw();
    }
}
void MainAPPStart::start_ota_scene(char *patch)
{
	char buff[128]={0};
	sprintf(buff,"unzip -o %s -d %s",patch,OTA_PATCH);
	system(buff);
	usleep(50000);
	system("/usr/bin/rc.ota");
}

void MainAPPStart::funcallback(msg_apps_t *msg)
{
    LV_LOG_USER("type:%d ->mode:%d",msg->type,msg->mode);
    switch(msg->type)
    {
        case UI_PHOTOLIST:
        if(msg->mode ==MODE_RETURN)
        {
            optMain->photomain_destory();
        }
        break;
        case UI_VIDEOLIST:
        if(msg->mode ==MODE_RETURN)
        {
            optMain->videoMain_destory();
        }
        break;
        case UI_CALENDAR:
        if(msg->mode ==MODE_RETURN)
        {
            optMain->calendarmain_destory();
        }
        break;
        case UI_MUSIC:
        if(msg->mode ==MODE_RETURN)
        {
            optMain->musiclist_destory();
        }
        break;
        case UI_ALARM:
        if(msg->mode ==MODE_RETURN)
        {
            optMain->alarmScenemain_destory();
        }
        else if(msg->mode ==VPLAY_PLAY_CMD)
        {
            if(optMain->alarmBounced == NULL)
            {
                optMain->alarmBounced = new Alarmbounced();
            }
        }
        else if(msg->mode == VPLAY_STOP_CMD)
        {
            if(optMain->alarmBounced != NULL)
            {
                delete optMain->alarmBounced;
                optMain->alarmBounced = NULL;
            }
        }
        break;
        case UI_CLOCK:
        if(msg->mode ==MODE_RETURN)
        {
            optMain->clockTimemain_destory();
        }
        break;
        case UI_SETTING:
        if(msg->mode ==MODE_RETURN)
        {
            optMain->settingScenemain_destory();
        }
        break;
        case UI_LAUNCHER:
            if(msg->mode == MODE_UPDATA)
            {
                optMain->weather_show =true;
                optMain->lauTimecnt =145;
            }
        break;
        case UI_WEATHER:
            if(msg->mode ==MODE_RETURN)
            {
                optMain->weathermain_destory();
            }
            else if(msg->mode == MODE_UPDATA)
            {
                optMain->weatherMainUpdata();
            }
        break;
		case UI_DISK:
			if(msg->mode ==DISK_SD_ENTER)
			{
				if(access(SDCARD_OTA_PATCH, 0)==0)
				{
					optMain->start_ota_scene(SDCARD_OTA_PATCH);
				}
			}
			else if(msg->mode ==DISK_U_ENTER)
			{
				if(access(UDISK_OTA_PATCH, 0)==0)
				{
					optMain->start_ota_scene(UDISK_OTA_PATCH);
				}
			}
        break;
        default:
        break;
    }
}

void MainAPPStart::photomain_destory(void)
{
    if(optMain->photoScene !=NULL)
    {
        delete optMain->photoScene;
        optMain->photoScene =NULL;
    }
    optMain->laufuncallback();

}

void MainAPPStart::videoMain_destory(void)
{
    if(optMain->VideoMain !=NULL)
    {
        delete optMain->VideoMain;
        optMain->VideoMain =NULL;
    }
    optMain->laufuncallback();
}

void MainAPPStart::musiclist_destory(void)
{
    if(optMain->music_list !=NULL)
    {
        delete optMain->music_list;
        optMain->music_list =NULL;
    }
    optMain->laufuncallback();
}

void MainAPPStart::calendarmain_destory(void)
{
    if(optMain->calendar_main !=NULL)
    {
        delete optMain->calendar_main;
        optMain->calendar_main =NULL;
    }
    optMain->laufuncallback();
}

void MainAPPStart::weathermain_destory(void)
{
    if(optMain->weather_main !=NULL)
    {
        delete optMain->weather_main;
        optMain->weather_main =NULL;
    }
    optMain->laufuncallback();
}

void MainAPPStart::clockTimemain_destory(void)
{
    if(optMain->clockTime_main !=NULL)
    {
        delete optMain->clockTime_main;
        optMain->clockTime_main =NULL;
    }
    optMain->laufuncallback();
}

void MainAPPStart::alarmScenemain_destory(void)
{
    if(optMain->alarmScene_main !=NULL)
    {
        delete optMain->alarmScene_main;
        optMain->alarmScene_main =NULL;
    }
    optMain->laufuncallback();
}

void MainAPPStart::settingScenemain_destory(void)
{
    if(optMain->settingScene_main !=NULL)
    {
        delete optMain->settingScene_main;
        optMain->settingScene_main =NULL;
    }
    optMain->laufuncallback();
}

void MainAPPStart::delete_str(void)
{
    if(str_a != NULL)
    {
        delete str_a;
        str_a =NULL;
    }
    if(str_c != NULL)
    {
        delete str_c;
        str_c =NULL;
    }
    if(str_v != NULL)
    {
        delete str_v;
        str_v =NULL;
    }
    if(str_m != NULL)
    {
        delete str_m;
        str_m =NULL;
    }
    if(str_s != NULL)
    {
        delete str_s;
        str_s =NULL;
    }
    if(str_city != NULL)
    {
        delete str_city;
        str_city =NULL;
    }
    if(str_temp != NULL)
    {
        delete str_temp;
        str_temp =NULL;
    }
    if(str_name_year != NULL)
    {
        delete str_name_year;
        str_name_year =NULL;
    }
    if(str_name_month != NULL)
    {
        delete str_name_month;
        str_name_month =NULL;
    }
    if(str_name_day != NULL)
    {
        delete str_name_day;
        str_name_day =NULL;
    }
    if(str_cur_date != NULL)
    {
        delete str_cur_date;
        str_cur_date =NULL;
    }
    if(str_cur_year != NULL)
    {
        delete str_cur_year;
        str_cur_year =NULL;
    }
    if(str_cur_time != NULL)
    {
        delete str_cur_time;
        str_cur_time =NULL;
    }
    if(str_apm_time != NULL)
    {
        delete str_apm_time;
        str_apm_time =NULL;
    }
    if(str_one_week != NULL)
    {
        delete str_one_week;
        str_one_week =NULL;
    }
    if(str_tow_week != NULL)
    {
        delete str_tow_week;
        str_tow_week =NULL;
    }
    if(str_three_week != NULL)
    {
        delete str_three_week;
        str_three_week =NULL;
    }
    if(str_one_mintemp != NULL)
    {
        delete str_one_mintemp;
        str_one_mintemp =NULL;
    }
    if(str_one_maxtemp != NULL)
    {
        delete str_one_maxtemp;
        str_one_maxtemp =NULL;
    }
    if(str_tow_mintemp != NULL)
    {
        delete str_tow_mintemp;
        str_tow_mintemp =NULL;
    }
    if(str_tow_maxtemp != NULL)
    {
        delete str_tow_maxtemp;
        str_tow_maxtemp =NULL;
    }
    if(str_three_mintemp != NULL)
    {
        delete str_three_mintemp;
        str_three_mintemp =NULL;
    }
    if(str_three_maxtemp != NULL)
    {
        delete str_three_maxtemp;
        str_three_maxtemp =NULL;
    }
}

void MainAPPStart::delete_ui_free(void)
{
    if(objbtn_p_child1 != NULL)
    {
        delete objbtn_p_child1;
        objbtn_p_child1 =NULL;
    }
    if(objbtn_p_child2 != NULL)
    {
        delete objbtn_p_child2;
        objbtn_p_child2 =NULL;
    }
    if(objbtn_p_child3 != NULL)
    {
        delete objbtn_p_child3;
        objbtn_p_child3 =NULL;
    }
    if(objbtn_w_cur != NULL)
    {
        delete objbtn_w_cur;
        objbtn_w_cur =NULL;
    }
    if(objbtn_w_one != NULL)
    {
        delete objbtn_w_one;
        objbtn_w_one =NULL;
    }
    if(objbtn_w_tow != NULL)
    {
        delete objbtn_w_tow;
        objbtn_w_tow =NULL;
    }
    if(objbtn_w_three != NULL)
    {
        delete objbtn_w_three;
        objbtn_w_three =NULL;
    }
    if(objbtn_wifi_state != NULL)
    {
        delete objbtn_wifi_state;
        objbtn_wifi_state =NULL;
    }

    if(objbtn_p != NULL)
    {
        delete objbtn_p;
        objbtn_p =NULL;
    }
    if(objbtn_m != NULL)
    {
        delete objbtn_m;
        objbtn_m =NULL;
    }
    if(objbtn_v != NULL)
    {
        delete objbtn_v;
        objbtn_v =NULL;
    }
    if(objbtn_ca != NULL)
    {
        delete objbtn_ca;
        objbtn_ca =NULL;
    }
    if(objbtn_cl != NULL)
    {
        delete objbtn_cl;
        objbtn_cl =NULL;
    }
    if(objbtn_w != NULL)
    {
        delete objbtn_w;
        objbtn_w =NULL;
    }
    if(objbtn_s != NULL)
    {
        delete objbtn_s;
        objbtn_s =NULL;
    }
    if(objbtn_a != NULL)
    {
        delete objbtn_a;
        objbtn_a =NULL;
    }
    if(objbtn_ws != NULL)
    {
        delete objbtn_ws;
        objbtn_ws =NULL;
    }
}

LvcppButton* MainAPPStart::LvcppButtonChild(lv_obj_t* paren,int x,int y,int w,int h,void * ui_patch)
{
    LvcppButton* child_button =NULL;

    child_button = new LvcppButton(paren);
    child_button->set_size(w,h);
    child_button->align_to(paren,LV_ALIGN_TOP_LEFT,x,y);
    child_button->set_main_bg_color(lv_color_white(),LV_OPA_0);
    child_button->set_main_radius(0);
    child_button->set_main_pad_all(0);
    child_button->set_main_border_width(0);
    child_button->set_main_bg_img_src(ui_patch);
    child_button->set_userdata(NULL);
    child_button->add_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
    return child_button;
}

LvcppLabel* MainAPPStart::LvcppLabelViewChild(lv_obj_t* paren,int x,int y,int w,int h,lv_align_t align,int str_color,char * str_buff)
{
    LvcppLabel* childView =NULL;

    childView = new LvcppLabel(paren);
    childView->set_size(w,h);
    childView->align_to(paren,LV_ALIGN_TOP_LEFT, x, y);
    childView->txt_font_size(h-6, FT_FONT_STYLE_NORMAL);
    childView->txt_align(align);
    childView->txt_color(lv_color_hex(str_color),LV_PART_MAIN);
    childView->set_txt(str_buff);
    return childView;
}

void MainAPPStart::Lvcpp_txt(LvcppLabel* parenView,char* str_buff)
{
    if((parenView ==NULL)||(str_buff ==NULL))
		return;
    parenView->set_txt(str_buff);
}

void MainAPPStart::Lvcpp_bg_img(LvcppButton* parenButton,void* pic_patch)
{
    if((parenButton ==NULL)||(pic_patch ==NULL))
		return;
    parenButton->set_main_bg_img_src(pic_patch);
}

LvcppButton* MainAPPStart::LvcppButtonIcon(lv_obj_t* paren,int x,int y,int w,int h,int icon,void *ui_patch)
{
    LvcppButton* Icon_button =NULL;

    Icon_button = new LvcppButton(paren);
    Icon_button->set_size(w,h);
    Icon_button->set_pos(x,y);
    Icon_button->set_main_bg_color(lv_color_white(),LV_OPA_0);
    Icon_button->set_main_radius(0);
    Icon_button->set_main_pad_all(0);
    Icon_button->set_main_border_width(0);
    Icon_button->set_main_bg_img_src(ui_patch);
    Icon_button->set_main_align(LV_ALIGN_TOP_LEFT);
    Icon_button->set_userdata(NULL);
    Icon_button->set_userdata((void*)icon);
    Icon_button->add_event_cb(main_event_handler,LV_EVENT_PRESSED,this);
    Icon_button->add_event_cb(main_event_handler,LV_EVENT_RELEASED,this);
    return Icon_button;
}

void* MainAPPStart::getCurWifiState(int wifi_ind)
{
    char* wifi_str =NULL;

    switch(wifi_ind)
    {
        case 0:
            wifi_str = (char*)HEAD_WIFI0_PNG;
        break;
        case 1:
            wifi_str = (char*)HEAD_WIFI1_PNG;
        break;
        case 2:
            wifi_str = (char*)HEAD_WIFI2_PNG;
        break;
        case 3:
            wifi_str = (char*)HEAD_WIFI3_PNG;
        break;
        case 4:
            wifi_str = (char*)HEAD_WIFI4_PNG;
        break;
        default:
            wifi_str = (char*)HEAD_WIFINO_PNG;
            break;
    }
    return wifi_str;
}

char* MainAPPStart::getCurWeekStr(int week)
{
    char* week_str =NULL;

    switch(week)
    {
        case 0:
            week_str = (char*)STR_SUNDAY;
        break;
        case 1:
            week_str = (char*)STR_MONDAY;
        break;
        case 2:
            week_str = (char*)STR_TUESDAY;
        break;
        case 3:
            week_str = (char*)STR_WEDNESDAY;
        break;
        case 4:
            week_str = (char*)STR_THURSDAY;
        break;
        case 5:
            week_str = (char*)STR_FRIDAY;
        break;
        case 6:
            week_str = (char*)STR_SATURDAY;
        break;
        default:
        break;
    }
    return week_str;
}

void MainAPPStart::show_weather(void)
{
    if(weather_show !=true)
    {
        objbtn_w_cur->show(false);
        str_city->show(false);
        str_temp->show(false);
        objbtn_w_one->show(false);
        objbtn_w_tow->show(false);
        objbtn_w_three->show(false);
        str_one_week->show(false);
        str_tow_week->show(false);
        str_three_week->show(false);
        str_one_mintemp->show(false);
        str_one_maxtemp->show(false);
        str_tow_mintemp->show(false);
        str_tow_maxtemp->show(false);
        str_three_mintemp->show(false);
        str_three_maxtemp->show(false);
    }
    else
    {
        objbtn_ws->add_txt("");
        objbtn_ws->set_main_bg_img_src(SCREEN_LAUWEATHER_BG_PNG);
        objbtn_w_cur->show(true);
        str_city->show(true);
        str_temp->show(true);
        objbtn_w_one->show(true);
        objbtn_w_tow->show(true);
        objbtn_w_three->show(true);
        str_one_week->show(true);
        str_tow_week->show(true);
        str_three_week->show(true);
        str_one_mintemp->show(true);
        str_one_maxtemp->show(true);
        str_tow_mintemp->show(true);
        str_tow_maxtemp->show(true);
        str_three_mintemp->show(true);
        str_three_maxtemp->show(true);
    }
}

void MainAPPStart::draw_scene_desktop(void)
{
    WifiHeadStr = getCurWifiState(cur_wifi_state);
    objbtn_wifi_state = LvcppButtonChild(m_parent,1190,10,58,58,WifiHeadStr);
    #ifdef IMAGE_DECODE
    objbtn_p = LvcppButtonIcon(m_parent,30,100,692,354,MAIN_DESKTOP_PHOTO,SCREEN_LAUPHOTO_PNG);
    objbtn_p_child1 = LvcppButtonChild(objbtn_p->myobj,8,8,220,166,SCREEN_LAUPHOTO1_PNG);
    objbtn_p_child2 = LvcppButtonChild(objbtn_p->myobj,8,181,220,166,SCREEN_LAUPHOTO2_PNG);
    objbtn_p_child3 = LvcppButtonChild(objbtn_p->myobj,235,8,450,338,SCREEN_LAUPHOTO3_PNG);
    objbtn_w = LvcppButtonIcon(m_parent,730,100,260,221,MAIN_DESKTOP_WEATHER,SCREEN_LAUWEATHER_PNG);
    objbtn_w_cur = LvcppButtonChild(objbtn_w->myobj,70,50,120,120,WEWATHER_BIG01_PNG);
    #else
    objbtn_p = LvcppButtonIcon(m_parent,30,100,692,354,MAIN_DESKTOP_PHOTO,(char*)SCREEN_LAUPHOTO_PNG);
    memset(photo1_patch,0,1024);
    strcpy(photo1_patch,(char*)SCREEN_LAUPHOTO1_PNG);
    memset(photo2_patch,0,1024);
    strcpy(photo2_patch,(char*)SCREEN_LAUPHOTO2_PNG);
    memset(photo3_patch,0,1024);
    strcpy(photo3_patch,(char*)SCREEN_LAUPHOTO3_PNG);
    objbtn_p_child1 = LvcppButtonChild(objbtn_p->myobj,8,8,220,166,(char *)photo1_patch);
    objbtn_p_child2 = LvcppButtonChild(objbtn_p->myobj,8,181,220,166,(char *)photo2_patch);
    objbtn_p_child3 = LvcppButtonChild(objbtn_p->myobj,235,8,450,338,(char *)photo3_patch);
    objbtn_w = LvcppButtonIcon(m_parent,730,100,260,221,MAIN_DESKTOP_WEATHER,(char*)SCREEN_LAUWEATHER_PNG);
    objbtn_w_cur = LvcppButtonChild(objbtn_w->myobj,70,50,120,120,(char *)WEWATHER_BIG00_PNG);
    #endif
    memset(datetime_buff,0,256);
    sprintf(datetime_buff,"%s","Shenzhen");
    str_city = LvcppLabelViewChild(objbtn_w->myobj,34,10,190,34,LV_ALIGN_TOP_LEFT,WHITE_COLOR,(char *)datetime_buff);
    memset(datetime_buff,0,256);
    sprintf(datetime_buff,"%s %.1f%s",curWeatherInfo.weinfo,curWeatherInfo.temp,STR_TEMP_C);
    str_temp = LvcppLabelViewChild(objbtn_w->myobj,6,170,245,34,LV_ALIGN_TOP_MID,WHITE_COLOR,(char *)datetime_buff);
    str_temp->txt_align(LV_TEXT_ALIGN_CENTER);
    str_temp->txt_long_mode(LV_LABEL_LONG_SCROLL_CIRCULAR);
    if(weather_show !=true)
    {
        objbtn_w_cur->show(false);
        str_city->show(false);
        str_temp->show(false);
    }
    #ifdef IMAGE_DECODE
    objbtn_ca = LvcppButtonIcon(m_parent,990,100,258,221,MAIN_DESKTOP_CALENDAR,SCREEN_LAUCALENDAR_PNG);
    #else
    objbtn_ca = LvcppButtonIcon(m_parent,990,100,258,221,MAIN_DESKTOP_CALENDAR,(char*)SCREEN_LAUCALENDAR_PNG);
    #endif

    str_name_year = LvcppLabelViewChild(objbtn_ca->myobj,18,122,245,30,LV_ALIGN_TOP_LEFT,WHITE_COLOR,(char *)STR_YEAR);
    str_name_month = LvcppLabelViewChild(objbtn_ca->myobj,18,63,70,30,LV_ALIGN_TOP_LEFT,WHITE_COLOR,(char *)STR_MONTH);
    str_name_day = LvcppLabelViewChild(objbtn_ca->myobj,108,63,70,30,LV_ALIGN_TOP_LEFT,WHITE_COLOR,(char *)STR_DAY);
    memset(datetime_buff,0,256);
    sprintf(datetime_buff,"%.2d/%.2d",cur_month,cur_day);
    str_cur_date = LvcppLabelViewChild(objbtn_ca->myobj,18,0,245,66,LV_ALIGN_TOP_LEFT,WHITE_COLOR,(char *)datetime_buff);
    memset(datetime_buff,0,256);
    sprintf(datetime_buff,"%.4d",cur_year);
    str_cur_year = LvcppLabelViewChild(objbtn_ca->myobj,18,91,245,36,LV_ALIGN_TOP_LEFT,WHITE_COLOR,(char *)datetime_buff);
    memset(datetime_buff,0,256);
    sprintf(datetime_buff,"%.2d:%.2d",cur_hours,cur_mintes);
    str_cur_time = LvcppLabelViewChild(objbtn_ca->myobj,18,140,245,66,LV_ALIGN_TOP_LEFT,WHITE_COLOR,(char *)datetime_buff);

    if(apm_status ==true)
    {
        memset(datetime_buff,0,256);
        if(cur_hours >=12)
        {
            sprintf(datetime_buff,"%s",STR_TEMP_PM);
        }
        else
        {
            sprintf(datetime_buff,"%s",STR_TEMP_AM);
        }
        str_apm_time = LvcppLabelViewChild(objbtn_ca->myobj,175,170,245,36,LV_ALIGN_TOP_LEFT,WHITE_COLOR,(char *)datetime_buff);
    }

#ifdef IMAGE_DECODE
    objbtn_ws = LvcppButtonIcon(m_parent,730,321,518,133,MAIN_DESKTOP_WEATHER,SCREEN_LAUWEATHER_NO_BG_PNG);
    objbtn_ws->add_txt(STR_NO_WEATHER);
    objbtn_ws->txt_size(498,133,LV_LABEL_LONG_WRAP);
    objbtn_ws->txt_align(LV_ALIGN_BOTTOM_MID,10,0);
    objbtn_ws->txt_font_size(26,0);
    objbtn_ws->txt_color(lv_color_white());

    objbtn_w_one = LvcppButtonChild(objbtn_ws->myobj,4,30,90,90,WEWATHER_SMALL01_PNG);
    objbtn_w_tow = LvcppButtonChild(objbtn_ws->myobj,178,30,90,90,WEWATHER_SMALL02_PNG);
    objbtn_w_three = LvcppButtonChild(objbtn_ws->myobj,350,30,90,90,WEWATHER_SMALL03_PNG);
#else
    objbtn_ws = LvcppButtonIcon(m_parent,730,321,518,133,MAIN_DESKTOP_WEATHER,(char*)SCREEN_LAUWEATHER_NO_BG_PNG);
    objbtn_ws->add_txt(STR_NO_WEATHER);
    objbtn_ws->txt_size(498,133,LV_LABEL_LONG_WRAP);
    objbtn_ws->txt_align(LV_ALIGN_BOTTOM_MID,10,0);
    objbtn_ws->txt_font_size(26,0);
    objbtn_ws->txt_color(lv_color_white());

    objbtn_w_one = LvcppButtonChild(objbtn_ws->myobj,4,30,90,90,(char *)WEWATHER_SMALL00_PNG);
    objbtn_w_tow = LvcppButtonChild(objbtn_ws->myobj,178,30,90,90,(char *)WEWATHER_SMALL00_PNG);
    objbtn_w_three = LvcppButtonChild(objbtn_ws->myobj,350,30,90,90,(char *)WEWATHER_SMALL00_PNG);
#endif

    WeekStrOne =getCurWeekStr(oneWeatherInfo.week);
    str_one_week = LvcppLabelViewChild(objbtn_ws->myobj,5,5,160,30,LV_ALIGN_TOP_LEFT,WHITE_COLOR,(char *)WeekStrOne);
    WeekStrTow =getCurWeekStr(towWeatherInfo.week);
    str_tow_week = LvcppLabelViewChild(objbtn_ws->myobj,178,5,160,30,LV_ALIGN_TOP_LEFT,WHITE_COLOR,(char *)WeekStrTow);
    WeekStrThree =getCurWeekStr(threeWeatherInfo.week);
    str_three_week = LvcppLabelViewChild(objbtn_ws->myobj,350,5,160,30,LV_ALIGN_TOP_LEFT,WHITE_COLOR,(char *)WeekStrThree);
    str_one_mintemp = LvcppLabelViewChild(objbtn_ws->myobj,95,50,65,26,LV_ALIGN_TOP_LEFT,WHITE_COLOR,(char *)weather_buff);
    str_one_maxtemp = LvcppLabelViewChild(objbtn_ws->myobj,95,80,65,26,LV_ALIGN_TOP_LEFT,WHITE_COLOR,(char *)weather_buff);
    str_tow_mintemp = LvcppLabelViewChild(objbtn_ws->myobj,270,50,65,26,LV_ALIGN_TOP_LEFT,WHITE_COLOR,(char *)weather_buff);
    str_tow_maxtemp = LvcppLabelViewChild(objbtn_ws->myobj,270,80,65,26,LV_ALIGN_TOP_LEFT,WHITE_COLOR,(char *)weather_buff);
    str_three_mintemp = LvcppLabelViewChild(objbtn_ws->myobj,445,50,65,26,LV_ALIGN_TOP_LEFT,WHITE_COLOR,(char *)weather_buff);
    str_three_maxtemp = LvcppLabelViewChild(objbtn_ws->myobj,445,80,65,26,LV_ALIGN_TOP_LEFT,WHITE_COLOR,(char *)weather_buff);

    show_weather();

#ifdef IMAGE_DECODE
    objbtn_a = LvcppButtonIcon(m_parent,30,464,233,236,MAIN_DESKTOP_ALARM,SCREEN_LAUALARM_PNG);
    str_a = LvcppLabelViewChild(objbtn_a->myobj,0,130,233,36,LV_ALIGN_TOP_MID,WHITE_COLOR,(char *)STR_ALARM);

    objbtn_cl = LvcppButtonIcon(m_parent,273,464,233,236,MAIN_DESKTOP_CLOCK,SCREEN_LAUCLOCK_PNG);
    str_c = LvcppLabelViewChild(objbtn_cl->myobj,0,130,233,36,LV_ALIGN_TOP_MID,WHITE_COLOR,(char *)STR_CLOCK);

    objbtn_v = LvcppButtonIcon(m_parent,516,464,240,236,MAIN_DESKTOP_VIDEO,SCREEN_LAUVIDEO_PNG);
    str_v = LvcppLabelViewChild(objbtn_v->myobj,0,130,233,36,LV_ALIGN_TOP_MID,WHITE_COLOR,(char *)STR_VIDEO);

    objbtn_m = LvcppButtonIcon(m_parent,766,464,240,236,MAIN_DESKTOP_MUSIC,SCREEN_LAUMUSIC_PNG);
    str_m = LvcppLabelViewChild(objbtn_m->myobj,0,130,233,36,LV_ALIGN_TOP_MID,WHITE_COLOR,(char *)STR_MUSIC);

    objbtn_s = LvcppButtonIcon(m_parent,1016,464,233,236,MAIN_DESKTOP_SETTING,SCREEN_LAUSETTING_PNG);
    str_s = LvcppLabelViewChild(objbtn_s->myobj,0,130,233,36,LV_ALIGN_TOP_MID,WHITE_COLOR,(char *)STR_SETTING);
#else
    objbtn_a = LvcppButtonIcon(m_parent,30,464,233,236,MAIN_DESKTOP_ALARM,(char*)SCREEN_LAUALARM_PNG);
    str_a = LvcppLabelViewChild(objbtn_a->myobj,0,130,233,36,LV_ALIGN_TOP_MID,WHITE_COLOR,(char *)STR_ALARM);

    objbtn_cl = LvcppButtonIcon(m_parent,273,464,233,236,MAIN_DESKTOP_CLOCK,(char*)SCREEN_LAUCLOCK_PNG);
    str_c = LvcppLabelViewChild(objbtn_cl->myobj,0,130,233,36,LV_ALIGN_TOP_MID,WHITE_COLOR,(char *)STR_CLOCK);

    objbtn_v = LvcppButtonIcon(m_parent,516,464,240,236,MAIN_DESKTOP_VIDEO,(char*)SCREEN_LAUVIDEO_PNG);
    str_v = LvcppLabelViewChild(objbtn_v->myobj,0,130,233,36,LV_ALIGN_TOP_MID,WHITE_COLOR,(char *)STR_VIDEO);

    objbtn_m = LvcppButtonIcon(m_parent,766,464,240,236,MAIN_DESKTOP_MUSIC,(char*)SCREEN_LAUMUSIC_PNG);
    str_m = LvcppLabelViewChild(objbtn_m->myobj,0,130,233,36,LV_ALIGN_TOP_MID,WHITE_COLOR,(char *)STR_MUSIC);

    objbtn_s = LvcppButtonIcon(m_parent,1016,464,233,236,MAIN_DESKTOP_SETTING,(char*)SCREEN_LAUSETTING_PNG);
    str_s = LvcppLabelViewChild(objbtn_s->myobj,0,130,233,36,LV_ALIGN_TOP_MID,WHITE_COLOR,(char *)STR_SETTING);
#endif

    if(file_total >0)
    {
        play_next_file();
    }
}

void MainAPPStart::draw_weather_scene(void)
{
#ifdef _UCHIP_T113
	sunxi_image_init();
#endif	
    char weaPatch[64]={0};

    if((weather_show !=true)&&(show_status !=true))
        return;
    httpStart->get_cur_weather(&curWeatherInfo);
    httpStart->get_first_weather(&oneWeatherInfo);
    httpStart->get_second_weather(&towWeatherInfo);
    httpStart->get_three_weather(&threeWeatherInfo);

    memset(datetime_buff,0,256);
    sprintf(datetime_buff,"%s","Shenzhen");
	Lvcpp_txt(str_city,datetime_buff);

    memset(datetime_buff,0,256);
    sprintf(datetime_buff,"%s %.1f%s",curWeatherInfo.weinfo,curWeatherInfo.temp,STR_TEMP_C);
    Lvcpp_txt(str_temp,datetime_buff);

    memset(weather_buff,0,64);
    sprintf(weather_buff,"%.1f%s",oneWeatherInfo.temp_min,STR_TEMP_C);
    Lvcpp_txt(str_one_mintemp,weather_buff);

    memset(weather_buff,0,64);
    sprintf(weather_buff,"%.1f%s",oneWeatherInfo.temp_max,STR_TEMP_C);
    Lvcpp_txt(str_one_maxtemp,weather_buff);

    memset(weather_buff,0,64);
    sprintf(weather_buff,"%.1f%s",towWeatherInfo.temp_min,STR_TEMP_C);
    Lvcpp_txt(str_tow_mintemp,weather_buff);

    memset(weather_buff,0,64);
    sprintf(weather_buff,"%.1f%s",towWeatherInfo.temp_max,STR_TEMP_C);
    Lvcpp_txt(str_tow_maxtemp,weather_buff);

    memset(weather_buff,0,64);
    sprintf(weather_buff,"%.1f%s",threeWeatherInfo.temp_min,STR_TEMP_C);
    Lvcpp_txt(str_three_mintemp,weather_buff);

    memset(weather_buff,0,64);
    sprintf(weather_buff,"%.1f%s",threeWeatherInfo.temp_max,STR_TEMP_C);
    Lvcpp_txt(str_three_maxtemp,weather_buff);

    WeekStrOne =getCurWeekStr(oneWeatherInfo.week);
    if(WeekStrOne !=NULL)
        Lvcpp_txt(str_one_week,WeekStrOne);

    WeekStrTow =getCurWeekStr(towWeatherInfo.week);
    if(WeekStrTow !=NULL)
        Lvcpp_txt(str_tow_week,WeekStrTow);

    WeekStrThree =getCurWeekStr(threeWeatherInfo.week);
    if(WeekStrThree !=NULL)
        Lvcpp_txt(str_three_week,WeekStrThree);
#ifdef _UCHIP_T113
    if(WEWATHER_BIG01_PNG!=NULL)
    {
        sunxi_image_free(WEWATHER_BIG01_PNG);
        WEWATHER_BIG01_PNG =NULL;
    }
    memset(weaPatch,0,64);
    sprintf(weaPatch,"%s%s.png",WEATHER_PATCH,curWeatherInfo.icon);
    if(access(weaPatch, F_OK) == 0)
    {
        if(objbtn_w_cur !=NULL)
        {
            WEWATHER_BIG01_PNG=(void*)sunxi_image_decode_scaler(weaPatch,objbtn_w_cur->width(),objbtn_w_cur->height());
            Lvcpp_bg_img(objbtn_w_cur,WEWATHER_BIG01_PNG);
        }
    }
    if(WEWATHER_SMALL01_PNG!=NULL)
    {
        sunxi_image_free(WEWATHER_SMALL01_PNG);
        WEWATHER_SMALL01_PNG =NULL;
    }
    memset(weaPatch,0,64);
    sprintf(weaPatch,"%s%s.png",WEATHER_PATCH,oneWeatherInfo.icon);
    if(access(weaPatch, F_OK) == 0)
    {
        if(objbtn_w_one !=NULL)
        {
            WEWATHER_SMALL01_PNG=(void*)sunxi_image_decode_scaler(weaPatch,objbtn_w_one->width(),objbtn_w_one->height());
            Lvcpp_bg_img(objbtn_w_one,WEWATHER_SMALL01_PNG);
        }
    }
    if(WEWATHER_SMALL02_PNG!=NULL)
    {
        sunxi_image_free(WEWATHER_SMALL02_PNG);
        WEWATHER_SMALL02_PNG =NULL;
    }
    memset(weaPatch,0,64);
    sprintf(weaPatch,"%s%s.png",WEATHER_PATCH,towWeatherInfo.icon);
    if(access(weaPatch, F_OK) == 0)
    {
        if(objbtn_w_tow !=NULL)
        {
            WEWATHER_SMALL02_PNG=(void*)sunxi_image_decode_scaler(weaPatch,objbtn_w_tow->width(),objbtn_w_tow->height());
            Lvcpp_bg_img(objbtn_w_tow,WEWATHER_SMALL02_PNG);
        }
    }
    if(WEWATHER_SMALL03_PNG!=NULL)
    {
        sunxi_image_free(WEWATHER_SMALL03_PNG);
        WEWATHER_SMALL03_PNG =NULL;
    }
    memset(weaPatch,0,64);
    sprintf(weaPatch,"%s%s.png",WEATHER_PATCH,threeWeatherInfo.icon);
    if(access(weaPatch, F_OK) == 0)
    {
        if(objbtn_w_three !=NULL)
        {
            WEWATHER_SMALL03_PNG=(void*)sunxi_image_decode_scaler(weaPatch,objbtn_w_three->width(),objbtn_w_three->height());
            Lvcpp_bg_img(objbtn_w_three,WEWATHER_SMALL03_PNG);
        }
    }
#endif	
#ifdef _UCHIP_T113
	sunxi_image_exit();
#endif	
}

void MainAPPStart::draw_calendar_scene(void)
{
    SYSDateTime gettime;
    user_time = gettime.current_datetime();

    cur_year = user_time.year;
    cur_month = user_time.month;
    cur_day = user_time.day;
    cur_hours = user_time.hour;
    cur_mintes = user_time.minute;

    WifiHeadStr = getCurWifiState(cur_wifi_state);
    Lvcpp_bg_img(objbtn_wifi_state,WifiHeadStr);

    memset(datetime_buff,0,256);
    sprintf(datetime_buff,"%.2d/%.2d",cur_month,cur_day);
	Lvcpp_txt(str_cur_date,datetime_buff);

    memset(datetime_buff,0,256);
    sprintf(datetime_buff,"%.4d",cur_year);
	Lvcpp_txt(str_cur_year,datetime_buff);

    memset(datetime_buff,0,256);
    sprintf(datetime_buff,"%.2d:%.2d",cur_hours,cur_mintes);
	Lvcpp_txt(str_cur_time,datetime_buff);

    if(apm_status ==true)
    {
        memset(datetime_buff,0,256);
        if(cur_hours >=12)
        {
            sprintf(datetime_buff,"%s",STR_TEMP_PM);
        }
        else
        {
            sprintf(datetime_buff,"%s",STR_TEMP_AM);
        }
		Lvcpp_txt(str_apm_time,datetime_buff);
    }
}

void MainAPPStart::main_event_handler(lv_event_t *event)
{
    MainAPPStart* opt = (MainAPPStart*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    lv_obj_t* cont = lv_event_get_current_target(event);
    int set_selete = (uintptr_t)target->user_data;

    if(cont != target)
    {
        set_selete = (uintptr_t)cont->user_data;
    }
    //LV_LOG_USER("set_selete:%d",set_selete);
    if(event->code== LV_EVENT_RELEASED)
    {
        switch(set_selete)
        {
            case MAIN_DESKTOP_PHOTO:
                opt->enter_photoList_app();
            break;
            case MAIN_DESKTOP_WEATHER:
                opt->enter_weatherScene_app();
            break;
            case MAIN_DESKTOP_CALENDAR:
                opt->enter_calendarScene_app();
            break;
            case MAIN_DESKTOP_ALARM:
                opt->enter_alarmScene_app();
            break;
            case MAIN_DESKTOP_CLOCK:
                opt->enter_clockScene_app();
            break;
            case MAIN_DESKTOP_VIDEO:
                opt->enter_videolist_app();
            break;
            case MAIN_DESKTOP_MUSIC:
                opt->enter_musicScene_app();
            break;
            case MAIN_DESKTOP_SETTING:
                opt->enter_settingScene_app();
            break;
            default:
            break;
        }
        if(set_selete>MAIN_DESKTOP && set_selete<MAIN_DESKTOP_MAX)
        {
            optMain->main_deinitial();
        }
    }
}

void MainAPPStart::play_next_file(void)
{
    file_inde ++;
    if(file_inde >file_total)
    {
        file_inde =1;
    }
    memset(cur_photo_patch,0,1024);
    switch (file_inde)
    {
        case 0:
            //strcpy(cur_photo_patch,(char*)PHOTO_PNG);
        break;
        default:
            break;
    }
    if(win_inde ==0)
    {
        memset(photo1_patch,0,1024);
        strcpy(photo1_patch,cur_photo_patch);
        objbtn_p_child1->set_main_bg_img_src(SCREEN_LAUPHOTO1_PNG); //photo1_patch
    }
    else if(win_inde ==1)
    {
        memset(photo2_patch,0,1024);
        strcpy(photo2_patch,cur_photo_patch);
        objbtn_p_child2->set_main_bg_img_src(SCREEN_LAUPHOTO2_PNG); //photo2_patch
    }
    else
    {
        memset(photo3_patch,0,1024);
        strcpy(photo3_patch,cur_photo_patch);
        objbtn_p_child3->set_main_bg_img_src(SCREEN_LAUPHOTO3_PNG); //photo3_patch
    }
    win_inde ++;
    if(win_inde >2)
        win_inde =0;
}
