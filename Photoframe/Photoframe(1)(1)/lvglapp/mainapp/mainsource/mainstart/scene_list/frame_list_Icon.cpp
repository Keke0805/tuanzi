#include "frame_list_icon.h"
#include  "lvgl/src/extra/lv_extra.h"
#include  "../include/str_config.h"
#include  "../include/ui_config.h"

frameListIcon::frameListIcon(lv_obj_t* parent,framelist_btn_t* btn_info,framelist_txt_t* txt_info,framelist_icon_t* icon_info)
{
    btn = new LvcppButton(parent);
    btn->set_size(btn_info->w,btn_info->h);
    btn->align(btn_info->align,btn_info->x,btn_info->y);
    btn->set_main_pad_all(0);
    btn->set_main_pad_row(0);
    btn->set_main_pad_column(0);
    btn->set_main_border_width(0);
    btn->set_main_radius(0);
    btn->set_main_bg_color(lv_color_hex(btn_info->bg_color),LV_OPA_100);
    btn->txt_size(txt_info->w, txt_info->h, LV_LABEL_LONG_WRAP);
	btn->set_style_text_font(txt_info->font, LV_PART_MAIN);
    btn->txt_align(txt_info->align,txt_info->x,txt_info->y);
    btn->txt_color(lv_color_hex(txt_info->txt_color));
    mainframe = btn->myobj;

    if(icon_info->showStatus ==true)
    {
        icon = new LvcppImageButton(mainframe);
        icon->set_size(icon_info->w,icon_info->h);
        icon->set_main_pad_all(0);
        icon->set_main_pad_row(0);
        icon->set_main_pad_column(0);
        icon->set_main_border_width(0);
        icon->set_main_radius(0);
        icon->align(icon_info->align,icon_info->x,icon_info->y);
        icon->add_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
        icon->set_main_bg_opa(LV_OPA_TRANSP);
        icon->set_main_bg_img_src(icon_info->iconPatch);
    }
    iconLine = new LvcppImageButton(mainframe);
    iconLine->set_size(btn_info->w,btn_info->line_h);
    iconLine->set_main_bg_color(lv_color_white(),LV_OPA_100);
    iconLine->set_main_pad_all(0);
    iconLine->set_main_pad_row(0);
    iconLine->set_main_pad_column(0);
    iconLine->set_main_border_width(0);
    iconLine->set_main_radius(0);
    iconLine->align(LV_ALIGN_TOP_LEFT,0,(btn_info->h-btn_info->line_h));
    iconLine->add_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
}

frameListIcon::~frameListIcon(void)
{
    if(icon != NULL)
    {
        delete icon;
        icon = NULL;
    }
    if(iconLine != NULL)
    {
        delete iconLine;
        iconLine = NULL;
    }
    if(btn != NULL)
    {
        delete btn;
        btn = NULL;
    }
}

void frameListIcon::set_IconName(char * iconname)
{
    btn->add_txt(iconname);
}

void frameListIcon::set_IconPtch(const void *iconPatch)
{
    icon->set_main_bg_img_src(iconPatch);
}
