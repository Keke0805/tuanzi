#ifndef PHOTOPLAYING_H
#define PHOTOPLAYING_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/include/configCustom.h"
#include  "mainstart/customer_config.h"
#include  "functional"
#include  "../../appmsg/appmsg.h"
#include "mainstart/scene_list/menu_list.h"

typedef enum {
    HEAD_PPLAY = 0,
    HEAD_PPLAY_ROA,
    HEAD_PPLAY_SCA,
    HEAD_PPLAY_PLAY,
    HEAD_PPLAY_DEL,
    HEAD_PPLAY_ZOO,
    HEAD_PPLAY_SET,
    HEAD_PPLAY_INFO,
    HEAD_PPLAY_HEAR,
    HEAD_PPLAY_SCENE,
    HEAD_PPLAY_MAX
}head_photo_icon_t;

typedef struct _lv_pplayui_inof_t {
    int x;
    int y;
    int w;
    int h;
    void *ui_patch;
} lv_pplayui_inof_t;

typedef struct
{
    menuList* Menulist[16];
}lv_ppmenulist_t;

class photoPlaying : public LvcppTimerTask
{
public:
    photoPlaying(void);
    ~photoPlaying(void);
    int init_parament(int disk_type, char* file_patch);

protected:
	void*  HEAD_RETURN_PNG=NULL;              
	void*  HEAD_RETURN_SEL_PNG=NULL;

	void*  LIST_UNSEL_PNG=NULL;
	void*  LIST_CIRCLESEL_PNG=NULL;

	void*  PHOTO_HEAD_ROAT_PNG=NULL;          
	void*  PHOTO_HEAD_SCAI_PNG=NULL;          
	void*  PHOTO_HEAD_SCAO_PNG=NULL;          
	void*  PHOTO_HEAD_PAUSE_PNG=NULL;         
	void*  PHOTO_HEAD_PLAY_PNG=NULL;          
	void*  PHOTO_HEAD_DEL_PNG=NULL;           
	void*  PHOTO_HEAD_ZOOM_PNG=NULL;          
	void*  PHOTO_HEAD_SET_PNG=NULL;           
	void*  PHOTO_HEAD_INFO_PNG=NULL;          
	void*  PHOTO_HEAD_HEARTF_PNG=NULL;        
	void*  PHOTO_HEAD_HEARTN_PNG=NULL;        
	void*  PHOTO_HEAD_SCENE_PNG=NULL;
	void*  PHOTO_PNG=NULL;                    
	void*  PHOTO_ALL_PNG=NULL;                
	void*  PHOTO_INTERNAL_PNG=NULL;           
	void*  PHOTO_SD_PNG=NULL;                 
	void*  PHOTO_USB_PNG=NULL;                
	void*  PHOTO_LOVE_PNG=NULL;               
	void*  PHOTO_OTHER_PNG=NULL;              
	void*  PHOTO_ROUND_PNG=NULL;
	
    void ui_image_decode(void);
    void ui_image_free(void);

private:
    LvcppScreen* frame;
    lv_obj_t*  mainscreen;
    lv_timer_t* photoPlayTimer =NULL;
    LvcppButton* buttonReturn =NULL;
    LvcppButton* buttonHead =NULL;
    LvcppButton* tonRoa =NULL;
    LvcppButton* tonSca =NULL;
    LvcppButton* tonPlay =NULL;
    LvcppButton* tonDel =NULL;
    LvcppButton* tonZoo =NULL;
    LvcppButton* tonSet =NULL;
    LvcppButton* tonInfo =NULL;
    LvcppButton* tonHear =NULL;
    LvcppButton* tonScene =NULL;
    LvcppLabel* str_num =NULL;

	LvcppButton* mainMenuButton =NULL;
    LvcppLabel* mainMenuLabel =NULL;
    LvcppLabel* intervalMenuLabel =NULL;

    LvcppLabel* cpNameLabel =NULL;
    LvcppLabel* bmNameLabel =NULL;
    LvcppLabel* inNameLabel =NULL;
    LvcppLabel* efNameLabel =NULL;
    LvcppLabel* cpDataLabel =NULL;
    LvcppLabel* bmDataLabel =NULL;
    LvcppLabel* inDataLabel =NULL;
    LvcppLabel* efDataLabel =NULL;
    LvcppLabel* mainLineLabel1 =NULL;
    LvcppLabel* mainLineLabel2 =NULL;
    LvcppLabel* mainLineLabel3 =NULL;

