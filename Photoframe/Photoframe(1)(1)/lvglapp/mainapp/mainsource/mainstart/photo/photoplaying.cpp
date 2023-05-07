#include  "../mainappstart.h"
#include "photomain.h"
#include "photoplaying.h"
#include "mainstart/scene_list/frame_list_icon.h"
#include  "lvgl/src/extra/lv_extra.h"
#include  "mainstart/include/ui_config.h"
#include  "mainstart/include/str_config.h"
#include  "common/common.h"

#define IMAGE_PLAY_TIME_STEP 10  //图片播放检测间隔，单位: ms

static const void *effectName[16]={STR_NORMAL,STR_RANDOM,STR_FADE,STR_MOSIAC,
									STR_SLIDE_UP,STR_SLIDE_DOWN,STR_SLIDE_LEFT,
									STR_SLIDE_RIGHT,STR_STRETCH_UP,STR_STRETCH_DOWN,
									STR_STRETCH_LEFT,STR_STRETCH_RIGHT,STR_ZOOM_IN,
									ZOOM_OUT,STR_PERSIANBLIND_H,STR_PERSIANBLIND_V};

static const void *intervaltName[6]={STR_5S,STR_10S,STR_15S,STR_30S,STR_1M,STR_5M};
static const void *statusName[2]={STR_OFF,STR_ON};
static const void *weekName[7]={STR_SUN,STR_MON,STR_TUE,STR_WED,STR_THU,STR_FRI,STR_SAT};
static const void *apmName[2]={STR_TEMP_AM,STR_TEMP_PM};
typedef struct
{
    int  is_auto_play;
    int  index;
    char mountpoint[MOUNT_PATH_MAX_LENGTH];
    char filename[FILE_PATH_LEN];
}photo_user_data_t;

typedef struct
{
    int  effect;
    int  speed;
    char filename[FILE_PATH_LEN];
    char mountpoint[MOUNT_PATH_MAX_LENGTH];
}photo_app_data_t;


typedef enum {
	IMAGE_PLAY_STOP,
	IMAGE_PLAY_START,
} image_play_state_t;

typedef enum {
	IMAGE_DIR_UP,
	IMAGE_DIR_DOWN,
	IMAGE_DIR_LEFT,
	IMAGE_DIR_RIGHT,
	IMAGE_DIR_UNKNOWN
} image_dir_t;

typedef struct {
	pthread_t id;
	pthread_t gif_id;
	pthread_t auto_play_id;
	sem_t sem;
	volatile image_play_state_t play_state;
	char *file_path;
	int file_index;
	int file_total_num;
	int setting_interface_hidden;
	int scaler_ratio; /* in percentage */
	image_rotate_angle_t rotate_angle;
	image_effect_show_mode_t  effect;
	int  speed;
	int  is_busy;
	int  is_early_exit;
	int  is_auto_play;
	photo_app_data_t app_data;
} image_mgr_t;

static image_mgr_t image_mgr;
static volatile int window_level = 0;
static pthread_cond_t  image_wait_cond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t image_wait_mutex;
static pthread_mutex_t image_busy_mutex;


static media_file_list_t *media_file_list = NULL;


void photoPlaying::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    HEAD_RETURN_PNG=(void*)parse_image_from_file(HEAD_RETURN_PNG_PATH);

	LIST_UNSEL_PNG=(void*)parse_image_from_file(LIST_UNSEL_PNG_PATH);
	LIST_CIRCLESEL_PNG=(void*)parse_image_from_file(LIST_CIRCLESEL_PNG_PATH);

    PHOTO_HEAD_ROAT_PNG=(void*)parse_image_from_file(PHOTO_HEAD_ROAT_PNG_PATH);
    PHOTO_HEAD_SCAI_PNG=(void*)parse_image_from_file(PHOTO_HEAD_SCAI_PNG_PATH);
    PHOTO_HEAD_SCAO_PNG=(void*)parse_image_from_file(PHOTO_HEAD_SCAO_PNG_PATH);
    PHOTO_HEAD_PAUSE_PNG=(void*)parse_image_from_file(PHOTO_HEAD_PAUSE_PNG_PATH);
    PHOTO_HEAD_PLAY_PNG=(void*)parse_image_from_file(PHOTO_HEAD_PLAY_PNG_PATH);
    PHOTO_HEAD_DEL_PNG=(void*)parse_image_from_file(PHOTO_HEAD_DEL_PNG_PATH);
    PHOTO_HEAD_ZOOM_PNG=(void*)parse_image_from_file(PHOTO_HEAD_ZOOM_PNG_PATH);
    PHOTO_HEAD_SET_PNG=(void*)parse_image_from_file(PHOTO_HEAD_SET_PNG_PATH);
    PHOTO_HEAD_INFO_PNG=(void*)parse_image_from_file(PHOTO_HEAD_INFO_PNG_PATH);
    PHOTO_HEAD_HEARTF_PNG=(void*)parse_image_from_file(PHOTO_HEAD_HEARTF_PNG_PATH);
    PHOTO_HEAD_HEARTN_PNG=(void*)parse_image_from_file(PHOTO_HEAD_HEARTN_PNG_PATH);
    PHOTO_HEAD_SCENE_PNG=(void*)parse_image_from_file(PHOTO_HEAD_SCENE_PNG_PATH);
	PHOTO_ROUND_PNG=(void*)parse_image_from_file(PHOTO_ROUND_PNG_PATH);
#endif
}
void photoPlaying::ui_image_free(void)
{
#ifdef IMAGE_DECODE
	free_image(HEAD_RETURN_PNG);

	free_image(LIST_UNSEL_PNG);
	free_image(LIST_CIRCLESEL_PNG);
	
    free_image(PHOTO_HEAD_ROAT_PNG);
    free_image(PHOTO_HEAD_SCAI_PNG);
    free_image(PHOTO_HEAD_SCAO_PNG);
    free_image(PHOTO_HEAD_PAUSE_PNG);
    free_image(PHOTO_HEAD_PLAY_PNG);
    free_image(PHOTO_HEAD_DEL_PNG);
    free_image(PHOTO_HEAD_ZOOM_PNG);
    free_image(PHOTO_HEAD_SET_PNG);
    free_image(PHOTO_HEAD_INFO_PNG);
    free_image(PHOTO_HEAD_HEARTF_PNG);
    free_image(PHOTO_HEAD_HEARTN_PNG);
    free_image(PHOTO_HEAD_SCENE_PNG);
	free_image(PHOTO_ROUND_PNG);
#endif
}

photoPlaying::photoPlaying(void)
{
    ui_image_decode();
    frame = new LvcppScreen(lv_layer_top());
    frame->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    frame->set_main_bg_color(lv_color_black(),LV_OPA_100);
    frame->set_userdata(NULL);
    frame->add_event_cb(main_event_handler,LV_EVENT_PRESSED,this);
    frame->add_event_cb(main_event_handler,LV_EVENT_RELEASED,this);
    frame->add_event_cb(main_event_handler,LV_EVENT_SCROLL_END,this);
    mainscreen = frame->myobj;
}

photoPlaying::~photoPlaying(void)
{
    StartTimerShow =false;
    if(tonRoa !=NULL)
    {
        delete tonRoa;
        tonRoa =NULL;
    }
    if(tonSca !=NULL)
    {
        delete tonSca;
        tonSca =NULL;
    }
    if(tonPlay !=NULL)
    {
        delete tonPlay;
        tonPlay =NULL;
    }
    if(tonDel !=NULL)
    {
        delete tonDel;
        tonDel =NULL;
    }
    if(tonZoo !=NULL)
    {
        delete tonZoo;
        tonZoo =NULL;
    }
    if(tonSet !=NULL)
    {
        delete tonSet;
        tonSet =NULL;
    }
    if(tonInfo !=NULL)
    {
        delete tonInfo;
        tonInfo =NULL;
    }
    if(tonHear !=NULL)
    {
        delete tonHear;
        tonHear =NULL;
    }
    if(tonScene !=NULL)
    {
        delete tonScene;
        tonScene =NULL;
    }
    if(str_num !=NULL)
    {
        delete str_num;
        str_num =NULL;
    }
    if(buttonHead !=NULL)
    {
        delete buttonHead;
        buttonHead =NULL;
    }
    if(buttonReturn !=NULL)
    {
        delete buttonReturn;
        buttonReturn =NULL;
    }
	photoplay_Menu_del();
	photoplay_InfoMenu_del();
	photoplay_caption_del();
    if(frame !=NULL)
    {
        delete frame;
        frame =NULL;
        lv_obj_clear_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);   // 清除标志(lv_layer_top层)
        lv_obj_set_style_bg_opa(lv_layer_top(), LV_OPA_TRANSP, 0);  // 设置透明度(lv_layer_top层)
    }
    ui_image_free();
	if(image_mgr.play_state == IMAGE_PLAY_START)
	{
		image_mgr.play_state = IMAGE_PLAY_STOP;
	}
	while(1)
	{
		pthread_mutex_lock(&image_busy_mutex);
		if(image_mgr.is_busy == 0)
		{
			LV_LOG_USER("image_mgr busy!!!\n");
			pthread_mutex_unlock(&image_busy_mutex);
			break;
		}
		pthread_mutex_unlock(&image_busy_mutex);
		usleep(100);
	}
	image_play_thread_up();
	pthread_join(image_mgr.auto_play_id, NULL);
	if(media_file_list!=NULL)
	{
		media_unload_file(media_file_list);
		media_file_list=NULL;
	}
}

