#include  "../mainappstart.h"
#include "weather.h"
#include  "lvgl/src/extra/lv_extra.h"
#include  "mainstart/include/ui_config.h"
#include  "mainstart/include/str_config.h"

#ifdef _UCHIP_T113
#define WEATHER_PATCH  "/usr/bin/resource/image/weathericon/"
#else
#define WEATHER_PATCH  "S:/resource/image/weathericon/"
#endif

void Weather::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    HEAD_RETURN_PNG=(void*)parse_image_from_file(HEAD_RETURN_PNG_PATH);
    HEAD_RETURN_SEL_PNG=(void*)parse_image_from_file(HEAD_RETURN_SEL_PNG_PATH);

    HEAD_ICON_WEATHER_PNG=(void*)parse_image_from_file(HEAD_ICON_WEATHER_PNG_PATH);

    LISTBG_PNG=(void*)parse_image_from_file(LISTBG_PNG_PATH);

    WEATHER_UNADD_PNG=(void*)parse_image_from_file(WEATHER_UNADD_PNG_PATH);
    WEATHER_ADD_PNG=(void*)parse_image_from_file(WEATHER_ADD_PNG_PATH);
    WEATHER_BIG_PNG=(void*)parse_image_from_file(WEATHER_BIG_PNG_PATH);
    WEATHER_MODE_PNG=(void*)parse_image_from_file(WEATHER_MODE_PNG_PATH);
    WEATHER_MODEB_PNG=(void*)parse_image_from_file(WEATHER_MODE_PNG_PATH);
#endif
}

void Weather::ui_image_free(void)
{
#ifdef IMAGE_DECODE
    if(HEAD_RETURN_PNG !=NULL)
    {
    	free_image(HEAD_RETURN_PNG);
        HEAD_RETURN_PNG =NULL;
    }
    if(HEAD_RETURN_SEL_PNG !=NULL)
    {
    	free_image(HEAD_RETURN_SEL_PNG);
        HEAD_RETURN_SEL_PNG =NULL;
    }
    if(HEAD_ICON_WEATHER_PNG !=NULL)
    {
    	free_image(HEAD_ICON_WEATHER_PNG);
        HEAD_ICON_WEATHER_PNG =NULL;
    }
    if(LISTBG_PNG !=NULL)
    {
    	free_image(LISTBG_PNG);
        LISTBG_PNG =NULL;
    }
    if(WEATHER_UNADD_PNG !=NULL)
    {
    	free_image(WEATHER_UNADD_PNG);
        WEATHER_UNADD_PNG =NULL;
    }
    if(WEATHER_ADD_PNG !=NULL)
    {
    	free_image(WEATHER_ADD_PNG);
        WEATHER_ADD_PNG =NULL;
    }
    if(WEATHER_BIG_PNG !=NULL)
    {
    	free_image(WEATHER_BIG_PNG);
        WEATHER_BIG_PNG =NULL;
    }
    if(WEATHER_MODE_PNG !=NULL)
    {
    	free_image(WEATHER_MODE_PNG);
        WEATHER_MODE_PNG =NULL;
    }
    if(WEATHER_MODEB_PNG !=NULL)
    {
		free_image(WEATHER_MODEB_PNG);
        WEATHER_MODEB_PNG =NULL;
    }
#endif
}

Weather::Weather(lv_obj_t* parent,Http *weaHttp)
{
#ifdef _UCHIP_T113
	sunxi_image_init();
#endif	
    ui_image_decode();
    frame = new LvcppScreen(parent);
    frame->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    frame->set_main_bg_color(lv_color_black(),LV_OPA_0);
    frame->set_main_bg_img_src(LISTBG_PNG);
    mainscreen = frame->myobj;
    memset(&curWeatherInfo,0,sizeof(weather_info_t));
    memset(&oneWeatherInfo,0,sizeof(weather_info_t));
    memset(&towWeatherInfo,0,sizeof(weather_info_t));
    memset(&threeWeatherInfo,0,sizeof(weather_info_t));
    if(weaHttp !=NULL)
    {
        weaHttp->set_msg_type(UI_WEATHER);
    }
    weaInfo = weaHttp;
    get_weather_scene_info();
    if(weathertimer == NULL)
    {
        weathertimer = startTimer(1000, this);
    }
}

Weather::~Weather(void)
{
    weater_head_dele();
    Weather_scene_dele();
    Weather_citylist_head_destory();
    if(frame !=NULL)
    {
        delete frame;
        frame =NULL;
        lv_obj_clear_flag(lv_scr_act(), LV_OBJ_FLAG_CLICKABLE);
    }
    ui_image_free();
#ifdef _UCHIP_T113
	sunxi_image_exit();
#endif	
}

