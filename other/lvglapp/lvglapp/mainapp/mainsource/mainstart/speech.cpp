#include "speech.h"
#include "stbimage/va_image.h"

static int retimetmp = 0;
static int photo =0;
static int timetmp = 0;
static int timecnt = 0;//static variable once assign
static int h1 = 0;
static int h2 = 0;
static int m1 = 0;
static int m2 = 0;
static int s1 = 0;
static int s2 = 0;
/*
h1 = hour/10;
h2 = hour%10;
m1 = mins/10;
m2 = mins%10;
s1 = sec/10;
s2 = sec%10;
sprintf(timeStr, "%d-%02d-%02d %02d:%02d:%02d", 1900 + t->tm_year, t->tm_mon + 1, t->tm_mday, t->tm_hour,t->tm_min,t->tm_sec);

static void  Curdatetime(void)
{
    char timeStr[128];
    if(SSTAR_ZPCGetServerConnectState())
    {
        if(g_zpcInfo.heartbeat_flag == 1)
        {
            if(!g_time)
            {
                sprintf(timeStr, "%d-%02d-%02d %02d:%02d:%02d",\
                                g_zpcInfo.server_dt.year,g_zpcInfo.server_dt.month,g_zpcInfo.server_dt.day,\
                                g_zpcInfo.server_dt.hour,g_zpcInfo.server_dt.minute,g_zpcInfo.server_dt.second);
                TimeHelper::setDateTime(timeStr);
                g_time=true;
                mTextview_clock_iconPtr->setVisible(true);
                mTextview_date_timePtr->setVisible(true);
                hb_send_start_time=get_tick_time_ms();
            }
        }
    }
    if(g_time)
    {
        struct tm *t = TimeHelper::getDateTime();
        sprintf(timeStr, "%d-%02d-%02d %02d:%02d:%02d", 1900 + t->tm_year, t->tm_mon + 1, t->tm_mday, t->tm_hour,t->tm_min,t->tm_sec);
        mTextview_date_timePtr->setText(timeStr);
        g_timeflag=true;
    }
    else
    {
        struct tm *t = TimeHelper::getDateTime();
        sprintf(timeStr, "0000-00-00 %02d:%02d:%02d",t->tm_hour,t->tm_min,t->tm_sec);
        mTextview_date_timePtr->setText(timeStr);
    }
}
*/
speech::speech(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(lv_scr_act());
    mscreen->set_pos(0,0);
    mscreen->set_size(SCREEN_HOR_SIZE, SCREEN_VER_SIZE);
    mscreen->set_bg_color(lv_color_black(),LV_OPA_0);
    mparent = mscreen->get_screen();
    bg = parse_image_from_file("./resource/image/ui/bg.png");
    speechimer = startTimer(500,this);
    /*num0 = parse_image_from_file("./resource/image/ui/0.png");
    num1 = parse_image_from_file("./resource/image/ui/1.png");
    num2 = parse_image_from_file("./resource/image/ui/2.png");
    num3 = parse_image_from_file("./resource/image/ui/3.png");
    num4 = parse_image_from_file("./resource/image/ui/4.png");
    num5 = parse_image_from_file("./resource/image/ui/5.png");
    num6 = parse_image_from_file("./resource/image/ui/6.png");
    num7 = parse_image_from_file("./resource/image/ui/7.png");
    num8 = parse_image_from_file("./resource/image/ui/8.png");
    num9 = parse_image_from_file("./resource/image/ui/9.png");
    */
    mscreen->showlogo((char*)bg, SCREEN_HOR_SIZE, SCREEN_VER_SIZE,0);
    lv_timer_t* creatTimer(lv_timer_cb_t timer_xcb, uint32_t period, void * user_data);
    initial();
}


