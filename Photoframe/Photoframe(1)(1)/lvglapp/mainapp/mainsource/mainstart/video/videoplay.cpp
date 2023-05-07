#include "videoplay.h"
#include "videomain.h"
#include "mainstart/include/ui_config.h"
#include "mainstart/include/configCustom.h"
#include "mainstart/customer_config.h"
#include "mainstart/include/str_config.h"
#include "appmsg/appmsg.h"
#include  "../mainappstart.h"
#ifdef _UCHIP_T113
#include "common/common.h"
#endif
VideoPlay* VPlayOpt = nullptr;
int list_update_flag=0;
static pthread_mutex_t g_scanLock;

static int play_finish = 0;
static media_file_list_t *media_file_list = NULL;


void VideoPlay::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    HEAD_RETURN_PNG=(void*)parse_image_from_file(HEAD_RETURN_PNG_PATH);
    HEAD_RETURN_SEL_PNG=(void*)parse_image_from_file(HEAD_RETURN_SEL_PNG_PATH);
    VIDEO_UNPLAYING_PNG=(void*)parse_image_from_file(VIDEO_UNPLAYING_PNG_PATH);
    VIDEO_PLAYING_PNG=(void*)parse_image_from_file(VIDEO_PLAYING_PNG_PATH);
    VIDEO_UNSTOP_PNG=(void*)parse_image_from_file(VIDEO_UNSTOP_PNG_PATH);
    VIDEO_STOP_PNG=(void*)parse_image_from_file(VIDEO_STOP_PNG_PATH);
    VIDEO_UNNEXT_PNG=(void*)parse_image_from_file(VIDEO_UNNEXT_PNG_PATH);
    VIDEO_NEXT_PNG=(void*)parse_image_from_file(VIDEO_NEXT_PNG_PATH);
    VIDEO_UNPREV_PNG=(void*)parse_image_from_file(VIDEO_UNPREV_PNG_PATH);
    VIDEO_PREV_PNG=(void*)parse_image_from_file(VIDEO_PREV_PNG_PATH);
    VIDEO_LIGHT_PNG=(void*)parse_image_from_file(VIDEO_LIGHT_PNG_PATH);
    VIDEO_VOLMAX_PNG=(void*)parse_image_from_file(VIDEO_VOLMAX_PNG_PATH);
    VIDEO_VOLMID_PNG=(void*)parse_image_from_file(VIDEO_VOLMID_PNG_PATH);
    VIDEO_VOLMIN_PNG=(void*)parse_image_from_file(VIDEO_VOLMIN_PNG_PATH);
    VIDEO_MUSICS_PNG=(void*)parse_image_from_file(VIDEO_MUSICS_PNG_PATH);
    VIDEO_MUSICSOFF_PNG=(void*)parse_image_from_file(VIDEO_MUSICSOFF_PNG_PATH);
    VIDEO_RING_PNG=(void*)parse_image_from_file(VIDEO_RING_PNG_PATH);
    VIDEO_RINGOFF_PNG=(void*)parse_image_from_file(VIDEO_RINGOFF_PNG_PATH);
#endif
}
void VideoPlay::ui_image_free(void)
{
#ifdef IMAGE_DECODE
    free_image(HEAD_RETURN_PNG);
    free_image(HEAD_RETURN_SEL_PNG);
    free_image(VIDEO_UNPLAYING_PNG);
    free_image(VIDEO_PLAYING_PNG);
    free_image(VIDEO_UNSTOP_PNG);
    free_image(VIDEO_STOP_PNG);
    free_image(VIDEO_UNNEXT_PNG);
    free_image(VIDEO_NEXT_PNG);
    free_image(VIDEO_UNPREV_PNG);
    free_image(VIDEO_PREV_PNG);
    free_image(VIDEO_LIGHT_PNG);
    free_image(VIDEO_VOLMAX_PNG);
    free_image(VIDEO_VOLMID_PNG);
    free_image(VIDEO_VOLMIN_PNG);
    free_image(VIDEO_MUSICS_PNG);
    free_image(VIDEO_MUSICSOFF_PNG);
    free_image(VIDEO_RING_PNG);
    free_image(VIDEO_RINGOFF_PNG);
#endif

}

VideoPlay::VideoPlay(player_ui_t *playerUi)
{
	VPlayOpt = this;
    ui_image_decode();
    vpscreen = new LvcppScreen(lv_layer_top());
    vpscreen->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    vpscreen->set_main_bg_color(lv_color_black(),LV_OPA_0);
    vpscreen->add_event_cb(main_event_handler,LV_EVENT_PRESSED,this);
    vpscreen->add_event_cb(main_event_handler,LV_EVENT_RELEASED,this);
    vpscreen->add_event_cb(main_event_handler,LV_EVENT_PRESSING,this);
    vp_parent = vpscreen->myobj;       
}