void Weather::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    static int timecnt = 0;
    timecnt++;
    if((timecnt%60)==0)
    {
        get_weather_scene_info();
        Weather_scene_draw();
    }
    if((timecnt%300)==0)
    {
        wifi_data_t wifi;
        get_wifi_data(&wifi);
        if(wifi.is_connected)
        {
            if(weaInfo !=NULL)
            {
                weaInfo->Http_get_weather();
            }
        }
    }

}

LvcppButton* Weather::LvcppButtonHead(lv_obj_t* paren,bool show_cb,lv_ui_inof_t *uiInfo)
{
    LvcppButton* child_button =NULL;

    child_button = new LvcppButton(paren);
    child_button->set_size(uiInfo->w,uiInfo->h);
    child_button->align_to(paren,LV_ALIGN_TOP_LEFT,uiInfo->x,uiInfo->y);
    child_button->set_main_bg_opa(LV_OPA_0);
    child_button->set_main_radius(0);
    child_button->set_main_pad_all(0);
    child_button->set_main_border_width(0);
    child_button->set_main_bg_img_src(uiInfo->ui_patch);
    child_button->add_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
    child_button->set_userdata(NULL);
    if(show_cb ==true)
    {
        child_button->set_userdata((void*)uiInfo->userdata);
        child_button->add_event_cb(head_event_handler,LV_EVENT_PRESSED,this);
        child_button->add_event_cb(head_event_handler,LV_EVENT_RELEASED,this);
    }
    return child_button;
}
void Weather::Lvcpp_Head_img(LvcppButton* parenButton,void* pic_patch)
{
    if((parenButton ==NULL)||(pic_patch ==NULL))
        return;
    parenButton->set_main_bg_img_src(pic_patch);
}

LvcppLabel* Weather::LvcppLabelViewChild(lv_obj_t* paren,lv_text_align_t align,lv_str_inof_t *strInfo)
{
    LvcppLabel* childView =NULL;

    childView = new LvcppLabel(paren);
    childView->set_size(strInfo->w,strInfo->h);
    childView->align_to(paren,LV_ALIGN_TOP_LEFT, strInfo->x, strInfo->y);
    childView->txt_font_size(strInfo->h-6, FT_FONT_STYLE_NORMAL);
    childView->txt_align(align);
    childView->txt_color(lv_color_hex(strInfo->str_color),LV_PART_MAIN);
    childView->set_txt(strInfo->str_buff);
    return childView;
}

char* Weather::calendar_get_week(int week)
{
    char *curWeek =NULL;

    switch(week)
    {
        case 0:
            curWeek = (char*)STR_SUNDAY;
        break;
        case 1:
            curWeek = (char*)STR_MONDAY;
        break;
        case 2:
            curWeek = (char*)STR_TUESDAY;
        break;
        case 3:
            curWeek = (char*)STR_WEDNESDAY;
        break;
        case 4:
            curWeek = (char*)STR_THURSDAY;
        break;
        case 5:
            curWeek = (char*)STR_FRIDAY;
        break;
        case 6:
            curWeek = (char*)STR_SATURDAY;
        break;
        default:
        break;
    }
    return curWeek;
}

void Weather::get_weather_CurInfo(float temp,char *curtemp)
{
    double temp_f=0;

    if(TempTpye !=true)
    {
        sprintf(curtemp,"%.1f%s",temp,STR_TEMP_C);
    }
    else
    {
        temp_f = (double)(temp*1.8);
        temp_f = (double)(temp_f+32);
        sprintf(curtemp,"%.1f%s",temp_f,STR_TEMP_F);
    }
}

void Weather::get_weather_MaxMinInfo(float MinTemp,float MaxTemp,char *curtemp)
{
    double tempMin_f=0;
    double tempMax_f=0;

    if(TempTpye !=true)
    {
        sprintf(curtemp,"%.1f~%.1f%s",MinTemp,MaxTemp,STR_TEMP_C);
    }
    else
    {
        tempMin_f = (double)(MinTemp*1.8);
        tempMin_f = (double)(tempMin_f+32);
        tempMax_f = (double)(MaxTemp*1.8);
        tempMax_f = (double)(tempMax_f+32);
        sprintf(curtemp,"%.1f~%.1f%s",tempMin_f,tempMax_f,STR_TEMP_F);
    }
}

