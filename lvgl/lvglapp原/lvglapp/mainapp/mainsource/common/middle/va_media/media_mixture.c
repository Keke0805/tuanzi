#include <pthread.h>
#include "player_int.h"
#include "media_load_file.h"
#include "media_mixture.h"
#include "DiskManager.h"
#include "rat_npl.h"
#include "media_spectrum.h"
#include "common.h"
#include "app_config_interface.h"


#define PRINT_ZXF 1
#if PRINT_ZXF
#define print_zxf(format, arg...)		printf("<***mixture***>%s,%d,"format"\n",__FILE__,__LINE__, ## arg);
#else
#define print_zxf(format, arg...)		do {} while (0)
#endif

#define		LOCK
#ifdef LOCK
#define	MUTEX_LOCK(mtx)			if(pthread_mutex_lock(&mtx)){\
									printf("%s:%d mutex lock fail\n",__func__,__LINE__);\
								}
#define	MUTEX_UNLOCK(mtx)		if(pthread_mutex_unlock(&mtx)){\
									printf("%s:%d mutex unlock fail\n",__func__,__LINE__);\
								}
#else
#define MUTEX_LOCK(mtx)
#define MUTEX_UNLOCK(mtx)
#endif
#define ISNULL(x) if(!x){return 0;}
enum {
	BREAKPOINT_SCENE_MUSIC = 0,
	BREAKPOINT_SCENE_MOVIE,
	BREAKPOINT_PLAY_SCENE_NUM
};
enum {
	AUTO_PLAY_SCENE_MUSIC = 0,
	AUTO_PLAY_SCENE_MOVIE,
	AUTO_PLAY_SCENE_PICTURE,
	AUTO_PLAY_SCENE_NUM
};
	
#ifdef _UCHIP_T113
void file_size_int_to_string(long int size_int, char *size_str)
{
	char *unit[5] = {"B", "KB", "MB", "GM", "TB"};
	unsigned char convert_count = 0;
	int long num;
	char num_string[10];
	int point;

	num = size_int;
	while (num /= 1000)
		convert_count++;

	memset(num_string, 0, sizeof(num_string));
	sprintf (num_string, "%ld", size_int);
	point = strlen(num_string) - (convert_count * 3);
	strncpy(size_str, num_string, point);
	strncat(size_str, ". ", 1);
	strncat(size_str, num_string+point, 1);
	strcat(size_str, unit[convert_count]);
}
void time_int_to_string(unsigned int int_time, char *time_str)
{
	int hours, minutes, second;

	second = int_time;
	minutes = second / 60;
	hours = minutes / 60;
	sprintf(time_str, "%02d:%02d:%02d", hours % 24, minutes % 60, second % 60);
}

static int media_tplayer_callback(void* pUserData, int msg, int param0, void* param1)
{
	//player_context_t* pPlayer = (player_context_t*)pUserData;
	player_ui_t *player_ui = media_get_player_data();
	int video_width;
	int video_height;
	switch(msg){
		case TPLAYER_NOTIFY_PREPARED:
				media_ui_send_event(MEDIA_PREPARE_EVENT, NULL, 0);
			break;
		case TPLAYER_NOTIFY_PLAYBACK_COMPLETE:
				media_ui_send_event(MEDIA_PLAY_COMPLETE_EVENT, NULL, 0);
			break;
		case TPLAYER_NOTIFY_MEDIA_ERROR:
			break;
		case TPLAYER_NOTIFY_AUDIO_FRAME:
			if(player_ui->play_info.fileType == RAT_MEDIA_TYPE_AUDIO){
				media_spectrum_init((AudioPcmData *)param1);
			}
			break;
		case TPLAYER_NOTIFY_MEDIA_VIDEO_SIZE:
		    if (STOP_STATUS == tplayer_get_status(player_ui->tplayer))
		    {
                video_width = ((int *)param1)[0];
                video_height = ((int *)param1)[1];
                com_info("width = %d height = %d\r\n", video_width, video_height);
                if (video_width > 1280 && video_height > 720)
                {
                    com_info("more than 720P\r\n");
                    player_ui->callback(player_ui, MEDIA_SET_ERROR, 0);
                }
		    }
			break;
		default:
			break;
	}
	
	return 0;
}

void media_ui_send_event(media_event_t event, void *param0, int param1)
{
	player_ui_t *player_ui = media_get_player_data();

	media_event_param_t *event_param = malloc(sizeof(media_event_param_t));
	event_param->event = event;
	event_param->param[0] = (long int)param0;
	event_param->param[1] = param1;
	__db_list_put_tail(player_ui->event_head, event_param);
	com_info("media ui send event = %d ", event_param->event);
}


