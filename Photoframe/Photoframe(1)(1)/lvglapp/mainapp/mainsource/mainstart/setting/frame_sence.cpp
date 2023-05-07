#include "frame_sence.h"
#include  "mainstart/include/ui_config.h"
#include  "mainstart/include/str_config.h"
#ifdef _UCHIP_T113
#include  "common/common.h"
#endif

#ifdef IMAGE_DECODE
#else
static const void *devPatch[2]={SETTING_DOWN_DEVICE_PNG,SETTING_UP_DEVICE_PNG};
#endif

void frameSence::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    SETTING_DISP_DEVICE_PNG=(void*)parse_image_from_file(SETTING_DISP_DEVICE_PNG_PATH);
    SETTING_DOWN_DEVICE_PNG=(void*)parse_image_from_file(SETTING_DOWN_DEVICE_PNG_PATH);
    SETTING_UP_DEVICE_PNG=(void*)parse_image_from_file(SETTING_UP_DEVICE_PNG_PATH);
    SETTING_FRAME_USERMAKE_PNG=(void*)parse_image_from_file(SETTING_FRAME_USERMAKE_PNG_PATH);
    SETTING_FRAME_ADD_PNG=(void*)parse_image_from_file(SETTING_FRAME_ADD_PNG_PATH);
#endif
}


void frameSence::ui_image_free(void)
{
#ifdef IMAGE_DECODE
    free_image(SETTING_DISP_DEVICE_PNG);
    free_image(SETTING_DOWN_DEVICE_PNG);
    free_image(SETTING_UP_DEVICE_PNG);
    free_image(SETTING_FRAME_USERMAKE_PNG);
    free_image(SETTING_FRAME_ADD_PNG);
#endif
}