void Weather::get_weather_CheckInfo(void)
{
    if(TempTpye ==true)
    {
        TempCheck1->set_main_bg_opa(LV_OPA_0);
        TempCheck1->txt_color(lv_color_hex(0xffffff));
        TempCheck2->set_main_bg_opa(LV_OPA_100);
        TempCheck2->txt_color(lv_color_hex(0xa7d4));
    }
    else
    {
        TempCheck1->set_main_bg_opa(LV_OPA_100);
        TempCheck1->txt_color(lv_color_hex(0xa7d4));
        TempCheck2->set_main_bg_opa(LV_OPA_0);
        TempCheck2->txt_color(lv_color_hex(0xffffff));
    }
}

int Weather::init_parament(void)
{
    weather_head_creat();
    Weather_scene_creat();
    Weather_citylist_creat();
    Weather_scene_draw();
    return 0;
}
void Weather::weather_head_creat(void)
{
    lv_ui_inof_t uiInfo;

    uiInfo.x =30;
    uiInfo.y =8;
    uiInfo.w =66;
    uiInfo.h =66;
    uiInfo.userdata =HEAD_ICON_RETURN;
    uiInfo.ui_patch =(char *)HEAD_RETURN_PNG;
    buttonReturn =LvcppButtonHead(mainscreen,true,&uiInfo);

    uiInfo.x =114;
    uiInfo.y =8;
    uiInfo.w =66;
    uiInfo.h =66;
    uiInfo.ui_patch =(char *)HEAD_ICON_WEATHER_PNG;
    weatherIcon =LvcppButtonHead(mainscreen,false,&uiInfo);
    weatherIcon->set_userdata(NULL);

    cityAddScene = new LvcppScreen(mainscreen);
    cityAddScene->set_size(1180, 680);
    cityAddScene->align(LV_ALIGN_TOP_LEFT, 50, 100);
    cityAddScene->set_bg_color(lv_color_hex(0x216fb1),LV_OPA_70);
    cityAddScene->set_main_radius(5);
    cityAddScene->set_main_pad_all(0);
    cityAddScene->set_main_border_width(0);
    cityAddScene->set_userdata(NULL);

    lineScene1 = new LvcppButton(mainscreen);
    lineScene1->set_size(1, 680);
    lineScene1->align(LV_ALIGN_TOP_LEFT, 370, 100);
    lineScene1->set_main_bg_color(lv_color_hex(0xb5eafa),LV_OPA_100);
    lineScene1->set_main_radius(0);
    lineScene1->set_main_pad_all(0);
    lineScene1->set_main_border_width(0);
    lineScene1->set_userdata(NULL);

    lineScene2 = new LvcppButton(mainscreen);
    lineScene2->set_size(860, 1);
    lineScene2->align(LV_ALIGN_TOP_LEFT, 370, 580);
    lineScene2->set_main_bg_color(lv_color_hex(0xb5eafa),LV_OPA_100);
    lineScene2->set_main_radius(0);
    lineScene2->set_main_pad_all(0);
    lineScene2->set_main_border_width(0);
    lineScene2->set_userdata(NULL);

    lineScene3 = new LvcppButton(mainscreen);
    lineScene3->set_size(1, 200);
    lineScene3->align(LV_ALIGN_TOP_LEFT, 800, 580);
    lineScene3->set_main_bg_color(lv_color_hex(0xb5eafa),LV_OPA_100);
    lineScene3->set_main_radius(0);
    lineScene3->set_main_pad_all(0);
    lineScene3->set_main_border_width(0);
    lineScene3->set_userdata(NULL);

    uiInfo.x =310;
    uiInfo.y =100;
    uiInfo.w =60;
    uiInfo.h =60;
    uiInfo.userdata =HEAD_ICON_PLAYING;
    uiInfo.ui_patch =(char *)WEATHER_UNADD_PNG;
    cityAdd =LvcppButtonHead(mainscreen,true,&uiInfo);
}
void Weather::weater_head_dele(void)
{
    if(buttonReturn != NULL)
    {
        delete buttonReturn;
        buttonReturn =NULL;
    }
    if(weatherIcon != NULL)
    {
        delete weatherIcon;
        weatherIcon =NULL;
    }
    if(cityAdd != NULL)
    {
        delete cityAdd;
        cityAdd =NULL;
    }
    if(cityAddScene != NULL)
    {
        delete cityAddScene;
        cityAddScene =NULL;
    }
    if(lineScene1 != NULL)
    {
        delete lineScene1;
        lineScene1 =NULL;
    }
    if(lineScene2 != NULL)
    {
        delete lineScene2;
        lineScene2 =NULL;
    }
    if(lineScene3 != NULL)
    {
        delete lineScene3;
        lineScene3 =NULL;
    }
}

