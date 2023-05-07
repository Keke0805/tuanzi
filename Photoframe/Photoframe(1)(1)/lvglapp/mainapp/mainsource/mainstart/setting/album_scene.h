#ifndef ALBUM_SCENE_H
#define ALBUM_SCENE_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include "album_list.h"
#include "album_language.h"
#include "album_slideshow.h"
#include "album_slideshow_mode.h"
#include "album_montion.h"

class albumScene
{
public:
    albumScene(lv_obj_t* parent = nullptr);
    ~albumScene(void);
    void albumLau_del(void);
    albumLanguage* lauList =NULL;

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
	
	void*  SETTING_HELP1_PNG=NULL;			  
	void*  SETTING_HELP2_PNG=NULL;

	void ui_image_decode(void);
	void ui_image_free(void);

private:
    void albumBri(void);
    void albumVol(void);
    void albumTpVol(void);
    void albumQiu(void);
    void albumLau(void);
    void albumSlideshow(void);
    void albumSlideshow_del(void);
    void albumSlideshowMode(void);
    void albumSlideshowMode_del(void);
    void albumplay(void);
    void albumphoto(void);
    void albumMiao(void);
    void albumIRQ(void);
    void albumMontions(void);
    void albumMontions_del(void);
    void albumsVol(void);
    static void albumScene_event_handler(lv_event_t *event);
    static void albumSlideShow_event_handler(lv_event_t *event);
    static void albumSlideShowMode_event_handler(lv_event_t *event);
    static void Montion_event_handler(lv_event_t *event);
    lv_obj_t* album_parent =NULL;
    albumList *briAlbumList =NULL;
    albumList *volAlbumList =NULL;
    albumList *tpVolAlbumList =NULL;
    albumList *qiuAlbumList =NULL;
    albumList *lauAlbumList =NULL;
    albumList *playAlbumList =NULL;
    albumList *photoAlbumList =NULL;
    albumList *miaoAlbumList =NULL;
    albumList *dateTimeAlbumList =NULL;
    albumList *sleepAlbumList =NULL;
    albumList *IRQAlbumList =NULL;
    albumList *sVolAlbumList =NULL;

    albumSlideShow *SlideshowList =NULL;
    albumSlideShowMode *SlideshowModeList =NULL;
    albumMontion *albumMontionList =NULL;
    int brightNum =0;
    int volNum =0;
    int touchSounds =0;
    int assistiveTouch =0;
    int slideshow =0;
    int slideshowMode =0;
    int caption =0;
    int montion =0;
    int notSound =0;
};

#endif // ALBUM_SCENE_H
