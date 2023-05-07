#include  "../mainappstart.h"
#include "music.h"
#include  "lvgl/src/extra/lv_extra.h"
#include  "mainstart/include/ui_config.h"
#include  "mainstart/include/str_config.h"

#ifdef IMAGE_DECODE
static const void  *iconName[4]={STR_FLASH_ALL,STR_FLASH_INTER,STR_FLASH_SD,STR_FLASH_USB};
#else
static const void  *iconPatch[2]={LIST_UNSEL_PNG,LIST_SEL_PNG};
static const void  *iconPatchMain[4]={LIST_ICON_ALL_PNG,LIST_ICON_FLASH_PNG,LIST_ICON_SD_PNG,LIST_ICON_U_PNG};
static const void  *iconName[4]={STR_FLASH_ALL,STR_FLASH_INTER,STR_FLASH_SD,STR_FLASH_USB};
#endif
static int timecnt = 0;
static media_file_list_t *media_file_list = NULL;
static bool finishStatus =false;
void musicList::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    HEAD_RETURN_PNG=(void*)parse_image_from_file(HEAD_RETURN_PNG_PATH);
    HEAD_RETURN_SEL_PNG=(void*)parse_image_from_file(HEAD_RETURN_SEL_PNG_PATH);
    HEAD_ICON_MUSIC_PNG=(void*)parse_image_from_file(HEAD_ICON_MUSIC_PNG_PATH);
	LISTBG_PNG=(void*)parse_image_from_file(LISTBG_PNG_PATH);
    LIST_ICON_ALL_PNG=(void*)parse_image_from_file(LIST_ICON_ALL_PNG_PATH);
    LIST_ICON_FLASH_PNG=(void*)parse_image_from_file(LIST_ICON_FLASH_PNG_PATH);
    LIST_ICON_SD_PNG=(void*)parse_image_from_file(LIST_ICON_SD_PNG_PATH);
    LIST_ICON_U_PNG=(void*)parse_image_from_file(LIST_ICON_U_PNG_PATH);
    LIST_ICON_FILE_PNG=(void*)parse_image_from_file(LIST_ICON_FILE_PNG_PATH);
    LIST_ICON_LOVE_PNG=(void*)parse_image_from_file(LIST_ICON_LOVE_PNG_PATH);
    LIST_ICON_USER_PNG=(void*)parse_image_from_file(LIST_ICON_USER_PNG_PATH);
    LIST_ICON_LINE_PNG=(void*)parse_image_from_file(LIST_ICON_LINE_PNG_PATH);
    LIST_ICON_UNDEL_PNG=(void*)parse_image_from_file(LIST_ICON_UNDEL_PNG_PATH);
    LIST_ICON_DEL_PNG=(void*)parse_image_from_file(LIST_ICON_DEL_PNG_PATH);
    LIST_ICON_DELSEL_PNG=(void*)parse_image_from_file(LIST_ICON_DELSEL_PNG_PATH);
    LIST_ICON_NOR_PNG=(void*)parse_image_from_file(LIST_ICON_NOR_PNG_PATH);
    LIST_ICON_NORSEL_PNG=(void*)parse_image_from_file(LIST_ICON_NORSEL_PNG_PATH);
    LIST_ICON_CHE_PNG=(void*)parse_image_from_file(LIST_ICON_CHE_PNG_PATH);
    LIST_ICON_CHELSEL_PNG=(void*)parse_image_from_file(LIST_ICON_CHELSEL_PNG_PATH);
    LIST_ICON_CAN_PNG=(void*)parse_image_from_file(LIST_ICON_CAN_PNG_PATH);
    LIST_ICON_CANLSEL_PNG=(void*)parse_image_from_file(LIST_ICON_CANLSEL_PNG_PATH);
    LIST_ICON_ICON_PNG=(void*)parse_image_from_file(LIST_ICON_ICON_PNG_PATH);
    LIST_ICON_ICONLSEL_PNG=(void*)parse_image_from_file(LIST_ICON_ICONLSEL_PNG_PATH);
    LIST_SEL_PNG=(void*)parse_image_from_file(LIST_SEL_PNG_PATH);
    LIST_UNSEL_PNG=(void*)parse_image_from_file(LIST_UNSEL_PNG_PATH);
    LIST_ICON_VIDEOLINE_PNG=(void*)parse_image_from_file(LIST_ICON_VIDEOLINE_PNG_PATH);
    LIST_COPY_PNG=(void*)parse_image_from_file(LIST_COPY_PNG_PATH);
    LIST_COPY_SEL_PNG=(void*)parse_image_from_file(LIST_COPY_SEL_PNG_PATH);
    LIST_UNCOPY_PNG=(void*)parse_image_from_file(LIST_UNCOPY_PNG_PATH);
    LIST_SORT_PNG=(void*)parse_image_from_file(LIST_SORT_PNG_PATH);
    LIST_SORT_SEL_PNG=(void*)parse_image_from_file(LIST_SORT_SEL_PNG_PATH);
	LIST_CIRCLE_PNG=(void*)parse_image_from_file(LIST_CIRCLE_PNG_PATH);
	LIST_CIRCLESEL_PNG=(void*)parse_image_from_file(LIST_CIRCLESEL_PNG_PATH);

    MUSIC_ICONCD_PNG=(void*)parse_image_from_file(MUSIC_ICONCD_PNG_PATH);
    MUSIC_UNPLAY_PNG=(void*)parse_image_from_file(MUSIC_UNPLAY_PNG_PATH);
    MUSIC_PLAY_PNG=(void*)parse_image_from_file(MUSIC_PLAY_PNG_PATH);
    MUSIC_UNSTOP_PNG=(void*)parse_image_from_file(MUSIC_UNSTOP_PNG_PATH);
    MUSIC_STOP_PNG=(void*)parse_image_from_file(MUSIC_STOP_PNG_PATH);
    MUSIC_UNPREV_PNG=(void*)parse_image_from_file(MUSIC_UNPREV_PNG_PATH);
    MUSIC_PREV_PNG=(void*)parse_image_from_file(MUSIC_PREV_PNG_PATH);
    MUSIC_UNNEXT_PNG=(void*)parse_image_from_file(MUSIC_UNNEXT_PNG_PATH);
    MUSIC_NEXT_PNG=(void*)parse_image_from_file(MUSIC_NEXT_PNG_PATH);
    MUSIC_UNSINGLE_PNG=(void*)parse_image_from_file(MUSIC_UNSINGLE_PNG_PATH);
    MUSIC_SINGLE_PNG=(void*)parse_image_from_file(MUSIC_SINGLE_PNG_PATH);
    MUSIC_UNSHUFFLE_PNG=(void*)parse_image_from_file(MUSIC_UNSHUFFLE_PNG_PATH);
    MUSIC_SHUFFLE_PNG=(void*)parse_image_from_file(MUSIC_SHUFFLE_PNG_PATH);
    MUSIC_UNLOOP_PNG=(void*)parse_image_from_file(MUSIC_UNLOOP_PNG_PATH);
    MUSIC_LOOP_PNG=(void*)parse_image_from_file(MUSIC_LOOP_PNG_PATH);
    MUSIC_VOLDOT_PNG=(void*)parse_image_from_file(MUSIC_VOLDOT_PNG_PATH);
    MUSIC_VOLICON_PNG=(void*)parse_image_from_file(MUSIC_VOLICON_PNG_PATH);
    MUSIC_VOLBG_PNG=(void*)parse_image_from_file(MUSIC_VOLBG_PNG_PATH);
    MUSIC_TIME_BG_PNG=(void*)parse_image_from_file(MUSIC_TIME_BG_PNG_PATH);
    MUSIC_TIMESEL_BG_PNG=(void*)parse_image_from_file(MUSIC_TIMESEL_BG_PNG_PATH);
    MUSIC_TIMECUR_PNG=(void*)parse_image_from_file(MUSIC_TIMECUR_PNG_PATH);

#endif

}
void musicList::ui_image_free(void)
{
#ifdef IMAGE_DECODE
    free_image(HEAD_RETURN_PNG);
    free_image(HEAD_RETURN_SEL_PNG);
    free_image(HEAD_ICON_MUSIC_PNG);
	free_image(LISTBG_PNG);
    free_image(LIST_ICON_ALL_PNG);
    free_image(LIST_ICON_FLASH_PNG);
    free_image(LIST_ICON_SD_PNG);
    free_image(LIST_ICON_U_PNG);
    free_image(LIST_ICON_FILE_PNG);
    free_image(LIST_ICON_LOVE_PNG);
    free_image(LIST_ICON_USER_PNG);
    free_image(LIST_ICON_LINE_PNG);
    free_image(LIST_ICON_UNDEL_PNG);
    free_image(LIST_ICON_DEL_PNG);
    free_image(LIST_ICON_DELSEL_PNG);
    free_image(LIST_ICON_NOR_PNG);
    free_image(LIST_ICON_NORSEL_PNG);
    free_image(LIST_ICON_CHE_PNG);
    free_image(LIST_ICON_CHELSEL_PNG);
    free_image(LIST_ICON_CAN_PNG);
    free_image(LIST_ICON_CANLSEL_PNG);
    free_image(LIST_ICON_ICON_PNG);
    free_image(LIST_ICON_ICONLSEL_PNG);
    free_image(LIST_SEL_PNG);
    free_image(LIST_UNSEL_PNG);
    free_image(LIST_ICON_VIDEOLINE_PNG);
    free_image(LIST_COPY_PNG);
    free_image(LIST_COPY_SEL_PNG);
    free_image(LIST_UNCOPY_PNG);
    free_image(LIST_SORT_PNG);
    free_image(LIST_SORT_SEL_PNG);
	free_image(LIST_CIRCLE_PNG);
	free_image(LIST_CIRCLESEL_PNG);
	
    free_image(MUSIC_ICONCD_PNG);
    free_image(MUSIC_UNPLAY_PNG);
    free_image(MUSIC_PLAY_PNG);
    free_image(MUSIC_UNSTOP_PNG);
    free_image(MUSIC_STOP_PNG);
    free_image(MUSIC_UNPREV_PNG);
    free_image(MUSIC_PREV_PNG);
    free_image(MUSIC_UNNEXT_PNG);
    free_image(MUSIC_NEXT_PNG);
    free_image(MUSIC_UNSINGLE_PNG);
    free_image(MUSIC_SINGLE_PNG);
    free_image(MUSIC_UNSHUFFLE_PNG);
    free_image(MUSIC_SHUFFLE_PNG);
    free_image(MUSIC_UNLOOP_PNG);
    free_image(MUSIC_LOOP_PNG);
    free_image(MUSIC_VOLDOT_PNG);
    free_image(MUSIC_VOLICON_PNG);
    free_image(MUSIC_VOLBG_PNG);
    free_image(MUSIC_TIME_BG_PNG);
    free_image(MUSIC_TIMESEL_BG_PNG);
    free_image(MUSIC_TIMECUR_PNG);

#endif

}

