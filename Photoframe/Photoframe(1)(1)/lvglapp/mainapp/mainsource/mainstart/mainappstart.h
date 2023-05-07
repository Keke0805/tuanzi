#ifndef MAINAPPSTART_H
#define MAINAPPSTART_H

#include  "lvgl/lvgl.h"
#include  "include/configCustom.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "customer_config.h"
#include  "photo/photomain.h"
#include  "video/videomain.h"
#include  "music/music.h"
#include  "calendar/calendar.h"
#include  "weather/weather.h"
#include  "clock/clock.h"
#include  "alarm/alarm.h"
#include  "setting/setting.h"
#include  "functional"
#include  "network/http.h"
#include  "appmsg/appmsg.h"
#include  "network/checktimemsg.h"
#include  "scene_list/alarm_bounced.h"
enum {
    MAIN_DESKTOP = 0,
    MAIN_DESKTOP_PHOTO,
    MAIN_DESKTOP_WEATHER,
    MAIN_DESKTOP_CALENDAR,
    MAIN_DESKTOP_ALARM,
    MAIN_DESKTOP_CLOCK,
    MAIN_DESKTOP_VIDEO,
    MAIN_DESKTOP_MUSIC,
    MAIN_DESKTOP_SETTING,
    MAIN_DESKTOP_MAX
};
typedef uint32_t main_desktop_t;

class MainAPPStart : public LvcppTimerTask
{
public:
    MainAPPStart(LvcppMainScreen* parent = nullptr);
    ~MainAPPStart(void);
	void TimerCB(lv_timer_t * tmr);
    static void funcallback(msg_apps_t *msg);
    static void photomain_destory(void);
    static void videoMain_destory(void);
    static void musiclist_destory(void);
    static void calendarmain_destory(void);
    static void weathermain_destory(void);
    static void clockTimemain_destory(void);
    static void alarmScenemain_destory(void);
    static void settingScenemain_destory(void);

protected:
	void*  SCREEN_LAUBG_PNG=NULL; 
	void*  SCREEN_LAUPHOTO_PNG=NULL;                 
	void*  SCREEN_LAUVIDEO_PNG=NULL;                 
	void*  SCREEN_LAUMUSIC_PNG=NULL;               
	void*  SCREEN_LAUCALENDAR_PNG=NULL;         
	void*  SCREEN_LAUCLOCK_PNG=NULL;                
	void*  SCREEN_LAUSETTING_PNG=NULL;         
	void*  SCREEN_LAUWEATHER_PNG=NULL;         
	void*  SCREEN_LAUALARM_PNG=NULL;            
	void*  SCREEN_LAUWEATHER_BG_PNG=NULL;      
	void*  SCREEN_LAUWEATHER_NO_BG_PNG=NULL;   

	void*  SCREEN_LAUPHOTO1_PNG=NULL;          
	void*  SCREEN_LAUPHOTO2_PNG=NULL;          
	void*  SCREEN_LAUPHOTO3_PNG=NULL;
	
	void*  HEAD_WIFI0_PNG=NULL;                
	void*  HEAD_WIFI1_PNG=NULL;                
	void*  HEAD_WIFI2_PNG=NULL;                
	void*  HEAD_WIFI3_PNG=NULL;                
	void*  HEAD_WIFI4_PNG=NULL;                
	void*  HEAD_WIFINO_PNG=NULL;  

	void*  WEWATHER_BIG01_PNG = NULL;
	void*  WEWATHER_SMALL01_PNG = NULL;     
	void*  WEWATHER_SMALL02_PNG  = NULL;      
	void*  WEWATHER_SMALL03_PNG  = NULL; 

	void ui_image_decode(void);
    void ui_image_free(void);

private:
    LvcppMainScreen* m_panel;
    lv_obj_t* m_parent;
    bool show_status =false;
    int lauTimecnt = 0;

    photoMain* photoScene =NULL;
    videoMain* VideoMain =NULL;
    musicList* music_list =NULL;
    Calendar* calendar_main =NULL;
    Weather* weather_main =NULL;
    ClockTime* clockTime_main =NULL;
    alarmScene* alarmScene_main =NULL;
    settingScene* settingScene_main =NULL;
    lv_timer_t* maintimer =NULL;
    LvcppButton* objbtn_p =NULL;
    LvcppButton* objbtn_m =NULL;
    LvcppButton* objbtn_v =NULL;
    LvcppButton* objbtn_ca =NULL;
    LvcppButton* objbtn_cl =NULL;
    LvcppButton* objbtn_w =NULL;
    LvcppButton* objbtn_s =NULL;
    LvcppButton* objbtn_a =NULL;
    LvcppButton* objbtn_ws =NULL;
    LvcppButton* objbtn_p_child1 =NULL;
    LvcppButton* objbtn_p_child2 =NULL;
    LvcppButton* objbtn_p_child3 =NULL;
    LvcppButton* objbtn_w_cur =NULL;
    LvcppButton* objbtn_w_one =NULL;
    LvcppButton* objbtn_w_tow =NULL;
    LvcppButton* objbtn_w_three =NULL;
    LvcppButton* objbtn_wifi_state =NULL;

