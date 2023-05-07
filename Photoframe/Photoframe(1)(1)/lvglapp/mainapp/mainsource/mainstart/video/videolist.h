#ifndef VIDEOLIST_H
#define VIDEOLIST_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/include/configCustom.h"
#include  "mainstart/customer_config.h"
#include  "mainstart/scene_list/frame_list_icon.h"
#include  "mainstart/scene_list/frame_scenelist.h"
#include  "mainstart/scene_list/frame_list_icon_center.h"
#include  "functional"
#include  "videoplay.h"
#include  "appmsg/appmsg.h"

typedef struct
{
    int count;
    frameListIconCenter* list_item[MAIN_LIST_MAX];
}main_videolist_item_info;

typedef struct
{
    int inde;
    int count;
    frameListIcon* list_item[FILE_LIST_MAX];
}videolist_item_info;

typedef struct Vfile_info_s
{
    int myindex;
	char filePath[1024];
    struct Vfile_info_s *next_list;
}Vfile_info_t;

class videoList
{
public:
    videoList(lv_obj_t* parent);
    ~videoList(void);
    int init_parament(int disk_type,char* file_patch);

protected:

	void*  HEAD_RETURN_PNG=NULL;              
	void*  HEAD_RETURN_SEL_PNG=NULL;

	void*  HEAD_ICON_VIDEO_PNG=NULL;

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
	
	void* VIDEO_UNPLAYING_PNG=NULL;           
	void* VIDEO_PLAYING_PNG=NULL;             
	void* VIDEO_UNSTOP_PNG=NULL;              
	void* VIDEO_STOP_PNG=NULL;                
	void* VIDEO_UNNEXT_PNG=NULL;              
	void* VIDEO_NEXT_PNG=NULL;                
	void* VIDEO_UNPREV_PNG=NULL;              
	void* VIDEO_PREV_PNG=NULL;                
	void* VIDEO_LIGHT_PNG=NULL;               
	void* VIDEO_VOLMAX_PNG=NULL;              
	void* VIDEO_VOLMID_PNG=NULL;              
	void* VIDEO_VOLMIN_PNG=NULL;              
	void* VIDEO_MUSICS_PNG=NULL;              
	void* VIDEO_MUSICSOFF_PNG=NULL;           
	void* VIDEO_RING_PNG=NULL;                
	void* VIDEO_RINGOFF_PNG=NULL;             
	void* VIDEO_BTN_PNG=NULL; 

    void ui_image_decode(void);
    void ui_image_free(void);
private:
	LvcppFreeTypeFont* myfont = nullptr;
	void check_disk_status(void);
	
    LvcppScreen* frame=NULL;
    lv_obj_t*  mainscreen=NULL;
    VideoPlay* video_play=NULL;
    LvcppButton* buttonReturn =NULL;
    LvcppButton* videoIcon =NULL;
    LvcppButton* IconSor =NULL;
    LvcppButton* IconCpy =NULL;
    LvcppButton* IconDel =NULL;
    LvcppButton* IconChe =NULL;
    LvcppButton* IconBack =NULL;
    LvcppButton* IconPlaying =NULL;
    LvcppButton* videoThum =NULL;
    LvcppImageButton* btnAIcon =NULL;
    LvcppButton* btnB =NULL;
    LvcppButton* btnBChild =NULL;
    LvcppImageButton* btnBIcon=NULL;
    LvcppLabel* labA =NULL;
    LvcppLabel* StrIconNum =NULL;
    LvcppList* list_main =NULL;
    LvcppList* list_videoList =NULL;
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
    main_videolist_item_info main_list_id;
    videolist_item_info video_list_id;

	Vfile_info_t *SelFileList=NULL;

	int play_flag = 0;
	int decode_flag = 0;
	int video_decode_start(void);
	void video_decode_delete(void);
	char *_get_cur_filelist_patch(int index);
	void selfilelist_add_node(Vfile_info_t *node);
    int _get_selfilelist_total(void);
    void _del_selfilelist(void);
    void _cpy_selfilelist(void);
    void _del_selfilelist_curpatch(int index);
    void _add_selfilelist(int index);
    void _destory_selfilelist(void);
	void _add_allfilelist(void);

	bool UEnter =false;
	bool SDEnter =false;
    bool IconStation =false;
    bool IconCheck =false;
    bool IconCheckAll =false;

	int CpyType =0;
	int DiskShowType =1;
    int flash_inde =0;
    int flash_total =4;
    int checkedNum =0;
	int videoIndex=0;
    int videoListTotal =0;
    char video_listpatch[1024]={0};
    char videoSize[64]={0};
    char videoNum[64]={0};
    LvcppButton* LvcppButtonHead(lv_obj_t* paren,bool show_cb,lv_ui_inof_t *uiInfo);
    LvcppLabel* LvcppLabelViewChild(lv_obj_t* paren,lv_text_align_t align,lv_str_inof_t *strInfo);
	void videoList_clean_fileInfo(int start);
	int videoList_media_creat(void);
	int draw_btn_info(void);
	void videolist_del_mute_creat(void);
	void videolist_del_mute_dele(void);
	void videolist_cpy_mute_creat(void);
    void videolist_cpy_mute_dele(void);
    static void videolist_cpy_event_handler(lv_event_t *event);
	static void videolist_del_event_handler(lv_event_t *event);
    void video_list_head_creat(void);
    void draw_headlist(void);
    void video_list_head_dele(void);
    static void head_event_handler(lv_event_t *event);
    int video_list_creat(void);
    int videomian_list_add(void);
    void videomian_list_add_info(main_videolist_item_info *list_id,int cur_num,char *nameIcon);
    int draw_main_list(void);
    void videomian_list_dele(void);
    static void main_event_handler(lv_event_t *event);
    int videoList_list_creat(void);
    int videoList_list_add(void);
    int draw_videoList_list(void);
    void set_videoListIcon_list(bool type);
    void draw_videoListIcon_list(bool type);
    void videoList_list_delete(void);
    static void videoList_event_handler(lv_event_t *event);
};

#endif // VIDEOLIST_H
