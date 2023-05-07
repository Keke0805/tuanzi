#include "light.h"
#include "common/common.h"
#include "math.h"

void Light::ui_image_decode(void)
{
    Light_PNG=(void*)parse_image_from_file((char*)EQ_LIGHT_PNG_PATH);
}

void Light::ui_image_free(void)
{
    if(Light_PNG !=NULL)
    {
        free_image(Light_PNG);
        Light_PNG =NULL;
    }
}

Light::Light(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(parent);
    mscreen->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    mscreen->set_main_bg_color(lv_color_white(),LV_OPA_0);
    m_parent = mscreen->myobj;
}

Light::~Light()
{
    deinitial();
    ui_image_free();
}

//User starts here
void Light::initial(int light_tmp,char *value)
{
    ui_image_decode();

    light_icon = new LvcppLabel(m_parent);
    light_icon->align(LV_ALIGN_CENTER,-230,40);
    light_icon->set_size(30,40);
    light_icon->set_txt("");
    light_icon->set_main_bg_img_src(Light_PNG);

    LV_LOG_USER("light_tmp = %d",light_tmp);
    light_bar = new LvcppLabel(m_parent);
    light_bar->align_to(light_icon->myobj,LV_ALIGN_OUT_RIGHT_MID,20,3);
    light_bar->set_size(light_tmp,20);
    light_bar->set_txt("");
    light_bar->set_main_bg_color(lv_color_white(),LV_OPA_80);
    light_bar->set_main_border(2,lv_color_hex(0x222222),LV_OPA_40);

    light_value = new LvcppLabel(m_parent);
    light_value->set_size(100,50);
    light_value->set_txt(value);
    light_value->txt_color(lv_color_white(),0);
    light_value->align_to(light_bar->myobj,LV_ALIGN_OUT_RIGHT_MID,20,10);
    //VOLUME_VALUE->set_main_bg_color(lv_color_black(),LV_OPA_100);

    maintimer = startTimer(20,this);
}

void Light::deinitial(void)
{
    if(light_icon != nullptr)
    {
        delete light_icon ;
        light_icon = nullptr;
    }
    if(light_bar != nullptr)
    {
        delete light_bar ;
        light_bar = nullptr;
    }
    if(light_value != nullptr)
    {
        delete light_value ;
        light_value = nullptr;
    }
    if(mscreen != nullptr)
    {
        delete mscreen ;
        mscreen = nullptr;
    }
}

void Light::update_light(int light_tmp)
{
    char value[16]={0};
    sprintf(value,"%d",light_tmp/8);
    light_bar->set_size(light_tmp,20);
    light_value->set_txt(value);
    light_value->align_to(light_bar->myobj,LV_ALIGN_OUT_RIGHT_MID,20,10);
}

//loop run(must achieve)
void Light::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    static int count = 0;//static variable once assign
}
