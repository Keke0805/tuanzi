#include "setbrighscreen.h"
#include "stbimage/va_image.h"
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

static int backlight_value  = 7;

setbrighscreen::setbrighscreen(lv_obj_t *parent,void* bg_png)
{
    bri_screen = new LvcppScreen(lv_scr_act());
    bri_screen->set_size(1024,600);
    bri_parent = bri_screen->get_screen();
    bri_screen->set_bg_color(lv_color_white(),LV_OPA_100);
    bri_screen->showlogo((char*)bg_png, SCREEN_HOR_SIZE, SCREEN_VER_SIZE,0);
    initial();
}

void setbrighscreen::initial()
{
    if(set_bri_slider ==nullptr)
    {
        set_bri_slider = new LvcppSlider(bri_parent);
        set_bri_slider->set_range(0,9);
        set_bri_slider->set_value(backlight_value,LV_ANIM_OFF);
        set_bri_slider->set_mode(LV_BAR_MODE_NORMAL);
        set_bri_slider->set_pos(380,250);
        set_bri_slider->set_style_bg_color(lv_color_hex(0xffffff),LV_OPA_100,LV_PART_INDICATOR);
        set_bri_slider->set_style_bg_color(lv_color_white(),LV_OPA_60,LV_PART_KNOB);
        set_bri_slider->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_60);
        set_bri_slider->add_event_cb(btn_event_hander,LV_EVENT_VALUE_CHANGED,this);
        set_bri_slider->add_event_cb(btn_event_hander,LV_EVENT_RELEASED,this);
    }
    if(max_value == nullptr)
    {
        max_value = new LvcppLabel(bri_parent);
        max_value->set_txt("背光调节");
        max_value->set_pos(470,200);
        max_value->txt_font_size(25,0);
        max_value->set_size(150,100);
        max_value->txt_color(lv_color_hex(0xffffff),0);
    }
    if(mix_value == nullptr)
    {
        char value[32];
        snprintf(value,sizeof(value),"%d",backlight_value+1);
        mix_value = new LvcppLabel(bri_parent);
        mix_value->set_txt(value);
        mix_value->set_pos(650,230);
        mix_value->txt_font_size(40,0);
        mix_value->set_size(100,100);
        mix_value->txt_color(lv_color_hex(0xffffff),0);
    }
    if(go_back == nullptr)
    {
        go_back = new LvcppButton(bri_parent);
        go_back->add_txt("返回");
        go_back->set_size(159,46);
        go_back->align(LV_ALIGN_BOTTOM_MID,0,-30);
        go_back->txt_font_size(20,0);
        //go_back->set_main_bg_color(lv_color_hex(0x000000),LV_OPA_0);
        go_back->txt_align(LV_ALIGN_CENTER,0,0);
        go_back->set_main_bg_img_src(GO_BACK);
        go_back->txt_color(lv_color_hex(0xffffff));
        go_back->add_event_cb(btn_event_hander,LV_EVENT_CLICKED,this);
    }
}

setbrighscreen::~setbrighscreen()
{
    if(set_bri_slider !=nullptr)
    {
        delete  set_bri_slider;
        set_bri_slider = nullptr;
    }
    if(max_value !=nullptr)
    {
        delete  max_value;
        max_value = nullptr;
    }
    if(mix_value !=nullptr)
    {
        delete  mix_value;
        mix_value = nullptr;
    }
    if(go_back !=nullptr)
    {
        delete  go_back;
        go_back = nullptr;
    }
    if(bri_screen !=nullptr)
    {
        delete  bri_screen;
        bri_screen = nullptr;
    }
}

void setbrighscreen::btn_event_hander(lv_event_t *event)
{
    //static member don't access other members of the class so must to use opt->
    setbrighscreen* opt = (setbrighscreen*)event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target == opt->go_back->myobj)
    {
        opt->bri_callback();
    }
    else if(target == opt->set_bri_slider->myobj)
    {
        if(lv_event_get_code(event)==LV_EVENT_RELEASED)
        {
            char value[32];
            char cmd[128];
            backlight_value = opt->set_bri_slider->get_value();
            LV_LOG_USER("backlightpro = %d",backlight_value+1);
            snprintf(value,sizeof(value),"%d",backlight_value+1);
            opt->mix_value->set_txt(value);
            if(backlight_value>=0 && backlight_value<=9)
            {
                memset(cmd,0,sizeof(cmd));
                sprintf(cmd,"echo %d > /sys/class/pwm/pwmchip0/pwm0/duty_cycle",(backlight_value+1)*10);
                system(cmd);
                usleep(10000);
                memset(cmd,0,sizeof(cmd));
                sprintf(cmd,"echo %d > /sys/class/pwm/pwmchip0/pwm1/duty_cycle",(backlight_value+1)*10);
                system(cmd);
                system("sync");
            }
            if(backlight_value < 0 || backlight_value>9)
            {
                return;
            }
            else
            {
                #if 0//(QTSIM_PLATFORM==0)
                msg_apps_t msg;
                urdev_param_t urcmd;
                urcmd.cmd_or_file = 2;
                urcmd.cmd_index = backlight_value;
                urcmd.cur_cmd = 9;
                memset(&msg, 0, sizeof(msg_apps_t));
                msg.type = MSG_SEND_CMD_TO_R2;
                memcpy(msg.content, &urcmd, sizeof(urdev_param_t));
                SSTAR_SendAsyncMsg(APP_NAME_URDEV, &msg);
                #endif
            }
        }
    }
}

void setbrighscreen::sendcb(void (*callback)(void))
{
    bri_callback = callback;
}
