#ifndef FRAME_SENCE_H
#define FRAME_SENCE_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/include/configCustom.h"
#include  "mainstart/customer_config.h"
#include "frame_info_sence.h"
#include "frame_user_sence.h"
#include "frame_change_str.h"
#include "frame_user_info.h"

typedef struct
{
    int index;
    int total;
    frameUserSence *list_item[USER_LIST_MAX];
}userSenceList_item_info;

class frameSence
{
public:
    frameSence(lv_obj_t* parent = nullptr);
    ~frameSence(void);
	void updata_user_info(int index);
	void get_user_info(int index);
    LvcppLabel* frameNameList =NULL;
    LvcppLabel* frameDeviceInfo =NULL;
    LvcppLabel* frameDevice =NULL;
    LvcppLabel* frameInfo =NULL;
    LvcppLabel* frameName =NULL;
    LvcppLabel* frameDownUp =NULL;
    frameInfoSence* frameInfoList =NULL;
    frameChangeStr* frameStr =NULL;
    frameUserInfo* UserInfo =NULL;
    LvcppLabel* frameLine1 =NULL;
    LvcppLabel* frameLine2 =NULL;
    LvcppLabel* frameManagement =NULL;
    LvcppLabel* frameManaUser =NULL;
    LvcppLabel* frameManaUserStr =NULL;
    LvcppLabel* frameManaUserAdd =NULL;
    LvcppLabel* frameUserStr =NULL;
    LvcppList* frameUserList =NULL;
    userSenceList_item_info userList_id;

protected:
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

	void ui_image_decode(void);
	void ui_image_free(void);

private:
    static void frame_list_event_handler(lv_event_t *event);
    static void devName_event_handler(lv_event_t *event);
    static void user_list_event_handler(lv_event_t *event);
    static void userInfo_event_handler(lv_event_t *event);
    void frameStr_head_creat(char *headStr,char *dataStr);
    void frameStr_head_del(void);
    void userInfo_head_creat(int userIdex);
    void userInfo_head_del(void);
	int settinglist_get_userNum(void);
	int settinglist_userInfo(int userNum,char *userID);
	void set_user_remarkName(int index);
    char deviceNickname[128]={0};
    char emailstr[128]={0};
    char userName[64]={0};
	char senderId[64]={0};
    bool frameInfoStatus =true;
    int frameStrType =0;
	int userTotal =0;
	int userCurIdex=0;
};

#endif // FRAME_SENCE_H
