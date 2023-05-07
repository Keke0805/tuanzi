#include "wifi.h"
#include "common/common.h"
#include "math.h"

void Wifi::ui_image_decode(void)
{
    SETTING_BACK_PNG=(void*)parse_image_from_file((char*)OTHER_GOBACK1_PNG_PATH);
    SETTING_WIFI_PNG=(void*)parse_image_from_file((char*)WIFI_JPG_PATH);
    SETTING_ON_PNG=(void*)parse_image_from_file((char*)OTHER_ON_PNG_PATH);
    SETTING_OFF_PNG=(void*)parse_image_from_file((char*)OTHER_OFF_PNG_PATH);
}


Wifi::Wifi(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(parent);
    mscreen->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    mscreen->set_main_bg_color(lv_color_white(),LV_OPA_100);
    m_parent = mscreen->myobj;
    initial();
}

Wifi::~Wifi()
{
    if(SETTING_BACK_PNG != NULL)
    {
        free_image(SETTING_BACK_PNG);
        SETTING_BACK_PNG = NULL;
    }
    if(SETTING_WIFI_PNG != NULL)
    {
        free_image(SETTING_WIFI_PNG);
        SETTING_WIFI_PNG = NULL;
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
    if(mscreen != NULL)
    {
        delete  mscreen;
        mscreen = NULL;
    }
}

void Wifi::initial(void)
{
    ui_image_decode();

    current_icon = new LvcppLabel(m_parent);
    current_icon->align(LV_ALIGN_CENTER,0,-200);
    current_icon->set_main_bg_img_src(SETTING_WIFI_PNG);
    current_icon->set_txt("");
    current_icon->txt_font_size(100,0);
    current_icon->set_size(219,90);

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

    on_and_off = new LvcppButton(m_parent);
    on_and_off->add_txt("");
    on_and_off->set_size(120,44);
    on_and_off->align(LV_ALIGN_CENTER,0,-130);
    on_and_off->set_main_bg_img_src(SETTING_ON_PNG);
    on_and_off->set_main_bg_color(lv_color_white(),LV_OPA_0);

    maintimer = startTimer(20,this);
}


void  Wifi::btn_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    Wifi* opt = ( Wifi*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    if(target == opt->back_icon->myobj)
        {
            if(event->code == LV_EVENT_CLICKED)
            {
                opt->volume_callback();
            }
        }
    }


void Wifi::sendcb(void (*callback)(void))
{
    volume_callback=callback;
}
//loop run(must achieve)
void Wifi::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    static int count = 0;//static variable once assign
}
