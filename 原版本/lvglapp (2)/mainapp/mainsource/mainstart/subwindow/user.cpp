#include "user.h"
#include "common/common.h"
#include "math.h"

User* useropt = nullptr;
static int name_or_pass = 0;
User::User(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(parent);
    mscreen->align(LV_ALIGN_CENTER,0,0);
    mscreen->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    mscreen->set_main_bg_color(lv_color_white(),LV_OPA_100);
    m_parent = mscreen->myobj;
    useropt = this;
    initial();
}

User::~User()
{
    ui_image_free();
    if(txt_tip != nullptr)
    {
        delete  txt_tip;
        txt_tip = nullptr;
    }
    if(back_icon != nullptr)
    {
        delete  back_icon;
        back_icon = nullptr;
    }
    if(user_name != nullptr)
    {
        delete  user_name;
        user_name = nullptr;
    }

    if(user_pass != nullptr)
    {
        delete  user_pass;
        user_pass = nullptr;
    }
    if(mscreen!=nullptr)
    {
        delete mscreen;
        mscreen = nullptr;
    }
}

void User::ui_image_free(void)
{
    if(BACK_PNG !=NULL)
    {
        free_image(BACK_PNG);
        BACK_PNG =NULL;
    }

}

void User::ui_image_decode(void)
{
    BACK_PNG=(void*)parse_image_from_file((char*)OTHER_GOBACK1_PNG_PATH);
}

void User::kb_create(void)
{
    if(input_kb == nullptr)
    {
        input_kb = new kbscreen(m_parent);
        input_kb->sendcb(kb_cb);
    }
}

void User::kb_cb(void)
{
    useropt->get_kbinput_text(name_or_pass);
    if(useropt->input_kb != nullptr)
    {
        delete useropt->input_kb;
        useropt->input_kb = NULL;
    }
}



void User::initial(void)
{
    ui_image_decode();

    txt_tip = new LvcppLabel(m_parent);
    txt_tip->align(LV_ALIGN_CENTER,.0,-200);
    txt_tip->set_size(200,70);
    txt_tip->set_txt("User");
    txt_tip->txt_color(lv_color_hex(0x222222),0);
    txt_tip->txt_font_size(75,0);
    txt_tip->txt_align(LV_TEXT_ALIGN_CENTER);

    back_icon = new LvcppButton(m_parent);
    back_icon->align(LV_ALIGN_CENTER,0,180);
    back_icon->set_size(60,60);
    back_icon->add_txt("");
    back_icon->set_main_bg_img_src(BACK_PNG);
    back_icon->set_main_bg_color(lv_color_white(),LV_OPA_0);

    user_name = new LvcppButton(m_parent);
    user_name->align(LV_ALIGN_CENTER,0,-50);
    user_name->set_size(400,60);
    user_name->add_txt("John123");
    user_name->txt_font_size(30,0);
    user_name->txt_color(lv_color_black());
    user_name->txt_center();
    user_name->set_main_radius(100);
    user_name->set_main_bg_color(lv_color_hex(0x444444),LV_OPA_20);
    user_name->set_main_border(2,lv_color_black(),LV_OPA_100);
    user_name->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);

    user_pass = new LvcppButton(m_parent);
    user_pass->align(LV_ALIGN_CENTER,0,20);
    user_pass->set_size(400,60);
    user_pass->add_txt("john@foxmail.com");
    user_pass->txt_font_size(30,0);
    user_pass->txt_color(lv_color_black());
    user_pass->txt_center();
    user_pass->set_main_radius(100);
    user_pass->set_main_bg_color(lv_color_hex(0x444444),LV_OPA_20);
    user_pass->set_main_border(2,lv_color_black(),LV_OPA_100);
    user_pass->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);

    maintimer = startTimer(20,this);
}

void User::get_kbinput_text(int type)
{
   if(type == 0)
   {
       user_name->add_txt(input_kb->input_box->get_text());
   }
   else
   {
       user_pass->add_txt(input_kb->input_box->get_text());
   }
}
//loop run(must achieve)
void User::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    static int count = 0;//static variable once assign
}


void User::textarea_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    User* opt = (User*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target == opt->user_name->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
           name_or_pass = 0;
           opt->kb_create();
           useropt->input_kb->initial(3);
        }
    }


    if(target == opt->user_pass->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            name_or_pass = 1;
            opt->kb_create();
            useropt->input_kb->initial(3);
        }
    }
}