void Weather::head_event_handler(lv_event_t *event)
{
    Weather* opt = (Weather*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    int set_selete = (uintptr_t)target->user_data;
    bool return_status =false;

    switch(set_selete)
    {
        case HEAD_ICON_RETURN:
            if(event->code== LV_EVENT_PRESSED)
            {
                opt->buttonReturn->set_main_bg_img_src(opt->HEAD_RETURN_SEL_PNG);
            }
            else
            {
                opt->buttonReturn->set_main_bg_img_src(opt->HEAD_RETURN_PNG);
                return_status =true;
            }
        break;
        case HEAD_ICON_PLAYING:
            if(event->code== LV_EVENT_PRESSED)
            {
                opt->cityAdd->set_main_bg_img_src(opt->WEATHER_ADD_PNG);
            }
            else
            {
                opt->cityAdd->set_main_bg_img_src(opt->WEATHER_UNADD_PNG);
            }
        break;
        case HEAD_ICON_CHECK:
            if(event->code== LV_EVENT_RELEASED)
            {
                if(opt->TempTpye ==true)
                {
                    opt->TempTpye =false;
                }
                else
                {
                    opt->TempTpye =true;
                }
                opt->get_weather_CheckInfo();
                opt->Weather_scene_draw();
            }
        break;
        default:
            break;
    }
    if(return_status ==true)
    {
        MainAPPStart::weathermain_destory();
        //msg_apps_t msg;
        //memset(&msg,0,sizeof(msg));
        //msg.type = UI_WEATHER;
        //msg.mode = MODE_RETURN;
        //SSTAR_SendAsyncMsg(APP_NAME_UI,&msg);
    }
}

void Weather::Weather_scene_creat(void)
{
    lv_ui_inof_t uiInfo;
    lv_str_inof_t strInfo;
    char *weekStrOne= NULL;
    char *weekStrTow= NULL;

    uiInfo.x =430;
    uiInfo.y =222;
    uiInfo.w =210;
    uiInfo.h =210;
    uiInfo.userdata =HEAD_ICON_MAX;
#ifdef IMAGE_DECODE
    uiInfo.ui_patch = WEATHER_BIG_PNG;
#else
    uiInfo.ui_patch =(char *)WEATHER_BIG_PNG;
#endif
    todayWea =LvcppButtonHead(mainscreen,false,&uiInfo);

    uiInfo.x =430;
    uiInfo.y =644;
    uiInfo.w =120;
    uiInfo.h =120;
    uiInfo.userdata =HEAD_ICON_MAX;
#ifdef IMAGE_DECODE
    uiInfo.ui_patch = WEATHER_MODE_PNG;
#else
    uiInfo.ui_patch =(char *)WEATHER_MODE_PNG;
#endif
    towWea =LvcppButtonHead(mainscreen,false,&uiInfo);

    uiInfo.x =860;
    uiInfo.y =644;
    uiInfo.w =120;
    uiInfo.h =120;
    uiInfo.userdata =HEAD_ICON_MAX;
#ifdef IMAGE_DECODE
    uiInfo.ui_patch = WEATHER_MODEB_PNG;
#else
    uiInfo.ui_patch =(char *)WEATHER_MODEB_PNG;
#endif
    threeWea =LvcppButtonHead(mainscreen,false,&uiInfo);

    strInfo.x=430;
    strInfo.y =450;
    strInfo.w =210;
    strInfo.h =38;
    strInfo.str_color =WHITE_COLOR;
    strInfo.str_buff =curWeatherInfo.weinfo;
    strTodayWea = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_CENTER,&strInfo);
    strTodayWea->txt_font_size(32, FT_FONT_STYLE_BOLD);

    strInfo.x=800;
    strInfo.y =250;
    strInfo.w =300;
    strInfo.h =76;
    strInfo.str_color =WHITE_COLOR;
    get_weather_CurInfo(curWeatherInfo.temp,CurTempBuff);
    strInfo.str_buff =CurTempBuff;
    strCurTemp = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_LEFT,&strInfo);
    strCurTemp->txt_font_size(70, FT_FONT_STYLE_BOLD);

    strInfo.x=800;
    strInfo.y =350;
    strInfo.w =160;
    strInfo.h =32;
    strInfo.str_color =WHITE_COLOR;
    get_weather_MaxMinInfo(curWeatherInfo.temp_min,curWeatherInfo.temp_max,OneTempBuff);
    strInfo.str_buff =OneTempBuff;
    strTodayTemp = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_LEFT,&strInfo);

    strInfo.x=800;
    strInfo.y =400;
    strInfo.w =300;
    strInfo.h =32;
    strInfo.str_color =WHITE_COLOR;

    sprintf(HumBuff,"%s:%d%c",STR_HUM,curWeatherInfo.humidity,'%');
    strInfo.str_buff =HumBuff;
    strCurHum = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_LEFT,&strInfo);

    strInfo.x=800;
    strInfo.y =450;
    strInfo.w =300;
    strInfo.h =32;
    strInfo.str_color =WHITE_COLOR;
    sprintf(WinBuff,"%s:%.1f mph S",STR_WIN,curWeatherInfo.speed);
    strInfo.str_buff =WinBuff;
    strCurWin = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_LEFT,&strInfo);

    strInfo.x=565;
    strInfo.y =675;
    strInfo.w =210;
    strInfo.h =30;
    strInfo.str_color =WHITE_COLOR;
    strInfo.str_buff =oneWeatherInfo.weinfo;
    strTowWea = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_LEFT,&strInfo);

    strInfo.x=565;
    strInfo.y =710;
    strInfo.w =210;
    strInfo.h =30;
    strInfo.str_color =WHITE_COLOR;
    get_weather_MaxMinInfo(oneWeatherInfo.temp_min,oneWeatherInfo.temp_max,TowTempBuff);
    strInfo.str_buff =TowTempBuff;
    strTowTemp = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_LEFT,&strInfo);

    strInfo.x=1000;
    strInfo.y =675;
    strInfo.w =210;
    strInfo.h =30;
    strInfo.str_color =WHITE_COLOR;
    strInfo.str_buff =towWeatherInfo.weinfo;
    strThreeWea = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_LEFT,&strInfo);

    strInfo.x=1000;
    strInfo.y =710;
    strInfo.w =210;
    strInfo.h =30;
    strInfo.str_color =WHITE_COLOR;
    get_weather_MaxMinInfo(towWeatherInfo.temp_min,towWeatherInfo.temp_max,ThreeTempBuff);
    strInfo.str_buff =ThreeTempBuff;
    strThreeTemp = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_LEFT,&strInfo);

    strInfo.x=430;
    strInfo.y =600;
    strInfo.w =350;
    strInfo.h =36;
    strInfo.str_color =WHITE_COLOR;
    weekStrOne = calendar_get_week(oneWeatherInfo.week);
    strInfo.str_buff =weekStrOne;
    strWeekTow = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_LEFT,&strInfo);

    strInfo.x=860;
    strInfo.y =600;
    strInfo.w =350;
    strInfo.h =36;
    strInfo.str_color =WHITE_COLOR;
    weekStrTow = calendar_get_week(towWeatherInfo.week);
    strInfo.str_buff =weekStrTow;
    strWeekThree = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_LEFT,&strInfo);

    TempCheck = new LvcppButton(mainscreen);
    TempCheck->set_size(110,40);
    TempCheck->align_to(mainscreen,LV_ALIGN_TOP_LEFT,960,346);
    TempCheck->set_main_bg_color(lv_color_hex(0xa7d4),LV_OPA_100);
    TempCheck->set_main_radius(50);
    TempCheck->set_main_pad_all(0);
    TempCheck->set_main_border_width(0);
    TempCheck->add_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
    TempCheck->set_userdata(NULL);
    TempCheck->set_userdata((void*)HEAD_ICON_CHECK);
    TempCheck->add_event_cb(head_event_handler,LV_EVENT_PRESSED,this);
    TempCheck->add_event_cb(head_event_handler,LV_EVENT_RELEASED,this);

    TempCheck1 = new LvcppButton(TempCheck->myobj);
    TempCheck1->set_size(50,36);
    TempCheck1->align_to(TempCheck->myobj,LV_ALIGN_TOP_LEFT,5,2);
    TempCheck1->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    TempCheck1->set_main_radius(30);
    TempCheck1->set_main_pad_all(0);
    TempCheck1->set_main_border_width(0);
    TempCheck1->txt_size(40, 36, LV_LABEL_LONG_WRAP);
    TempCheck1->txt_font_size(30, FT_FONT_STYLE_NORMAL);
    TempCheck1->txt_align(LV_ALIGN_TOP_MID,5,0);
    TempCheck1->txt_color(lv_color_hex(0xa7d4));
    TempCheck1->add_txt(STR_TEMP_C);
    TempCheck1->add_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
    TempCheck1->set_userdata((void*)HEAD_ICON_CHECK);


    TempCheck2 = new LvcppButton(TempCheck->myobj);
    TempCheck2->set_size(50,36);
    TempCheck2->align_to(TempCheck->myobj,LV_ALIGN_TOP_LEFT,55,2);
    TempCheck2->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    TempCheck2->set_main_radius(30);
    TempCheck2->set_main_pad_all(0);
    TempCheck2->set_main_border_width(0);
    TempCheck2->txt_size(40, 36, LV_LABEL_LONG_WRAP);
    TempCheck2->txt_font_size(30, FT_FONT_STYLE_NORMAL);
    TempCheck2->txt_align(LV_ALIGN_TOP_MID,5,0);
    TempCheck2->txt_color(lv_color_hex(0xa7d4));
    TempCheck2->add_txt(STR_TEMP_F);
    TempCheck2->add_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
    TempCheck2->set_userdata((void*)HEAD_ICON_CHECK);
    get_weather_CheckInfo();
}

