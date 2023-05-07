#include "alarm_list.h"
#include  "mainstart/include/ui_config.h"
#include  "mainstart/include/str_config.h"
#include  "common/common.h"


void Alarmlist::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    ALARM_SET_PNG=(void*)parse_image_from_file(ALARM_SET_PNG_PATH);
    ALARM_DEL_PNG=(void*)parse_image_from_file(ALARM_DEL_PNG_PATH);
#endif
}

void Alarmlist::ui_image_free(void)
{
#ifdef IMAGE_DECODE
    free_image(ALARM_SET_PNG);
    free_image(ALARM_DEL_PNG);
#endif
}
Alarmlist::Alarmlist(lv_obj_t* parent)
{
	ui_image_decode();
    IconBg = new LvcppLabel(parent);
    IconBg->set_size(590,110);
    IconBg->align(LV_ALIGN_TOP_LEFT, 0, 0);
    IconBg->set_main_bg_color(lv_color_hex(0x546fb4),LV_OPA_0);
    IconBg->set_txt("");
    mainframe = IconBg->myobj;

    TimeStr = new LvcppLabel(mainframe);
    TimeStr->set_size(100,44);
    TimeStr->align(LV_ALIGN_LEFT_MID, 15, 0);
    TimeStr->set_main_bg_opa(LV_OPA_0);
    TimeStr->txt_font_size(38, FT_FONT_STYLE_NORMAL);
    TimeStr->txt_align(LV_TEXT_ALIGN_LEFT);
    TimeStr->txt_color(lv_color_white(),LV_PART_MAIN);
    TimeStr->set_txt("");

    IconName = new LvcppLabel(mainframe);
    IconName->set_size(290,32);
    IconName->align(LV_ALIGN_TOP_LEFT, 130, 15);
    IconName->set_main_bg_opa(LV_OPA_0);
    IconName->txt_font_size(24, FT_FONT_STYLE_NORMAL);
    IconName->txt_align(LV_TEXT_ALIGN_LEFT);
    IconName->txt_long_mode(LV_LABEL_LONG_WRAP);
    IconName->txt_color(lv_color_white(),LV_PART_MAIN);
    IconName->set_txt("");

    IconType = new LvcppLabel(mainframe);
    IconType->set_size(290,32);
    IconType->align(LV_ALIGN_LEFT_MID, 130, 15);
    IconType->set_main_bg_opa(LV_OPA_0);
    IconType->txt_font_size(24, FT_FONT_STYLE_NORMAL);
    IconType->txt_align(LV_TEXT_ALIGN_LEFT);
    IconType->txt_long_mode(LV_LABEL_LONG_WRAP);
    IconType->txt_color(lv_color_white(),LV_PART_MAIN);
    IconType->set_txt("");

    IconSet = new LvcppButton(mainframe);
    IconSet->set_size(40,40);
    IconSet->align(LV_ALIGN_RIGHT_MID, -100, 0);
    IconSet->set_main_bg_color(lv_color_hex(0x00a7d4),LV_OPA_100);
    IconSet->set_main_bg_img_src(ALARM_SET_PNG);
    IconSet->set_main_radius(20);
    IconSet->show(false);

    IconDel = new LvcppButton(mainframe);
    IconDel->set_size(40,40);
    IconDel->align(LV_ALIGN_RIGHT_MID, -25, 0);
    IconDel->set_main_bg_color(lv_color_hex(0x00a7d4),LV_OPA_100);
    IconDel->set_main_bg_img_src(ALARM_DEL_PNG);
    IconDel->set_main_radius(20);
    IconDel->show(false);

    IconClose = new LvcppLabel(mainframe);
    IconClose->set_size(80,40);
    IconClose->set_main_radius(40);
    IconClose->align(LV_ALIGN_RIGHT_MID, -20, 0);
    IconClose->set_main_bg_color(lv_color_hex(0x5c5c5c),LV_OPA_100);
    IconClose->set_txt("");
    IconClose->add_flag(LV_OBJ_FLAG_CLICKABLE);

    StatusClose = new LvcppLabel(IconClose->myobj);
    StatusClose->set_size(40,40);
    StatusClose->set_main_radius(40);
    StatusClose->align(LV_ALIGN_LEFT_MID, 0, 0);
    StatusClose->set_main_bg_color(lv_color_white(),LV_OPA_100);
    StatusClose->set_txt("");

    IconLine = new LvcppLabel(mainframe);
    IconLine->set_size(590,1);
    IconLine->align(LV_ALIGN_BOTTOM_MID, 0, 0);
    IconLine->set_main_bg_color(lv_color_hex(0xbbbbbb),LV_OPA_100);
    IconLine->set_txt("");
}

Alarmlist::~Alarmlist(void)
{
    if(StatusClose != NULL)
    {
        delete StatusClose;
        StatusClose = NULL;
    }
    if(IconClose != NULL)
    {
        delete IconClose;
        IconClose = NULL;
    }
    if(IconLine != NULL)
    {
        delete IconLine;
        IconLine = NULL;
    }
    if(IconDel != NULL)
    {
        delete IconDel;
        IconDel = NULL;
    }
    if(IconSet != NULL)
    {
        delete IconSet;
        IconSet = NULL;
    }
    if(IconName != NULL)
    {
        delete IconName;
        IconName = NULL;
    }
    if(IconType != NULL)
    {
        delete IconType;
        IconType = NULL;
    }
    if(TimeStr != NULL)
    {
        delete TimeStr;
        TimeStr = NULL;
    }
    if(IconBg != NULL)
    {
        delete IconBg;
        IconBg = NULL;
    }
	ui_image_free();
}

