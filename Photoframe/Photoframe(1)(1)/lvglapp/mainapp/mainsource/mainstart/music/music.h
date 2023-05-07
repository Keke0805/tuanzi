#ifndef MUSIC_H
#define MUSIC_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/include/configCustom.h"
#include  "mainstart/customer_config.h"
#include  "mainstart/scene_list/frame_list_icon.h"
#include  "mainstart/scene_list/frame_scenelist.h"
#include  "mainstart/scene_list/frame_list_icon_center.h"
#include  "mainstart/scene_list/shuffle_list.h"
#include  "functional"
#include  "../../appmsg/appmsg.h"

typedef struct
{
    int count;
    frameListIconCenter* list_item[MAIN_LIST_MAX];
}main_musiclist_item_info;

typedef struct
{
    int inde;
    int count;
    frameListIcon* list_item[FILE_LIST_MAX];
}musiclist_item_info;

typedef struct Mfile_info_s
{
    int myindex;
	char filePath[1024];
    struct Mfile_info_s *next_list;
}Mfile_info_t;
class musicList : public LvcppTimerTask
{
public:
    musicList(lv_obj_t* parent);
    ~musicList(void);
    int init_parament(void);
	
protected:
	void*  HEAD_RETURN_PNG=NULL;              
	void*  HEAD_RETURN_SEL_PNG=NULL;

	void*  HEAD_ICON_MUSIC_PNG=NULL;
	void*  LISTBG_PNG=NULL; 

	void*  LIST_ICON_ALL_PNG=NULL;            
	void*  LIST_ICON_FLASH_PNG=NULL;          
	void*  LIST_ICON_SD_PNG=NULL;             
	void*  LIST_ICON_U_PNG=NULL;              
	void*  LIST_ICON_FILE_PNG=NULL;           
	void*  LIST_ICON_LOVE_PNG=NULL;           
	void*  LIST_ICON_USER_PNG=NULL;           
	void*  LIST_ICON_USERON_PNG=NULL;         
	void*  LIST_ICON_LINE_PNG=NULL;           
	void*  LIST_ICON_UNDEL_PNG=NULL;          
	void*  LIST_ICON_DEL_PNG=NULL;            
	void*  LIST_ICON_DELSEL_PNG=NULL;         
	void*  LIST_ICON_NOR_PNG=NULL;            
	void*  LIST_ICON_NORSEL_PNG=NULL;         
	void*  LIST_ICON_CHE_PNG=NULL;            
	void*  LIST_ICON_CHELSEL_PNG=NULL;        
	void*  LIST_ICON_CAN_PNG=NULL;            
	void*  LIST_ICON_CANLSEL_PNG=NULL;        
	void*  LIST_ICON_ICON_PNG=NULL;           
	void*  LIST_ICON_ICONLSEL_PNG=NULL;       
	void*  LIST_SEL_PNG=NULL;                 
	void*  LIST_UNSEL_PNG=NULL;               
	void*  LIST_ICON_VIDEOLINE_PNG=NULL;      
	void*  LIST_COPY_PNG=NULL;                
	void*  LIST_COPY_SEL_PNG=NULL;            
	void*  LIST_UNCOPY_PNG=NULL;              
	void*  LIST_SORT_PNG=NULL;                
	void*  LIST_SORT_SEL_PNG=NULL;            
	void*  LIST_ADDFILE_PNG=NULL;             
	void*  LIST_ADDFILE_SEL_PNG=NULL;         
	void*  LIST_UNADDFILE_PNG=NULL;                              
	void*  LIST_CIRCLE_PNG=NULL;
	void*  LIST_CIRCLESEL_PNG=NULL;

