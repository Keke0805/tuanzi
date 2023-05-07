#ifndef CLOCK_H
#define CLOCK_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/include/configCustom.h"
#include  "mainstart/customer_config.h"
#include  "mainstart/scene_list/clock_list.h"
#include  "mainstart/scene_list/clock_secne.h"
#include  "mainstart/scene_list/clock_timelist.h"
#include  "functional"
#include  "../../appmsg/appmsg.h"

typedef struct
{
    int count;
    clockList* list_item[CLOCK_LIST_MAX];
}clocklist_item_info;

typedef struct
{
    int count;
    clockSecne* list_item[CLOCK_LIST_MAX-1];
}clockscene_item_info;

class ClockTime : public LvcppTimerTask
{
public:
    ClockTime(lv_obj_t* parent);
    ~ClockTime(void);
    int init_parament(void);
protected:
	void*  HEAD_RETURN_PNG=NULL;              
	void*  HEAD_RETURN_SEL_PNG=NULL;

	void*  HEAD_ICON_ClOCK_PNG=NULL; 
	
	void*  CLOCK_CLOCK0_PNG=NULL;             
	void*  CLOCK_CLOCK1_PNG=NULL;             
	void*  CLOCK_CLOCK2_PNG=NULL;             
	void*  CLOCK_CLOCK3_PNG=NULL;             
	void*  CLOCK_CLOCK4_PNG=NULL;             
	void*  CLOCK_CLOCK5_PNG=NULL;             
	void*  CLOCK_CLOCK6_PNG=NULL;             
	void*  CLOCK_CLOCK7_PNG=NULL;             
	void*  CLOCK_CLOCK8_PNG=NULL;             

	void*  CLOCK_SCENE0_PNG=NULL;             
	void*  CLOCK_SCENE1_PNG=NULL;             
	void*  CLOCK_SCENE2_PNG=NULL;             
	void*  CLOCK_SCENE3_PNG=NULL;             
	void*  CLOCK_SCENE4_PNG=NULL;             
	void*  CLOCK_SCENE5_PNG=NULL;             
	void*  CLOCK_SCENE6_PNG=NULL;             
	void*  CLOCK_SCENE7_PNG=NULL;             
	void*  CLOCK_SCENE8_PNG=NULL;             

	void*  CLOCK_HOURS1_PNG=NULL;             
	void*  CLOCK_HOURS2_PNG=NULL;             
	void*  CLOCK_HOURS3_PNG=NULL;             
	void*  CLOCK_HOURS4_PNG=NULL;             
	void*  CLOCK_HOURS5_PNG=NULL;             
	void*  CLOCK_HOURS6_PNG=NULL;             
	void*  CLOCK_HOURS7_PNG=NULL;             
	void*  CLOCK_HOURS8_PNG=NULL;             

	void*  CLOCK_MINUTE1_PNG=NULL;            
	void*  CLOCK_MINUTE2_PNG=NULL;            
	void*  CLOCK_MINUTE3_PNG=NULL;            
	void*  CLOCK_MINUTE4_PNG=NULL;            
	void*  CLOCK_MINUTE5_PNG=NULL;            
	void*  CLOCK_MINUTE6_PNG=NULL;            
	void*  CLOCK_MINUTE7_PNG=NULL;            
	void*  CLOCK_MINUTE8_PNG=NULL;            

	void*  CLOCK_SECOND1_PNG=NULL;            
	void*  CLOCK_SECOND2_PNG=NULL;            
	void*  CLOCK_SECOND3_PNG=NULL;            
	void*  CLOCK_SECOND4_PNG=NULL;            
	void*  CLOCK_SECOND5_PNG=NULL;            
	void*  CLOCK_SECOND6_PNG=NULL;            
	void*  CLOCK_SECOND7_PNG=NULL;            
	void*  CLOCK_SECOND8_PNG=NULL;            

	void*  CLOCK_DOT1_PNG=NULL;               
	void*  CLOCK_DOT2_PNG=NULL;               
	void*  CLOCK_DOT3_PNG=NULL;               
	void*  CLOCK_DOT4_PNG=NULL;               
	void*  CLOCK_DOT5_PNG=NULL;               
	void*  CLOCK_DOT6_PNG=NULL;               
	void*  CLOCK_DOT7_PNG=NULL;               
	void*  CLOCK_DOT8_PNG=NULL;               

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

	void ui_image_decode_scene(int curScene);
	void ui_image_free_scene(int curScene);
	
	void ui_image_decode_list(void);
	void ui_image_free_list(void);
private:
    LvcppScreen* frame;
    lv_obj_t*  mainscreen;
	lv_timer_t*clockTimer =NULL;
    lvcpp_sys_datetime_t user_time;
    LvcppButton* buttonReturn =NULL;
    LvcppScreen* headIcon =NULL;
    LvcppButton* clockIcon =NULL;
    LvcppList* ClockList =NULL;
    LvcppList* ClockScene =NULL;
    clocklist_item_info clockList_id;
    clockscene_item_info clockScene_id;
    clockTimeList* timeList_item =NULL;
    int timecntback = 0;
    bool StartTimerShow =false;
    bool head_show =true;
    bool clockList_show =false;
	bool clockList_down =false;
	void set_image_scene(int curScene);
    static void main_event_handler(lv_event_t *event);
    void TimerCB(lv_timer_t * tmr);
    void clocktime_head_creat(void);
    void clocktime_head_dele(void);
    static void head_event_handler(lv_event_t *event);
    void clocktime_clockList_creat(void);
    void clocktime_clockList_delete(void);
    void clocktime_clockScene_creat(void);
    void clocktime_clockScene_delete(void);
	void updata_clockScene_index(int index);
    static void scene_event_handler(lv_event_t *event);
	void scene_del_clock(void);
	void scene_set_clock(void);
};

#endif // CLOCK_H
