#ifndef ALARM_INFO_H
#define ALARM_INFO_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "../include/configCustom.h"
#include  "../include/str_config.h"
#include  "../include/ui_config.h"
#include  "mainstart/customer_config.h"

#ifdef _UCHIP_T113
#include  "common/common.h"
#else
    #include  "driver/va_wifi.h"
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
}click_statue_t;





class Alarminfo
{
public:
    Alarminfo(int dayType,lv_obj_t* parent = nullptr);
    ~Alarminfo();
	
    char switch_day[128]={0};
    int get_info(void);
    LvcppScreen* alarm_frame=nullptr;
    lv_obj_t*  alarmscreen=nullptr;
    LvcppButton* alarm_info=nullptr;
    LvcppButton* alarm_info_sun=nullptr;
    LvcppButton* alarm_info_mon=nullptr;
    LvcppButton* alarm_info_tue=nullptr;
    LvcppButton* alarm_info_wed=nullptr;
    LvcppButton* alarm_info_thur=nullptr;
    LvcppButton* alarm_info_fri=nullptr;
    LvcppButton* alarm_info_sat=nullptr;

    LvcppButton* alarm_info_sun_pic=nullptr;
    LvcppButton* alarm_info_mon_pic=nullptr;
    LvcppButton* alarm_info_tue_pic=nullptr;
    LvcppButton* alarm_info_wed_pic=nullptr;
    LvcppButton* alarm_info_thur_pic=nullptr;
    LvcppButton* alarm_info_fri_pic=nullptr;
    LvcppButton* alarm_info_sat_pic=nullptr;

    LvcppButton* cancel=nullptr;
    LvcppButton* confirm=nullptr;

    LvcppButton* alarm_info_line_1=nullptr;
    LvcppButton* alarm_info_line_2=nullptr;
    LvcppButton* alarm_info_line_3=nullptr;
    LvcppButton* alarm_info_line_4=nullptr;
    LvcppButton* alarm_info_line_5=nullptr;
    LvcppButton* alarm_info_line_6=nullptr;
    LvcppButton* alarm_info_line_7=nullptr;

    click_statue_t click_statue;

 protected:

	void*  LIST_CIRCLE_PNG=NULL;
	void*  LIST_ICON_CHE_PNG=NULL;  
	
    void ui_image_decode(void);
    void ui_image_free(void);


private:
	void set_info(int dayType);
    static void clicked_event_handler(lv_event_t *event);
    lv_obj_t* alarm_info_frame=nullptr;
};

#endif // ALARM_INFO_H



