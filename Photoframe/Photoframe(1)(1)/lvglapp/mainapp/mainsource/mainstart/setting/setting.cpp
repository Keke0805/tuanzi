#include  "../mainappstart.h"
#include "setting.h"
#include  "lvgl/src/extra/lv_extra.h"
#include  "mainstart/include/ui_config.h"
#include  "mainstart/include/str_config.h"
#include  "common/common.h"

void settingScene::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    HEAD_RETURN_PNG=(void*)parse_image_from_file(HEAD_RETURN_PNG_PATH);
    HEAD_RETURN_SEL_PNG=(void*)parse_image_from_file(HEAD_RETURN_SEL_PNG_PATH);
    HEAD_ICON_SETTING_PNG=(void*)parse_image_from_file(HEAD_ICON_SETTING_PNG_PATH);
	LISTBG_PNG=(void*)parse_image_from_file(LISTBG_PNG_PATH);
	
	SETTING_DISP_OPEN_PNG=(void*)parse_image_from_file(SETTING_DISP_OPEN_PNG_PATH);
	SETTING_DISP_CLOSE_PNG=(void*)parse_image_from_file(SETTING_DISP_CLOSE_PNG_PATH);
    SETTING_MYFRAME_PNG=(void*)parse_image_from_file(SETTING_MYFRAME_PNG_PATH);
    SETTING_ALBUM_PNG=(void*)parse_image_from_file(SETTING_ALBUM_PNG_PATH);
    SETTING_WIFI_PNG=(void*)parse_image_from_file(SETTING_WIFI_PNG_PATH);
    SETTING_FACTORY_PNG=(void*)parse_image_from_file(SETTING_FACTORY_PNG_PATH);
    SETTING_HELP_PNG=(void*)parse_image_from_file(SETTING_HELP_PNG_PATH);
    SETTING_ABOUT_PNG=(void*)parse_image_from_file(SETTING_ABOUT_PNG_PATH);
#endif
}
void settingScene::ui_image_free(void)
{
#ifdef IMAGE_DECODE
    free_image(HEAD_RETURN_PNG);
    free_image(HEAD_RETURN_SEL_PNG);
    free_image(HEAD_ICON_SETTING_PNG);
	free_image(LISTBG_PNG);
	
	free_image(SETTING_DISP_OPEN_PNG);
	free_image(SETTING_DISP_CLOSE_PNG);
    free_image(SETTING_MYFRAME_PNG);
    free_image(SETTING_ALBUM_PNG);
    free_image(SETTING_WIFI_PNG);
    free_image(SETTING_FACTORY_PNG);
    free_image(SETTING_HELP_PNG);
    free_image(SETTING_ABOUT_PNG);
#endif
}

settingScene::settingScene(lv_obj_t* parent)
{
    ui_image_decode();
    frame = new LvcppScreen(parent);
    frame->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    frame->set_main_bg_color(lv_color_hex(0x0084e1),LV_OPA_0);
    frame->set_main_bg_img_src(LISTBG_PNG);
    mainscreen = frame->myobj;
	wlantimer = startTimer(1000, this);
}

