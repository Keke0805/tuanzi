#include "light.h"
#include "common/common.h"
#include "math.h"

int  brightness=DEFAULT_BRIGHTNESS;
void Light::ui_image_decode(void)
{
    Light_PNG=(void*)parse_image_from_file((char*)EQ_LIGHT_PNG_PATH);
   CLASSIC_JPG=(void*)parse_image_from_file((char*)MAIN_MENU_CLASSIC_JPG_PATH);

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
    ui_image_decode();
    mscreen = new LvcppScreen(parent);
    mscreen->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    mscreen->set_main_bg_color(lv_color_white(),LV_OPA_0);
    //mscreen->showlogo((const char *)CLASSIC_JPG,SCREEN_HOR_SIZE,SCREEN_VER_SIZE,0);
    mscreen->showlogo(static_cast<const char*>(CLASSIC_JPG),SCREEN_HOR_SIZE,SCREEN_VER_SIZE,0);
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
    light_slider = new LvcppSlider(m_parent);
    light_slider->align_to(light_icon->myobj,LV_ALIGN_OUT_RIGHT_MID,10,0);

    light_slider->set_size(320,20);
    light_slider->set_range(0,70);
    light_slider->set_value(light_tmp/8,LV_ANIM_OFF);
    light_slider->set_style_bg_color(lv_color_white(), LV_OPA_0, LV_PART_KNOB);
    light_slider->set_style_bg_color(lv_color_black(), LV_OPA_50,LV_PART_INDICATOR);
    light_slider->set_style_bg_color(lv_color_white(), LV_OPA_0, LV_PART_MAIN);
    light_slider->set_style_border_style(0, lv_color_white(), LV_OPA_0, LV_PART_MAIN);
    light_slider->set_style_radius(0,LV_PART_MAIN);
    light_slider->set_style_radius(0,LV_PART_INDICATOR);
    light_slider->set_style_radius(0,LV_PART_KNOB);
    light_slider->add_event_cb(btn_event_hander,LV_EVENT_VALUE_CHANGED,this);

    //VOLUME_VALUE->set_main_bg_color(lv_color_black(),LV_OPA_100);
    light_VALUE = new LvcppLabel(m_parent);
    light_VALUE->set_size(50,70);
    light_VALUE->set_txt(value);
    light_VALUE->set_main_bg_color(lv_color_white(),LV_OPA_0);
    light_VALUE->align_to(light_slider->myobj,LV_ALIGN_OUT_RIGHT_MID,30,20);
    light_VALUE->set_main_bg_color(lv_color_white(),LV_OPA_0);

    maintimer = startTimer(20,this);
}

void Light::deinitial(void)
{
    if(light_icon != nullptr)
    {
        delete light_icon ;
        light_icon = nullptr;
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
    light_slider->set_size(light_tmp,20);

}
void  Light::btn_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    Light* opt = ( Light*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    if(target == opt->light_slider->myobj)
    {
        if(event->code == LV_EVENT_VALUE_CHANGED)
        {
            LV_LOG_USER("LV_EVENT_VALUE_CHANGED");
            char valuetxt[32];
            int value = opt->light_slider->get_value();
            sprintf(valuetxt,"%d",value);
            opt->light_VALUE->set_txt(valuetxt);
        }
    }
}
/*
void set_brightness(int value) {
    brightness = value;

    lv_scr_load_anim(,LV_SCR_LOAD_ANIM_FADE_IN,1000,100,true); // 屏幕渐变效果
}
*/
//loop run(must achieve)
void Light::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    static int count = 0;//static variable once assign
}
