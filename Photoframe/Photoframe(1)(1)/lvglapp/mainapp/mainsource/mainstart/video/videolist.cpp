#include  "../mainappstart.h"
#include  "videolist.h"
#include  "lvgl/src/extra/lv_extra.h"
#include  "mainstart/include/ui_config.h"
#include  "mainstart/include/str_config.h"
#ifdef _UCHIP_T113
#include "common/common.h"
#endif
#ifdef IMAGE_DECODE
static const void *iconName[4]={STR_FLASH_ALL,STR_FLASH_INTER,STR_FLASH_SD,STR_FLASH_USB};
#else
static const void *iconPatch[2]={LIST_UNSEL_PNG,LIST_SEL_PNG};
static const void *iconPatchMain[5]={LIST_ICON_ALL_PNG,LIST_ICON_FLASH_PNG,LIST_ICON_SD_PNG,LIST_ICON_U_PNG,LIST_ICON_USER_PNG};
static const void *iconName[4]={STR_FLASH_ALL,STR_FLASH_INTER,STR_FLASH_SD,STR_FLASH_USB};
#endif

typedef struct
{
    char video_path[128];
}videolist_file_info;

#ifdef _UCHIP_T113
static media_file_list_t *media_file_list = NULL;
#endif

static videolist_file_info video_info[VIDEODEC_MAX];
static void * video_image= NULL;

void videoList::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    HEAD_RETURN_PNG=(void*)parse_image_from_file(HEAD_RETURN_PNG_PATH);
    HEAD_RETURN_SEL_PNG=(void*)parse_image_from_file(HEAD_RETURN_SEL_PNG_PATH);

    HEAD_ICON_VIDEO_PNG=(void*)parse_image_from_file(HEAD_ICON_VIDEO_PNG_PATH);

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

    VIDEO_UNPLAYING_PNG=(void*)parse_image_from_file(VIDEO_UNPLAYING_PNG_PATH);
    VIDEO_PLAYING_PNG=(void*)parse_image_from_file(VIDEO_PLAYING_PNG_PATH);
    VIDEO_BTN_PNG=(void*)parse_image_from_file(VIDEO_BTN_PNG_PATH);

#endif

}
void videoList::ui_image_free(void)
{
#ifdef IMAGE_DECODE
    free_image(HEAD_RETURN_PNG);
    free_image(HEAD_RETURN_SEL_PNG);

    free_image(HEAD_ICON_VIDEO_PNG);

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
	
	free_image(VIDEO_UNPLAYING_PNG);
    free_image(VIDEO_PLAYING_PNG);
    free_image(VIDEO_BTN_PNG);
#endif

}

static int videolist_url_htoi(char *s)
{
    int value;
    int c;

    c = ((unsigned char *)s)[0];
    if (isupper(c))
        c = tolower(c);
    value = (c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10) * 16;

    c = ((unsigned char *)s)[1];
    if (isupper(c))
        c = tolower(c);
    value += c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10;

    return (value);
}

int _videolist_url_decode(char *str, int len)
{
    char *dest = str;
    char *data = str;

    while (len--)
    {
        if (*data == '+')
        {
            *dest = ' ';
        }
        else if (*data == '%' && len >= 2 && isxdigit((int) *(data + 1)) && isxdigit((int) *(data + 2)))
        {
            *dest = (char) videolist_url_htoi(data + 1);
            data += 2;
            len -= 2;
        }
        else
        {
            *dest = *data;
        }
        data++;
        dest++;
    }
    *dest = '\0';
    return dest - str;
}

static int videolist_userInfo(int userNum,char *userID)
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
int videolist_get_userNum(void)
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
			num ++;
        }
    }
	return num;
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

