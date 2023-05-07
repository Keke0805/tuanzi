#include "clock.h"
#include "common/common.h"
#include "math.h"


using namespace LVGLOPTAPI;

void Clock::ui_image_decode(void)
{
    OTHER_GOBACK1_PNG=(void*)parse_image_from_file((char*)OTHER_GOBACK1_PNG_PATH);
    SAVE_PNG=(void*)parse_image_from_file((char*)OTHER_SAVE_PNG_PATH);
    SAVE1_PNG=(void*)parse_image_from_file((char*)OTHER_SAVE_1_PNG_PATH);
}

void Clock::ui_image_free(void)
{
    if(SAVE_PNG !=NULL)
    {
        free_image(SAVE_PNG);
        SAVE_PNG =NULL;
    }
    if(SAVE1_PNG !=NULL)
    {
        free_image(SAVE1_PNG);
        SAVE1_PNG =NULL;
    }
    if(OTHER_GOBACK1_PNG !=NULL)
    {
        free_image(OTHER_GOBACK1_PNG);
        OTHER_GOBACK1_PNG =NULL;
    }

}



Clock::~Clock()
{
    deinitial();
    ui_image_free();
}

Clock::Clock(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(parent);
    mscreen->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    mscreen->set_main_bg_color(lv_color_white(),LV_OPA_100);
    m_parent = mscreen->myobj;
    initial();
}


