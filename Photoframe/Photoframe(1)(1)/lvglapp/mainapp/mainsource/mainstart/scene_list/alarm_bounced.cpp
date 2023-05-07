#include "alarm_bounced.h"
#include  "../appmsg/appmsg.h"
#include  "../include/configCustom.h"
#include  "mainstart/include/ui_config.h"
#include  "mainstart/include/str_config.h"
#include  "common/common.h"

#ifndef IMAGE_DECODE
static const void *iconPatch[4]={ALARM_SLIDING0_PNG,ALARM_SLIDING1_PNG,ALARM_SLIDING2_PNG,ALARM_SLIDING3_PNG};
#endif

void Alarmbounced::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    ALARM_SLIDING_PNG=(void*)parse_image_from_file(ALARM_SLIDING_PNG_PATH);
    ALARM_SLIDING0_PNG=(void*)parse_image_from_file(ALARM_SLIDING0_PNG_PATH);
    ALARM_SLIDING1_PNG=(void*)parse_image_from_file(ALARM_SLIDING1_PNG_PATH);
    ALARM_SLIDING2_PNG=(void*)parse_image_from_file(ALARM_SLIDING2_PNG_PATH);
    ALARM_SLIDING3_PNG=(void*)parse_image_from_file(ALARM_SLIDING3_PNG_PATH);
