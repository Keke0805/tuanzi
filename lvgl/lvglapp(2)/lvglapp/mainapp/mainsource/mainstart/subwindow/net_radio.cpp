#include "net_radio.h"
#include "common/common.h"
#include "math.h"

void Net_radio::ui_image_decode(void)
{
    RADIO_PNG=(void*)parse_image_from_file((char*)RADIO_PNG_PATH);
}

void Net_radio::ui_image_free(void)
{
    if(RADIO_PNG !=NULL)
    {
        free_image(RADIO_PNG);
        RADIO_PNG =NULL;
    }
}

void Net_radio::deinitial(void)
{

    if(current_icon != nullptr)
    {
        delete  current_icon;
        current_icon = nullptr;
    }
    if(mscreen!=nullptr)
    {
        delete mscreen;
        mscreen = nullptr;
    }
}


Net_radio::Net_radio(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(parent);
    mscreen->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    mscreen->set_main_bg_color(lv_color_white(),LV_OPA_100);
    m_parent = mscreen->myobj;
    initial();
}

Net_radio::~Net_radio()
{
    deinitial();
    ui_image_free();
}


//User starts here
void Net_radio::initial(void)
{
    ui_image_decode();
    maintimer = startTimer(20,this);

    current_icon = new LvcppLabel(m_parent);
    current_icon->align(LV_ALIGN_CENTER,0,-200);
    current_icon->set_size(130,130);
    current_icon->set_txt("");
    current_icon->set_main_bg_img_src(RADIO_PNG);

}

//loop run(must achieve)
void Net_radio::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    static int count = 0;//static variable once assign
}
