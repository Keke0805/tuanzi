#include "sginscreen.h"
#include "stbimage/va_image.h"

sginscreen * sgin_screen= nullptr;
sginscreen::sginscreen(lv_obj_t* praent)
{
    sgin_screen = this;
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


sginscreen::~sginscreen()
{
    if(bg!=nullptr)
    {
        free_image(bg);
        bg = nullptr;
    }
    if(company != nullptr)
    {
        delete company;
        company = nullptr;
    }
    if(name != nullptr)
    {
        delete name;
        name = nullptr;
    }
    if(time != nullptr)
    {
        delete time;
        time = nullptr;
    }
    if(back != nullptr)
    {
        delete back;
        back = nullptr;
    }
    if(Sgin != nullptr)
    {
        delete Sgin;
        Sgin = nullptr;
    }
    if(mscreen != nullptr)
    {
        delete mscreen;
        mscreen = nullptr;
    }
}

void sginscreen::initial(void)
{
    if(company == nullptr)
    {
        company = new LvcppButton(mparent);
        company->add_txt("Company");
        company->set_size(300,66);
        company->align(LV_ALIGN_CENTER,0,-110);
        company->txt_font_size(20,0);
        company->txt_center();
        company->set_main_bg_img_src(PAINT_TEXT_BG_BUTTON);
        company->txt_align(LV_ALIGN_CENTER,-5,0);
        company->txt_color(lv_color_hex(0xffffff));
        company->set_main_bg_color(lv_color_white(),LV_OPA_0);
        company->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
    if(name == nullptr)
    {
        name = new LvcppButton(mparent);
        name->add_txt("Name");
        name->set_size(300,66);
        name->align_to(company->myobj,LV_ALIGN_OUT_BOTTOM_MID,0,30);
        name->txt_font_size(20,0);
        //name->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
        name->txt_center();
        name->set_main_bg_img_src(PAINT_TEXT_BG_BUTTON);
        name->txt_align(LV_ALIGN_CENTER,-5,0);
        name->txt_color(lv_color_hex(0xffffff));
        name->set_main_bg_color(lv_color_white(),LV_OPA_0);
        name->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
    if(time == nullptr)
    {
        time = new LvcppButton(mparent);
        time->add_txt("Time");
        time->set_size(300,66);
        time->align_to(name->myobj,LV_ALIGN_OUT_BOTTOM_MID,0,30);
        time->txt_font_size(20,0);
        //time->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
        time->txt_center();
        time->set_main_bg_img_src(PAINT_TEXT_BG_BUTTON);
        time->txt_align(LV_ALIGN_CENTER,-5,0);
        time->txt_color(lv_color_hex(0xffffff));
        time->set_main_bg_color(lv_color_white(),LV_OPA_0);
        time->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
    if(Sgin == nullptr)
    {
        Sgin = new LvcppButton(mparent);
        Sgin->add_txt("Sgin");
        Sgin->set_size(159,46);
        Sgin->align_to(time->myobj,LV_ALIGN_OUT_BOTTOM_MID,0,30);
        Sgin->txt_font_size(20,0);
        //Other_requests->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
        Sgin->txt_align(LV_ALIGN_CENTER,0,0);
        Sgin->set_main_bg_img_src(PAGE_BUTTON);
        Sgin->txt_color(lv_color_hex(0xffffff));
        Sgin->set_main_bg_color(lv_color_white(),LV_OPA_0);
        Sgin->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
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

void sginscreen::create_boxwindow()
{
    if(box_screen==nullptr)
    {
        box_screen = new boxtipscreen(mparent);
        box_screen->sendcb(box_cb);
    }
}

void sginscreen::box_cb(void)
{
    if(sgin_screen->box_screen != nullptr)
    {
        delete sgin_screen->box_screen;
        sgin_screen->box_screen = NULL;
    }
}

void sginscreen::sendcb(void (*callback)(void))
{
    sgin_callback=callback;
}

void sginscreen::btn_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    sginscreen* opt = (sginscreen*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target==opt->Sgin->myobj)//单机改名
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->create_boxwindow();
        }

    }
    else if(target==opt->back->myobj)//单机改名
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->sgin_callback();
        }

    }
}

