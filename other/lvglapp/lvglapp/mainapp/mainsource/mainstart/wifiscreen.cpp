#include "wifiscreen.h"
#include "stbimage/va_image.h"


wifiscreen::wifiscreen(lv_obj_t* praent)
{
    mscreen = new LvcppScreen(lv_scr_act());
    mscreen->set_pos(0,0);
    mscreen->set_size(SCREEN_HOR_SIZE, SCREEN_VER_SIZE);
    mscreen->set_bg_color(lv_color_black(),LV_OPA_0);
    mparent = mscreen->get_screen();
    bg = parse_image_from_file("./resource/image/ui/bg.png");
    mscreen->showlogo((char*)bg, SCREEN_HOR_SIZE, SCREEN_VER_SIZE,0);
    //singletimer = startTimer(50,this);
    initial();
}


wifiscreen::~wifiscreen()
{
    if(bg!=nullptr)
    {
        free_image(bg);
        bg = nullptr;
    }
    if(Frame != nullptr)
    {
        delete Frame;
        Frame = nullptr;
    }
    if(back != nullptr)
    {
        delete back;
        back = nullptr;
    }
    if(mscreen != nullptr)
    {
        delete mscreen;
        mscreen = nullptr;
    }
}

void wifiscreen::initial(void)
{
    if(Frame == nullptr)
    {
        Frame = new LvcppLabel(mparent);
        Frame->set_txt("");
        Frame->set_size(805,416);
        Frame->align(LV_ALIGN_CENTER,0,0);
        Frame->txt_font_size(20,0);
        Frame->set_main_border(1,lv_color_white(),LV_OPA_30);
        //Frame->set_main_bg_img_src(WIFI_BUTTON);
        Frame->set_main_bg_color(lv_color_white(),LV_OPA_0);
        Frame->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
    if(head == nullptr)
    {
        head = new LvcppLabel(mparent);
        head->set_txt("");
        head->set_size(805,70);
        head->align(LV_ALIGN_CENTER,0,-173);
        head->txt_font_size(20,0);
        //Frame->set_main_bg_img_src(WIFI_BUTTON);
        head->set_main_bg_color(lv_color_white(),LV_OPA_10);
        head->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
    if(back == nullptr)
    {
        back = new LvcppButton(mparent);
        back->add_txt("Back");
        back->set_size(159,46);
        back->align(LV_ALIGN_BOTTOM_MID,0,-30);
        back->txt_font_size(20,0);
        //Frame->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
        back->txt_align(LV_ALIGN_CENTER,0,0);
        back->set_main_bg_img_src(GO_BACK);
        back->txt_color(lv_color_hex(0xffffff));
        back->set_main_bg_color(lv_color_white(),LV_OPA_0);
        back->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }

}

void wifiscreen::sendcb(void (*callback)(void))
{
    wifiscreen_callback=callback;
}

void wifiscreen::btn_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    wifiscreen* opt = (wifiscreen*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target==opt->back->myobj)//单机改名
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->wifiscreen_callback();
        }

    }
}