char *videoList::_get_cur_filelist_patch(int index)
{
	Vfile_info_t* tmp_list;
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
void videoList::selfilelist_add_node(Vfile_info_t *node)
{
    Vfile_info_t *tmp_list;

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
int videoList::_get_selfilelist_total(void)
{
    Vfile_info_t* tmp_list;
    int numTotal =0;

    tmp_list = SelFileList;

    while(tmp_list != NULL)
    {
        numTotal ++;
        tmp_list = tmp_list->next_list;
    }
    return numTotal;
}
void videoList::_del_selfilelist(void)
{
    Vfile_info_t* tmp_list;
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
void videoList::_cpy_selfilelist(void)
{
    Vfile_info_t* tmp_list;
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
static Vfile_info_t *_del_selfilelist_curpatch_head(Vfile_info_t *head_list)
{
	Vfile_info_t *tmp_list;
	
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
void videoList::_del_selfilelist_curpatch(int index)
{
    Vfile_info_t *tmp_list_prev;
    Vfile_info_t *tmp_list_last;

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

void videoList::_add_selfilelist(int index)
{
    Vfile_info_t* tmp_list;
	char patch[1024]={0};
	int ret =0;
	
	if(media_file_list != NULL)
	{
		ret = rat_npl_index2file(media_file_list->media_hrat, index, patch);
		if(ret == EPDK_OK)
		{
			tmp_list = (Vfile_info_t*)malloc(sizeof(Vfile_info_t));
		    memset(tmp_list,0,sizeof(Vfile_info_t));
			tmp_list->myindex =index;
		    sprintf(tmp_list->filePath,"%s",patch);
		    selfilelist_add_node(tmp_list);
		}
	}   
}
void videoList::_destory_selfilelist(void)
{
    Vfile_info_t * tmp_list_prev;
    Vfile_info_t * tmp_list_last;

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

void videoList::_add_allfilelist(void)
{
	void *iconPatch[2]={LIST_UNSEL_PNG,LIST_SEL_PNG};
	int i =0;

	for(i=0;i<video_list_id.count;i++)
	{
		if(video_list_id.list_item[i]!=NULL)
		{
			video_list_id.list_item[i]->set_IconPtch(iconPatch[1]);
            video_list_id.list_item[i]->check_ok =true;
			_add_selfilelist(i);
		}
	}
	checkedNum = _get_selfilelist_total();
}

void videoList::check_disk_status(void)
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
videoList::videoList(lv_obj_t* parent)
{
	if(myfont==nullptr)
	{
		myfont = new LvcppFreeTypeFont(26,0);
	}
	sunxi_image_init();
	ui_image_decode();
    frame = new LvcppScreen(parent);
    frame->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    frame->set_main_bg_color(lv_color_black(),LV_OPA_0);
    frame->set_main_bg_img_src(LISTBG_PNG);
    mainscreen = frame->myobj;
    IconStation =false;
    IconCheck =false;
}


videoList::~videoList(void)
{
    video_list_head_dele();
    videomian_list_dele();
    videoList_list_delete();
	_destory_selfilelist();
	videolist_del_mute_dele();
	videolist_cpy_mute_dele();
	
    if(btnBIcon != NULL)
    {
        delete btnBIcon;
        btnBIcon =NULL;
    }
    if(btnBChild != NULL)
    {
        delete btnBChild;
        btnBChild =NULL;
    }
    if(btnB != NULL)
    {
        delete btnB;
        btnB =NULL;
    }
    if(labA != NULL)
    {
        delete labA;
        labA =NULL;
    }
    if(btnAIcon != NULL)
    {
        delete btnAIcon;
        btnAIcon =NULL;
    }
    if(videoThum != NULL)
    {
        delete videoThum;
        videoThum =NULL;
    }
    if(frame !=NULL)
    {
        delete frame;
        frame =NULL;
    }
	if(LIST_ICON_USERON_PNG !=NULL)
    {
        sunxi_image_free(LIST_ICON_USERON_PNG);
        LIST_ICON_USERON_PNG =NULL;
    }
	video_decode_delete();
	ui_image_free();
	sunxi_image_exit();
	if(myfont!=nullptr)
	{
		delete myfont;
		myfont = nullptr;
	}
}

LvcppButton* videoList::LvcppButtonHead(lv_obj_t* paren,bool show_cb,lv_ui_inof_t *uiInfo)
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

LvcppLabel* videoList::LvcppLabelViewChild(lv_obj_t* paren,lv_text_align_t align,lv_str_inof_t *strInfo)
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
void videoList::videoList_clean_fileInfo(int start)
{
	int i=0,fileNum =0;
	char *path =NULL;
	char *file_path =NULL;
	
	for(i=start;i<videoListTotal;i++)
	{
		if(fileNum<VIDEODEC_MAX)
		{
			memset(video_info[fileNum].video_path,0,sizeof(video_info[fileNum].video_path));
			if(media_file_list !=NULL)
			{
				path = media_get_file_path(media_file_list,i);
				if(path !=NULL)
				{
					file_path = media_get_path_to_name(path);
					if(file_path !=NULL)
					{
						strcpy(video_info[fileNum].video_path,file_path);
					}
				}
			}
		}
		fileNum++;
	}
}
int videoList::videoList_media_creat(void)
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
	/*for(i=0;i<VIDEODEC_MAX;i++)
	{
		memset(video_info[i].video_path,0,sizeof(video_info[i].video_path));
	}
	*/
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
		else if(flash_inde ==3)
		{
			strcpy(MountPoint,"/mnt/exUDISK");
		}
		else
		{
			if(videolist_userInfo((flash_inde -VIDEOLIST_MAX),userPatch)<0)
				return 0;
			else
				sprintf(MountPoint,"/mnt/UDISK/%s",userPatch);	
		}
		LV_LOG_USER("MountPoint:%s",MountPoint);
		media_file_list = media_load_file(RAT_MEDIA_TYPE_VIDEO, MountPoint);
		if (NULL == media_file_list)
		{
			LV_LOG_USER("%s don't find video list\n",MountPoint);
			videoListTotal = 0;
			videoIndex =0;
		}
		else
		{
			videoListTotal = media_file_list->total_num;
			videoIndex = media_get_index_from_path(media_file_list,video_listpatch);
			if(videoIndex<0)
			{
				videoIndex =0;
				file_path = media_get_file_path(media_file_list,i);
				if(file_path !=NULL)
				{
					strcpy(video_listpatch,file_path);
				}
			}
		}
		
		//videoList_clean_fileInfo(0);
		if(videoListTotal <=0)
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
	return 0;
}
int videoList::init_parament(int disk_type,char* file_patch)
{
	frame->show(true);

    if(file_patch !=NULL)
    {
        strcpy(video_listpatch,file_patch);
    }
    flash_inde = disk_type;
	flash_total = (int)(videolist_get_userNum()+VIDEOLIST_MAX);
	video_list_head_creat();
	videoList_media_creat();

    videoThum = new LvcppButton(mainscreen);
    videoThum->set_size(548,386);
    videoThum->align_to(mainscreen,LV_ALIGN_TOP_LEFT,682,262);
    videoThum->set_main_bg_color(lv_color_black(),LV_OPA_100);
    videoThum->set_main_radius(0);
    videoThum->set_main_pad_all(0);
    videoThum->set_main_border_width(0);
	
    btnAIcon = new LvcppImageButton(mainscreen);
    btnAIcon->set_size(20,20);
    btnAIcon->align_to(mainscreen,LV_ALIGN_TOP_LEFT,680,672);
    btnAIcon->set_main_bg_opa(LV_OPA_0);
    btnAIcon->set_main_radius(0);
    btnAIcon->set_main_pad_all(0);
    btnAIcon->set_main_border_width(0);
    btnAIcon->set_main_bg_img_src(VIDEO_BTN_PNG);

    labA = new LvcppLabel(mainscreen);
    labA->set_size(250,40);
    labA->align_to(btnAIcon->myobj,LV_ALIGN_OUT_RIGHT_TOP, 5, -5);
    labA->txt_font_size(26, FT_FONT_STYLE_NORMAL);
    labA->txt_align(LV_TEXT_ALIGN_LEFT);
    labA->txt_color(lv_color_white(),LV_PART_MAIN);
	labA->set_txt(videoSize);
    
    btnB = new LvcppButton(mainscreen);
    btnB->set_size(270,40);
    btnB->align_to(mainscreen,LV_ALIGN_TOP_LEFT,960,665);
    btnB->set_main_radius(0);
    btnB->set_main_pad_all(0);
    btnB->set_main_pad_row(0);
    btnB->set_main_bg_opa(LV_OPA_0);

    btnBChild = new LvcppButton(btnB->myobj);
    btnBChild->set_size(250,40);
    btnBChild->center_align();
    btnBChild->set_main_radius(0);
    btnBChild->set_main_pad_all(0);
    btnBChild->set_main_pad_row(0);
    btnBChild->set_main_bg_opa(LV_OPA_0);
    btnBChild->txt_long_mode(LV_LABEL_LONG_WRAP);
    btnBChild->txt_align(LV_ALIGN_RIGHT_MID,0,0);
    btnBChild->add_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
    btnBChild->txt_color(lv_color_white());
	btnBChild->add_txt(videoNum);

    btnBIcon = new LvcppImageButton(btnB->myobj);
    btnBIcon->set_size(20,20);
	btnBIcon->align(LV_ALIGN_RIGHT_MID,-45,0);
    btnBIcon->set_main_radius(0);
    btnBIcon->add_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
    btnBIcon->set_main_bg_img_src(VIDEO_BTN_PNG);

    video_list_creat();
    videoList_list_creat();
    draw_btn_info();
	
    return 0;
}


int videoList::video_decode_start(void)
{
	int ret=-1;
	char path[1024] = {0};
	LV_LOG_USER("video_decode_start");

	memset(videoSize,0,sizeof(videoSize));
	memset(videoNum,0,sizeof(videoNum));
	if((media_file_list != NULL)&&(videoListTotal>0))
	{
		memset(path,0, sizeof(path));
		ret = rat_npl_index2file(media_file_list->media_hrat, videoIndex, path);
		if(ret != EPDK_OK) {
			printf("rat_npl_index2file fail!\n");
			return ret;
		}
		LV_LOG_USER("[%d]path:%s",videoIndex,path);
		_get_file_size(path,videoSize);
		sprintf(videoNum,"%d/%d",(video_list_id.inde +1),videoListTotal);
#ifdef _UCHIP_T113
		if(video_image!=NULL)
		{
			sunxi_image_free(video_image);
			video_image=NULL;
		}
		if(media_get_file_type(media_file_list,videoIndex)==RAT_MEDIA_TYPE_VIDEO)
		{
			video_image = video_frame_image_scaler(path,30,548,386);
		}
		else if(media_get_file_type(media_file_list,videoIndex)==RAT_MEDIA_TYPE_PIC)
		{
			video_image =sunxi_image_decode_scaler(path,548,386);
		}
		videoThum->set_main_bg_img_src(video_image);//video_scaler_image
#endif
	}
	draw_btn_info();
	LV_LOG_USER("video_decode_start end");
	return 0;
}

void videoList::video_decode_delete(void)
{
	if(video_image!=NULL)
	{
		sunxi_image_free(video_image);
		video_image=NULL;
	}
	if(media_file_list!=NULL)
	{
		media_unload_file(media_file_list);
		media_file_list = NULL;
	}
}

int videoList::draw_btn_info(void)
{
	if(labA)
	{
    	labA->set_txt(videoSize);
	}
	if(btnBChild)
	{
    	btnBChild->add_txt(videoNum);
	}
    return 0;
}
void videoList::videolist_del_mute_creat(void)
{
    delButton = new LvcppButton(mainscreen);
    delButton->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    delButton->set_main_bg_color(lv_color_black(),LV_OPA_60);
    delButton->add_event_cb(videolist_del_event_handler,LV_EVENT_CLICKED,this);

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
    delChildButtonCancel->add_event_cb(videolist_del_event_handler,LV_EVENT_PRESSED,this);
    delChildButtonCancel->add_event_cb(videolist_del_event_handler,LV_EVENT_RELEASED,this);
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
    delChildButtonOk->add_event_cb(videolist_del_event_handler,LV_EVENT_PRESSED,this);
    delChildButtonOk->add_event_cb(videolist_del_event_handler,LV_EVENT_RELEASED,this);
    delChildButtonOk->txt_size(SCREEN_HOR_SIZE/4-20, SCREEN_VER_SIZE/12-10, LV_LABEL_LONG_WRAP);
    delChildButtonOk->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    delChildButtonOk->txt_center();
    delChildButtonOk->txt_color(lv_color_white());
    delChildButtonOk->add_txt(STR_OK);
}

void videoList::videolist_del_mute_dele(void)
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
void videoList::videolist_del_event_handler(lv_event_t *event)
{
    videoList* opt = (videoList*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target==opt->delButton->myobj)
    {
        opt->videolist_del_mute_dele();
        opt->draw_headlist();
    }
    else if(target==opt->delChildButtonCancel->myobj)
    {
        if(event->code == LV_EVENT_RELEASED)
        {
            opt->videolist_del_mute_dele();
            opt->draw_headlist();
        }
    }
    else if(target==opt->delChildButtonOk->myobj)
    {
        if(event->code == LV_EVENT_RELEASED)
        {
            opt->videolist_del_mute_dele();
			opt->IconCheck =false;
			opt->IconStation =false;
            opt->IconDel->show(false);
			opt->IconChe->show(false);
			opt->IconCpy->show(false);
			opt->IconSor->show(false);
            opt->StrIconNum->show(false);
            opt->_del_selfilelist();
            opt->draw_headlist();
			opt->videoList_list_delete();
			opt->videoList_media_creat();
			opt->videoList_list_creat();
        }
    }
}

void videoList::videolist_cpy_mute_creat(void)
{
    cpyButton = new LvcppButton(mainscreen);
    cpyButton->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    cpyButton->set_main_bg_color(lv_color_black(),LV_OPA_60);
    cpyButton->add_event_cb(videolist_cpy_event_handler,LV_EVENT_CLICKED,this);

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
            cpyCheckBox1->add_event_cb(videolist_cpy_event_handler,LV_EVENT_CLICKED,this);

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
            cpyCheckBox2->add_event_cb(videolist_cpy_event_handler,LV_EVENT_CLICKED,this);

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
    cpyChildButtonCancel->add_event_cb(videolist_cpy_event_handler,LV_EVENT_PRESSED,this);
    cpyChildButtonCancel->add_event_cb(videolist_cpy_event_handler,LV_EVENT_RELEASED,this);
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
    cpyChildButtonOk->add_event_cb(videolist_cpy_event_handler,LV_EVENT_PRESSED,this);
    cpyChildButtonOk->add_event_cb(videolist_cpy_event_handler,LV_EVENT_RELEASED,this);
    cpyChildButtonOk->txt_size(SCREEN_HOR_SIZE/4-20, SCREEN_VER_SIZE/12-10, LV_LABEL_LONG_WRAP);
    cpyChildButtonOk->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    cpyChildButtonOk->txt_center();
    cpyChildButtonOk->txt_color(lv_color_white());
    cpyChildButtonOk->add_txt(STR_OK);
}

void videoList::videolist_cpy_mute_dele(void)
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
void videoList::videolist_cpy_event_handler(lv_event_t *event)
{
    videoList* opt = (videoList*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target==opt->cpyButton->myobj)
    {
        opt->videolist_cpy_mute_dele();
        opt->draw_headlist();
    }
    else if(target==opt->cpyChildButtonCancel->myobj)
    {
        if(event->code == LV_EVENT_RELEASED)
        {
            opt->videolist_cpy_mute_dele();
            opt->draw_headlist();
        }
    }
    else if(target==opt->cpyChildButtonOk->myobj)
    {
        if(event->code == LV_EVENT_RELEASED)
        {
            opt->videolist_cpy_mute_dele();
			opt->IconCheck =false;
			opt->IconStation =false;
            opt->IconDel->show(false);
			opt->IconChe->show(false);
			opt->IconCpy->show(false);
			opt->IconSor->show(false);
            opt->StrIconNum->show(false);
			opt->draw_headlist();
			opt->_cpy_selfilelist();
            opt->draw_videoListIcon_list(false);
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

void videoList::video_list_head_creat(void)
{
    lv_ui_inof_t uiInfo;
    lv_str_inof_t strInfo;
    char buff[12]={0};

	uiInfo.x =926;
    uiInfo.y =401;
    uiInfo.w =78;
    uiInfo.h =78;
    uiInfo.userdata =HEAD_ICON_PLAYING;
    uiInfo.ui_patch =(char *)VIDEO_UNPLAYING_PNG;
    IconPlaying =LvcppButtonHead(mainscreen,true,&uiInfo);
	
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
    uiInfo.ui_patch =(char *)HEAD_ICON_VIDEO_PNG;
    videoIcon =LvcppButtonHead(mainscreen,false,&uiInfo);
    videoIcon->set_userdata(NULL);

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
}

void videoList::draw_headlist(void)
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

void videoList::video_list_head_dele(void)
{
    if(IconPlaying != NULL)
    {
        delete IconPlaying;
        IconPlaying =NULL;
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
    if(buttonReturn != NULL)
    {
        delete buttonReturn;
        buttonReturn =NULL;
    }
    if(videoIcon != NULL)
    {
        delete videoIcon;
        videoIcon =NULL;
    }
}

void videoList::head_event_handler(lv_event_t *event)
{
    videoList* opt = (videoList*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    int set_selete = (uintptr_t)target->user_data;

    switch(set_selete)
    {
        case HEAD_ICON_RETURN:
            if(event->code== LV_EVENT_PRESSED)
            {
                opt->buttonReturn->set_main_bg_img_src(opt->HEAD_RETURN_SEL_PNG);
            }
            else
            {
                 MainAPPStart::videoMain_destory();
				 return;
            }
        break;
        case HEAD_ICON_PLAYING:
            if(event->code== LV_EVENT_PRESSED)
            {
                opt->IconPlaying->set_main_bg_img_src(opt->VIDEO_PLAYING_PNG);
            }
            else
            {
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
					opt->videolist_cpy_mute_creat();
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
					opt->videolist_del_mute_creat();
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
					opt->set_videoListIcon_list(false);
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
					opt->draw_videoListIcon_list(true);
                }
                else
                {
                    opt->IconBack->set_main_bg_img_src(opt->LIST_ICON_ICON_PNG);
                    opt->IconDel->show(false);
                    opt->IconChe->show(false);
					opt->IconCpy->show(false);
					opt->IconSor->show(false);
                    opt->StrIconNum->show(false);
					opt->draw_videoListIcon_list(false);
                }
                opt->draw_headlist();
            }
        break;
        default:
            break;
    }
}

int videoList::video_list_creat(void)
{
	if(list_main==NULL)
	{
    	list_main = new LvcppList(mainscreen);
	}
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

    memset(&main_list_id, 0 , sizeof(main_videolist_item_info));
    videomian_list_add();
	list_main->set_scroll_to(flash_inde*318,0, LV_ANIM_OFF);
    list_main->set_select_state(flash_inde,lv_color_hex(0x00a7d4));
    return 0;
}

int videoList::videomian_list_add(void)
{
    char buff[64]={0};
	char userBuff[64]={0};
	char LogoBuff[128]={0};
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
	
    #ifdef IMAGE_DECODE
    void *iconPatchMain[5]={LIST_ICON_ALL_PNG,LIST_ICON_FLASH_PNG,LIST_ICON_SD_PNG,LIST_ICON_U_PNG,LIST_ICON_USER_PNG};
    #endif

    for(int i=main_list_id.count;i < flash_total;i++)
    {
        main_list_id.list_item[i] = new frameListIconCenter(list_main->myobj,&btn_info,WHITE_COLOR,&icon_info);
        main_list_id.list_item[i]->btn->add_event_cb(main_event_handler,LV_EVENT_CLICKED,this);
        main_list_id.list_item[i]->btn->set_userdata(NULL);
        main_list_id.list_item[i]->btn->set_userdata((void*)i);
        if(i<VIDEOLIST_MAX)
        {
            strcpy(main_list_id.list_item[i]->IconName,(const char*)iconName[i]);
            main_list_id.list_item[i]->set_IconName();
            main_list_id.list_item[i]->set_IconPtch(42,(char*)iconPatchMain[i]);
        }
        else
        {
        	memset(buff,0,sizeof(buff));
            if(videolist_userInfo((i-VIDEOLIST_MAX),userBuff)<0)
            {
				sprintf(main_list_id.list_item[i]->IconName,"%s%d","User",(i-VIDEOLIST_MAX));
                main_list_id.list_item[i]->set_IconPtch(42,(char *)iconPatchMain[VIDEOLIST_MAX]);
            }
			else
			{    
				memset(buff,0,sizeof(buff));
	            if(read_string_userinfo_param(userBuff,SENDERREMARKNAME,buff,sizeof(buff))<0)
	            {
	                memset(buff,0,sizeof(buff));
	                if(read_string_userinfo_param(userBuff,SENDERNICKNAME,buff,sizeof(buff))<0)
	                {
	                    memset(buff,0,sizeof(buff));
	                    if(read_string_userinfo_param(userBuff,SENDNAME,buff,sizeof(buff))<0)
	                    {
	                        sprintf(buff,"%s",userBuff);
	                    }
	                    else
	                    {
	                        _videolist_url_decode(buff,strlen(buff));
	                    }
	                }
	                else
	                {
	                    _videolist_url_decode(buff,strlen(buff));
	                }
	            }
				else
				{
					_videolist_url_decode(buff,strlen(buff));
				}
            }
			sprintf(main_list_id.list_item[i]->IconName,"%s",buff);
            main_list_id.list_item[i]->set_IconName();
			sprintf(LogoBuff,"/mnt/UDISK/%s.png",userBuff);
			if(0 != access(LogoBuff, 0))
			{
				main_list_id.list_item[i]->set_IconPtch(42,(char *)iconPatchMain[VIDEOLIST_MAX]);
			}
			else
			{
#ifdef _UCHIP_T113
				/*
			    if(LIST_ICON_USERON_PNG !=NULL)
			    {
			        sunxi_image_free(LIST_ICON_USERON_PNG);
			        LIST_ICON_USERON_PNG =NULL;
			    }
			    LIST_ICON_USERON_PNG=(void*)sunxi_image_decode_scaler(LogoBuff,icon_info.w,icon_info.h);
			    main_list_id.list_item[i]->set_IconPtch(42,(void *)LIST_ICON_USERON_PNG);*/
#endif
			}
        }
        main_list_id.count++;
    }
    return 0;
}

void videoList::videomian_list_dele(void)
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

void videoList::main_event_handler(lv_event_t *event)
{
    videoList* opt = (videoList*) event->user_data;
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
	opt->videoList_list_delete();
	opt->videoList_media_creat();
	opt->videoList_list_creat();
}

int videoList::videoList_list_creat(void)
{
    list_videoList = new LvcppList(mainscreen);
    list_videoList->set_size(610,548);
    list_videoList->align(LV_ALIGN_TOP_LEFT,20,212);
    list_videoList->set_flex_flow(LV_FLEX_FLOW_COLUMN);
    list_videoList->set_scrollbar_mode(LV_SCROLLBAR_MODE_ON);
    list_videoList->set_scrollbar_dir(LV_DIR_VER);
    list_videoList->set_main_bg_opa(LV_OPA_0);
    list_videoList->set_main_pad_all(0);
    list_videoList->set_main_pad_row(2);
    list_videoList->set_main_pad_column(0);
    list_videoList->set_main_border_width(0);
    list_videoList->set_main_radius(0);

    memset(&video_list_id, 0 , sizeof(videolist_item_info));
	if(media_file_list!=NULL)
	{
		if(media_get_file_type(media_file_list,videoIndex)==RAT_MEDIA_TYPE_VIDEO||
			media_get_file_type(media_file_list,videoIndex)==RAT_MEDIA_TYPE_PIC)
		{
			video_decode_start();
		}
		else
		{
		#ifdef _UCHIP_T113
			if(video_image!=NULL)
			{
				sunxi_image_free(video_image);
				video_image=NULL;
			}
		#endif
			videoThum->set_main_bg_img_src(NULL);//video_scaler_image
		}
	}
    videoList_list_add();
    return 0;
}

int videoList::videoList_list_add(void)
{
	void *iconPatch[2]={LIST_UNSEL_PNG,LIST_SEL_PNG};
    framelist_btn_t btn_info;
    framelist_txt_t txt_info;
    framelist_icon_t icon_info;
	char *path =NULL;
	char *file_path =NULL;
	char video_path[128]={0};

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

    for(int i=video_list_id.count;i < videoListTotal;i++)
    {
        icon_info.iconPatch = (char*)iconPatch[0];
        video_list_id.list_item[i] = new frameListIcon(list_videoList->myobj,&btn_info,&txt_info,&icon_info);
		memset(video_path,0,sizeof(video_path));
		if(media_file_list !=NULL)
		{
			path = media_get_file_path(media_file_list,i);
			if(path !=NULL)
			{
				file_path = media_get_path_to_name(path);
				if(file_path !=NULL)
				{
					strcpy(video_path,file_path);
				}
			}
		}
		video_list_id.list_item[i]->set_IconName(video_path);
        video_list_id.list_item[i]->btn->add_event_cb(videoList_event_handler,LV_EVENT_CLICKED,this);
        video_list_id.list_item[i]->btn->set_userdata(NULL);
        video_list_id.list_item[i]->btn->set_userdata((void*)i);
        video_list_id.list_item[i]->icon->show(false);
        video_list_id.count++;
    }

	if(videoListTotal>0)
	{
		video_list_id.inde = videoIndex;
		list_videoList->set_scroll_to(0,videoIndex*81, LV_ANIM_OFF);
    	list_videoList->set_select_state(video_list_id.inde,lv_color_hex(0x00a7d4));
	}
    return 0;
}

void videoList::set_videoListIcon_list(bool type)
{
	void *iconPatch[2]={LIST_UNSEL_PNG,LIST_SEL_PNG};
    for(int i=0;i<video_list_id.count;i++)
    {
        if(type == true)
        {
            video_list_id.list_item[i]->set_IconPtch(iconPatch[1]);
            video_list_id.list_item[i]->check_ok =true;
        }
        else
        {
           video_list_id.list_item[i]->set_IconPtch(iconPatch[0]);
           video_list_id.list_item[i]->check_ok =false;
        }
    }
}

void videoList::draw_videoListIcon_list(bool type)
{
    for(int i=0;i<video_list_id.count;i++)
    {
        if(type == true)
        {
            list_videoList->set_select_state(video_list_id.inde,lv_color_hex(0x0a85a6));
            video_list_id.list_item[i]->btn->txt_align(LV_ALIGN_TOP_LEFT,50,24);
            video_list_id.list_item[i]->icon->show(true);
        }
        else
        {
            video_list_id.list_item[i]->check_ok =false;
            video_list_id.list_item[i]->btn->txt_align(LV_ALIGN_TOP_LEFT,10,24);
            video_list_id.list_item[i]->icon->show(false);
            list_videoList->set_select_state(video_list_id.inde,lv_color_hex(0x00a7d4));
        }
    }
}

void videoList::videoList_list_delete(void)
{
    for(int i=video_list_id.count;i>0;i--)
    {
        video_list_id.count--;
        if(video_list_id.list_item[video_list_id.count] !=NULL)
        {
            delete video_list_id.list_item[video_list_id.count];
            video_list_id.list_item[video_list_id.count] =NULL;
        }
    }
    if(list_videoList !=NULL)
    {
        delete list_videoList;
        list_videoList =NULL;
    }
}

void videoList::videoList_event_handler(lv_event_t *event)
{

    videoList* opt = (videoList*) event->user_data;
	void *iconPatch[2]={opt->LIST_UNSEL_PNG,opt->LIST_SEL_PNG};
    lv_obj_t* target = lv_event_get_target(event);
    lv_obj_t* cont = lv_event_get_current_target(event);
    int inde =0,ret=0;
	char filepath[1024]={0};

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
        if(opt->video_list_id.list_item[inde]->check_ok ==true)
        {
            opt->video_list_id.list_item[inde]->check_ok =false;
            opt->video_list_id.list_item[inde]->set_IconPtch(iconPatch[0]);
            opt->_del_selfilelist_curpatch(inde);
        }
        else
        {
            opt->video_list_id.list_item[inde]->check_ok =true;
            opt->video_list_id.list_item[inde]->set_IconPtch(iconPatch[1]);
            opt->_add_selfilelist(inde);
        }
		opt->checkedNum = opt->_get_selfilelist_total();
        opt->draw_headlist();
    }
	else
	{
	    opt->video_list_id.inde = inde;
	    if(opt->video_list_id.inde != opt->videoIndex)
    	{
			opt->list_videoList->switch_select_state(opt->video_list_id.inde,lv_color_hex(0x0a85a6),lv_color_hex(0x00a7d4));
			opt->videoIndex = opt->video_list_id.inde;
			if(media_file_list!=NULL)
			{
				if(media_get_file_type(media_file_list,opt->videoIndex)==RAT_MEDIA_TYPE_VIDEO ||
				    media_get_file_type(media_file_list,opt->videoIndex)==RAT_MEDIA_TYPE_PIC)
				{
					opt->video_decode_start();
				}
				else
				{
				#ifdef _UCHIP_T113
					if(video_image!=NULL)
					{
						sunxi_image_free(video_image);
						video_image=NULL;
					}
				#endif
					opt->videoThum->set_main_bg_img_src(NULL);//video_scaler_image
				}
			}
		}
		else
		{
			if(media_file_list != NULL)
			{
				ret = rat_npl_index2file(media_file_list->media_hrat, opt->video_list_id.inde,filepath);
				if(ret == EPDK_OK)
				{
					videoMain::enterVideoPlay(opt->flash_inde,filepath);
				}
			}
		}
	}
}
