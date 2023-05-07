#include "version.h"
#include "common/common.h"
#include "math.h"


Version::Version(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(parent);
    mscreen->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    mscreen->set_main_bg_color(lv_color_white(),LV_OPA_100);
    m_parent = mscreen->myobj;
    initial();
}

void Version::ui_image_decode(void)
{
    BACK_PNG=(void*)parse_image_from_file((char*)OTHER_GOBACK1_PNG_PATH);
    VERSION_PNG=(void*)parse_image_from_file((char*)MAIN_MENU_VERSION_B_PNG_PATH);
}

void Version::ui_image_free(void)
{
    if(BACK_PNG !=NULL)
    {
        free_image(BACK_PNG);
        BACK_PNG =NULL;
    }
    if(VERSION_PNG !=NULL)
    {
        free_image(VERSION_PNG);
        VERSION_PNG =NULL;
    }

}

Version::~Version()
{
    deinitial();
    ui_image_free();
    if(current_icon != nullptr)
    {
        delete  current_icon;
        current_icon = nullptr;
    }
    if(back_icon != nullptr)
    {
        delete  back_icon;
        back_icon = nullptr;
    }
    if(txt_tip != nullptr)
    {
        delete  txt_tip;
        txt_tip = nullptr;
    }
    if(txt_s_tip != nullptr)
    {
        delete  txt_s_tip;
        txt_s_tip = nullptr;
    }
    if(mscreen != nullptr)
    {
        delete  mscreen;
        mscreen = nullptr;
    }
}

void Version::initial(void)
{
    ui_image_decode();

    current_icon = new LvcppButton(m_parent);
    current_icon->align(LV_ALIGN_CENTER,0,50);
    current_icon->set_size(130,130);
    current_icon->add_txt("");
    current_icon->set_main_bg_img_src(VERSION_PNG);
    current_icon->set_main_bg_color(lv_color_white(),LV_OPA_0);

    back_icon = new LvcppButton(m_parent);
    back_icon->align(LV_ALIGN_CENTER,0,180);
    back_icon->set_size(60,60);
    back_icon->add_txt("");
    back_icon->set_main_bg_img_src(BACK_PNG);
    back_icon->set_main_bg_color(lv_color_white(),LV_OPA_0);
    #if QTSIM_PLATFORM==0
    LvcppGroup::add_group_obj(get_key_group(),back_icon->myobj);
    #endif
    back_icon->add_event_cb(btn_event_hander,LV_EVENT_FOCUSED,this);
    back_icon->add_event_cb(btn_event_hander,LV_EVENT_KEY,this);
    back_icon->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    txt_tip = new LvcppLabel(m_parent);
    txt_tip->align(LV_ALIGN_CENTER,0,-200);
    txt_tip->set_size(300,70);
    txt_tip->set_txt("Version");
    txt_tip->txt_color(lv_color_hex(0x222222),0);
    txt_tip->txt_font_size(75,0);
    txt_tip->txt_align(LV_TEXT_ALIGN_CENTER);

    txt_s_tip = new LvcppLabel(m_parent);
    txt_s_tip->align(LV_ALIGN_CENTER,0,-40);
    txt_s_tip->set_size(260,100);
    txt_s_tip->txt_align(LV_TEXT_ALIGN_CENTER);
    txt_s_tip->txt_color(lv_color_hex(0x444444),0);
    txt_s_tip->set_txt("V2023_103");
    txt_s_tip->txt_font_size(20,0);
    txt_s_tip->txt_align(LV_TEXT_ALIGN_CENTER);

    maintimer = startTimer(20,this);
}
void Version::deinitial(void)
{

    if(current_icon != nullptr)
    {
        delete  current_icon;
        current_icon = nullptr;
    }
    if(back_icon != nullptr)
    {
        delete  back_icon;
        back_icon = nullptr;
    }
    if(txt_tip != nullptr)
    {
        delete  txt_tip;
        txt_tip = nullptr;
    }
    if(txt_s_tip != nullptr)
    {
        delete  txt_s_tip;
        txt_s_tip = nullptr;
    }
    if(mscreen!=nullptr)
    {
        delete mscreen;
        mscreen = nullptr;
    }
}

void  Version::btn_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    Version* opt = ( Version*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    if(target == opt->back_icon->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->volume_callback();
        }
    }
}
void Version::sendcb(void (*callback)(void))
{
    volume_callback=callback;
}
//loop run(must achieve)
void Version::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    static int count = 0;//static variable once assign
}
