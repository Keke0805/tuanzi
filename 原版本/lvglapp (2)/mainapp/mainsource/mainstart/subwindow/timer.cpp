#include "timer.h"
#include "common/common.h"
#include "math.h"


void Timer::ui_image_decode(void)
{
    SETTING_BACK_PNG=(void*)parse_image_from_file((char*)OTHER_GOBACK1_PNG_PATH);
    SETTING_ON_PNG=(void*)parse_image_from_file((char*)OTHER_ON_PNG_PATH);
    SETTING_OFF_PNG=(void*)parse_image_from_file((char*)OTHER_OFF_PNG_PATH);
    TIMER_EXCIRCLE_PNG=(void*)parse_image_from_file((char*)TIMER_EXCIRCLE_PNG_PATH);
    TIMER_FILLET_PNG=(void*)parse_image_from_file((char*)TIMER_FILLET_PNG_PATH);
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

    back_icon = new LvcppLabel(m_parent);
    back_icon->align(LV_ALIGN_CENTER,0,250);
    back_icon->set_size(60,60);
    back_icon->set_txt("");
    back_icon->set_main_bg_img_src(SETTING_BACK_PNG);

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

    time_value = new LvcppButton(m_parent);
    time_value->align(LV_ALIGN_CENTER,5,-53);
    time_value->add_txt("55");
    time_value->txt_center();
    time_value->set_main_bg_color(lv_color_white(),LV_OPA_0);
    time_value->txt_color(lv_color_black());
    time_value->txt_font_size(60,0);
    time_value->set_size(70,70);


    maintimer = startTimer(20,this);
}



//loop run(must achieve)
void Timer::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    static int count = 0;//static variable once assign

}