    LvcppImageButton* Image5S =NULL;
    LvcppImageButton* Image10S =NULL;
    LvcppImageButton* Image15S =NULL;
    LvcppImageButton* Image30S =NULL;
    LvcppImageButton* Image1M =NULL;
    LvcppImageButton* Image5M =NULL;
    LvcppLabel* Label5S =NULL;
    LvcppLabel* Label10S =NULL;
    LvcppLabel* Label15S =NULL;
    LvcppLabel* Label30S =NULL;
    LvcppLabel* Label1M =NULL;
    LvcppLabel* Label5M =NULL;
    LvcppLabel* inLineLabel1 =NULL;
    LvcppLabel* inLineLabel2 =NULL;
    LvcppLabel* inLineLabel3 =NULL;
    LvcppLabel* inLineLabel4 =NULL;
    LvcppLabel* inLineLabel5 =NULL;
    LvcppList* effectList =NULL;
    lv_ppmenulist_t effectmenuList;

	LvcppButton* InfoMenuButton =NULL;
    LvcppLabel* InfoMenuLabel =NULL;
    LvcppLabel* FlieLabel =NULL;
    LvcppLabel* InfoLineLabel =NULL;
    LvcppLabel* PatchLabel =NULL;
    LvcppLabel* FlieNameLabel =NULL;
    LvcppLabel* FlieSizeLabel =NULL;
    LvcppLabel* FlieTimeLabel =NULL;

	LvcppLabel* CapLabel =NULL;
    LvcppLabel* CaIconLabel =NULL;
    LvcppLabel* CaTimeLabel =NULL;
    LvcppLabel* CaDateLabel =NULL;
    LvcppLabel* CaWeekLabel =NULL;
    lvcpp_sys_datetime_t user_time;
	
    int captionType=0;
    int bgmType=0;
    int intervalType=0;
    int effectType=0;

    char photo_playpatch[1024]={0};
	char MountPoint[128]={0};
    int timecntback = 0;
    int flash_inde =0;
    int file_inde =1;
    int file_total =7;
    bool show_status =false;
	bool show_zoom =false;
    int show_time_num =0;
	int senceType =1;
	int senceMode =0;
    int slide_time[6]={5,10,15,30,60,300};
    bool StartTimerShow =false;
    bool head_show =true;
    void TimerCB(lv_timer_t * tmr);
    static void main_event_handler(lv_event_t *event);
    static void back_event_handler(lv_event_t *event);
    LvcppButton* LvcppButtonHead(lv_obj_t* paren,lv_pplayui_inof_t *uiInfo);
    LvcppLabel* LvcppLabelViewHead(lv_obj_t* paren,int x,int y,int w,int h,char * str_buff);
    void photo_play_head_creat(void);
    static void head_event_handler(lv_event_t *event);
    void play_next_file(void);
    void draw_picture(void * playpatch);

	void image_play_scan(char *CurPatch);
	void image_play_phread_creat(void);
	void image_play_phread_down(void);
	void image_play_thread_up(void);
	void image_play_stop(void);
	void image_auto_play_start(void);
	void image_auto_play_stop(void);
	void image_play_prepare(void);

	int image_play_get_status(void);
	int image_play_get_interval(void);

	static void* image_auto_play_pthread(void *arg);
	void photoplay_mainMenu_creat(void);
    void photoplay_mainMenu_del(void);
    void photoplay_intervalMenu_creat(void);
    void photoplay_intervalMenu_del(void);
    void photoplay_effectMenu_creat(void);
    void photoplay_effectMenu_del(void);
    void photoplay_Menu_del(void);
    static void photoplay_mainMenu_event_handler(lv_event_t *event);
	void photoplay_InfoMenu_creat(void);
    void photoplay_InfoMenu_del(void);
    static void photoplay_InfoMenu_event_handler(lv_event_t *event);
	void photoplay_caption_creat(void);
    void photoplay_caption_del(void);
    char* get_week_str(void);
    char* get_apm_str(void);
    void photoplay_caption_show(bool status);
    void photoplay_caption_updata(void);
	void photoplay_rm_CurFile(void);
};

#endif // PHOTOPLAYING_H
