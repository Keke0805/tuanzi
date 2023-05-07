#include "alarm.h"
#include "common/common.h"
#include "math.h"

void Alarm::ui_image_decode(void)
{
    SETTING_BACK_PNG=(void*)parse_image_from_file((char*)OTHER_GOBACK1_PNG_PATH);
    SETTING_ON_PNG=(void*)parse_image_from_file((char*)OTHER_ON_PNG_PATH);
    SETTING_OFF_PNG=(void*)parse_image_from_file((char*)OTHER_OFF_PNG_PATH);
    SETTING_ALARM_1_1_PNG=(void*)parse_image_from_file((char*)OTHER_ALARM_1_1_PNG_PATH);
    SETTING_ALARM_1_2_PNG=(void*)parse_image_from_file((char*)OTHER_ALARM_1_2_PNG_PATH);
    SETTING_ALARM_2_1_PNG=(void*)parse_image_from_file((char*)OTHER_ALARM_2_1_PNG_PATH);
    SETTING_ALARM_2_2_PNG=(void*)parse_image_from_file((char*)OTHER_ALARM_2_2_PNG_PATH);
}


Alarm::Alarm(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(parent);
    mscreen->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    mscreen->set_main_bg_color(lv_color_white(),LV_OPA_100);
    m_parent = mscreen->myobj;
    initial();
}

Alarm::~Alarm()
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
    if(colon!=nullptr)
    {
        delete colon;
        colon = nullptr;
    }
    if(minute!=nullptr)
    {
        delete minute;
        minute = nullptr;
    }
    if(time!=nullptr)
    {
        delete time;
        time = nullptr;
    }
    if(Alarm_num!=nullptr)
    {
        delete Alarm_num;
        Alarm_num = nullptr;
    }
    if(Alarm_num1!=nullptr)
    {
        delete Alarm_num1;
        Alarm_num1 = nullptr;
    }
    if(Alarm_one1!=nullptr)
    {
        delete Alarm_one1;
        Alarm_one1 = nullptr;
    }
    if(Alarm_one!=nullptr)
    {
        delete Alarm_one;
        Alarm_one = nullptr;
    }
    if(colon1 !=nullptr)
    {
        delete colon1;
        colon1 = nullptr;
    }
    if(minute1 !=nullptr)
    {
        delete minute1;
        minute1 = nullptr;
    }
    if(time1 !=nullptr)
    {
        delete time1;
        time1 = nullptr;
    }
    if(mscreen != NULL)
    {
        delete  mscreen;
        mscreen = NULL;
    }
}

