#ifndef __MEDIA_MIXTURE_H__
#define __MEDIA_MIXTURE_H__

#include <pthread.h>
#include "lvgl/lvgl.h"
#include "player_int.h"
#include "media_load_file.h"
#include "DiskManager.h"
#include "rat_npl.h"

#ifdef _UCHIP_T113
#include "Vp_image.h"
#endif

#define FILE_NAME_LEN 128
#define FILE_PATH_LEN 512

typedef struct play_info_t
{
	char                root_path[MOUNT_PATH_MAX_LENGTH];
	char				filename[FILE_NAME_LEN];
	char				path[FILE_PATH_LEN];
	rat_media_type_t	fileType;
	int					index;
	int					time;
	int					offset;
	int					nDurationSec;
} play_info_t;

typedef struct media_cfg_t
{
	int loop;
	int volume;
	rat_play_mode_e play_mode;
} media_cfg_t;

typedef enum{
	MEDIA_IDLE_EVENT = 0,
	MEDIA_PREPARE_EVENT = 1,
	MEDIA_PLAY_EVENT = 2,
	MEDIA_PAUSE_EVENT = 3,
	MEDIA_STOP_EVENT = 4,
	MEDIA_SET_VOLUME_EVENT = 5,
	MEDIA_SEEKTO_EVENT = 6,
	MEDIA_PLAY_COMPLETE_EVENT = 7,
	MEDIA_SET_AUDIO_EQ = 8,
	MEDIA_SET_LOOP = 9,
	MEDIA_SET_ROTATE = 10,
	MEDIA_SET_ERROR = 11,
} media_event_t;

typedef void (*media_ui_callback)(void *ui_player, media_event_t event, void *param);

typedef struct media_event_param_t{
	media_event_t event;
	long int param[2];
}media_event_param_t;

typedef struct PLAYER_UI_T{
	lv_timer_t *		lv_task;
	player_t			*tplayer;

	media_ui_callback	callback;

	//ui event
	db_list_t*			event_head;
	media_event_param_t	event_param;

	//the info of media be playing
	char				scene_name[64];
	play_info_t			play_info;
}player_ui_t;

player_ui_t * media_init(void);
void media_uninit(player_ui_t *player_ui);
player_ui_t *media_get_player_data(void);

void media_func_register(char *player_name, media_ui_callback callback);
void media_func_unregister(char *player_name, bool en_back);

void media_ui_send_event(media_event_t event, void *param0, int param1);
#endif
