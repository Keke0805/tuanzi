#include "microphone.h"
#include "common/common.h"
#include "math.h"


using namespace LVGLOPTAPI;
//static int volume_tmp = 320;
void Microphone::ui_image_decode(void)
{
    Volume_B_PNG=(void*)parse_image_from_file((char*)OTHER_BAR_PNG_PATH);
    VOLUME_S_ICON=(void*)parse_image_from_file((char*)VOLUME_B_S_PNG_PATH);
    BAR_PNG1=(void*)parse_image_from_file((char*)OTHER_BAR_PNG_PATH);
}

void Microphone::ui_image_free(void)
{

    if(Volume_B_PNG !=NULL)
    {
        free_image(Volume_B_PNG);
        Volume_B_PNG = NULL;
    }
    if(VOLUME_S_ICON !=NULL)
    {
        free_image(VOLUME_S_ICON);
        VOLUME_S_ICON =NULL;
    }
    if(BAR_PNG1 !=NULL)
    {
        free_image(BAR_PNG1);
        BAR_PNG1 =NULL;
    }
}

void Microphone::deinitial(void)
{
    if(VOLUME_icon != nullptr)
    {
        delete  VOLUME_icon;
        VOLUME_icon = nullptr;
    }
    if(VOLUME_bar != nullptr)
    {
        delete  VOLUME_bar;
        VOLUME_bar = nullptr;
    }
    if(VOLUME_VALUE != nullptr)
    {
        delete  VOLUME_VALUE;
        VOLUME_VALUE = nullptr;
    }
    if(mscreen!=nullptr)
    {
        delete mscreen;
        mscreen = nullptr;
    }
}

Microphone::Microphone(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(parent);
    mscreen->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    mscreen->set_main_bg_color(lv_color_white(),LV_OPA_100);
    m_parent = mscreen->myobj;
    //initial(volume_tmp);
}

Microphone::~Microphone()
{
    deinitial();
    ui_image_free();
}

//User starts here
void Microphone::initial(int volume_tmp,char *value)
{
    ui_image_decode();


    VOLUME_icon = new LvcppLabel(m_parent);
    VOLUME_icon->align(LV_ALIGN_CENTER,-230,40);
    VOLUME_icon->set_size(30,30);
    VOLUME_icon->set_txt("");
    VOLUME_icon->set_main_bg_img_src(VOLUME_S_ICON);

    VOLUME_bar = new LvcppLabel(m_parent);
    VOLUME_bar->set_pos(770,570);
    VOLUME_bar->set_size(volume_tmp,20);
    VOLUME_bar->set_txt("");
    VOLUME_bar->set_main_bg_img_src(Volume_B_PNG);
    //Microphone_bar->set_main_bg_color(lv_color_black(),LV_OPA_80);
    //Microphone_bar->set_main_border(2,lv_color_hex(0x222222),LV_OPA_40);

    VOLUME_VALUE = new LvcppLabel(m_parent);
    VOLUME_VALUE->set_size(50,60);
    VOLUME_VALUE->set_txt(value);
    VOLUME_VALUE->align_to(VOLUME_bar->myobj,LV_ALIGN_OUT_RIGHT_MID,30,15);
    VOLUME_VALUE->set_main_bg_color(lv_color_white(),LV_OPA_0);
    //Microphone_VALUE->set_main_bg_color(lv_color_black(),LV_OPA_100);

    maintimer = startTimer(20,this);
}

void Microphone::down_volume(int volume_tmp)
{
    VOLUME_bar->set_size(volume_tmp,20);
    VOLUME_VALUE->align_to(VOLUME_bar->myobj,LV_ALIGN_OUT_RIGHT_MID,30,15);
}

void Microphone::up_volume(int volume_tmp)
{
    VOLUME_bar->set_size(volume_tmp,20);
    VOLUME_VALUE->align_to(VOLUME_bar->myobj,LV_ALIGN_OUT_RIGHT_MID,30,15);
}

//loop run(must achieve)
void Microphone::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    static int count = 0;//static variable once assign
}
