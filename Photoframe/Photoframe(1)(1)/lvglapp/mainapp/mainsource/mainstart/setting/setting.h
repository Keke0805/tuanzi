#ifndef SETTING_H
#define SETTING_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/include/configCustom.h"
#include  "mainstart/customer_config.h"
#include  "functional"
#include  "../../appmsg/appmsg.h"
#include "main_icon_list.h"
#include "frame_sence.h"
#include "album_scene.h"
#include "factory_sence.h"
#include "about_sence.h"
#include "help_sence.h"

#ifdef _UCHIP_T113
#include  "common/common.h"
#else
    #include  "driver/va_wifi.h"
#endif

typedef struct
{
	char device_name[128];									//我的相框---设备名
	char user_name[128];									//我的相框---用户名
	int blk;												//背光
	int vol;												//声音
	int tpvol_statue;										//TP---声音
	int ball;												//悬浮球
	int language;											//语言
	int autoplay;											//自动播放
	int disp_order;											//显示顺序
	int order_sty;											//排序方式
	int describe;											//描述
	int renti;												//人体感应
	int msg_sound;											//消息通知声音
	int res_factory;										//恢复出厂设置
	int auto_datetime;										//自动确定日期和时间
	int time_sty;											//自动确定日期和时间
	char day[24];											//日期
	char time[24];											//时间

	int auto_sleep;											//自动关机
	char auto_startup[128];									//自动开机时间
	char auto_shutdown[128];								//自动关机时间
	
	char set_day[128];										//手动设置的日期
	char set_time[128];										//手动设置的时间

	int wlan_sw;											//wifi开关
} setting_statue_info;

class settingScene : public LvcppTimerTask
{
public:
    settingScene(lv_obj_t* parent);
    ~settingScene(void);
    int init_parament(void);

protected:

	void*  HEAD_RETURN_PNG=NULL;              
	void*  HEAD_RETURN_SEL_PNG=NULL;

	void*  HEAD_ICON_SETTING_PNG=NULL;

	void*  LISTBG_PNG=NULL;

	void*  SETTING_MYFRAME_PNG=NULL;          
	void*  SETTING_ALBUM_PNG=NULL;            
	void*  SETTING_WIFI_PNG=NULL;             
	void*  SETTING_FACTORY_PNG=NULL;          
	void*  SETTING_HELP_PNG=NULL;             
	void*  SETTING_ABOUT_PNG=NULL;            

	void*  SETTING_ALBUM_DELETE_PNG=NULL;     
	void*  SETTING_ALBUM_TURE_PNG=NULL;       
	void*  SETTING_DISP_BRI_PNG=NULL;         
	void*  SETTING_DISP_TZVOL_PNG=NULL;       
	void*  SETTING_DISP_TPVOL_PNG=NULL;       
	void*  SETTING_DISP_BOY_PNG=NULL;         
	void*  SETTING_DISP_LAGU_PNG=NULL;        
	void*  SETTING_DISP_PLAY_PNG=NULL;        
	void*  SETTING_DISP_PHOTO_PNG=NULL;       
	void*  SETTING_DISP_VOL_PNG=NULL;         
	void*  SETTING_DISP_DATATIME_PNG=NULL;    
	void*  SETTING_DISP_MIAOSHU_PNG=NULL;     
	void*  SETTING_DISP_RENTI_PNG=NULL;       
	void*  SETTING_DISP_SLEEP_PNG=NULL;       
	void*  SETTING_DISP_DEVICE_PNG=NULL;      
	void*  SETTING_DISP_OPEN_PNG=NULL;        
	void*  SETTING_DISP_CLOSE_PNG=NULL;       
	void*  SETTING_DOWN_DEVICE_PNG=NULL;      
	void*  SETTING_UP_DEVICE_PNG=NULL; 
	void*  SETTING_FRAME_USERMAKE_PNG=NULL;   
	void*  SETTING_FRAME_REFRESH_PNG=NULL;    
	void*  SETTING_FRAME_ADD_PNG=NULL;        
	void*  SETTING_FRAME_USERHEAD_PNG=NULL;   

	void*  SETTING_HELP1_PNG=NULL;            
	void*  SETTING_HELP2_PNG=NULL;            
	void* SETTING_ICON_SCENE1_PNG=NULL;       
	void* SETTING_ICON_SCENE2_PNG=NULL;       
	void* SETTING_ICON_SCENE3_PNG=NULL;       
	void* SETTING_ICON_SCENE4_PNG=NULL;       
	void* SETTING_ICON_SCENE5_PNG=NULL;       
	void* SETTING_GOOGLE_PNG=NULL;            
	void* SETTING_IOSAPP_PNG=NULL;            
	void* SETTING_LEFT_PNG=NULL;              
	void* SETTING_RIGHT_PNG=NULL;             
	void* SETTING_SCENE1_PNG=NULL;            
	void* SETTING_SCENE2_PNG=NULL;            
	void* SETTING_SCENE3_PNG=NULL;            
	void* SETTING_SCENE4_PNG=NULL;            
	void* SETTING_SCENE5_PNG=NULL;            
	void* SETTING_SCENE6_PNG=NULL;

    void ui_image_decode(void);
    void ui_image_free(void);

private:
    lv_timer_t* wlantimer =NULL;
    void TimerCB(lv_timer_t * tmr);

    int list_index=0;
	int list_save_index=0;
	setting_statue_info statue;
    LvcppScreen* frame;
    lv_obj_t*  mainscreen;
    LvcppButton* buttonReturn =NULL;
    LvcppButton* settingIcon =NULL;
	LvcppButton* line_head =NULL;
    LvcppList* mainList =NULL;
    mainIconList* MyFrameList =NULL;
    mainIconList* AlbumList =NULL;
    mainIconList* WiFiList =NULL;
    mainIconList* FactoryList =NULL;
    mainIconList* HelpList =NULL;
    mainIconList* AboutList =NULL;
    LvcppButton* listframe =NULL;
    LvcppButton* helpReturn=NULL;
	
	LvcppList* childList =NULL;
    frameSence* frame_scene =NULL;
    albumScene* album_scene =NULL;
    factorySence* fcactory_scene =NULL;
    aboutSence* about_scene =NULL;
    helpSence* help_scene =NULL;
	
	static void head_event_handler(lv_event_t *event);
	static void settingScene_main_event_handler(lv_event_t *event);
    void settingScene_head_creat(void);
    void settingScene_head_dele(void);

    void settingScene_main_creat(void);
    void settingScene_main_dele(void);
   
    void child_scene_creat(void);
    void child_scene_del(void);
    void create_child_list(int indexList);
    void del_child_list(int indexList);
    void create_frame_list(void);
    void delete_frame_list(void);
    void create_album_list(void);
    void delete_album_list(void);
    void create_fcactory_list(void);
    void delete_fcactory_list(void);
    void create_help_list(void);
    void delete_help_list(void);
    void create_about_list(void);
    void delete_about_list(void);
};

#endif // SETTING_H
