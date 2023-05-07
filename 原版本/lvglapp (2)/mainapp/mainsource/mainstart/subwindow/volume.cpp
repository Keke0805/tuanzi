#include "volume.h"
#include "common/common.h"
#include "math.h"

using namespace LVGLOPTAPI;
void Volume::ui_image_decode(void)
{
    Volume_PNG=(void*)parse_image_from_file((char*)VOLUME_PNG_PATH);
    EQ_B_PNG=(void*)parse_image_from_file((char*)EQ_setting_b_S_PNG_PATH);
    EQ_S_PNG=(void*)parse_image_from_file((char*)EQ_setting_S_S_PNG_PATH);
    Volume_B_PNG=(void*)parse_image_from_file((char*)VOLUME_B_S_PNG_PATH);
    Volume_S_PNG=(void*)parse_image_from_file((char*)VOLUME_S_S_PNG_PATH);
    BACK_PNG=(void*)parse_image_from_file((char*)OTHER_GOBACK1_PNG_PATH);

    BAR_PNG=(void*)parse_image_from_file((char*)OTHER_BAR_PNG_PATH);
    BAR_PNG1=(void*)parse_image_from_file((char*)OTHER_BAR_1_PNG_PATH);
}

void Volume::ui_image_free(void)
{
    if(Volume_PNG !=NULL)
    {
        free_image(Volume_PNG);
        Volume_PNG = NULL;
    }
    if(EQ_B_PNG !=NULL)
    {
        free_image(EQ_B_PNG);
        EQ_B_PNG = NULL;
    }
    if(EQ_S_PNG !=NULL)
    {
        free_image(EQ_S_PNG);
        EQ_S_PNG = NULL;
    }
    if(Volume_B_PNG !=NULL)
    {
        free_image(Volume_B_PNG);
        Volume_B_PNG = NULL;
    }
    if(Volume_S_PNG !=NULL)
    {
        free_image(Volume_S_PNG);
        Volume_S_PNG = NULL;
    }
    if(BACK_PNG !=NULL)
    {
        free_image(BACK_PNG);
        BACK_PNG =NULL;
    }
    if(BAR_PNG !=NULL)
    {
        free_image(BAR_PNG);
        BAR_PNG =NULL;
    }
    if(BAR_PNG1 !=NULL)
    {
        free_image(BAR_PNG1);
        BAR_PNG1 =NULL;
    }
}

void Volume::deinitial(void)
{

    if(current_icon != nullptr)
    {
        delete  current_icon;
        current_icon = nullptr;
    }
    if(EQ_icon != nullptr)
    {
        delete  EQ_icon;
        EQ_icon = nullptr;
    }
    if(VOLUME_icon != nullptr)
    {
        delete  VOLUME_icon;
        VOLUME_icon = nullptr;
    }
    if(back_icon != nullptr)
    {
        delete  back_icon;
        back_icon = nullptr;
    }
    if(EQ_bar != nullptr)
    {
        delete  EQ_bar;
        EQ_bar = nullptr;
    }
    if(EQ_VALUE != nullptr)
    {
        delete  EQ_VALUE;
        EQ_VALUE = nullptr;
    }
    if(VOLUME_VALUE != nullptr)
    {
        delete  VOLUME_VALUE;
        VOLUME_VALUE = nullptr;
    }
    if(VOLUME_slider != nullptr)
    {
        delete  VOLUME_slider;
        VOLUME_slider = nullptr;
    }
    if(mscreen!=nullptr)
    {
        delete mscreen;
        mscreen = nullptr;
    }
}

Volume::Volume(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(parent);
    mscreen->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    mscreen->set_main_bg_color(lv_color_white(),LV_OPA_100);
    m_parent = mscreen->myobj;

}

Volume::~Volume()
{
    deinitial();
    ui_image_free();
}

