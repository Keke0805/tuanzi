#ifndef CALENDAR_H
#define CALENDAR_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/include/configCustom.h"
#include  "mainstart/customer_config.h"
#include  "functional"
#include  "../../appmsg/appmsg.h"

class Calendar : public LvcppTimerTask
{
public:
    Calendar(lv_obj_t* parent);
    ~Calendar(void);
    int init_parament(void);

protected:
	void*  HEAD_RETURN_PNG=NULL;              
	void*  HEAD_RETURN_SEL_PNG=NULL;
	
	void*  HEAD_ICON_CALENDART_PNG=NULL; 
	void*  LISTBG_PNG=NULL; 

	void*  CALENDAR_UNPREV_PNG=NULL;          
	void*  CALENDAR_PREV_PNG=NULL;            
	void*  CALENDAR_UNNEXT_PNG=NULL;          
	void*  CALENDAR_NEXT_PNG=NULL; 

    void ui_image_decode(void);
    void ui_image_free(void);
	
private:
    LvcppScreen* frame;
    lv_obj_t*  mainscreen;
    lvcpp_sys_datetime_t user_time;
    LvcppButton* buttonReturn =NULL;
    LvcppButton* calendarIcon =NULL;
    LvcppButton* monthPrev =NULL;
    LvcppButton* monthNext =NULL;
    LvcppButton* strToday =NULL;
    LvcppLabel* strDate =NULL;
    LvcppLabel* strTime =NULL;
    LvcppLabel* strApm =NULL;
    LvcppLabel* strWeek =NULL;
    LvcppLabel* strDateTime =NULL;
    LvcppLabel* strSun =NULL;
    LvcppLabel* strMon =NULL;
    LvcppLabel* strTue =NULL;
    LvcppLabel* strWeb =NULL;
    LvcppLabel* strThu =NULL;
    LvcppLabel* strFri =NULL;
    LvcppLabel* strSat =NULL;
    LvcppCalendar* calScene =NULL;
    char *weekStr =NULL;
    char headDate[12]={0};
    char todayDate[12]={0};
    char todayTime[12]={0};
    int timeType =12;
    int dayInde =0;
    int monthInde =0;
    int yearInde =0;
    bool StartTimerShow =false;
    bool apmType =false;
    void TimerCB(lv_timer_t * tmr);
    LvcppButton* LvcppButtonHead(lv_obj_t* paren,bool show_cb,lv_ui_inof_t *uiInfo);
    LvcppLabel* LvcppLabelViewChild(lv_obj_t* paren,lv_text_align_t align,lv_str_inof_t *strInfo);
    char* calendar_get_week(int y,int m,int d);
    void get_dateTime(void);
    static void head_event_handler(lv_event_t *event);
    void calendar_head_creat(void);
    void calendar_head_dele(void);
    void Calendar_scene_creat(void);
    static void calList_event_handler(lv_event_t *event);
    void calList_list_dele(void);
};

#endif // CALENDAR_H
