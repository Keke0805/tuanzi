#include "timer.h"
#include "common/common.h"
#include "math.h"

static int retimetmp = 0;
static int photo =0;
static int timetmp = 0;
static int timecnt = 0;
static int s1 = 0;
void Timer::ui_image_decode(void)
{
    SETTING_BACK_PNG=(void*)parse_image_from_file((char*)OTHER_GOBACK1_PNG_PATH);
    SETTING_ON_PNG=(void*)parse_image_from_file((char*)OTHER_ON_PNG_PATH);
    SETTING_OFF_PNG=(void*)parse_image_from_file((char*)OTHER_OFF_PNG_PATH);
    TIMER_PNG=(void*)parse_image_from_file((char*)TIMER_PNG_PATH);
    TIMER_ZHIZHEN_PNG=(void*)parse_image_from_file((char*)TIMER_ZHIZHEN_PNG_PATH);
}


Timer::Timer(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(parent);
    mscreen->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    mscreen->set_main_bg_color(lv_color_white(),LV_OPA_100);
    m_parent = mscreen->myobj;
    initial();
}

Timer::~Timer()
{
    if(SETTING_BACK_PNG != NULL)
    {
        free_image(SETTING_BACK_PNG);
        SETTING_BACK_PNG = NULL;
    }
    if(SETTING_ON_PNG != NULL)
    {
        free_image(SETTING_ON_PNG);
        SETTING_ON_PNG = NULL;
    }
    if(SETTING_OFF_PNG != NULL)
    {
        free_image(SETTING_OFF_PNG);
        SETTING_OFF_PNG = NULL;
    }
    if(TIMER_EXCIRCLE_PNG != NULL)
    {
        free_image(TIMER_EXCIRCLE_PNG);
        TIMER_EXCIRCLE_PNG = NULL;
    }
    if(TIMER_FILLET_PNG != NULL)
    {
        free_image(TIMER_FILLET_PNG);
        TIMER_FILLET_PNG = NULL;
    }
    if(current_icon != NULL)
    {
        delete  current_icon;
        current_icon = NULL;
    }
    if(back_icon != NULL)
    {
        delete  back_icon;
        back_icon = NULL;
    }
    if(on_and_off != NULL)
    {
        delete  on_and_off;
        on_and_off = NULL;
    }
    if(excircle_icon != NULL)
    {
        delete  excircle_icon;
        excircle_icon = NULL;
    }
    if(fillet_icon != NULL)
    {
        delete  fillet_icon;
        fillet_icon = NULL;
    }
    if(mscreen != NULL)
    {
        delete  mscreen;
        mscreen = NULL;
    }
}

void Timer::initial(void)
{
    ui_image_decode();

    current_icon = new LvcppButton(m_parent);
    current_icon->align(LV_ALIGN_CENTER,0,-300);
    current_icon->add_txt("Timer");
    current_icon->txt_center();
    current_icon->set_main_bg_color(lv_color_white(),LV_OPA_100);
    current_icon->txt_color(lv_color_black());
    current_icon->txt_font_size(50,0);
    current_icon->set_size(230,90);

    back_icon = new LvcppButton(m_parent);
    back_icon->align(LV_ALIGN_CENTER,0,250);
    back_icon->set_size(60,60);
    back_icon->add_txt("");
    back_icon->set_main_bg_img_src(SETTING_BACK_PNG);
    back_icon->set_main_bg_color(lv_color_white(),LV_OPA_0);
    #if QTSIM_PLATFORM==0
    LvcppGroup::add_group_obj(get_key_group(),back_icon->myobj);
    #endif
    back_icon->add_event_cb(btn_event_hander,LV_EVENT_FOCUSED,this);
    back_icon->add_event_cb(btn_event_hander,LV_EVENT_KEY,this);
    back_icon->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);

    excircle_icon = new LvcppLabel(m_parent);
    excircle_icon->align(LV_ALIGN_CENTER,0,-60);
    excircle_icon->set_size(400,300);
    excircle_icon->set_txt("");
    excircle_icon->set_main_bg_img_src(TIMER_EXCIRCLE_PNG);

    fillet_icon = new LvcppLabel(m_parent);
    fillet_icon->align(LV_ALIGN_CENTER,5,-53);
    fillet_icon->set_size(220,220);
    fillet_icon->set_txt("");
    fillet_icon->set_main_bg_img_src(TIMER_FILLET_PNG);

    on_and_off = new LvcppButton(m_parent);
    on_and_off->add_txt("");
    on_and_off->set_size(120,44);
    on_and_off->align(LV_ALIGN_CENTER,0,180);
    on_and_off->set_main_bg_img_src(SETTING_ON_PNG);
    on_and_off->set_main_bg_color(lv_color_white(),LV_OPA_0);
    on_and_off->add_event_cb(btn_event_hander2,LV_EVENT_CLICKED,this);

    time_value = new LvcppButton(m_parent);
    time_value->align(LV_ALIGN_CENTER,5,-53);
    time_value->add_txt("55");
    time_value->txt_center();
    time_value->set_main_bg_color(lv_color_white(),LV_OPA_0);
    time_value->txt_color(lv_color_black());
    time_value->txt_font_size(60,0);
    time_value->set_size(70,70);



    maintimer = startTimer(1000,this);
}
void Timer::reset_param()
{
    second->set_selected(0,LV_ANIM_ON);
}
/*
void Timer::update_num_clickable(void)
{
    second->clicked_enable(false);
}
*/

//loop run(must achieve)
void  Timer::btn_event_hander(lv_event_t *event)
{   Timer* opt = ( Timer*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    if(target == opt->back_icon->myobj)
        {
            if(event->code == LV_EVENT_CLICKED)
            {
                opt->volume_callback();
            }
        }

}
void Timer::sendcb(void (*callback)(void))
{
    volume_callback=callback;
}
void  Timer::btn_event_hander2(lv_event_t *event)
{
    Timer* opt = ( Timer*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    if(target == opt->on_and_off->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->reset_param();
            //opt->update_num_clickable();
        }
    }

}
void Timer::time_split(int time)
{
    if(time >= 0)
     {
        s1= time%3600%60/10;
        second->set_selected(s1,LV_ANIM_ON);
     }
}

void Timer::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    //LV_LOG_USER("111");
    static int count = 0;
    SYSDateTime gettime;
    char time_current[1024];
    char second_current[1024];
    user_time = gettime.current_datetime();
    sprintf(time_current,"%d-%02d-%02d %02d:%02d:%02d",user_time.year,user_time.month,user_time.day,user_time.hour,user_time.minute,user_time.second);
    sprintf(second_current,"%02d",user_time.second);
    LV_LOG_USER("%s",time_current);

    time_value->add_txt(second_current);

    //static variable once assign
}

#if 0
void Timer::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    static int count = 0;
    if(timetmp == 0)
    {
    timecnt++;
    time_split(timecnt);
    LV_LOG_USER("Positive timing");
    }
    else if(timetmp>0)
    {
       timecnt= second->get_selected()*10;
       LV_LOG_USER("timecnt =%d", timecnt);
    }

}
#endif
