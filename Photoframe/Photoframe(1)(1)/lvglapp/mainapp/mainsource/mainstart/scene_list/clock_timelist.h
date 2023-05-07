#ifndef CLOCK_TIMELIST_H
#define CLOCK_TIMELIST_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "../include/configCustom.h"
#include  "lvgl/src/extra/lv_extra.h"
#include  "mainstart/include/ui_config.h"
#include  "mainstart/include/str_config.h"

class clockTimeList
{
public:
    clockTimeList(lv_obj_t* parent,lvcpp_sys_datetime_t *dateTime);
    ~clockTimeList(void);
    void update_time(lvcpp_sys_datetime_t *dateTime);
    LvcppButton *plateImage =NULL;

protected:
	void*  CLOCK_SCENE0_PNG=NULL;             
	void*  CLOCK_SCENE1_PNG=NULL;             
	void*  CLOCK_SCENE2_PNG=NULL;             
	void*  CLOCK_SCENE3_PNG=NULL;             
	void*  CLOCK_SCENE4_PNG=NULL;             
	void*  CLOCK_SCENE5_PNG=NULL;             
	void*  CLOCK_SCENE6_PNG=NULL;             
	void*  CLOCK_SCENE7_PNG=NULL;             
	void*  CLOCK_SCENE8_PNG=NULL;
	void*  CLOCK_NUM0_PNG=NULL;               
	void*  CLOCK_NUM1_PNG=NULL;               
	void*  CLOCK_NUM2_PNG=NULL;               
	void*  CLOCK_NUM3_PNG=NULL;               
	void*  CLOCK_NUM4_PNG=NULL;               
	void*  CLOCK_NUM5_PNG=NULL;               
	void*  CLOCK_NUM6_PNG=NULL;               
	void*  CLOCK_NUM7_PNG=NULL;               
	void*  CLOCK_NUM8_PNG=NULL;               
	void*  CLOCK_NUM9_PNG=NULL; 
    void ui_image_decode(void);
    void ui_image_free(void);
private:
    lv_obj_t* mainframe=NULL;
    LvcppImage *hours0Image =NULL;
    LvcppImage *hours1Image =NULL;
    LvcppImage *minute0Image =NULL;
    LvcppImage *minute1Image =NULL;
    LvcppImage *second0Image =NULL;
    LvcppImage *second1Image =NULL;
    LvcppLabel* strWeek =NULL;
    LvcppLabel* strDate =NULL;
    char month[128]={0};
    lvcpp_sys_time_t dateTimesave;
};

#endif // CLOCK_TIMELIST_H
