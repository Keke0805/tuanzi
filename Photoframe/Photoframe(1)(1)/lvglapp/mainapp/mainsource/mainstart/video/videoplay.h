#ifndef VIDEOPLAY_H
#define VIDEOPLAY_H

#include "lv_cpp/lvcpp_class.h"

#ifdef _UCHIP_T113
#include "common/common.h"
#endif


class VideoPlay :public LvcppTimerTask
{
public:
    VideoPlay(player_ui_t *playerUi);
    virtual ~VideoPlay();
    void init_parament(int disktype, char* file);
	
	static void media_player_ui_callback(void *ui_player, media_event_t event, void *param);

protected:

	void*  HEAD_RETURN_PNG=NULL;              
	void*  HEAD_RETURN_SEL_PNG=NULL;

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
    lv_timer_t* vplayer_timer=NULL;
    void TimerCB(lv_timer_t * tmr);

    LvcppScreen* vpscreen = NULL;
    lv_obj_t* vp_parent=NULL;
    LvcppSlider* bar_left=NULL;
    LvcppSlider* bar_right=NULL;
    LvcppButton* IconReturn =NULL;
    LvcppLabel* label_title=NULL;
    LvcppLabel* labelIcon=NULL;
    LvcppLabel* label_current=NULL;
    LvcppLabel* label_total=NULL;
    LvcppSlider* bar_progress=NULL;
    LvcppButton* btn_play=NULL;
    LvcppButton* btn_go_after=NULL;
    LvcppButton* btn_go_before=NULL;
    LvcppButton* btn_backlight=NULL;
    LvcppSlider* bar_backligh=NULL;
    LvcppButton* btn_volume=NULL;
    LvcppSlider* bar_volume=NULL;
    LvcppLabel* label_music=NULL;
    LvcppLabel* label_musicS=NULL;
    LvcppSlider* bar_musicS=NULL;
    LvcppLabel* label_musicR=NULL;

	char* play_url=NULL;
	int play_type = 0;
	int play_next_type = 0;
	player_ui_t *PlayerUi=NULL;
    bool IconStatus =true;
    bool LightStatus =true;
    bool VolStatus =true;
	bool PlayEnd =false;
    int play_state=0;
    int dursec=1;
    int cursec=0;
	int disIndex=0;
	int play_index=0;
	int play_total=0;
    int downNumIcon=0;
    int downNumLight=0;
    int downNumVol=0;
    int ring_status=1;
    int bl_val=5;
    int bl_total=10;
    int volume_val=0;

	bool quit_flag =false;

	player_t* video_player = nullptr;

	player_t* audio_player = nullptr;

	void video_play_scan(int disktype,char* curPath);
	static void main_event_handler(lv_event_t *event);
	void playIcon_creat(void);
	void playIcon_del(void);
    static void playIcon_event_handler(lv_event_t *event);
	void play_time_update(void);
    void playIcon_show(void);
    void playIcon_hid(void);
    void lightIcon_show(void);
    void lightIcon_hid(void);
    void volIcon_show(void);
    void volIcon_hid(void);
	void play_prve_next_file(bool status);
};

#endif // VIDEOPLAY_H