#endif

}
void Alarmbounced::ui_image_free(void)
{
#ifdef IMAGE_DECODE
    free_image(ALARM_SLIDING_PNG);
    free_image(ALARM_SLIDING0_PNG);
    free_image(ALARM_SLIDING1_PNG);
    free_image(ALARM_SLIDING2_PNG);
    free_image(ALARM_SLIDING3_PNG);
#endif
}
Alarmbounced::Alarmbounced(void)
{
	LV_LOG_USER("%%%%%%%%%%%%Alarmbounced%%%%%%%%%%%%%");
    ui_image_decode();
#ifdef IMAGE_DECODE
    void *iconPatch[4]={ALARM_SLIDING0_PNG,ALARM_SLIDING1_PNG,ALARM_SLIDING2_PNG,ALARM_SLIDING3_PNG};
#endif
    frame = new LvcppScreen(lv_layer_top());
    frame->set_size(LV_HOR_RES_MAX,LV_VER_RES_MAX);
    frame->set_main_bg_color(lv_color_hex(0x0a85a6),LV_OPA_100);

    alarmScene = new LvcppList(frame->myobj);
    alarmScene->set_size(LV_HOR_RES_MAX,LV_VER_RES_MAX);
    alarmScene->center_align();
    alarmScene->set_main_bg_color(lv_color_hex(0x0a85a6),LV_OPA_100);
    alarmScene->set_flex_flow(LV_FLEX_FLOW_ROW);
    alarmScene->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    alarmScene->set_scrollbar_snap_x(LV_SCROLL_SNAP_START);
    alarmScene->set_main_pad_all(0);
    alarmScene->set_main_pad_row(0);
    alarmScene->set_main_border_width(0);
    alarmScene->set_main_radius(0);
    alarmScene->add_event_cb(scene_event_handler,LV_EVENT_SCROLL_END,this);
	LV_LOG_USER("%%%%%%%%%%%%Alarmbounced%%%%%%%%%%%%%");
    SceneFirst = new LvcppLabel(alarmScene->myobj);
    SceneFirst->set_size(LV_HOR_RES_MAX,LV_VER_RES_MAX);
    SceneFirst->center_align();
    SceneFirst->set_main_bg_opa(LV_OPA_0);
    SceneFirst->set_txt("");

    SceneSecond = new LvcppLabel(alarmScene->myobj);
    SceneSecond->set_size(LV_HOR_RES_MAX,LV_VER_RES_MAX);
    SceneSecond->center_align();
    SceneSecond->set_main_bg_opa(LV_OPA_0);
    SceneSecond->set_txt("");
	LV_LOG_USER("%%%%%%%%%%%%Alarmbounced%%%%%%%%%%%%%");
    BgSecond = new LvcppImageButton(SceneSecond->myobj);
    BgSecond->set_size(196,230);
    BgSecond->set_main_bg_img_src(ALARM_SLIDING_PNG);
    BgSecond->center_align();

    LineSecond = new LvcppImageButton(SceneSecond->myobj);
    LineSecond->set_size(72,40);
    LineSecond->set_main_radius(0);
    LineSecond->add_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
    LineSecond->set_main_bg_img_src(iconPatch[lineNum]);
    LineSecond->align(LV_ALIGN_CENTER,0,150);

    NameSecond = new LvcppLabel(SceneSecond->myobj);
    NameSecond->set_size(1280,40);
    NameSecond->align(LV_ALIGN_CENTER, 0, 190);
    NameSecond->txt_font_size(34, FT_FONT_STYLE_BOLD);
    NameSecond->txt_align(LV_TEXT_ALIGN_CENTER);
    NameSecond->txt_color(lv_color_white(),LV_PART_MAIN);
    alarmScene->set_scroll_to(LV_HOR_RES_MAX, 0, LV_ANIM_OFF);
    NameSecond->set_txt(STR_ALARM_BELL);
    alarmScene->set_scroll_to(LV_HOR_RES_MAX, 0, LV_ANIM_OFF);
	LV_LOG_USER("%%%%%%%%%%%%Alarmbounced%%%%%%%%%%%%%");
    sceneTime = startTimer(250, this);
}
Alarmbounced::~Alarmbounced(void)
{ 
	StopTimerCB();
	LV_LOG_USER("%%%%%%%%%%%%%%%%%%%%%%%%%");
    if(NameSecond !=NULL)
    {
        delete NameSecond;
        NameSecond =NULL;
    }
	LV_LOG_USER("%%%%%%%%%%%%%%%%%%%%%%%%%");
    if(LineSecond !=NULL)
    {
        delete LineSecond;
        LineSecond =NULL;
    }
	LV_LOG_USER("%%%%%%%%%%%%%%%%%%%%%%%%%");
    if(BgSecond !=NULL)
    {
        delete BgSecond;
        BgSecond =NULL;
    }
	LV_LOG_USER("%%%%%%%%%%%%%%%%%%%%%%%%%");
    if(SceneFirst !=NULL)
    {
        delete SceneFirst;
        SceneFirst =NULL;
    }
	LV_LOG_USER("%%%%%%%%%%%%%%%%%%%%%%%%%");
    if(SceneSecond !=NULL)
    {
        delete SceneSecond;
        SceneSecond =NULL;
    }
	LV_LOG_USER("%%%%%%%%%%%%%%%%%%%%%%%%%");
    if(alarmScene !=NULL)
    {
        delete alarmScene;
        alarmScene =NULL;
    }
	LV_LOG_USER("%%%%%%%%%%%%%%%%%%%%%%%%%");
    if(frame !=NULL)
    {
        delete frame;
        frame =NULL;
        lv_obj_clear_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_bg_opa(lv_layer_top(), LV_OPA_TRANSP, 0);
    }
	LV_LOG_USER("%%%%%%%%%%%%%%%%%%%%%%%%%");
    ui_image_free();
	LV_LOG_USER("%%%%%%%%%%%%%%%%%%%%%%%%%");
}
void Alarmbounced::TimerCB(lv_timer_t * tmr)
{
#ifdef IMAGE_DECODE
    void *iconPatch[4]={ALARM_SLIDING0_PNG,ALARM_SLIDING1_PNG,ALARM_SLIDING2_PNG,ALARM_SLIDING3_PNG};
#endif
    LV_UNUSED(tmr);
	if(TimerStatus)
		return;
	
    lineNum ++;
    if(lineNum >3)
        lineNum =0;
    if(LineSecond !=NULL)
        LineSecond->set_main_bg_img_src(iconPatch[lineNum]);
	timeNum ++;
	if(timeNum >235)
	{
		timeNum =0;
		exit_scene();
	}
}
void Alarmbounced::StopTimerCB(void)
{
	pause(sceneTime);
}
void Alarmbounced::exit_scene(void)
{
	msg_apps_t msg;
	
	TimerStatus =true;
    memset(&msg,0,sizeof(msg));
    msg.type = UI_ALARM;
    msg.mode = VPLAY_STOP_CMD;
    SSTAR_SendAsyncMsg(APP_NAME_UI,&msg);
}
void Alarmbounced::scene_event_handler(lv_event_t *event)
{
    Alarmbounced* opt = (Alarmbounced*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
	
    if((opt->alarmScene !=NULL)&&(target==opt->alarmScene->myobj))
    {
        if(opt->alarmScene->get_scroll_x() ==0)
        {
        	opt->exit_scene();
        }
    }
}

