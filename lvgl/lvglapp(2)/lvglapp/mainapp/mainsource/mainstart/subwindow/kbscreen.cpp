#include "kbscreen.h"
using namespace LVGLOPTAPI;
kbscreen* kbopt=nullptr;
kbscreen::kbscreen(lv_obj_t* parent)
{
    kb_screen = new LvcppScreen(lv_scr_act());
    kb_screen->set_bg_color(lv_color_white(),LV_OPA_100);
    kb_parent = kb_screen->get_screen();
    kb_screen->align(LV_ALIGN_CENTER,0,0);
    kb_screen->set_bg_color(lv_color_black(),LV_OPA_50);
    kb_screen->set_size(1024,600);
    kbopt = this;

    kb_screen->add_flag(LV_OBJ_FLAG_CLICKABLE);
    kb_screen->clear_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
    kb_screen->clear_flag(LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
    kb_screen->clear_flag(LV_OBJ_FLAG_SCROLL_CHAIN_VER);
    kb_screen->add_event_cb(kb_textarea_event_hander,LV_EVENT_PRESSING,this);
    kb_screen->add_event_cb(kb_textarea_event_hander,LV_EVENT_PRESSED,this);
}

void kbscreen::initial(int type)
{
    //myfont = new LvcppFreeTypeFont(32,0);
    if(input_box == nullptr)
    {
        input_box =new LvcppTextArea(kb_parent);
        input_box->set_pos(0,0);
        input_box->set_size(1024,250);
        input_box->set_main_radius(0);
        input_box->set_cursor_flicker(true);
        //input_box->set_one_line(true);
        //input_box->set_style_text_font(myfont->font(),0);
        input_box->set_max_length(50);
        input_box->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        input_box->add_event_cb(kb_textarea_event_hander,LV_EVENT_VALUE_CHANGED,this);
        input_box->add_event_cb(kb_textarea_event_hander,LV_EVENT_FOCUSED,this);
    }
    if(kb == nullptr)
    {
        kb =new LvcppKeyboard(kb_parent);
        //kb->set_text_font(myfont->font(),0);
        kb->set_textarea(input_box->myobj);
        kb->add_event_cb(kb_textarea_event_hander,LV_EVENT_VALUE_CHANGED,this);
        //lv_obj_add_event_cb(lv_ime_pinyin_get_kb(kb->myobj),kb_textarea_event_hander,LV_EVENT_VALUE_CHANGED,this);
        if(type == 4)
        {
            kb->set_mode(4);
            LV_LOG_USER("set_mode 4");
        }
        if(type == 3)
        {
            //kb->set_mode(1);
            LV_LOG_USER("set_mode");
        }
        if(type == 2)
        {
            kb->set_mode(4);
            LV_LOG_USER("set_mode 4 type == 2");
        }
        if(type == 1)
        {
            kb->set_mode(4);
            LV_LOG_USER("set_mode 4 type == 1");
        }
        kb_type = type;
    }
}

void kbscreen::sendcb(void (*callback)(void))
{
    kb_callback=callback;
}

kbscreen::~kbscreen()
{
    if(input_box != nullptr)
    {
        delete input_box;
        input_box =nullptr;
    }
    if(kb != nullptr)
    {
        delete kb;
        kb = nullptr;
    }
    if(kb_screen != nullptr)
    {
        delete  kb_screen;
        kb_screen = nullptr;
    }
}

void kbscreen::kb_textarea_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    kbscreen* opt = (kbscreen*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target==opt->kb_screen->myobj)
    {
        if(event->code == LV_EVENT_PRESSING)
        {
            lv_obj_t* obj = lv_event_get_target(event); //获取事件产生的对象
            lv_indev_t* indev = lv_indev_get_act();  //获取活动界面输入设备
            lv_point_t vect;
            lv_indev_get_vect(indev, &vect); //获取vect point
            lv_coord_t x = lv_obj_get_x(obj) + vect.x; //计算x
            lv_coord_t y = lv_obj_get_y(obj) + vect.y; // 计算y
            lv_obj_set_pos(obj, x, y); //移动对象到x,y
        }
        else if(event->code == LV_EVENT_PRESSED)
        {
            opt->kb_screen->move_foreground();
        }
    }
    if(opt->kb_type == 1)
    {
        if(target==opt->input_box->myobj)
        {
            if(event->code == LV_EVENT_FOCUSED)
            {
                opt->kb->set_textarea(opt->input_box->myobj);
            }
            int value = atoi(opt->input_box->get_text());
            if(value<1)
            {
                value=0;
            }
            if(value<1 && strlen(opt->input_box->get_text())>=2)
            {
                value=0;
                opt->input_box->set_text("0");
                return;
            }
            else if(value<10 && strlen(opt->input_box->get_text())==2)//01
            {
                 value = atoi(opt->input_box->get_text());
                 char string[25];
                 snprintf(string,sizeof(string),"%d",value);
                 opt->input_box->set_text(string);
            }
            else if(value>0 && value<100 && strlen(opt->input_box->get_text())==3)//005
            {
                value = atoi(opt->input_box->get_text());
                char string[25];
                snprintf(string,sizeof(string),"%d",value);
                opt->input_box->set_text(string);
            }
            else if(value>=10 && value<100 && strlen(opt->input_box->get_text())==3)//055
            {
                value = atoi(opt->input_box->get_text());
                char string[25];
                snprintf(string,sizeof(string),"%d",value);
                opt->input_box->set_text(string);
            }
        }
     }
     else
     {
        if(target==opt->input_box->myobj)
        {
            if(event->code == LV_EVENT_FOCUSED)
            {
                opt->kb->set_textarea(opt->input_box->myobj);
            }
        }
     }

}