int photoPlaying::init_parament(int disk_type,char* file_patch)
{
	SYSDateTime gettime;
	memset(&image_mgr, 0, sizeof(image_mgr));
	image_mgr.scaler_ratio = 100;
	image_mgr.rotate_angle = IMAGE_ROTATE_0;
	read_int_type_param(SETTING_SCENE, SET_DESCRIBE, &captionType);
	read_int_type_param(PHOTO_SCENE, SET_MSG_BGM, &bgmType);
	read_int_type_param(PHOTO_SCENE, SET_MSG_INTERVAL, &intervalType);
	read_int_type_param(PHOTO_SCENE, SET_MSG_EFFECT, &effectType);
	image_disp_cache_enable(1);
	image_disp_rect_set(IMAGE_FULL_SCREEN);
	image_show(file_patch, IMAGE_FULL_SCREEN_SCLAER);
	image_disp_cache_enable(0);
	image_rotate(image_mgr.rotate_angle);
	frame->set_main_bg_color(lv_color_black(),LV_OPA_0);
	
	user_time = gettime.current_datetime();
    flash_inde = disk_type;
	image_play_scan(file_patch);
    StartTimerShow =true;
	image_play_phread_creat();
	photoplay_caption_creat();
	photo_play_head_creat();
	photoPlayTimer = startTimer(500, this);
    return 0;
}

void photoPlaying::TimerCB(lv_timer_t * tmr)
{
	SYSDateTime gettime;
    LV_UNUSED(tmr);
    if(StartTimerShow !=true)
        return;
    static int timecnt = 0;
    timecnt++;
    if((timecntback >10)&&(head_show ==true))
    {
        timecntback =0;
		photoplay_Menu_del();
        buttonReturn->show(false);
        buttonHead->show(false);
        head_show =false;
    }
    else if(head_show ==true)
    {
        timecntback ++;
    }

    if(show_status ==true)
    {
        show_time_num ++;
    }
    else
    {
        show_time_num =0;
    }
	if((captionType)&&(!(timecnt%30)))
    {
        user_time = gettime.current_datetime();
        photoplay_caption_updata();
    }
    //LV_LOG_USER("timecnt:%d",timecnt);
}

void photoPlaying::main_event_handler(lv_event_t *event)
{
    photoPlaying* opt = (photoPlaying*) event->user_data;
	lv_obj_t* target = lv_event_get_target(event);

	if(target == opt->frame->myobj)
	{
	    switch(event->code)
	    {
	        case LV_EVENT_RELEASED:
	            opt->timecntback =0;
	            if(opt->head_show ==false)
	            {
	                opt->buttonReturn->show(true);
	                opt->buttonHead->show(true);
	                opt->head_show =true;
	            }
	            else
	            {
	            	opt->photoplay_Menu_del();
	                opt->buttonReturn->show(false);
	                opt->buttonHead->show(false);
	                opt->head_show =false;
	            }
	        break;
	        case LV_EVENT_SCROLL_END:
	        LV_LOG_USER("LV_EVENT_SCROLL_END !!!!!!");
	        break;
	        default:
	            break;
	    }
	}
}

