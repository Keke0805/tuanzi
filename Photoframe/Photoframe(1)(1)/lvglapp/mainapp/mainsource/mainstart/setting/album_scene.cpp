#include "album_scene.h"
#include "mainstart/include/ui_config.h"
#include "mainstart/include/str_config.h"
#include "mainstart/include/configCustom.h"
#include "mainstart/customer_config.h"
#ifdef _UCHIP_T113
#include  "common/common.h"
#endif

#ifdef IMAGE_DECODE
#else
static const void *openPatch[2]={SETTING_DISP_CLOSE_PNG,SETTING_DISP_OPEN_PNG};
#endif
static const void *timeStr[8]={STR_15S,STR_30S,STR_1M,STR_2M,STR_5M,STR_10M,STR_30M,STR_NEVER};
static const void *modeStr[2]={STR_SEQUENTIAL,STR_RANDOMS};
static const void *motionStr[5]={STR_OFF,STR_2M,STR_5M,STR_15M,STR_30M};

void albumScene::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    SETTING_DISP_CLOSE_PNG=(void*)parse_image_from_file(SETTING_DISP_CLOSE_PNG_PATH);
    SETTING_DISP_OPEN_PNG=(void*)parse_image_from_file(SETTING_DISP_OPEN_PNG_PATH);

    SETTING_DISP_BRI_PNG=(void*)parse_image_from_file(SETTING_DISP_BRI_PNG_PATH);
    SETTING_DISP_VOL_PNG=(void*)parse_image_from_file(SETTING_DISP_VOL_PNG_PATH);
    SETTING_DISP_TPVOL_PNG=(void*)parse_image_from_file(SETTING_DISP_TPVOL_PNG_PATH);
    SETTING_DISP_BOY_PNG=(void*)parse_image_from_file(SETTING_DISP_BOY_PNG_PATH);
    SETTING_DISP_LAGU_PNG=(void*)parse_image_from_file(SETTING_DISP_LAGU_PNG_PATH);
    SETTING_DISP_PLAY_PNG=(void*)parse_image_from_file(SETTING_DISP_PLAY_PNG_PATH);
    SETTING_DISP_PHOTO_PNG=(void*)parse_image_from_file(SETTING_DISP_PHOTO_PNG_PATH);
    SETTING_DISP_MIAOSHU_PNG=(void*)parse_image_from_file(SETTING_DISP_MIAOSHU_PNG_PATH);
    SETTING_DISP_DATATIME_PNG=(void*)parse_image_from_file(SETTING_DISP_DATATIME_PNG_PATH);
    SETTING_DISP_SLEEP_PNG=(void*)parse_image_from_file(SETTING_DISP_SLEEP_PNG_PATH);
    SETTING_DISP_RENTI_PNG=(void*)parse_image_from_file(SETTING_DISP_RENTI_PNG_PATH);
    SETTING_DISP_TZVOL_PNG=(void*)parse_image_from_file(SETTING_DISP_TZVOL_PNG_PATH);
#endif
}
void albumScene::ui_image_free(void)
{
#ifdef IMAGE_DECODE
    free_image(SETTING_DISP_CLOSE_PNG);
    free_image(SETTING_DISP_OPEN_PNG);

    free_image(SETTING_DISP_BRI_PNG);
    free_image(SETTING_DISP_VOL_PNG);
    free_image(SETTING_DISP_TPVOL_PNG);
    free_image(SETTING_DISP_BOY_PNG);
    free_image(SETTING_DISP_LAGU_PNG);
    free_image(SETTING_DISP_PLAY_PNG);
    free_image(SETTING_DISP_PHOTO_PNG);
    free_image(SETTING_DISP_MIAOSHU_PNG);
    free_image(SETTING_DISP_DATATIME_PNG);
    free_image(SETTING_DISP_SLEEP_PNG);
    free_image(SETTING_DISP_RENTI_PNG);
    free_image(SETTING_DISP_TZVOL_PNG);
#endif
}


