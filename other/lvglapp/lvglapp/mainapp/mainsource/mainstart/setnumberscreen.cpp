#include "setnumberscreen.h"
#include "stbimage/va_image.h"

setnumberscreen* setnumopt=nullptr;

setnumberscreen::setnumberscreen(lv_obj_t *parent,void* bg_png)
{
    num_screen = new LvcppScreen(lv_scr_act());
    num_screen->set_size(1024,600);
    num_parent = num_screen->get_screen();
    num_screen->set_bg_color(lv_color_white(),LV_OPA_100);
    num_screen->showlogo((char*)bg_png, SCREEN_HOR_SIZE, SCREEN_VER_SIZE,0);
    setnumopt = this;
    initial();
}

void setnumberscreen::initial()
{
    if(home_server == nullptr)
    {
        home_server = new LvcppButton(num_parent);
        home_server->add_txt("本地服务器");
        home_server->set_size(132,44);
        home_server->set_pos(850,150);
        home_server->txt_font_size(25,0);
        home_server->txt_align(LV_ALIGN_CENTER,0,0);
        home_server->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_70);
        home_server->txt_color(lv_color_hex(0xffffff));
        home_server->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
    if(cloud_server == nullptr)
    {
        cloud_server = new LvcppButton(num_parent);
        cloud_server->add_txt("云服务器");
        cloud_server->set_size(132,44);
        cloud_server->set_pos(850,220);
        cloud_server->txt_font_size(25,0);
        cloud_server->txt_align(LV_ALIGN_CENTER,0,0);
        cloud_server->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_20);
        cloud_server->txt_color(lv_color_hex(0xffffff));
        cloud_server->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
    if(go_back == nullptr)
    {
        go_back = new LvcppButton(num_parent);
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
    if(input_tip == nullptr)
    {
        input_tip = new LvcppLabel(num_parent);
        input_tip->set_txt("数字桌牌由三位数字组成，根据改名片摆放的位置，从1到999进行编号\n使用云服务器时，需要通过扫码或者添加MAC地址的方式把桌牌添加到账号");
        input_tip->set_pos(290,300);
        input_tip->txt_color(lv_color_hex(0xffffff),0);
        input_tip->txt_font_size(15,0);
        input_tip->set_size(520,100);
    }
    if(Table_number == nullptr)
    {
        Table_number = new LvcppLabel(num_parent);
        Table_number->set_txt("桌牌编号:");
        Table_number->set_pos(300,190);
        Table_number->txt_font_size(20,0);
        Table_number->txt_color(lv_color_hex(0xffffff),0);
        Table_number->set_size(110,100);
    }
    if(input_txt == nullptr)
    {
        input_txt = new LvcppButton(num_parent);
        input_txt->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        input_txt->set_pos(420,180);
        input_txt->set_size(200,40);
        #if (QTSIM_PLATFORM==0)
        input_txt->add_txt(g_zpcInfo.deskid);
        #else
        input_txt->add_txt("001");
        #endif
        input_txt->txt_font_size(32,0);
        input_txt->txt_center();
        input_txt->set_main_border(1,lv_color_hex(0xffffff),LV_OPA_100);
        input_txt->txt_color(lv_color_hex(0xffffff));
        input_txt->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
        input_txt->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
    #if (QTSIM_PLATFORM==0)
    if(g_zpcInfo.server_type==1)
    {
        home_server->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_20);
        cloud_server->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_70);
    }
    else
    {
        home_server->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_70);
        cloud_server->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_20);
    }
    #endif
}

setnumberscreen::~setnumberscreen()
{
    if(kb !=nullptr)
    {
        delete  kb;
        kb = nullptr;
    }
    if(input_kb !=nullptr)
    {
        delete  input_kb;
        input_kb = nullptr;
    }

    if(home_server !=nullptr)
    {
        delete  home_server;
        home_server = nullptr;
    }
    if(cloud_server !=nullptr)
    {
        delete  cloud_server;
        cloud_server = nullptr;
    }
    if(go_back !=nullptr)
    {
        delete  go_back;
        go_back = nullptr;
    }

    if(input_tip !=nullptr)
    {
        delete  input_tip;
        input_tip = nullptr;
    }
    if(Table_number !=nullptr)
    {
        delete  Table_number;
        Table_number = nullptr;
    }
    if(input_txt !=nullptr)
    {
        delete  input_txt;
        input_txt = nullptr;
    }

    if(num_screen !=nullptr)
    {
        delete  num_screen;
        num_screen = nullptr;
    }
}

void setnumberscreen::kb_create(void)
{
    if(input_kb == nullptr)
    {
        input_kb = new kbscreen(num_parent);
        input_kb->initial(1);
        input_kb->sendcb(kb_cb);
    }
}


void setnumberscreen::kb_cb(void)
{
    setnumopt->get_kbinput_text();
    if(setnumopt->input_kb != nullptr)
    {
        delete setnumopt->input_kb;
        setnumopt->input_kb = NULL;
    }
}

void setnumberscreen::get_kbinput_text(void)
{
    int id=0;
    char num[1024];
    memset(num,0,sizeof(num));
    id = atoi(input_kb->input_box->get_text());
    if(id<=0 || id>999)
    {
        return;
    }
    else
    {
        sprintf(num,"%03d",id);
        input_txt->add_txt(num);
    }
    #if (QTSIM_PLATFORM==0)
    zpc_msg_t msg;
    msg.type = ZPC_MSG_UPDATE_ID;
    msg.data_len = strlen(num);
    memset(msg.data_buf, 0, sizeof(msg.data_buf));
    strncpy(msg.data_buf,num,msg.data_len);
    SSTAR_ZPCMsg(&msg);
    #endif
}

void setnumberscreen::btn_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    setnumberscreen* opt = (setnumberscreen*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target == opt->go_back->myobj)
    {
        opt->num_callback();
    }
    else if(target == opt->input_txt->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            opt->kb_create();
        }
    }
    else if(target == opt->cloud_server->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            int g_type=1;
            #if (QTSIM_PLATFORM==0)
            zpc_msg_t msg;
            msg.type = ZPC_MSG_CHANGE_SERVER_TYPE;
            memcpy(msg.data_buf,&g_type, sizeof(g_type));
            SSTAR_ZPCMsg(&msg);
            #endif
            opt->home_server->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_20);
            opt->cloud_server->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_70);
        }
    }
    else if(target == opt->home_server->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            int g_type=0;
            #if (QTSIM_PLATFORM==0)
            zpc_msg_t msg;
            msg.type = ZPC_MSG_CHANGE_SERVER_TYPE;
            memcpy(msg.data_buf,&g_type, sizeof(g_type));
            SSTAR_ZPCMsg(&msg);
            #endif
            opt->home_server->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_70);
            opt->cloud_server->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_20);
        }
    }
}

void setnumberscreen::sendcb(void (*callback)(void))
{
    num_callback = callback;
}