void photoPlaying::back_event_handler(lv_event_t *event)
{
    photoPlaying* opt = (photoPlaying*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
	char *file_path =NULL;

    if(target == opt->buttonReturn->myobj)
    {
        if(event->code== LV_EVENT_PRESSED)
        {
        	opt->StartTimerShow = false;
        	opt->show_status =false;
            opt->buttonReturn->set_main_bg_img_src(opt->HEAD_RETURN_SEL_PNG);
			opt->image_auto_play_stop();
        }
        else
        {
			opt->pause(opt->photoPlayTimer);
			if(media_file_list !=NULL)
				file_path = media_get_file_path(media_file_list,image_mgr.file_index);
            photoMain::exitPhotoPlay(opt->flash_inde,file_path);
        }
    }
}

LvcppButton* photoPlaying::LvcppButtonHead(lv_obj_t* paren,lv_pplayui_inof_t *uiInfo)
{
    LvcppButton* child_button =NULL;

    child_button = new LvcppButton(paren);
    child_button->set_size(uiInfo->w,uiInfo->h);
    child_button->align_to(paren,LV_ALIGN_TOP_LEFT,uiInfo->x,uiInfo->y);
    child_button->set_main_bg_opa(LV_OPA_0);
    child_button->set_main_radius(0);
    child_button->set_main_pad_all(0);
    child_button->set_main_border_width(0);
    child_button->set_main_bg_img_src(uiInfo->ui_patch);
    child_button->add_event_cb(head_event_handler,LV_EVENT_PRESSED,this);
    child_button->add_event_cb(head_event_handler,LV_EVENT_RELEASED,this);
    return child_button;
}

LvcppLabel* photoPlaying::LvcppLabelViewHead(lv_obj_t* paren,int x,int y,int w,int h,char * str_buff)
{
    LvcppLabel* childView =NULL;

    childView = new LvcppLabel(paren);
    childView->set_size(w,h);
    childView->align_to(paren,LV_ALIGN_TOP_LEFT, x, y);
    childView->txt_font_size(h-6, FT_FONT_STYLE_NORMAL);
    childView->txt_align(LV_TEXT_ALIGN_CENTER);
    childView->txt_color(lv_color_hex(WHITE_COLOR),LV_PART_MAIN);
    childView->set_txt(str_buff);
    return childView;
}

void photoPlaying::photo_play_head_creat(void)
{
    lv_pplayui_inof_t uiInfo;
    char str_buff[64]={0};
	int firstSize =24;
	int sizeMax =128;
	int x, y, w, h;

    head_show =false;
    buttonReturn = new LvcppButton(mainscreen);
    buttonReturn->set_size(66,66);
    buttonReturn->align_to(mainscreen,LV_ALIGN_TOP_LEFT,30,8);
    buttonReturn->set_main_bg_opa(LV_OPA_0);
    buttonReturn->set_main_radius(0);
    buttonReturn->set_main_pad_all(0);
    buttonReturn->set_main_border_width(0);
    buttonReturn->set_main_bg_img_src(HEAD_RETURN_PNG);
    buttonReturn->add_event_cb(back_event_handler,LV_EVENT_PRESSED,this);
    buttonReturn->add_event_cb(back_event_handler,LV_EVENT_RELEASED,this);
    buttonReturn->show(false);

    buttonHead = new LvcppButton(mainscreen);
	if((flash_inde ==0)||(flash_inde ==2)||(flash_inde ==3))
	{
		buttonHead->set_size(1152,100);
    	buttonHead->align_to(mainscreen,LV_ALIGN_TOP_LEFT,64,700);
	}
    else
    {
		buttonHead->set_size(1280,100);
    	buttonHead->align_to(mainscreen,LV_ALIGN_TOP_LEFT,0,700);
	}
    buttonHead->set_main_bg_color(lv_color_black(),LV_OPA_50);
    buttonHead->set_main_radius(10);
    buttonHead->set_main_pad_all(0);
    buttonHead->set_main_border_width(0);
    buttonHead->set_userdata(NULL);
    buttonHead->set_userdata((void*)HEAD_PPLAY);
    buttonHead->add_event_cb(head_event_handler,LV_EVENT_PRESSED,this);
    buttonHead->add_event_cb(head_event_handler,LV_EVENT_RELEASED,this);
    buttonHead->show(false);

	
    uiInfo.x =(int)(firstSize + sizeMax*(HEAD_PPLAY_ROA-1));
    uiInfo.y =10;
    uiInfo.w =80;
    uiInfo.h =80;
    uiInfo.ui_patch =(char *)PHOTO_HEAD_ROAT_PNG;
    tonRoa = LvcppButtonHead(buttonHead->myobj,&uiInfo);

    uiInfo.x =(int)(firstSize + sizeMax*(HEAD_PPLAY_SCA-1));
    uiInfo.y =10;
	if(senceMode ==0)
	{
    	uiInfo.ui_patch =(char *)PHOTO_HEAD_SCAO_PNG;
	}
	else
	{
		uiInfo.ui_patch =(char *)PHOTO_HEAD_SCAI_PNG;
	}
    tonSca = LvcppButtonHead(buttonHead->myobj,&uiInfo);

    uiInfo.x =(int)(firstSize + sizeMax*(HEAD_PPLAY_PLAY-1));
    uiInfo.y =10;
    if(show_status ==true)
    {
    	uiInfo.ui_patch =(char *)PHOTO_HEAD_PAUSE_PNG;
    }
    else
    {
		uiInfo.ui_patch =(char *)PHOTO_HEAD_PLAY_PNG;
    }
    tonPlay = LvcppButtonHead(buttonHead->myobj,&uiInfo);

    uiInfo.x =(int)(firstSize + sizeMax*(HEAD_PPLAY_DEL-1));
    uiInfo.y =10;
    uiInfo.ui_patch =(char *)PHOTO_HEAD_DEL_PNG;
    tonDel = LvcppButtonHead(buttonHead->myobj,&uiInfo);

    uiInfo.x =(int)(firstSize + sizeMax*(HEAD_PPLAY_ZOO-1));
    uiInfo.y =10;
    uiInfo.ui_patch =(char *)PHOTO_HEAD_ZOOM_PNG;
    tonZoo = LvcppButtonHead(buttonHead->myobj,&uiInfo);

    uiInfo.x =(int)(firstSize + sizeMax*(HEAD_PPLAY_SET-1));
    uiInfo.y =10;
    uiInfo.ui_patch =(char *)PHOTO_HEAD_SET_PNG;
    tonSet = LvcppButtonHead(buttonHead->myobj,&uiInfo);

    uiInfo.x =(int)(firstSize + sizeMax*(HEAD_PPLAY_INFO-1));
    uiInfo.y =10;
    uiInfo.ui_patch =(char *)PHOTO_HEAD_INFO_PNG;
    tonInfo = LvcppButtonHead(buttonHead->myobj,&uiInfo);

	if((flash_inde !=0)&&(flash_inde !=2)&&(flash_inde !=3))
	{
	    uiInfo.x =(int)(firstSize + sizeMax*(HEAD_PPLAY_HEAR-1));
	    uiInfo.y =10;
	    uiInfo.ui_patch =(char *)PHOTO_HEAD_HEARTF_PNG;
	    tonHear = LvcppButtonHead(buttonHead->myobj,&uiInfo);
		uiInfo.x =(int)(firstSize + sizeMax*(HEAD_PPLAY_SCENE-1));
		x = (int)(firstSize + sizeMax*(HEAD_PPLAY_MAX-1)-25);
	}
	else
	{
		uiInfo.x =(int)(firstSize + sizeMax*(HEAD_PPLAY_SCENE-2));
		x = (int)(firstSize + sizeMax*(HEAD_PPLAY_SCENE-1)-25);
	}

   	memset(str_buff,0,64);
	sprintf(str_buff,"%d",senceType);
	y = 32;
	w = 130;
	h = 36;
    uiInfo.y =10;
    uiInfo.ui_patch =(char *)PHOTO_HEAD_SCENE_PNG;
    tonScene = LvcppButtonHead(buttonHead->myobj,&uiInfo);
	tonScene->txt_size(80, 36, LV_LABEL_LONG_WRAP);
    tonScene->txt_font_size(30, FT_FONT_STYLE_NORMAL);
    tonScene->txt_align(LV_ALIGN_TOP_MID,0,0);
    tonScene->txt_color(lv_color_white());
	tonScene->add_txt(str_buff);
	
    memset(str_buff,0,64);
    sprintf(str_buff,"%d/%d",file_inde,file_total);
    str_num = LvcppLabelViewHead(buttonHead->myobj,x,y,w,h,str_buff);
}

void photoPlaying::head_event_handler(lv_event_t *event)
{
    photoPlaying* opt = (photoPlaying*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    opt->timecntback =0;
    if((opt->head_show ==false)&&(event->code ==LV_EVENT_PRESSED))
    {
        opt->buttonReturn->show(true);
        opt->buttonHead->show(true);
        opt->head_show =true;
    }

	if(event->code== LV_EVENT_RELEASED)
    {
    	if((opt->tonRoa !=NULL)&&(target ==opt->tonRoa->myobj))
        {
	        LV_LOG_USER("HEAD_PPLAY_ROA !!!!");
			if(opt->image_play_get_status() != IMAGE_PLAY_START)
			{
				int angle = (int)image_mgr.rotate_angle;
				angle++; 
				if(angle > 3)
				{
					angle = 0;
				}
				image_mgr.rotate_angle =(image_rotate_angle_t)angle;
				image_rotate(image_mgr.rotate_angle);
			}
    	}
		else if((opt->tonSca !=NULL)&&(target ==opt->tonSca->myobj))
		{
			LV_LOG_USER("HEAD_PPLAY_SCA !!!!");
			if(opt->image_play_get_status() != IMAGE_PLAY_START)
			{
				if(opt->senceMode)
				{
					LV_LOG_USER("HEAD_PPLAY_SCA A!!!!");
					opt->senceMode = 0;
					if(opt->tonSca !=NULL)
						opt->tonSca->set_main_bg_img_src(opt->PHOTO_HEAD_SCAO_PNG);
					image_disp_cache_enable(1);
					image_disp_rect_set(IMAGE_FULL_SCREEN);
					image_show(image_mgr.file_path, IMAGE_FULL_SCREEN_SCLAER);
					image_disp_cache_enable(0);
				}
				else
				{
					LV_LOG_USER("HEAD_PPLAY_SCA B!!!!");
					opt->senceMode = 1;
					if(opt->tonSca !=NULL)
						opt->tonSca->set_main_bg_img_src(opt->PHOTO_HEAD_SCAI_PNG);
					image_mgr.scaler_ratio = 80;
					image_scaler(&image_mgr.scaler_ratio);
				}
			}
		}
		else if((opt->tonPlay !=NULL)&&(target ==opt->tonPlay->myobj))
		{
			LV_LOG_USER("HEAD_PPLAY_PLAY !!!!");
			if(opt->image_play_get_status() != IMAGE_PLAY_START)
			{
				opt->show_status =true;
				LV_LOG_USER("image_auto_play_start !!!!");
                opt->tonPlay->set_main_bg_img_src(opt->PHOTO_HEAD_PAUSE_PNG);
				opt->image_auto_play_start();
			}
            else
            {
                opt->show_status =false;
				LV_LOG_USER("image_auto_play_stop !!!!");
                opt->tonPlay->set_main_bg_img_src(opt->PHOTO_HEAD_PLAY_PNG);
				opt->image_auto_play_stop();
            }
		}
		else if((opt->tonDel !=NULL)&&(target ==opt->tonDel->myobj))
		{
			LV_LOG_USER("HEAD_PPLAY_DEL !!!!");
			opt->photoplay_rm_CurFile();
		}
		else if((opt->tonZoo !=NULL)&&(target ==opt->tonZoo->myobj))
		{
			LV_LOG_USER("HEAD_PPLAY_ZOO !!!!");
			if(opt->image_play_get_status() != IMAGE_PLAY_START)
			{
				image_mgr.scaler_ratio += 20;
				if(image_mgr.scaler_ratio > 100)
				{
					image_mgr.scaler_ratio = 20;
				}
				image_scaler(&image_mgr.scaler_ratio);
			}
		}
		else if((opt->tonSet !=NULL)&&(target ==opt->tonSet->myobj))
		{
			LV_LOG_USER("HEAD_PPLAY_SET !!!!");
			opt->photoplay_mainMenu_creat();
		}
		else if((opt->tonInfo !=NULL)&&(target ==opt->tonInfo->myobj))
		{
			LV_LOG_USER("HEAD_PPLAY_INFO !!!!");
			opt->photoplay_InfoMenu_creat();
		}
		else if((opt->tonHear !=NULL)&&(target ==opt->tonHear->myobj))
		{
			LV_LOG_USER("HEAD_PPLAY_HEAR !!!!");
		}
    }
}

void photoPlaying::play_next_file(void)
{
    file_inde ++;
    if(file_inde >file_total)
    {
        file_inde =1;
    }
    memset(photo_playpatch,0,1024);
    draw_picture(photo_playpatch);
}

void photoPlaying::draw_picture(void * playpatch)
{
    if(frame !=NULL)
    {
        frame->set_main_bg_img_src(playpatch);
    }
}


//auto play
static int photoplay_userInfo(int userNum,char *userID)
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

void photoPlaying::image_play_scan(char *CurPatch)
{
	char userPatch[64]={0};
	
	if(media_file_list!=NULL)
	{
		media_unload_file(media_file_list);
		media_file_list=NULL;
	}
	memset(MountPoint,0,128);
	if(flash_inde ==0)
	{
        strcpy(MountPoint,"/mnt");
	}
	else if(flash_inde ==1)
	{
		strcpy(MountPoint,"/mnt/UDISK");
	}
	else if(flash_inde ==2)
	{
		strcpy(MountPoint,"/mnt/SDCARD");
	}
	else if(flash_inde ==3)
	{
		strcpy(MountPoint,"/mnt/exUDISK");
	}
	else if(flash_inde ==4)
	{
		strcpy(MountPoint,"/mnt/UDISK/favor");
	}
	else
	{
		if(photoplay_userInfo((flash_inde -PHOTOLIST_MAX),userPatch)<0)
			return ;
		else
			sprintf(MountPoint,"/mnt/UDISK/%s",userPatch);	
	}
	LV_LOG_USER("MountPoint:%s\n",MountPoint);
	media_file_list = media_load_file(RAT_MEDIA_TYPE_PIC, MountPoint);
	if(NULL == media_file_list)
	{
		LV_LOG_USER("%s don't find photo list\n",MountPoint);
        return;
	}
	image_mgr.file_index = media_get_index_from_path(media_file_list,CurPatch);
	image_mgr.file_path  = CurPatch;
}

void photoPlaying::image_play_phread_creat(void)
{
	pthread_mutex_init(&image_busy_mutex, NULL);
	pthread_mutex_init(&image_wait_mutex, NULL);
	pthread_cond_init(&image_wait_cond, NULL);
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr,0x4000);
	pthread_create(&image_mgr.auto_play_id, NULL, image_auto_play_pthread, this);
}

void photoPlaying::image_play_phread_down(void)
{
	pthread_mutex_lock(&image_wait_mutex);
	pthread_cond_wait(&image_wait_cond, &image_wait_mutex);
	pthread_mutex_unlock(&image_wait_mutex);
}

void photoPlaying::image_play_thread_up(void)
{
	pthread_mutex_lock(&image_wait_mutex);
	pthread_cond_signal(&image_wait_cond);
	pthread_mutex_unlock(&image_wait_mutex);
}

void photoPlaying::image_play_stop(void)
{
	if (image_mgr.play_state != IMAGE_PLAY_STOP) {
		image_mgr.play_state = IMAGE_PLAY_STOP;
		pthread_join(image_mgr.id, NULL);
		sem_destroy(&image_mgr.sem);
	}
}

void photoPlaying::image_auto_play_start(void)
{
	image_disp_cache_enable(1);
	image_mgr.rotate_angle = IMAGE_ROTATE_0;
	image_mgr.scaler_ratio = 100;
	image_disp_rect_set(IMAGE_FULL_SCREEN);
	image_show_normal();
	image_disp_cache_enable(0);
	show_time_num =0;
	image_mgr.play_state = IMAGE_PLAY_START;
	image_play_thread_up();
}

void photoPlaying::image_auto_play_stop(void)
{
	image_mgr.play_state = IMAGE_PLAY_STOP;
}

void photoPlaying::image_play_prepare(void)
{
	char buff[1024]={0};
	
	image_mgr.file_index = (image_mgr.file_index + 1) % image_mgr.file_total_num;
	image_mgr.file_path = media_get_file_path(media_file_list,image_mgr.file_index);
	if(image_mgr.file_path==NULL)
	{
		image_mgr.file_index = 0;
		image_mgr.file_path = media_get_file_path(media_file_list,image_mgr.file_index);
		if(image_mgr.file_path==NULL)
		{
			if(show_status ==true)
            {
                show_status =false;
				LV_LOG_USER("image_auto_play_stop !!!!");
                tonPlay->set_main_bg_img_src(PHOTO_HEAD_PLAY_PNG);
				image_auto_play_stop();
            }
            else
            {
                show_status =true;
				LV_LOG_USER("image_auto_play_start !!!!");
                tonPlay->set_main_bg_img_src(PHOTO_HEAD_PAUSE_PNG);
				image_auto_play_start();
            }
		}
	}
	
	if(CaIconLabel !=NULL)
	{
		memset(buff,0,1024);
	    if(image_mgr.file_path != NULL)
	    {
			_get_file_time(image_mgr.file_path,buff);
		}
    	CaIconLabel->set_txt(buff);
	}
}

int photoPlaying::image_play_get_status(void)
{
	return image_mgr.play_state;
}

int photoPlaying::image_play_get_interval(void)
{
	return image_mgr.speed;
}


void* photoPlaying::image_auto_play_pthread(void *arg)
{
	photoPlaying* opt = (photoPlaying*)arg;
	int interval,delay_cnt;
	int ret = 0;
	while(1)
	{
		if(opt->image_play_get_status() == IMAGE_PLAY_START)
		{
			if(opt->show_time_num > opt->slide_time[opt->intervalType]*2)
	        {
	            opt->show_time_num =0;
				pthread_mutex_lock(&image_busy_mutex);
				image_mgr.is_busy = 1;
				pthread_mutex_unlock(&image_busy_mutex);
				opt->image_play_prepare();
				ret = image_effect_show(image_mgr.file_path, (image_effect_show_mode_t)opt->effectType);
				opt->show_time_num =0;
	        }
		}
		if(opt->image_play_get_status() == IMAGE_PLAY_STOP)
		{
			printf("down!!!\n");
			pthread_mutex_lock(&image_busy_mutex);
			image_mgr.is_busy = 0;
			pthread_mutex_unlock(&image_busy_mutex);
			opt->image_play_phread_down();
			printf("up!!!!\n");
		}
		if(opt->image_play_get_status() == IMAGE_PLAY_STOP)
		{
			pthread_exit(0);
		}
	}

}

void photoPlaying::photoplay_mainMenu_creat(void)
{
    mainMenuButton = new LvcppButton(mainscreen);
    mainMenuButton->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    mainMenuButton->set_main_bg_color(lv_color_black(),LV_OPA_60);
    mainMenuButton->add_event_cb(photoplay_mainMenu_event_handler,LV_EVENT_CLICKED,this);

    mainMenuLabel = new LvcppLabel(mainMenuButton->myobj);
    mainMenuLabel->set_size(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/5*2);
    mainMenuLabel->center_align();
    mainMenuLabel->set_main_bg_color(lv_color_black(),LV_OPA_60);
    mainMenuLabel->set_main_border_width(1);
    mainMenuLabel->set_main_border_color(lv_color_white());
    mainMenuLabel->set_main_radius(10);
    mainMenuLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
    mainMenuLabel->set_txt("");

    cpNameLabel =new LvcppLabel(mainMenuLabel->myobj);
    cpNameLabel->set_size(SCREEN_HOR_SIZE/3-10,SCREEN_VER_SIZE/10-1);
    cpNameLabel->align(LV_ALIGN_TOP_LEFT,10,0);
    cpNameLabel->set_main_bg_color(lv_color_black(),LV_OPA_60);
    cpNameLabel->txt_font_size(24, FT_FONT_STYLE_NORMAL);
    cpNameLabel->txt_align(LV_TEXT_ALIGN_LEFT);
    cpNameLabel->txt_color(lv_color_white(),LV_PART_MAIN);
    cpNameLabel->set_txt(STR_CAPTION);
    cpNameLabel->set_main_pad_T_B(22,0);
    cpNameLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
    cpNameLabel->add_event_cb(photoplay_mainMenu_event_handler,LV_EVENT_CLICKED,this);

    cpDataLabel =new LvcppLabel(mainMenuLabel->myobj);
    cpDataLabel->set_size(SCREEN_HOR_SIZE/6-10,SCREEN_VER_SIZE/10-1);
    cpDataLabel->align(LV_ALIGN_TOP_RIGHT,-10,0);
    cpDataLabel->set_main_bg_color(lv_color_black(),LV_OPA_60);
    cpDataLabel->txt_font_size(24, FT_FONT_STYLE_NORMAL);
    cpDataLabel->txt_align(LV_TEXT_ALIGN_RIGHT);
    cpDataLabel->txt_color(lv_color_white(),LV_PART_MAIN);
    cpDataLabel->set_txt((char*) statusName[captionType]);
    cpDataLabel->set_main_pad_T_B(22,0);
    cpDataLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
    cpDataLabel->add_event_cb(photoplay_mainMenu_event_handler,LV_EVENT_CLICKED,this);

    mainLineLabel1 =new LvcppLabel(mainMenuLabel->myobj);
    mainLineLabel1->set_size(SCREEN_HOR_SIZE/2,1);
    mainLineLabel1->set_main_bg_color(lv_color_white(),LV_OPA_100);
    mainLineLabel1->align(LV_ALIGN_TOP_LEFT,0,SCREEN_VER_SIZE/10-1);
    mainLineLabel1->set_txt("");

    bmNameLabel =new LvcppLabel(mainMenuLabel->myobj);
    bmNameLabel->set_size(SCREEN_HOR_SIZE/3-10,SCREEN_VER_SIZE/10-1);
    bmNameLabel->align(LV_ALIGN_TOP_LEFT,10,SCREEN_VER_SIZE/10);
    bmNameLabel->set_main_bg_color(lv_color_black(),LV_OPA_60);
    bmNameLabel->txt_font_size(24, FT_FONT_STYLE_NORMAL);
    bmNameLabel->txt_align(LV_TEXT_ALIGN_LEFT);
    bmNameLabel->txt_color(lv_color_white(),LV_PART_MAIN);
    bmNameLabel->set_txt(STR_BGM);
    bmNameLabel->set_main_pad_T_B(22,0);
    bmNameLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
    bmNameLabel->add_event_cb(photoplay_mainMenu_event_handler,LV_EVENT_CLICKED,this);

    bmDataLabel =new LvcppLabel(mainMenuLabel->myobj);
    bmDataLabel->set_size(SCREEN_HOR_SIZE/6-10,SCREEN_VER_SIZE/10-1);
    bmDataLabel->align(LV_ALIGN_TOP_RIGHT,-10,SCREEN_VER_SIZE/10);
    bmDataLabel->set_main_bg_color(lv_color_black(),LV_OPA_60);
    bmDataLabel->txt_font_size(24, FT_FONT_STYLE_NORMAL);
    bmDataLabel->txt_align(LV_TEXT_ALIGN_RIGHT);
    bmDataLabel->txt_color(lv_color_white(),LV_PART_MAIN);
    bmDataLabel->set_txt((char*) statusName[bgmType]);
    bmDataLabel->set_main_pad_T_B(22,0);
    bmDataLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
    bmDataLabel->add_event_cb(photoplay_mainMenu_event_handler,LV_EVENT_CLICKED,this);

    mainLineLabel2 =new LvcppLabel(mainMenuLabel->myobj);
    mainLineLabel2->set_size(SCREEN_HOR_SIZE/2,1);
    mainLineLabel2->set_main_bg_color(lv_color_white(),LV_OPA_100);
    mainLineLabel2->align(LV_ALIGN_TOP_LEFT,0,SCREEN_VER_SIZE/5-1);
    mainLineLabel2->set_txt("");

    inNameLabel =new LvcppLabel(mainMenuLabel->myobj);
    inNameLabel->set_size(SCREEN_HOR_SIZE/3-10,SCREEN_VER_SIZE/10-1);
    inNameLabel->align(LV_ALIGN_TOP_LEFT,10,SCREEN_VER_SIZE/5);
    inNameLabel->set_main_bg_color(lv_color_black(),LV_OPA_60);
    inNameLabel->txt_font_size(24, FT_FONT_STYLE_NORMAL);
    inNameLabel->txt_align(LV_TEXT_ALIGN_LEFT);
    inNameLabel->txt_color(lv_color_white(),LV_PART_MAIN);
    inNameLabel->set_txt(STR_INTERVAL);
    inNameLabel->set_main_pad_T_B(22,0);
    inNameLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
    inNameLabel->add_event_cb(photoplay_mainMenu_event_handler,LV_EVENT_CLICKED,this);

    inDataLabel =new LvcppLabel(mainMenuLabel->myobj);
    inDataLabel->set_size(SCREEN_HOR_SIZE/6-10,SCREEN_VER_SIZE/10-1);
    inDataLabel->align(LV_ALIGN_TOP_RIGHT,-10,SCREEN_VER_SIZE/5);
    inDataLabel->set_main_bg_color(lv_color_black(),LV_OPA_60);
    inDataLabel->txt_font_size(24, FT_FONT_STYLE_NORMAL);
    inDataLabel->txt_align(LV_TEXT_ALIGN_RIGHT);
    inDataLabel->txt_color(lv_color_white(),LV_PART_MAIN);
    inDataLabel->set_txt((char*) intervaltName[intervalType]);
    inDataLabel->set_main_pad_T_B(22,0);
    inDataLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
    inDataLabel->add_event_cb(photoplay_mainMenu_event_handler,LV_EVENT_CLICKED,this);

    mainLineLabel3 =new LvcppLabel(mainMenuLabel->myobj);
    mainLineLabel3->set_size(SCREEN_HOR_SIZE/2,1);
    mainLineLabel3->set_main_bg_color(lv_color_white(),LV_OPA_100);
    mainLineLabel3->align(LV_ALIGN_TOP_LEFT,0,SCREEN_VER_SIZE/10*3-1);
    mainLineLabel3->set_txt("");

    efNameLabel =new LvcppLabel(mainMenuLabel->myobj);
    efNameLabel->set_size(SCREEN_HOR_SIZE/3-10,SCREEN_VER_SIZE/10-2);
    efNameLabel->align(LV_ALIGN_TOP_LEFT,10,SCREEN_VER_SIZE/10*3);
    efNameLabel->set_main_bg_color(lv_color_black(),LV_OPA_60);
    efNameLabel->txt_font_size(24, FT_FONT_STYLE_NORMAL);
    efNameLabel->txt_align(LV_TEXT_ALIGN_LEFT);
    efNameLabel->txt_color(lv_color_white(),LV_PART_MAIN);
    efNameLabel->set_txt(STR_EFFECT);
    efNameLabel->set_main_pad_T_B(22,0);
    efNameLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
    efNameLabel->add_event_cb(photoplay_mainMenu_event_handler,LV_EVENT_CLICKED,this);

    efDataLabel =new LvcppLabel(mainMenuLabel->myobj);
    efDataLabel->set_size(SCREEN_HOR_SIZE/6-10,SCREEN_VER_SIZE/10-2);
    efDataLabel->align(LV_ALIGN_TOP_RIGHT,-10,SCREEN_VER_SIZE/10*3);
    efDataLabel->set_main_bg_color(lv_color_black(),LV_OPA_60);
    efDataLabel->txt_font_size(24, FT_FONT_STYLE_NORMAL);
    efDataLabel->txt_align(LV_TEXT_ALIGN_RIGHT);
    efDataLabel->txt_color(lv_color_white(),LV_PART_MAIN);
    efDataLabel->set_txt((char*) effectName[effectType]);
    efDataLabel->set_main_pad_T_B(22,0);
    efDataLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
    efDataLabel->add_event_cb(photoplay_mainMenu_event_handler,LV_EVENT_CLICKED,this);
}

void photoPlaying::photoplay_mainMenu_del(void)
{
    if(mainLineLabel1 != NULL)
    {
        delete mainLineLabel1;
        mainLineLabel1 =NULL;
    }
    if(mainLineLabel2 != NULL)
    {
        delete mainLineLabel2;
        mainLineLabel2 =NULL;
    }
    if(mainLineLabel3 != NULL)
    {
        delete mainLineLabel3;
        mainLineLabel3 =NULL;
    }
    if(efNameLabel != NULL)
    {
        delete efNameLabel;
        efNameLabel =NULL;
    }
    if(inNameLabel != NULL)
    {
        delete inNameLabel;
        inNameLabel =NULL;
    }
    if(bmNameLabel != NULL)
    {
        delete bmNameLabel;
        bmNameLabel =NULL;
    }
    if(cpNameLabel != NULL)
    {
        delete cpNameLabel;
        cpNameLabel =NULL;
    }
    if(mainMenuLabel != NULL)
    {
        delete mainMenuLabel;
        mainMenuLabel =NULL;
    }
}

void photoPlaying::photoplay_intervalMenu_creat(void)
{
    intervalMenuLabel = new LvcppLabel(mainMenuButton->myobj);
    intervalMenuLabel->set_size(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/3*2);
    intervalMenuLabel->center_align();
    intervalMenuLabel->set_main_bg_color(lv_color_black(),LV_OPA_60);
    intervalMenuLabel->set_main_border_width(1);
    intervalMenuLabel->set_main_border_color(lv_color_white());
    intervalMenuLabel->set_main_radius(10);
    intervalMenuLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
    intervalMenuLabel->set_txt("");

    Label5S =new LvcppLabel(intervalMenuLabel->myobj);
    Label5S->set_size(SCREEN_HOR_SIZE/2-20,SCREEN_VER_SIZE/9-1);
    Label5S->align(LV_ALIGN_TOP_LEFT,10,0);
    Label5S->set_main_bg_color(lv_color_black(),LV_OPA_60);
    Label5S->txt_font_size(24, FT_FONT_STYLE_NORMAL);
    Label5S->txt_align(LV_TEXT_ALIGN_LEFT);
    Label5S->txt_color(lv_color_white(),LV_PART_MAIN);
    Label5S->set_txt(STR_5S);
    Label5S->set_main_pad_T_B(24,0);
    Label5S->add_flag(LV_OBJ_FLAG_CLICKABLE);
    Label5S->add_event_cb(photoplay_mainMenu_event_handler,LV_EVENT_CLICKED,this);

    Image5S = new LvcppImageButton(Label5S->myobj);
    Image5S->set_size(32,32);
    Image5S->set_align_mode(LV_ALIGN_RIGHT_MID);
    Image5S->align(LV_ALIGN_RIGHT_MID,0,-12);
    Image5S->set_main_bg_img_src(LIST_UNSEL_PNG);

    inLineLabel1 =new LvcppLabel(intervalMenuLabel->myobj);
    inLineLabel1->set_size(SCREEN_HOR_SIZE/2,1);
    inLineLabel1->set_main_bg_color(lv_color_white(),LV_OPA_100);
    inLineLabel1->align(LV_ALIGN_TOP_LEFT,0,SCREEN_VER_SIZE/9-1);
    inLineLabel1->set_txt("");

    Label10S =new LvcppLabel(intervalMenuLabel->myobj);
    Label10S->set_size(SCREEN_HOR_SIZE/2-20,SCREEN_VER_SIZE/9-1);
    Label10S->align(LV_ALIGN_TOP_LEFT,10,SCREEN_VER_SIZE/9);
    Label10S->set_main_bg_color(lv_color_black(),LV_OPA_60);
    Label10S->txt_font_size(24, FT_FONT_STYLE_NORMAL);
    Label10S->txt_align(LV_TEXT_ALIGN_LEFT);
    Label10S->txt_color(lv_color_white(),LV_PART_MAIN);
    Label10S->set_txt(STR_10S);
    Label10S->set_main_pad_T_B(24,0);
    Label10S->add_flag(LV_OBJ_FLAG_CLICKABLE);
    Label10S->add_event_cb(photoplay_mainMenu_event_handler,LV_EVENT_CLICKED,this);

    Image10S = new LvcppImageButton(Label10S->myobj);
    Image10S->set_size(32,32);
    Image10S->set_align_mode(LV_ALIGN_RIGHT_MID);
    Image10S->align(LV_ALIGN_RIGHT_MID,0,-12);
    Image10S->set_main_bg_img_src(LIST_UNSEL_PNG);

    inLineLabel2 =new LvcppLabel(intervalMenuLabel->myobj);
    inLineLabel2->set_size(SCREEN_HOR_SIZE/2,1);
    inLineLabel2->set_main_bg_color(lv_color_white(),LV_OPA_100);
    inLineLabel2->align(LV_ALIGN_TOP_LEFT,0,SCREEN_VER_SIZE/9*2-1);
    inLineLabel2->set_txt("");

    Label15S =new LvcppLabel(intervalMenuLabel->myobj);
    Label15S->set_size(SCREEN_HOR_SIZE/2-20,SCREEN_VER_SIZE/9-1);
    Label15S->align(LV_ALIGN_TOP_LEFT,10,SCREEN_VER_SIZE/9*2);
    Label15S->set_main_bg_color(lv_color_black(),LV_OPA_60);
    Label15S->txt_font_size(24, FT_FONT_STYLE_NORMAL);
    Label15S->txt_align(LV_TEXT_ALIGN_LEFT);
    Label15S->txt_color(lv_color_white(),LV_PART_MAIN);
    Label15S->set_txt(STR_15S);
    Label15S->set_main_pad_T_B(24,0);
    Label15S->add_flag(LV_OBJ_FLAG_CLICKABLE);
    Label15S->add_event_cb(photoplay_mainMenu_event_handler,LV_EVENT_CLICKED,this);

    Image15S = new LvcppImageButton(Label15S->myobj);
    Image15S->set_size(32,32);
    Image15S->set_align_mode(LV_ALIGN_RIGHT_MID);
    Image15S->align(LV_ALIGN_RIGHT_MID,0,-12);
    Image15S->set_main_bg_img_src(LIST_UNSEL_PNG);

    inLineLabel3 =new LvcppLabel(intervalMenuLabel->myobj);
    inLineLabel3->set_size(SCREEN_HOR_SIZE/2,1);
    inLineLabel3->set_main_bg_color(lv_color_white(),LV_OPA_100);
    inLineLabel3->align(LV_ALIGN_TOP_LEFT,0,SCREEN_VER_SIZE/3-1);
    inLineLabel3->set_txt("");

    Label30S =new LvcppLabel(intervalMenuLabel->myobj);
    Label30S->set_size(SCREEN_HOR_SIZE/2-20,SCREEN_VER_SIZE/9-1);
    Label30S->align(LV_ALIGN_TOP_LEFT,10,SCREEN_VER_SIZE/3);
    Label30S->set_main_bg_color(lv_color_black(),LV_OPA_60);
    Label30S->txt_font_size(24, FT_FONT_STYLE_NORMAL);
    Label30S->txt_align(LV_TEXT_ALIGN_LEFT);
    Label30S->txt_color(lv_color_white(),LV_PART_MAIN);
    Label30S->set_txt(STR_30S);
    Label30S->set_main_pad_T_B(24,0);
    Label30S->add_flag(LV_OBJ_FLAG_CLICKABLE);
    Label30S->add_event_cb(photoplay_mainMenu_event_handler,LV_EVENT_CLICKED,this);

    Image30S = new LvcppImageButton(Label30S->myobj);
    Image30S->set_size(32,32);
    Image30S->set_align_mode(LV_ALIGN_RIGHT_MID);
    Image30S->align(LV_ALIGN_RIGHT_MID,0,-12);
    Image30S->set_main_bg_img_src(LIST_UNSEL_PNG);

    inLineLabel4 =new LvcppLabel(intervalMenuLabel->myobj);
    inLineLabel4->set_size(SCREEN_HOR_SIZE/2,1);
    inLineLabel4->set_main_bg_color(lv_color_white(),LV_OPA_100);
    inLineLabel4->align(LV_ALIGN_TOP_LEFT,0,SCREEN_VER_SIZE/9*4-1);
    inLineLabel4->set_txt("");

    Label1M =new LvcppLabel(intervalMenuLabel->myobj);
    Label1M->set_size(SCREEN_HOR_SIZE/2-20,SCREEN_VER_SIZE/9-1);
    Label1M->align(LV_ALIGN_TOP_LEFT,10,SCREEN_VER_SIZE/9*4);
    Label1M->set_main_bg_color(lv_color_black(),LV_OPA_60);
    Label1M->txt_font_size(24, FT_FONT_STYLE_NORMAL);
    Label1M->txt_align(LV_TEXT_ALIGN_LEFT);
    Label1M->txt_color(lv_color_white(),LV_PART_MAIN);
    Label1M->set_txt(STR_1M);
    Label1M->set_main_pad_T_B(24,0);
    Label1M->add_flag(LV_OBJ_FLAG_CLICKABLE);
    Label1M->add_event_cb(photoplay_mainMenu_event_handler,LV_EVENT_CLICKED,this);

    Image1M = new LvcppImageButton(Label1M->myobj);
    Image1M->set_size(32,32);
    Image1M->set_align_mode(LV_ALIGN_RIGHT_MID);
    Image1M->align(LV_ALIGN_RIGHT_MID,0,-12);
    Image1M->set_main_bg_img_src(LIST_UNSEL_PNG);

    inLineLabel5 =new LvcppLabel(intervalMenuLabel->myobj);
    inLineLabel5->set_size(SCREEN_HOR_SIZE/2,1);
    inLineLabel5->set_main_bg_color(lv_color_white(),LV_OPA_100);
    inLineLabel5->align(LV_ALIGN_TOP_LEFT,0,SCREEN_VER_SIZE/9*5-1);
    inLineLabel5->set_txt("");

    Label5M =new LvcppLabel(intervalMenuLabel->myobj);
    Label5M->set_size(SCREEN_HOR_SIZE/2-20,SCREEN_VER_SIZE/9-2);
    Label5M->align(LV_ALIGN_TOP_LEFT,10,SCREEN_VER_SIZE/9*5);
    Label5M->set_main_bg_color(lv_color_black(),LV_OPA_60);
    Label5M->txt_font_size(24, FT_FONT_STYLE_NORMAL);
    Label5M->txt_align(LV_TEXT_ALIGN_LEFT);
    Label5M->txt_color(lv_color_white(),LV_PART_MAIN);
    Label5M->set_txt(STR_5M);
    Label5M->set_main_pad_T_B(24,0);
    Label5M->add_flag(LV_OBJ_FLAG_CLICKABLE);
    Label5M->add_event_cb(photoplay_mainMenu_event_handler,LV_EVENT_CLICKED,this);

    Image5M = new LvcppImageButton(Label5M->myobj);
    Image5M->set_size(32,32);
    Image5M->align(LV_ALIGN_RIGHT_MID,0,-12);
    Image5M->set_main_bg_img_src(LIST_UNSEL_PNG);

    if(intervalType ==1)
    {
        Image10S->set_main_bg_img_src(LIST_CIRCLESEL_PNG);
    }
    else if(intervalType ==2)
    {
        Image15S->set_main_bg_img_src(LIST_CIRCLESEL_PNG);
    }
    else if(intervalType ==3)
    {
        Image30S->set_main_bg_img_src(LIST_CIRCLESEL_PNG);
    }
    else if(intervalType ==4)
    {
        Image1M->set_main_bg_img_src(LIST_CIRCLESEL_PNG);
    }
    else if(intervalType ==5)
    {
        Image5M->set_main_bg_img_src(LIST_CIRCLESEL_PNG);
    }
    else
    {
        Image5S->set_main_bg_img_src(LIST_CIRCLESEL_PNG);
    }
}

void photoPlaying::photoplay_intervalMenu_del(void)
{
    if(Image5S != NULL)
    {
        delete Image5S;
        Image5S =NULL;
    }
    if(Label5S != NULL)
    {
        delete Label5S;
        Label5S =NULL;
    }
    if(Image10S != NULL)
    {
        delete Image10S;
        Image10S =NULL;
    }
    if(Label10S != NULL)
    {
        delete Label10S;
        Label10S =NULL;
    }
    if(Image15S != NULL)
    {
        delete Image15S;
        Image15S =NULL;
    }
    if(Label15S != NULL)
    {
        delete Label15S;
        Label15S =NULL;
    }
    if(Image30S != NULL)
    {
        delete Image30S;
        Image30S =NULL;
    }
    if(Label30S != NULL)
    {
        delete Label30S;
        Label30S =NULL;
    }
    if(Image1M != NULL)
    {
        delete Image1M;
        Image1M =NULL;
    }
    if(Label1M != NULL)
    {
        delete Label1M;
        Label1M =NULL;
    }
    if(Image5M != NULL)
    {
        delete Image5M;
        Image5M =NULL;
    }
    if(Label5M != NULL)
    {
        delete Label5M;
        Label5M =NULL;
    }
    if(inLineLabel1 != NULL)
    {
        delete inLineLabel1;
        inLineLabel1 =NULL;
    }
    if(inLineLabel2 != NULL)
    {
        delete inLineLabel2;
        inLineLabel2 =NULL;
    }
    if(inLineLabel3 != NULL)
    {
        delete inLineLabel3;
        inLineLabel3 =NULL;
    }
    if(inLineLabel4 != NULL)
    {
        delete inLineLabel4;
        inLineLabel4 =NULL;
    }
    if(inLineLabel5 != NULL)
    {
        delete inLineLabel5;
        inLineLabel5 =NULL;
    }
    if(intervalMenuLabel != NULL)
    {
        delete intervalMenuLabel;
        intervalMenuLabel =NULL;
    }
}
void photoPlaying::photoplay_effectMenu_creat(void)
{
    int i=0;

    effectList = new LvcppList(mainMenuButton->myobj);
    effectList->set_size(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/2);
    effectList->center_align();
    effectList->set_main_bg_color(lv_color_black(),LV_OPA_60);
    effectList->set_main_border_color(lv_color_white());
    effectList->set_main_border_width(1);
    effectList->set_flex_flow(LV_FLEX_FLOW_COLUMN);
    effectList->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    effectList->set_main_pad_all(0);
    effectList->set_main_pad_row(10);
    effectList->set_main_pad_column(0);
    effectList->set_main_radius(10);
    memset(&effectmenuList, 0 , sizeof(lv_ppmenulist_t));
	effectList->add_event_cb(photoplay_mainMenu_event_handler,LV_EVENT_SCROLL_END,this);

	for(i=0;i<16;i++)
    {
        effectmenuList.Menulist[i] = new menuList(effectList->myobj);
        effectmenuList.Menulist[i]->Label->set_size(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/10);
        effectmenuList.Menulist[i]->Label->center_align();
        effectmenuList.Menulist[i]->Label->set_main_bg_color(lv_color_black(),LV_OPA_60);
        effectmenuList.Menulist[i]->Label->txt_font_size(24, FT_FONT_STYLE_NORMAL);
        effectmenuList.Menulist[i]->Label->txt_align(LV_TEXT_ALIGN_LEFT);
        effectmenuList.Menulist[i]->Label->txt_color(lv_color_white(),LV_PART_MAIN);
        effectmenuList.Menulist[i]->Label->set_txt((char*) effectName[i]);
        effectmenuList.Menulist[i]->Label->set_main_pad_T_B(24,0);
        effectmenuList.Menulist[i]->Label->set_main_pad_L_R(10,0);
        effectmenuList.Menulist[i]->Label->add_flag(LV_OBJ_FLAG_CLICKABLE);
        effectmenuList.Menulist[i]->Label->add_event_cb(photoplay_mainMenu_event_handler,LV_EVENT_CLICKED,this);

        effectmenuList.Menulist[i]->chelImage->set_size(32,32);
        effectmenuList.Menulist[i]->chelImage->align(LV_ALIGN_RIGHT_MID,-10,-12);
        if(effectType ==i)
            effectmenuList.Menulist[i]->chelImage->set_main_bg_img_src(LIST_CIRCLESEL_PNG);
        else
            effectmenuList.Menulist[i]->chelImage->set_main_bg_img_src(LIST_UNSEL_PNG);

        effectmenuList.Menulist[i]->LineLabel->set_size(SCREEN_HOR_SIZE/2,1);
        effectmenuList.Menulist[i]->LineLabel->set_main_bg_color(lv_color_white(),LV_OPA_100);
        effectmenuList.Menulist[i]->LineLabel->align(LV_ALIGN_TOP_LEFT,0,SCREEN_VER_SIZE/10);
        effectmenuList.Menulist[i]->LineLabel->set_txt("");
    }
	effectList->set_scroll_to(0,effectType*SCREEN_VER_SIZE/10, LV_ANIM_OFF);
}
void photoPlaying::photoplay_effectMenu_del(void)
{
    int i=0;

    for(i=15;i>=0;i--)
    {
        if(effectmenuList.Menulist[i] != NULL)
        {
            delete effectmenuList.Menulist[i];
            effectmenuList.Menulist[i] =NULL;
        }
    }
    if(effectList != NULL)
    {
        delete effectList;
        effectList =NULL;
    }
}
void photoPlaying::photoplay_Menu_del(void)
{
	if(intervalMenuLabel != NULL)
    {
        photoplay_intervalMenu_del();
    }
    if(effectList != NULL)
    {
		photoplay_effectMenu_del();
    }
	if(mainMenuLabel != NULL)
	{
    	photoplay_mainMenu_del();
	}
    if(mainMenuButton != NULL)
    {
        delete mainMenuButton;
        mainMenuButton =NULL;
    }
}
void photoPlaying::photoplay_mainMenu_event_handler(lv_event_t *event)
{
    photoPlaying* opt = (photoPlaying*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    int i=0;
	
	opt->timecntback =0;
	
	if(event->code ==LV_EVENT_SCROLL_END)
	{
		return;
	}
    if(target==opt->mainMenuButton->myobj)
    {
        opt->photoplay_Menu_del();
    }
    else if((target==opt->cpNameLabel->myobj)||(target==opt->cpDataLabel->myobj))
    {
        if(opt->captionType ==1)
            opt->captionType =0;
        else
            opt->captionType =1;
		write_int_type_param(SETTING_SCENE, SET_DESCRIBE, opt->captionType);
        opt->cpDataLabel->set_txt((char*) statusName[opt->captionType]);
		opt->photoplay_caption_show(opt->captionType);
    }
    else if((target==opt->bmNameLabel->myobj)||(target==opt->bmDataLabel->myobj))
    {
        if(opt->bgmType ==1)
            opt->bgmType =0;
        else
            opt->bgmType =1;
		write_int_type_param(PHOTO_SCENE, SET_MSG_BGM, opt->bgmType);
        opt->bmDataLabel->set_txt((char*) statusName[opt->bgmType]);
    }
    else if((target==opt->inNameLabel->myobj)||(target==opt->inDataLabel->myobj))
    {
        opt->mainMenuLabel->show(false);
        opt->photoplay_intervalMenu_creat();
    }
    else if((target==opt->efNameLabel->myobj)||(target==opt->efDataLabel->myobj))
    {
        opt->mainMenuLabel->show(false);
        opt->photoplay_effectMenu_creat();
    }
    else if((opt->intervalMenuLabel !=NULL)&&(target==opt->Label5S->myobj))
    {
       opt->intervalType=0;
	   opt->show_time_num =0;
	   write_int_type_param(PHOTO_SCENE, SET_MSG_INTERVAL, opt->intervalType);
       opt->Image5S->set_main_bg_img_src(opt->LIST_CIRCLESEL_PNG);
       opt->photoplay_intervalMenu_del();
       opt->inDataLabel->set_txt((char*) intervaltName[opt->intervalType]);
       opt->mainMenuLabel->show(true);
    }
    else if((opt->intervalMenuLabel !=NULL)&&(target==opt->Label10S->myobj))
    {
       opt->intervalType=1;
	   opt->show_time_num =0;
	   write_int_type_param(PHOTO_SCENE, SET_MSG_INTERVAL, opt->intervalType);
       opt->Image10S->set_main_bg_img_src(opt->LIST_CIRCLESEL_PNG);
       opt->photoplay_intervalMenu_del();
       opt->inDataLabel->set_txt((char*) intervaltName[opt->intervalType]);
       opt->mainMenuLabel->show(true);
    }
    else if((opt->intervalMenuLabel !=NULL)&&(target==opt->Label15S->myobj))
    {
       opt->intervalType=2;
	   opt->show_time_num =0;
	   write_int_type_param(PHOTO_SCENE, SET_MSG_INTERVAL, opt->intervalType);
       opt->Image15S->set_main_bg_img_src(opt->LIST_CIRCLESEL_PNG);
       opt->photoplay_intervalMenu_del();
       opt->inDataLabel->set_txt((char*) intervaltName[opt->intervalType]);
       opt->mainMenuLabel->show(true);
    }
    else if((opt->intervalMenuLabel !=NULL)&&(target==opt->Label30S->myobj))
    {
       opt->intervalType=3;
	   opt->show_time_num =0;
	   write_int_type_param(PHOTO_SCENE, SET_MSG_INTERVAL, opt->intervalType);
       opt->Image30S->set_main_bg_img_src(opt->LIST_CIRCLESEL_PNG);
       opt->photoplay_intervalMenu_del();
       opt->inDataLabel->set_txt((char*) intervaltName[opt->intervalType]);
       opt->mainMenuLabel->show(true);
    }
    else if((opt->intervalMenuLabel !=NULL)&&(target==opt->Label1M->myobj))
    {
       opt->intervalType=4;
	   opt->show_time_num =0;
	   write_int_type_param(PHOTO_SCENE, SET_MSG_INTERVAL, opt->intervalType);
       opt->Image1M->set_main_bg_img_src(opt->LIST_CIRCLESEL_PNG);
       opt->photoplay_intervalMenu_del();
       opt->inDataLabel->set_txt((char*) intervaltName[opt->intervalType]);
       opt->mainMenuLabel->show(true);
    }
    else if((opt->intervalMenuLabel !=NULL)&&(target==opt->Label5M->myobj))
    {
       opt->intervalType=5;
	   opt->show_time_num =0;
	   write_int_type_param(PHOTO_SCENE, SET_MSG_INTERVAL, opt->intervalType);
       opt->Image5M->set_main_bg_img_src(opt->LIST_CIRCLESEL_PNG);
       opt->photoplay_intervalMenu_del();
       opt->inDataLabel->set_txt((char*) intervaltName[opt->intervalType]);
       opt->mainMenuLabel->show(true);
    }
    else if(opt->effectList !=NULL)	
	{
        for(i=0;i<16;i++)
        {
            if(target == opt->effectmenuList.Menulist[i]->Label->myobj)
            {
                opt->effectType=i;
				write_int_type_param(PHOTO_SCENE, SET_MSG_EFFECT, opt->effectType);
				if(opt->effectList != NULL)
					opt->photoplay_effectMenu_del();
				else
					break;
				if(opt->efDataLabel !=NULL)
                	opt->efDataLabel->set_txt((char*) effectName[opt->effectType]);
				else
					break;
				if(opt->mainMenuLabel !=NULL)
					opt->mainMenuLabel->show(true);
				else
					break;
                break;
            }
        }
    }
}

void photoPlaying::photoplay_InfoMenu_creat(void)
{
	char *fileName =NULL;
    char buff[1024]={0};
	char fileBuff[128]={0};
	char line='/';

    InfoMenuButton = new LvcppButton(mainscreen);
    InfoMenuButton->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    InfoMenuButton->set_main_bg_color(lv_color_black(),LV_OPA_60);
    InfoMenuButton->add_event_cb(photoplay_InfoMenu_event_handler,LV_EVENT_CLICKED,this);

    InfoMenuLabel = new LvcppLabel(InfoMenuButton->myobj);
    InfoMenuLabel->set_size(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/3);
    InfoMenuLabel->center_align();
    InfoMenuLabel->set_main_bg_color(lv_color_black(),LV_OPA_60);
    InfoMenuLabel->set_main_border_width(1);
    InfoMenuLabel->set_main_border_color(lv_color_white());
    InfoMenuLabel->set_main_radius(10);
    InfoMenuLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
    InfoMenuLabel->set_txt("");

    FlieLabel =new LvcppLabel(InfoMenuLabel->myobj);
    FlieLabel->set_size(SCREEN_HOR_SIZE/2-10,SCREEN_VER_SIZE/12);
    FlieLabel->align(LV_ALIGN_TOP_MID,0,0);
    FlieLabel->set_main_bg_color(lv_color_black(),LV_OPA_60);
    FlieLabel->txt_font_size(34, FT_FONT_STYLE_NORMAL);
    FlieLabel->txt_align(LV_TEXT_ALIGN_CENTER);
    FlieLabel->txt_color(lv_color_white(),LV_PART_MAIN);
    memset(buff,0,1024);
	if(image_mgr.file_path !=NULL)
	{
		fileName = media_get_path_to_name(image_mgr.file_path);
		if(fileName !=NULL)
			strcpy(buff,fileName);
	}
    FlieLabel->set_txt(buff);
    FlieLabel->set_main_pad_T_B(5,0);
    FlieLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);

    InfoLineLabel =new LvcppLabel(InfoMenuLabel->myobj);
    InfoLineLabel->set_size(SCREEN_HOR_SIZE/2,1);
    InfoLineLabel->set_main_bg_color(lv_color_white(),LV_OPA_100);
    InfoLineLabel->align(LV_ALIGN_TOP_LEFT,0,SCREEN_VER_SIZE/12);
    InfoLineLabel->set_txt("");

    PatchLabel =new LvcppLabel(InfoMenuLabel->myobj);
    PatchLabel->set_size(SCREEN_HOR_SIZE/2-10,SCREEN_VER_SIZE/24);
    PatchLabel->align(LV_ALIGN_TOP_LEFT,0,SCREEN_VER_SIZE/12+1);
    PatchLabel->set_main_bg_color(lv_color_black(),LV_OPA_60);
    PatchLabel->txt_font_size(24, FT_FONT_STYLE_NORMAL);
    PatchLabel->txt_align(LV_TEXT_ALIGN_LEFT);
    PatchLabel->txt_color(lv_color_white(),LV_PART_MAIN);
    PatchLabel->set_main_pad_L_R(10,0);
    memset(buff,0,1024);
	memset(fileBuff,0,128);
	if(image_mgr.file_path !=NULL)
	{
		fileName = media_get_path_to_name(image_mgr.file_path);
		if(fileName !=NULL)
		{
			memcpy(fileBuff,image_mgr.file_path,(strlen(image_mgr.file_path)-strlen(fileName)));
		}
		sprintf(buff,"%s:%s",STR_PATH,fileBuff);
	}
	else
	{
		sprintf(buff,"%s:",STR_PATH);
	}
    
    PatchLabel->set_txt(buff);
    PatchLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);

    FlieNameLabel =new LvcppLabel(InfoMenuLabel->myobj);
    FlieNameLabel->set_size(SCREEN_HOR_SIZE/2-10,SCREEN_VER_SIZE/24);
    FlieNameLabel->align(LV_ALIGN_TOP_LEFT,0,SCREEN_VER_SIZE/8);
    FlieNameLabel->set_main_bg_color(lv_color_black(),LV_OPA_60);
    FlieNameLabel->txt_font_size(24, FT_FONT_STYLE_NORMAL);
    FlieNameLabel->txt_align(LV_TEXT_ALIGN_LEFT);
    FlieNameLabel->txt_color(lv_color_white(),LV_PART_MAIN);
    FlieNameLabel->set_main_pad_L_R(10,0);
    memset(buff,0,1024);
    if(image_mgr.file_path !=NULL)
	{
		fileName = media_get_path_to_name(image_mgr.file_path);
		if(fileName !=NULL)
			strcpy(buff,fileName);
	}
    FlieNameLabel->set_txt(buff);
    FlieNameLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);

    FlieSizeLabel =new LvcppLabel(InfoMenuLabel->myobj);
    FlieSizeLabel->set_size(SCREEN_HOR_SIZE/2-10,SCREEN_VER_SIZE/24);
    FlieSizeLabel->align(LV_ALIGN_TOP_LEFT,0,SCREEN_VER_SIZE/25*5);
    FlieSizeLabel->set_main_bg_color(lv_color_black(),LV_OPA_60);
    FlieSizeLabel->txt_font_size(24, FT_FONT_STYLE_NORMAL);
    FlieSizeLabel->txt_align(LV_TEXT_ALIGN_LEFT);
    FlieSizeLabel->txt_color(lv_color_white(),LV_PART_MAIN);
    FlieSizeLabel->set_main_pad_L_R(10,0);
    memset(buff,0,1024);
	memset(fileBuff,0,128);
	if(image_mgr.file_path != NULL)
    {
		_get_file_size(image_mgr.file_path,fileBuff);
	}
	sprintf(buff,"%s:%s",STR_SIZE,fileBuff);
    FlieSizeLabel->set_txt(buff);
    FlieSizeLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);

    FlieTimeLabel =new LvcppLabel(InfoMenuLabel->myobj);
    FlieTimeLabel->set_size(SCREEN_HOR_SIZE/2-10,SCREEN_VER_SIZE/24);
    FlieTimeLabel->align(LV_ALIGN_TOP_LEFT,0,SCREEN_VER_SIZE/25*7);
    FlieTimeLabel->set_main_bg_color(lv_color_black(),LV_OPA_60);
    FlieTimeLabel->txt_font_size(24, FT_FONT_STYLE_NORMAL);
    FlieTimeLabel->txt_align(LV_TEXT_ALIGN_LEFT);
    FlieTimeLabel->txt_color(lv_color_white(),LV_PART_MAIN);
    FlieTimeLabel->set_main_pad_L_R(10,0);
    memset(buff,0,1024);
	memset(fileBuff,0,128);
	if(image_mgr.file_path != NULL)
    {
		_get_file_time(image_mgr.file_path,fileBuff);
	}
	sprintf(buff,"%s:%s",STR_DATE,fileBuff);
    FlieTimeLabel->set_txt(buff);
    FlieTimeLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
}

