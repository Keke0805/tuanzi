#ifndef ALARM_H
#define ALARM_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/include/configCustom.h"
#include  "mainstart/customer_config.h"
#include  "../scene_list/alarm_list.h"
#include  "../scene_list/alarm_info.h"
#include  "../scene_list/alarm_info_bell.h"
#include  "../scene_list/alarm_info_label.h"
#include  "../scene_list/alarm_info_time.h"
#include  "functional"
#include  "../../appmsg/appmsg.h"
#include  "network/checktimemsg.h"
#define  ALARM_LIST_MAX_ITEM    100

typedef struct alarm_info_s
{
    int index;
	alarm_info AlarmInfo;
    struct alarm_info_s *next_list;
}alarm_info_t;

typedef struct
{
    int count;
    Alarmlist* item[ALARM_LIST_MAX_ITEM];
}alarm_list_item_info;

typedef struct
{
    char day[128];
    char bell[64];
    char label[64];
    char time[64];
}okIcon_alarm_info;

class alarmScene : public LvcppTimerTask
{
public:
    alarmScene(lv_obj_t* parent,checkTimeMsg* alarmList);
    ~alarmScene(void);
	static void funcallback(msg_apps_t *msg);
    int init_parament(void);

protected:
	void*  HEAD_RETURN_PNG=NULL;              
	void*  HEAD_RETURN_SEL_PNG=NULL;

	void*  HEAD_ICON_ALARM_PNG=NULL;
	void*  LISTBG_PNG=NULL;  

	void*  ALARM_SCENE_PNG=NULL;              
	void*  ALARM_HOURS_PNG=NULL;              
	void*  ALARM_MINUTE_PNG=NULL;             
	void*  ALARM_SECOND_PNG=NULL;             
	void*  ALARM_DOT_PNG=NULL;
	
    void ui_image_decode(void);
    void ui_image_free(void);
private:
    LvcppScreen* frame;
    LvcppScreen* alarmListFrame;
	checkTimeMsg *CheckAlarmList =NULL;
	lv_timer_t* alarmSceneTimer =NULL;
    lv_obj_t*  mainscreen;
    LvcppList* mainList =NULL;
    LvcppList* confirm_list =NULL;
    LvcppButton* repeat =NULL;
    LvcppButton* bell =NULL;
    LvcppButton* label =NULL;
    LvcppButton* settime =NULL;
    LvcppButton* repeat_txt =NULL;
    LvcppButton* bell_txt =NULL;
    LvcppButton* label_txt =NULL;
    LvcppButton* settime_txt =NULL;
    LvcppButton* line1 =NULL;
    LvcppButton* line2 =NULL;
    LvcppButton* line3 =NULL;
    LvcppButton* line4 =NULL;
    LvcppButton* buttonReturn =NULL;
    LvcppButton* alarmIcon =NULL;
    LvcppButton* addIcon =NULL;
    LvcppButton* editIcon =NULL;
    LvcppButton* cancelIcon =NULL;
    LvcppButton* okIcon =NULL;
    LvcppImage *plateImage =NULL;
    LvcppImage *hoursImage =NULL;
    LvcppImage *minuteImage =NULL;
    LvcppImage *secondImage =NULL;
    LvcppImage *dotImage =NULL;
	LvcppLabel* repeatLabel =NULL;
	LvcppLabel* repeatName =NULL;
	LvcppLabel* repeatData =NULL;
	LvcppLabel* repeatLine =NULL;
	LvcppLabel* repeatDot =NULL;
	LvcppLabel* ringLabel =NULL;
	LvcppLabel* ringName =NULL;
	LvcppLabel* ringData =NULL;
	LvcppLabel* ringLine =NULL;
	LvcppLabel* ringDot =NULL;
	LvcppLabel* labelLabel =NULL;
	LvcppLabel* labelName =NULL;
	LvcppLabel* labelData =NULL;
	LvcppLabel* labelLine =NULL;
	LvcppLabel* labelDot =NULL;
	LvcppLabel* timeLabel =NULL;
	LvcppLabel* timeName =NULL;
	LvcppLabel* timeData =NULL;
	LvcppLabel* timeLine =NULL;
	LvcppLabel* timeDot =NULL;
    lvcpp_sys_datetime_t user_time;
    
    alarm_list_item_info alarm_list;
	alarm_info_t *AlarmInfo =NULL;
    okIcon_alarm_info ok_alarm_info;

    Alarminfo* alarmInfo = NULL;
    Alarminfo_Bell* alarm_info_bell = NULL;
    Alarminfo_Label* alarm_info_label = NULL;
    Alarminfo_Time* alarm_info_time = NULL;
	alarm_info infoAlarmCur;

	bool StartTimerShow =false;
	bool editShow =false;
	int timeType =12;
	int alarnNum =0;
	int alarmIndex =0;
	int alarmListIndex=0;
	char reData[64]={0};
	char tiData[24]={0};
	void selalarm_add_node(alarm_info_t *node);
	void alarm_sort(void);
	int get_alarm_total(void);
	int get_alarm_info(int index,alarm_info *infoAlarm);
	void set_alarm_info(int index,alarm_info *infoAlarm);
	void set_alarm_CurStatus(int index,int status);
	int set_alarm_off_CurStatus(int hours,int minutes,int status);
	int get_alarm_CurStatus(int index);
	bool check_alarm_Cur(alarm_info *infoAlarm);
	void del_alarm_CurStatus(int index);
	void selalarm_destory(void);
	void alarm_add_info(alarm_info *alarnInfo);
    void TimerCB(lv_timer_t * tmr);
	void alarm_cjson_alarmInfo(char*alarmBuff);
	void get_all_alarmList(void);
    void delete_Alarminfo(void);
    void delete_Alarminfo_Bell(void);
    void delete_Alarminfo_Label(void);
    void delete_Alarminfo_Time(void);

    void alarmScene_head_creat(void);
    void alarmScene_head_dele(void);
    static void head_event_handler(lv_event_t *event);
    static void alarm_list_event_handler(lv_event_t *event);
    static void alarm_confirm_event_handler(lv_event_t *event);
 
    void alarm_day_info_creat(void);
    void alarm_bell_info_creat(void);
    void alarm_label_info_creat(void);
    void alarm_time_info_creat(void);
    void alarmScene_sence_creat(void);
    void alarmScene_sence_draw(void);
    void alarmScene_sence_delete(void);

    void alarm_list_creat(void);
	void alarm_list_show(bool status);
    void alarm_list_delete(void);


    void add_alarm_list_item(void);
	void get_dayType_str(int dayType,char *dayTypeStr);
	void alarm_setlist_creat(void);
	void alarm_setlist_del(void);

};

#endif // ALARM_H