//User starts here
void Clock::initial(void)
{
    ui_image_decode();
    maintimer = startTimer(20,this);

    txt_tip = new LvcppLabel(m_parent);
    txt_tip->align(LV_ALIGN_CENTER,10,-200);
    txt_tip->set_size(200,50);
    txt_tip->set_txt("Time set");
    txt_tip->txt_font_size(50,0);


    time = new LvcppButton(m_parent);
    time->align(LV_ALIGN_CENTER,-40,-100);
    time->set_size(80,60);
    time->add_txt("");
    time->txt_font_size(30,0);
    time->txt_center();
    time->set_main_bg_color(lv_color_white(),LV_OPA_0);
    time->txt_color(lv_color_white());
    time->set_main_border(2,lv_color_black(),LV_OPA_100);
    if(hour == nullptr)
    {
    hour = new LvcppRoller(m_parent);
    hour->set_size(60,70);
    hour->align(LV_ALIGN_CENTER,-40,-100);
    hour->set_options("00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23",LV_ROLLER_MODE_INFINITE);
    hour->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    hour->set_style_bg_color(lv_color_white(),LV_OPA_0,LV_PART_SELECTED );
    lv_obj_set_style_text_color(hour->myobj,lv_color_black(),LV_PART_SELECTED);
    hour->set_main_border(0,lv_color_white(),LV_OPA_100);
    hour->set_visible_row_count(1);
    }

    colon = new LvcppLabel(m_parent);
    colon->align_to(time->myobj,LV_ALIGN_OUT_RIGHT_MID,10,-5);
    colon->set_size(50,50);
    colon->set_txt(":");
    colon->txt_font_size(30,0);

    minute = new LvcppButton(m_parent);
    minute->align_to(colon->myobj,LV_ALIGN_OUT_RIGHT_MID,-30,-31);
    minute->set_size(80,60);
    minute->add_txt("");
    minute->txt_color(lv_color_black());
    minute->txt_font_size(30,0);
    minute->txt_center();
    minute->set_main_bg_color(lv_color_white(),LV_OPA_0);
    minute->set_main_border(2,lv_color_black(),LV_OPA_100);
    //minute->set_main_bg_color(lv_color_hex(0x444444),LV_OPA_80);
    //minute->txt_color(lv_color_white(),LV_OPA_100);
    if(minute1 == nullptr)
    {
    minute1 = new LvcppRoller(m_parent);
    minute1->set_size(60,70);
    minute1->align_to(colon->myobj,LV_ALIGN_OUT_RIGHT_MID,-22,7);
    minute1->set_options("00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26"
                         "\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47\n48\n49\n50\n51\n52\n53\n54\n55\n56\n57\n58\n59",LV_ROLLER_MODE_INFINITE);
    minute1->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    minute1->set_style_bg_color(lv_color_white(),LV_OPA_0,LV_PART_SELECTED );
    lv_obj_set_style_text_color(minute1->myobj,lv_color_black(),LV_PART_SELECTED);
    minute1->set_main_border(0,lv_color_white(),LV_OPA_100);
    minute1->set_visible_row_count(1);
    }

    year = new LvcppButton(m_parent);
    year->align(LV_ALIGN_CENTER,-55,0);
    year->set_main_bg_color(lv_color_white(),LV_OPA_0);
    year->set_size(120,70);
    year->add_txt("");
    year->txt_color(lv_color_black());
    year->txt_font_size(30,0);
    year->txt_center();
    year->set_main_border(2,lv_color_black(),LV_OPA_100);
    if(year1 == nullptr)
    {
    year1 = new LvcppRoller(m_parent);
    year1->set_size(110,70);
    year1->align(LV_ALIGN_CENTER,-55,0);
    year1->set_options("1999\n2000\n2001\n2002\n2003\n2004\n2005\n2006\n2007\n2008\n2009\n2010\n2011\n2012\n2013\n2014\n2015\n2016\n2017\n2018\n2019\n2020\n2021\n2022\n2023\n2024\n2025"
                       "\n2026\n2027\n2028\n2029\n2030\n2031\n2032\n2033\n2034\n2035\n2036\n2037\n2038\n2039\n2040\n2041\n2042\n2043\n2044\n2045\n2046\n2047\n2048\n2049\n2050",LV_ROLLER_MODE_INFINITE);
    year1->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    year1->set_style_bg_color(lv_color_white(),LV_OPA_0,LV_PART_SELECTED );
    lv_obj_set_style_text_color(year1->myobj,lv_color_black(),LV_PART_SELECTED);
    year1->set_main_border(0,lv_color_white(),LV_OPA_100);
    year1->set_visible_row_count(1);
    }

    month = new LvcppButton(m_parent);
    month->align_to(year->myobj,LV_ALIGN_OUT_RIGHT_MID,5,-30);
    month->set_main_bg_color(lv_color_white(),LV_OPA_0);
    month->set_size(70,70);
    month->add_txt("3");
    month->txt_color(lv_color_black());
    month->txt_font_size(30,0);
    month->txt_center();
    month->set_main_border(2,lv_color_black(),LV_OPA_100);
    if(mouth1 == nullptr)
    {
    mouth1 = new LvcppRoller(m_parent);
    mouth1->set_size(60,80);
    mouth1->align_to(year->myobj,LV_ALIGN_OUT_RIGHT_MID,8,17);
    mouth1->set_options("1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12",LV_ROLLER_MODE_INFINITE);
    mouth1->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    mouth1->set_style_bg_color(lv_color_white(),LV_OPA_0,LV_PART_SELECTED );
    lv_obj_set_style_text_color(mouth1->myobj,lv_color_black(),LV_PART_SELECTED);
    mouth1->set_main_border(0,lv_color_white(),LV_OPA_100);
    mouth1->set_visible_row_count(1);
    }

    day = new LvcppButton(m_parent);
    day->align_to(month->myobj,LV_ALIGN_OUT_RIGHT_MID,5,-30);
    day->set_main_bg_color(lv_color_white(),LV_OPA_0);
    day->set_size(70,70);
    day->add_txt("");
    day->txt_color(lv_color_black());
    day->txt_font_size(30,0);
    day->txt_center();
    day->set_main_border(2,lv_color_black(),LV_OPA_100);
    if(day1 == nullptr)
    {
    day1 = new LvcppRoller(m_parent);
    day1->set_size(60,80);
    day1->align_to(month->myobj,LV_ALIGN_OUT_RIGHT_MID,9,17);
    day1->set_options("01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n2425\n26\n27\n28\n29\n30\n31\n",LV_ROLLER_MODE_INFINITE);
    day1->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_100);
    day1->set_style_bg_color(lv_color_white(),LV_OPA_0,LV_PART_SELECTED );
    lv_obj_set_style_text_color(day1->myobj,lv_color_black(),LV_PART_SELECTED);
    day1->set_main_border(0,lv_color_white(),LV_OPA_100);
    day1->set_visible_row_count(1);
    }


    current_icon = new LvcppButton(m_parent);
    current_icon->align(LV_ALIGN_CENTER,0,110);
    current_icon->set_size(60,60);
    current_icon->add_txt("");
    //current_icon->set_main_bg_color(lv_color_black(),LV_OPA_100);
    current_icon->set_main_bg_img_src(SAVE_PNG);
    current_icon->set_main_bg_color(lv_color_white(),LV_OPA_0);
    #if QTSIM_PLATFORM==0
    LvcppGroup::add_group_obj(get_key_group(),back_icon->myobj);
    #endif
    current_icon->add_event_cb(btn_event_hander,LV_EVENT_FOCUSED,this);
    current_icon->add_event_cb(btn_event_hander,LV_EVENT_KEY,this);
    current_icon->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);

    back_icon = new LvcppButton(m_parent);
    back_icon->align(LV_ALIGN_CENTER,0,180);
    back_icon->set_size(60,60);
    back_icon->add_txt("");
    //back_icon->set_main_bg_color(lv_color_black(),LV_OPA_100);
    back_icon->set_main_bg_img_src(OTHER_GOBACK1_PNG);
    back_icon->set_main_bg_color(lv_color_white(),LV_OPA_0);
    #if QTSIM_PLATFORM==0
    LvcppGroup::add_group_obj(get_key_group(),back_icon->myobj);
    #endif
    back_icon->add_event_cb(btn_event_hander,LV_EVENT_FOCUSED,this);
    back_icon->add_event_cb(btn_event_hander,LV_EVENT_KEY,this);
    back_icon->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
}

void Clock::deinitial(void)
{
    if(txt_tip!=nullptr)
    {
        delete txt_tip;
        txt_tip = nullptr;
    }
    if(current_icon!=nullptr)
    {
        delete current_icon;
        current_icon = nullptr;
    }
    if(back_icon!=nullptr)
    {
        delete back_icon;
        back_icon = nullptr;
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
    if(year!=nullptr)
    {
        delete year;
        year = nullptr;
    }
    if(month!=nullptr)
    {
        delete month;
        month = nullptr;
    }
    if(day!=nullptr)
    {
        delete day;
        day = nullptr;
    }

    if(mscreen!=nullptr)
    {
        delete mscreen;
        mscreen = nullptr;
    }
}

void  Clock::btn_event_hander(lv_event_t *event)
{
    Clock* opt = ( Clock*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    if(target==opt->current_icon->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->save_callback();
        }


    }
 else  if(target == opt->back_icon->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->volume_callback();
        }
    }
}


void Clock::sendcb(void (*callback)(void))
{
    volume_callback=callback;
    save_callback=callback;
}

//loop run(must achieve)
void Clock::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    static int count = 0;//static variable once assign
}
