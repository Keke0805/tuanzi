#ifndef ALARM_INFO_TIME_H
#define ALARM_INFO_TIME_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "../include/configCustom.h"
#include  "../include/str_config.h"
#include  "../include/ui_config.h"
#include  "mainstart/customer_config.h"
#ifdef _UCHIP_T113
#include  "common/common.h"
#endif

class Alarminfo_Time
{
public:
    Alarminfo_Time(int Hours,int Minute,int Hours24,lv_obj_t* parent = nullptr);
    ~Alarminfo_Time();
	
    char apm[24]={0};
    char hour[24]={0};
    char minute[24]={0};
    int get_info(void);
    LvcppScreen* alarm_frame_label=nullptr;
    lv_obj_t*  alarmscreen=nullptr;
    LvcppButton* alarm_info=nullptr;

    LvcppButton* cancel=nullptr;
    LvcppButton* confirm=nullptr;

    LvcppRoller* roller1 =nullptr;
    LvcppRoller* roller2 =nullptr;
    LvcppRoller* roller3 =nullptr;

private:
    void Alarminfo_Time_delete(void);
    lv_obj_t* alarm_info_frame=nullptr;
	bool Type24Time =false;
};

#endif // ALARM_INFO_TIME_H



