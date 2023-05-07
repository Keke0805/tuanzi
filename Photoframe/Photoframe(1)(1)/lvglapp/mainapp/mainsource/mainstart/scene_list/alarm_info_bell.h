#ifndef ALARM_INFO_BELL_H
#define ALARM_INFO_BELL_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "../include/configCustom.h"
#include  "../include/str_config.h"
#include  "../include/ui_config.h"
#include  "mainstart/customer_config.h"
#ifdef _UCHIP_T113
#include  "common/common.h"
#endif


typedef struct
{
    bool click_sun;
    bool click_mon;
    bool click_tue;
    bool click_wed;
    bool click_thui;
    bool click_fri;
    bool click_sat;
}click_bell_statue_t;


class Alarminfo_Bell
{
public:

    char switch_bell[128]={0};
    int choose=0;
    Alarminfo_Bell(int Song,lv_obj_t* parent = nullptr);
    ~Alarminfo_Bell();
	
    LvcppScreen* alarm_frame_bell=nullptr;
    lv_obj_t*  alarmscreen=nullptr;
    LvcppButton* alarm_info=nullptr;
    LvcppButton* alarm_info_1=nullptr;
    LvcppButton* alarm_info_2=nullptr;
    LvcppButton* alarm_info_3=nullptr;
    LvcppButton* alarm_info_4=nullptr;
    LvcppButton* alarm_info_5=nullptr;


    LvcppButton* alarm_info_pic1=nullptr;
    LvcppButton* alarm_info_pic2=nullptr;
    LvcppButton* alarm_info_pic3=nullptr;
    LvcppButton* alarm_info_pic4=nullptr;

    LvcppButton* alarm_info_line_1=nullptr;
    LvcppButton* alarm_info_line_2=nullptr;
    LvcppButton* alarm_info_line_3=nullptr;
    LvcppButton* alarm_info_line_4=nullptr;
    LvcppButton* alarm_info_line_5=nullptr;
    LvcppButton* alarm_info_line_6=nullptr;
    LvcppButton* alarm_info_line_7=nullptr;

    click_bell_statue_t click_bell_statue;
    LvcppButton* cancel=nullptr;
    LvcppButton* confirm=nullptr;
    int get_info(void);

protected:
	
	void*  LIST_CIRCLE_PNG=NULL;
	void*  LIST_ICON_CHE_PNG=NULL;
    void ui_image_decode(void);
    void ui_image_free(void);

private:
    static void clicked_event_handler(lv_event_t *event);
    lv_obj_t* alarm_info_frame=nullptr;
};

#endif // ALARM_INFO_BELL_H



