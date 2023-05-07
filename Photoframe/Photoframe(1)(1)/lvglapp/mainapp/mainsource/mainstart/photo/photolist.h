#ifndef PHOTOLIST_H
#define PHOTOLIST_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/include/configCustom.h"
#include  "mainstart/customer_config.h"
#include  "mainstart/scene_list/frame_list_icon.h"
#include "photolist_icon.h"
#include  "functional"
#include  "appmsg/appmsg.h"
#include "photoplaying.h"
#ifdef _UCHIP_T113
#include  "common/common.h"
#include  "common/list.h"
#endif
typedef struct photoListMainInfo_s
{
    int count;
    frameListIcon* list_item;
    photoListMainInfo_s *next_list;
}photoListMainInfo_t;

typedef struct photoChild_info_s
{
    photolistIcon* listIcon;
    photoChild_info_s *next_list;
}photoChild_info_t;

typedef struct saveImage_s
{
	int index;
    void* listImage;
    saveImage_s *next_list;
}saveImage_t;

typedef struct file_info_s
{
    int myindex;
    struct file_info_s *next_list;
}file_info_t;

class photoList : public LvcppTimerTask
{
public:
    photoList(int disType,lv_obj_t* parent,char *path);
    ~photoList(void);
	static void funcallback(msg_apps_t *msg);
    void photoPlaying_dele(void);
    int init_parament(void);
	void page_hide(void);
	char *_get_cur_filelist_patch(int index);
    void selfilelist_add_node(file_info_t *node);
    int _get_selfilelist_total(void);
    void _del_selfilelist(void);
    void _cpy_selfilelist(void);
    void _del_selfilelist_curpatch(int index);
    void _add_selfilelist(int index);
    void _destory_selfilelist(void);
	void _add_allfilelist(void);
protected:

	void*  HEAD_RETURN_PNG=NULL;              
	void*  HEAD_RETURN_SEL_PNG=NULL;

	void*  HEAD_ICON_PHOTO_PNG=NULL;
	
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

	void*  PHOTO_PNG=NULL; 
    void ui_image_decode(void);
    void ui_image_free(void);
private:

	LvcppFreeTypeFont* myfont = nullptr;
	lv_timer_t* photoListTimer =NULL;
	void TimerCB(lv_timer_t * tmr);
	void childFileList_add_node(photoChild_info_t *node);
	void add_childFileList(int index);
	photoChild_info_t* get_cur_childFileList(int index);
	void free_childFileList(void);
	void change_childFileList_status(int index);
	void freeall_childFileList(void);
	void destory_childFileList(void);
	void saveImage_add_node(saveImage_t *node);
	void add_saveImage(photoChild_info_t* curFileList);
	void free_cur_saveImage(int index);
	void destory_saveImage(void);
	int get_saveImage_total(void);
    LvcppScreen* frame=NULL;
    lv_obj_t*  mainscreen=NULL;
    LvcppButton* buttonReturn =NULL;
    LvcppButton* photoIcon =NULL;
	LvcppButton* IconAdd =NULL;
	LvcppButton* IconSor =NULL;
	LvcppButton* IconCpy =NULL;
    LvcppButton* IconDel =NULL;
    LvcppButton* IconChe =NULL;
    LvcppButton* IconBack =NULL;
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
    LvcppLabel* StrIconNum =NULL;
    LvcppList* list_main =NULL;
    LvcppTableFlex* list_photoList =NULL;
    photoListMainInfo_t* mainListHead =NULL;
    photoChild_info_t* photoListHead =NULL;
	saveImage_t* saveImageHead =NULL;
    file_info_t *SelFileList=NULL;
	
	int photoIndex =0;
	int decode_count = -1;
	int MoveStatu = 0;
	int FileStart = 0;
	int decodeStart = 0;
	int decodeCur = 0;
	int decodeEnd = 15;
	int heightOffect =0;
	int YOffect = 0;
	int height_num =5;
	int width_num =4;
	int DiskShowType =1;
	int CpyType =0;
	bool enterPathStatus =false;
	bool ScrollStatus =false;
	bool UEnter =false;
	bool SDEnter =false;
	bool drawListStatus =false;
	bool chDisStatus =false;
	bool deStatus =false;
	bool checkThreadStatus =false;
	int deCur =0;
	static void* check_thread_start(void *param);
	static void *decode_thread_start(void *param);
	void photoList_stop_decode(void);
	void photoList_exit_decode(void);
	void photoList_start_decode(void);
	int photo_media_creat(void);
	void photo_media_delete(void);
	void check_disk_status(void);
    char photo_listpatch[1024]={0};
    int flash_inde =0;
    int flash_total =6;
    int checkedNum =0;
    int photoListCur =0;
    int photoListTotal =0;
    bool IconStation =false;
    bool IconCheck =false;
    photoPlaying* photoPlay =NULL;
    LvcppButton* LvcppButtonHead(lv_obj_t* paren,bool show_cb,lv_ui_inof_t *uiInfo);
    LvcppLabel* LvcppLabelViewChild(lv_obj_t* paren,lv_text_align_t align,lv_str_inof_t *strInfo);
    void delete_ui_free(void);
	void photolist_del_mute_creat(void);
	void photolist_del_mute_dele(void);
	void photolist_cpy_mute_creat(void);
    void photolist_cpy_mute_dele(void);
    static void photolist_cpy_event_handler(lv_event_t *event);
	static void photolist_del_event_handler(lv_event_t *event);
    void photo_list_head_creat(void);
    void draw_headlist(void);
    void photo_list_head_dele(void);
    static void head_event_handler(lv_event_t *event);
    int photomian_list_creat(void);
    int photomian_list_add(void);
    void photomian_list_head_creat(int data,framelist_btn_t *btn,framelist_txt_t *txt,framelist_icon_t *icon);
    void photomian_list_head_add(photoListMainInfo_t *mainlist);
    void photomian_list_dele(void);
    static void main_event_handler(lv_event_t *event);
    int photoList_list_creat(void);
    void draw_photoList_list(void);
    void draw_photoListIcon_list(void);
    void photoList_list_delete(void);
	static void photoList_scroll_event_handler(lv_event_t *event);
    static void photoList_event_handler(lv_event_t *event);
};

#endif // PHOTOLIST_H
