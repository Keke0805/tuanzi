#ifndef WEATHER_H
#define WEATHER_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/include/configCustom.h"
#include  "mainstart/customer_config.h"
#include  "mainstart/scene_list/weather_list.h"
#include  "functional"
#include  "../../appmsg/appmsg.h"
#include  "network/http.h"

typedef struct cityListInfo_s
{
    int count;
    WeatherList* list_item;
    cityListInfo_s *next_list;
}cityListInfo_t;

class Weather : public LvcppTimerTask
{
public:
    Weather(lv_obj_t* parent,Http *httpStart);
    ~Weather(void);
    int init_parament(void);
    void get_weather_scene_info(void);
    void Weather_scene_draw(void);
	
protected:

	void*  HEAD_RETURN_PNG=NULL;
	void*  HEAD_RETURN_SEL_PNG=NULL;
	
	void*  HEAD_ICON_WEATHER_PNG=NULL;

	void*  LISTBG_PNG=NULL; 
	
	void*  WEATHER_UNADD_PNG=NULL;
	void*  WEATHER_ADD_PNG=NULL;
	void*  WEATHER_BIG_PNG=NULL;
	void*  WEATHER_MODE_PNG=NULL;
	void*  WEATHER_MODEB_PNG=NULL;
	
    void ui_image_decode(void);
    void ui_image_free(void);
	
private:
    lv_timer_t* weathertimer =NULL;
    LvcppScreen* frame;
    lv_obj_t*  mainscreen;
    Http *weaInfo =NULL;
    LvcppButton* buttonReturn =NULL;
    LvcppButton* weatherIcon =NULL;
    LvcppButton* todayWea =NULL;
    LvcppButton* towWea =NULL;
    LvcppButton* threeWea =NULL;
    LvcppButton* cityScene =NULL;
    LvcppButton* lineScene1 =NULL;
    LvcppButton* lineScene2 =NULL;
    LvcppButton* lineScene3 =NULL;
    LvcppScreen* cityAddScene =NULL;
    LvcppButton* cityAdd =NULL;
    LvcppButton* TempCheck =NULL;
    LvcppButton* TempCheck1 =NULL;
    LvcppButton* TempCheck2 =NULL;
    LvcppLabel* strTodayWea =NULL;
    LvcppLabel* strTowWea =NULL;
    LvcppLabel* strThreeWea =NULL;
    LvcppLabel* strWeekTow =NULL;
    LvcppLabel* strWeekThree =NULL;
    LvcppLabel* strCurTemp =NULL;
    LvcppLabel* strTodayTemp =NULL;
    LvcppLabel* strTowTemp =NULL;
    LvcppLabel* strThreeTemp =NULL;
    LvcppLabel* strCurHum =NULL;
    LvcppLabel* strCurWin =NULL;
    LvcppList*  cityList =NULL;
    cityListInfo_t *cityListHead =NULL;
    weather_info_t curWeatherInfo;
    weather_info_t oneWeatherInfo;
    weather_info_t towWeatherInfo;
    weather_info_t threeWeatherInfo;
    char *todayWeaPatch=NULL;
    char *towWeaPatch=NULL;
    char *threeWeaPatch=NULL;
    char CurTempBuff[12]={0};
    char OneTempBuff[12]={0};
    char TowTempBuff[12]={0};
    char ThreeTempBuff[12]={0};
    char HumBuff[128]={0};
    char WinBuff[128]={0};
    bool TempTpye =false;
    int CurCity =0;

    void TimerCB(lv_timer_t * tmr);
    LvcppButton* LvcppButtonHead(lv_obj_t* paren,bool show_cb,lv_ui_inof_t *uiInfo);
    void Lvcpp_Head_img(LvcppButton* parenButton,void* pic_patch);
    LvcppLabel* LvcppLabelViewChild(lv_obj_t* paren,lv_text_align_t align,lv_str_inof_t *strInfo);
    char* calendar_get_week(int week);
    void get_weather_CurInfo(float temp,char *curtemp);
    void get_weather_MaxMinInfo(float MinTemp,float MaxTemp,char *curtemp);
    void get_weather_CheckInfo(void);
    void weather_head_creat(void);
    void weater_head_dele(void);
    static void head_event_handler(lv_event_t *event);
    void Weather_scene_creat(void);
    void Weather_scene_dele(void);
    void Weather_citylist_creat(void);
    void citylist_add(void);
    static void citylist_event_handler(lv_event_t *event);
    void Weather_citylist_dele(void);
    void Weather_citylist_head_creat(int data,double lat,double lon,char *cityName);
    void Weather_citylist_head_add(cityListInfo_t *citylist);
    void Weather_citylist_head_draw(void);
    void Weather_citylist_head_destory(void);
};

#endif // WEATHER_H
