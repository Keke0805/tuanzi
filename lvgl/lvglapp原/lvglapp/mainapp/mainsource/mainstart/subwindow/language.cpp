#include "language.h"
#include "common/common.h"
#include "math.h"

Language* languageopt = nullptr;

Language::Language(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(parent);
    mscreen->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    mscreen->set_main_bg_color(lv_color_white(),LV_OPA_100);
    m_parent = mscreen->myobj;
    initial();
}

Language::~Language()
{
    if(txt_tip!=nullptr)
    {
        delete txt_tip;
        txt_tip = nullptr;
    }
    if(language_tip!=nullptr)
    {
        delete language_tip;
        language_tip = nullptr;
    }
    if(mscreen!=nullptr)
    {
        delete mscreen;
        mscreen = nullptr;
    }
}


void Language::initial(void)
{
    txt_tip = new LvcppLabel(m_parent);
    txt_tip->align(LV_ALIGN_CENTER,0,-200);
    txt_tip->set_size(350,100);
    txt_tip->set_txt("Language");
    txt_tip->txt_color(lv_color_hex(0x222222),0);
    txt_tip->txt_font_size(75,0);

    language_tip = new LvcppButton(m_parent);
    language_tip->align(LV_ALIGN_CENTER,0,-50);
    language_tip->set_size(400,60);
    language_tip->add_txt("Deutsch");
    language_tip->txt_font_size(30,0);
    language_tip->txt_color(lv_color_black());
    language_tip->txt_center();
    language_tip->set_main_radius(100);
    language_tip->set_main_bg_color(lv_color_hex(0x444444),LV_OPA_20);
    language_tip->set_main_border(2,lv_color_black(),LV_OPA_100);
    language_tip->add_event_cb(textarea_event_hander,LV_EVENT_CLICKED,this);


    maintimer = startTimer(20,this);
}


//loop run(must achieve)
void Language::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    static int count = 0;//static variable once assign
}
void Language::textarea_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    Language* opt = (Language*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target == opt->language_tip->myobj)
    {
        if(event->code == LV_EVENT_CLICKED)
        {
           //name_or_pass = 0;
           //opt->kb_create();
           //languageopt->input_kb->initial(3);
        }
    }


}
