#include "votescreen.h"
#include "stbimage/va_image.h"


votescreen::votescreen(lv_obj_t* praent)
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


votescreen::~votescreen()
{
    if(bg!=nullptr)
    {
        free_image(bg);
        bg = nullptr;
    }
    if(tip != nullptr)
    {
        delete tip;
        tip = nullptr;
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

void votescreen::initial(void)
{
    if(tip == nullptr)
    {
        tip = new LvcppButton(mparent);
        tip->add_txt("Vote over");
        tip->set_size(300,200);
        tip->align(LV_ALIGN_CENTER,0,-250);
        tip->txt_font_size(40,0);
        //tip->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
        tip->txt_align(LV_ALIGN_BOTTOM_MID,-5,0);
        tip->txt_color(lv_color_hex(0xffffff));
        //tip->set_main_border(2,lv_color_white(),LV_OPA_100);
        tip->set_main_bg_color(lv_color_white(),LV_OPA_0);
        tip->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
    if(back == nullptr)
    {
        back = new LvcppButton(mparent);
        back->add_txt("Back");
        back->set_size(159,46);
        back->align(LV_ALIGN_BOTTOM_MID,0,-30);
        back->txt_font_size(20,0);
        //Other_requests->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
        back->txt_align(LV_ALIGN_CENTER,0,0);
        back->set_main_bg_img_src(GO_BACK);
        back->txt_color(lv_color_hex(0xffffff));
        back->set_main_bg_color(lv_color_white(),LV_OPA_0);
        back->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }

}

void votescreen::sendcb(void (*callback)(void))
{
    vote_callback=callback;
}

void votescreen::btn_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    votescreen* opt = (votescreen*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target==opt->back->myobj)//单机改名
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->vote_callback();
        }

    }
}