//User starts here
void Volume::initial(int eq_tmp,char *value)
{
    ui_image_decode();

    current_icon = new LvcppLabel(m_parent);
    current_icon->align(LV_ALIGN_CENTER,0,-200);
    current_icon->set_size(130,130);
    current_icon->set_txt("");
    current_icon->set_main_bg_img_src(Volume_PNG);

    VOLUME_icon = new LvcppLabel(m_parent);
    VOLUME_icon->align(LV_ALIGN_CENTER,-230,40);
    VOLUME_icon->set_size(30,40);
    VOLUME_icon->set_txt("");
    VOLUME_icon->set_main_bg_img_src(EQ_B_PNG);
        //

        //
    LV_LOG_USER("eq_tmp = %d",eq_tmp);
    VOLUME_slider = new LvcppSlider(m_parent);
    VOLUME_slider->align_to(VOLUME_icon->myobj,LV_ALIGN_OUT_RIGHT_MID,10,0);

    VOLUME_slider->set_size(320,20);
    VOLUME_slider->set_range(0,40);
    VOLUME_slider->set_value(eq_tmp/8,LV_ANIM_OFF);
    VOLUME_slider->set_style_bg_color(lv_color_white(), LV_OPA_0, LV_PART_KNOB);
    VOLUME_slider->set_style_bg_color(lv_color_black(), LV_OPA_50,LV_PART_INDICATOR);
    VOLUME_slider->set_style_bg_color(lv_color_white(), LV_OPA_0, LV_PART_MAIN);
    VOLUME_slider->set_style_border_style(0, lv_color_white(), LV_OPA_0, LV_PART_MAIN);
    VOLUME_slider->set_style_radius(0,LV_PART_MAIN);
    VOLUME_slider->set_style_radius(0,LV_PART_INDICATOR);
    VOLUME_slider->set_style_radius(0,LV_PART_KNOB);
    //VOLUME_slider->set_txt("");
    //VOLUME_slider->set_main_bg_img_src(BAR_PNG);

    //VOLUME_bar->set_main_bg_color(lv_color_black(),LV_OPA_80);
    //VOLUME_bar->set_main_border(2,lv_color_hex(0x222222),LV_OPA_40);

    VOLUME_VALUE = new LvcppLabel(m_parent);
    VOLUME_VALUE->set_size(50,70);
    VOLUME_VALUE->set_txt(value);
    VOLUME_VALUE->set_main_bg_color(lv_color_white(),LV_OPA_0);
    VOLUME_VALUE->align_to(VOLUME_slider->myobj,LV_ALIGN_OUT_RIGHT_MID,30,20);
    VOLUME_VALUE->set_main_bg_color(lv_color_white(),LV_OPA_0);
    //VOLUME_VALUE->set_main_bg_color(lv_color_black(),LV_OPA_100);

//
    VOLUME_B_bar = new LvcppLabel(m_parent);
    //VOLUME_B_bar->align(LV_ALIGN_CENTER,-230,30);
    VOLUME_B_bar->align(LV_ALIGN_CENTER,-230,-10);
    VOLUME_B_bar->set_size(30,40);
    VOLUME_B_bar->set_txt("");
    VOLUME_B_bar->set_main_bg_img_src(Volume_B_PNG);


    VOLUME_B_slider = new LvcppSlider(m_parent);
    VOLUME_B_slider->align_to(VOLUME_B_bar->myobj,LV_ALIGN_OUT_RIGHT_MID,10,0);
    VOLUME_B_slider->set_size(320,20);
    VOLUME_B_slider->set_range(0,40);
    VOLUME_B_slider->set_value(eq_tmp/8,LV_ANIM_OFF);
    VOLUME_B_slider->set_style_bg_color(lv_color_white(), LV_OPA_0, LV_PART_KNOB);
    VOLUME_B_slider->set_style_bg_color(lv_color_black(), LV_OPA_50,LV_PART_INDICATOR);
    VOLUME_B_slider->set_style_bg_color(lv_color_white(), LV_OPA_0, LV_PART_MAIN);
    VOLUME_B_slider->set_style_border_style(0, lv_color_white(), LV_OPA_0, LV_PART_MAIN);
    VOLUME_B_slider->set_style_radius(0,LV_PART_MAIN);
    VOLUME_B_slider->set_style_radius(0,LV_PART_INDICATOR);
    VOLUME_B_slider->set_style_radius(0,LV_PART_KNOB);

    VOLUME_B_slider->set_style_shadow_width(0, LV_PART_MAIN);

    //VOLUME_B_slider->set_txt("");
    //VOLUME_B_slider->set_main_bg_img_src(BAR_PNG);
    VOLUME_B_slider->add_event_cb(btn_event_hander,LV_EVENT_FOCUSED,this);

    VOLUME_B_VALUE = new LvcppLabel(m_parent);
    VOLUME_B_VALUE->set_size(50,70);
    VOLUME_B_VALUE->set_txt(value);
    VOLUME_B_VALUE->align_to(VOLUME_B_slider->myobj,LV_ALIGN_OUT_RIGHT_MID,30,20);
    VOLUME_B_VALUE->set_main_bg_color(lv_color_white(),LV_OPA_0);



    back_icon = new LvcppButton(m_parent);
    back_icon->align(LV_ALIGN_CENTER,0,180);
    back_icon->set_size(60,60);
    back_icon->add_txt("");
    back_icon->set_main_bg_img_src(BACK_PNG);
    back_icon->set_main_bg_color(lv_color_white(),LV_OPA_0);

    maintimer = startTimer(20,this);
}
void  Volume::btn_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    Volume* opt = ( Volume*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    //if(target==opt->->myobj)
    opt->VOLUME_B_slider->add_state(LV_STATE_EDITED|LV_STATE_FOCUSED);
}
void Volume::update_volume(int eq_tmp)
{
    char value[16]={0};
    sprintf(value,"%d",eq_tmp/8);
    VOLUME_slider->set_size(eq_tmp,20);
    VOLUME_VALUE->set_txt(value);
    VOLUME_VALUE->align_to(VOLUME_slider->myobj,LV_ALIGN_OUT_RIGHT_MID,30,20);
}

//loop run(must achieve)
void Volume::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);

    static int count = 0;//static variable once assign
}
