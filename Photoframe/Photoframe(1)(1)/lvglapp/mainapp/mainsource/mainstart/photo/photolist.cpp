#include  "../mainappstart.h"
#include  "photolist.h"
#include  "lvgl/src/extra/lv_extra.h"
#include  "mainstart/include/ui_config.h"
#include  "mainstart/include/str_config.h"

#ifdef IMAGE_DECODE
static const void *iconName[5]={STR_FLASH_ALL,STR_FLASH_INTER,STR_FLASH_SD,STR_FLASH_USB,STR_FLASH_FAVOR};
#else
static const void *iconPatch[6]={LIST_ICON_ALL_PNG,LIST_ICON_FLASH_PNG,LIST_ICON_SD_PNG,LIST_ICON_U_PNG,
                           LIST_ICON_LOVE_PNG,LIST_ICON_USER_PNG};
static const void *iconName[5]={STR_FLASH_ALL,STR_FLASH_INTER,STR_FLASH_SD,STR_FLASH_USB,STR_FLASH_FAVOR};
#endif

#ifdef _UCHIP_T113
static media_file_list_t *media_file_list = NULL;
#endif
static int stop_decode_thread_ruing =0;
static bool s_decode_stop_flag = false;
photoList* PHOTOList =NULL;
static sem_t photosem;
static pthread_mutex_t s_pthread_mutex;
static pthread_cond_t s_pthread_cond;
static pthread_t s_pthread;
static pthread_t s_pthread_stop;
static bool s_decode_thread_inited = false;
static bool s_decode_thread_inited_stop = false;
static bool pthreadMutexStatu =false;

void photoList::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    HEAD_RETURN_PNG=(void*)parse_image_from_file(HEAD_RETURN_PNG_PATH);
    HEAD_RETURN_SEL_PNG=(void*)parse_image_from_file(HEAD_RETURN_SEL_PNG_PATH);
    HEAD_ICON_PHOTO_PNG=(void*)parse_image_from_file(HEAD_ICON_PHOTO_PNG_PATH);

	LISTBG_PNG=(void*)parse_image_from_file(LISTBG_PNG_PATH);
    LIST_ICON_ALL_PNG=(void*)parse_image_from_file(LIST_ICON_ALL_PNG_PATH);
    LIST_ICON_FLASH_PNG=(void*)parse_image_from_file(LIST_ICON_FLASH_PNG_PATH);
    LIST_ICON_SD_PNG=(void*)parse_image_from_file(LIST_ICON_SD_PNG_PATH);
    LIST_ICON_U_PNG=(void*)parse_image_from_file(LIST_ICON_U_PNG_PATH);
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
    PHOTO_PNG=(void*)parse_image_from_file(PHOTO_PNG_PATH);
#endif
}
void photoList::ui_image_free(void)
{
#ifdef IMAGE_DECODE
    free_image(HEAD_RETURN_PNG);
    free_image(HEAD_RETURN_SEL_PNG);
    free_image(HEAD_ICON_PHOTO_PNG);
    free_image(LIST_ICON_ALL_PNG);
    free_image(LIST_ICON_FLASH_PNG);
    free_image(LIST_ICON_SD_PNG);
    free_image(LIST_ICON_U_PNG);
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
    free_image(LISTBG_PNG);
    free_image(PHOTO_PNG);
	free_image(LIST_CIRCLE_PNG);
	free_image(LIST_CIRCLESEL_PNG);
#endif
}
static void _decode_lock_init(void)
{
    sem_init(&photosem, 0, 0);
}
static int _decode_write_lock(void)
{
	int val = 0;
	sem_getvalue(&photosem, &val);
    sem_wait(&photosem);
    return 0;
}
static int _decode_write_unlock(void)
{
    int val = 0;
	
    sem_getvalue(&photosem, &val);
	//LV_LOG_USER("val:%d",val);
	if(val > 0)
    {
        return 0;
    }
    sem_post(&photosem);
    return 0;
}
static void _decode_lock_deinit(void)
{
    sem_destroy(&photosem);
}
static void _mutex_lock_init(void)
{
    pthread_mutex_init(&s_pthread_mutex,NULL);
	pthreadMutexStatu =true;
}
static void _mutex_write_lock(void)
{
	if(pthreadMutexStatu)
	{
		pthread_mutex_lock(&s_pthread_mutex);
	}
}

static void _mutex_write_unlock(void)
{
	if(pthreadMutexStatu)
	{
		pthread_mutex_unlock(&s_pthread_mutex);
	}
}
static void _mutex_lock_deinit(void)
{
	if(pthreadMutexStatu)
	{
	    pthread_mutex_destroy(&s_pthread_mutex);
		pthreadMutexStatu =false;
	}
}
static bool photo_thread_decode_thumb_create(void *(*start_rtn)(void*))
{
    s_decode_thread_inited = true;
	
    if(0 > pthread_create(&s_pthread, NULL, start_rtn, NULL))
    {
        LV_LOG_USER("\ncreate clien_start_dns_task fail!\n");
    }
    return true;
}
static bool photo_thread_decode_thumb_delete(void)
{
    if (s_decode_thread_inited != true)
    {
        return true;
    }
    if(s_pthread != 0)
    {
        pthread_join(s_pthread, NULL);
    }
    memset(&s_pthread, 0x00, sizeof(s_pthread));
	s_decode_thread_inited = false;
    return true;
}
static int stop_decode_thread(void *(*start_rtn)(void*))
{
	s_decode_thread_inited_stop =true;
    if(0 > pthread_create(&s_pthread_stop, NULL, start_rtn, NULL))
    {
        LV_LOG_USER("\n stop_decode_thread fail!\n");
    }
    return 0;
}
static bool stop_decode_thread_delete(void)
{
    if (s_decode_thread_inited_stop != true)
    {
        return true;
    }
    if(s_pthread_stop != 0)
    {
        pthread_join(s_pthread_stop, NULL);
    }
    memset(&s_pthread_stop, 0x00, sizeof(s_pthread_stop));
	s_decode_thread_inited_stop = false;
    return true;
}
void* photoList::check_thread_start(void *param)
{
	_mutex_write_lock();
	PHOTOList->checkThreadStatus =true;
	_mutex_write_unlock();
	pthread_exit(NULL);
}