VideoPlay::~VideoPlay()
{
	playIcon_del();
	if(media_file_list!=NULL)
	{
		media_unload_file(media_file_list);
		media_file_list=NULL;
	}
	ui_image_free();
	if(play_type==RAT_MEDIA_TYPE_PIC)
	{
		image_exit();
	}
	else if(play_type==RAT_MEDIA_TYPE_AUDIO)
	{
		media_func_unregister(MUSIC_SCENE,0);
	}
	else if(play_type==RAT_MEDIA_TYPE_VIDEO)
	{
		media_func_unregister(MOVIE_SCENE,0);
	}
}

void VideoPlay::init_parament(int disktype, char* file)
{
	char *fileBuff=NULL;
	char buff[512]={0};
	int val =0;
	
    video_play_scan(disktype, file);
	disIndex = disktype;
	read_int_type_param(PUBLIC_SCENE, VOLUME, (int *)&val);
	volume_val =(int)(val/4);
#ifdef _UCHIP_T113
    /*tplayer_play_url(PlayerUi->tplayer, file);
	usleep(30000);
    tplayer_set_displayrect(PlayerUi->tplayer, 0, 0, LV_VER_RES_MAX, LV_HOR_RES_MAX);
	tplayer_play(PlayerUi->tplayer);
	play_state =1;*/
#endif
	playIcon_creat();
	if(play_type==RAT_MEDIA_TYPE_PIC)
	{
		image_init();
		image_disp_cache_enable(1);
		image_disp_rect_set(IMAGE_FULL_SCREEN);
		image_show(play_url, IMAGE_FULL_SCREEN_SCLAER);
		image_disp_cache_enable(0);
	}
	else if(play_type==RAT_MEDIA_TYPE_AUDIO)
	{
		media_func_register(MUSIC_SCENE,media_player_ui_callback);
		usleep(30000);
		PlayerUi = media_get_player_data();
		tplayer_play_url(PlayerUi->tplayer, play_url);
		tplayer_play(PlayerUi->tplayer);
	}
	else if(play_type==RAT_MEDIA_TYPE_VIDEO)
	{
		media_func_register(MOVIE_SCENE,media_player_ui_callback);
		PlayerUi = media_get_player_data();
		tplayer_set_rotate(PlayerUi->tplayer, TPLAYER_VIDEO_ROTATE_DEGREE_90);
		usleep(30000);
		tplayer_play_url(PlayerUi->tplayer, play_url);
	    tplayer_set_displayrect(PlayerUi->tplayer, 0, 0, LV_VER_RES_MAX, LV_HOR_RES_MAX);
		tplayer_play(PlayerUi->tplayer);
	}
	play_state = 1;
	btn_play->set_main_bg_img_src(VIDEO_STOP_PNG);
	if(vplayer_timer == NULL)
    { 
        vplayer_timer = startTimer(200, this);
    }
}

void VideoPlay::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    static int timecnt = 0;

	if(play_type==RAT_MEDIA_TYPE_PIC && play_state)
	{
		timecnt++;
		if(timecnt>25)
		{
			play_prve_next_file(true);
			timecnt = 0;
		}
	}
	else
	{
		timecnt = 0;
	}
	
    if(downNumIcon >15)
    {
        downNumIcon =0;
        playIcon_hid();
    }
    downNumIcon ++;

    if(downNumLight >15)
    {
        downNumLight =0;
        lightIcon_hid();
    }
    downNumLight ++;

    if(downNumVol >15)
    {
        downNumVol =0;
        volIcon_hid();
    }
    downNumVol ++;
    
}

void VideoPlay::media_player_ui_callback(void *ui_player, media_event_t event, void *param)
{        
	/*player_ui_t * player_ui = (player_ui_t *)ui_player;
	if (player_ui == NULL) 
	{                
		return;        
	}  */
	switch (event) 
	{                
		case MEDIA_IDLE_EVENT:
			if (tplayer_get_status(VPlayOpt->PlayerUi->tplayer) == PLAY_STATUS)
            {
				tplayer_get_current_pos(VPlayOpt->PlayerUi->tplayer, &VPlayOpt->cursec);
			    tplayer_get_duration(VPlayOpt->PlayerUi->tplayer, &VPlayOpt->dursec);
				VPlayOpt->play_time_update();
			}
			break;                
		case MEDIA_UPDATE_LIST_EVENT:
			break;                
		case MEDIA_PLAY_EVENT: 
			break;
		case MEDIA_PAUSE_EVENT:
			break;                
		case MEDIA_DOWNLOAD_EVENT:
			break;                
		case MEDIA_LOAD_LRC_EVENT:
			break;                
		case MEDIA_LIST_LOOP_EVENT:
			break;                
		case MEDIA_PLAY_COMPLETE_EVENT:
			media_ui_send_event(MEDIA_IDLE_EVENT, NULL, 0);
			VPlayOpt->play_prve_next_file(true);
			break;                
		default:                        
			break;       
	}
}

