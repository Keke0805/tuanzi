#include "boxtipscreen.h"
#include "stbimage/va_image.h"


boxtipscreen::boxtipscreen(lv_obj_t* praent)
{
    mscreen = new LvcppScreen(lv_scr_act());
    mscreen->set_pos(0,0);
    mscreen->set_size(430, 265);
    mscreen->center_align();
    mscreen->set_bg_color(lv_color_black(),LV_OPA_0);
    mparent = mscreen->get_screen();
    bg = parse_image_from_file("./resource/image/ui/box.png");
    mscreen->showlogo((char*)bg, SCREEN_HOR_SIZE, SCREEN_VER_SIZE,0);
    //singletimer = startTimer(50,this);
    initial();
}


boxtipscreen::~boxtipscreen()
{
    if(tips != nullptr)
    {
        delete tips;
        tips = nullptr;
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

void boxtipscreen::initial(void)
{
    if(tips == nullptr)
    {
        tips = new LvcppLabel(mparent);
        tips->set_txt("NULL");
        tips->set_size(400,120);
        tips->txt_center();
        //tips->align(LV_ALIGN_CENTER,0,0);
        tips->txt_font_size(40,0);
        //paper_and_pen->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
        //tips->txt_color(lv_color_hex(0xffffff));
        tips->set_main_bg_color(lv_color_white(),LV_OPA_0);
        tips->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
    if(back == nullptr)
    {
        back = new LvcppButton(mparent);
        back->add_txt("Back");
        back->set_size(159,46);
        back->align_to(tips->myobj,LV_ALIGN_BOTTOM_MID,0,20);
        back->txt_font_size(20,0);
        back->txt_align(LV_ALIGN_CENTER,0,0);
        back->set_main_bg_img_src(GO_BACK);
        back->txt_color(lv_color_hex(0xffffff));
        back->set_main_bg_color(lv_color_white(),LV_OPA_0);
        back->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }

}

void boxtipscreen::sendcb(void (*callback)(void))
{
    ser_callback=callback;
}

void boxtipscreen::btn_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    boxtipscreen* opt = (boxtipscreen*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target==opt->back->myobj)//单机改名
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->ser_callback();
        }

    }
}