    LvcppLabel* str_a =NULL;
    LvcppLabel* str_c =NULL;
    LvcppLabel* str_v =NULL;
    LvcppLabel* str_m =NULL;
    LvcppLabel* str_s =NULL;
    LvcppLabel* str_city =NULL;
    LvcppLabel* str_temp =NULL;
    LvcppLabel* str_name_year =NULL;
    LvcppLabel* str_name_month =NULL;
    LvcppLabel* str_name_day =NULL;
    LvcppLabel* str_cur_date =NULL;
    LvcppLabel* str_cur_year =NULL;
    LvcppLabel* str_cur_time =NULL;
    LvcppLabel* str_apm_time =NULL;
    LvcppLabel* str_one_week =NULL;
    LvcppLabel* str_tow_week =NULL;
    LvcppLabel* str_three_week =NULL;
    LvcppLabel* str_one_mintemp =NULL;
    LvcppLabel* str_one_maxtemp =NULL;
    LvcppLabel* str_tow_mintemp =NULL;
    LvcppLabel* str_tow_maxtemp =NULL;
    LvcppLabel* str_three_mintemp =NULL;
    LvcppLabel* str_three_maxtemp =NULL;
    Alarmbounced* alarmBounced =NULL;

    lvcpp_sys_datetime_t user_time;
    char cur_photo_patch[1024]={0};
    char photo1_patch[1024]={0};
    char photo2_patch[1024]={0};
    char photo3_patch[1024]={0};
    char datetime_buff[256]={0};
    char weather_buff[64]={0};
    char* WeekStrOne =NULL;
    char* WeekStrTow =NULL;
    char* WeekStrThree =NULL;
    void* WifiHeadStr =NULL;
    bool apm_status =true;
    bool weather_show =false;
    int cur_hours =8, cur_mintes =30;
    int cur_year =2022,cur_month =1,cur_day =1;
    int cur_wifi_state =-1;
    int file_inde =0;
    int file_total =0;
    int win_inde =0;
    int show_time =0;
    int show_time_num =0;
    int slide_time[6]={5,10,15,30,60,300};
    Http *httpStart =NULL;
	checkTimeMsg *alarmCheckList =NULL;
    weather_info_t curWeatherInfo;
    weather_info_t oneWeatherInfo;
    weather_info_t towWeatherInfo;
    weather_info_t threeWeatherInfo;

    main_desktop_t cur_desktop =MAIN_DESKTOP;
    LvcppButton* LvcppButtonChild(lv_obj_t* paren,int x,int y,int w,int h,void  *ui_patch);
    LvcppLabel* LvcppLabelViewChild(lv_obj_t* paren,int x,int y,int w,int h,lv_align_t align,int str_color,char *str_buff);
	void Lvcpp_txt(LvcppLabel* parenView,char* str_buff);
    void Lvcpp_bg_img(LvcppButton* parenButton,void* pic_patch);
    LvcppButton* LvcppButtonIcon(lv_obj_t* paren,int x,int y,int w,int h,int icon,void *ui_patch);
	void* getCurWifiState(int wifi_ind);
    char* getCurWeekStr(int week);
    void getCurWeek(int y,int m, int d);
    int main_initial(void);
    int main_deinitial(void);
    void get_wifi_info(void);
    void delete_str(void);
    void delete_ui_free(void);
    void show_weather(void);
    void draw_scene_desktop(void);
    void draw_weather_scene(void);
    void draw_calendar_scene(void);
    void laufuncallback(void);
    void weatherMainUpdata(void);
	void start_ota_scene(char *patch);
    static void main_event_handler(lv_event_t *event);
    void play_next_file(void);
    int http_start(void);
    int http_get(int type);
    int _get_weather(char *cityname);
    void enter_photoList_app(void);
    void enter_videolist_app(void);
    void enter_musicScene_app(void);
    void enter_calendarScene_app(void);
    void enter_weatherScene_app(void);
    void enter_clockScene_app(void);
    void enter_alarmScene_app(void);
    void enter_settingScene_app(void);
};

#endif // MAINAPPSTART_H