albumScene::albumScene(lv_obj_t* parent)
{
    album_parent = parent;
	ui_image_decode();
#ifdef _UCHIP_T113
    read_int_type_param(PUBLIC_SCENE, BACKLIGHT, &brightNum);
    read_int_type_param(PUBLIC_SCENE, VOLUME, &volNum);
    read_int_type_param(SETTING_SCENE, SET_TP_VOL_MOD, &touchSounds);
    read_int_type_param(SETTING_SCENE, SET_BOY, &assistiveTouch);
    //read_int_type_param(PUBLIC_SCENE, LANGUAGE, &statue.language);
    read_int_type_param(SETTING_SCENE, SET_AUTOPLAY_MOD, &slideshow);
    read_int_type_param(SETTING_SCENE, SET_PHOTO_DISP_ORDER, &slideshowMode);
    read_int_type_param(SETTING_SCENE, SET_DESCRIBE, &caption);
    read_int_type_param(SETTING_SCENE, SET_BODY_INDUCTION, &montion);
    read_int_type_param(SETTING_SCENE, SET_MSG_VOL, &notSound);
#endif
    albumBri();
    albumVol();
    albumTpVol();
    albumQiu();
    lauAlbumList = new albumList(false,false,true,false,album_parent);
    lauAlbumList->iconLabel->set_main_bg_img_src(SETTING_DISP_LAGU_PNG);
    lauAlbumList->nameLabel->set_txt(STR_LANGUAGE);
    lauAlbumList->headLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
    lauAlbumList->headLabel->add_event_cb(albumScene_event_handler,LV_EVENT_CLICKED,this);
    albumplay();
    albumphoto();
    albumMiao();
    dateTimeAlbumList = new albumList(false,false,true,false,album_parent);
    dateTimeAlbumList->iconLabel->set_main_bg_img_src(SETTING_DISP_DATATIME_PNG);
    dateTimeAlbumList->nameLabel->set_txt(STR_DATETIME);
    dateTimeAlbumList->headLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
    dateTimeAlbumList->headLabel->add_event_cb(albumScene_event_handler,LV_EVENT_CLICKED,this);

    sleepAlbumList = new albumList(false,false,true,false,album_parent);
    sleepAlbumList->iconLabel->set_main_bg_img_src(SETTING_DISP_SLEEP_PNG);
    sleepAlbumList->nameLabel->set_txt(STR_SLEEP);
    sleepAlbumList->headLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
    sleepAlbumList->headLabel->add_event_cb(albumScene_event_handler,LV_EVENT_CLICKED,this);
    albumIRQ();
    albumsVol();
}
void albumScene::albumBri(void)
{
    if(briAlbumList ==NULL)
    {
        briAlbumList = new albumList(true,false,false,false,album_parent);
        briAlbumList->iconLabel->set_main_bg_img_src(SETTING_DISP_BRI_PNG);
        briAlbumList->nameLabel->set_txt(STR_BRIGHTNESS);
        briAlbumList->albumSlider->set_range(1, 100);
        briAlbumList->albumSlider->add_event_cb(albumScene_event_handler, LV_EVENT_VALUE_CHANGED,this);
    }
    briAlbumList->albumSlider->set_value(brightNum, LV_ANIM_ON);
}
void albumScene::albumVol(void)
{
    if(volAlbumList ==NULL)
    {
        volAlbumList = new albumList(true,false,false,false,album_parent);
        volAlbumList->iconLabel->set_main_bg_img_src(SETTING_DISP_VOL_PNG);
        volAlbumList->nameLabel->set_txt(STR_VOLUME);
        volAlbumList->albumSlider->set_range(0, 40);
        volAlbumList->albumSlider->add_event_cb(albumScene_event_handler, LV_EVENT_VALUE_CHANGED,this);
    }
    volAlbumList->albumSlider->set_value(volNum, LV_ANIM_ON);
}
void albumScene::albumTpVol(void)
{
#ifdef IMAGE_DECODE
    void *openPatch[2]={SETTING_DISP_CLOSE_PNG,SETTING_DISP_OPEN_PNG};
#endif
    if(tpVolAlbumList ==NULL)
    {
        tpVolAlbumList = new albumList(false,false,false,true,album_parent);
        tpVolAlbumList->iconLabel->set_main_bg_img_src(SETTING_DISP_TPVOL_PNG);
        tpVolAlbumList->nameLabel->set_txt(STR_TOUCHSOUNDS);
        tpVolAlbumList->headLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
        tpVolAlbumList->headLabel->add_event_cb(albumScene_event_handler,LV_EVENT_CLICKED,this);
    }
    tpVolAlbumList->switchLabel->set_main_bg_img_src(openPatch[touchSounds]);
}
void albumScene::albumQiu(void)
{
#ifdef IMAGE_DECODE
    void *openPatch[2]={SETTING_DISP_CLOSE_PNG,SETTING_DISP_OPEN_PNG};
#endif
    if(qiuAlbumList ==NULL)
    {
        qiuAlbumList = new albumList(false,false,false,true,album_parent);
        qiuAlbumList->iconLabel->set_main_bg_img_src(SETTING_DISP_BOY_PNG);
        qiuAlbumList->nameLabel->set_txt(STR_ASSISTIVETOUCH);
        qiuAlbumList->headLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
        qiuAlbumList->headLabel->add_event_cb(albumScene_event_handler,LV_EVENT_CLICKED,this);
    }
    qiuAlbumList->switchLabel->set_main_bg_img_src(openPatch[assistiveTouch]);
}
void albumScene::albumLau(void)
{
    if(lauList ==NULL)
    {
        lauList = new albumLanguage();
    }
}
void albumScene::albumLau_del(void)
{
    if(lauList !=NULL)
    {
        delete lauList;
        lauList = NULL;
    }
}
void albumScene::albumSlideshow(void)
{
    if(SlideshowList ==NULL)
    {
        SlideshowList = new albumSlideShow(slideshow);
        SlideshowList->SlideshowScreen->add_event_cb(albumSlideShow_event_handler,LV_EVENT_RELEASED,this);
        SlideshowList->CancelButton->add_event_cb(albumSlideShow_event_handler,LV_EVENT_RELEASED,this);
        SlideshowList->OKButton->add_event_cb(albumSlideShow_event_handler,LV_EVENT_RELEASED,this);
        SlideshowList->TimeList0->headLabel->add_event_cb(albumSlideShow_event_handler,LV_EVENT_CLICKED,this);
        SlideshowList->TimeList1->headLabel->add_event_cb(albumSlideShow_event_handler,LV_EVENT_CLICKED,this);
        SlideshowList->TimeList2->headLabel->add_event_cb(albumSlideShow_event_handler,LV_EVENT_CLICKED,this);
        SlideshowList->TimeList3->headLabel->add_event_cb(albumSlideShow_event_handler,LV_EVENT_CLICKED,this);
        SlideshowList->TimeList4->headLabel->add_event_cb(albumSlideShow_event_handler,LV_EVENT_CLICKED,this);
        SlideshowList->TimeList5->headLabel->add_event_cb(albumSlideShow_event_handler,LV_EVENT_CLICKED,this);
        SlideshowList->TimeList6->headLabel->add_event_cb(albumSlideShow_event_handler,LV_EVENT_CLICKED,this);
        SlideshowList->TimeList7->headLabel->add_event_cb(albumSlideShow_event_handler,LV_EVENT_CLICKED,this);
    }
}
void albumScene::albumSlideshow_del(void)
{
    if(SlideshowList !=NULL)
    {
        delete SlideshowList;
        SlideshowList = NULL;
    }
}
void albumScene::albumSlideshowMode(void)
{
    if(SlideshowList ==NULL)
    {
        SlideshowModeList = new albumSlideShowMode(slideshowMode);
        SlideshowModeList->SlideshowModeScreen->add_event_cb(albumSlideShowMode_event_handler,LV_EVENT_RELEASED,this);
        SlideshowModeList->CancelButton->add_event_cb(albumSlideShowMode_event_handler,LV_EVENT_RELEASED,this);
        SlideshowModeList->OKButton->add_event_cb(albumSlideShowMode_event_handler,LV_EVENT_RELEASED,this);
        SlideshowModeList->ModeList0->headLabel->add_event_cb(albumSlideShowMode_event_handler,LV_EVENT_CLICKED,this);
        SlideshowModeList->ModeList1->headLabel->add_event_cb(albumSlideShowMode_event_handler,LV_EVENT_CLICKED,this);
    }
}
void albumScene::albumSlideshowMode_del(void)
{
    if(SlideshowModeList !=NULL)
    {
        delete SlideshowModeList;
        SlideshowModeList = NULL;
    }
}
void albumScene::albumplay(void)
{
    if(playAlbumList ==NULL)
    {
        playAlbumList = new albumList(false,true,true,false,album_parent);
        playAlbumList->iconLabel->set_main_bg_img_src(SETTING_DISP_PLAY_PNG);
        playAlbumList->nameLabel->set_txt(STR_SLIDESHOW);
        playAlbumList->headLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
        playAlbumList->headLabel->add_event_cb(albumScene_event_handler,LV_EVENT_CLICKED,this);
    }
    playAlbumList->dataLabel->set_txt((char*)timeStr[slideshow]);
}
void albumScene::albumphoto(void)
{
    if(photoAlbumList ==NULL)
    {
        photoAlbumList = new albumList(false,true,true,false,album_parent);
        photoAlbumList->iconLabel->set_main_bg_img_src(SETTING_DISP_PHOTO_PNG);
        photoAlbumList->nameLabel->set_txt(STR_SLIDESHOWMODE);
        photoAlbumList->headLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
        photoAlbumList->headLabel->add_event_cb(albumScene_event_handler,LV_EVENT_CLICKED,this);
    }
    photoAlbumList->dataLabel->set_txt((char*)modeStr[slideshowMode]);
}
void albumScene::albumMiao(void)
{
#ifdef IMAGE_DECODE
    void *openPatch[2]={SETTING_DISP_CLOSE_PNG,SETTING_DISP_OPEN_PNG};
#endif
    if(miaoAlbumList ==NULL)
    {
        miaoAlbumList = new albumList(false,false,false,true,album_parent);
        miaoAlbumList->iconLabel->set_main_bg_img_src(SETTING_DISP_MIAOSHU_PNG);
        miaoAlbumList->nameLabel->set_txt(STR_CAPTION);
        miaoAlbumList->headLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
        miaoAlbumList->headLabel->add_event_cb(albumScene_event_handler,LV_EVENT_CLICKED,this);
    }
    miaoAlbumList->switchLabel->set_main_bg_img_src(openPatch[caption]);
}
void albumScene::albumIRQ(void)
{
    if(IRQAlbumList ==NULL)
    {
        IRQAlbumList = new albumList(false,true,true,false,album_parent);
        IRQAlbumList->iconLabel->set_main_bg_img_src(SETTING_DISP_RENTI_PNG);
        IRQAlbumList->nameLabel->set_txt(STR_MONTION);
        IRQAlbumList->headLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
        IRQAlbumList->headLabel->add_event_cb(albumScene_event_handler,LV_EVENT_CLICKED,this);
    }
    IRQAlbumList->dataLabel->set_txt((char*)motionStr[montion]);
}
void albumScene::albumMontions(void)
{
    if(albumMontionList ==NULL)
    {
        albumMontionList = new albumMontion(montion);
        albumMontionList->MontionScreen->add_event_cb(Montion_event_handler,LV_EVENT_RELEASED,this);
        albumMontionList->CancelButton->add_event_cb(Montion_event_handler,LV_EVENT_RELEASED,this);
        albumMontionList->OKButton->add_event_cb(Montion_event_handler,LV_EVENT_RELEASED,this);
        albumMontionList->TimeList0->headLabel->add_event_cb(Montion_event_handler,LV_EVENT_CLICKED,this);
        albumMontionList->TimeList1->headLabel->add_event_cb(Montion_event_handler,LV_EVENT_CLICKED,this);
        albumMontionList->TimeList2->headLabel->add_event_cb(Montion_event_handler,LV_EVENT_CLICKED,this);
        albumMontionList->TimeList3->headLabel->add_event_cb(Montion_event_handler,LV_EVENT_CLICKED,this);
        albumMontionList->TimeList4->headLabel->add_event_cb(Montion_event_handler,LV_EVENT_CLICKED,this);
    }
}
void albumScene::albumMontions_del(void)
{
    if(albumMontionList !=NULL)
    {
        delete albumMontionList;
        albumMontionList = NULL;
    }
}
void albumScene::albumsVol(void)
{
#ifdef IMAGE_DECODE
    void *openPatch[2]={SETTING_DISP_CLOSE_PNG,SETTING_DISP_OPEN_PNG};
#endif
    if(sVolAlbumList ==NULL)
    {
        sVolAlbumList = new albumList(false,false,false,true,album_parent);
        sVolAlbumList->iconLabel->set_main_bg_img_src(SETTING_DISP_TZVOL_PNG);
        sVolAlbumList->nameLabel->set_txt(STR_NOTIFICATION);
        sVolAlbumList->headLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
        sVolAlbumList->headLabel->add_event_cb(albumScene_event_handler,LV_EVENT_CLICKED,this);
    }
    sVolAlbumList->switchLabel->set_main_bg_img_src(openPatch[notSound]);
}
albumScene::~albumScene(void)
{
    albumLau_del();
    albumSlideshow_del();
    albumSlideshowMode_del();
    albumSlideshowMode_del();
    if(briAlbumList !=NULL)
    {
        delete briAlbumList;
        briAlbumList = NULL;
    }
    if(volAlbumList !=NULL)
    {
        delete volAlbumList;
        volAlbumList = NULL;
    }
    if(tpVolAlbumList !=NULL)
    {
        delete tpVolAlbumList;
        tpVolAlbumList = NULL;
    }
    if(qiuAlbumList !=NULL)
    {
        delete qiuAlbumList;
        qiuAlbumList = NULL;
    }
    if(lauAlbumList !=NULL)
    {
        delete lauAlbumList;
        lauAlbumList = NULL;
    }
    if(playAlbumList !=NULL)
    {
        delete playAlbumList;
        playAlbumList = NULL;
    }
    if(photoAlbumList !=NULL)
    {
        delete photoAlbumList;
        photoAlbumList = NULL;
    }
    if(miaoAlbumList !=NULL)
    {
        delete miaoAlbumList;
        miaoAlbumList = NULL;
    }
    if(dateTimeAlbumList !=NULL)
    {
        delete dateTimeAlbumList;
        dateTimeAlbumList = NULL;
    }
    if(sleepAlbumList !=NULL)
    {
        delete sleepAlbumList;
        sleepAlbumList = NULL;
    }
    if(IRQAlbumList !=NULL)
    {
        delete IRQAlbumList;
        IRQAlbumList = NULL;
    }
    if(sVolAlbumList !=NULL)
    {
        delete sVolAlbumList;
        sVolAlbumList = NULL;
    }
    ui_image_free();
}