frameSence::frameSence(lv_obj_t* parent)
{
	ui_image_decode();
#ifdef IMAGE_DECODE
    void *devPatch[2]={SETTING_DOWN_DEVICE_PNG,SETTING_UP_DEVICE_PNG};
#endif
#ifdef _UCHIP_T113
    read_string_type_param(WEATHER_SCENE, DEVNICKNAME, deviceNickname,sizeof(deviceNickname));
#endif

    frameNameList = new LvcppLabel(parent);
    frameNameList->set_size(860,60);
    frameNameList->set_main_bg_opa(LV_OPA_0);
    frameNameList->set_main_pad_L_R(20,0);
    frameNameList->set_main_pad_T_B(10,0);
    frameNameList->txt_color(lv_color_white(),LV_PART_MAIN);
    frameNameList->txt_font_size(30, FT_FONT_STYLE_NORMAL);
    frameNameList->txt_align(LV_TEXT_ALIGN_LEFT);
    frameNameList->txt_long_mode(LV_LABEL_LONG_DOT);
    frameNameList->set_txt(STR_MYFRAME);

    frameDeviceInfo = new LvcppLabel(parent);
    frameDeviceInfo->set_size(870,80);
    frameDeviceInfo->set_main_bg_color(lv_color_hex(0x00516a),LV_OPA_0);
    frameDeviceInfo->set_txt("");
    frameDeviceInfo->add_flag(LV_OBJ_FLAG_CLICKABLE);
    frameDeviceInfo->add_event_cb(frame_list_event_handler,LV_EVENT_CLICKED,this);

    frameDevice = new LvcppLabel(frameDeviceInfo->myobj);
    frameDevice->set_size(44,44);
    frameDevice->set_main_bg_img_src(SETTING_DISP_DEVICE_PNG);
    frameDevice->align(LV_ALIGN_TOP_LEFT,20,18);
    frameDevice->set_main_bg_opa(LV_OPA_0);
    frameDevice->set_txt("");

    frameInfo = new LvcppLabel(frameDeviceInfo->myobj);
    frameInfo->set_size(550,36);
    frameInfo->set_main_bg_opa(LV_OPA_0);
    frameInfo->align(LV_ALIGN_TOP_LEFT,80,22);
    frameInfo->txt_color(lv_color_white(),LV_PART_MAIN);
    frameInfo->txt_font_size(30, FT_FONT_STYLE_NORMAL);
    frameInfo->txt_align(LV_TEXT_ALIGN_LEFT);
    frameInfo->txt_long_mode(LV_LABEL_LONG_DOT);
    frameInfo->set_txt(STR_DEVICEINFO);

    frameName = new LvcppLabel(frameDeviceInfo->myobj);
    frameName->set_size(290,40);
    frameName->set_main_bg_opa(LV_OPA_0);
    frameName->align(LV_ALIGN_RIGHT_MID,-46,0);
    frameName->txt_color(lv_color_white(),LV_PART_MAIN);
    frameName->txt_font_size(30, FT_FONT_STYLE_NORMAL);
    frameName->txt_align(LV_TEXT_ALIGN_RIGHT);
    frameName->txt_long_mode(LV_LABEL_LONG_DOT);
    frameName->set_txt(deviceNickname);
    frameName->add_flag(LV_OBJ_FLAG_CLICKABLE);
    frameName->add_event_cb(frame_list_event_handler,LV_EVENT_CLICKED,this);

    frameDownUp = new LvcppLabel(frameDeviceInfo->myobj);
    frameDownUp->set_size(36,26);
    frameDownUp->set_main_bg_img_src(devPatch[frameInfoStatus]);
    frameDownUp->align(LV_ALIGN_RIGHT_MID,0,0);
    frameDownUp->set_main_bg_opa(LV_OPA_0);
    frameDownUp->set_txt("");

    frameInfoList = new frameInfoSence(parent);
    frameInfoList->qrcodeButton->add_event_cb(frame_list_event_handler,LV_EVENT_CLICKED,this);

    frameLine1 = new LvcppLabel(parent);
    frameLine1->set_size(880,2);
    frameLine1->set_main_bg_color(MENU_BTN_COLOR,LV_OPA_100);
    frameLine1->align(LV_ALIGN_CENTER,0,0);
    frameLine1->set_txt("");

    frameManagement = new LvcppLabel(parent);
    frameManagement->set_size(860,80);
    frameManagement->set_main_bg_color(lv_color_hex(0x00516a),LV_OPA_0);
    frameManagement->set_txt("");
    frameManagement->add_flag(LV_OBJ_FLAG_CLICKABLE);
    frameManagement->add_event_cb(frame_list_event_handler,LV_EVENT_CLICKED,this);

    frameManaUser = new LvcppLabel(frameManagement->myobj);
    frameManaUser->set_size(48,44);
    frameManaUser->set_main_bg_img_src(SETTING_FRAME_USERMAKE_PNG);
    frameManaUser->align(LV_ALIGN_TOP_LEFT,20,18);
    frameManaUser->set_main_bg_opa(LV_OPA_0);
    frameManaUser->set_txt("");

    frameManaUserStr = new LvcppLabel(frameManagement->myobj);
    frameManaUserStr->set_size(550,36);
    frameManaUserStr->set_main_bg_opa(LV_OPA_0);
    frameManaUserStr->align(LV_ALIGN_TOP_LEFT,80,22);
    frameManaUserStr->txt_color(lv_color_white(),LV_PART_MAIN);
    frameManaUserStr->txt_font_size(30, FT_FONT_STYLE_NORMAL);
    frameManaUserStr->txt_align(LV_TEXT_ALIGN_LEFT);
    frameManaUserStr->txt_long_mode(LV_LABEL_LONG_DOT);
    frameManaUserStr->set_txt(STR_USERMANAGMENT);

    frameManaUserAdd = new LvcppLabel(frameManagement->myobj);
    frameManaUserAdd->set_size(40,40);
    frameManaUserAdd->set_main_bg_img_src(SETTING_FRAME_ADD_PNG);
    frameManaUserAdd->align(LV_ALIGN_RIGHT_MID,0,0);
    frameManaUserAdd->set_main_bg_opa(LV_OPA_0);
    frameManaUserAdd->set_txt("");

    frameLine2 = new LvcppLabel(parent);
    frameLine2->set_size(880,2);
    frameLine2->set_main_bg_color(MENU_BTN_COLOR,LV_OPA_100);
    frameLine2->align(LV_ALIGN_CENTER,0,0);
    frameLine2->set_txt("");

    frameUserStr = new LvcppLabel(parent);
    frameUserStr->set_size(550,60);
    frameUserStr->set_main_pad_L_R(20,0);
    frameUserStr->set_main_pad_T_B(10,0);
    frameUserStr->set_main_bg_opa(LV_OPA_0);
    frameUserStr->txt_color(lv_color_white(),LV_PART_MAIN);
    frameUserStr->txt_font_size(30, FT_FONT_STYLE_NORMAL);
    frameUserStr->txt_align(LV_TEXT_ALIGN_LEFT);
    frameUserStr->txt_long_mode(LV_LABEL_LONG_DOT);
    frameUserStr->set_txt(STR_USERS);

    frameUserList = new LvcppList(parent);
    frameUserList->set_size(880,200);
    frameUserList->set_main_bg_opa(LV_OPA_0);
    frameUserList->set_flex_flow(LV_FLEX_FLOW_ROW_WRAP);
    frameUserList->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    frameUserList->set_main_pad_all(0);
    frameUserList->set_main_pad_row(0);
    frameUserList->set_main_pad_column(2);
    frameUserList->set_main_border_width(0);
    frameUserList->set_main_radius(0);

    memset(&userList_id, 0 , sizeof(userSenceList_item_info));
	userTotal = settinglist_get_userNum();
    for(int i=userList_id.total;i<userTotal;i++)
    {
        userList_id.list_item[i] = new frameUserSence(frameUserList->myobj);
        userList_id.list_item[i]->frameUser->set_userdata((void*)i);
        userList_id.list_item[i]->frameUser->add_event_cb(user_list_event_handler,LV_EVENT_RELEASED,this);
		updata_user_info(i);
        userList_id.total++;
    }
}
frameSence::~frameSence(void)
{
    for(int i=userList_id.total;i>0;i--)
    {
        userList_id.total--;
        if(userList_id.list_item[userList_id.total] !=NULL)
        {
            delete userList_id.list_item[userList_id.total];
            userList_id.list_item[userList_id.total] =NULL;
        }
    }
    if(UserInfo !=NULL)
    {
        delete UserInfo;
        UserInfo = NULL;
    }
    if(frameStr !=NULL)
    {
        delete frameStr;
        frameStr = NULL;
    }
    if(frameUserList != NULL)
    {
        delete frameUserList;
        frameUserList = NULL;
    }
    if(frameUserStr != NULL)
    {
        delete frameUserStr;
        frameUserStr = NULL;
    }
    if(frameManaUser != NULL)
    {
        delete frameManaUser;
        frameManaUser = NULL;
    }
    if(frameManaUserStr != NULL)
    {
        delete frameManaUserStr;
        frameManaUserStr = NULL;
    }
    if(frameManaUserAdd != NULL)
    {
        delete frameManaUserAdd;
        frameManaUserAdd = NULL;
    }
    if(frameManagement != NULL)
    {
        delete frameManagement;
        frameManagement = NULL;
    }
    if(frameLine1 != NULL)
    {
        delete frameLine1;
        frameLine1 = NULL;
    }
    if(frameLine2 != NULL)
    {
        delete frameLine2;
        frameLine2 = NULL;
    }
    if(frameDownUp != NULL)
    {
        delete frameDownUp;
        frameDownUp = NULL;
    }
    if(frameName != NULL)
    {
        delete frameName;
        frameName = NULL;
    }
    if(frameInfo != NULL)
    {
        delete frameInfo;
        frameInfo = NULL;
    }
    if(frameDevice != NULL)
    {
        delete frameDevice;
        frameDevice = NULL;
    }
    if(frameDeviceInfo != NULL)
    {
        delete frameDeviceInfo;
        frameDeviceInfo = NULL;
    }
    if(frameNameList != NULL)
    {
        delete frameNameList;
        frameNameList = NULL;
    }
    if(frameInfoList != NULL)
    {
        delete frameInfoList;
        frameInfoList = NULL;
    }
    ui_image_free();
}