static int videoplay_userInfo(int userNum,char *userID)
{
#ifdef _UCHIP_T113
    char nameInfo[512]={0};
    char *token = NULL;
    char line[]={";"};
    int num =0;

    if(read_string_type_param(PUBLIC_SCENE,USERINFO,nameInfo,sizeof(nameInfo))==0)
    {
        for(token = strtok(nameInfo, line); token != NULL; token = strtok(NULL, line))
        {
            if(userNum ==num)
            {
                strcpy(userID,token);
                return 0;
            }
            num ++;
        }
    }
    return -1;
#endif
}

void VideoPlay::video_play_scan(int disktype, char* CurPatch)
{
    char MountPoint[128]={0};
    char userPatch[64]={0};

	if(media_file_list!=NULL)
	{
		media_unload_file(media_file_list);
		media_file_list=NULL;
	}

	if (NULL == media_file_list)
	{
        if(disktype ==0)
        {
            strcpy(MountPoint,"/mnt");
        }
        else if(disktype ==1)
        {
            strcpy(MountPoint,"/mnt/UDISK");
        }
        else if(disktype ==2)
        {
            strcpy(MountPoint,"/mnt/SDCARD");
        }
        else if(disktype ==3)
        {
            strcpy(MountPoint,"/mnt/exUDISK");
        }
        else
        {
            if(videoplay_userInfo((disktype -VIDEOLIST_MAX),userPatch)<0)
                return ;
            else
                sprintf(MountPoint,"/mnt/UDISK/%s",userPatch);
        }
        media_file_list = media_load_file(RAT_MEDIA_TYPE_VIDEO, MountPoint);
        if (NULL == media_file_list)
        {
            LV_LOG_USER("%s don't find video list\n",MountPoint);
            play_total = 0;
            play_index =0;
            play_url = NULL;
        }
        else
        {
            play_total = media_file_list->total_num;
            play_index =  media_get_index_from_path(media_file_list,CurPatch);
			play_url = media_get_file_path(media_file_list,play_index);
			play_type = media_get_file_type(media_file_list,play_index);
			LV_LOG_USER("----play_type = %d ---- play_url: %s  ----",play_type,play_url);
        }
    }
}