settingScene::~settingScene(void)
{

#ifdef _UCHIP_T113
	write_string_type_param(SETTING_SCENE, SET_DEV_NAME, statue.device_name,sizeof(statue.device_name));
	write_string_type_param(SETTING_SCENE, SET_USER_NAME, statue.user_name,sizeof(statue.user_name));
	write_int_type_param(PUBLIC_SCENE, BACKLIGHT, statue.blk);
	write_int_type_param(PUBLIC_SCENE, VOLUME, statue.vol);
	write_int_type_param(SETTING_SCENE, SET_TP_VOL_MOD, statue.tpvol_statue);
	write_int_type_param(SETTING_SCENE, SET_BOY, statue.ball);
	write_int_type_param(PUBLIC_SCENE, LANGUAGE, statue.language);
	write_int_type_param(SETTING_SCENE, SET_AUTOPLAY_MOD, statue.autoplay);
	write_int_type_param(SETTING_SCENE, SET_PHOTO_DISP_ORDER, statue.disp_order);
	write_int_type_param(SETTING_SCENE, SET_PHOTO_SORT_ORDER, statue.order_sty);
	write_int_type_param(SETTING_SCENE, SET_DESCRIBE, statue.describe);
	write_int_type_param(SETTING_SCENE, SET_BODY_INDUCTION, statue.renti);
	write_int_type_param(SETTING_SCENE, SET_MSG_VOL, statue.msg_sound);
	//write_int_type_param(SETTING_SCENE, SET_RES_FACTORY, statue.res_factory);
	write_int_type_param(SETTING_SCENE, SET_DATA_STY, statue.auto_datetime);
	write_int_type_param(SETTING_SCENE, SET_TIME_STY, statue.time_sty);
#endif

    child_scene_del();
    settingScene_head_dele();
    settingScene_main_dele();

	if(listframe != NULL)
    {
        delete listframe;
        listframe = NULL;
    }
    if(frame !=NULL)
    {
        delete frame;
        frame =NULL;
    }
    ui_image_free();
}

int settingScene::init_parament(void)
{
	memset(&statue, 0 , sizeof(setting_statue_info));
#ifdef _UCHIP_T113
	read_string_type_param(SETTING_SCENE, SET_DEV_NAME, statue.device_name,sizeof(statue.device_name));
	read_string_type_param(SETTING_SCENE, SET_USER_NAME, statue.user_name,sizeof(statue.user_name));
	
	//read_int_type_param(SETTING_SCENE, SET_RES_FACTORY, &statue.res_factory);
	read_int_type_param(SETTING_SCENE, SET_DATA_STY, &statue.auto_datetime);
	read_int_type_param(SETTING_SCENE, SET_TIME_STY, &statue.time_sty);
	read_string_type_param(PUBLIC_SCENE, DATE, statue.day,sizeof(statue.day));
	read_string_type_param(PUBLIC_SCENE, TIME, statue.time,sizeof(statue.time));
#endif
	settingScene_head_creat();
    settingScene_main_creat();
    child_scene_creat();
	create_child_list(list_index);
    return 0;
}
void settingScene::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    static int timecnt = 0;
    timecnt++;
}
void settingScene::settingScene_head_creat(void)
{
    buttonReturn = new LvcppButton(mainscreen);
    buttonReturn->set_size(66,66);
    buttonReturn->align(LV_ALIGN_TOP_LEFT,30,8);
    buttonReturn->set_main_bg_opa(LV_OPA_0);
    buttonReturn->set_main_radius(0);
    buttonReturn->set_main_pad_all(0);
    buttonReturn->set_main_border_width(0);
    buttonReturn->set_main_bg_img_src(HEAD_RETURN_PNG);
    buttonReturn->add_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
    buttonReturn->add_event_cb(head_event_handler,LV_EVENT_PRESSED,this);
    buttonReturn->add_event_cb(head_event_handler,LV_EVENT_RELEASED,this);

	line_head = new LvcppButton(mainscreen);
    line_head->set_size(1280,2);
    line_head->align(LV_ALIGN_TOP_LEFT,0,78);
    line_head->set_main_bg_color(lv_color_hex(0x00516a),LV_OPA_100);
	line_head->clear_flag(LV_OBJ_FLAG_CLICKABLE);
	

    settingIcon = new LvcppButton(mainscreen);
    settingIcon->set_size(66,66);
    settingIcon->align(LV_ALIGN_TOP_LEFT,114,8);
    settingIcon->set_main_bg_opa(LV_OPA_0);
    settingIcon->set_main_radius(0);
    settingIcon->set_main_pad_all(0);
    settingIcon->set_main_border_width(0);
    settingIcon->set_main_bg_img_src(HEAD_ICON_SETTING_PNG);
}

