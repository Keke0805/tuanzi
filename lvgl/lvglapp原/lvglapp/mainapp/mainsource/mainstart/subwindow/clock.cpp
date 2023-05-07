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
    time->set_size(70,70);
    time->add_txt("55");
    time->txt_font_size(30,0);
    time->txt_center();
    time->set_main_bg_color(lv_color_hex(0x444444),LV_OPA_80);
    time->txt_color(lv_color_white());
    time->set_main_border(2,lv_color_black(),LV_OPA_100);


    colon = new LvcppLabel(m_parent);
    colon->align_to(time->myobj,LV_ALIGN_OUT_RIGHT_MID,10,-5);
    colon->set_size(50,50);
    colon->set_txt(":");
    colon->txt_font_size(30,0);

    minute = new LvcppButton(m_parent);
    minute->align_to(colon->myobj,LV_ALIGN_OUT_RIGHT_MID,-30,-36);
    minute->set_size(70,70);
    minute->add_txt("39");
    minute->txt_color(lv_color_black());
    minute->txt_font_size(30,0);
    minute->txt_center();
    minute->set_main_bg_color(lv_color_white(),LV_OPA_0);
    minute->set_main_border(2,lv_color_black(),LV_OPA_100);
    //minute->set_main_bg_color(lv_color_hex(0x444444),LV_OPA_80);
    //minute->txt_color(lv_color_white(),LV_OPA_100);

    year = new LvcppButton(m_parent);
    year->align(LV_ALIGN_CENTER,-70,0);
    year->set_main_bg_color(lv_color_white(),LV_OPA_0);
    year->set_size(120,70);
    year->add_txt("2023");
    year->txt_color(lv_color_black());
    year->txt_font_size(30,0);
    year->txt_center();
    year->set_main_border(2,lv_color_black(),LV_OPA_100);


    month = new LvcppButton(m_parent);
    month->align_to(year->myobj,LV_ALIGN_OUT_RIGHT_MID,5,-30);
    month->set_main_bg_color(lv_color_white(),LV_OPA_0);
    month->set_size(70,70);
    month->add_txt("3");
    month->txt_color(lv_color_black());
    month->txt_font_size(30,0);
    month->txt_center();
    month->set_main_border(2,lv_color_black(),LV_OPA_100);

    day = new LvcppButton(m_parent);
    day->align_to(month->myobj,LV_ALIGN_OUT_RIGHT_MID,5,-30);
    day->set_main_bg_color(lv_color_white(),LV_OPA_0);
    day->set_size(70,70);
    day->add_txt("12");
    day->txt_color(lv_color_black());
    day->txt_font_size(30,0);
    day->txt_center();
    day->set_main_border(2,lv_color_black(),LV_OPA_100);



    current_icon = new LvcppLabel(m_parent);
    current_icon->align(LV_ALIGN_CENTER,0,110);
    current_icon->set_size(60,60);
    current_icon->set_txt("");
    //current_icon->set_main_bg_color(lv_color_black(),LV_OPA_100);
    current_icon->set_main_bg_img_src(SAVE_PNG);

    back_icon = new LvcppLabel(m_parent);
    back_icon->align(LV_ALIGN_CENTER,0,180);
    back_icon->set_size(60,60);
    back_icon->set_txt("");
    //back_icon->set_main_bg_color(lv_color_black(),LV_OPA_100);
    back_icon->set_main_bg_img_src(OTHER_GOBACK1_PNG);

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


//loop run(must achieve)
void Clock::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    static int count = 0;//static variable once assign
}