void Weather::Weather_scene_dele(void)
{
    if(todayWea != NULL)
    {
        delete todayWea;
        todayWea =NULL;
    }
    if(towWea != NULL)
    {
        delete towWea;
        towWea =NULL;
    }
    if(threeWea != NULL)
    {
        delete threeWea;
        threeWea =NULL;
    }
    if(strWeekTow != NULL)
    {
        delete strWeekTow;
        strWeekTow =NULL;
    }
    if(strWeekThree != NULL)
    {
        delete strWeekThree;
        strWeekThree =NULL;
    }
    if(strTodayWea != NULL)
    {
        delete strTodayWea;
        strTodayWea =NULL;
    }
    if(strTowWea != NULL)
    {
        delete strTowWea;
        strTowWea =NULL;
    }
    if(strThreeWea != NULL)
    {
        delete strThreeWea;
        strThreeWea =NULL;
    }
    if(strCurTemp != NULL)
    {
        delete strCurTemp;
        strCurTemp =NULL;
    }
    if(strTodayTemp != NULL)
    {
        delete strTodayTemp;
        strTodayTemp =NULL;
    }
    if(strTowTemp != NULL)
    {
        delete strTowTemp;
        strTowTemp =NULL;
    }
    if(strThreeTemp != NULL)
    {
        delete strThreeTemp;
        strThreeTemp =NULL;
    }
    if(strCurHum != NULL)
    {
        delete strCurHum;
        strCurHum =NULL;
    }
    if(strCurWin != NULL)
    {
        delete strCurWin;
        strCurWin =NULL;
    }
    if(TempCheck1 != NULL)
    {
        delete TempCheck1;
        TempCheck1 =NULL;
    }
    if(TempCheck2 != NULL)
    {
        delete TempCheck2;
        TempCheck2 =NULL;
    }
    if(TempCheck != NULL)
    {
        delete TempCheck;
        TempCheck =NULL;
    }
}

