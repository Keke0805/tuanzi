#include "meetingscreen.h"
#include "stbimage/va_image.h"

meetingscreen * meeting_screen= nullptr;
meetingscreen::meetingscreen(lv_obj_t* praent)
{
    meeting_screen = this ;
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


meetingscreen::~meetingscreen()
{
    if(conference_agenda != nullptr)
    {
        delete conference_agenda;
        conference_agenda = nullptr;
    }
    if(content_of_meeting != nullptr)
    {
        delete content_of_meeting;
        content_of_meeting = nullptr;
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

void meetingscreen::initial(void)
{
    if(conference_agenda == nullptr)
    {
        conference_agenda = new LvcppButton(mparent);
        conference_agenda->add_txt("Agenda");
        conference_agenda->set_size(130,150);
        conference_agenda->align(LV_ALIGN_CENTER,-100,0);
        conference_agenda->txt_font_size(20,0);
        //conference_agenda->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
        conference_agenda->txt_align(LV_ALIGN_CENTER,0,0);
        conference_agenda->set_main_bg_img_src(AGENDA_PNG);
        conference_agenda->txt_align(LV_ALIGN_BOTTOM_MID,-5,0);
        conference_agenda->txt_color(lv_color_hex(0xffffff));
        //conference_agenda->set_main_border(2,lv_color_white(),LV_OPA_100);
        conference_agenda->set_main_bg_color(lv_color_white(),LV_OPA_0);
        conference_agenda->add_event_cb(btn_event_hander,LV_EVENT_RELEASED,this);
        conference_agenda->add_event_cb(btn_event_hander,LV_EVENT_PRESSING,this);
    }
    if(content_of_meeting == nullptr)
    {
        content_of_meeting = new LvcppButton(mparent);
        content_of_meeting->add_txt("Content");
        content_of_meeting->set_size(130,150);
        content_of_meeting->align_to(conference_agenda->myobj,LV_ALIGN_RIGHT_MID,200,0);
        content_of_meeting->txt_font_size(20,0);
        //content_of_meeting->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
        content_of_meeting->txt_align(LV_ALIGN_CENTER,0,0);
        content_of_meeting->set_main_bg_img_src(CONTENT_PNG);
        content_of_meeting->txt_align(LV_ALIGN_BOTTOM_MID,0,0);
        content_of_meeting->txt_color(lv_color_hex(0xffffff));
        content_of_meeting->set_main_bg_color(lv_color_white(),LV_OPA_0);
        content_of_meeting->add_event_cb(btn_event_hander,LV_EVENT_RELEASED,this);
        content_of_meeting->add_event_cb(btn_event_hander,LV_EVENT_PRESSING,this);
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


void meetingscreen::create_boxwindow()
{
    if(box_screen==nullptr)
    {
        box_screen = new boxtipscreen(mparent);
        box_screen->sendcb(box_cb);
    }
}

void meetingscreen::box_cb(void)
{
    if(meeting_screen->box_screen != nullptr)
    {
        delete meeting_screen->box_screen;
        meeting_screen->box_screen = NULL;
    }
}

void meetingscreen::sendcb(void (*callback)(void))
{
    meeting_callback=callback;
}

void meetingscreen::btn_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    meetingscreen* opt = (meetingscreen*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target==opt->conference_agenda->myobj)//单机改名
    {
        if(event->code == LV_EVENT_PRESSING)
        {
            opt->conference_agenda->set_main_bg_img_src(AGENDAH_PNG);
        }
        else  if(event->code == LV_EVENT_RELEASED)
        {
            opt->conference_agenda->set_main_bg_img_src(AGENDA_PNG);
            opt->create_boxwindow();
        }

    }
    else if(target==opt->content_of_meeting->myobj)//单机改名
    {
        if(event->code == LV_EVENT_PRESSING)
        {
            opt->content_of_meeting->set_main_bg_img_src(CONTENTH_PNG);
        }
        else  if(event->code == LV_EVENT_RELEASED)
        {
            opt->content_of_meeting->set_main_bg_img_src(CONTENT_PNG);
            opt->create_boxwindow();
        }

    }
    else if(target==opt->back->myobj)//单机改名
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->meeting_callback();
        }

    }

}

