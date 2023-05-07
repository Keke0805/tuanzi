#ifndef ALARM_LIST_H
#define ALARM_LIST_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "../include/ui_config.h"

class Alarmlist
{
public:
    Alarmlist(lv_obj_t* parent = NULL);
    ~Alarmlist();

    LvcppLabel* IconBg=NULL;
    LvcppLabel* TimeStr=NULL;
    LvcppLabel* IconName=NULL;
    LvcppLabel* IconType=NULL;
    LvcppLabel* IconClose=NULL;
    LvcppLabel* StatusClose=NULL;
    LvcppButton* IconSet=NULL;
    LvcppButton* IconDel=NULL;
    LvcppLabel* IconLine=NULL;

protected:
	void*  ALARM_SET_PNG=NULL;                
	void*  ALARM_DEL_PNG=NULL;   
    void ui_image_decode(void);
    void ui_image_free(void);
private:
    lv_obj_t* mainframe=nullptr;
};

#endif // SETTING_LIST_H