static off_t get_file_size(char *file_name)
{
	int ret;
	int fd = -1;
	struct stat file_stat;

	fd = open(file_name, O_RDONLY);
	if (fd == -1) {
		printf("Open file %s failed : %s\n", file_name, strerror(errno));
		return -1;
	}
	ret = fstat(fd, &file_stat);
	if (ret == -1) {
		printf("Get file %s stat failed:%s\n", file_name, strerror(errno));
		close(fd);
		return -1;
	}
	close(fd);
	return file_stat.st_size;
}

char *musicList::_get_cur_filelist_patch(int index)
{
	Mfile_info_t* tmp_list;
	tmp_list = SelFileList;

    while(tmp_list != NULL)
    {
		if(index == tmp_list->myindex)
		{
			return tmp_list->filePath;
		}
        tmp_list = tmp_list->next_list;
    }
	return NULL;
}

/*选择文件链表*/
void musicList::selfilelist_add_node(Mfile_info_t *node)
{
    Mfile_info_t *tmp_list;

    tmp_list = SelFileList;

    if(SelFileList == NULL)
    {
        SelFileList = node;
        SelFileList->next_list = NULL;
    }
    else
    {
        while(tmp_list->next_list != NULL)
        {
            tmp_list = tmp_list->next_list;
        }
        tmp_list->next_list = node;
        tmp_list->next_list->next_list = NULL;
    }
}
int musicList::_get_selfilelist_total(void)
{
    Mfile_info_t* tmp_list;
    int numTotal =0;

    tmp_list = SelFileList;

    while(tmp_list != NULL)
    {
        numTotal ++;
        tmp_list = tmp_list->next_list;
    }
    return numTotal;
}
void musicList::_del_selfilelist(void)
{
    Mfile_info_t* tmp_list;
	char *patch =NULL;
	char filePath[1024]={0};

    tmp_list = SelFileList;
    while(tmp_list != NULL)
    {
    	patch =_get_cur_filelist_patch(tmp_list->myindex);
    	if(patch !=NULL)
    	{
			memset(filePath,0,sizeof(filePath));
    		sprintf(filePath,"rm -r %s",patch);
			system(filePath);
			LV_LOG_USER("filePath:%s",filePath);
			system("sync");
		}
        tmp_list = tmp_list->next_list;
    }
    _destory_selfilelist();
}
void musicList::_cpy_selfilelist(void)
{
    Mfile_info_t* tmp_list;
	char patch[64]={0};
    char buff[1024]={0};
	char *filePath =NULL;
	off_t file_size =0;

    tmp_list = SelFileList;
	if(CpyType ==1)
	{
		strcpy(patch,SDCARD_PATCH);
	}
	else if(CpyType ==2)
	{
		strcpy(patch,UDISK_PATCH);
	}
	else
	{
		strcpy(patch,ROOT_PATCH);
	}
    while(tmp_list != NULL)
    {
    	filePath =_get_cur_filelist_patch(tmp_list->myindex);
    	if(filePath !=NULL)
    	{
    		file_size = get_file_size(filePath);
			sprintf(buff,"cp %s %s/",filePath,patch);
			LV_LOG_USER("buff:%s",buff);
        	system(buff);
			system("sync");
		}
        tmp_list = tmp_list->next_list;
    }
    _destory_selfilelist();
}
static Mfile_info_t *_del_selfilelist_curpatch_head(Mfile_info_t *head_list)
{
	Mfile_info_t *tmp_list;
	
	if(head_list ==NULL)
	{
		return NULL;
	}
	tmp_list = head_list->next_list;
	free(head_list);
	if(tmp_list ==NULL)
	{
		return NULL;
	}
	head_list = tmp_list;
	return head_list;
}
void musicList::_del_selfilelist_curpatch(int index)
{
    Mfile_info_t *tmp_list_prev;
    Mfile_info_t *tmp_list_last;

	if(SelFileList ==NULL)
	{
		return ;
	}
    tmp_list_prev = SelFileList;

	if(SelFileList->myindex == index)
	{
		SelFileList =_del_selfilelist_curpatch_head(SelFileList);
		return;
	}
    else
    {
        tmp_list_prev = SelFileList;
		tmp_list_last = SelFileList->next_list;
		while(tmp_list_last != NULL)
		{
			if(tmp_list_last->myindex==index)
			{
				tmp_list_prev->next_list = tmp_list_last->next_list;
				free(tmp_list_last);
				return;
			}
			else
			{
				tmp_list_prev =tmp_list_last;
				tmp_list_last = tmp_list_last->next_list;
			}
		}
    }
}

void musicList::_add_selfilelist(int index)
{
    Mfile_info_t* tmp_list;
	char patch[1024]={0};
	int ret =0;
	
	if(media_file_list != NULL)
	{
		ret = rat_npl_index2file(media_file_list->media_hrat, index, patch);
		if(ret == EPDK_OK)
		{
			tmp_list = (Mfile_info_t*)malloc(sizeof(Mfile_info_t));
		    memset(tmp_list,0,sizeof(Mfile_info_t));
			tmp_list->myindex =index;
		    sprintf(tmp_list->filePath,"%s",patch);
		    selfilelist_add_node(tmp_list);
		}
	}   
}
void musicList::_destory_selfilelist(void)
{
    Mfile_info_t * tmp_list_prev;
    Mfile_info_t * tmp_list_last;

    tmp_list_prev = SelFileList;
    while(tmp_list_prev != NULL)
    {
        tmp_list_last = tmp_list_prev->next_list;
        free(tmp_list_prev);
        tmp_list_prev = tmp_list_last;
    }
	checkedNum =0;
    SelFileList = NULL;
}

void musicList::_add_allfilelist(void)
{
	void *iconPatch[2]={LIST_UNSEL_PNG,LIST_SEL_PNG};
	int i =0;

	for(i=0;i<music_list_id.count;i++)
	{
		if(music_list_id.list_item[i]!=NULL)
		{
			music_list_id.list_item[i]->set_IconPtch(iconPatch[1]);
            music_list_id.list_item[i]->check_ok =true;
			_add_selfilelist(i);
		}
	}
	checkedNum = _get_selfilelist_total();
}

void musicList::check_disk_status(void)
{
	DiskInfo_t *disk_tmp = NULL;
	int count =0,i=0;
	
	SDEnter =false;
	UEnter =false;
	count = DiskManager_GetDiskNum();
	if(count <2)
		return;
	for(i = 0; i < count; i++) 
	{
		disk_tmp = DiskManager_GetDiskInfoByIndex(i);
		if(disk_tmp != NULL) 
		{
			if(disk_tmp->MediaType ==MEDIUM_USB_MASSSTORAGE)
			{
				UEnter =true;
			}
			else if(disk_tmp->MediaType ==MEDIUM_SD_CARD)
			{
				SDEnter =true;
			}
		}
	}
}
musicList::musicList(lv_obj_t* parent)
{
	if(myfont==nullptr)
	{
		myfont = new LvcppFreeTypeFont(26,0);
	}
	ui_image_decode();
    frame = new LvcppScreen(parent);
    frame->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    frame->set_main_bg_color(lv_color_black(),LV_OPA_0);
    frame->set_main_bg_img_src(LISTBG_PNG);
    mainscreen = frame->myobj;
    IconStation =false;
    IconCheck =false;
    startTimer(200, this);
    StartTimerShow =false;
    PlayerUiM = media_get_player_data();
	media_func_register(MUSIC_SCENE, media_player_ui_callback);
}

musicList::~musicList(void)
{
    StartTimerShow =false;
    music_list_head_dele();
    musicmian_list_dele();
    musicList_list_delete();
    music_Slider_delete();
	_destory_selfilelist();
	musiclist_del_mute_dele();
	musiclist_cpy_mute_dele();
    if(animCd !=NULL)
    {
        delete animCd;
        animCd =NULL;
    }
    if(frame !=NULL)
    {
        delete frame;
        frame =NULL;
        lv_obj_clear_flag(lv_scr_act(), LV_OBJ_FLAG_CLICKABLE);
    }
    if(musicShuffleList !=NULL)
    {
        delete musicShuffleList;
        musicShuffleList =NULL;
    }
	if(media_file_list!=NULL)
	{
		media_unload_file(media_file_list);
		media_file_list=NULL;
	}
	media_func_unregister(MUSIC_SCENE, 0);	
	ui_image_free();
	if(myfont!=nullptr)
	{
		delete myfont;
		myfont = nullptr;
	}
}

int musicList::init_parament(void)
{
	int val =0;
	read_int_type_param(PUBLIC_SCENE, VOLUME, (int *)&val);
	read_int_type_param(MUSIC_SCENE, LOOPMUSIC, (int *)&PlayMode);
	CurVol =(int)(val/4);
    music_list_head_creat();
	musicList_media_creat();
    music_list_creat();
    musicList_list_creat();
	music_Slider_creat();
    ImgCd_creat();
	music_list_start_playing();
    play_time_update();
    return 0;
}