void frameSence::frame_list_event_handler(lv_event_t *event)
{
    frameSence* opt = (frameSence*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
#ifdef IMAGE_DECODE
    void *devPatch[2]={opt->SETTING_DOWN_DEVICE_PNG,opt->SETTING_UP_DEVICE_PNG};
#endif

    if((opt->frameDeviceInfo !=NULL)&&(target ==opt->frameDeviceInfo->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            opt->frameInfoStatus = !opt->frameInfoStatus;
            opt->frameDownUp->set_main_bg_img_src(devPatch[opt->frameInfoStatus]);
            opt->frameInfoList->frame->show(opt->frameInfoStatus);
        }
    }
    else if((opt->frameName !=NULL)&&(target ==opt->frameName->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            opt->frameStrType =0;
            opt->frameStr_head_creat((char*)STR_DEVHEAD,opt->deviceNickname);
        }
    }
    else if((opt->frameInfoList !=NULL)&&(opt->frameInfoList->qrcodeButton !=NULL)&&(target ==opt->frameInfoList->qrcodeButton->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            if((opt->frameInfoList !=NULL)&&(opt->frameInfoList->qrcodeButton !=NULL))
            {
                opt->frameInfoList->qrcode_updata();
            }
        }
    }
    else if((opt->frameManagement !=NULL)&&(target ==opt->frameManagement->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            memset(opt->emailstr,0,sizeof(opt->emailstr));
            opt->frameStrType =1;
            opt->frameStr_head_creat((char*)STR_EMAILHEAD,opt->emailstr);
        }
    }
}
void frameSence::frameStr_head_creat(char *headStr,char *dataStr)
{
    if(frameStr ==NULL)
    {
        frameStr = new frameChangeStr(headStr,dataStr);
        frameStr->StrScreen->add_event_cb(devName_event_handler,LV_EVENT_RELEASED,this);
        frameStr->headLabel->add_event_cb(devName_event_handler,LV_EVENT_RELEASED,this);
        frameStr->OKLabel->add_event_cb(devName_event_handler,LV_EVENT_RELEASED,this);
        frameStr->CancelLabel->add_event_cb(devName_event_handler,LV_EVENT_RELEASED,this);
    }
}
void frameSence::frameStr_head_del(void)
{
    if(frameStr !=NULL)
    {
        delete frameStr;
        frameStr = NULL;
    }
}
void frameSence::devName_event_handler(lv_event_t *event)
{
    frameSence* opt = (frameSence*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    const char *txt_buff =NULL;

    if((opt->frameStr !=NULL)&&(opt->frameStr->OKLabel!=NULL)&&(target ==opt->frameStr->OKLabel->myobj))
    {
        if(event->code== LV_EVENT_RELEASED)
        {
            txt_buff = opt->frameStr->textarea->get_text();
            if(txt_buff !=NULL)
            {
                if(opt->frameStrType ==0)
                {
                    memset(opt->deviceNickname,0,sizeof(opt->deviceNickname));
                    sprintf(opt->deviceNickname,txt_buff);
                    if(opt->frameName !=NULL)
                        opt->frameName->set_txt(opt->deviceNickname);
                }
                else if(opt->frameStrType ==1)
                {
                    memset(opt->emailstr,0,sizeof(opt->emailstr));
                    sprintf(opt->emailstr,txt_buff);
                }
                else
                {
                    memset(opt->userName,0,sizeof(opt->userName));
                    sprintf(opt->userName,txt_buff);
					opt->set_user_remarkName(opt->userCurIdex);
					opt->updata_user_info(opt->userCurIdex);
                }
            }
            opt->frameStr_head_del();
        }
    }
    else if((opt->frameStr !=NULL)&&(opt->frameStr->CancelLabel!=NULL)&&(target ==opt->frameStr->CancelLabel->myobj))
    {
        if(event->code== LV_EVENT_RELEASED)
        {
            opt->frameStr_head_del();
        }
    }
    else if((opt->frameStr !=NULL)&&(opt->frameStr->StrScreen!=NULL)&&(target ==opt->frameStr->StrScreen->myobj))
    {
        opt->frameStr_head_del();
    }
}

void frameSence::user_list_event_handler(lv_event_t *event)
{
    frameSence* opt = (frameSence*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    lv_obj_t* cont = lv_event_get_current_target(event);
    int sel_selete = (uintptr_t)target->user_data;

    if(cont != target)
    {
        sel_selete = (uintptr_t)cont->user_data;
    }

    if(event->code== LV_EVENT_RELEASED)
    {
        LV_LOG_USER("sel_selete:%d",sel_selete);
        opt->userInfo_head_creat(sel_selete);
    }
}

void frameSence::userInfo_head_creat(int userIdex)
{
    if(UserInfo ==NULL)
    {
    	userCurIdex = userIdex;
		get_user_info(userIdex);
		LV_LOG_USER("userName:%s",userName);
        UserInfo = new frameUserInfo(userName);
        UserInfo->UserInfoScreen->add_event_cb(userInfo_event_handler,LV_EVENT_RELEASED,this);
        UserInfo->headLabel->add_event_cb(userInfo_event_handler,LV_EVENT_RELEASED,this);
        UserInfo->ViewPhotos->add_event_cb(userInfo_event_handler,LV_EVENT_RELEASED,this);
        UserInfo->remarkName->add_event_cb(userInfo_event_handler,LV_EVENT_RELEASED,this);
        UserInfo->delUser->add_event_cb(userInfo_event_handler,LV_EVENT_RELEASED,this);
        UserInfo->delUserPhoto->add_event_cb(userInfo_event_handler,LV_EVENT_RELEASED,this);
    }
}

void frameSence::userInfo_head_del(void)
{
    if(UserInfo !=NULL)
    {
        delete UserInfo;
        UserInfo = NULL;
    }
}
void frameSence::userInfo_event_handler(lv_event_t *event)
{
    frameSence* opt = (frameSence*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if((opt->UserInfo !=NULL)&&(opt->UserInfo->ViewPhotos!=NULL)&&(target ==opt->UserInfo->ViewPhotos->myobj))
    {
        if(event->code== LV_EVENT_RELEASED)
        {
            LV_LOG_USER("ViewPhotos");
        }
    }
    else if((opt->UserInfo !=NULL)&&(opt->UserInfo->remarkName!=NULL)&&(target ==opt->UserInfo->remarkName->myobj))
    {
        if(event->code== LV_EVENT_RELEASED)
        {
            opt->frameStrType =2;
            opt->frameStr_head_creat((char*)STR_REMARKNAME,opt->userName);
            opt->userInfo_head_del();
        }
    }
    else if((opt->UserInfo !=NULL)&&(opt->UserInfo->delUser!=NULL)&&(target ==opt->UserInfo->delUser->myobj))
    {
        if(event->code== LV_EVENT_RELEASED)
        {
            LV_LOG_USER("delUser");
        }
    }
    else if((opt->UserInfo !=NULL)&&(opt->UserInfo->delUserPhoto!=NULL)&&(target ==opt->UserInfo->delUserPhoto->myobj))
    {
        if(event->code== LV_EVENT_RELEASED)
        {
            LV_LOG_USER("delUserPhoto");
        }
    }
    else if((opt->UserInfo !=NULL)&&(opt->UserInfo->UserInfoScreen!=NULL)&&(target ==opt->UserInfo->UserInfoScreen->myobj))
    {
        opt->userInfo_head_del();
    }
}
int frameSence::settinglist_get_userNum(void)
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
int frameSence::settinglist_userInfo(int userNum,char *userID)
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

static int settinglist_url_htoi(char *s)
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

int _settinglist_url_decode(char *str, int len)
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
            *dest = (char) settinglist_url_htoi(data + 1);
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

void frameSence::updata_user_info(int index)
{
	char buff[64]={0};
    char userBuff[64]={0};
	
	if(settinglist_userInfo(index,userBuff)<0)
            sprintf(buff,"%s%d","User",index);
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
                    _settinglist_url_decode(buff,strlen(buff));
                }
            }
            else
            {
                _settinglist_url_decode(buff,strlen(buff));
            }
        }
        else
        {
           _settinglist_url_decode(buff,strlen(buff));
        }
#endif
	}
	if(userList_id.list_item[index]!=NULL)
	{
		userList_id.list_item[index]->frameUser_updata_Name(buff);
	}
}
void frameSence::get_user_info(int index)
{
    memset(userName,0,sizeof(userName));
	memset(senderId,0,sizeof(senderId));
	if(settinglist_userInfo(index,senderId)<0)
            sprintf(userName,"%s%d","User",index);
    else
    {
#ifdef _UCHIP_T113
        memset(userName,0,sizeof(userName));
        if(read_string_userinfo_param(senderId,SENDERREMARKNAME,userName,sizeof(userName))<0)
        {
            memset(userName,0,sizeof(userName));
            if(read_string_userinfo_param(senderId,SENDERNICKNAME,userName,sizeof(userName))<0)
            {
                memset(userName,0,sizeof(userName));
                if(read_string_userinfo_param(senderId,SENDNAME,userName,sizeof(userName))<0)
                {
                    memset(userName,0,sizeof(userName));
                    sprintf(userName,"%s",senderId);
                }
                else
                {
                    _settinglist_url_decode(userName,strlen(userName));
                }
            }
            else
            {
                _settinglist_url_decode(userName,strlen(userName));
            }
        }
        else
        {
           _settinglist_url_decode(userName,strlen(userName));
        }
#endif
	}
}
void frameSence::set_user_remarkName(int index)
{
    char userBuff[64]={0};
	
	if(settinglist_userInfo(index,userBuff)<0)
		return;
    else
    {
#ifdef _UCHIP_T113
        write_string_userinfo_param(userBuff,SENDERREMARKNAME,userName,sizeof(userName));
#endif
	}
}