static void media_ui_task(struct _lv_timer_t *param)
{
	
	player_ui_t *player_ui = (player_ui_t *)param->user_data;
	media_event_param_t *event_param = NULL;
	DiskInfo_t *disk_info;

	/*default event MEDIA_IDLE_EVENT, so when event_head is empty do not return*/
	event_param = (struct media_event_param_t *)__db_list_pop(player_ui->event_head);
	if (NULL != event_param) {
		memset(&player_ui->event_param, 0x00, sizeof(struct media_event_param_t));
		memcpy(&player_ui->event_param, event_param, sizeof(struct media_event_param_t));
		free(event_param);
		com_info("media ui get event = %d ", player_ui->event_param.event);
	}

	switch(player_ui->event_param.event){
		case MEDIA_IDLE_EVENT:
        {
            if (tplayer_get_status(player_ui->tplayer) == PLAY_STATUS)
            {
                tplayer_get_current_pos(player_ui->tplayer, &player_ui->play_info.time);
                player_ui->play_info.nDurationSec = (player_ui->tplayer->mMediaInfo->nDurationMs) / 1000;
            }
        break;
        }
		case MEDIA_PREPARE_EVENT:
        {
            media_ui_send_event(MEDIA_IDLE_EVENT, NULL, 0);

        break;
        }
		case MEDIA_PLAY_EVENT:
        {
            tplayer_play(player_ui->tplayer);
            media_ui_send_event(MEDIA_IDLE_EVENT, NULL, 0);

        break;
        }
		case MEDIA_PAUSE_EVENT:
        {
            tplayer_pause(player_ui->tplayer);
            media_ui_send_event(MEDIA_IDLE_EVENT, NULL, 0);
        break;
        }
		case MEDIA_STOP_EVENT:
        {
            tplayer_stop(player_ui->tplayer);
            media_ui_send_event(MEDIA_IDLE_EVENT, NULL, 0);
        break;
        }
		case MEDIA_SET_VOLUME_EVENT:
        {
            tplayer_volume(player_ui->tplayer, player_ui->event_param.param[1]); 
            media_ui_send_event(MEDIA_IDLE_EVENT, NULL, 0);
        break;
        }
		case MEDIA_SEEKTO_EVENT:
        {
            tplayer_seekto(player_ui->tplayer, player_ui->event_param.param[1]);
            if(tplayer_get_status(player_ui->tplayer) == SEEKTO_STATUS)
            {
                media_ui_send_event(MEDIA_IDLE_EVENT, NULL, 0);
            }
        break;
        }
		case MEDIA_PLAY_COMPLETE_EVENT:
		{
			media_ui_send_event(MEDIA_IDLE_EVENT, NULL, 0);
		break;
		}
		case MEDIA_SET_AUDIO_EQ:
        {
            tplayer_set_audio_eq(player_ui->tplayer, player_ui->event_param.param[1]);
			media_ui_send_event(MEDIA_IDLE_EVENT, NULL, 0);
        break;
        }
		case MEDIA_SET_LOOP:
		{
			tplayer_set_looping(player_ui->tplayer, (bool)player_ui->event_param.param[1]);
			media_ui_send_event(MEDIA_IDLE_EVENT, NULL, 0);
		break;
		}
		case MEDIA_SET_ROTATE:
		{
			tplayer_set_rotate(player_ui->tplayer, player_ui->event_param.param[1]);
			media_ui_send_event(MEDIA_IDLE_EVENT, NULL, 0);
		break;
		}
		default:
        {
        break;
        }
	}
	
	if(player_ui->callback){
		player_ui->callback(param->user_data, player_ui->event_param.event, (void *)player_ui->event_param.param);
	}
	

}

static player_ui_t *player_data;

player_ui_t *media_get_player_data(void)
{
	return player_data;
}

player_ui_t *media_init(void)
{
	player_ui_t *player_ui;

	player_ui = (player_ui_t *)malloc(sizeof(player_ui_t));
	if(player_ui == NULL){
		com_err("player_ui malloc failed!\r\n");
		goto end;
	}
	player_data = player_ui;
	
	memset(player_ui, 0, sizeof(player_ui_t));
	player_ui->tplayer = tplayer_pthread_create();
	if(!player_ui->tplayer){
		com_err("tplayer create failed!\r\n");
		goto end;
	}
    tplayer_set_callback(player_ui->tplayer, media_tplayer_callback);
	
	player_ui->event_head = db_list_create("media_event", 0);
	if (!player_ui->event_head) {
		com_err("event head create failed!\r\n");
		goto end;
	}

	player_ui->lv_task = lv_timer_create(media_ui_task, 30, (void *)player_ui);

	if(!player_ui->lv_task){
		com_err("lv timer create failed!\r\n");
		goto end;
	}
end:
	return player_ui;
}

void media_uninit(player_ui_t *player_ui)
{
	lv_timer_del(player_ui->lv_task);
	tplayer_pthread_destory(player_ui->tplayer);
	__db_list_destory(player_ui->event_head);
	free(player_ui);
	player_data = NULL;
}

void media_func_register(char *player_name, media_ui_callback callback)
{
    int player_type = 0;
	player_ui_t *player_ui = media_get_player_data();
	memcpy(player_ui->scene_name, player_name, strlen(player_name));
	if (0 == strcmp(player_name, "MOVIE_SCENE"))
	{
        player_type = CEDARX_PLAYER;
	}
	else if (0 == strcmp(player_name, "MUSIC_SCENE"))
	{
        player_type = AUDIO_PLAYER;
	}
	player_ui->callback = callback;
	tplayer_init(player_ui->tplayer, player_type);
}

//en_back : 1: support play in backstage
void media_func_unregister(char *player_name, bool en_back)
{
	player_ui_t *player_ui = media_get_player_data();
	if(strcmp(player_ui->scene_name, player_name) == 0){
		player_ui->callback = NULL;
		media_spectrum_destroy();
		if (!en_back) {
			tplayer_exit(player_ui->tplayer);
			memset(&player_ui->play_info, 0x00, sizeof(play_info_t));
			memset(player_ui->scene_name, 0, sizeof(player_ui->scene_name));
		}
	}
}
#endif