	void*  MUSIC_ICONCD_PNG=NULL;             
	void*  MUSIC_UNPLAY_PNG=NULL;             
	void*  MUSIC_PLAY_PNG=NULL;               
	void*  MUSIC_UNSTOP_PNG=NULL;             
	void*  MUSIC_STOP_PNG=NULL;               
	void*  MUSIC_UNPREV_PNG=NULL;             
	void*  MUSIC_PREV_PNG=NULL;               
	void*  MUSIC_UNNEXT_PNG=NULL;             
	void*  MUSIC_NEXT_PNG=NULL;               
	void*  MUSIC_UNSINGLE_PNG=NULL;           
	void*  MUSIC_SINGLE_PNG=NULL;             
	void*  MUSIC_UNSHUFFLE_PNG=NULL;          
	void*  MUSIC_SHUFFLE_PNG=NULL;            
	void*  MUSIC_UNLOOP_PNG=NULL;             
	void*  MUSIC_LOOP_PNG=NULL;               
	void*  MUSIC_VOLDOT_PNG=NULL;             
	void*  MUSIC_VOLICON_PNG=NULL;            
	void*  MUSIC_VOLBG_PNG=NULL;              
	void*  MUSIC_TIME_BG_PNG=NULL;            
	void*  MUSIC_TIMESEL_BG_PNG=NULL;         
	void*  MUSIC_TIMECUR_PNG=NULL;            
	void*  MUSIC_RECT_PNG=NULL; 
    void ui_image_decode(void);
    void ui_image_free(void);
	
private:
	LvcppFreeTypeFont* myfont = nullptr;
    LvcppScreen* frame;
    lv_obj_t*  mainscreen;
    LvcppButton* buttonReturn =NULL;
    LvcppButton* musicIcon =NULL;
    LvcppButton* IconSor =NULL;
    LvcppButton* IconCpy =NULL;
    LvcppButton* IconDel =NULL;
    LvcppButton* IconChe =NULL;
    LvcppButton* IconBack =NULL;
    LvcppButton* IconPlay =NULL;
    LvcppButton* IconPrev =NULL;
    LvcppButton* IconNext =NULL;
    LvcppButton* IconMode =NULL;
    LvcppButton* IconVol =NULL;
    LvcppImage *cdImg =NULL;
    LvcppAnimimg *animCdB;
    LvcppRotateAnimimg *animCd;
    LvcppLabel* StrIconNum =NULL;
    LvcppLabel* StrStartTime =NULL;
    LvcppLabel* StrEndTime =NULL;
    LvcppLabel* StrAlbum =NULL;
    LvcppLabel* StrArtist =NULL;
    LvcppList* list_main =NULL;
    LvcppList* list_musicList =NULL;
    LvcppSlider* musicSlider =NULL;
    LvcppSlider* volSlider =NULL;
	LvcppButton* delButton =NULL;
	LvcppButton* delChildButtonOk =NULL;
    LvcppButton* delChildButtonCancel =NULL;
	LvcppButton* cpyButton =NULL;
    LvcppButton* cpyChildButtonOk =NULL;
    LvcppButton* cpyChildButtonCancel =NULL;
    LvcppLabel* delChildButtonLine =NULL;
    LvcppLabel* delChildLabel =NULL;
	LvcppLabel* cpyChildButtonLine =NULL;
    LvcppLabel* cpyChildLabel =NULL;
    LvcppLabel* cpyCheckBox1 =NULL;
    LvcppLabel* cpyCheckBox2 =NULL;
    LvcppLabel* cpyChildLabel1 =NULL;
    LvcppLabel* cpyChildLabel2 =NULL;
    main_musiclist_item_info main_list_id;
    musiclist_item_info music_list_id;

	player_ui_t *PlayerUiM =NULL;
    shuffle_list *musicShuffleList =NULL;
	Mfile_info_t *SelFileList=NULL;

    bool StartTimerShow =false;
    bool IconStation =false;
    bool IconCheck =false;
    bool IconCheckAll =false;
    bool playStatus =false;
	bool UEnter =false;
	bool SDEnter =false;
	int DiskShowType =1;
    int PlayMode =0;
    int flash_inde =0;
    int flash_total =4;
    int checkedNum =0;
	int musicIndex=0;
    int musicListTotal =0;
    int StartTime =0;
    int EndTime =1;
    int CurVol =0;
	int CpyType =0;
    char music_listpatch[1024]={0};
    char AlbumBuff[256]={0};
    char ArtistBuff[256]={0};
    char startTimeBuff[10]={0};
    char endtTimeBuff[10]={0};
	void check_disk_status(void);
	char *_get_cur_filelist_patch(int index);
	void selfilelist_add_node(Mfile_info_t *node);
    int _get_selfilelist_total(void);
    void _del_selfilelist(void);
    void _cpy_selfilelist(void);
    void _del_selfilelist_curpatch(int index);
    void _add_selfilelist(int index);
    void _destory_selfilelist(void);
	void _add_allfilelist(void);
	void musiclist_del_mute_creat(void);
	void musiclist_del_mute_dele(void);
	void musiclist_cpy_mute_creat(void);
    void musiclist_cpy_mute_dele(void);
	static void musiclist_cpy_event_handler(lv_event_t *event);
	static void musiclist_del_event_handler(lv_event_t *event);
    LvcppButton* LvcppButtonHead(lv_obj_t* paren,bool show_cb,lv_ui_inof_t *uiInfo);
    LvcppLabel* LvcppLabelViewChild(lv_obj_t* paren,lv_text_align_t align,lv_str_inof_t *strInfo);
    LvcppSlider* LvcppSliderChild(lv_obj_t* paren,lv_slider_inof_t * curSlider);
	static void media_player_ui_callback(void *ui_player, media_event_t event, void *param);
	int play_time_update(void);
	void musicList_media_creat(void);
    void TimerCB(lv_timer_t * tmr);
    void ImgCd_creat(void);
    void music_Slider_creat(void);
    void music_Slider_delete(void);
    static void musicSlider_event_handler(lv_event_t *event);
    void music_list_head_creat(void);
    void draw_headlist(void);
    void music_list_head_dele(void);
    static void head_event_handler(lv_event_t *event);
    int music_list_creat(void);
    int musicmian_list_add(void);
    void musicmian_list_add_info(main_musiclist_item_info *list_id,int cur_num,char *nameIcon);
    int draw_main_list(void);
    void musicmian_list_dele(void);
    static void main_event_handler(lv_event_t *event);
    int musicList_list_creat(void);
    int musicList_list_add(void);
    int draw_musicList_list(void);
    void set_musicListIcon_list(bool type);
    void draw_musicListIcon_list(bool type);
    void musicList_list_delete(void);
    static void musicList_event_handler(lv_event_t *event);
	
	void music_list_start_playing(void);
	void music_list_stop_playing(void);
	void play_prve_next_file(bool status);
	void play_next_file(void);
};

#endif // MUSIC_H
