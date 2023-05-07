#include "bluetooth.h"
#include "common/common.h"
#include "math.h"

using namespace LVGLOPTAPI;

void Bluetooth::ui_image_decode(void)
{
    BLUETOOTH_PNG=(void*)parse_image_from_file((char*)BLUETOOTH_PNG_PATH);
    OTHER_GOBACK1_PNG=(void*)parse_image_from_file((char*)OTHER_GOBACK1_PNG_PATH);
    OTHER_GOBACK2_PNG=(void*)parse_image_from_file((char*)OTHER_GOBACK2_PNG_PATH);
}

void Bluetooth::ui_image_free(void)
{
    if(BLUETOOTH_PNG !=NULL)
    {
        free_image(BLUETOOTH_PNG);
        BLUETOOTH_PNG =NULL;
    }
    if(OTHER_GOBACK1_PNG !=NULL)
    {
        free_image(OTHER_GOBACK1_PNG);
        OTHER_GOBACK1_PNG =NULL;
    }
    if(OTHER_GOBACK2_PNG !=NULL)
    {
        free_image(OTHER_GOBACK2_PNG);
        OTHER_GOBACK2_PNG =NULL;
    }
}

Bluetooth::Bluetooth(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(parent);
    mscreen->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    mscreen->set_main_bg_color(lv_color_white(),LV_OPA_100);
    m_parent = mscreen->myobj;
    initial();
}

Bluetooth::~Bluetooth()
{
    deinitial();
    ui_image_free();
}


//User starts here
void Bluetooth::initial(void)
{
    ui_image_decode();
    maintimer = startTimer(20,this);

    current_icon = new LvcppLabel(m_parent);
    current_icon->align(LV_ALIGN_CENTER,0,-200);
    current_icon->set_size(130,130);
    current_icon->set_txt("");
    current_icon->set_main_bg_img_src(BLUETOOTH_PNG);

    back_icon = new LvcppLabel(m_parent);
    back_icon->align(LV_ALIGN_CENTER,0,180);
    back_icon->set_size(60,60);
    back_icon->set_txt("");
    back_icon->set_main_bg_img_src(OTHER_GOBACK1_PNG);

    txt_tip = new LvcppLabel(m_parent);
    txt_tip->align(LV_ALIGN_CENTER,10,-50);
    txt_tip->set_size(200,50);
    txt_tip->set_txt("AMOZOL-1");
    txt_tip->txt_font_size(50,0);

    txt_s_tip = new LvcppLabel(m_parent);
    txt_s_tip->align(LV_ALIGN_CENTER,20,70);
    txt_s_tip->set_size(260,100);
    txt_s_tip->txt_align(LV_TEXT_ALIGN_CENTER);
    txt_s_tip->txt_color(lv_color_hex(0x444444),0);
    txt_s_tip->set_txt("waiting for connection ...\n(iPhone connected)");
    txt_s_tip->txt_font_size(20,0);
}

void Bluetooth::deinitial(void)
{
    if(current_icon != nullptr)
    {
        delete  current_icon;
        current_icon = nullptr;
    }
    if(back_icon != nullptr)
    {
        delete  back_icon;
        back_icon = nullptr;
    }
    if(txt_tip != nullptr)
    {
        delete  txt_tip;
        txt_tip = nullptr;
    }
    if(txt_s_tip != nullptr)
    {
        delete  txt_s_tip;
        txt_s_tip = nullptr;
    }
    if(mscreen!=nullptr)
    {
        delete mscreen;
        mscreen = nullptr;
    }
}


//loop run(must achieve)
void Bluetooth::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    static int count = 0;//static variable once assign
}