void *photoList::decode_thread_start(void *param)
{
	photoChild_info_t* curFileList =NULL;
	int DecodeType =0,StartIndex =0,DecodeNum =0;
	int Start =0,End=0,index=0,DecodeCurNum=0;
	int ret =0;
	
	if(media_file_list != NULL)
	{
		_mutex_write_lock();
		sleep(1);
		PHOTOList->free_childFileList();
		StartIndex =(PHOTOList->decodeCur * PHOTOList->width_num);
		for(index =StartIndex;index < PHOTOList->photoListTotal;index++) 
		{
			if(DecodeNum<PHOTODEC_MAX)
			{
				if(s_decode_stop_flag)
				{
					LV_LOG_USER("s_decode_stop_flag!!!");
					goto end;
				}
				else
				{
					_decode_write_lock();
				}
				
				curFileList = PHOTOList->get_cur_childFileList(index);
				if((s_decode_stop_flag)||(curFileList == NULL))
				{
					LV_LOG_USER("get_cur_childFileList fail!!!");
					goto end;
				}
				memset(curFileList->listIcon->filepatch, 0x00, sizeof(curFileList->listIcon->filepatch));
				ret = rat_npl_index2file(media_file_list->media_hrat, index, curFileList->listIcon->filepatch);
				if(ret == EPDK_OK) 
				{
					if(s_decode_stop_flag)
					{
						LV_LOG_USER("s_decode_stop_flag!!!");
						goto end;
					}
					if(!curFileList->listIcon->bmp_valid)
					{
						PHOTOList->add_saveImage(curFileList);
						PHOTOList->deStatus =true;
					}
				}
				_decode_write_unlock();
			}
			else
			{
				_decode_write_unlock();
				goto Connect;
			}
			DecodeNum ++;
		}
		
Connect:
		DecodeNum =0;
		DecodeCurNum =(PHOTOList->decodeCur * PHOTOList->width_num + PHOTODEC_MAX);
		if(DecodeCurNum<PHOTOList->photoListTotal)
			StartIndex = DecodeCurNum;
		else
			StartIndex = PHOTOList->photoListTotal;
		
		for(index =StartIndex;index < PHOTOList->photoListTotal;index++) 
		{
			if(DecodeNum<PHOTODEC_MAX)
			{
				if(s_decode_stop_flag)
				{
					LV_LOG_USER("s_decode_stop_flag!!!");
					goto end;
				}
				else
				{
					_decode_write_lock();
				}
				
				curFileList = PHOTOList->get_cur_childFileList(index);
				if((s_decode_stop_flag)||(curFileList == NULL))
				{
					LV_LOG_USER("get_cur_childFileList fail!!!");
					goto end;
				}
				memset(curFileList->listIcon->filepatch, 0x00, sizeof(curFileList->listIcon->filepatch));
				ret = rat_npl_index2file(media_file_list->media_hrat, index, curFileList->listIcon->filepatch);
				if(ret == EPDK_OK) 
				{
					if(s_decode_stop_flag)
					{
						LV_LOG_USER("s_decode_stop_flag!!!");
						goto end;
					}
					if(!curFileList->listIcon->bmp_valid)
					{
						PHOTOList->add_saveImage(curFileList);
						PHOTOList->deStatus =true;
					}
				}
				_decode_write_unlock();
			}
			else
			{
				_decode_write_unlock();
				goto next;
			}
			DecodeNum ++;
		}
next:
		DecodeNum =0;
		StartIndex = (PHOTOList->decodeCur * PHOTOList->width_num -1);
		if(StartIndex<0)
		{
			DecodeCurNum =(PHOTOList->decodeCur * PHOTOList->width_num + 2*PHOTODEC_MAX);
			if(DecodeCurNum<PHOTOList->photoListTotal)
				StartIndex = DecodeCurNum;
			else
				StartIndex = PHOTOList->photoListTotal;
			
			for(index =StartIndex;index < PHOTOList->photoListTotal;index++) 
			{
				if(DecodeNum<PHOTODEC_MAX)
				{
					if(s_decode_stop_flag)
					{
						LV_LOG_USER("s_decode_stop_flag!!!");
						goto end;
					}
					else
					{
						_decode_write_lock();
					}
					
					curFileList = PHOTOList->get_cur_childFileList(index);
					if((s_decode_stop_flag)||(curFileList == NULL))
					{
						LV_LOG_USER("get_cur_childFileList fail!!!");
						goto end;
					}
					memset(curFileList->listIcon->filepatch, 0x00, sizeof(curFileList->listIcon->filepatch));
					ret = rat_npl_index2file(media_file_list->media_hrat, index, curFileList->listIcon->filepatch);
					if(ret == EPDK_OK) 
					{
						if(s_decode_stop_flag)
						{
							LV_LOG_USER("s_decode_stop_flag!!!");
							goto end;
						}
						if(!curFileList->listIcon->bmp_valid)
						{
							PHOTOList->add_saveImage(curFileList);
							PHOTOList->deStatus =true;
						}
					}
					_decode_write_unlock();
				}
				else
				{
					goto end;
				}
				DecodeNum ++;
			}
		}
		else
		{
			for(index =StartIndex;index >=0;index--) 
			{
				if(DecodeNum<PHOTODEC_MAX)
				{
					if(s_decode_stop_flag)
					{
						LV_LOG_USER("s_decode_stop_flag!!!");
						goto end;
					}
					else
					{
						_decode_write_lock();
					}
					
					curFileList = PHOTOList->get_cur_childFileList(index);
					if((s_decode_stop_flag)||(curFileList == NULL))
					{
						LV_LOG_USER("get_cur_childFileList fail!!!");
						goto end;
					}
					memset(curFileList->listIcon->filepatch, 0x00, sizeof(curFileList->listIcon->filepatch));
					ret = rat_npl_index2file(media_file_list->media_hrat, index, curFileList->listIcon->filepatch);
					if(ret == EPDK_OK) 
					{
						if(!curFileList->listIcon->bmp_valid)
						{
							PHOTOList->add_saveImage(curFileList);
							PHOTOList->deStatus =true;
						}
					}
					_decode_write_unlock();
				}
				else
				{
					goto end;
				}
				DecodeNum ++;
			}
		}
	}
end:
	_mutex_write_unlock();
	_decode_write_unlock();
	LV_LOG_USER("decode_thread_start end!!!");
	pthread_exit(NULL);
	return (void *)NULL;
}

static int photolist_url_htoi(char *s)
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

int _photolist_url_decode(char *str, int len)
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
            *dest = (char) photolist_url_htoi(data + 1);
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

int photolist_get_userNum(void)
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

static int photolist_userInfo(int userNum,char *userID)
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