void Weather::Weather_scene_draw(void)
{
    char *weekStrOne =NULL;
    char *weekStrTow= NULL;

#ifdef _UCHIP_T113
    char weaPatch[64]={0};
    if(WEATHER_BIG_PNG!=NULL)
    {
        sunxi_image_free(WEATHER_BIG_PNG);
        WEATHER_BIG_PNG =NULL;
    }
    memset(weaPatch,0,64);
    sprintf(weaPatch,"%s%s.png",WEATHER_PATCH,curWeatherInfo.icon);
    if(access(weaPatch, F_OK) == 0)
    {
        if(todayWea !=NULL)
        {
            WEATHER_BIG_PNG=(void*)sunxi_image_decode_scaler(weaPatch,todayWea->width(),todayWea->height());
            Lvcpp_Head_img(todayWea,WEATHER_BIG_PNG);
        }
    }
    if(WEATHER_MODE_PNG!=NULL)
    {
        sunxi_image_free(WEATHER_MODE_PNG);
        WEATHER_MODE_PNG =NULL;
    }
    memset(weaPatch,0,64);
    sprintf(weaPatch,"%s%s.png",WEATHER_PATCH,oneWeatherInfo.icon);
    if(access(weaPatch, F_OK) == 0)
    {
        if(towWea !=NULL)
        {
            WEATHER_MODE_PNG=(void*)sunxi_image_decode_scaler(weaPatch,towWea->width(),towWea->height());
            Lvcpp_Head_img(towWea,WEATHER_MODE_PNG);
        }
    }
    if(WEATHER_MODEB_PNG!=NULL)
    {
        sunxi_image_free(WEATHER_MODEB_PNG);
        WEATHER_MODEB_PNG =NULL;
    }
    memset(weaPatch,0,64);
    sprintf(weaPatch,"%s%s.png",WEATHER_PATCH,towWeatherInfo.icon);
    if(access(weaPatch, F_OK) == 0)
    {
        if(threeWea !=NULL)
        {
            WEATHER_MODEB_PNG=(void*)sunxi_image_decode_scaler(weaPatch,threeWea->width(),threeWea->height());
            Lvcpp_Head_img(threeWea,WEATHER_MODEB_PNG);
        }
    }
#else
    if(todayWea !=NULL)
    {
        todayWea->set_main_bg_img_src(todayWeaPatch);
    }
    if(towWea !=NULL)
    {
        towWea->set_main_bg_img_src(towWeaPatch);
    }
    if(threeWea !=NULL)
    {
        threeWea->set_main_bg_img_src(threeWeaPatch);
    }
#endif
    if(strTodayWea !=NULL)
    {
        strTodayWea->set_txt(curWeatherInfo.weinfo);
    }
    if(strCurTemp !=NULL)
    {
        get_weather_CurInfo(curWeatherInfo.temp,CurTempBuff);
        strCurTemp->set_txt(CurTempBuff);
    }
    if(strTodayTemp !=NULL)
    {
        get_weather_MaxMinInfo(curWeatherInfo.temp_min,curWeatherInfo.temp_max,OneTempBuff);
        strTodayTemp->set_txt(OneTempBuff);
    }
    if(strCurHum !=NULL)
    {
        sprintf(HumBuff,"%s:%d%s",STR_HUM,curWeatherInfo.humidity,"%");
        strCurHum->set_txt(HumBuff);
    }
    if(strCurWin !=NULL)
    {
        sprintf(WinBuff,"%s:%.1f mph S",STR_WIN,curWeatherInfo.speed);
        strCurWin->set_txt(WinBuff);
    }

    if(strWeekTow !=NULL)
    {
        weekStrOne = calendar_get_week(oneWeatherInfo.week);
        strWeekTow->set_txt(weekStrOne);
    }
    if(strTowWea !=NULL)
    {
        strTowWea->set_txt(oneWeatherInfo.weinfo);
    }
    if(strTowTemp !=NULL)
    {
        get_weather_MaxMinInfo(oneWeatherInfo.temp_min,oneWeatherInfo.temp_max,TowTempBuff);
        strTowTemp->set_txt(TowTempBuff);
    }
    if(strWeekThree !=NULL)
    {
        weekStrTow = calendar_get_week(towWeatherInfo.week);
        strWeekThree->set_txt(weekStrTow);
    }
    if(strThreeWea !=NULL)
    {
        strThreeWea->set_txt(towWeatherInfo.weinfo);
    }
    if(strThreeTemp !=NULL)
    {
        get_weather_MaxMinInfo(towWeatherInfo.temp_min,towWeatherInfo.temp_max,ThreeTempBuff);
        strThreeTemp->set_txt(ThreeTempBuff);
    }
}

