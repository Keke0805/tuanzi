#include "single_screen.h"
#include "stbimage/va_image.h"

using namespace LVGLIMAGE;
using namespace LVGLOPTAPI;

#define FILE_PATH_LONG 		1024


const char* list_button1[SETTING_LIST_ITEM] = {"Rename","Service","Sgin","Vote","Meeting","Speak","Message","Setting"};

//const char* list_button1[SETTING_LIST_ITEM] = {"单机改名","呼叫服务","会议签到","投票表决","会议内容","发言计时","短信接收","系统设置"};

single_screen * s_screen= nullptr;
single_screen::single_screen(lv_obj_t* parent)
{
    s_screen = this;
    mscreen = new LvcppScreen(lv_scr_act());
    mscreen->set_pos(0,0);
    mscreen->set_size(SCREEN_HOR_SIZE, SCREEN_VER_SIZE);
    mscreen->set_bg_color(lv_color_black(),LV_OPA_100);
    mparent = mscreen->get_screen();
    bg = parse_image_from_file("./resource/image/ui/bg.png");
    mscreen->showlogo((char*)bg, SCREEN_HOR_SIZE, SCREEN_VER_SIZE,0);
    singletimer = startTimer(50,this);
    initial();
}

single_screen::~single_screen()
{
    deinitial();
}


void single_screen::initial()
{

    //myfont = new LvcppFreeTypeFont(18,0);
    if(settingview == nullptr)
    {
        settingview = new LvcppList(mparent);
        settingview->set_size(800,300);
        settingview->set_pos(113,170);
        //settingview->align(LV_ALIGN_TOP_MID,0,100);
        settingview->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        settingview->set_main_pad_all(0);
        settingview->set_main_border_width(0);
        settingview->set_main_radius(0);
        settingview->set_main_shadow_width(0);
        settingview->set_flex_flow(LV_FLEX_FLOW_COLUMN_WRAP);
        settingview->set_flex_align(LV_FLEX_ALIGN_SPACE_BETWEEN,LV_FLEX_ALIGN_CENTER,LV_FLEX_ALIGN_SPACE_AROUND);
        //settingview->set_main_border(1,lv_color_hex(0xffffff),LV_OPA_20);
        settingview->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_0);
        settingview->switch_select_state(0, lv_color_hex(0x000000), lv_color_hex(0x000000));
     }
    memset(&btnlist,0,sizeof(btn_list_t1));
    for(int i= 0;i < SETTING_LIST_ITEM;i++)
    {
       if(btnlist.item[i] == nullptr)
       {
           btnlist.item[i] = new singlelist(settingview->myobj);
           btnlist.item[i]->set_txt(list_button1[i],i);
           btnlist.item[i]->set_logo_list(i,0);
           //LV_LOG_USER("list_button1[i]=%s",list_button1[i]);
           btnlist.item[i]->txt_list->add_event_cb(btn_event_hander,LV_EVENT_PRESSING,this);
           btnlist.item[i]->txt_list->add_event_cb(btn_event_hander,LV_EVENT_RELEASED,this);
       }
       settingview->set_select_state(0,lv_color_hex(0xff00ff));
   }
    if(idcard == nullptr)
    {
        idcard = new LvcppButton(mparent);
        idcard->add_txt("Incard");
        idcard->set_size(159,46);
        idcard->align(LV_ALIGN_BOTTOM_MID,0,-30);
        idcard->txt_font_size(20,0);
        //Other_requests->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
        idcard->txt_align(LV_ALIGN_CENTER,0,0);
        idcard->set_main_bg_img_src(INCARD_BUTTON);
        idcard->txt_color(lv_color_hex(0xffffff));
        idcard->set_main_bg_color(lv_color_white(),LV_OPA_0);
        idcard->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
}

void single_screen::deinitial()
{
    if(bg!=nullptr)
    {
        free_image(bg);
        bg = nullptr;
    }
    if(settingview != NULL)
    {
        delete settingview;
        settingview = NULL;
    }
    if(idcard != NULL)
    {
        delete idcard;
        idcard = NULL;
    }
    if(mscreen != NULL)
    {
        delete mscreen;
        mscreen = NULL;
    }
}

void single_screen::create_renamewindow()
{
    if(rename_screen==nullptr)
    {
        rename_screen = new RenameScreen(mparent);
        rename_screen->sendcb(re_cb);
    }
}

void single_screen::re_cb(void)
{
    if(s_screen->rename_screen != nullptr)
    {
        delete s_screen->rename_screen;
        s_screen->rename_screen = NULL;
    }
}


void single_screen::create_incardwindow()
{
    if(incard_screen == nullptr)
    {
        incard_screen = new IdcardScreen(mparent);
        //incard_screen->mscreen->show(true);
    }
    else
    {
        incard_screen->mscreen->show(true);
    }
}

void single_screen::incard_cb(void)
{
    if(s_screen->incard_screen != nullptr)
    {
        s_screen->incard_screen->mscreen->show(false);
    }
}


void single_screen::create_servicewindow()
{
    if(ser_screen==nullptr)
    {
        ser_screen = new service(mparent);
        ser_screen->sendcb(ser_cb);
    }
}

void single_screen::ser_cb(void)
{
    if(s_screen->ser_screen != nullptr)
    {
        delete s_screen->ser_screen;
        s_screen->ser_screen = NULL;
    }
}


void single_screen::create_sginwindow()
{
    if(sgin_screen==nullptr)
    {
        sgin_screen = new sginscreen(mparent);
        sgin_screen->sendcb(sgin_cb);
    }
}

void single_screen::sgin_cb(void)
{
    if(s_screen->sgin_screen != nullptr)
    {
        delete s_screen->sgin_screen;
        s_screen->sgin_screen = NULL;
    }
}