void Alarm::initial(void)
{

    ui_image_decode();


    current_icon = new LvcppButton(m_parent);
    current_icon->align(LV_ALIGN_CENTER,0,-200);
    current_icon->add_txt("Alarm set");
    current_icon->txt_center();
    current_icon->set_main_bg_color(lv_color_white(),LV_OPA_100);
    current_icon->txt_color(lv_color_black());
    current_icon->txt_font_size(50,0);
    current_icon->set_size(230,90);

    back_icon = new LvcppButton(m_parent);
    back_icon->align(LV_ALIGN_CENTER,0,180);
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

    time = new LvcppButton(m_parent);
    time->align(LV_ALIGN_CENTER,-200,-70);
    time->set_size(70,70);
    time->add_txt("");
    time->txt_center();
    time->set_main_bg_color(lv_color_white(),LV_OPA_0);
    time->txt_color(lv_color_white());
    time->set_main_border(2,lv_color_black(),LV_OPA_100);
    if(hour1 == nullptr)
    {
    hour1 = new LvcppRoller(m_parent);
    hour1->set_size(60,150);
    hour1->align(LV_ALIGN_CENTER,-200,-70);
    hour1->set_options("00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23",LV_ROLLER_MODE_INFINITE);
    hour1->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    hour1->set_style_bg_color(lv_color_white(),LV_OPA_0,LV_PART_SELECTED );
    lv_obj_set_style_text_color(hour1->myobj,lv_color_black(),LV_PART_SELECTED);
    hour1->set_main_border(0,lv_color_white(),LV_OPA_100);
    hour1->set_visible_row_count(1);
    }
    alarm_on_1=new LvcppLabel(m_parent);
    alarm_on_1->align_to(time->myobj,LV_ALIGN_OUT_LEFT_MID,-20,-8);
    alarm_on_1->set_txt("");
    alarm_on_1->set_main_bg_img_src(SETTING_ALARM_1_2_PNG);
    alarm_on_1->set_size(50,50);

    colon = new LvcppLabel(m_parent);
    colon->align_to(time->myobj,LV_ALIGN_OUT_RIGHT_MID,10,-5);
    colon->set_size(50,50);
    colon->set_txt(":");
    colon->txt_font_size(30,0);

    minute = new LvcppButton(m_parent);
    minute->align_to(colon->myobj,LV_ALIGN_OUT_RIGHT_MID,-30,-36);
    minute->set_size(70,70);
    minute->add_txt("");
    minute->txt_color(lv_color_black());
    minute->txt_center();
    minute->set_main_bg_color(lv_color_white(),LV_OPA_0);
    minute->set_main_border(2,lv_color_black(),LV_OPA_100);
    if(minute_1 == nullptr)
    {
    minute_1 = new LvcppRoller(m_parent);
    minute_1->set_size(60,150);
    minute_1->align(LV_ALIGN_CENTER,-100,-70);
    minute_1->set_options("00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26"
                          "\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47\n48\n49\n50\n51\n52\n53\n54\n55\n56\n57\n58\n59",LV_ROLLER_MODE_INFINITE);
    minute_1->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    //minute_1->set_style_text_font(myfont->font(),LV_PART_MAIN);
    minute_1->set_style_bg_color(lv_color_white(),LV_OPA_0,LV_PART_SELECTED );
    //minute_1->set_main_border(0,lv_color_white(),LV_OPA_0);
    lv_obj_set_style_text_color(minute_1->myobj,lv_color_black(),LV_PART_SELECTED);
    minute_1->set_main_border(0,lv_color_white(),LV_OPA_100);
    minute_1->set_visible_row_count(1);
    }
    //minute->set_main_bg_color(lv_color_hex(0x444444),LV_OPA_80);
    //minute->txt_color(lv_color_white(),LV_OPA_100);



    Alarm_num = new LvcppButton(m_parent);
    Alarm_num->align_to(minute->myobj,LV_ALIGN_OUT_RIGHT_MID,10,-30);
    Alarm_num->set_size(100,70);
    Alarm_num->add_txt("");
    Alarm_num->txt_color(lv_color_black());
    Alarm_num->txt_font_size(30,0);
    Alarm_num->txt_center();
    Alarm_num->set_main_bg_color(lv_color_white(),LV_OPA_0);
    Alarm_num->set_main_border(2,lv_color_black(),LV_OPA_100);
    if(bell1 == nullptr)
    {
    bell1 = new LvcppRoller(m_parent);
    bell1->set_size(80,150);
    bell1->align(LV_ALIGN_CENTER,-5,-70);
    bell1->set_options("Alarm\nSiren",LV_ROLLER_MODE_INFINITE);
    bell1->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    bell1->set_style_bg_color(lv_color_white(),LV_OPA_0,LV_PART_SELECTED );
    lv_obj_set_style_text_color(bell1->myobj,lv_color_black(),LV_PART_SELECTED);
    bell1->set_main_border(0,lv_color_white(),LV_OPA_100);
    bell1->set_visible_row_count(1);
    }

 #if 0
    if(bell1== nullptr)
    {
        bell1=new LvcppDropdown(m_parent);
        bell1->set_size(90,60);
        bell1->set_options("Alarm\nSiren");
        bell1->align_to(Alarm_num->myobj,LV_ALIGN_CENTER,0,0);
        bell1->set_selected(1);
        bell1->set_selected_highlight(false);
        bell1->txt_font_size(90,0);
        bell1->txt_color(lv_color_black());
        bell1->set_dir(LV_DIR_BOTTOM);


        bell1->set_main_border(20,lv_color_black(),LV_OPA_0);



    }
#endif

    Alarm_one = new LvcppButton(m_parent);
    Alarm_one->align_to(Alarm_num->myobj,LV_ALIGN_OUT_RIGHT_MID,10,-30);
    Alarm_one->set_size(130,70);
    Alarm_one->add_txt("");
    Alarm_one->txt_color(lv_color_black());
    Alarm_one->txt_font_size(30,0);
    Alarm_one->txt_center();
    Alarm_one->set_main_bg_color(lv_color_white(),LV_OPA_0);
    Alarm_one->set_main_border(2,lv_color_black(),LV_OPA_100);

    if(cycle1== nullptr)
    {
    cycle1 = new LvcppRoller(m_parent);
    cycle1->set_size(120,150);
    cycle1->align(LV_ALIGN_CENTER,120,-70);
    cycle1->set_options("one\nworkday\neveryday\n",LV_ROLLER_MODE_INFINITE);
    cycle1->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    cycle1->set_style_bg_color(lv_color_white(),LV_OPA_0,LV_PART_SELECTED );
    lv_obj_set_style_text_color(cycle1->myobj,lv_color_black(),LV_PART_SELECTED);
    cycle1->set_main_border(0,lv_color_white(),LV_OPA_100);
    cycle1->set_visible_row_count(1);
    }

    on_and_off = new LvcppButton(m_parent);
    on_and_off->add_txt("");
    on_and_off->set_size(120,44);
    on_and_off->align_to(Alarm_one->myobj,LV_ALIGN_OUT_RIGHT_MID,20,0);
    on_and_off->set_main_bg_img_src(SETTING_ON_PNG);
    on_and_off->set_main_bg_color(lv_color_white(),LV_OPA_0);
    on_and_off->add_event_cb(clicked_event_handler,LV_EVENT_CLICKED,this);

    time1 = new LvcppButton(m_parent);
    time1->align(LV_ALIGN_CENTER,-200,30);
    time1->set_size(70,70);
    time1->add_txt("");
    time1->txt_font_size(30,0);
    time1->txt_center();
    time1->set_main_bg_color(lv_color_white(),LV_OPA_0);
    time1->txt_color(lv_color_white());
    time1->set_main_border(2,lv_color_black(),LV_OPA_100);
    if(hour2 == nullptr)
    {
    hour2 = new LvcppRoller(m_parent);
    hour2->set_size(60,150);
    hour2->align(LV_ALIGN_CENTER,-200,30);
    hour2->set_options("00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23",LV_ROLLER_MODE_INFINITE);
    hour2->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    hour2->set_style_bg_color(lv_color_white(),LV_OPA_0,LV_PART_SELECTED );
    lv_obj_set_style_text_color(hour2->myobj,lv_color_black(),LV_PART_SELECTED);
    hour2->set_main_border(0,lv_color_white(),LV_OPA_100);
    hour2->set_visible_row_count(1);
    }

    alarm_on_2=new LvcppLabel(m_parent);
    alarm_on_2->align_to(time1->myobj,LV_ALIGN_OUT_LEFT_MID,-20,-8);
    alarm_on_2->set_txt("");
    alarm_on_2->set_main_bg_img_src(SETTING_ALARM_2_2_PNG);
    alarm_on_2->set_size(50,50);

    colon1 = new LvcppLabel(m_parent);
    colon1->align_to(time1->myobj,LV_ALIGN_OUT_RIGHT_MID,10,-5);
    colon1->set_size(50,50);
    colon1->set_txt(":");
    colon1->txt_font_size(30,0);

    minute1 = new LvcppButton(m_parent);
    minute1->align_to(colon1->myobj,LV_ALIGN_OUT_RIGHT_MID,-30,-36);
    minute1->set_size(70,70);
    minute1->add_txt("");
    minute1->txt_color(lv_color_black());
    minute1->txt_font_size(30,0);
    minute1->txt_center();
    minute1->set_main_bg_color(lv_color_white(),LV_OPA_0);
    minute1->set_main_border(2,lv_color_black(),LV_OPA_100);
    //minute->set_main_bg_color(lv_color_hex(0x444444),LV_OPA_80);
    //minute->txt_color(lv_color_white(),LV_OPA_100);
    if(minute1_1 == nullptr)
    {
    minute1_1 = new LvcppRoller(m_parent);
    minute1_1->set_size(60,150);
    minute1_1->align(LV_ALIGN_CENTER,-100,30);
    minute1_1->set_options("00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26"
                          "\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47\n48\n49\n50\n51\n52\n53\n54\n55\n56\n57\n58\n59",LV_ROLLER_MODE_INFINITE);
    minute1_1->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    //minute_1->set_style_text_font(myfont->font(),LV_PART_MAIN);
    minute1_1->set_style_bg_color(lv_color_white(),LV_OPA_0,LV_PART_SELECTED );
    //minute_1->set_main_border(0,lv_color_white(),LV_OPA_0);
    lv_obj_set_style_text_color(minute1_1->myobj,lv_color_black(),LV_PART_SELECTED);
    minute1_1->set_main_border(0,lv_color_white(),LV_OPA_100);
    minute1_1->set_visible_row_count(1);
    }
    Alarm_num1 = new LvcppButton(m_parent);
    Alarm_num1->align_to(minute1->myobj,LV_ALIGN_OUT_RIGHT_MID,10,-30);
    Alarm_num1->set_size(100,70);
    Alarm_num1->add_txt("Siren");
    Alarm_num1->txt_color(lv_color_black());
    Alarm_num1->txt_font_size(30,0);
    Alarm_num1->txt_center();
    Alarm_num1->set_main_bg_color(lv_color_white(),LV_OPA_0);
    Alarm_num1->set_main_border(2,lv_color_black(),LV_OPA_100);
    if(bell2 == nullptr)
    {
    bell2 = new LvcppRoller(m_parent);
    bell2->set_size(80,150);
    bell2->align(LV_ALIGN_CENTER,-5,30);
    bell2->set_options("Alarm\nSiren",LV_ROLLER_MODE_INFINITE);
    bell2->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    bell2->set_style_bg_color(lv_color_white(),LV_OPA_0,LV_PART_SELECTED );
    lv_obj_set_style_text_color(bell2->myobj,lv_color_black(),LV_PART_SELECTED);
    bell2->set_main_border(0,lv_color_white(),LV_OPA_100);
    bell2->set_visible_row_count(1);
    }

    Alarm_one1 = new LvcppButton(m_parent);
    Alarm_one1->align_to(Alarm_num1->myobj,LV_ALIGN_OUT_RIGHT_MID,10,-30);
    Alarm_one1->set_size(130,70);
    Alarm_one1->add_txt("workday");
    Alarm_one1->txt_color(lv_color_black());
    Alarm_one1->txt_font_size(30,0);
    Alarm_one1->txt_center();
    Alarm_one1->set_main_bg_color(lv_color_white(),LV_OPA_0);
    Alarm_one1->set_main_border(2,lv_color_black(),LV_OPA_100);

    if(cycle2== nullptr)
    {
    cycle2 = new LvcppRoller(m_parent);
    cycle2->set_size(120,150);
    cycle2->align(LV_ALIGN_CENTER,120,30);
    cycle2->set_options("one\nworkday\neveryday\n",LV_ROLLER_MODE_INFINITE);
    cycle2->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    cycle2->set_style_bg_color(lv_color_white(),LV_OPA_0,LV_PART_SELECTED );
    lv_obj_set_style_text_color(cycle2->myobj,lv_color_black(),LV_PART_SELECTED);
    cycle2->set_main_border(0,lv_color_white(),LV_OPA_100);
    cycle2->set_visible_row_count(1);
    }

    on_and_off1 = new LvcppButton(m_parent);
    on_and_off1->add_txt("");
    on_and_off1->set_size(120,44);
    on_and_off1->align_to(Alarm_one1->myobj,LV_ALIGN_OUT_RIGHT_MID,20,0);
    on_and_off1->set_main_bg_img_src(SETTING_ON_PNG);
    on_and_off1->set_main_bg_color(lv_color_white(),LV_OPA_0);
    on_and_off1->add_event_cb(clicked_event_handler2,LV_EVENT_CLICKED,this);


    switch(choose)
        {
            case 0:
                alarm_on_1->set_main_bg_img_src(SETTING_ALARM_1_2_PNG);
                on_and_off->set_main_bg_img_src(SETTING_ON_PNG);
                break;
            case 1:
                alarm_on_1->set_main_bg_img_src(SETTING_ALARM_1_1_PNG);
                on_and_off->set_main_bg_img_src(SETTING_OFF_PNG);
                break;
    }
    maintimer = startTimer(20,this);
}


