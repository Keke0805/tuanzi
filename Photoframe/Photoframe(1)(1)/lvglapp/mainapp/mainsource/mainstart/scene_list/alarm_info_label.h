#ifndef ALARM_INFO_LABEL_H
#define ALARM_INFO_LABEL_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "../include/configCustom.h"
#include  "../include/str_config.h"
#include  "../include/ui_config.h"
#include  "mainstart/customer_config.h"
#ifdef _UCHIP_T113
#include  "common/common.h"
#endif

class Alarminfo_Label
{
public:
    Alarminfo_Label(lv_obj_t* parent = nullptr);
    ~Alarminfo_Label();
	
    LvcppScreen* alarm_frame_label=nullptr;
    lv_obj_t*  alarmscreen=nullptr;
    LvcppButton* alarm_info=nullptr;
    LvcppButton* alarm_info_1=nullptr;
    LvcppButton* alarm_info_line_1=nullptr;

    LvcppTextArea* textarea=nullptr;
    LvcppKeyboard* kb=nullptr;

    LvcppButton* cancel=nullptr;
    LvcppButton* confirm=nullptr;

private:
    void Alarminfo_Label_delete(void);
    void show_keyboard(void);
    lv_obj_t* alarm_info_frame=nullptr;
};

#endif // ALARM_INFO_BELL_H