void settingScene::settingScene_head_dele(void)
{
    if(buttonReturn != NULL)
    {
        delete buttonReturn;
        buttonReturn =NULL;
    }
	if(line_head != NULL)
    {
        delete line_head;
        line_head =NULL;
    }
    if(settingIcon != NULL)
    {
        delete settingIcon;
        settingIcon =NULL;
    }
}

void settingScene::head_event_handler(lv_event_t *event)
{
    settingScene* opt = (settingScene*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    bool reStatus =true;

    if((opt->helpReturn !=NULL)&&(target ==opt->helpReturn->myobj))
    {
        if(event->code== LV_EVENT_PRESSED)
        {
            if(opt->helpReturn !=NULL)
                opt->helpReturn->set_main_bg_img_src(opt->HEAD_RETURN_SEL_PNG);
        }
        else if(event->code== LV_EVENT_RELEASED)
        {
            opt->del_child_list(opt->list_save_index);
            opt->list_index =0;
			opt->mainList->switch_select_state(opt->list_index,lv_color_hex(0x0a85a6),lv_color_hex(0x00516a));
            opt->create_child_list(opt->list_index);
            opt->list_save_index =opt->list_index;  
        }
    }
	else if((opt->buttonReturn !=NULL)&&(target ==opt->buttonReturn->myobj))
	{
		if(event->code== LV_EVENT_PRESSED)
        {
            opt->buttonReturn->set_main_bg_img_src(opt->HEAD_RETURN_SEL_PNG);
        }
        else if(event->code== LV_EVENT_RELEASED)
        {
            if(opt->album_scene !=NULL)
            {
                if(opt->album_scene->lauList!=NULL)
                {
                    if(opt->album_scene->lauList->LanguageScreen!=NULL)
                    {
                        opt->album_scene->albumLau_del();
                        reStatus =false;
                    }
                }
            }
            if(reStatus ==true)
            {
                MainAPPStart::settingScenemain_destory();
            }
        }
	}
	LV_LOG_USER("list_index =%d",opt->list_index);
}

void settingScene::settingScene_main_creat(void)
{
    mainList = new LvcppList(mainscreen);
    mainList->set_size(380,720);
    mainList->align(LV_ALIGN_TOP_LEFT,0,80);
    mainList->set_main_bg_color(lv_color_hex(0x00516a),LV_OPA_0);
    mainList->set_flex_flow(LV_FLEX_FLOW_COLUMN);
    mainList->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    mainList->set_main_pad_all(1);
    mainList->set_main_pad_row(1);
    mainList->set_main_pad_column(0);
    mainList->set_main_border_width(0);
    mainList->set_main_radius(0);

    MyFrameList =new mainIconList(mainList->myobj);
    MyFrameList->updata_icon_name((void*)SETTING_MYFRAME_PNG,(char*)STR_MYFRAME);
    MyFrameList->frame->add_event_cb(settingScene_main_event_handler,LV_EVENT_CLICKED,this);

    AlbumList =new mainIconList(mainList->myobj);
    AlbumList->updata_icon_name((void*)SETTING_ALBUM_PNG,(char*)STR_ALBUM);
    AlbumList->frame->add_event_cb(settingScene_main_event_handler,LV_EVENT_CLICKED,this);

    WiFiList =new mainIconList(mainList->myobj);
    WiFiList->updata_icon_name((void*)SETTING_WIFI_PNG,(char*)STR_WI_FI);
    WiFiList->frame->add_event_cb(settingScene_main_event_handler,LV_EVENT_CLICKED,this);

    FactoryList =new mainIconList(mainList->myobj);
    FactoryList->updata_icon_name((void*)SETTING_FACTORY_PNG,(char*)STR_FACTORY);
    FactoryList->frame->add_event_cb(settingScene_main_event_handler,LV_EVENT_CLICKED,this);

    HelpList =new mainIconList(mainList->myobj);
    HelpList->updata_icon_name((void*)SETTING_HELP_PNG,(char*)STR_HELP);
    HelpList->frame->add_event_cb(settingScene_main_event_handler,LV_EVENT_CLICKED,this);

    AboutList =new mainIconList(mainList->myobj);
    AboutList->updata_icon_name((void*)SETTING_ABOUT_PNG,(char*)STR_ABOUT);
    AboutList->frame->add_event_cb(settingScene_main_event_handler,LV_EVENT_CLICKED,this);

	mainList->set_select_state(list_index,lv_color_hex(0x0084e1));
}

void settingScene::settingScene_main_dele(void)
{
    if(MyFrameList != NULL)
    {
        delete MyFrameList;
        MyFrameList =NULL;
    }
    if(AlbumList != NULL)
    {
        delete AlbumList;
        AlbumList =NULL;
    }
    if(WiFiList != NULL)
    {
        delete WiFiList;
        WiFiList =NULL;
    }
    if(FactoryList != NULL)
    {
        delete FactoryList;
        FactoryList =NULL;
    }
    if(HelpList != NULL)
    {
        delete HelpList;
        HelpList =NULL;
    }
    if(AboutList != NULL)
    {
        delete AboutList;
        AboutList =NULL;
    }
    if(mainList != NULL)
    {
        delete mainList;
        mainList =NULL;
    }
}

void settingScene::settingScene_main_event_handler(lv_event_t *event)
{
    settingScene* opt = (settingScene*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
	
    if((opt->MyFrameList !=NULL)&&(opt->MyFrameList->frame!=NULL)&&(target==opt->MyFrameList->frame->myobj))
    {
        opt->list_index =0;
    }
    else if((opt->AlbumList !=NULL)&&(opt->AlbumList->frame!=NULL)&&(target==opt->AlbumList->frame->myobj))
    {
        opt->list_index =1;
    }
    else if((opt->WiFiList !=NULL)&&(opt->WiFiList->frame!=NULL)&&(target==opt->WiFiList->frame->myobj))
    {
        opt->list_index =2;
    }
    else if((opt->FactoryList !=NULL)&&(opt->FactoryList->frame!=NULL)&&(target==opt->FactoryList->frame->myobj))
    {
        opt->list_index =3;
    }
    else if((opt->HelpList !=NULL)&&(opt->HelpList->frame!=NULL)&&(target==opt->HelpList->frame->myobj))
    {
        opt->list_index =4;
    }
    else if((opt->AboutList !=NULL)&&(opt->AboutList->frame!=NULL)&&(target==opt->AboutList->frame->myobj))
    {
        opt->list_index =5;
    }
    opt->mainList->switch_select_state(opt->list_index,lv_color_hex(0x0a85a6),lv_color_hex(0x0084e1));
	if(opt->list_save_index !=opt->list_index)
	{
		opt->del_child_list(opt->list_save_index);
		opt->create_child_list(opt->list_index);
		opt->list_save_index =opt->list_index;
	}
	else if(opt->list_index==1)
	{
		LV_LOG_USER("list_index =%d",opt->list_index);
		if(opt->album_scene !=NULL)
        {
            if(opt->album_scene->lauList!=NULL)
            {
                if(opt->album_scene->lauList->LanguageScreen!=NULL)
                {
                	LV_LOG_USER("list_index =%d",opt->list_index);
                    opt->album_scene->albumLau_del();
					LV_LOG_USER("list_index =%d",opt->list_index);
                }
            }
        }
		LV_LOG_USER("list_index =%d",opt->list_index);
	}
	LV_LOG_USER("list_index =%d",opt->list_index);
}

void settingScene::child_scene_creat(void)
{
    childList = new LvcppList(mainscreen);
    childList->set_size(880,700);
    childList->align(LV_ALIGN_TOP_LEFT,390,90);
    childList->set_main_bg_color(lv_color_hex(0x0499c3),LV_OPA_100);
    childList->set_flex_flow(LV_FLEX_FLOW_COLUMN);
    childList->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    childList->set_main_pad_all(0);
    childList->set_main_pad_row(0);
    childList->set_main_pad_column(0);
    childList->set_main_border_width(0);
    childList->set_main_radius(0);
}
void settingScene::child_scene_del(void)
{
    delete_frame_list();
	delete_album_list();
    delete_fcactory_list();
    delete_about_list();
    if(childList != NULL)
    {
        delete childList;
        childList = NULL;
    }
}
void settingScene::create_child_list(int indexList)
{
    switch(indexList)
    {
        case 0:
            create_frame_list();
        break;
        case 1:
            create_album_list();
        break;
        case 3:
            create_fcactory_list();
        break;
        case 4:
            create_help_list();
        break;
        case 5:
            create_about_list();
        break;
        default:
        break;
    }
}
void settingScene::del_child_list(int indexList)
{
    switch(indexList)
    {
        case 0:
            delete_frame_list();
        break;
        case 1:
            delete_album_list();
        break;
        case 3:
            delete_fcactory_list();
        break;
        case 4:
            delete_help_list();
        break;
        case 5:
            delete_about_list();
        break;
        default:
        break;
    }
	list_save_index =indexList;
}
void settingScene::create_frame_list(void)
{
	
	if(frame_scene ==NULL)
	{
		printf("%s %d %s create_frame_list\n", __FILE__, __LINE__, __func__);
        frame_scene = new frameSence(childList->myobj);
	}
}

void settingScene::delete_frame_list(void)
{
    if(frame_scene != NULL)
    {
    	printf("%s %d %s delete_frame_list\n", __FILE__, __LINE__, __func__);
        delete frame_scene;
        frame_scene = NULL;
    }
}

void settingScene::create_album_list(void)
{
    if(album_scene == NULL)
    {
    	printf("%s %d %s create_album_list\n", __FILE__, __LINE__, __func__);
        album_scene = new albumScene(childList->myobj);
		LV_LOG_USER("create_album_list finish");
    }
}

void settingScene::delete_album_list(void)
{
    if(album_scene != NULL)
    {
    	printf("%s %d %s delete_album_list\n", __FILE__, __LINE__, __func__);
        delete album_scene;
        album_scene = NULL;
    }
}

void settingScene::create_fcactory_list(void)
{
    if(fcactory_scene == NULL)
    {
        fcactory_scene = new factorySence(childList->myobj);
    }
}

void settingScene::delete_fcactory_list(void)
{
    if(fcactory_scene != NULL)
    {
        delete fcactory_scene;
        fcactory_scene = NULL;
    }
}

void settingScene::create_help_list(void)
{
    if(help_scene == NULL)
    {
        help_scene = new helpSence();
        if(helpReturn ==NULL)
        {
            helpReturn = new LvcppButton(help_scene->helpScreen->myobj);
            helpReturn->set_size(66,66);
            helpReturn->align(LV_ALIGN_TOP_LEFT,30,8);
            helpReturn->set_main_bg_opa(LV_OPA_0);
            helpReturn->set_main_radius(0);
            helpReturn->set_main_pad_all(0);
            helpReturn->set_main_border_width(0);
            helpReturn->set_main_bg_img_src(HEAD_RETURN_PNG);
            helpReturn->add_event_cb(head_event_handler,LV_EVENT_PRESSED,this);
            helpReturn->add_event_cb(head_event_handler,LV_EVENT_RELEASED,this);
        }
    }
}

void settingScene::delete_help_list(void)
{
    if(helpReturn != NULL)
    {
        delete helpReturn;
        helpReturn = NULL;
    }
    if(help_scene != NULL)
    {
        delete help_scene;
        help_scene = NULL;
    }
}

void settingScene::create_about_list(void)
{
    if(about_scene == NULL)
    {
        about_scene = new aboutSence(childList->myobj);
    }
}

void settingScene::delete_about_list(void)
{
    if(about_scene != NULL)
    {
        delete about_scene;
        about_scene = NULL;
    }
}