void musicList::musiclist_del_mute_creat(void)
{
    delButton = new LvcppButton(mainscreen);
    delButton->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    delButton->set_main_bg_color(lv_color_black(),LV_OPA_60);
    delButton->add_event_cb(musiclist_del_event_handler,LV_EVENT_CLICKED,this);

    delChildLabel = new LvcppLabel(mainscreen);
    delChildLabel->set_size(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/6);
    delChildLabel->center_align();
    delChildLabel->set_main_bg_color(lv_color_white(),LV_OPA_100);
    delChildLabel->set_main_radius(10);
    delChildLabel->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    delChildLabel->txt_align(LV_TEXT_ALIGN_CENTER);
    delChildLabel->txt_color(lv_color_black(),LV_PART_MAIN);
	delChildLabel->set_main_pad_T_B(10,0);
    delChildLabel->set_txt(STR_DELSELFILE);
    delChildLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);

    delChildButtonLine = new LvcppLabel(delChildLabel->myobj);
    delChildButtonLine->set_size(SCREEN_HOR_SIZE/2,1);
    delChildButtonLine->center_align();
    delChildButtonLine->set_main_bg_color(MENU_BTN_COLOR,LV_OPA_100);

    delChildButtonCancel = new LvcppButton(delChildLabel->myobj);
    delChildButtonCancel->set_size(SCREEN_HOR_SIZE/4-20,SCREEN_VER_SIZE/12-10);
    delChildButtonCancel->align(LV_ALIGN_BOTTOM_LEFT,5,-5);
    delChildButtonCancel->set_main_radius(10);
    delChildButtonCancel->set_main_bg_color(TABLE_SETTING_COLOR,LV_OPA_100);
    delChildButtonCancel->add_event_cb(musiclist_del_event_handler,LV_EVENT_PRESSED,this);
    delChildButtonCancel->add_event_cb(musiclist_del_event_handler,LV_EVENT_RELEASED,this);
    delChildButtonCancel->txt_size(SCREEN_HOR_SIZE/4-20, SCREEN_VER_SIZE/12-10, LV_LABEL_LONG_WRAP);
    delChildButtonCancel->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    delChildButtonCancel->txt_center();
    delChildButtonCancel->txt_color(lv_color_white());
    delChildButtonCancel->add_txt(STR_CANCEL);

    delChildButtonOk = new LvcppButton(delChildLabel->myobj);
    delChildButtonOk->set_size(SCREEN_HOR_SIZE/4-20,SCREEN_VER_SIZE/12-10);
    delChildButtonOk->align(LV_ALIGN_BOTTOM_RIGHT,-5,-5);
    delChildButtonOk->set_main_radius(10);
    delChildButtonOk->set_main_bg_color(TABLE_SETTING_COLOR,LV_OPA_100);
    delChildButtonOk->add_event_cb(musiclist_del_event_handler,LV_EVENT_PRESSED,this);
    delChildButtonOk->add_event_cb(musiclist_del_event_handler,LV_EVENT_RELEASED,this);
    delChildButtonOk->txt_size(SCREEN_HOR_SIZE/4-20, SCREEN_VER_SIZE/12-10, LV_LABEL_LONG_WRAP);
    delChildButtonOk->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    delChildButtonOk->txt_center();
    delChildButtonOk->txt_color(lv_color_white());
    delChildButtonOk->add_txt(STR_OK);
}

void musicList::musiclist_del_mute_dele(void)
{
    if(delChildButtonOk != NULL)
    {
        delete delChildButtonOk;
        delChildButtonOk =NULL;
    }
    if(delChildButtonCancel != NULL)
    {
        delete delChildButtonCancel;
        delChildButtonCancel =NULL;
    }
    if(delChildButtonLine != NULL)
    {
        delete delChildButtonLine;
        delChildButtonLine =NULL;
    }
    if(delChildLabel != NULL)
    {
        delete delChildLabel;
        delChildLabel =NULL;
    }
    if(delButton != NULL)
    {
        delete delButton;
        delButton =NULL;
    }
}
void musicList::musiclist_del_event_handler(lv_event_t *event)
{
    musicList* opt = (musicList*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target==opt->delButton->myobj)
    {
        opt->musiclist_del_mute_dele();
        opt->draw_headlist();
    }
    else if(target==opt->delChildButtonCancel->myobj)
    {
        if(event->code == LV_EVENT_RELEASED)
        {
            opt->musiclist_del_mute_dele();
            opt->draw_headlist();
        }
    }
    else if(target==opt->delChildButtonOk->myobj)
    {
        if(event->code == LV_EVENT_RELEASED)
        {
            opt->musiclist_del_mute_dele();
			opt->IconCheck =false;
			opt->IconStation =false;
            opt->IconDel->show(false);
			opt->IconChe->show(false);
			opt->IconCpy->show(false);
			opt->IconSor->show(false);
            opt->StrIconNum->show(false);
            opt->_del_selfilelist();
            opt->draw_headlist();
			opt->musicList_list_delete();
			opt->musicList_media_creat();
			opt->musicList_list_creat();
        }
    }
}

void musicList::musiclist_cpy_mute_creat(void)
{
    cpyButton = new LvcppButton(mainscreen);
    cpyButton->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    cpyButton->set_main_bg_color(lv_color_black(),LV_OPA_60);
    cpyButton->add_event_cb(musiclist_cpy_event_handler,LV_EVENT_CLICKED,this);

    cpyChildLabel = new LvcppLabel(mainscreen);
    if(DiskShowType ==3)
    {
        cpyChildLabel->set_size(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/3);
    }
    else if(DiskShowType ==2)
    {
        cpyChildLabel->set_size(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/4);
    }
    else
    {
        cpyChildLabel->set_size(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/6);
    }
    cpyChildLabel->center_align();
    cpyChildLabel->set_main_bg_color(lv_color_white(),LV_OPA_100);
    cpyChildLabel->set_main_radius(10);
    cpyChildLabel->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    cpyChildLabel->txt_align(LV_TEXT_ALIGN_CENTER);
    cpyChildLabel->txt_color(lv_color_black(),LV_PART_MAIN);
	cpyChildLabel->set_main_pad_T_B(10,0);
    cpyChildLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
    if(DiskShowType ==1)
    {
    	CpyType =0;
        cpyChildLabel->set_txt(STR_IMPORTFILE);
    }
    else
    {
        cpyChildLabel->set_txt(STR_ROOTTOOUT);
    }
    cpyChildLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);

    if(DiskShowType !=1)
    {
        cpyChildButtonLine = new LvcppLabel(cpyChildLabel->myobj);
        cpyChildButtonLine->set_size(SCREEN_HOR_SIZE/2,1);
        cpyChildButtonLine->align(LV_ALIGN_TOP_MID,0,SCREEN_VER_SIZE/12);
        cpyChildButtonLine->set_main_bg_color(MENU_BTN_COLOR,LV_OPA_100);

        if(DiskShowType ==2)
        {
            cpyCheckBox1 = new LvcppLabel(cpyChildLabel->myobj);
            cpyCheckBox1->set_size(SCREEN_HOR_SIZE/2-30,SCREEN_VER_SIZE/12);
            cpyCheckBox1->align(LV_ALIGN_TOP_MID,0,SCREEN_VER_SIZE/12+2);
            cpyCheckBox1->set_main_bg_color(lv_color_white(),LV_OPA_100);
            cpyCheckBox1->txt_font_size(28, FT_FONT_STYLE_NORMAL);
            cpyCheckBox1->txt_align(LV_TEXT_ALIGN_LEFT);
            cpyCheckBox1->txt_color(lv_color_black(),LV_PART_MAIN);
			cpyCheckBox1->set_main_pad_T_B(8,0);
            if(SDEnter == true)
            {
                cpyCheckBox1->set_txt(STR_FLASH_SD);
				CpyType =1;
            }
            else
            {
                cpyCheckBox1->set_txt(STR_FLASH_USB);
				CpyType =2;
            }

			cpyChildLabel1 = new LvcppLabel(cpyCheckBox1->myobj);
            cpyChildLabel1->set_size(32,32);
            cpyChildLabel1->align(LV_ALIGN_RIGHT_MID,0,-8);
            cpyChildLabel1->set_main_bg_img_src(LIST_CIRCLESEL_PNG);
            cpyChildLabel1->txt_font_size(24, FT_FONT_STYLE_NORMAL);
            cpyChildLabel1->set_txt("");
        }
        else
        {
            cpyCheckBox1 = new LvcppLabel(cpyChildLabel->myobj);
            cpyCheckBox1->set_size(SCREEN_HOR_SIZE/2-30,SCREEN_VER_SIZE/12);
            cpyCheckBox1->align(LV_ALIGN_TOP_MID,0,SCREEN_VER_SIZE/12+2);
            cpyCheckBox1->set_main_bg_color(lv_color_white(),LV_OPA_100);
            cpyCheckBox1->txt_font_size(28, FT_FONT_STYLE_NORMAL);
            cpyCheckBox1->txt_align(LV_TEXT_ALIGN_LEFT);
            cpyCheckBox1->txt_color(lv_color_black(),LV_PART_MAIN);
			cpyCheckBox1->set_main_pad_T_B(8,0);
            cpyCheckBox1->set_txt(STR_FLASH_SD);
			cpyCheckBox1->add_flag(LV_OBJ_FLAG_CLICKABLE);
            cpyCheckBox1->add_event_cb(musiclist_cpy_event_handler,LV_EVENT_CLICKED,this);

            cpyChildLabel1 = new LvcppLabel(cpyCheckBox1->myobj);
            cpyChildLabel1->set_size(32,32);
            cpyChildLabel1->align(LV_ALIGN_RIGHT_MID,0,-8);
            cpyChildLabel1->set_main_bg_img_src(LIST_CIRCLESEL_PNG);
            cpyChildLabel1->txt_font_size(24, FT_FONT_STYLE_NORMAL);
            cpyChildLabel1->set_txt("");

            cpyCheckBox2 = new LvcppLabel(cpyChildLabel->myobj);
            cpyCheckBox2->set_size(SCREEN_HOR_SIZE/2-30,SCREEN_VER_SIZE/12);
            cpyCheckBox2->align(LV_ALIGN_TOP_MID,0,SCREEN_VER_SIZE/6+2);
            cpyCheckBox2->set_main_bg_color(lv_color_white(),LV_OPA_100);
			cpyCheckBox2->set_main_pad_T_B(8,0);
            cpyCheckBox2->txt_font_size(28, FT_FONT_STYLE_NORMAL);
            cpyCheckBox2->txt_align(LV_TEXT_ALIGN_LEFT);
            cpyCheckBox2->txt_color(lv_color_black(),LV_PART_MAIN);
            cpyCheckBox2->set_txt(STR_FLASH_USB);
			cpyCheckBox2->add_flag(LV_OBJ_FLAG_CLICKABLE);
            cpyCheckBox2->add_event_cb(musiclist_cpy_event_handler,LV_EVENT_CLICKED,this);

            cpyChildLabel2 = new LvcppLabel(cpyCheckBox2->myobj);
            cpyChildLabel2->set_size(24,24);
            cpyChildLabel2->align(LV_ALIGN_RIGHT_MID,0,-8);
            cpyChildLabel2->set_main_bg_img_src(LIST_CIRCLE_PNG);
            cpyChildLabel2->txt_font_size(24, FT_FONT_STYLE_NORMAL);
            cpyChildLabel2->set_txt("");
        }
    }

    cpyChildButtonCancel = new LvcppButton(cpyChildLabel->myobj);
    cpyChildButtonCancel->set_size(SCREEN_HOR_SIZE/4-20,SCREEN_VER_SIZE/12-10);
    cpyChildButtonCancel->align(LV_ALIGN_BOTTOM_LEFT,5,-5);
    cpyChildButtonCancel->set_main_radius(10);
    cpyChildButtonCancel->set_main_bg_color(TABLE_SETTING_COLOR,LV_OPA_100);
    cpyChildButtonCancel->add_event_cb(musiclist_cpy_event_handler,LV_EVENT_PRESSED,this);
    cpyChildButtonCancel->add_event_cb(musiclist_cpy_event_handler,LV_EVENT_RELEASED,this);
    cpyChildButtonCancel->txt_size(SCREEN_HOR_SIZE/4-20, SCREEN_VER_SIZE/12-10,LV_LABEL_LONG_WRAP);
    cpyChildButtonCancel->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    cpyChildButtonCancel->txt_center();
    cpyChildButtonCancel->txt_color(lv_color_white());
    cpyChildButtonCancel->add_txt(STR_CANCEL);

    cpyChildButtonOk = new LvcppButton(cpyChildLabel->myobj);
    cpyChildButtonOk->set_size(SCREEN_HOR_SIZE/4-20,SCREEN_VER_SIZE/12-10);
    cpyChildButtonOk->align(LV_ALIGN_BOTTOM_RIGHT,-5,-5);
    cpyChildButtonOk->set_main_radius(10);
    cpyChildButtonOk->set_main_bg_color(TABLE_SETTING_COLOR,LV_OPA_100);
    cpyChildButtonOk->add_event_cb(musiclist_cpy_event_handler,LV_EVENT_PRESSED,this);
    cpyChildButtonOk->add_event_cb(musiclist_cpy_event_handler,LV_EVENT_RELEASED,this);
    cpyChildButtonOk->txt_size(SCREEN_HOR_SIZE/4-20, SCREEN_VER_SIZE/12-10, LV_LABEL_LONG_WRAP);
    cpyChildButtonOk->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    cpyChildButtonOk->txt_center();
    cpyChildButtonOk->txt_color(lv_color_white());
    cpyChildButtonOk->add_txt(STR_OK);
}