speech::~speech()
{
    if(bg!=nullptr)
    {
        free_image(bg);
        bg = nullptr;
    }
    if(hour != nullptr)
    {
        delete hour;
        hour = nullptr;
    }
    if(hour1 != nullptr)
    {
        delete hour1;
        hour1 = nullptr;
    }
    if(minute != nullptr)
    {
        delete minute;
        minute = nullptr;
    }
    if(minute1 != nullptr)
    {
        delete minute1;
        minute1 = nullptr;
    }
    if(second != nullptr)
    {
        delete second;
        second = nullptr;
    }
    if(second1 != nullptr)
    {
        delete second1;
        second1 = nullptr;
    }
    if(paly_stop != nullptr)
    {
        delete paly_stop;
        paly_stop = nullptr;
    }
    if(paly_stop != nullptr)
    {
        delete paly_stop;
        paly_stop = nullptr;
    }
    if(back != nullptr)
    {
        delete back;
        back = nullptr;
    }
    if(resetbuttton != nullptr)
    {
        delete resetbuttton;
        resetbuttton = nullptr;
    }
    if(time_tip != nullptr)
    {
        delete time_tip;
        time_tip = nullptr;
    }
    if(play_stop_tip != nullptr)
    {
        delete play_stop_tip;
        play_stop_tip = nullptr;
    }    if(resetbuttton_tip != nullptr)
    {
        delete resetbuttton_tip;
        resetbuttton_tip = nullptr;
    }
    if(mscreen != nullptr)
    {
        delete mscreen;
        mscreen = nullptr;
    }
}

