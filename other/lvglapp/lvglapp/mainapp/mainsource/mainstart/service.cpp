#include "service.h"
#include "stbimage/va_image.h"

service * service_screen= nullptr;
service::service(lv_obj_t* praent)
{
    mscreen = new LvcppScreen(lv_scr_act());
    service_screen = this;
    mscreen->set_pos(0,0);
    mscreen->set_size(SCREEN_HOR_SIZE, SCREEN_VER_SIZE);
    mscreen->set_bg_color(lv_color_black(),LV_OPA_0);
    mparent = mscreen->get_screen();
    bg = parse_image_from_file("./resource/image/ui/bg.png");
    mscreen->showlogo((char*)bg, SCREEN_HOR_SIZE, SCREEN_VER_SIZE,0);
    //singletimer = startTimer(50,this);
    initial();
}


service::~service()
{
    if(tea != nullptr)
    {
        delete tea;
        tea = nullptr;
    }
    if(paper_and_pen != nullptr)
    {
        delete paper_and_pen;
        paper_and_pen = nullptr;
    }
    if(microphone != nullptr)
    {
        delete microphone;
        microphone = nullptr;
    }
    if(waiter != nullptr)
    {
        delete waiter;
        waiter = nullptr;
    }
    if(Other_requests != nullptr)
    {
        delete Other_requests;
        Other_requests = nullptr;
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

void service::initial(void)
{
    if(tea == nullptr)
    {
        tea = new LvcppButton(mparent);
        tea->add_txt("tea");
        tea->set_size(130,150);
        tea->align(LV_ALIGN_CENTER,-380,0);
        tea->txt_font_size(20,0);
        //tea->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
        tea->txt_align(LV_ALIGN_CENTER,0,0);
        tea->set_main_bg_img_src(TEA_PNG);
        tea->txt_align(LV_ALIGN_BOTTOM_MID,-5,0);
        tea->txt_color(lv_color_hex(0xffffff));
        //tea->set_main_border(2,lv_color_white(),LV_OPA_100);
        tea->set_main_bg_color(lv_color_white(),LV_OPA_0);
        tea->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
    if(paper_and_pen == nullptr)
    {
        paper_and_pen = new LvcppButton(mparent);
        paper_and_pen->add_txt("paper");
        paper_and_pen->set_size(130,150);
        paper_and_pen->align_to(tea->myobj,LV_ALIGN_RIGHT_MID,200,0);
        paper_and_pen->txt_font_size(20,0);
        //paper_and_pen->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
        paper_and_pen->txt_align(LV_ALIGN_CENTER,0,0);
        paper_and_pen->set_main_bg_img_src(PAPER_PNG);
        paper_and_pen->txt_align(LV_ALIGN_BOTTOM_MID,0,0);
        paper_and_pen->txt_color(lv_color_hex(0xffffff));
        paper_and_pen->set_main_bg_color(lv_color_white(),LV_OPA_0);
        paper_and_pen->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
    if(microphone == nullptr)
    {
        microphone = new LvcppButton(mparent);
        microphone->add_txt("microphone");
        microphone->set_size(130,150);
        microphone->align_to(paper_and_pen->myobj,LV_ALIGN_RIGHT_MID,200,0);
        microphone->txt_font_size(20,0);
        //microphone->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
        microphone->txt_align(LV_ALIGN_CENTER,0,0);
        microphone->set_main_bg_img_src(MICROPHOME_PNG);
        microphone->txt_align(LV_ALIGN_BOTTOM_MID,0,0);
        microphone->txt_color(lv_color_hex(0xffffff));
        microphone->set_main_bg_color(lv_color_white(),LV_OPA_0);
        microphone->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
    if(waiter == nullptr)
    {
        waiter = new LvcppButton(mparent);
        waiter->add_txt("waiter");
        waiter->set_size(130,150);
        waiter->align_to(microphone->myobj,LV_ALIGN_RIGHT_MID,200,0);
        waiter->txt_font_size(20,0);
        //waiter->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
        waiter->txt_align(LV_ALIGN_CENTER,0,0);
        waiter->set_main_bg_img_src(WAITER_PNG);
        waiter->txt_align(LV_ALIGN_BOTTOM_MID,0,0);
        waiter->txt_color(lv_color_hex(0xffffff));
        waiter->set_main_bg_color(lv_color_white(),LV_OPA_0);
        waiter->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
    if(Other_requests == nullptr)
    {
        Other_requests = new LvcppButton(mparent);
        Other_requests->add_txt("requests");
        Other_requests->set_size(130,150);
        Other_requests->align_to(waiter->myobj,LV_ALIGN_RIGHT_MID,200,0);
        Other_requests->txt_font_size(20,0);
        //Other_requests->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
        Other_requests->txt_align(LV_ALIGN_CENTER,0,0);
        Other_requests->set_main_bg_img_src(REQUESTS_PNG);
        Other_requests->txt_align(LV_ALIGN_BOTTOM_MID,-10,0);
        Other_requests->txt_color(lv_color_hex(0xffffff));
        Other_requests->set_main_bg_color(lv_color_white(),LV_OPA_0);
        Other_requests->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
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

void service::create_boxwindow()
{
    if(box_screen==nullptr)
    {
        box_screen = new boxtipscreen(mparent);
        box_screen->sendcb(box_cb);
    }
}

void service::box_cb(void)
{
    if(service_screen->box_screen != nullptr)
    {
        delete service_screen->box_screen;
        service_screen->box_screen = NULL;
    }
}


void service::kb_create(void)
{
    if(input_kb == nullptr)
    {
        input_kb = new kbscreen(mparent);
        input_kb->sendcb(kb_cb);
    }
}


void service::kb_cb(void)
{
    //renameopt->get_kbinput_text();
    if(service_screen->input_kb != nullptr)
    {
        delete service_screen->input_kb;
        service_screen->input_kb = NULL;
    }
}

void service::sendcb(void (*callback)(void))
{
    ser_callback=callback;
}

void service::btn_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    service* opt = (service*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target==opt->tea->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->create_boxwindow();
        }
    }
    else if(target==opt->paper_and_pen->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->create_boxwindow();
        }
    }
    else if(target==opt->microphone->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->create_boxwindow();
        }
    }
    else if(target==opt->waiter->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->create_boxwindow();
        }

    }
    else if(target==opt->Other_requests->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->kb_create();
            opt->input_kb->initial(3);
        }
    }
    else if(target==opt->back->myobj)//单机改名
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->ser_callback();
        }

    }
}