void musicList::musiclist_cpy_mute_dele(void)
{
    if(cpyChildButtonOk != NULL)
    {
        delete cpyChildButtonOk;
        cpyChildButtonOk =NULL;
    }
    if(cpyChildButtonCancel != NULL)
    {
        delete cpyChildButtonCancel;
        cpyChildButtonCancel =NULL;
    }
    if(cpyChildLabel1 != NULL)
    {
        delete cpyChildLabel1;
        cpyChildLabel1 =NULL;
    }
    if(cpyChildLabel2 != NULL)
    {
        delete cpyChildLabel2;
        cpyChildLabel2 =NULL;
    }
    if(cpyCheckBox1 != NULL)
    {
        delete cpyCheckBox1;
        cpyCheckBox1 =NULL;
    }
    if(cpyCheckBox2 != NULL)
    {
        delete cpyCheckBox2;
        cpyCheckBox2 =NULL;
    }
    if(cpyChildButtonLine != NULL)
    {
        delete cpyChildButtonLine;
        cpyChildButtonLine =NULL;
    }
    if(cpyChildLabel != NULL)
    {
        delete cpyChildLabel;
        cpyChildLabel =NULL;
    }
    if(cpyButton != NULL)
    {
        delete cpyButton;
        cpyButton =NULL;
    }
}
void musicList::musiclist_cpy_event_handler(lv_event_t *event)
{
    musicList* opt = (musicList*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target==opt->cpyButton->myobj)
    {
        opt->musiclist_cpy_mute_dele();
        opt->draw_headlist();
    }
    else if(target==opt->cpyChildButtonCancel->myobj)
    {
        if(event->code == LV_EVENT_RELEASED)
        {
            opt->musiclist_cpy_mute_dele();
            opt->draw_headlist();
        }
    }
    else if(target==opt->cpyChildButtonOk->myobj)
    {
        if(event->code == LV_EVENT_RELEASED)
        {
            opt->musiclist_cpy_mute_dele();
			opt->IconCheck =false;
			opt->IconStation =false;
            opt->IconDel->show(false);
			opt->IconChe->show(false);
			opt->IconCpy->show(false);
			opt->IconSor->show(false);
            opt->StrIconNum->show(false);
			opt->draw_headlist();
			opt->_cpy_selfilelist();
            opt->draw_musicListIcon_list(false);
        }
    }
	else if((opt->cpyCheckBox1 !=NULL)&&(target==opt->cpyCheckBox1->myobj))
    {
    	if(opt->cpyCheckBox1 !=NULL)
        	opt->cpyChildLabel1->set_main_bg_img_src(opt->LIST_CIRCLESEL_PNG);
		if(opt->cpyCheckBox2 !=NULL)
        	opt->cpyChildLabel2->set_main_bg_img_src(opt->LIST_CIRCLE_PNG);
		opt->CpyType =1;
    }
    else if((opt->cpyCheckBox2 !=NULL)&&(target==opt->cpyCheckBox2->myobj))
    {
    	if(opt->cpyCheckBox1 !=NULL)
        	opt->cpyChildLabel1->set_main_bg_img_src(opt->LIST_CIRCLE_PNG);
		if(opt->cpyCheckBox2 !=NULL)
			opt->cpyChildLabel2->set_main_bg_img_src(opt->LIST_CIRCLESEL_PNG);
		opt->CpyType =2;
    }
}

void musicList::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    if(StartTimerShow !=true)
        return;
    timecnt++;

    tplayer_get_current_pos(PlayerUiM->tplayer, &StartTime);
    tplayer_get_duration(PlayerUiM->tplayer, &EndTime);
    if(((timecnt%5)==0)&&(playStatus ==true))
    {
    	play_time_update();
    }
	if(finishStatus ==true)
	{
		finishStatus =false;
		playStatus = false;
		StartTimerShow =false;
		IconPlay->set_main_bg_img_src(MUSIC_UNPLAY_PNG);
	    animCd->set_time(1);
	    animCd->set_repeat_count(0);
	    animCd->start();
		play_time_update();
		play_next_file();
	}
}

void musicList::media_player_ui_callback(void *ui_player, media_event_t event, void *param)
{        
	player_ui_t * player_ui = (player_ui_t *)ui_player;
	if (player_ui == NULL) 
	{                
		return;        
	}
	switch (event) 
	{                
		case MEDIA_IDLE_EVENT:
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
			finishStatus =true;
			break;                
		default:                        
			break;       
	}
}

void musicList::musicList_media_creat(void)
{	
	char MountPoint[128]={0};
	char userPatch[64]={0};
	char *file_path =NULL;
	int i=0;

	if(media_file_list !=NULL)
	{
		media_unload_file(media_file_list);
		media_file_list = NULL;
	}
	if(musicShuffleList !=NULL)
    {
        delete musicShuffleList;
        musicShuffleList =NULL;
    }
	musicShuffleList = new shuffle_list();
	if(media_file_list == NULL)
	{
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
		else
		{
			strcpy(MountPoint,"/mnt/exUDISK");
		}

		LV_LOG_USER("MountPoint:%s",MountPoint);
		media_file_list = media_load_file(RAT_MEDIA_TYPE_AUDIO, MountPoint);
		if(NULL == media_file_list)
		{
			LV_LOG_USER("%s don't find music list\n",MountPoint);
			musicListTotal = 0;
			musicIndex =0;
		}
		else
		{
			musicListTotal = media_file_list->total_num;
			musicIndex =0;
		}
		
		if(musicListTotal <=0)
		{
			if(IconBack !=NULL)
				IconBack->show(false);
		}
		else
		{
			if(IconBack !=NULL)
				IconBack->show(true);
		}
	}
}

int musicList::play_time_update(void)
{
    char durstr[16]={0};
    char curstr[16]={0};
    sprintf(durstr,"%02d:%02d",EndTime/60,EndTime%60);
    sprintf(curstr,"%02d:%02d",StartTime/60,StartTime%60);
    if(StrEndTime!=NULL)
    {
        StrEndTime->set_txt(durstr);
    }
    if(StrEndTime!=NULL)
    {
        StrStartTime->set_txt(curstr);
    }
    if(musicSlider!=NULL)
    {
        if(EndTime==0)
        {
            return -1;
        }
        musicSlider->set_range(0, EndTime);
        musicSlider->set_value(StartTime, LV_ANIM_ON);
    }
    return 0;
}

LvcppButton* musicList::LvcppButtonHead(lv_obj_t* paren,bool show_cb,lv_ui_inof_t *uiInfo)
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
    child_button->add_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
    child_button->set_userdata(NULL);
    if(show_cb ==true)
    {
        child_button->set_userdata((void*)uiInfo->userdata);
        child_button->add_event_cb(head_event_handler,LV_EVENT_PRESSED,this);
        child_button->add_event_cb(head_event_handler,LV_EVENT_RELEASED,this);
    }
    return child_button;
}

LvcppLabel* musicList::LvcppLabelViewChild(lv_obj_t* paren,lv_text_align_t align,lv_str_inof_t *strInfo)
{
    LvcppLabel* childView =NULL;

    childView = new LvcppLabel(paren);
    childView->set_size(strInfo->w,strInfo->h);
    childView->align_to(paren,LV_ALIGN_TOP_LEFT, strInfo->x, strInfo->y);
    childView->txt_font_size(strInfo->h-6, FT_FONT_STYLE_NORMAL);
    childView->txt_align(align);
    childView->txt_color(lv_color_hex(strInfo->str_color),LV_PART_MAIN);
    childView->set_txt(strInfo->str_buff);
    return childView;
}