void  Alarm::btn_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    Alarm* opt = ( Alarm*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    if(target == opt->back_icon->myobj)
        {
            if(event->code == LV_EVENT_CLICKED)
            {
                if(opt->volume_callback)
                opt->volume_callback();

            }
        }
}
void Alarm::clicked_event_handler(lv_event_t *event)
{
    Alarm* opt = (Alarm*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    if(target==opt->on_and_off->myobj)
   {
       if(event->code == LV_EVENT_CLICKED)
       {
           if(opt->choose==1)
           {
               opt->on_and_off->set_main_bg_img_src(opt->SETTING_OFF_PNG);
               opt->alarm_on_1->set_main_bg_img_src(opt->SETTING_ALARM_1_1_PNG);
               opt->choose=0;

           }  else if(opt->choose==0)
           {
               opt->on_and_off->set_main_bg_img_src(opt->SETTING_ON_PNG);
               opt->alarm_on_1->set_main_bg_img_src(opt->SETTING_ALARM_1_2_PNG);
               opt->choose=1;
           }
       }
    }

}
void Alarm::clicked_event_handler2(lv_event_t *event)
{
    Alarm* opt = (Alarm*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    if(target==opt->on_and_off1->myobj)
   {
       if(event->code == LV_EVENT_CLICKED)
       {
           if(opt->choose==1)
           {
               opt->on_and_off1->set_main_bg_img_src(opt->SETTING_OFF_PNG);
               opt->alarm_on_2->set_main_bg_img_src(opt->SETTING_ALARM_2_1_PNG);
               opt->choose=0;

           }  else if(opt->choose==0)
           {
               opt->on_and_off1->set_main_bg_img_src(opt->SETTING_ON_PNG);
               opt->alarm_on_2->set_main_bg_img_src(opt->SETTING_ALARM_2_2_PNG);
               opt->choose=1;
           }
       }
    }

}


int Alarm::get_info(void)
{
    return choose;
}
void Alarm::sendcb(void (*callback)(void))
{
    volume_callback=callback;
}
//loop run(must achieve)
void Alarm::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    static int count = 0;//static variable once assign
}
