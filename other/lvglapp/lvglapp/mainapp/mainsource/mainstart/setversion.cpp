#include "setversion.h"

#if (QTSIM_PLATFORM==0)
#ifdef __cplusplus
extern "C" {
#endif

#include  "mainstart/hotplugdetect/hotplugdetect.h"
#include  "mainstart/hotplugdetect/common/applib/applib.h"
#include  "mainstart/hotplugdetect/common/applib/app_config.h"

#ifdef __cplusplus
} /*extern "C"*/
#endif
#endif

static char softver[64]={0};
static char hardver[64]={0};

setversion::setversion(lv_obj_t *parent)
{
    ver_screen = new LvcppScreen(lv_scr_act());
    ver_screen->set_size(1024,600);
    ver_parent = ver_screen->get_screen();
    ver_screen->set_bg_color(lv_color_white(),LV_OPA_0);
    ver_screen->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    initial();
}

void setversion::initial()
{
    #if (QTSIM_PLATFORM==0)
    memset(softver,0,sizeof(softver));
    apl_get_config(CFG_SOFTVER,softver,sizeof(softver));
    memset(hardver,0,sizeof(hardver));
    apl_get_config(CFG_HWVER,hardver,sizeof(hardver));
    #endif

    if(bglabel == nullptr)
    {
        bglabel = new LvcppLabel(ver_parent);
        bglabel->set_size(480,100);
        bglabel->align(LV_ALIGN_CENTER,3,0);
        bglabel->set_txt("");
        bglabel->set_main_bg_color(lv_color_white(),LV_OPA_100);
    }
    if(hard == nullptr)
    {
        hard = new LvcppLabel(bglabel->myobj);
        hard->set_pos(10,10);
        hard->txt_color(lv_color_hex(0x000000),0);
        hard->set_size(120,40);
        hard->set_txt("硬件版本:");
        hard->txt_font_size(24,0);
    }
    if(soft == nullptr)
    {
        soft = new LvcppLabel(bglabel->myobj);
        soft->set_pos(10,60);
        soft->txt_color(lv_color_hex(0x000000),0);
        soft->set_size(120,40);
        soft->set_txt("软件版本:");
        soft->txt_font_size(24,0);
    }
    if(hardversion == nullptr)
    {
        hardversion = new LvcppLabel(bglabel->myobj);
        #if (QTSIM_PLATFORM==0)
        hardversion->set_txt(hardver);
        #else
        hardversion->set_txt("SSD220BA_V09");
        #endif
        hardversion->set_size(340,40);
        hardversion->txt_align(LV_TEXT_ALIGN_RIGHT);
        hardversion->align_to(hard->myobj,LV_ALIGN_OUT_RIGHT_TOP,0,0);
        hardversion->txt_color(lv_color_hex(0x000000),0);
        hardversion->txt_font_size(24,0);
    }
    if(softversion == nullptr)
    {
        softversion = new LvcppLabel(bglabel->myobj);
        #if (QTSIM_PLATFORM==0)
        softversion->set_txt(softver);
        #else
        softversion->set_txt("SS02db_HDYFX65_230228v1.00");
        #endif
        softversion->txt_align(LV_TEXT_ALIGN_RIGHT);
        softversion->align_to(soft->myobj,LV_ALIGN_OUT_RIGHT_TOP,0,0);
        softversion->set_size(340,40);
        softversion->txt_color(lv_color_hex(0x000000),0);
        softversion->txt_font_size(24,0);
    }
}

setversion::~setversion()
{
    if(hard == nullptr)
    {
        delete  hard;
        hard = nullptr;
    }
    if(soft == nullptr)
    {
        delete  soft;
        soft = nullptr;
    }
    if(hardversion == nullptr)
    {
        delete  hardversion;
        hardversion = nullptr;
    }
    if(softversion == nullptr)
    {
        delete  softversion;
        softversion = nullptr;
    }
    if(bglabel !=nullptr)
    {
        delete  bglabel;
        bglabel = nullptr;
    }
    if(ver_screen !=nullptr)
    {
        delete  ver_screen;
        ver_screen = nullptr;
    }
}

void setversion::btn_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    setversion* opt = (setversion*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target == opt->ver_parent)
    {
        opt->ver_callback();
    }
}

void setversion::sendcb(void (*callback)(void))
{
    ver_callback = callback;
}