void speech::initial(void)
{
    if(myfont==nullptr)
    {
        myfont = new LvcppFreeTypeFont(60,0);
    }
    if(hour == nullptr)
    {
        hour = new LvcppRoller(mparent);
        hour->set_size(75,110);
        hour->align(LV_ALIGN_CENTER,-270,-50);
        hour->set_options("0\n1\n2\n3\n4\n5\n6\n7\n8\n9",1);
        hour->set_main_bg_img_src(TIME_BUTTON);
        hour->set_main_bg_color(lv_color_white(),LV_OPA_30);
        hour->set_style_text_font(myfont->font(),LV_PART_MAIN);
        hour->set_style_bg_color(lv_color_hex(0X66B2FF),LV_OPA_0,LV_PART_SELECTED );
        hour->set_main_border(0,lv_color_white(),LV_OPA_0);
        hour->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
    if(hour1 == nullptr)
    {
        hour1 = new LvcppRoller(mparent);
        hour1->set_size(75,110);
        hour1->set_options("0\n1\n2\n3\n4\n5\n6\n7\n8\n9",1);
        hour1->align_to(hour->myobj,LV_ALIGN_RIGHT_MID,120,0);
        hour1->set_main_bg_img_src(TIME_BUTTON);
        hour1->set_main_bg_color(lv_color_white(),LV_OPA_30);
        hour1->set_style_text_font(myfont->font(),LV_PART_MAIN);
        hour1->set_style_bg_color(lv_color_hex(0X66B2FF),LV_OPA_0,LV_PART_SELECTED );
        hour1->set_main_border(0,lv_color_white(),LV_OPA_0);
        //hour1->set_style_bg_color(lv_color_hex(0X66B2FF),LV_OPA_60,LV_PART_SELECTED );
        hour1->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
    if(minute == nullptr)
    {
        minute = new LvcppRoller(mparent);
        minute->set_size(75,110);
        minute->align_to(hour1->myobj,LV_ALIGN_RIGHT_MID,150,0);
        minute->set_options("0\n1\n2\n3\n4\n5",1);
        minute->set_main_bg_img_src(TIME_BUTTON);
        minute->set_main_bg_color(lv_color_white(),LV_OPA_30);
        minute->set_style_text_font(myfont->font(),LV_PART_MAIN);
        minute->set_style_bg_color(lv_color_hex(0X66B2FF),LV_OPA_0,LV_PART_SELECTED );
        minute->set_main_border(0,lv_color_white(),LV_OPA_0);
        minute->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
    if(minute1 == nullptr)
    {
        minute1 = new LvcppRoller(mparent);
        minute1->set_size(75,110);
        minute1->align_to(minute->myobj,LV_ALIGN_RIGHT_MID,120,0);
        minute1->set_options("0\n1\n2\n3\n4\n5\n6\n7\n8\n9",1);
        minute1->set_main_bg_img_src(TIME_BUTTON);
        minute1->set_main_bg_color(lv_color_white(),LV_OPA_30);
        minute1->set_style_text_font(myfont->font(),LV_PART_MAIN);
        minute1->set_style_bg_color(lv_color_hex(0X66B2FF),LV_OPA_0,LV_PART_SELECTED );
        minute1->set_main_border(0,lv_color_white(),LV_OPA_0);
        minute1->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
    if(second == nullptr)
    {
        second = new LvcppRoller(mparent);
        second->set_size(75,110);
        second->align_to(minute1->myobj,LV_ALIGN_RIGHT_MID,150,0);
        second->set_options("0\n1\n2\n3\n4\n5",1);
        second->set_main_bg_img_src(TIME_BUTTON);
        second->set_main_bg_color(lv_color_white(),LV_OPA_30);
        second->set_style_text_font(myfont->font(),LV_PART_MAIN);
        second->set_style_bg_color(lv_color_hex(0X66B2FF),LV_OPA_0,LV_PART_SELECTED );
        second->set_main_border(0,lv_color_white(),LV_OPA_0);
        second->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
    if(second1== nullptr)
    {
        second1 = new LvcppRoller(mparent);
        second1->set_size(75,110);
        second1->align_to(second->myobj,LV_ALIGN_RIGHT_MID,120,0);
        second1->set_main_bg_img_src(TIME_BUTTON);
        second1->set_options("0\n1\n2\n3\n4\n5\n6\n7\n8\n9",1);
        second1->set_main_bg_color(lv_color_white(),LV_OPA_30);
        second1->set_style_text_font(myfont->font(),LV_PART_MAIN);
        second1->set_style_bg_color(lv_color_hex(0X66B2FF),LV_OPA_0,LV_PART_SELECTED );
        second1->set_main_border(0,lv_color_white(),LV_OPA_0);
        second1->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
    if(paly_stop == nullptr)
    {
        paly_stop = new LvcppButton(mparent);
        paly_stop->add_txt("");
        paly_stop->set_size(116,116);
        paly_stop->align(LV_ALIGN_CENTER,-0,120);
        paly_stop->txt_font_size(20,0);
        //paly_stop->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
        paly_stop->set_main_bg_img_src(ON_PNG);
        paly_stop->txt_color(lv_color_hex(0xffffff));
        paly_stop->set_main_bg_color(lv_color_white(),LV_OPA_0);
        paly_stop->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
    if(resetbuttton == nullptr)
    {
        resetbuttton = new LvcppButton(mparent);
        resetbuttton->add_txt("");
        resetbuttton->set_size(116,116);
        resetbuttton->align_to(paly_stop->myobj,LV_ALIGN_RIGHT_MID,150,0);
        resetbuttton->txt_font_size(20,0);
        //paly_stop->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
        resetbuttton->txt_align(LV_ALIGN_CENTER,0,0);
        resetbuttton->set_main_bg_img_src(RESRT_PNG);
        resetbuttton->txt_color(lv_color_hex(0xffffff));
        resetbuttton->set_main_bg_color(lv_color_white(),LV_OPA_0);
        resetbuttton->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
    if(time == nullptr)
    {
        time = new LvcppButton(mparent);
        time->add_txt("");
        time->set_size(116,116);
        time->align_to(paly_stop->myobj,LV_ALIGN_RIGHT_MID,-150,0);
        time->txt_font_size(20,0);
        //paly_stop->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
        time->txt_align(LV_ALIGN_CENTER,0,0);
        time->set_main_bg_img_src(TIME_PNG);
        time->txt_color(lv_color_hex(0xffffff));
        time->set_main_bg_color(lv_color_white(),LV_OPA_0);
        time->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
    if(time_tip == nullptr)
    {
        time_tip = new LvcppLabel(mparent);
        time_tip->set_size(160,60);
        time_tip->align_to(time->myobj,LV_ALIGN_BOTTOM_MID,27,60);
        time_tip->txt_color(lv_color_white(),0);
        time_tip->txt_align(LV_ALIGN_CENTER);
        time_tip->set_txt("Positive timing");
        time_tip->txt_font_size(20,0);

    }
    if(play_stop_tip == nullptr)
    {
        play_stop_tip = new LvcppLabel(mparent);
        play_stop_tip->set_size(100,60);
        play_stop_tip->align_to(paly_stop->myobj,LV_ALIGN_BOTTOM_MID,27,60);
        play_stop_tip->set_txt("Start");
        play_stop_tip->txt_align(LV_ALIGN_CENTER);
        play_stop_tip->txt_color(lv_color_white(),0);
        play_stop_tip->txt_font_size(20,0);
    }
    if(resetbuttton_tip == nullptr)
    {
        resetbuttton_tip = new LvcppLabel(mparent);
        resetbuttton_tip->set_size(100,60);
        resetbuttton_tip->align_to(resetbuttton->myobj,LV_ALIGN_BOTTOM_MID,27,60);
        resetbuttton_tip->set_txt("Reset");
        resetbuttton_tip->txt_align(LV_ALIGN_CENTER);
        resetbuttton_tip->txt_color(lv_color_white(),0);
        resetbuttton_tip->txt_font_size(20,0);
    }
    if(dot == nullptr)
    {
        dot = new LvcppLabel(mparent);
        dot->set_size(50,78);
        dot->align_to(hour1->myobj,LV_ALIGN_RIGHT_MID,70,0);
        dot->set_txt("");
        dot->set_main_bg_img_src(DOT_PNG);
    }
    if(dot1 == nullptr)
    {
        dot1 = new LvcppLabel(mparent);
        dot1->set_size(50,78);
        dot1->align_to(minute1->myobj,LV_ALIGN_RIGHT_MID,70,0);
        dot1->set_txt("");
        dot1->set_main_bg_img_src(DOT_PNG);
    }
    if(back == nullptr)
    {
        back = new LvcppButton(mparent);
        back->add_txt("Back");
        back->set_size(159,46);
        back->align(LV_ALIGN_BOTTOM_MID,0,-30);
        back->txt_font_size(20,0);
        //paly_stop->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
        back->txt_align(LV_ALIGN_CENTER,0,0);
        back->set_main_bg_img_src(GO_BACK);
        back->txt_color(lv_color_hex(0xffffff));
        back->set_main_bg_color(lv_color_white(),LV_OPA_0);
        back->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
    clean_num_clickable();
}
void speech::reset_param()
{
    /*
   lv_obj_t* obj = lv_event_get_target(event); //获取事件产生的对象
   lv_indev_t* indev = lv_indev_get_act();  //获取活动界面输入设备
   lv_point_t vect;
   lv_indev_get_vect(indev, &vect); //获取vect point
   lv_coord_t x = lv_obj_get_x(obj) + vect.x; //计算x
   lv_coord_t y = lv_obj_get_y(obj) + vect.y; // 计算y
   lv_obj_set_pos(obj, x, y); //移动对象到x,y
   */
    paly_stop->set_main_bg_img_src(ON_PNG);
    play_stop_tip->set_txt("Start");
    hour->set_selected(0,LV_ANIM_ON);
    hour1->set_selected(0,LV_ANIM_ON);
    minute->set_selected(0,LV_ANIM_ON);
    minute1->set_selected(0,LV_ANIM_ON);
    second->set_selected(0,LV_ANIM_ON);
    second1->set_selected(0,LV_ANIM_ON);
    photo = 0;
}

void speech::clean_num_clickable(void)
{
    LV_LOG_USER("clean_num_clickable");
    hour->clicked_enable(true);
    hour1->clicked_enable(true);
    minute->clicked_enable(true);
    minute1->clicked_enable(true);
    second->clicked_enable(true);
    second1->clicked_enable(true);
}

void speech::update_num_clickable(void)
{
    LV_LOG_USER("update_num_clickable");
    hour->clicked_enable(false);
    hour1->clicked_enable(false);
    minute->clicked_enable(false);
    minute1->clicked_enable(false);
    second->clicked_enable(false);
    second1->clicked_enable(false);
}

void speech::sendcb(void (*callback)(void))
{
    sp_callback=callback;
}

void speech::btn_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    speech* opt = (speech*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target==opt->paly_stop->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            if(photo == 0)
            {
                opt->paly_stop->set_main_bg_img_src(OFF_PNG);
                opt->play_stop_tip->set_txt("Stop");
                photo = 1;
                timecnt = opt->hour->get_selected()*36000+opt->hour1->get_selected()*3600+opt->minute->get_selected()*600+opt->minute1->get_selected()*60+opt->second->get_selected()*10+opt->second1->get_selected();
                if(timecnt == 0)
                {
                    opt->paly_stop->set_main_bg_img_src(ON_PNG);
                    opt->play_stop_tip->set_txt("Start");
                    opt->update_num_clickable();
                    LV_LOG_USER("aaaaaaaaaaa");
                    photo = 0;
                }
                if(timecnt > 0 && photo == 0)
                {
                    timecnt = 0;
                    opt->paly_stop->set_main_bg_img_src(ON_PNG);
                    opt->play_stop_tip->set_txt("Start");
                    opt->update_num_clickable();
                    LV_LOG_USER("aaaaaaaaaaa");
                }
                //opt->resetbuttton->clicked_enable(true);
                //opt->time->clicked_enable(true);
                //opt->clean_num_clickable();
            }
            else
            {
                LV_LOG_USER("aaaaaaaaaaa");
                opt->paly_stop->set_main_bg_img_src(ON_PNG);
                opt->play_stop_tip->set_txt("Start");
                photo = 0;
                retimetmp = 0;
                //opt->resetbuttton->clicked_enable(false);
                //opt->time->clicked_enable(false);
                if(timetmp == 1)
                {
                    opt->update_num_clickable();
                }
            }
        }

    }
    else if(target==opt->resetbuttton->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->reset_param();
            opt->paly_stop->set_main_bg_img_src(ON_PNG);
            opt->play_stop_tip->set_txt("Start");
            photo = 0;
            timecnt = 0;
        }

    }

    else if(target==opt->time->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            if(timetmp == 0)
            {
                opt->time->set_main_bg_img_src(TIMEH_PNG);
                opt->time_tip->set_txt("Count down");
                opt->reset_param();
                opt->update_num_clickable();

                opt->paly_stop->set_main_bg_img_src(ON_PNG);
                opt->play_stop_tip->set_txt("Start");
                photo = 0;
                timecnt = 0;

                timetmp = 1;
            }
            else
            {
                opt->time->set_main_bg_img_src(TIME_PNG);
                opt->time_tip->set_txt("Positive timing");
                opt->reset_param();
                opt->clean_num_clickable();

                opt->paly_stop->set_main_bg_img_src(ON_PNG);
                opt->play_stop_tip->set_txt("Start");
                photo = 0;
                timecnt = 0;
                timetmp = 0;
            }
        }
    }

    else if(target==opt->back->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->sp_callback();
        }

    }

}

void speech::time_split(int time)
{
    if(time >= 0)
    {
        h1 = time/3600/10;
        h2 = time/3600%10;
        m1 = time%3600/60/10;
        m2 = time%3600/60%10;
        s1 = time%3600%60/10;
        s2 = time%3600%60%10;
        //LV_LOG_USER("h1 = %d,h2 =%d,m1 = %d,m2 = %d,s1 =%d,s2 = %d",h1,h2,m1,m2,s1,s2);

        hour->set_selected(h1,LV_ANIM_ON);
        hour1->set_selected(h2,LV_ANIM_ON);
        minute->set_selected(m1,LV_ANIM_ON);
        minute1->set_selected(m2,LV_ANIM_ON);
        second->set_selected(s1,LV_ANIM_ON);
        second1->set_selected(s2,LV_ANIM_ON);
    }
}

//loop run(must achieve)
void speech::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);

    if(photo == 1)
    {
        if(timetmp == 0)
        {
            if(retimetmp == 1)
            {
                timecnt = 0;
                paly_stop->set_main_bg_img_src(OFF_PNG);
                play_stop_tip->set_txt("Stop");
            }
            else
            {
                timecnt++;
                //LV_LOG_USER("timecnt =%d", timecnt);
                time_split(timecnt);

            }
            LV_LOG_USER("Positive timing");

        }
        else if(timetmp == 1 && timecnt > 0)
        {
            timecnt = hour->get_selected()*36000+hour1->get_selected()*3600+minute->get_selected()*600+minute1->get_selected()*60+second->get_selected()*10+second1->get_selected();
            LV_LOG_USER("timecnt =%d", timecnt);

            if(timecnt < 0)
            {


            }
            else
            {
                    timecnt--;
                    paly_stop->set_main_bg_img_src(OFF_PNG);
                    play_stop_tip->set_txt("Stop");
                    time_split(timecnt);
            }

            LV_LOG_USER("Count down");
        }
    }

}