LvcppSlider* musicList::LvcppSliderChild(lv_obj_t* paren,lv_slider_inof_t * curSlider)
{
    LvcppSlider* childSlider =NULL;

    childSlider = new LvcppSlider(paren);
    childSlider->set_size(curSlider->w, curSlider->h);
    childSlider->align(LV_ALIGN_TOP_LEFT, curSlider->x, curSlider->y);
    childSlider->set_mode(LV_BAR_MODE_NORMAL);
    childSlider->set_range(curSlider->minInde, curSlider->maxInde);
    childSlider->set_style_radius(0, LV_PART_INDICATOR);
    childSlider->set_style_pad_all(0,0);
    childSlider->set_main_border_width(0);
    childSlider->set_style_bg_color(lv_color_hex(0x74dafa),LV_OPA_0,LV_PART_MAIN);
    childSlider->set_style_bg_color(lv_color_hex(0xffffff),LV_OPA_0,LV_PART_INDICATOR);
    childSlider->set_style_bg_color(lv_color_hex(0xffffff),LV_OPA_0,LV_PART_KNOB);
    childSlider->set_style_bg_img_src(curSlider->bg_patch,LV_PART_MAIN);
    childSlider->set_style_bg_img_src(curSlider->curbg_patch,LV_PART_INDICATOR);
    childSlider->set_style_bg_img_src(curSlider->cur_patch,LV_PART_KNOB);
    childSlider->set_left_value(0, LV_ANIM_ON);
    childSlider->set_value(curSlider->Inde, LV_ANIM_ON);
    childSlider->add_event_cb(musicSlider_event_handler, LV_EVENT_VALUE_CHANGED,this);
    childSlider->set_userdata(NULL);
    childSlider->set_userdata((void*)curSlider->userdata);
    return childSlider;
}

void musicList::ImgCd_creat(void)
{
    animCd = new LvcppRotateAnimimg(mainscreen);
    animCd->set_animimg_src(MUSIC_ICONCD_PNG);
    animCd->align(LV_ALIGN_TOP_LEFT, 870, 212);
    animCd->set_size(170, 170);
    animCd->set_values(3600, 1);
    animCd->set_time(1);
    animCd->set_repeat_count(0);
    animCd->start();
}

void musicList::music_Slider_creat(void)
{
    lv_slider_inof_t SliderInfo;
    lv_str_inof_t strInfo;

    SliderInfo.x =780;
    SliderInfo.y =616;
    SliderInfo.w =368;
    SliderInfo.h =24;
    SliderInfo.minInde =0;
    SliderInfo.maxInde =EndTime;
    SliderInfo.Inde =StartTime;
    SliderInfo.userdata =LIST_ICON_PLAY;
    SliderInfo.bg_patch =(char*)MUSIC_TIME_BG_PNG;
    SliderInfo.curbg_patch =(char*)MUSIC_TIMESEL_BG_PNG;
    SliderInfo.cur_patch =(char*)MUSIC_TIMECUR_PNG;
    musicSlider = LvcppSliderChild(mainscreen,&SliderInfo);

    SliderInfo.x =1085;
    SliderInfo.y =540;
    SliderInfo.w =128;
    SliderInfo.h =30;
    SliderInfo.minInde =0;
    SliderInfo.maxInde =VOL_MAX;
    SliderInfo.Inde =CurVol;
    SliderInfo.userdata =LIST_ICON_VOLA;
    SliderInfo.bg_patch =(char*)MUSIC_VOLBG_PNG;
    SliderInfo.curbg_patch =(char*)MUSIC_VOLBG_PNG;
    SliderInfo.cur_patch =(char*)MUSIC_VOLICON_PNG;
    volSlider = LvcppSliderChild(mainscreen,&SliderInfo);

    strInfo.x=650;
    strInfo.y =615;
    strInfo.w =125;
    strInfo.h =30;
    strInfo.str_color =WHITE_COLOR;
    if(StartTime <3600)
    {
        sprintf(startTimeBuff,"%.2d:%.2d",StartTime/60,StartTime%60);
    }
    else
    {
        sprintf(startTimeBuff,"%.2d:%.2d:%.2d",StartTime/3600,(StartTime-3600)/60,(StartTime-3600)%60);
    }
    strInfo.str_buff =startTimeBuff;
    StrStartTime = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_CENTER,&strInfo);

    strInfo.x=1154;
    strInfo.y =615;
    strInfo.w =120;
    strInfo.h =30;
    strInfo.str_color =WHITE_COLOR;
    if(EndTime <3600)
    {
        sprintf(endtTimeBuff,"%.2d:%.2d",EndTime/60,EndTime%60);
    }
    else
    {
        sprintf(endtTimeBuff,"%.2d:%.2d:%.2d",EndTime/3600,(EndTime-3600)/60,(EndTime-3600)%60);
    }
    strInfo.str_buff =endtTimeBuff;
    StrEndTime = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_CENTER,&strInfo);

    strInfo.x=680;
    strInfo.y =410;
    strInfo.w =550;
    strInfo.h =30;
    strInfo.str_color =WHITE_COLOR;
    strcpy(AlbumBuff,"null");
    strInfo.str_buff =AlbumBuff;
    StrAlbum = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_CENTER,&strInfo);
    StrAlbum->txt_long_mode(LV_LABEL_LONG_SCROLL_CIRCULAR);

    strInfo.x=680;
    strInfo.y =455;
    strInfo.w =550;
    strInfo.h =30;
    strInfo.str_color =WHITE_COLOR;
    strcpy(ArtistBuff,"null");
    strInfo.str_buff =ArtistBuff;
    StrArtist = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_CENTER,&strInfo);
    StrArtist->txt_long_mode(LV_LABEL_LONG_SCROLL_CIRCULAR);
}

void musicList::music_Slider_delete(void)
{
    if(StrAlbum!=NULL)
    {
        delete StrAlbum;
        StrAlbum =NULL;
    }
    if(StrArtist!=NULL)
    {
        delete StrArtist;
        StrArtist =NULL;
    }
    if(StrStartTime!=NULL)
    {
        delete StrStartTime;
        StrStartTime =NULL;
    }
    if(StrEndTime!=NULL)
    {
        delete StrEndTime;
        StrEndTime =NULL;
    }
    if(musicSlider!=NULL)
    {
        delete musicSlider;
        musicSlider =NULL;
    }
    if(volSlider!=NULL)
    {
        delete volSlider;
        volSlider =NULL;
    }
}