void single_screen::create_votewindow()
{
    if(vote_screen==nullptr)
    {
        vote_screen = new votescreen(mparent);
        vote_screen->sendcb(vote_cb);
    }
}

void single_screen::vote_cb(void)
{
    if(s_screen->vote_screen != nullptr)
    {
        delete s_screen->vote_screen;
        s_screen->vote_screen = NULL;
    }
}

void single_screen::create_meetingwindow()
{
    if(meet_sceen==nullptr)
    {
        meet_sceen = new meetingscreen(mparent);
        meet_sceen->sendcb(meet_cb);
    }
}

void single_screen::meet_cb(void)
{
    if(s_screen->meet_sceen != nullptr)
    {
        delete s_screen->meet_sceen;
        s_screen->meet_sceen = NULL;
    }
}


void single_screen::create_speechwindow()
{
    if(speech_screen==nullptr)
    {
        speech_screen = new speech(mparent);
        speech_screen->sendcb(speech_cb);
    }
    else
    {
        speech_screen->mscreen->show(true);
    }
}

void single_screen::speech_cb(void)
{
    if(s_screen->speech_screen != nullptr)
    {
        s_screen->speech_screen->mscreen->show(false);
        //delete s_screen->speech_screen;
        //s_screen->speech_screen = NULL;
    }
}


void single_screen::create_messagewindow()
{
    if(message_screen==nullptr)
    {
        message_screen = new messagescreen(mparent);
        message_screen->sendcb(message_cb);
    }
}

void single_screen::message_cb(void)
{
    if(s_screen->message_screen != nullptr)
    {
        delete s_screen->message_screen;
        s_screen->message_screen = NULL;
    }
}


void single_screen::create_wifiwindow()
{
    if(wifi_screen==nullptr)
    {
        wifi_screen = new wifiscreen(mparent);
        wifi_screen->sendcb(wifi_cb);
    }
}

void single_screen::wifi_cb(void)
{
    if(s_screen->wifi_screen != nullptr)
    {
        delete s_screen->wifi_screen;
        s_screen->wifi_screen = NULL;
    }
}

void single_screen::btn_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    single_screen* opt = (single_screen*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);


    if(target==opt->btnlist.item[0]->txt_list->myobj)//单机改名
    {
        if(event->code == LV_EVENT_PRESSING)
        {
            opt->btnlist.item[0]->set_logo_list(0,1);
        }
        else if(event->code == LV_EVENT_RELEASED)
        {
            opt->btnlist.item[0]->set_logo_list(0,0);

            opt->create_renamewindow();
        }
    }
    else if(target==opt->btnlist.item[1]->txt_list->myobj)//呼叫服务
    {
        if(event->code == LV_EVENT_PRESSING)
        {
            opt->btnlist.item[1]->set_logo_list(1,1);
        }
        else if(event->code == LV_EVENT_RELEASED)
        {
            opt->btnlist.item[1]->set_logo_list(1,0);
            opt->create_servicewindow();
        }
    }
    else if(target==opt->btnlist.item[2]->txt_list->myobj)//会议签到
    {
        if(event->code == LV_EVENT_PRESSING)
        {
            opt->btnlist.item[2]->set_logo_list(2,1);
        }
        else if(event->code == LV_EVENT_RELEASED)
        {
            opt->btnlist.item[2]->set_logo_list(2,0);
            opt->create_sginwindow();
        }
    }
    else if(target==opt->btnlist.item[3]->txt_list->myobj)//投票表决
    {
        if(event->code == LV_EVENT_PRESSING)
        {
            opt->btnlist.item[3]->set_logo_list(3,1);
        }
        else if(event->code == LV_EVENT_RELEASED)
        {
            opt->btnlist.item[3]->set_logo_list(3,0);
            opt->create_votewindow();
        }
    }
    else if(target==opt->btnlist.item[4]->txt_list->myobj)//会议内容
    {
        if(event->code == LV_EVENT_PRESSING)
        {
            opt->btnlist.item[4]->set_logo_list(4,1);
        }
        else if(event->code == LV_EVENT_RELEASED)
        {
            opt->btnlist.item[4]->set_logo_list(4,0);
            opt->create_meetingwindow();
        }
    }
    else if(target==opt->btnlist.item[5]->txt_list->myobj)//发言计时
    {
        if(event->code == LV_EVENT_PRESSING)
        {
            opt->btnlist.item[5]->set_logo_list(5,1);
        }
        else if(event->code == LV_EVENT_RELEASED)
        {
            opt->btnlist.item[5]->set_logo_list(5,0);
            opt->create_speechwindow();
        }
    }
    else if(target==opt->btnlist.item[6]->txt_list->myobj)//短信接收
    {
        if(event->code == LV_EVENT_PRESSING)
        {
            opt->btnlist.item[6]->set_logo_list(6,1);
        }
        else if(event->code == LV_EVENT_RELEASED)
        {
            opt->btnlist.item[6]->set_logo_list(6,0);
            opt->create_messagewindow();
        }
    }
    else if(target==opt->btnlist.item[7]->txt_list->myobj)//系统设置
    {
        if(event->code == LV_EVENT_PRESSING)
        {
            opt->btnlist.item[7]->set_logo_list(7,1);
        }
        else if(event->code == LV_EVENT_RELEASED)
        {
            opt->btnlist.item[7]->set_logo_list(7,0);
            opt->create_wifiwindow();
        }
    }
    else if(target==opt->idcard->myobj)//系统设置
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->create_incardwindow();
        }
    }
}


void single_screen::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    static int timecnt = 0;//static variable once assign

}
