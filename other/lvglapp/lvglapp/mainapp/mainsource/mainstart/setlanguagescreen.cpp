#include "setlanguagescreen.h"
#include "stbimage/va_image.h"

setlanguagescreen::setlanguagescreen(lv_obj_t *parent,void* bg_png)
{
    la_screen = new LvcppScreen(lv_scr_act());
    la_screen->set_size(1024,600);
    la_parent = la_screen->get_screen();
    la_screen->set_bg_color(lv_color_white(),LV_OPA_100);
    la_screen->showlogo((char*)bg_png, SCREEN_HOR_SIZE, SCREEN_VER_SIZE,0);
    initial();
}

void setlanguagescreen::initial()
{
    if(Chinese == nullptr)
    {
        Chinese = new LvcppButton(la_parent);
        Chinese->add_txt("中文");
        Chinese->set_size(132,44);
        Chinese->set_pos(450,200);
        Chinese->txt_font_size(25,0);
        Chinese->txt_align(LV_ALIGN_CENTER,0,0);
        Chinese->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_70);
        Chinese->txt_color(lv_color_hex(0xffffff));
        Chinese->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
    if(English == nullptr)
    {
        English = new LvcppButton(la_parent);
        English->add_txt("English");
        English->set_size(132,44);
        English->set_pos(450,310);
        English->txt_font_size(25,0);
        English->txt_align(LV_ALIGN_CENTER,0,0);
        English->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_20);
        English->txt_color(lv_color_hex(0xffffff));
        English->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
    if(go_back == nullptr)
    {
        go_back = new LvcppButton(la_parent);
        go_back->add_txt("返回");
        go_back->set_size(159,46);
        go_back->align(LV_ALIGN_BOTTOM_MID,0,-30);
        go_back->txt_font_size(20,0);
        go_back->txt_align(LV_ALIGN_CENTER,0,0);
        //go_back->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
        go_back->set_main_bg_img_src(GO_BACK);
        go_back->txt_color(lv_color_hex(0xffffff));
        go_back->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
}

setlanguagescreen::~setlanguagescreen()
{
    if(Chinese !=nullptr)
    {
        delete  Chinese;
        Chinese = nullptr;
    }
    if(English !=nullptr)
    {
        delete  English;
        English = nullptr;
    }
    if(go_back !=nullptr)
    {
        delete  go_back;
        go_back = nullptr;
    }
    if(la_screen !=nullptr)
    {
        delete  la_screen;
        la_screen = nullptr;
    }
}

void setlanguagescreen::btn_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    setlanguagescreen* opt = (setlanguagescreen*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target == opt->go_back->myobj)
    {
        opt->la_callback();
    }
    else if(target == opt->Chinese->myobj)
    {
        opt->English->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_20);
        opt->Chinese->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_70);
        opt->go_back->add_txt("返回");
    }
    else if(target == opt->English->myobj)
    {
        opt->Chinese->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_20);
        opt->English->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_70);
        opt->go_back->add_txt("go back");
    }
}

void setlanguagescreen::sendcb(void (*callback)(void))
{
    la_callback = callback;
}