void musicList::musicSlider_event_handler(lv_event_t *event)
{
    musicList* opt = (musicList*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
	int val =0;

	if((opt->volSlider !=NULL)&&(target ==opt->volSlider->myobj))
	{
		if(event->code== LV_EVENT_VALUE_CHANGED)
        {
            opt->CurVol = opt->volSlider->get_value();
			val =(int)(opt->CurVol*4);
		    tplayer_volume(opt->PlayerUiM->tplayer,val);
			write_int_type_param(PUBLIC_SCENE, VOLUME,val);
        }
	}
	else if((opt->musicSlider !=NULL)&&(target ==opt->musicSlider->myobj))
	{
		if(event->code== LV_EVENT_VALUE_CHANGED)
        {
            opt->StartTime = opt->musicSlider->get_value();
            memset(opt->startTimeBuff,0,10);
            if(opt->StartTime <3600)
            {
                sprintf(opt->startTimeBuff,"%.2d:%.2d",opt->StartTime/60,opt->StartTime%60);
            }
            else
            {
                sprintf(opt->startTimeBuff,"%.2d:%.2d:%.2d",opt->StartTime/3600,(opt->StartTime-3600)/60,(opt->StartTime-3600)%60);
            }
            opt->StrStartTime->set_txt(opt->startTimeBuff);
			tplayer_seekto(opt->PlayerUiM->tplayer,opt->StartTime);
        }
	}
}

void musicList::music_list_head_creat(void)
{
    lv_ui_inof_t uiInfo;
    lv_str_inof_t strInfo;
    char buff[12]={0};

	uiInfo.x =30;
    uiInfo.y =8;
    uiInfo.w =66;
    uiInfo.h =66;
    uiInfo.userdata =HEAD_ICON_RETURN;
    uiInfo.ui_patch =(char *)HEAD_RETURN_PNG;
    buttonReturn =LvcppButtonHead(mainscreen,true,&uiInfo);

    uiInfo.x =114;
    uiInfo.y =8;
    uiInfo.w =66;
    uiInfo.h =66;
    uiInfo.ui_patch =(char *)HEAD_ICON_MUSIC_PNG;
    musicIcon =LvcppButtonHead(mainscreen,false,&uiInfo);
    musicIcon->set_userdata(NULL);

    uiInfo.x =1120;
    uiInfo.y =3;
    uiInfo.w =78;
    uiInfo.h =78;
    uiInfo.userdata =HEAD_ICON_CHECK;
    uiInfo.ui_patch =(char *)LIST_ICON_NORSEL_PNG;
    IconChe =LvcppButtonHead(mainscreen,true,&uiInfo);
    IconChe->show(false);

    uiInfo.x =1200;
    uiInfo.y =3;
    uiInfo.w =78;
    uiInfo.h =78;
    uiInfo.userdata =HEAD_ICON_BALCK;
    uiInfo.ui_patch =(char *)LIST_ICON_ICON_PNG;
    IconBack =LvcppButtonHead(mainscreen,true,&uiInfo);

    strInfo.x=1120;
    strInfo.y =25;
    strInfo.w =78;
    strInfo.h =30;
    strInfo.str_color =WHITE_COLOR;
    strInfo.str_buff =buff;
    StrIconNum = LvcppLabelViewChild(mainscreen,LV_TEXT_ALIGN_CENTER,&strInfo);
    StrIconNum->show(false);

    uiInfo.x =1040;
    uiInfo.y =3;
    uiInfo.w =78;
    uiInfo.h =78;
    uiInfo.userdata =HEAD_ICON_DEL;
    uiInfo.ui_patch =(char *)LIST_ICON_UNDEL_PNG;
    IconDel =LvcppButtonHead(mainscreen,true,&uiInfo);
    IconDel->show(false);

	uiInfo.x =960;
    uiInfo.y =3;
    uiInfo.w =78;
    uiInfo.h =78;
    uiInfo.userdata =HEAD_ICON_COPY;
    uiInfo.ui_patch =(char *)LIST_UNCOPY_PNG;
    IconCpy =LvcppButtonHead(mainscreen,true,&uiInfo);
    IconCpy->show(false);

	uiInfo.x =880;
    uiInfo.y =3;
    uiInfo.w =78;
    uiInfo.h =78;
    uiInfo.userdata =HEAD_ICON_SORT;
    uiInfo.ui_patch =(char *)LIST_SORT_PNG;
    IconSor =LvcppButtonHead(mainscreen,true,&uiInfo);
    IconSor->show(false);

    uiInfo.x =700;
    uiInfo.y =692;
    uiInfo.w =45;
    uiInfo.h =45;
    uiInfo.userdata =HEAD_ICON_PREV;
    uiInfo.ui_patch =MUSIC_UNPREV_PNG;
    IconPrev =LvcppButtonHead(mainscreen,true,&uiInfo);

    uiInfo.x =935;
    uiInfo.y =690;
    uiInfo.w =45;
    uiInfo.h =48;
    uiInfo.userdata =HEAD_ICON_PLAYING;
    if(playStatus !=true)
    {
        uiInfo.ui_patch =MUSIC_UNPLAY_PNG;
    }
    else
    {
        uiInfo.ui_patch =MUSIC_UNSTOP_PNG;
    }
    IconPlay =LvcppButtonHead(mainscreen,true,&uiInfo);

    uiInfo.x =1170;
    uiInfo.y =692;
    uiInfo.w =45;
    uiInfo.h =45;
    uiInfo.userdata =HEAD_ICON_NEXT;
    uiInfo.ui_patch =MUSIC_UNNEXT_PNG;
    IconNext =LvcppButtonHead(mainscreen,true,&uiInfo);

    uiInfo.x =690;
    uiInfo.y =540;
    uiInfo.w =45;
    uiInfo.h =45;
    uiInfo.userdata =HEAD_ICON_MODE;
    if(PlayMode ==0)
    {
        uiInfo.ui_patch =MUSIC_UNLOOP_PNG;
    }
    else if(PlayMode ==1)
    {
        uiInfo.ui_patch =MUSIC_UNSHUFFLE_PNG;
    }
    else
    {
        uiInfo.ui_patch =MUSIC_UNSINGLE_PNG;
    }
    IconMode =LvcppButtonHead(mainscreen,true,&uiInfo);

    uiInfo.x =1032;
    uiInfo.y =536;
    uiInfo.w =40;
    uiInfo.h =36;
    uiInfo.ui_patch =MUSIC_VOLDOT_PNG;
    IconVol =LvcppButtonHead(mainscreen,false,&uiInfo);
}

void musicList::draw_headlist(void)
{
    int icon_x =0,icon_y =0;
    char buff[12]={0};

    if(IconStation !=true)
    {
		icon_x =880;
        icon_y =3;
        IconSor->align_to(mainscreen,LV_ALIGN_TOP_LEFT,icon_x,icon_y);
        IconSor->show(false);
		
		icon_x =960;
        icon_y =3;
        IconCpy->align_to(mainscreen,LV_ALIGN_TOP_LEFT,icon_x,icon_y);
        IconCpy->show(false);
		
        icon_x =1040;
        icon_y =3;
        IconDel->align_to(mainscreen,LV_ALIGN_TOP_LEFT,icon_x,icon_y);
        IconDel->show(false);
        icon_x =1120;
        icon_y =3;
        IconDel->align_to(mainscreen,LV_ALIGN_TOP_LEFT,icon_x,icon_y);
        IconChe->show(false);
        IconBack->set_main_bg_img_src(LIST_ICON_ICON_PNG);
    }
    else
    {
        if(IconCheck ==true)
        {	
    		icon_x =800;
            icon_y =3;
            IconSor->align_to(mainscreen,LV_ALIGN_TOP_LEFT,icon_x,icon_y);
            IconSor->set_main_bg_img_src(LIST_SORT_PNG);

			icon_x =880;
            icon_y =3;
            IconCpy->align_to(mainscreen,LV_ALIGN_TOP_LEFT,icon_x,icon_y);
			if(flash_inde ==0)
			{
				IconCpy->set_main_bg_img_src(LIST_UNCOPY_PNG);
			}
			else if((flash_inde ==2)||(flash_inde ==3))
			{
				IconCpy->set_main_bg_img_src(LIST_COPY_PNG);
			}
			else
			{
				if((UEnter !=true)&&(SDEnter !=true))
				{
					IconCpy->set_main_bg_img_src(LIST_UNCOPY_PNG);
				}
				else
				{
					IconCpy->set_main_bg_img_src(LIST_COPY_PNG);
				}
			}
			
            icon_x =960;
            icon_y =3;
            IconDel->align_to(mainscreen,LV_ALIGN_TOP_LEFT,icon_x,icon_y);
            IconDel->set_main_bg_img_src(LIST_ICON_DEL_PNG);
			
            icon_x =1040;
            icon_y =3;
            IconChe->align_to(mainscreen,LV_ALIGN_TOP_LEFT,icon_x,icon_y);
            IconChe->set_main_bg_img_src(LIST_ICON_CHE_PNG);
            memset(buff,0,12);
            sprintf(buff,"%d",checkedNum);
            StrIconNum->set_txt(buff);
            StrIconNum->show(true);
        }
        else
        {
    		icon_x =880;
            icon_y =3;
            IconSor->align_to(mainscreen,LV_ALIGN_TOP_LEFT,icon_x,icon_y);
            IconSor->set_main_bg_img_src(LIST_SORT_PNG);

			icon_x =960;
            icon_y =3;
            IconCpy->align_to(mainscreen,LV_ALIGN_TOP_LEFT,icon_x,icon_y);
            IconCpy->set_main_bg_img_src(LIST_UNCOPY_PNG);
			
            icon_x =1040;
            icon_y =3;
            IconDel->align_to(mainscreen,LV_ALIGN_TOP_LEFT,icon_x,icon_y);
            IconDel->set_main_bg_img_src(LIST_ICON_UNDEL_PNG);
			
            icon_x =1120;
            icon_y =3;
            IconChe->align_to(mainscreen,LV_ALIGN_TOP_LEFT,icon_x,icon_y);
            IconChe->set_main_bg_img_src(LIST_ICON_NOR_PNG);
            memset(buff,0,12);
            StrIconNum->set_txt(buff);
            StrIconNum->show(false);
        }
    }
}

void musicList::music_list_head_dele(void)
{
    if(IconPlay != NULL)
    {
        delete IconPlay;
        IconPlay =NULL;
    }
    if(IconPrev != NULL)
    {
        delete IconPrev;
        IconPrev =NULL;
    }
    if(IconNext != NULL)
    {
        delete IconNext;
        IconNext =NULL;
    }
    if(IconMode != NULL)
    {
        delete IconMode;
        IconMode =NULL;
    }
    if(IconVol != NULL)
    {
        delete IconVol;
        IconVol =NULL;
    }
    if(buttonReturn != NULL)
    {
        delete buttonReturn;
        buttonReturn =NULL;
    }
    if(musicIcon != NULL)
    {
        delete musicIcon;
        musicIcon =NULL;
    }
    if(IconSor != NULL)
    {
        delete IconSor;
        IconSor =NULL;
    }
    if(IconCpy != NULL)
    {
        delete IconCpy;
        IconCpy =NULL;
    }
    if(IconDel != NULL)
    {
        delete IconDel;
        IconDel =NULL;
    }
    if(IconChe != NULL)
    {
        delete IconChe;
        IconChe =NULL;
    }
    if(IconBack != NULL)
    {
        delete IconBack;
        IconBack =NULL;
    }
    if(StrIconNum != NULL)
    {
        delete StrIconNum;
        StrIconNum =NULL;
    }
}

void musicList::head_event_handler(lv_event_t *event)
{
    musicList* opt = (musicList*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    int set_selete = (uintptr_t)target->user_data;
    int icon_x =0,icon_y =0;

    switch(set_selete)
    {
        case HEAD_ICON_RETURN:
            if(event->code== LV_EVENT_PRESSED)
            {
                opt->buttonReturn->set_main_bg_img_src(opt->HEAD_RETURN_SEL_PNG);
            }
            else
            {
                opt->StartTimerShow =false;
        		MainAPPStart::musiclist_destory();
				return;
            }
        break;
        case HEAD_ICON_PREV:
            if(event->code== LV_EVENT_PRESSED)
            {
                opt->IconPrev->set_main_bg_img_src(opt->MUSIC_PREV_PNG);
            }
            else
            {
                opt->IconPrev->set_main_bg_img_src(opt->MUSIC_UNPREV_PNG);
				opt->play_prve_next_file(false);
            }
        break;
        case HEAD_ICON_PLAYING:
            if(event->code== LV_EVENT_PRESSED)
            {
                if(opt->playStatus !=true)
                {
                    opt->IconPlay->set_main_bg_img_src(opt->MUSIC_PLAY_PNG);
                }
                else
                {
                    opt->IconPlay->set_main_bg_img_src(opt->MUSIC_STOP_PNG);
                }
            }
            else
            {
                if(opt->playStatus !=true)
                {
                    opt->IconPlay->set_main_bg_img_src(opt->MUSIC_UNSTOP_PNG);
                    opt->music_list_start_playing();
                }
                else
                {
                    opt->IconPlay->set_main_bg_img_src(opt->MUSIC_UNPLAY_PNG);
					opt->music_list_stop_playing();
                }
            }
        break;
        case HEAD_ICON_NEXT:
            if(event->code== LV_EVENT_PRESSED)
            {
                opt->IconNext->set_main_bg_img_src(opt->MUSIC_NEXT_PNG);
            }
            else
            {
                opt->IconNext->set_main_bg_img_src(opt->MUSIC_UNNEXT_PNG);
				opt->play_prve_next_file(true);
            }
        break;
        case HEAD_ICON_MODE:
            if(event->code== LV_EVENT_PRESSED)
            {
                if(opt->PlayMode ==0)
                {
                    opt->IconMode->set_main_bg_img_src(opt->MUSIC_LOOP_PNG);
                }
                else if(opt->PlayMode ==1)
                {
                    opt->IconMode->set_main_bg_img_src(opt->MUSIC_SHUFFLE_PNG);
                }
                else
                {
                    opt->IconMode->set_main_bg_img_src(opt->MUSIC_SINGLE_PNG);
                }
                opt->PlayMode ++;
                if(opt->PlayMode>2)
                    opt->PlayMode =0;
				write_int_type_param(MUSIC_SCENE, LOOPMUSIC,opt->PlayMode);
            }
            else
            {
                if(opt->PlayMode ==0)
                {
                    opt->IconMode->set_main_bg_img_src(opt->MUSIC_UNLOOP_PNG);
                }
                else if(opt->PlayMode ==1)
                {
                    opt->IconMode->set_main_bg_img_src(opt->MUSIC_UNSHUFFLE_PNG);
					opt->musicShuffleList->shuffle(opt->musicListTotal,opt->musicIndex,1);
                }
                else
                {
                    opt->IconMode->set_main_bg_img_src(opt->MUSIC_UNSINGLE_PNG);
                }
            }
        break;
		case HEAD_ICON_COPY:
            if(opt->IconStation !=true)
            {
                opt->IconCpy->show(false);
                break;
            }
			if((opt->flash_inde==0)||((opt->flash_inde!=2)&&(opt->flash_inde!=3)&&(opt->SDEnter !=TRUE)&&(opt->UEnter !=true)))
				break;
            if(event->code== LV_EVENT_PRESSED)
            {
                if(opt->IconCheck ==true)
                {
                    opt->IconCpy->set_main_bg_img_src(opt->LIST_COPY_SEL_PNG);
                }
                else
                {
                    opt->IconCpy->set_main_bg_img_src(opt->LIST_UNCOPY_PNG);
                }
            }
            else
            {
                if(opt->IconCheck ==true)
                {
                    opt->IconCpy->set_main_bg_img_src(opt->LIST_COPY_PNG);
					opt->check_disk_status();
					if((opt->flash_inde ==2)||(opt->flash_inde ==3))
					{
						opt->DiskShowType =1;
					}
					else if((opt->SDEnter ==TRUE)&&(opt->UEnter ==true))
					{
						opt->DiskShowType =3;
					}
					else
					{
						opt->DiskShowType =2;
					}
					opt->musiclist_cpy_mute_creat();
                }
                else
                {
                    opt->IconCpy->set_main_bg_img_src(opt->LIST_UNCOPY_PNG);
                }
                opt->draw_headlist();
            }
        break;
        case HEAD_ICON_DEL:
            if(opt->IconStation !=true)
            {
                opt->IconDel->show(false);
                break;
            }
			if(opt->checkedNum <=0)
				break;
            if(event->code== LV_EVENT_PRESSED)
            {
                if(opt->IconCheck ==true)
                {
                    opt->IconDel->set_main_bg_img_src(opt->LIST_ICON_DELSEL_PNG);
                }
                else
                {
                    opt->IconDel->set_main_bg_img_src(opt->LIST_ICON_UNDEL_PNG);
                }
            }
            else
            {
                if(opt->IconCheck ==true)
                {
                    opt->IconDel->set_main_bg_img_src(opt->LIST_ICON_DEL_PNG);
					opt->musiclist_del_mute_creat();
                }
                else
                {
                    opt->IconDel->set_main_bg_img_src(opt->LIST_ICON_UNDEL_PNG);
                }
                opt->draw_headlist();
            }
        break;
        case HEAD_ICON_CHECK:
            if(opt->IconStation !=true)
            {
                opt->IconChe->show(false);
                break;
            }
            if(event->code== LV_EVENT_PRESSED)
            {
                if(opt->IconCheck ==true)
                {
                    opt->IconChe->set_main_bg_img_src(opt->LIST_ICON_CHELSEL_PNG);
                    opt->IconCheck =false;
                }
                else
                {
                    opt->IconChe->set_main_bg_img_src(opt->LIST_ICON_NORSEL_PNG);
                    opt->IconCheck =true;
                }
            }
            else
            {
                if(opt->IconCheck ==true)
                {
                    opt->IconChe->set_main_bg_img_src(opt->LIST_ICON_CHE_PNG);
					opt->_add_allfilelist();
                }
                else
                {
                    opt->IconChe->set_main_bg_img_src(opt->LIST_ICON_NOR_PNG);
					opt->_destory_selfilelist();
					opt->set_musicListIcon_list(false);
                }
                opt->draw_headlist();
            }
        break;
        case HEAD_ICON_BALCK:
            if(event->code== LV_EVENT_PRESSED)
            {
                if(opt->IconStation ==true)
                {
                    opt->IconBack->set_main_bg_img_src(opt->LIST_ICON_CANLSEL_PNG);
                    opt->IconStation =false;
                }
                else
                {
                    opt->IconBack->set_main_bg_img_src(opt->LIST_ICON_ICONLSEL_PNG);
                    opt->IconStation =true;
                }
				opt->_destory_selfilelist();
            }
            else
            {
                if(opt->IconStation ==true)
                {
                	opt->check_disk_status();
                	opt->IconCheck =false;
                    opt->IconBack->set_main_bg_img_src(opt->LIST_ICON_CAN_PNG);
					opt->IconDel->set_main_bg_img_src(opt->LIST_ICON_UNDEL_PNG);
					opt->IconChe->set_main_bg_img_src(opt->LIST_ICON_NOR_PNG);
                    opt->IconDel->show(true);
                    opt->IconChe->show(true);
					opt->IconCpy->show(true);
					opt->IconSor->show(true);
					opt->draw_musicListIcon_list(true);
                }
                else
                {
                    opt->IconBack->set_main_bg_img_src(opt->LIST_ICON_ICON_PNG);
                    opt->IconDel->show(false);
                    opt->IconChe->show(false);
					opt->IconCpy->show(false);
					opt->IconSor->show(false);
                    opt->StrIconNum->show(false);
					opt->draw_musicListIcon_list(false);
                }
                opt->draw_headlist();
            }
        break;
        default:
            break;
    }
}

int musicList::music_list_creat(void)
{
    list_main = new LvcppList(mainscreen);
    list_main->set_size(1280,82);
    list_main->align(LV_ALIGN_TOP_LEFT,0,84);
    list_main->set_main_bg_color(lv_color_hex(0x0a85a6),LV_OPA_COVER);
    list_main->set_main_bg_opa(LV_OPA_100);
    list_main->set_flex_flow(LV_FLEX_FLOW_ROW);
    list_main->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    list_main->set_main_pad_all(0);
    list_main->set_main_pad_row(0);
    list_main->set_main_pad_column(2);
    list_main->set_main_border_width(0);
    list_main->set_main_radius(0);

    memset(&main_list_id, 0 , sizeof(main_musiclist_item_info));
    musicmian_list_add();
    list_main->set_select_state(flash_inde,lv_color_hex(0x00a7d4));
    return 0;
}

int musicList::musicmian_list_add(void)
{
    void  *iconPatchMain[4]={LIST_ICON_ALL_PNG,LIST_ICON_FLASH_PNG,LIST_ICON_SD_PNG,LIST_ICON_U_PNG};
    frameiconlist_btn_t btn_info;
    frameiconlist_icon_t icon_info;

    btn_info.x =0;
    btn_info.y =0;
    btn_info.w =318;
    btn_info.h =80;
    btn_info.bg_color =0x0099bb;
    btn_info.value =LV_OPA_100;
    btn_info.align =LV_ALIGN_TOP_LEFT;

    icon_info.x =0;
    icon_info.y =0;
    icon_info.w =42;
    icon_info.h =44;
    icon_info.align =LV_ALIGN_TOP_LEFT;

    for(int i=main_list_id.count;i < flash_total;i++)
    {
        main_list_id.list_item[i] = new frameListIconCenter(list_main->myobj,&btn_info,WHITE_COLOR,&icon_info);
        main_list_id.list_item[i]->btn->add_event_cb(main_event_handler,LV_EVENT_CLICKED,this);
        main_list_id.list_item[i]->btn->set_userdata(NULL);
        main_list_id.list_item[i]->btn->set_userdata((void*)i);
        strcpy(main_list_id.list_item[i]->IconName,(const char*)iconName[i]);
        main_list_id.list_item[i]->set_IconName();
        main_list_id.list_item[i]->set_IconPtch(42,(char*)iconPatchMain[i]);
        main_list_id.count++;
    }
    return 0;
}

void musicList::musicmian_list_dele(void)
{
    for(int i=main_list_id.count;i>0;i--)
    {
        main_list_id.count--;
        if(main_list_id.list_item[main_list_id.count] !=NULL)
        {
            delete main_list_id.list_item[main_list_id.count];
            main_list_id.list_item[main_list_id.count] =NULL;
        }
    }

    if(list_main !=NULL)
    {
        delete list_main;
        list_main =NULL;
    }
}

void musicList::main_event_handler(lv_event_t *event)
{
    musicList* opt = (musicList*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    lv_obj_t* cont = lv_event_get_current_target(event);

    if(cont != target)
    {
        opt->flash_inde = (uintptr_t)cont->user_data;
    }
    else
    {
       opt->flash_inde =(uintptr_t)target->user_data;
    }
    if(opt->IconStation == true)
    {
        opt->IconStation =false;
        opt->draw_headlist();
    }
    opt->list_main->switch_select_state(opt->flash_inde,lv_color_hex(0x0099bb),lv_color_hex(0x00a7d4));
	opt->musicList_list_delete();
	opt->musicList_media_creat();
	opt->musicList_list_creat();
}

int musicList::musicList_list_creat(void)
{
    list_musicList = new LvcppList(mainscreen);
    list_musicList->set_size(610,548);
    list_musicList->align(LV_ALIGN_TOP_LEFT,20,212);
    list_musicList->set_flex_flow(LV_FLEX_FLOW_COLUMN);
    list_musicList->set_scrollbar_mode(LV_SCROLLBAR_MODE_ON);
    list_musicList->set_scrollbar_dir(LV_DIR_VER);
    list_musicList->set_main_bg_opa(LV_OPA_0);
    list_musicList->set_main_pad_all(0);
    list_musicList->set_main_pad_row(2);
    list_musicList->set_main_pad_column(0);
    list_musicList->set_main_border_width(0);
    list_musicList->set_main_radius(0);

    memset(&music_list_id, 0 , sizeof(musiclist_item_info));
    musicList_list_add();
    return 0;
}

int musicList::musicList_list_add(void)
{
	void  *iconPatch[2]={LIST_UNSEL_PNG,LIST_SEL_PNG};
    framelist_btn_t btn_info;
    framelist_txt_t txt_info;
    framelist_icon_t icon_info;
	char *path =NULL;
	char *file_path =NULL;
	char music_path[128]={0};

    btn_info.x =0;
    btn_info.y =0;
    btn_info.w =548;
    btn_info.h =81;
    btn_info.bg_color =0x0a85a6;
    btn_info.line_h =1;
    btn_info.line_color =WHITE_COLOR;
    btn_info.align =LV_ALIGN_TOP_LEFT;

    txt_info.x =10;
    txt_info.y =24;
    txt_info.w =490;
    txt_info.h =32;
    txt_info.font_size =26;
    txt_info.txt_color =WHITE_COLOR;
    txt_info.align =LV_ALIGN_TOP_LEFT;
	txt_info.font = myfont->font();

    icon_info.x =5;
    icon_info.y =24;
    icon_info.w =32;
    icon_info.h =32;
    icon_info.showStatus =true;
    icon_info.align =LV_ALIGN_TOP_LEFT;

    for(int i=music_list_id.count;i < musicListTotal;i++)
    {
        icon_info.iconPatch = (char*)iconPatch[0];
        music_list_id.list_item[i] = new frameListIcon(list_musicList->myobj,&btn_info,&txt_info,&icon_info);
		if(media_file_list !=NULL)
		{
			path = media_get_file_path(media_file_list,i);
			if(path !=NULL)
			{
				file_path = media_get_path_to_name(path);
				if(file_path !=NULL)
				{
					strcpy(music_path,file_path);
				}
			}
		}
		music_list_id.list_item[i]->set_IconName(music_path);
        music_list_id.list_item[i]->btn->add_event_cb(musicList_event_handler,LV_EVENT_CLICKED,this);
        music_list_id.list_item[i]->btn->set_userdata(NULL);
        music_list_id.list_item[i]->btn->set_userdata((void*)i);
        music_list_id.list_item[i]->icon->show(false);
        music_list_id.count++;
    }
	if(musicListTotal>0)
	{
		music_list_id.inde = musicIndex;
		list_musicList->set_scroll_to(0,musicIndex*81, LV_ANIM_OFF);
    	list_musicList->set_select_state(music_list_id.inde,lv_color_hex(0x00a7d4));
	}
    return 0;
}

void musicList::set_musicListIcon_list(bool type)
{
    void  *iconPatch[2]={LIST_UNSEL_PNG,LIST_SEL_PNG};
	
    for(int i=0;i<music_list_id.count;i++)
    {
        if(type == true)
        {
            music_list_id.list_item[i]->set_IconPtch(iconPatch[1]);
            music_list_id.list_item[i]->check_ok =true;
        }
        else
        {
           music_list_id.list_item[i]->set_IconPtch(iconPatch[0]);
           music_list_id.list_item[i]->check_ok =false;
        }
    }
}

void musicList::draw_musicListIcon_list(bool type)
{
    for(int i=0;i<music_list_id.count;i++)
    {
        if(type == true)
        {
            list_musicList->set_select_state(music_list_id.inde,lv_color_hex(0x0a85a6));
            music_list_id.list_item[i]->check_ok =true;
            music_list_id.list_item[i]->btn->txt_align(LV_ALIGN_TOP_LEFT,50,24);
            music_list_id.list_item[i]->icon->show(true);
        }
        else
        {
            music_list_id.list_item[i]->check_ok =false;
            music_list_id.list_item[i]->btn->txt_align(LV_ALIGN_TOP_LEFT,10,24);
            music_list_id.list_item[i]->icon->show(false);
            list_musicList->set_select_state(music_list_id.inde,lv_color_hex(0x00a7d4));
        }
    }
}

void musicList::musicList_list_delete(void)
{
    for(int i=music_list_id.count;i>0;i--)
    {
        music_list_id.count--;
        if(music_list_id.list_item[music_list_id.count] !=NULL)
        {
            delete music_list_id.list_item[music_list_id.count];
            music_list_id.list_item[music_list_id.count] =NULL;
        }
    }
    if(list_musicList !=NULL)
    {
        delete list_musicList;
        list_musicList =NULL;
    }
}

void musicList::musicList_event_handler(lv_event_t *event)
{
    musicList* opt = (musicList*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    lv_obj_t* cont = lv_event_get_current_target(event);
	void  *iconPatch[2]={opt->LIST_UNSEL_PNG,opt->LIST_SEL_PNG};
    int inde =0;

    if(cont != target)
    {
        inde = (uintptr_t)cont->user_data;
    }
    else
    {
       inde =(uintptr_t)target->user_data;
    }
    if(opt->IconStation ==true)
    {
        if(opt->IconCheck !=true)
        {
            opt->IconCheck =true;
            opt->IconCheckAll =false;
        }
        if(opt->music_list_id.list_item[inde]->check_ok ==true)
        {
            opt->music_list_id.list_item[inde]->check_ok =false;
            opt->music_list_id.list_item[inde]->set_IconPtch(iconPatch[0]);
            opt->_del_selfilelist_curpatch(inde);
        }
        else
        {
            opt->music_list_id.list_item[inde]->check_ok =true;
            opt->music_list_id.list_item[inde]->set_IconPtch(iconPatch[1]);
            opt->_add_selfilelist(inde);
        }
		opt->checkedNum = opt->_get_selfilelist_total();
        opt->draw_headlist();
        
    }
	else
	{
	    opt->music_list_id.inde = inde;
		opt->checkedNum = inde;
	    opt->list_musicList->switch_select_state(opt->music_list_id.inde,lv_color_hex(0x0a85a6),lv_color_hex(0x00a7d4));
	    opt->IconPlay->set_main_bg_img_src(opt->MUSIC_UNSTOP_PNG);
	    opt->animCd->set_values(3600, 1);
	    opt->animCd->set_time(3000);
	    opt->animCd->set_repeat_count(LV_ANIM_REPEAT_INFINITE);
	    opt->animCd->start();
		opt->musicIndex =opt->music_list_id.inde;
		opt->music_list_start_playing();   
	}
}

void musicList::music_list_start_playing(void)
{
	char *file_path=NULL;
	char patch[1024]={0};
	MediaInfo *fileInfo =NULL;
	
	if((media_file_list !=NULL)&&(musicListTotal>0))
	{
		file_path = media_get_file_path(media_file_list,musicIndex);
		if(file_path !=NULL)
		{
			strcpy(patch,file_path);
			LV_LOG_USER("patch:%s",patch);
			tplayer_play_url(PlayerUiM->tplayer, patch);
			tplayer_play(PlayerUiM->tplayer);
			fileInfo= tplayer_get_media_Info(PlayerUiM->tplayer);
			if(fileInfo !=NULL)
			{
				sprintf(AlbumBuff,"%s",fileInfo->Id3Info->album);
				if(strlen(AlbumBuff)<=0)
				{
					strcpy(AlbumBuff,"null");
				}
				sprintf(ArtistBuff,"%s",fileInfo->Id3Info->artist);
				if(strlen(ArtistBuff)<=0)
				{
					strcpy(ArtistBuff,"null");
				}
			}
			else
			{
				strcpy(AlbumBuff,"null");
				strcpy(ArtistBuff,"null");
			}
			StrAlbum->set_txt(AlbumBuff);
			StrArtist->set_txt(ArtistBuff);
			playStatus = true;
			StartTimerShow =true;
			IconPlay->set_main_bg_img_src(MUSIC_UNSTOP_PNG);
            animCd->set_values(3600, 1);
            animCd->set_time(3000);
            animCd->set_repeat_count(LV_ANIM_REPEAT_INFINITE);
            animCd->start();
		}
	}
	
}

void musicList::music_list_stop_playing(void)
{
    tplayer_pause(PlayerUiM->tplayer);
	playStatus = false;
	StartTimerShow =false;
	IconPlay->set_main_bg_img_src(MUSIC_UNPLAY_PNG);
    animCd->set_time(1);
    animCd->set_repeat_count(0);
    animCd->start();
}

void musicList::play_prve_next_file(bool status)
{
    if(status ==true)
    {
		if(PlayMode !=1)
		{
		    musicIndex++;
			if(musicIndex >=musicListTotal)
			{
				musicIndex = 0;
			}
		}
		else 
		{
		    if(musicShuffleList !=NULL)
				musicIndex = musicShuffleList->shuffle_next();
		}
	}
	else
	{
		if(PlayMode !=1)
		{
			musicIndex--;
			if(musicIndex<0)
			{
				musicIndex = musicListTotal-1;
			}
		}
		else 
		{
		    if(musicShuffleList !=NULL)
				musicIndex = musicShuffleList->shuffle_prev();
		}
	}
	music_list_id.inde =musicIndex;
	if(musicListTotal>0)
	{
		if(musicIndex >6)
		{
			list_musicList->set_scroll_to(0,(musicIndex-6)*81, LV_ANIM_OFF);
		}
    	list_musicList->switch_select_state(musicIndex,lv_color_hex(0x0a85a6),lv_color_hex(0x00a7d4));
	}
	music_list_start_playing();
}

void musicList::play_next_file(void)
{
	if(PlayMode ==0)
	{
	    musicIndex++;
		if(musicIndex >=musicListTotal)
		{
			musicIndex = 0;
		}
	}
	else if(PlayMode ==1)
	{
	    if(musicShuffleList !=NULL)
			musicIndex = musicShuffleList->shuffle_next();
	}
	music_list_id.inde =musicIndex;
	if(musicListTotal>0)
	{
		list_musicList->set_scroll_to(0,musicIndex*81, LV_ANIM_OFF);
    	list_musicList->switch_select_state(musicIndex,lv_color_hex(0x0a85a6),lv_color_hex(0x00a7d4));
	}
	music_list_start_playing();
}

