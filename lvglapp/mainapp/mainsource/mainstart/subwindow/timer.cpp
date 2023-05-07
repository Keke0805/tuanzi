#include "timer.h"
#include "common/common.h"
#include "math.h"

static int retimetmp = 0;
static int photo =0;
static int timetmp = 0;
static int timecnt = 0;
static int s1 = 0;
Timer* timeropt = nullptr;
static int name_or_pass = 0;
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
    timeropt = this;
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
    if(TIMER_PNG != NULL)
    {
        free_image(TIMER_PNG);
        TIMER_PNG = NULL;
    }
    if(TIMER_ZHIZHEN_PNG != NULL)
    {
        free_image(TIMER_ZHIZHEN_PNG);
        TIMER_ZHIZHEN_PNG = NULL;
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
    if(input_kb != nullptr)
    {
        delete input_kb;
        input_kb = NULL;
    }
}
//input time
void Timer::kb_create(void)
{
    if(input_kb == nullptr)
    {
        input_kb = new kbscreen(m_parent);
        input_kb->sendcb(kb_cb);
    }
}
void Timer::kb_cb(void)
{
    timeropt->get_kbinput_text(name_or_pass);
    if(timeropt->input_kb != nullptr)
    {
        delete timeropt->input_kb;
        timeropt->input_kb = NULL;
    }
}
void Timer::get_kbinput_text(int type)
{
   if(type == 0)
   {
       time_value->add_txt(input_kb->input_box->get_text());
   }
}
//动画控件--设置角度的函数回调
static void set_angle(void* img, int32_t v)
{
    lv_img_set_angle((lv_obj_t *)img, v);//img类型不匹配，要强转类型
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
/*
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
*/
    on_and_off = new LvcppButton(m_parent);
    on_and_off->add_txt("");
    on_and_off->set_size(120,44);
    on_and_off->align(LV_ALIGN_CENTER,0,180);
    on_and_off->set_main_bg_img_src(SETTING_ON_PNG);
    on_and_off->set_main_bg_color(lv_color_white(),LV_OPA_0);
    on_and_off->add_event_cb(btn_event_hander2,LV_EVENT_CLICKED,this);

    time_value = new LvcppButton(m_parent);
    time_value->align(LV_ALIGN_CENTER,5,-53);
    time_value->add_txt("");
    time_value->txt_center();
    time_value->set_main_bg_color(lv_color_white(),LV_OPA_0);
    time_value->txt_color(lv_color_black());
    time_value->txt_font_size(60,0);
    time_value->set_size(70,70);
    time_value->add_event_cb(btn_event_hander2,LV_EVENT_CLICKED,this);

    plate=new LvcppImage(m_parent);
    plate->set_size(170,167);
    plate->align(LV_ALIGN_CENTER,5,-53);
    plate->set_main_bg_img_src(TIMER_PNG);
    plate->set_main_bg_color(lv_color_white(),LV_OPA_0);
    anim=new LvcppRotateAnimimg(m_parent);
    anim->set_animimg_src(TIMER_ZHIZHEN_PNG);
    anim->align(LV_ALIGN_CENTER,5,-53);
    anim->set_main_bg_color(lv_color_black(),LV_OPA_0);
    anim->set_exec_cb(set_angle);
    anim->set_values(0,3600);//值的范围----0--转一圈
    anim->set_time(2000);//动画持续时间，user传进来的秒数
    anim->set_repeat_count(LV_ANIM_REPEAT_INFINITE);
    anim->start();

    //anim->set_playback_time(1000);
    //anim->set_exec_cb(set_zoom);
    //anim->set_values(100,100);

    maintimer = startTimer(200,this);
}

void Timer::reset_param()
{
    second->set_selected(0,LV_ANIM_ON);
}

//loop run(must achieve)
//btn--back
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
//btn--on/off wifi and input time
void  Timer::btn_event_hander2(lv_event_t *event)
{
    Timer* opt = ( Timer*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    if(target==opt->time_value->myobj)
   {

        if(event->code==LV_EVENT_CLICKED)
        {
            if(opt->choose==0)
            {
            LV_LOG_USER("111");
            name_or_pass = 0;
            opt->kb_create();
            timeropt->input_kb->initial(4);
            }
        }
   }
  else  if(target==opt->on_and_off->myobj)
   {

       if(event->code == LV_EVENT_CLICKED)
       {
           if(opt->choose==1)
           {
               opt->on_and_off->set_main_bg_img_src(opt->SETTING_OFF_PNG);
               opt->choose=0;

           }  else if(opt->choose==0)
           {
               opt->on_and_off->set_main_bg_img_src(opt->SETTING_ON_PNG);
               opt->choose=1;
           }
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
/*
void  Timer::textarea_event_hander(lv_event_t *event)
{
    Timer* opt = ( Timer*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    if(target==opt->time_value->myobj&&opt->choose==0)
   {
        if(event->code==LV_EVENT_CLICKED)
        {
            name_or_pass = 0;
            opt->kb_create();
            timeropt->input_kb->initial(4);
        }
   }

}
*/







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
/*
void Timer::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    static int count = 0;
    SYSDateTime gettime;
    char time_current[1024];
    user_time1=gettime.current_time();
    sprintf(time_current,"%02d",user_time.second);
    int s=user_time.second;
    zhizhen->set_angle(s);


}
*/