void VideoPlay::main_event_handler(lv_event_t *event)
{
    VideoPlay* opt = (VideoPlay*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    char *playUrl =NULL;

    if(target == opt->vpscreen->myobj)
    {
        switch(event->code)
        {
            case LV_EVENT_RELEASED:
                opt->playIcon_show();
            break;
	        case LV_EVENT_PRESSING:
	        break;
            default:
                break;
        }
    }
    else if(target==opt->IconReturn->myobj)
    {
        if(event->code == LV_EVENT_PRESSED)
        {
            opt->IconReturn->set_main_bg_img_src(opt->HEAD_RETURN_SEL_PNG);
        }
        else if(event->code == LV_EVENT_RELEASED)
        {
        	if(media_file_list !=NULL)
        	{
	            playUrl = media_get_file_path(media_file_list,opt->play_index);
				if(playUrl !=NULL)
				{
	            	videoMain::exitVideoPlay(opt->disIndex,playUrl);
	        	}
        	}
    	}
	}
}
void VideoPlay::playIcon_creat(void)
{
	char *playUrl=NULL;
	char *fileBuff=NULL;
	char buff[512]={0};

	memset(buff,0,sizeof(buff));
	if(media_file_list !=NULL)
	{
		playUrl = media_get_file_path(media_file_list,play_index);
		if(playUrl !=NULL)
		{
	    	fileBuff = media_get_path_to_name(playUrl);
			memset(buff,0,sizeof(buff));
			if(fileBuff !=NULL)
				sprintf(buff,"%s",fileBuff);
		}
	}

    IconReturn = new LvcppButton(vp_parent);
    IconReturn->set_size(66,66);
    IconReturn->align(LV_ALIGN_TOP_LEFT,60,8);
    IconReturn->set_main_bg_opa(LV_OPA_0);
    IconReturn->set_main_bg_img_src(HEAD_RETURN_PNG);
    IconReturn->add_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
    IconReturn->add_event_cb(main_event_handler,LV_EVENT_PRESSED,this);
    IconReturn->add_event_cb(main_event_handler,LV_EVENT_RELEASED,this);

    label_title = new LvcppLabel(vp_parent);
    label_title->set_size(500,40);
    label_title->align(LV_ALIGN_TOP_LEFT,150,20);
    label_title->set_txt(buff);
    label_title->txt_color(lv_color_white(),LV_PART_MAIN);
    label_title->txt_font_size(36,FT_FONT_STYLE_NORMAL);

    memset(buff,0,sizeof(buff));
    labelIcon = new LvcppLabel(vp_parent);
    labelIcon->set_size(1280,100);
    labelIcon->align(LV_ALIGN_BOTTOM_MID,0,-100);
    labelIcon->set_main_bg_color(lv_color_black(),LV_OPA_50);
    labelIcon->set_txt(buff);

	memset(buff,0,sizeof(buff));
    label_current = new LvcppLabel(labelIcon->myobj);
    label_current->set_size(110,30);
    label_current->align(LV_ALIGN_TOP_LEFT,5,35);
    label_current->txt_font_size(26,FT_FONT_STYLE_NORMAL);
    label_current->txt_align(LV_TEXT_ALIGN_CENTER);
    label_current->txt_color(lv_color_white(),LV_PART_MAIN);
    label_current->set_txt(buff);

	memset(buff,0,sizeof(buff));
    label_total = new LvcppLabel(labelIcon->myobj);
    label_total->set_size(110,30);
    label_total->set_main_pad_all(0);
    label_total->align(LV_ALIGN_TOP_RIGHT,-5,35);
    label_total->txt_font_size(26,0);
    label_total->txt_align(LV_TEXT_ALIGN_CENTER);
    label_total->txt_color(lv_color_white(),LV_PART_MAIN);
    label_total->set_txt(buff);

    bar_progress =new LvcppSlider(labelIcon->myobj);
    bar_progress->set_size(1040,10);
    bar_progress->align(LV_ALIGN_TOP_LEFT,120,45);
    bar_progress->set_mode(LV_BAR_MODE_NORMAL);
    bar_progress->set_main_pad_all(0);
    bar_progress->set_style_radius(0, LV_PART_INDICATOR);
    bar_progress->set_style_pad_all(0,0);
    bar_progress->set_main_border_width(0);
    bar_progress->set_range(0, dursec);
    bar_progress->set_style_bg_color(MENU_BTN_COLOR,LV_OPA_100,LV_PART_MAIN);
    bar_progress->set_style_bg_color(TABLE_SETTING_COLOR,LV_OPA_100,LV_PART_INDICATOR);
    bar_progress->set_style_bg_color(lv_color_white(),LV_OPA_100,LV_PART_KNOB);
    bar_progress->set_left_value(0, LV_ANIM_OFF);
    bar_progress->set_value(cursec, LV_ANIM_OFF);
	bar_progress->add_event_cb(playIcon_event_handler,LV_EVENT_VALUE_CHANGED,this);

    btn_play = new LvcppButton(vp_parent);
    btn_play->set_size(80,80);
    btn_play->align(LV_ALIGN_CENTER,0,0);
    btn_play->set_main_pad_all(0);
    btn_play->set_main_bg_opa(LV_OPA_0);
    btn_play->set_main_bg_img_src(VIDEO_STOP_PNG);
    btn_play->add_event_cb(playIcon_event_handler,LV_EVENT_PRESSED,this);
    btn_play->add_event_cb(playIcon_event_handler,LV_EVENT_RELEASED,this);

    btn_go_before = new LvcppButton(vp_parent);
    btn_go_before->set_size(66,66);
    btn_go_before->set_main_pad_all(0);
    btn_go_before->set_main_bg_opa(LV_OPA_0);
    btn_go_before->align(LV_ALIGN_CENTER,-200,0);
    btn_go_before->set_main_bg_img_src(VIDEO_PREV_PNG);
    btn_go_before->add_event_cb(playIcon_event_handler,LV_EVENT_PRESSED,this);
    btn_go_before->add_event_cb(playIcon_event_handler,LV_EVENT_RELEASED,this);

    btn_go_after = new LvcppButton(vp_parent);
    btn_go_after->set_size(66,66);
    btn_go_after->set_main_pad_all(0);
    btn_go_after->set_main_bg_opa(LV_OPA_0);
    btn_go_after->align(LV_ALIGN_CENTER,200,0);
    btn_go_after->set_main_bg_img_src(VIDEO_NEXT_PNG);
    btn_go_after->add_event_cb(playIcon_event_handler,LV_EVENT_PRESSED,this);
    btn_go_after->add_event_cb(playIcon_event_handler,LV_EVENT_RELEASED,this);

    btn_backlight = new LvcppButton(vp_parent);
    btn_backlight->set_size(100,100);
    btn_backlight->set_main_pad_all(0);
    btn_backlight->set_main_bg_color(lv_color_black(),LV_OPA_50);
    btn_backlight->align(LV_ALIGN_CENTER,0,0);
    btn_backlight->set_main_bg_img_src(VIDEO_LIGHT_PNG);
    btn_backlight->clear_flag(LV_OBJ_FLAG_CLICKABLE);

    bar_backligh =new LvcppSlider(btn_backlight->myobj);
    bar_backligh->set_size(90,8);
    bar_backligh->align(LV_ALIGN_BOTTOM_MID,0,-10);
    bar_backligh->set_mode(LV_BAR_MODE_NORMAL);
    bar_backligh->set_main_pad_all(0);
    bar_backligh->set_style_radius(0, LV_PART_INDICATOR);
    bar_backligh->set_style_pad_all(0,0);
    bar_backligh->set_main_border_width(0);
    bar_backligh->set_range(0, bl_total);
    bar_backligh->set_style_bg_color(lv_color_black(),LV_OPA_100,LV_PART_MAIN);
    bar_backligh->set_style_bg_color(MENU_BTN_COLOR,LV_OPA_100,LV_PART_INDICATOR);
    bar_backligh->set_style_bg_color(MENU_BTN_COLOR,LV_OPA_0,LV_PART_KNOB);
    bar_backligh->set_left_value(0, LV_ANIM_OFF);
    bar_backligh->set_value(bl_val, LV_ANIM_OFF);
    bar_backligh->clear_flag(LV_OBJ_FLAG_CLICKABLE);

    btn_volume = new LvcppButton(vp_parent);
    btn_volume->set_size(100,100);
    btn_volume->set_main_pad_all(0);
    btn_volume->set_main_bg_color(lv_color_black(),LV_OPA_50);
    btn_volume->align(LV_ALIGN_CENTER,0,0);
    btn_volume->set_main_bg_img_src(VIDEO_VOLMAX_PNG);
    btn_volume->clear_flag(LV_OBJ_FLAG_CLICKABLE);

    bar_volume =new LvcppSlider(btn_volume->myobj);
    bar_volume->set_size(90,8);
    bar_volume->align(LV_ALIGN_BOTTOM_MID,0,-10);
    bar_volume->set_mode(LV_BAR_MODE_NORMAL);
    bar_volume->set_main_pad_all(0);
    bar_volume->set_style_radius(0, LV_PART_INDICATOR);
    bar_volume->set_style_pad_all(0,0);
    bar_volume->set_main_border_width(0);
    bar_volume->set_range(0, VOL_MAX);
    bar_volume->set_style_bg_color(lv_color_black(),LV_OPA_100,LV_PART_MAIN);
    bar_volume->set_style_bg_color(MENU_BTN_COLOR,LV_OPA_100,LV_PART_INDICATOR);
    bar_volume->set_style_bg_color(MENU_BTN_COLOR,LV_OPA_0,LV_PART_KNOB);
    bar_volume->set_left_value(0, LV_ANIM_OFF);
    bar_volume->set_value(volume_val, LV_ANIM_OFF);
    bar_volume->clear_flag(LV_OBJ_FLAG_CLICKABLE);

    memset(buff,0,sizeof(buff));
    label_music = new LvcppLabel(vp_parent);
    label_music->set_size(80,205);
    label_music->align(LV_ALIGN_TOP_RIGHT,0,(SCREEN_VER_SIZE-180)/2);
    label_music->set_main_bg_color(lv_color_black(),LV_OPA_0);
    label_music->set_txt(buff);
    label_music->add_flag(LV_OBJ_FLAG_CLICKABLE);

    label_musicR = new LvcppLabel(label_music->myobj);
    label_musicR->set_size(60,60);
    label_musicR->align(LV_ALIGN_TOP_MID,0,0);
    label_musicR->set_main_radius(5);
    label_musicR->set_main_bg_color(lv_color_white(),LV_OPA_90);
    label_musicR->set_main_bg_img_src(VIDEO_RING_PNG);
    label_musicR->set_txt(buff);
    label_musicR->add_flag(LV_OBJ_FLAG_CLICKABLE);
    label_musicR->add_event_cb(playIcon_event_handler,LV_EVENT_CLICKED,this);

    label_musicS = new LvcppLabel(label_music->myobj);
    label_musicS->set_size(60,140);
    label_musicS->align(LV_ALIGN_BOTTOM_MID,0,0);
    label_musicS->set_main_radius(5);
    label_musicS->set_main_bg_color(lv_color_white(),LV_OPA_90);
    label_musicS->set_main_bg_img_src(VIDEO_MUSICS_PNG);
    label_musicS->set_txt(buff);
    label_musicS->add_flag(LV_OBJ_FLAG_CLICKABLE);

    bar_musicS =new LvcppSlider(label_musicS->myobj);
    bar_musicS->set_size(2,70);
    bar_musicS->align(LV_ALIGN_TOP_MID,0,25);
    bar_musicS->set_mode(LV_BAR_MODE_NORMAL);
    bar_musicS->set_main_pad_all(0);
    bar_musicS->set_style_radius(0, LV_PART_INDICATOR);
    bar_musicS->set_style_pad_all(0,0);
    bar_musicS->set_main_border_width(0);
    bar_musicS->set_range(0, VOL_MAX);
    bar_musicS->set_style_bg_color(GAS_BTN_COLOR,LV_OPA_100,LV_PART_MAIN);
    bar_musicS->set_style_bg_color(lv_color_black(),LV_OPA_100,LV_PART_INDICATOR);
    bar_musicS->set_style_bg_color(lv_color_black(),LV_OPA_100,LV_PART_KNOB);
    bar_musicS->set_left_value(0, LV_ANIM_OFF);
    bar_musicS->set_value(volume_val, LV_ANIM_OFF);
    bar_musicS->add_flag(LV_OBJ_FLAG_CLICKABLE);
    bar_musicS->add_event_cb(playIcon_event_handler,LV_EVENT_VALUE_CHANGED,this);
	bar_musicS->add_event_cb(playIcon_event_handler,LV_EVENT_CLICKED,this);
	
    playIcon_hid();
    lightIcon_hid();
    volIcon_hid();
}

void VideoPlay::playIcon_del(void)
{
    if(bar_backligh != NULL)
    {
        delete bar_backligh;
        bar_backligh =NULL;
    }
    if(btn_backlight != NULL)
    {
        delete btn_backlight;
        btn_backlight =NULL;
    }
    if(bar_volume != NULL)
    {
        delete bar_volume;
        bar_volume =NULL;
    }
    if(label_musicR != NULL)
    {
        delete label_musicR;
        label_musicR =NULL;
    }
    if(bar_musicS != NULL)
    {
        delete bar_musicS;
        bar_musicS =NULL;
    }
    if(label_musicS != NULL)
    {
        delete label_musicS;
        label_musicS =NULL;
    }
    if(label_music != NULL)
    {
        delete label_music;
        label_music =NULL;
    }
    if(btn_volume != NULL)
    {
        delete btn_volume;
        btn_volume =NULL;
    }
    if(btn_go_before != NULL)
    {
        delete btn_go_before;
        btn_go_before =NULL;
    }
    if(btn_go_after != NULL)
    {
        delete btn_go_after;
        btn_go_after =NULL;
    }
    if(btn_play != NULL)
    {
        delete btn_play;
        btn_play =NULL;
    }
    if(label_total != NULL)
    {
        delete label_total;
        label_total =NULL;
    }
    if(label_current != NULL)
    {
        delete label_current;
        label_current =NULL;
    }
    if(bar_progress != NULL)
    {
        delete bar_progress;
        bar_progress =NULL;
    }

    if(label_title != NULL)
    {
        delete label_title;
        label_title =NULL;
    }

    if(labelIcon != NULL)
    {
        delete labelIcon;
        labelIcon =NULL;
    }
    if(IconReturn != NULL)
    {
        delete IconReturn;
        IconReturn =NULL;
    }
    if(vpscreen !=NULL)
    {
        delete vpscreen;
        vpscreen =NULL;
    }
}

void VideoPlay::playIcon_event_handler(lv_event_t *event)
{
    VideoPlay* opt = (VideoPlay*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
	int value =0;

    if((opt->btn_play !=NULL)&&(target==opt->btn_play->myobj))
    {
        if(event->code == LV_EVENT_PRESSED)
        {
            if(opt->play_state)
            {
                opt->btn_play->set_main_bg_img_src(opt->VIDEO_UNSTOP_PNG);
            }
            else
            {
                opt->btn_play->set_main_bg_img_src(opt->VIDEO_UNPLAYING_PNG);
            }
        }
        else if(event->code == LV_EVENT_RELEASED)
        {
            if(!opt->play_state)
            {
                opt->play_state =1;
                opt->btn_play->set_main_bg_img_src(opt->VIDEO_STOP_PNG);
                tplayer_play(opt->PlayerUi->tplayer);
            }
            else
            {
                opt->play_state =0;
                opt->btn_play->set_main_bg_img_src(opt->VIDEO_PLAYING_PNG);
                tplayer_pause(opt->PlayerUi->tplayer);
            }
        }
        opt->playIcon_show();
    }
    else if((opt->btn_go_before !=NULL)&&(target==opt->btn_go_before->myobj))
    {
        if(event->code == LV_EVENT_PRESSED)
        {
            opt->btn_go_before->set_main_bg_img_src(opt->VIDEO_UNPREV_PNG);
        }
        else if(event->code == LV_EVENT_RELEASED)
        {
            opt->btn_go_before->set_main_bg_img_src(opt->VIDEO_PREV_PNG);
			opt->play_prve_next_file(false);
        }
        opt->playIcon_show();
    }
    else if((opt->btn_go_after !=NULL)&&(target==opt->btn_go_after->myobj))
    {
        if(event->code == LV_EVENT_PRESSED)
        {
            opt->btn_go_after->set_main_bg_img_src(opt->VIDEO_UNNEXT_PNG);
        }
        else if(event->code == LV_EVENT_RELEASED)
        {
            opt->btn_go_after->set_main_bg_img_src(opt->VIDEO_NEXT_PNG);
			opt->play_prve_next_file(true);
        }
        opt->playIcon_show();
    }
    else if((opt->label_musicR!=NULL)&&(target==opt->label_musicR->myobj))
    {
        if(event->code == LV_EVENT_CLICKED)
        {
            if(opt->ring_status)
            {
                opt->ring_status =0;
                opt->label_musicR->set_main_bg_img_src(opt->VIDEO_RINGOFF_PNG);
            }
            else
            {
                opt->ring_status =1;
                opt->label_musicR->set_main_bg_img_src(opt->VIDEO_RING_PNG);
            }
            opt->volIcon_show();
        }
    }
    else if((opt->bar_musicS!=NULL)&&(target==opt->bar_musicS->myobj))
    {
        if(event->code == LV_EVENT_VALUE_CHANGED)
        {
            opt->volume_val = opt->bar_musicS->get_value();
            if(opt->bar_volume!=NULL)
                opt->bar_volume->set_value(opt->volume_val, LV_ANIM_OFF);
            if(opt->volume_val <=0)
            {
                opt->label_musicS->set_main_bg_img_src(opt->VIDEO_MUSICSOFF_PNG);
                if(opt->btn_volume!=NULL)
                    opt->btn_volume->set_main_bg_img_src(opt->VIDEO_VOLMIN_PNG);
            }
            else
            {
                opt->label_musicS->set_main_bg_img_src(opt->VIDEO_MUSICS_PNG);
                if(opt->volume_val <6)
                {
                    if(opt->btn_volume!=NULL)
                        opt->btn_volume->set_main_bg_img_src(opt->VIDEO_VOLMID_PNG);
                }
                else
                {
                    if(opt->btn_volume!=NULL)
                        opt->btn_volume->set_main_bg_img_src(opt->VIDEO_VOLMAX_PNG);
                }
            }
			tplayer_volume(opt->PlayerUi->tplayer,opt->volume_val);
        }
        opt->volIcon_show();
    }
    else if((opt->bar_progress!=NULL)&&(target==opt->bar_progress->myobj))
    {
    	value =(int)opt->bar_progress->get_value();
		opt->playIcon_show();
		if(event->code == LV_EVENT_VALUE_CHANGED)
        {
			LV_LOG_USER("LV_EVENT_VALUE_CHANGED:%d",value);
			tplayer_seekto(opt->PlayerUi->tplayer,value);
			usleep(30000);
        }
    }
	else if((opt->bar_musicS!=NULL)&&(target==opt->bar_musicS->myobj))
    {	
		opt->volIcon_show();
        if((event->code == LV_EVENT_VALUE_CHANGED)||(event->code == LV_EVENT_CLICKED))
        {
        	opt->volume_val =(int)opt->bar_musicS->get_value();
        	value=(int)(opt->volume_val*4);
			tplayer_volume(opt->PlayerUi->tplayer,value);
			write_int_type_param(PUBLIC_SCENE, VOLUME,value);
        }
	}
}

void VideoPlay::play_time_update(void)
{
    char durstr[16]={0};
    char curstr[16]={0};
	
    if((dursec/3600)>0)
    {
        sprintf(durstr,"%d:%02d:%02d",dursec/3600,(dursec-3600)/60,(dursec-3600)%60);
    }
    else
    {
        sprintf(durstr,"%02d:%02d",dursec/60,dursec%60);
    }
	if((cursec/3600)>0)
    {
        sprintf(curstr,"%d:%02d:%02d",cursec/3600,(cursec-3600)/60,(cursec-3600)%60);
    }
    else
    {
        sprintf(curstr,"%02d:%02d",cursec/60,cursec%60);
    }
    if(label_total!=NULL)
    {
        label_total->set_txt(durstr);
    }
    if(label_current!=NULL)
    {
        label_current->set_txt(curstr);
    }
    if(bar_progress!=NULL)
    {
        if(dursec==0)
        {
            return;
        }
        bar_progress->set_range(0, dursec);
        bar_progress->set_value(cursec, LV_ANIM_OFF);
    }
}

void VideoPlay::playIcon_show(void)
{
     downNumIcon =0;
    if(IconStatus ==true)
        return;
    IconStatus =true;
    if(play_state)
    {
        btn_play->set_main_bg_img_src(VIDEO_STOP_PNG);
    }
    else
    {
        btn_play->set_main_bg_img_src(VIDEO_PLAYING_PNG);
    }
    IconReturn->show(true);
    label_title->show(true);
    labelIcon->show(true);
    btn_play->show(true);
    btn_go_after->show(true);
    btn_go_before->show(true);
}

void VideoPlay::playIcon_hid(void)
{
    if(IconStatus ==false)
        return;
    IconStatus =false;
    IconReturn->show(false);
    label_title->show(false);
    labelIcon->show(false);
    btn_play->show(false);
    btn_go_after->show(false);
    btn_go_before->show(false);
}

void VideoPlay::lightIcon_show(void)
{
    downNumLight =0;
    if(LightStatus ==true)
        return;
    LightStatus =true;
    btn_backlight->show(true);
}

void VideoPlay::lightIcon_hid(void)
{
    if(LightStatus ==false)
        return;
    LightStatus =false;
    btn_backlight->show(false);
}

void VideoPlay::volIcon_show(void)
{
    downNumVol =0;
    if(VolStatus ==true)
        return;
    VolStatus =true;
    btn_volume->show(true);
    label_music->show(true);
}

void VideoPlay::volIcon_hid(void)
{
    if(VolStatus ==false)
        return;
    VolStatus =false;
    btn_volume->show(false);
    label_music->show(false);
}

void VideoPlay::play_prve_next_file(bool status)
{
    if(status ==true)
    {
		play_index++;
		if(play_index >=play_total)
		{
			play_index = 0;
		}
	}
	else
	{
		play_index--;
		if(play_index<0)
		{
			play_index = play_total-1;
		}
	}
	if(media_file_list !=NULL)
	{
		play_url = media_get_file_path(media_file_list,play_index);
		play_next_type = media_get_file_type(media_file_list,play_index); 
	}
	if(play_next_type != play_type)
	{
		if(play_type==RAT_MEDIA_TYPE_PIC)
		{
			image_exit();
		}
		else if(play_type==RAT_MEDIA_TYPE_AUDIO)
		{
			media_func_unregister(MUSIC_SCENE,0);
			sleep(2);
		}
		else if(play_type==RAT_MEDIA_TYPE_VIDEO)
		{
			media_func_unregister(MOVIE_SCENE,0);
			sleep(2);
		}
		play_type = play_next_type;
		if(play_url !=NULL)
		{
			if(play_next_type==RAT_MEDIA_TYPE_PIC)
			{
				image_init();
				image_disp_cache_enable(1);
				image_disp_rect_set(IMAGE_FULL_SCREEN);
				image_show(play_url, IMAGE_FULL_SCREEN_SCLAER);
				image_disp_cache_enable(0);
			}
			else if(play_next_type==RAT_MEDIA_TYPE_AUDIO)
			{
				media_func_register(MUSIC_SCENE,media_player_ui_callback);
				usleep(30000);
				PlayerUi = media_get_player_data();
				tplayer_play_url(PlayerUi->tplayer, play_url);
				tplayer_play(PlayerUi->tplayer);
			}
			else if(play_next_type==RAT_MEDIA_TYPE_VIDEO)
			{
				media_func_register(MOVIE_SCENE,media_player_ui_callback);
				PlayerUi = media_get_player_data();
				usleep(30000);
				tplayer_set_rotate(PlayerUi->tplayer, TPLAYER_VIDEO_ROTATE_DEGREE_90);
				tplayer_play_url(PlayerUi->tplayer, play_url);
				tplayer_set_displayrect(PlayerUi->tplayer, 0, 0, LV_VER_RES_MAX, LV_HOR_RES_MAX);
				tplayer_play(PlayerUi->tplayer);
			}
			play_state = 1;
			btn_play->set_main_bg_img_src(VIDEO_STOP_PNG);
		}
	}
	else
	{
		if(play_url !=NULL)
		{
			if(play_next_type==RAT_MEDIA_TYPE_PIC)
			{
				image_disp_cache_enable(1);
				image_disp_rect_set(IMAGE_FULL_SCREEN);
				image_show(play_url, IMAGE_FULL_SCREEN_SCLAER);
				image_disp_cache_enable(0);
			}
			else if(play_next_type==RAT_MEDIA_TYPE_AUDIO)
			{
				tplayer_stop(PlayerUi->tplayer);
				usleep(30000);
				PlayerUi = media_get_player_data();
				tplayer_play_url(PlayerUi->tplayer, play_url);
				tplayer_play(PlayerUi->tplayer);
			}
			else if(play_next_type==RAT_MEDIA_TYPE_VIDEO)
			{
				tplayer_stop(PlayerUi->tplayer);
				usleep(30000);
				tplayer_play_url(PlayerUi->tplayer, play_url);
				tplayer_set_displayrect(PlayerUi->tplayer, 0, 0, LV_VER_RES_MAX, LV_HOR_RES_MAX);
				tplayer_play(PlayerUi->tplayer);
			}
			play_state = 1;
			btn_play->set_main_bg_img_src(VIDEO_STOP_PNG);
		}
	}
#ifdef _UCHIP_T113  


#endif
}

