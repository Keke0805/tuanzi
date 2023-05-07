#include "kbscreen.h"
using namespace LVGLOPTAPI;
kbscreen* kbopt=nullptr;
kbscreen::kbscreen(lv_obj_t* parent)
{
    kb_screen = new LvcppScreen(lv_scr_act());
    kb_screen->set_bg_color(lv_color_white(),LV_OPA_100);
    kb_parent = kb_screen->get_screen();
    kb_screen->set_size(1024,600);
    kbopt = this;
}

void kbscreen::initial(int type)
{
    myfont = new LvcppFreeTypeFont(32,0);
    if(input_box == nullptr)
    {
        input_box =new LvcppTextArea(kb_parent);
        input_box->set_pos(0,0);
        input_box->set_size(1024,250);
        input_box->set_main_radius(0);
        input_box->set_cursor_flicker(true);
        //input_box->set_one_line(true);
        input_box->set_style_text_font(myfont->font(),0);
        input_box->set_max_length(MAX_DATA_LENGTH);
        input_box->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
        input_box->add_event_cb(kb_textarea_event_hander,LV_EVENT_VALUE_CHANGED,this);
        input_box->add_event_cb(kb_textarea_event_hander,LV_EVENT_FOCUSED,this);
    }
    if(kb == nullptr)
    {
        kb =new LvcppKeyboard(kb_parent);
        kb->set_text_font(myfont->font(),0);
        kb->set_textarea(input_box->myobj);
        //kb->add_event_cb(kb_textarea_event_hander,LV_EVENT_VALUE_CHANGED,this);
        lv_obj_add_event_cb(lv_ime_pinyin_get_kb(kb->myobj),kb_textarea_event_hander,LV_EVENT_VALUE_CHANGED,this);
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

    if(opt->kb_type == 4)
    {
        if(target==opt->input_box->myobj)
        {
            if(event->code == LV_EVENT_FOCUSED)
            {
                opt->kb->set_textarea(opt->input_box->myobj);
            }
            else if(event->code == LV_EVENT_VALUE_CHANGED)
            {
                uint value = atoi(opt->input_box->get_text());
                if(value>255)
                {
                    value =255;
                    opt->input_box->set_text("255");
                }
                else if(value<1)
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
     }
    if(opt->kb_type == 1)
    {
        if(target==opt->input_box->myobj)
        {
            if(event->code == LV_EVENT_FOCUSED)
            {
                opt->kb->set_textarea(opt->input_box->myobj);
            }
            uint value = atoi(opt->input_box->get_text());
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
    else if(opt->kb_type == 2)
    {
        if(target==opt->input_box->myobj)
        {
            if(event->code == LV_EVENT_FOCUSED)
            {
                opt->kb->set_textarea(opt->input_box->myobj);
            }
            else if(event->code == LV_EVENT_VALUE_CHANGED)
            {
                uint value = atoi(opt->input_box->get_text());
                if(value>1024)
                {
                    value =1024;
                    opt->input_box->set_text("1024");
                }
                else if(value<1)
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

    const char *txt = lv_btnmatrix_get_btn_text(lv_ime_pinyin_get_kb(opt->kb->myobj),lv_btnmatrix_get_selected_btn(lv_ime_pinyin_get_kb(opt->kb->myobj)));
    if(txt == NULL) return;
    if(target==lv_ime_pinyin_get_kb(opt->kb->myobj))
    {
        if(strcmp(txt,LV_SYMBOL_OK)==0)
        {
             kbopt->kb_callback();
        }
    }

}