void Weather::get_weather_scene_info(void)
{
    if(weaInfo ==NULL)
        return;
    weaInfo->get_cur_weather(&curWeatherInfo);
    weaInfo->get_first_weather(&oneWeatherInfo);
    weaInfo->get_second_weather(&towWeatherInfo);
    weaInfo->get_three_weather(&threeWeatherInfo);
}
void Weather::Weather_citylist_creat(void)
{
    cityList = new LvcppList(mainscreen);
    cityList->set_size(320,620);
    cityList->align(LV_ALIGN_TOP_LEFT,50,160);
    cityList->set_main_bg_color(lv_color_hex(0x216fb1),LV_OPA_COVER);
    cityList->set_main_bg_opa(LV_OPA_0);
    cityList->set_flex_flow(LV_FLEX_FLOW_COLUMN);
    cityList->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    cityList->set_main_pad_all(0);
    cityList->set_main_pad_row(0);
    cityList->set_main_pad_column(0);
    cityList->set_main_border_width(0);
    cityList->set_main_radius(0);
    citylist_add();
    Weather_citylist_head_draw();
}

void Weather::citylist_add(void)
{
    FILE *fd;
    struct stat buf;
    cJSON	*json = NULL;
    cJSON	*array = NULL;
    cJSON	*arrayItem = NULL;
    cJSON	*item = NULL;
    char *strbuff=NULL;
    int sizeLen=0,data_size=0,totalCity=0;
    double latData=0;
    double lonData=0;
#if 0
    fd= lv_fs_open(CITYINFO_CFG,"rb");
    if(!fd)
    {
         LV_LOG_USER("open %s fail!!!",CITYINFO_CFG);
    }
    else
#endif
    {
#if 0
        if(stat(CITYINFO_CFG, &buf) == 0)
        {
            sizeLen = buf.st_size;
        }
        LV_LOG_USER("sizeLen:%d",sizeLen);
        if(sizeLen >0)
        {
            strbuff = new char[sizeLen + 1];
            data_size = fread(strbuff, 1, sizeLen, fd);
        }

        fclose(fd);
        fd =NULL;
#else
    sizeLen=150;
    strbuff = new char[sizeLen + 1];
    strcpy(strbuff,"{\"data\":[{\"name\":\"Shenzhen\",\"lat\":25.3,\"lon\":36.8},{\"name\":\"Guangzhou\",\"lat\":15.3,\"lon\":26.8},{\"name\":\"Zhuhai\",\"lat\":45.3,\"lon\":66.8}]}");
    data_size = sizeLen;
#endif
        if(data_size>0)
        {
            json = cJSON_Parse(strbuff);
            if(json != NULL)
            {
                array = cJSON_GetObjectItem(json,"data");
                if(array != NULL)
                {
                    totalCity = cJSON_GetArraySize(array);
                    if(totalCity >0)
                    {
                        for(int i=0;i<totalCity;i++)
                        {
                            arrayItem = cJSON_GetArrayItem(array,i);
                            if(arrayItem !=NULL)
                            {
                                item = cJSON_GetObjectItem(arrayItem,"lat");
                                if(item != NULL)
                                {
                                    latData =item->valuedouble;
                                }
                                item = cJSON_GetObjectItem(arrayItem,"lon");
                                if(item != NULL)
                                {
                                    lonData =item->valuedouble;
                                }
                                item = cJSON_GetObjectItem(arrayItem,"name");
                                if(item != NULL)
                                {
                                    if(item->valuestring !=NULL)
                                    {
                                        Weather_citylist_head_creat(i,latData,lonData,item->valuestring);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                LV_LOG_USER("cJSON_Parse %s fail!!!",strbuff);
            }
        }
        if(json != NULL)
        {
            cJSON_Delete(json);
            json = NULL;
        }
        if(strbuff!= NULL)
        {
            delete[] strbuff;
            strbuff =NULL;
        }
    }
}

void Weather::citylist_event_handler(lv_event_t *event)
{
    Weather* opt = (Weather*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    lv_obj_t* cont = lv_event_get_current_target(event);

    if(cont != target)
    {
        opt->CurCity = (uintptr_t)cont->user_data;
    }
    else
    {
       opt->CurCity =(uintptr_t)target->user_data;
    }
    opt->Weather_citylist_head_draw();
}


void Weather::Weather_citylist_head_creat(int data,double lat,double lon,char *cityName)
{
    cityListInfo_t *tmp_list =new cityListInfo_t;
    tmp_list->count =data;
    tmp_list->list_item = new WeatherList(cityList->myobj,lat,lon,cityName);
    tmp_list->list_item->btn->add_event_cb(citylist_event_handler,LV_EVENT_CLICKED,this);
    tmp_list->list_item->btn->set_userdata((void*)data);
    tmp_list->list_item->Icon1->add_event_cb(citylist_event_handler,LV_EVENT_CLICKED,this);
    tmp_list->list_item->Icon1->set_userdata((void*)data);
    Weather_citylist_head_add(tmp_list);
}

void Weather::Weather_citylist_head_add(cityListInfo_t *citylist)
{
    cityListInfo_t *tmp_list;

    tmp_list = cityListHead;

    if(cityListHead == NULL)
    {
        cityListHead = citylist;
        cityListHead->next_list = NULL;
    }
    else
    {
        while(tmp_list->next_list != NULL)
        {
            tmp_list = tmp_list->next_list;
        }
        tmp_list->next_list = citylist;
        tmp_list->next_list->next_list = NULL;
    }
}

void Weather::Weather_citylist_head_draw(void)
{
    cityListInfo_t * tmp_list;

    tmp_list = cityListHead;
    while(tmp_list != NULL)
    {
        if(tmp_list->count ==CurCity)
        {
            tmp_list->list_item->update_weatherList(true);
        }
        else
        {
            tmp_list->list_item->update_weatherList(false);
        }
        tmp_list = tmp_list->next_list;
    }
}

void Weather::Weather_citylist_head_destory(void)
{
    cityListInfo_t *tmp_list_prev;
    cityListInfo_t *tmp_list_last;

    tmp_list_prev = cityListHead;
    while(tmp_list_prev != NULL)
    {
        tmp_list_last = tmp_list_prev->next_list;
        if(tmp_list_prev->list_item !=NULL)
        {
            delete tmp_list_prev->list_item;
            tmp_list_prev->list_item =NULL;
        }
        tmp_list_prev = tmp_list_last;
    }
    cityListHead = NULL;
    if(cityList != NULL)
    {
        delete cityList;
        cityList =NULL;
    }
}