void photoPlaying::photoplay_InfoMenu_del(void)
{
    if(FlieTimeLabel != NULL)
    {
        delete FlieTimeLabel;
        FlieTimeLabel =NULL;
    }
    if(FlieSizeLabel != NULL)
    {
        delete FlieSizeLabel;
        FlieSizeLabel =NULL;
    }
    if(FlieNameLabel != NULL)
    {
        delete FlieNameLabel;
        FlieNameLabel =NULL;
    }
    if(PatchLabel != NULL)
    {
        delete PatchLabel;
        PatchLabel =NULL;
    }
    if(InfoLineLabel != NULL)
    {
        delete InfoLineLabel;
        InfoLineLabel =NULL;
    }
    if(FlieLabel != NULL)
    {
        delete FlieLabel;
        FlieLabel =NULL;
    }
    if(InfoMenuLabel != NULL)
    {
        delete InfoMenuLabel;
        InfoMenuLabel =NULL;
    }
    if(InfoMenuButton != NULL)
    {
        delete InfoMenuButton;
        InfoMenuButton =NULL;
    }
}

void photoPlaying::photoplay_InfoMenu_event_handler(lv_event_t *event)
{
    photoPlaying* opt = (photoPlaying*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
	
	opt->timecntback =0;
    if(target==opt->InfoMenuButton->myobj)
    {
        opt->photoplay_InfoMenu_del();
    }
}

void photoPlaying::photoplay_caption_creat(void)
{
    char buff[1024]={0};

    CapLabel = new LvcppLabel(mainscreen);
    CapLabel->set_size(70,70);
    CapLabel->set_main_bg_img_src(PHOTO_ROUND_PNG);
    CapLabel->align(LV_ALIGN_BOTTOM_LEFT,20,-20);
    CapLabel->set_txt("");

    CaIconLabel= new LvcppLabel(mainscreen);
    CaIconLabel->set_size(1040,50);
    CaIconLabel->set_main_bg_color(lv_color_white(),LV_OPA_30);
    CaIconLabel->set_main_radius(10);
    CaIconLabel->align(LV_ALIGN_BOTTOM_LEFT,110,-30);
    CaIconLabel->txt_font_size(22, FT_FONT_STYLE_NORMAL);
    CaIconLabel->txt_align(LV_TEXT_ALIGN_LEFT);
    CaIconLabel->txt_color(lv_color_black(),LV_PART_MAIN);
    CaIconLabel->set_main_pad_T_B(14,0);
    CaIconLabel->set_main_pad_L_R(20,0);
	if(image_mgr.file_path != NULL)
    {
		_get_file_time(image_mgr.file_path,buff);
	}
    CaIconLabel->set_txt(buff);

    CaTimeLabel = new LvcppLabel(mainscreen);
    CaTimeLabel->set_size(100,40);
    CaTimeLabel->set_main_bg_color(lv_color_white(),LV_OPA_0);
    CaTimeLabel->align(LV_ALIGN_BOTTOM_RIGHT,-15,-80);
    CaTimeLabel->txt_font_size(36, FT_FONT_STYLE_NORMAL);
    CaTimeLabel->txt_align(LV_TEXT_ALIGN_CENTER);
    CaTimeLabel->txt_color(lv_color_white(),LV_PART_MAIN);
    memset(buff,0,1024);
    sprintf(buff,"%.2d:%.2d",user_time.hour,user_time.minute);
    CaTimeLabel->set_txt(buff);

    CaDateLabel = new LvcppLabel(mainscreen);
    CaDateLabel->set_size(100,24);
    CaDateLabel->set_main_bg_color(lv_color_white(),LV_OPA_0);
    CaDateLabel->align(LV_ALIGN_BOTTOM_RIGHT,-15,-50);
    CaDateLabel->txt_font_size(18, FT_FONT_STYLE_NORMAL);
    CaDateLabel->txt_align(LV_TEXT_ALIGN_CENTER);
    CaDateLabel->txt_color(lv_color_white(),LV_PART_MAIN);
    memset(buff,0,1024);
    sprintf(buff,"%.4d.%.2d.%.2d",user_time.year,user_time.month,user_time.day);
    CaDateLabel->set_txt(buff);

    CaWeekLabel = new LvcppLabel(mainscreen);
    CaWeekLabel->set_size(100,28);
    CaWeekLabel->set_main_bg_color(lv_color_white(),LV_OPA_0);
    CaWeekLabel->align(LV_ALIGN_BOTTOM_RIGHT,-15,-20);
    CaWeekLabel->txt_font_size(22, FT_FONT_STYLE_NORMAL);
    CaWeekLabel->txt_align(LV_TEXT_ALIGN_CENTER);
    CaWeekLabel->txt_color(lv_color_white(),LV_PART_MAIN);
    memset(buff,0,1024);
    sprintf(buff,"%s    %s",get_week_str(),get_apm_str());
    CaWeekLabel->set_txt(buff);
    photoplay_caption_show(captionType);
}

void photoPlaying::photoplay_caption_del(void)
{
    if(CaWeekLabel != NULL)
    {
        delete CaWeekLabel;
        CaWeekLabel =NULL;
    }
    if(CaDateLabel != NULL)
    {
        delete CaDateLabel;
        CaDateLabel =NULL;
    }
    if(CaTimeLabel != NULL)
    {
        delete CaTimeLabel;
        CaTimeLabel =NULL;
    }
    if(CaIconLabel != NULL)
    {
        delete CaIconLabel;
        CaIconLabel =NULL;
    }
    if(CapLabel != NULL)
    {
        delete CapLabel;
        CapLabel =NULL;
    }
}

char* photoPlaying::get_week_str(void)
{
    int y=0,m=0,d=0,w=0;

    y= user_time.year;
    m= user_time.month;
    d= user_time.day;
    w =(d+1+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;

    return (char*)weekName[w];
}

char* photoPlaying::get_apm_str(void)
{
    int apm=0;

    if(user_time.hour >=12)
        apm=1;

    return (char*)apmName[apm];
}

void photoPlaying::photoplay_caption_show(bool status)
{
    if(CaWeekLabel != NULL)
    {
        CaWeekLabel->show(status);
    }
    if(CaDateLabel != NULL)
    {
        CaDateLabel->show(status);
    }
    if(CaTimeLabel != NULL)
    {
        CaTimeLabel->show(status);
    }
    if(CaIconLabel != NULL)
    {
        CaIconLabel->show(status);
    }
    if(CapLabel != NULL)
    {
        CapLabel->show(status);
    }
}

void photoPlaying::photoplay_caption_updata(void)
{
    char buff[1024]={0};

    if(CaWeekLabel != NULL)
    {
        memset(buff,0,1024);
        sprintf(buff,"%s    %s",get_week_str(),get_apm_str());
        CaWeekLabel->set_txt(buff);
    }
    if(CaDateLabel != NULL)
    {
        memset(buff,0,1024);
        sprintf(buff,"%.4d.%.2d.%.2d",user_time.year,user_time.month,user_time.day);
        CaDateLabel->set_txt(buff);
    }
    if(CaTimeLabel != NULL)
    {
        memset(buff,0,1024);
        sprintf(buff,"%.2d:%.2d",user_time.hour,user_time.minute);
        CaTimeLabel->set_txt(buff);
    }
}

void photoPlaying::photoplay_rm_CurFile(void)
{
    char buff[1024]={0};
	int file_index =0;
	
	if(media_file_list ==NULL)
		return;
    file_index = (image_mgr.file_index + 1) % image_mgr.file_total_num;
	memset(buff,0,1024);
	image_mgr.file_path = media_get_file_path(media_file_list,image_mgr.file_index);
	sprintf(buff,"rm -r %s",image_mgr.file_path);
	image_mgr.file_path = media_get_file_path(media_file_list,file_index);
	if(file_index !=0)
	{
		file_index = image_mgr.file_index;
	}
	system(buff);
	system("sync");
	image_play_scan(image_mgr.file_path);
	image_effect_show(image_mgr.file_path, IMAGE_SHOW_NORMAL);
}