void albumScene::albumScene_event_handler(lv_event_t *event)
{
    albumScene* opt = (albumScene*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
	int index =0;

    if((opt->briAlbumList !=NULL)&&(target ==opt->briAlbumList->albumSlider->myobj))
    {
        if(event->code== LV_EVENT_VALUE_CHANGED)
        {
            index = opt->briAlbumList->albumSlider->get_value();
			if(index !=opt->brightNum)
			{
				opt->brightNum =index;				
#ifdef _UCHIP_T113
				write_int_type_param(PUBLIC_SCENE, BACKLIGHT, opt->brightNum);
				va_display_lcd_set_backlight(opt->brightNum);
#endif
			}
        }
    }
    else if((opt->volAlbumList !=NULL)&&(target ==opt->volAlbumList->albumSlider->myobj))
    {
        if(event->code== LV_EVENT_VALUE_CHANGED)
        {
            index = opt->volAlbumList->albumSlider->get_value();
			if(index !=opt->volNum)
			{
				opt->volNum =index;			
#ifdef _UCHIP_T113
				write_int_type_param(PUBLIC_SCENE, VOLUME, opt->volNum);
				va_audio_set_volume(opt->volNum);
#endif
			}
        }
    }
    else if((opt->tpVolAlbumList !=NULL)&&(target ==opt->tpVolAlbumList->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            opt->touchSounds =!opt->touchSounds;
            opt->albumTpVol();
#ifdef _UCHIP_T113
			write_int_type_param(SETTING_SCENE, SET_TP_VOL_MOD, opt->touchSounds);
#endif	
        }
    }
    else if((opt->qiuAlbumList !=NULL)&&(target ==opt->qiuAlbumList->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
           opt->assistiveTouch =!opt->assistiveTouch;
           opt->albumQiu();
#ifdef _UCHIP_T113
			write_int_type_param(SETTING_SCENE, SET_BOY, opt->assistiveTouch);
#endif
        }
    }
    else if((opt->lauAlbumList !=NULL)&&(target ==opt->lauAlbumList->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
           opt->albumLau();
        }
    }
    else if((opt->playAlbumList !=NULL)&&(target ==opt->playAlbumList->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
           opt->albumSlideshow();
        }
    }
    else if((opt->photoAlbumList !=NULL)&&(target ==opt->photoAlbumList->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
           opt->albumSlideshowMode();
        }
    }
    else if((opt->miaoAlbumList !=NULL)&&(target ==opt->miaoAlbumList->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            opt->caption =!opt->caption;
            opt->albumMiao();
#ifdef _UCHIP_T113
			write_int_type_param(SETTING_SCENE, SET_DESCRIBE, opt->caption);
#endif
        }
    }
    else if((opt->dateTimeAlbumList !=NULL)&&(target ==opt->dateTimeAlbumList->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
           LV_LOG_USER("dateTimeAlbumList");
        }
    }
    else if((opt->sleepAlbumList !=NULL)&&(target ==opt->sleepAlbumList->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
           LV_LOG_USER("sleepAlbumList");
        }
    }
    else if((opt->IRQAlbumList !=NULL)&&(target ==opt->IRQAlbumList->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
           opt->albumMontions();
        }
    }
    else if((opt->sVolAlbumList !=NULL)&&(target ==opt->sVolAlbumList->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            opt->notSound =!opt->notSound;
            opt->albumsVol();
#ifdef _UCHIP_T113
			write_int_type_param(SETTING_SCENE, SET_MSG_VOL, opt->notSound);
#endif
        }
    }
}
void albumScene::albumSlideShow_event_handler(lv_event_t *event)
{
    albumScene* opt = (albumScene*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if((opt->SlideshowList !=NULL)&&(target ==opt->SlideshowList->SlideshowScreen->myobj))
    {
        if(event->code== LV_EVENT_RELEASED)
        {
            opt->albumSlideshow_del();
        }
    }
    else if((opt->SlideshowList !=NULL)&&(target ==opt->SlideshowList->CancelButton->myobj))
    {
        if(event->code== LV_EVENT_RELEASED)
        {
            opt->albumSlideshow_del();
        }
    }
    else if((opt->SlideshowList !=NULL)&&(target ==opt->SlideshowList->OKButton->myobj))
    {
        if(event->code== LV_EVENT_RELEASED)
        {
            opt->slideshow =opt->SlideshowList->get_SlideShow_cur();
            opt->albumSlideshow_del();
            opt->playAlbumList->dataLabel->set_txt((char*)timeStr[opt->slideshow]);
#ifdef _UCHIP_T113
            write_int_type_param(SETTING_SCENE, SET_AUTOPLAY_MOD, opt->slideshow);
#endif
        }
    }
    else if((opt->SlideshowList !=NULL)&&(target ==opt->SlideshowList->TimeList0->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            opt->SlideshowList->set_SlideShow_cur(0);
        }
    }
    else if((opt->SlideshowList !=NULL)&&(target ==opt->SlideshowList->TimeList1->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            opt->SlideshowList->set_SlideShow_cur(1);
        }
    }
    else if((opt->SlideshowList !=NULL)&&(target ==opt->SlideshowList->TimeList2->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            opt->SlideshowList->set_SlideShow_cur(2);
        }
    }
    else if((opt->SlideshowList !=NULL)&&(target ==opt->SlideshowList->TimeList3->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            opt->SlideshowList->set_SlideShow_cur(3);
        }
    }
    else if((opt->SlideshowList !=NULL)&&(target ==opt->SlideshowList->TimeList4->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            opt->SlideshowList->set_SlideShow_cur(4);
        }
    }
    else if((opt->SlideshowList !=NULL)&&(target ==opt->SlideshowList->TimeList5->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            opt->SlideshowList->set_SlideShow_cur(5);
        }
    }
    else if((opt->SlideshowList !=NULL)&&(target ==opt->SlideshowList->TimeList6->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            opt->SlideshowList->set_SlideShow_cur(6);
        }
    }
    else if((opt->SlideshowList !=NULL)&&(target ==opt->SlideshowList->TimeList7->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            opt->SlideshowList->set_SlideShow_cur(7);
        }
    }
}
void albumScene::albumSlideShowMode_event_handler(lv_event_t *event)
{
    albumScene* opt = (albumScene*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if((opt->SlideshowModeList !=NULL)&&(target ==opt->SlideshowModeList->SlideshowModeScreen->myobj))
    {
        if(event->code== LV_EVENT_RELEASED)
        {
            opt->albumSlideshowMode_del();
        }
    }
    else if((opt->SlideshowModeList !=NULL)&&(target ==opt->SlideshowModeList->CancelButton->myobj))
    {
        if(event->code== LV_EVENT_RELEASED)
        {
            opt->albumSlideshowMode_del();
        }
    }
    else if((opt->SlideshowModeList !=NULL)&&(target ==opt->SlideshowModeList->OKButton->myobj))
    {
        if(event->code== LV_EVENT_RELEASED)
        {
            opt->slideshowMode =opt->SlideshowModeList->get_SlideShowMode_cur();
            opt->albumSlideshowMode_del();
            opt->photoAlbumList->dataLabel->set_txt((char*)modeStr[opt->slideshowMode]);
#ifdef _UCHIP_T113
            write_int_type_param(SETTING_SCENE, SET_PHOTO_DISP_ORDER, opt->slideshowMode);
#endif
        }
    }
    else if((opt->SlideshowModeList !=NULL)&&(target ==opt->SlideshowModeList->ModeList0->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            opt->SlideshowModeList->set_SlideShowMode_cur(0);
        }
    }
    else if((opt->SlideshowModeList !=NULL)&&(target ==opt->SlideshowModeList->ModeList1->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            opt->SlideshowModeList->set_SlideShowMode_cur(1);
        }
    }
}
void albumScene::Montion_event_handler(lv_event_t *event)
{
    albumScene* opt = (albumScene*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if((opt->albumMontionList !=NULL)&&(target ==opt->albumMontionList->MontionScreen->myobj))
    {
        if(event->code== LV_EVENT_RELEASED)
        {
            opt->albumMontions_del();
        }
    }
    else if((opt->albumMontionList !=NULL)&&(target ==opt->albumMontionList->CancelButton->myobj))
    {
        if(event->code== LV_EVENT_RELEASED)
        {
            opt->albumMontions_del();
        }
    }
    else if((opt->albumMontionList !=NULL)&&(target ==opt->albumMontionList->OKButton->myobj))
    {
        if(event->code== LV_EVENT_RELEASED)
        {
            opt->montion =opt->albumMontionList->get_Montion_cur();
            opt->albumMontions_del();
            opt->IRQAlbumList->dataLabel->set_txt((char*)motionStr[opt->montion]);
#ifdef _UCHIP_T113
            write_int_type_param(SETTING_SCENE, SET_BODY_INDUCTION, opt->montion);
#endif
        }
    }
    else if((opt->albumMontionList !=NULL)&&(target ==opt->albumMontionList->TimeList0->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            opt->albumMontionList->set_Montion_cur(0);
        }
    }
    else if((opt->albumMontionList !=NULL)&&(target ==opt->albumMontionList->TimeList1->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            opt->albumMontionList->set_Montion_cur(1);
        }
    }
    else if((opt->albumMontionList !=NULL)&&(target ==opt->albumMontionList->TimeList2->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            opt->albumMontionList->set_Montion_cur(2);
        }
    }
    else if((opt->albumMontionList !=NULL)&&(target ==opt->albumMontionList->TimeList3->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            opt->albumMontionList->set_Montion_cur(3);
        }
    }
    else if((opt->albumMontionList !=NULL)&&(target ==opt->albumMontionList->TimeList4->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            opt->albumMontionList->set_Montion_cur(4);
        }
    }
}