char *photoList::_get_cur_filelist_patch(int index)
{
    photoChild_info_t *tmp_list;
	int ret =0;

	tmp_list = photoListHead;

	while(tmp_list != NULL)
	{
		if(index == tmp_list->listIcon->myindex)
		{
			if(strlen(tmp_list->listIcon->filepatch)>0)
			{
				return tmp_list->listIcon->filepatch;
			}
			else
			{
				if(media_file_list != NULL)
				{
					ret = rat_npl_index2file(media_file_list->media_hrat, index, tmp_list->listIcon->filepatch);
					if(ret == EPDK_OK)
					{
						return tmp_list->listIcon->filepatch;
					}
					else
						return NULL;
				}
				else
					return NULL;
			}
		}
		tmp_list = tmp_list->next_list;
	}
	return NULL;
}


void photoList::childFileList_add_node(photoChild_info_t *node)
{
	photoChild_info_t *tmp_list;

	tmp_list = photoListHead;

	if(photoListHead == NULL)
	{
		photoListHead = node;
		photoListHead->next_list = NULL;
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
void photoList::add_childFileList(int index)
{
	photoChild_info_t* tmp_list;
	int list_x =0,list_y =0,list_w =210,list_h =150;
    int icon_x =170,icon_y =8,icon_w =32,icon_h =32;
	
	tmp_list = (photoChild_info_t*)malloc(sizeof(photoChild_info_t));
	memset(tmp_list,0,sizeof(photoChild_info_t));
	
	tmp_list->listIcon = new photolistIcon(list_photoList->myobj);
	tmp_list->listIcon->btn->set_size(list_w,list_h);
    tmp_list->listIcon->btn->align(LV_ALIGN_TOP_LEFT,list_x,list_y);
	tmp_list->listIcon->icon->set_size(icon_w,icon_h);
    tmp_list->listIcon->icon->align(LV_ALIGN_TOP_LEFT,icon_x,icon_y);
    tmp_list->listIcon->btn->add_event_cb(photoList_event_handler,LV_EVENT_CLICKED ,this);
    tmp_list->listIcon->btn->set_userdata((void*)index);
    tmp_list->listIcon->myindex=index;
	tmp_list->listIcon->type=0;
	tmp_list->listIcon->bmp_valid=false;
    tmp_list->listIcon->check_ok=false;
	memset(tmp_list->listIcon->filepatch,0,sizeof(tmp_list->listIcon->filepatch));
	tmp_list->listIcon->update_sceneList((char*)PHOTO_PNG);
	childFileList_add_node(tmp_list);
}

photoChild_info_t* photoList::get_cur_childFileList(int index)
{
	photoChild_info_t* tmp_list;
	tmp_list = photoListHead;

	while(tmp_list != NULL)
	{
		if(index == tmp_list->listIcon->myindex)
		{
			return tmp_list;
		}
		tmp_list = tmp_list->next_list;
	}
	return NULL;
}
void photoList::free_childFileList(void)
{
	photoChild_info_t* tmp_list;
	int startNum=0;
	tmp_list = photoListHead;
	startNum = decodeCur*width_num;
	while(tmp_list != NULL)
	{
		if((tmp_list->listIcon->myindex <(startNum-20))||(tmp_list->listIcon->myindex >=(startNum+40)))
		{
			if(tmp_list->listIcon->bmp_valid)
			{
				tmp_list->listIcon->bmp_valid =false;
				tmp_list->listIcon->update_sceneList((char*)PHOTO_PNG);
				free_cur_saveImage(tmp_list->listIcon->myindex);
			}
		}
		tmp_list = tmp_list->next_list;
	}
}
void photoList::change_childFileList_status(int index)
{
	photoChild_info_t* tmp_list;
	
	tmp_list = photoListHead;
	while(tmp_list != NULL)
	{
		if(tmp_list->listIcon->myindex ==index)
		{
			if(tmp_list->listIcon->check_ok !=true)
	        {
	            tmp_list->listIcon->check_ok =true;
	            _add_selfilelist(index);
	        }
	        else
	        {
	            tmp_list->listIcon->check_ok =false;
	            _del_selfilelist_curpatch(index);
	        }
		}
		tmp_list = tmp_list->next_list;
	}
}
void photoList::freeall_childFileList(void)
{
	photoChild_info_t* tmp_list;
	
	tmp_list = photoListHead;
	while(tmp_list != NULL)
	{
		if(tmp_list->listIcon!= NULL)
		{
			tmp_list->listIcon->bmp_valid =false;
			tmp_list->listIcon->update_sceneList((char*)PHOTO_PNG);
		}
		tmp_list = tmp_list->next_list;
	}
}
void photoList::destory_childFileList(void)
{
	photoChild_info_t * tmp_list_prev;
	photoChild_info_t * tmp_list_last;

	tmp_list_prev = photoListHead;
	_mutex_write_lock();
	while(tmp_list_prev != NULL)
	{
		tmp_list_last = tmp_list_prev->next_list;
		if(tmp_list_prev->listIcon !=NULL)
		{
			tmp_list_prev->listIcon->bmp_valid =false;
			tmp_list_prev->listIcon->update_sceneList((char*)PHOTO_PNG);
			delete tmp_list_prev->listIcon;
			tmp_list_prev->listIcon =NULL;
		}
		free(tmp_list_prev);
		tmp_list_prev = tmp_list_last;
	}
	_mutex_write_unlock();
	photoListHead = NULL;
}
void photoList::saveImage_add_node(saveImage_t *node)
{
	saveImage_t *tmp_list;

	tmp_list = saveImageHead;

	if(saveImageHead == NULL)
	{
		saveImageHead = node;
		saveImageHead->next_list = NULL;
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
void photoList::add_saveImage(photoChild_info_t* curFileList)
{
	saveImage_t *tmp_list;
	
	if((s_decode_stop_flag !=true)&&(curFileList !=NULL)&&(curFileList->listIcon !=NULL))
	{
		tmp_list = (saveImage_t*)malloc(sizeof(saveImage_t));
		memset(tmp_list,0,sizeof(saveImage_t));
		tmp_list->listImage = sunxi_image_decode_scaler(curFileList->listIcon->filepatch, 210, 150);
		curFileList->listIcon->update_sceneList(tmp_list->listImage);
		tmp_list->index =curFileList->listIcon->myindex;
		curFileList->listIcon->bmp_valid =true;
		saveImage_add_node(tmp_list);
	}
}

static saveImage_t *del_saveImage_head(saveImage_t *head_list)
{
	saveImage_t *tmp_list;
	
	if(head_list ==NULL)
	{
		return NULL;
	}
	tmp_list = head_list->next_list;
	if(head_list->listImage !=NULL)
	{
		sunxi_image_free(head_list->listImage);	
		head_list->listImage =NULL;
	}
	free(head_list);
	if(tmp_list ==NULL)
	{
		return NULL;
	}
	head_list = tmp_list;
	return head_list;
}
void photoList::free_cur_saveImage(int index)
{
	saveImage_t* tmp_list_prev;
	saveImage_t* tmp_list_last;

	if(saveImageHead ==NULL)
        return;

	if(saveImageHead->index == index)
	{
		saveImageHead =del_saveImage_head(saveImageHead);
		return;
	}
	else
    {
        tmp_list_prev = saveImageHead;
		tmp_list_last = saveImageHead->next_list;
		while(tmp_list_last != NULL)
		{
			if(tmp_list_last->index==index)
			{
				tmp_list_prev->next_list = tmp_list_last->next_list;
				if(tmp_list_last->listImage !=NULL)
				{
					sunxi_image_free(tmp_list_last->listImage);	
					tmp_list_last->listImage =NULL;
				}
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
int photoList::get_saveImage_total(void)
{
	saveImage_t * tmp_list;
	int num =0;

	tmp_list = saveImageHead;
	while(tmp_list != NULL)
	{
		tmp_list = tmp_list->next_list;
		num++;
	}
	return num;
}
void photoList::destory_saveImage(void)
{
	saveImage_t * tmp_list_prev;
	saveImage_t * tmp_list_last;

	tmp_list_prev = saveImageHead;
	while(tmp_list_prev != NULL)
	{
		tmp_list_last = tmp_list_prev->next_list;
		if(tmp_list_prev->listImage !=NULL)
		{
			sunxi_image_free(tmp_list_prev->listImage);	
			tmp_list_prev->listImage =NULL;
		}
		free(tmp_list_prev);
		tmp_list_prev = tmp_list_last;
	}
	saveImageHead = NULL;
}
/*选择文件链表*/
void photoList::selfilelist_add_node(file_info_t *node)
{
    file_info_t *tmp_list;

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
int photoList::_get_selfilelist_total(void)
{
    file_info_t* tmp_list;
    int numTotal =0;

    tmp_list = SelFileList;

    while(tmp_list != NULL)
    {
        numTotal ++;
        tmp_list = tmp_list->next_list;
    }
    return numTotal;
}
void photoList::_del_selfilelist(void)
{
    file_info_t* tmp_list;
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
			system("sync");
		}
        tmp_list = tmp_list->next_list;
    }
    _destory_selfilelist();
}
void photoList::_cpy_selfilelist(void)
{
    file_info_t* tmp_list;
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
			LV_LOG_USER("file_size:%ld",file_size);
			sprintf(buff,"cp %s %s/",filePath,patch);
        	system(buff);
			system("sync");
		}
        tmp_list = tmp_list->next_list;
    }
    _destory_selfilelist();
}
static file_info_t *_del_selfilelist_curpatch_head(file_info_t *head_list)
{
	file_info_t *tmp_list;
	
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
void photoList::_del_selfilelist_curpatch(int index)
{
    file_info_t *tmp_list_prev;
    file_info_t *tmp_list_last;

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

void photoList::_add_selfilelist(int index)
{
    file_info_t* tmp_list;

    tmp_list = (file_info_t*)malloc(sizeof(file_info_t));
    memset(tmp_list,0,sizeof(file_info_t));
    tmp_list->myindex =index;
    selfilelist_add_node(tmp_list);
}
void photoList::_destory_selfilelist(void)
{
    file_info_t * tmp_list_prev;
    file_info_t * tmp_list_last;

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

void photoList::_add_allfilelist(void)
{
	photoChild_info_t* tmp_list;
	
	tmp_list = photoListHead;
	while(tmp_list != NULL)
	{
		if(tmp_list->listIcon!= NULL)
		{
			_add_selfilelist(tmp_list->listIcon->myindex);
		}
		tmp_list = tmp_list->next_list;
	}
	checkedNum = _get_selfilelist_total();
}
void photoList::photoList_stop_decode(void)
{
	s_decode_stop_flag = true;
}
void photoList::photoList_exit_decode(void)
{
	_mutex_write_lock();
	photo_thread_decode_thumb_delete();
	_mutex_write_unlock();
}
void photoList::photoList_start_decode(void)
{
	_decode_write_unlock();
	s_decode_stop_flag = false;
	if(PHOTOList->photoListTotal<=0)
		return;
    photo_thread_decode_thumb_create(decode_thread_start);
}
photoList::photoList(int disType,lv_obj_t* parent,char *path)
{
	if(myfont==nullptr)
	{
		myfont = new LvcppFreeTypeFont(26,0);
	}
	ui_image_decode();
	_decode_lock_init();
	_mutex_lock_init();
    frame = new LvcppScreen(parent);
    frame->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    frame->set_main_bg_color(lv_color_black(),LV_OPA_0);
    frame->set_main_bg_img_src(LISTBG_PNG);
    mainscreen = frame->myobj;
    IconStation =false;
    IconCheck =false;
	PHOTOList =this;
    flash_inde =disType;
	SSTAR_RegisterApplib(APP_NAME_UI,funcallback);
	if((path !=NULL)&&(strlen(path)>0))
	{
		enterPathStatus =true;
		memset(photo_listpatch,0,1024);
		strcpy(photo_listpatch,path);
	}
}

photoList::~photoList(void)
{
	photoList_stop_decode();
	photoList_exit_decode();
	photoList_list_delete();
	photo_media_delete();
    photo_list_head_dele();
    photomian_list_dele();
    delete_ui_free();
    _destory_selfilelist();
	photolist_del_mute_dele();
	photolist_cpy_mute_dele();
    if(frame !=NULL)
    {
        delete frame;
        frame =NULL;
    }
	_decode_lock_deinit();
	_mutex_lock_deinit();
	SSTAR_UnRegisterApplib(APP_NAME_UI,funcallback);
	ui_image_free();
	if(myfont!=nullptr)
	{
		delete myfont;
		myfont = nullptr;
	}
}

void photoList::funcallback(msg_apps_t *msg)
{
    LV_LOG_USER("type:%d ->mode:%d",msg->type,msg->mode);
    switch(msg->type)
    {
		case UI_DISK:
			if(msg->mode ==DISK_SD_ENTER)
			{
				PHOTOList->SDEnter =true;
			}
			else if(msg->mode ==DISK_SD_OUT)
			{
				PHOTOList->SDEnter =false;
			}
			else if(msg->mode ==DISK_U_ENTER)
			{
				PHOTOList->UEnter =true;
			}
			else if(msg->mode ==DISK_U_OUT)
			{
				PHOTOList->UEnter =false;
			}
        break;
		case UI_PHOTOLIST:
			if(msg->mode ==MODE_UPDATA)
			{

	    	}
			else if(msg->mode ==MODE_NEXTSCENE)
			{
			}
			break;
        default:
        break;
    }
}
int photoList::init_parament(void)
{
    frame->show(true);
	photo_media_creat();
    flash_total = (int)(photolist_get_userNum()+PHOTOLIST_MAX);
    photomian_list_creat();
    photo_list_head_creat();
    photoList_list_creat();
	if(enterPathStatus ==true)
	{
		enterPathStatus =false;
		if(media_file_list !=NULL)
		{
			photoIndex = media_get_index_from_path(media_file_list,photo_listpatch);
			if(photoIndex >16)
			{
				decodeCur =(int)(photoIndex/PHOTOLIST_MAX);
				FileStart =decodeCur;
				decodeStart =FileStart -4;
				decodeEnd = FileStart+11;
			}
			list_photoList->set_scroll_to(0,FileStart*YOffect, LV_ANIM_OFF);
		}
	}
    photoList_start_decode();
	if(photoListTimer !=NULL)
	{
		resume(photoListTimer);
	}
	else
	{
		photoListTimer = startTimer(10, this);
	}
    return 0;
}

void photoList::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    static int timecnt = 0;
    timecnt++;
	
	if(checkThreadStatus)
	{
		checkThreadStatus =false;
		photo_media_creat();
		photoList_list_creat();
		photoList_start_decode();
	}
}

LvcppButton* photoList::LvcppButtonHead(lv_obj_t* paren,bool show_cb,lv_ui_inof_t *uiInfo)
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
    child_button->set_userdata(NULL);
    if(show_cb ==true)
    {
        child_button->set_userdata((void*)uiInfo->userdata);
        child_button->add_event_cb(head_event_handler,LV_EVENT_PRESSED,this);
        child_button->add_event_cb(head_event_handler,LV_EVENT_RELEASED,this);
    }
    return child_button;
}

LvcppLabel* photoList::LvcppLabelViewChild(lv_obj_t* paren,lv_text_align_t align,lv_str_inof_t *strInfo)
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

int photoList::photo_media_creat(void)
{
#ifdef _UCHIP_T113
	char MountPoint[128]={0};
	char userPatch[64]={0};

	if(media_file_list !=NULL)
	{
		media_unload_file(media_file_list);
		media_file_list = NULL;
	}
	
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
		else if(flash_inde ==4)
		{
			strcpy(MountPoint,"/mnt/UDISK/favor");
		}
		else
		{
			if(photolist_userInfo((flash_inde -PHOTOLIST_MAX),userPatch)<0)
				return 0;
			else
				sprintf(MountPoint,"/mnt/UDISK/%s",userPatch);	
		}
		media_file_list = media_load_file(RAT_MEDIA_TYPE_PIC, MountPoint);
		if (NULL == media_file_list)
		{
			LV_LOG_USER("%s don't find photo list\n",MountPoint);
			photoListTotal = 0;
		}
		else
		{
			photoListTotal = media_file_list->total_num;
		}
		if(photoListTotal <=0)
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
#endif
	return 0;
}

void photoList::photo_media_delete(void)
{
#ifdef _UCHIP_T113
	if(media_file_list!=NULL)
	{
		media_unload_file(media_file_list);
		media_file_list = NULL;
	}
#endif
}

void photoList::delete_ui_free(void)
{
    if(buttonReturn != NULL)
    {
        delete buttonReturn;
        buttonReturn =NULL;
    }
    if(photoIcon != NULL)
    {
        delete photoIcon;
        photoIcon =NULL;
    }
}

void photoList::photolist_del_mute_creat(void)
{
    delButton = new LvcppButton(mainscreen);
    delButton->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    delButton->set_main_bg_color(lv_color_black(),LV_OPA_60);
    delButton->add_event_cb(photolist_del_event_handler,LV_EVENT_CLICKED,this);

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
    delChildButtonCancel->add_event_cb(photolist_del_event_handler,LV_EVENT_PRESSED,this);
    delChildButtonCancel->add_event_cb(photolist_del_event_handler,LV_EVENT_RELEASED,this);
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
    delChildButtonOk->add_event_cb(photolist_del_event_handler,LV_EVENT_PRESSED,this);
    delChildButtonOk->add_event_cb(photolist_del_event_handler,LV_EVENT_RELEASED,this);
    delChildButtonOk->txt_size(SCREEN_HOR_SIZE/4-20, SCREEN_VER_SIZE/12-10, LV_LABEL_LONG_WRAP);
    delChildButtonOk->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    delChildButtonOk->txt_center();
    delChildButtonOk->txt_color(lv_color_white());
    delChildButtonOk->add_txt(STR_OK);
}

void photoList::photolist_del_mute_dele(void)
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
void photoList::photolist_del_event_handler(lv_event_t *event)
{
    photoList* opt = (photoList*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target==opt->delButton->myobj)
    {
        opt->photolist_del_mute_dele();
        opt->draw_headlist();
    }
    else if(target==opt->delChildButtonCancel->myobj)
    {
        if(event->code == LV_EVENT_RELEASED)
        {
            opt->photolist_del_mute_dele();
            opt->draw_headlist();
        }
    }
    else if(target==opt->delChildButtonOk->myobj)
    {
        if(event->code == LV_EVENT_RELEASED)
        {
            opt->photolist_del_mute_dele();
			opt->IconCheck =false;
			opt->IconStation =false;
            opt->IconDel->show(false);
			opt->IconChe->show(false);
			opt->IconCpy->show(false);
			opt->IconSor->show(false);
            opt->StrIconNum->show(false);
            opt->_del_selfilelist();
			opt->list_photoList->show(false);
            opt->draw_headlist();
			opt->photoList_stop_decode();
			opt->photoList_exit_decode();
			opt->photoList_list_delete();
			stop_decode_thread_delete();
			stop_decode_thread(opt->check_thread_start);
			stop_decode_thread_delete();
        }
    }
}

void photoList::photolist_cpy_mute_creat(void)
{
    cpyButton = new LvcppButton(mainscreen);
    cpyButton->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    cpyButton->set_main_bg_color(lv_color_black(),LV_OPA_60);
    cpyButton->add_event_cb(photolist_cpy_event_handler,LV_EVENT_CLICKED,this);

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
            cpyCheckBox1->add_event_cb(photolist_cpy_event_handler,LV_EVENT_CLICKED,this);

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
            cpyCheckBox2->add_event_cb(photolist_cpy_event_handler,LV_EVENT_CLICKED,this);

            cpyChildLabel2 = new LvcppLabel(cpyCheckBox2->myobj);
            cpyChildLabel2->set_size(32,32);
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
    cpyChildButtonCancel->add_event_cb(photolist_cpy_event_handler,LV_EVENT_PRESSED,this);
    cpyChildButtonCancel->add_event_cb(photolist_cpy_event_handler,LV_EVENT_RELEASED,this);
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
    cpyChildButtonOk->add_event_cb(photolist_cpy_event_handler,LV_EVENT_PRESSED,this);
    cpyChildButtonOk->add_event_cb(photolist_cpy_event_handler,LV_EVENT_RELEASED,this);
    cpyChildButtonOk->txt_size(SCREEN_HOR_SIZE/4-20, SCREEN_VER_SIZE/12-10, LV_LABEL_LONG_WRAP);
    cpyChildButtonOk->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    cpyChildButtonOk->txt_center();
    cpyChildButtonOk->txt_color(lv_color_white());
    cpyChildButtonOk->add_txt(STR_OK);
}

void photoList::photolist_cpy_mute_dele(void)
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
void photoList::photolist_cpy_event_handler(lv_event_t *event)
{
    photoList* opt = (photoList*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if(target==opt->cpyButton->myobj)
    {
        opt->photolist_cpy_mute_dele();
        opt->draw_headlist();
    }
    else if(target==opt->cpyChildButtonCancel->myobj)
    {
        if(event->code == LV_EVENT_RELEASED)
        {
            opt->photolist_cpy_mute_dele();
            opt->draw_headlist();
        }
    }
    else if(target==opt->cpyChildButtonOk->myobj)
    {
        if(event->code == LV_EVENT_RELEASED)
        {
            opt->photolist_cpy_mute_dele();
			opt->IconCheck =false;
			opt->IconStation =false;
            opt->IconDel->show(false);
			opt->IconChe->show(false);
			opt->IconCpy->show(false);
			opt->IconSor->show(false);
            opt->StrIconNum->show(false);
			opt->draw_headlist();
			opt->_cpy_selfilelist();
            opt->draw_photoList_list();
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

void photoList::photo_list_head_creat(void)
{
    lv_ui_inof_t uiInfo;
    lv_str_inof_t strInfo;
    char buff[12]={0};

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
	if(photoListTotal <=0)
	{
		IconBack->show(false);
	}
	else
	{
		IconBack->show(true);
	}

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

void photoList::draw_headlist(void)
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

void photoList::photo_list_head_dele(void)
{
	if(IconBack != NULL)
    {
        delete IconBack;
        IconBack =NULL;
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
    
    if(StrIconNum != NULL)
    {
        delete StrIconNum;
        StrIconNum =NULL;
    }
}
void photoList::check_disk_status(void)
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
void photoList::head_event_handler(lv_event_t *event)
{
    photoList* opt = (photoList*) event->user_data;
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
            	opt->pause(opt->photoListTimer);
                MainAPPStart::photomain_destory();
                return;
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
					opt->photolist_cpy_mute_creat();
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
					opt->photolist_del_mute_creat();
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
					opt->draw_photoList_list();
                }
                else
                {
                    opt->IconChe->set_main_bg_img_src(opt->LIST_ICON_NOR_PNG);
					opt->_destory_selfilelist();
					opt->draw_photoListIcon_list();
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
                opt->IconBack->show(true);
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
                }
                else
                {
                    opt->IconBack->set_main_bg_img_src(opt->LIST_ICON_ICON_PNG);
                    opt->IconDel->show(false);
                    opt->IconChe->show(false);
					opt->IconCpy->show(false);
					opt->IconSor->show(false);
                    opt->StrIconNum->show(false);
                }
                opt->IconBack->show(true);
                opt->draw_headlist();
                opt->draw_photoListIcon_list();
            }
        break;
        default:
            break;
    }
}

int photoList::photomian_list_creat(void)
{
	lv_ui_inof_t uiInfo;
	
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
    uiInfo.ui_patch =(char *)HEAD_ICON_PHOTO_PNG;
    photoIcon =LvcppButtonHead(mainscreen,false,&uiInfo);

    list_main = new LvcppList(mainscreen);
    list_main->set_size(378,718);
    list_main->align(LV_ALIGN_TOP_LEFT,0,82);
    list_main->set_main_bg_color(lv_color_hex(0x0099bb),LV_OPA_COVER);
    list_main->set_main_bg_opa(LV_OPA_100);
    list_main->set_flex_flow(LV_FLEX_FLOW_COLUMN);
    list_main->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    list_main->set_main_pad_all(0);
    list_main->set_main_pad_row(2);
    list_main->set_main_pad_column(0);
    list_main->set_main_border_width(0);
    list_main->set_main_radius(0);

    photomian_list_add();
    list_main->set_select_state(flash_inde,lv_color_hex(0x00a7d4));
	list_main->set_scroll_to(0,flash_inde*85, LV_ANIM_OFF);
    return 0;
}

int photoList::photomian_list_add(void)
{
    framelist_btn_t btn_info;
    framelist_txt_t txt_info;
    framelist_icon_t icon_info;
    char buff[64]={0};
    char LogoBuff[128]={0};

    btn_info.x =0;
    btn_info.y =0;
    btn_info.w =378;
    btn_info.h =85;
    btn_info.bg_color =0x0099bb;
    btn_info.line_h =1;
    btn_info.line_color =WHITE_COLOR;
    btn_info.align =LV_ALIGN_TOP_LEFT;

    txt_info.x =86;
    txt_info.y =29;
    txt_info.w =280;
    txt_info.h =32;
    txt_info.font_size =26;
    txt_info.txt_color =WHITE_COLOR;
    txt_info.align =LV_ALIGN_TOP_LEFT;
	txt_info.font = myfont->font();

    icon_info.x =28;
    icon_info.y =20;
    icon_info.w =42;
    icon_info.h =44;
    icon_info.showStatus =true;
    icon_info.align =LV_ALIGN_TOP_LEFT;
#ifdef IMAGE_DECODE
    void *iconPatch[6]={LIST_ICON_ALL_PNG,LIST_ICON_FLASH_PNG,LIST_ICON_SD_PNG,LIST_ICON_U_PNG,
                               LIST_ICON_LOVE_PNG,LIST_ICON_USER_PNG};
#endif
    for(int i=0;i < flash_total;i++)
    {
        if(i<PHOTOLIST_MAX)
        {
            icon_info.iconPatch =(char *)iconPatch[i];
        }
        else
        {
            memset(buff,0,64);
            if(photolist_userInfo((i-PHOTOLIST_MAX),buff)<0)
                icon_info.iconPatch =(char *)iconPatch[PHOTOLIST_MAX];
            else
            {
                sprintf(LogoBuff,"/mnt/UDISK/%s.png",buff);
                if(0 != access(LogoBuff, 0))
                {
                    icon_info.iconPatch =(char *)iconPatch[PHOTOLIST_MAX];
                }
                else
                {
#ifdef _UCHIP_T113
					/*
                    if(LIST_ICON_USERON_PNG!=NULL)
                    {
                        sunxi_image_free(LIST_ICON_USERON_PNG);
                        LIST_ICON_USERON_PNG =NULL;
                    }
                    LIST_ICON_USERON_PNG=(void*)sunxi_image_decode_scaler(LogoBuff,icon_info.w,icon_info.h);
                    icon_info.iconPatch =(void *)LIST_ICON_USERON_PNG;
                    */
#endif
                }
            }
        }
        photomian_list_head_creat(i,&btn_info,&txt_info,&icon_info);
    }
    return 0;
}

void photoList::photomian_list_head_creat(int data,framelist_btn_t *btn,framelist_txt_t *txt,framelist_icon_t *icon)
{
    char buff[64]={0};
    char userBuff[64]={0};

    photoListMainInfo_t *tmp_list =new photoListMainInfo_t;
    tmp_list->count =data;
    tmp_list->list_item = new frameListIcon(list_main->myobj,btn,txt,icon);
    tmp_list->list_item->btn->add_event_cb(main_event_handler,LV_EVENT_RELEASED,this);
    tmp_list->list_item->btn->set_userdata((void*)data);
    if(data<PHOTOLIST_MAX)
    {
        tmp_list->list_item->btn->add_txt((char *)iconName[data]);
    }
    else
    {
        memset(buff,0,64);
        memset(userBuff,0,64);
        if(photolist_userInfo((data-PHOTOLIST_MAX),userBuff)<0)
            sprintf(buff,"%s%d","User",(data-PHOTOLIST_MAX));
        else
        {
#ifdef _UCHIP_T113
            memset(buff,0,64);
            if(read_string_userinfo_param(userBuff,SENDERREMARKNAME,buff,sizeof(buff))<0)
            {
                memset(buff,0,64);
                if(read_string_userinfo_param(userBuff,SENDERNICKNAME,buff,sizeof(buff))<0)
                {
                    memset(buff,0,64);
                    if(read_string_userinfo_param(userBuff,SENDNAME,buff,sizeof(buff))<0)
                    {
                        memset(buff,0,64);
                        sprintf(buff,"%s",userBuff);
                    }
                    else
                    {
                        _photolist_url_decode(buff,strlen(buff));
                    }
                }
                else
                {
                    _photolist_url_decode(buff,strlen(buff));
                }
            }
            else
            {
               _photolist_url_decode(buff,strlen(buff));
            }
#else
            sprintf(buff,"%s%d","User",(data-PHOTOLIST_MAX));
#endif
        }
        tmp_list->list_item->btn->add_txt(buff);
    }
    photomian_list_head_add(tmp_list);
}

void photoList::photomian_list_head_add(photoListMainInfo_t *mainlist)
{
    photoListMainInfo_t *tmp_list;

    tmp_list = mainListHead;

    if(mainListHead == NULL)
    {
        mainListHead = mainlist;
        mainListHead->next_list = NULL;
    }
    else
    {
        while(tmp_list->next_list != NULL)
        {
            tmp_list = tmp_list->next_list;
        }
        tmp_list->next_list = mainlist;
        tmp_list->next_list->next_list = NULL;
    }
}

void photoList::photomian_list_dele(void)
{
    photoListMainInfo_t *tmp_list_prev;
    photoListMainInfo_t *tmp_list_last;

    tmp_list_prev = mainListHead;
    while(tmp_list_prev != NULL)
    {
        tmp_list_last = tmp_list_prev->next_list;
        if(tmp_list_prev->list_item !=NULL)
        {
            delete tmp_list_prev->list_item;
            tmp_list_prev->list_item =NULL;
        }
        tmp_list_prev = tmp_list_last;
    }
    mainListHead = NULL;
    if(list_main !=NULL)
    {
        delete list_main;
        list_main =NULL;
    }
}

void photoList::main_event_handler(lv_event_t *event)
{
    photoList* opt = (photoList*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    lv_obj_t* cont = lv_event_get_current_target(event);
    int flash_inde = opt->flash_inde;
    bool IconStation =false;
    bool FlashStation =false;

    if(cont != target)
    {
        flash_inde = (uintptr_t)cont->user_data;
    }
    else
    {
       flash_inde =(uintptr_t)target->user_data;
    }
    if(opt->IconStation == true)
    {
        opt->IconStation =false;
        opt->draw_headlist();
        IconStation =true;
    }
    if(flash_inde !=opt->flash_inde)
    {
        opt->flash_inde = flash_inde;
        FlashStation =true;
    }
    opt->list_main->switch_select_state(opt->flash_inde,lv_color_hex(0x0099bb),lv_color_hex(0x00a7d4));
    if((IconStation ==true)||(FlashStation ==true))
    {
    	opt->IconCheck =false;
        opt->IconStation =false;
		if(opt->IconBack !=NULL)
			opt->IconBack->show(false);
		if(opt->IconDel !=NULL)
        	opt->IconDel->show(false);
		if(opt->IconChe !=NULL)
			opt->IconChe->show(false);
		if(opt->IconCpy !=NULL)
			opt->IconCpy->show(false);
		if(opt->IconSor !=NULL)
			opt->IconSor->show(false);
		if(opt->StrIconNum !=NULL)
        	opt->StrIconNum->show(false);
		if(opt->list_photoList !=NULL)
			opt->list_photoList->show(false);
		opt->photoList_stop_decode();
		opt->photoList_exit_decode();
		opt->photoList_list_delete();
		stop_decode_thread_delete();
		stop_decode_thread(opt->check_thread_start);
		stop_decode_thread_delete();
    }
	else
	{
		opt->draw_photoList_list();
	}
}

int photoList::photoList_list_creat(void)
{
	int i =0;
	
	FileStart = 0;
	decodeStart = 0;
	decodeEnd =15;
	decodeCur =0;
	
	if(photoListTotal <=0)
		return -1;
	
	YOffect = 160;
	photoIndex =0;

    list_photoList = new LvcppTableFlex(mainscreen);
    list_photoList->set_size(880,680);
    list_photoList->align(LV_ALIGN_TOP_LEFT,398,102);
    list_photoList->set_flex_flow(LV_FLEX_FLOW_ROW_WRAP);
    list_photoList->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    list_photoList->set_scrollbar_dir(LV_DIR_VER);
    list_photoList->set_main_bg_opa(LV_OPA_0);
    list_photoList->set_main_pad_all(0);
    list_photoList->set_main_pad_row(10);
    list_photoList->set_main_pad_column(10);
    list_photoList->set_main_border_width(0);
    list_photoList->set_main_radius(0);
	
	list_photoList->add_event_cb(photoList_scroll_event_handler,LV_EVENT_SCROLL_BEGIN ,this);
	list_photoList->add_event_cb(photoList_scroll_event_handler,LV_EVENT_SCROLL ,this);
	list_photoList->add_event_cb(photoList_scroll_event_handler,LV_EVENT_SCROLL_END ,this);
	list_photoList->set_userdata(NULL); 

    for(i=photoIndex;i < photoListTotal;i++)
    {
        add_childFileList(i);
    }
	
    return 0;
}

void photoList::draw_photoList_list(void)
{
	photoChild_info_t* tmp_list;
	int i=0,startNum =0;
	
	tmp_list = photoListHead;
	startNum = decodeCur*width_num;
	while(tmp_list != NULL)
	{
		if((startNum+i) == tmp_list->listIcon->myindex)
		{
			if(true == s_decode_stop_flag)
				return;
			if(IconStation == true)
	        {
	            if(tmp_list->listIcon->check_ok !=true)
	            {
	                tmp_list->listIcon->type=1;
	            }
	            else
	            {
	                tmp_list->listIcon->type=2;
	            }
	        }
	        else
	        {
	            tmp_list->listIcon->type=0;
	        }
			if(tmp_list->listIcon !=NULL)
				tmp_list->listIcon->update_sceneListIcon();
		}
		
		tmp_list = tmp_list->next_list;
		i++;
		if(i >= 20)
			goto end;
	}
end:
	if(list_photoList !=NULL)
		list_photoList->invalidate();
}

void photoList::draw_photoListIcon_list(void)
{
	photoChild_info_t* tmp_list;

	tmp_list = photoListHead;
	while(tmp_list != NULL)
	{
		if(true == s_decode_stop_flag)
			return;
		if(IconStation == true)
        {
            tmp_list->listIcon->type=1;
        }
        else
        {
            tmp_list->listIcon->type=0;
        }
		tmp_list->listIcon->check_ok =false;
		tmp_list->listIcon->update_sceneListIcon();
		tmp_list = tmp_list->next_list;
	}
}

void photoList::photoList_list_delete(void)
{
    destory_childFileList();
	destory_saveImage();
	if(IconBack !=NULL)
		IconBack->show(false);
    if(list_photoList !=NULL)
    {
        delete list_photoList;
        list_photoList =NULL;
    }
}

void photoList::photoList_scroll_event_handler(lv_event_t *event)
{
    photoList* opt = (photoList*) event->user_data;
	int curY=0,offect =0,curLine=0,sceneOffect=0;

	curY = opt->list_photoList->get_scroll_y();
	curLine =(int)curY/opt->YOffect;

	if(event->code ==LV_EVENT_SCROLL_BEGIN)
	{
		opt->ScrollStatus =true;
		opt->FileStart = curLine;
	}
	else if(event->code ==LV_EVENT_SCROLL)
	{
		opt->ScrollStatus =true;
	}
	else if(event->code ==LV_EVENT_SCROLL_END)
	{
		opt->decodeCur =curLine;
		opt->ScrollStatus =false;
		offect = curLine - opt->FileStart;
		if(offect <0)
		{
			opt->MoveStatu =-1;
			opt->decodeStart -= abs(offect);
			if(opt->decodeStart <0)
				opt->decodeStart=0;
			opt->decodeEnd =opt->decodeStart+15;
		}
		else if(offect >0)
		{
			opt->MoveStatu =1;
			opt->decodeStart += abs(offect);
			opt->decodeEnd =opt->decodeStart+15;
		}
		else
		{
			opt->MoveStatu =0;
		}
		opt->photoList_stop_decode();
		opt->photoList_exit_decode();
		opt->photoList_start_decode();
		opt->draw_photoList_list();
	}
}

void photoList::photoList_event_handler(lv_event_t *event)
{
    photoList* opt = (photoList*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    lv_obj_t* cont = lv_event_get_current_target(event);
	photoChild_info_t* curFileList=NULL;
	char *patch =NULL;
    int icon_x=0,icon_y=0;

    if(cont != target)
    {
        opt->photoIndex = (uintptr_t)cont->user_data;
    }
    else
    {
       opt->photoIndex =(uintptr_t)target->user_data;
    }
	
    if((opt->IconStation != true)&&(opt->ScrollStatus !=true))
    {
    	curFileList = opt->get_cur_childFileList(opt->photoIndex);
		if(curFileList !=NULL)
		{
			memset(opt->photo_listpatch,0,sizeof(opt->photo_listpatch));
	        sprintf(opt->photo_listpatch,"%s",curFileList->listIcon->filepatch);
			LV_LOG_USER("path = %s",opt->photo_listpatch);
			opt->pause(opt->photoListTimer);
			photoMain::enterPhotoPlay(opt->flash_inde,opt->photo_listpatch);
		}
    }
    else if((opt->IconStation)&&(opt->ScrollStatus !=true))
    {
    	opt->change_childFileList_status(opt->photoIndex);
        opt->checkedNum = opt->_get_selfilelist_total();
        if(opt->checkedNum >0)
        {
            opt->IconCheck =true;
        }
        else
        {
            opt->IconCheck =false;
        }
        if(opt->IconCheck ==true)
        {
            icon_x =1040;
            icon_y =3;
        }
        else
        {
            icon_x =1120;
            icon_y =3;
        }
        opt->IconChe->align_to(opt->mainscreen,LV_ALIGN_TOP_LEFT,icon_x,icon_y);
        opt->draw_photoList_list();
        opt->draw_headlist();
    }
}

