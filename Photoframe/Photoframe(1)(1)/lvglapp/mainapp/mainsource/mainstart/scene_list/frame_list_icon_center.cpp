#include "frame_list_icon_center.h"
#include  "lvgl/src/extra/lv_extra.h"
#include  "../include/str_config.h"
#include  "../include/ui_config.h"

frameListIconCenter::frameListIconCenter(lv_obj_t* parent,frameiconlist_btn_t* btn_info,int txt_color,frameiconlist_icon_t* icon_info)
{
    btn = new LvcppButton(parent);
    btn->set_size(btn_info->w,btn_info->h);
    btn->align(btn_info->align,btn_info->x,btn_info->y);
    btn->set_main_radius(0);
    btn->set_main_pad_all(0);
    btn->set_main_pad_row(0);
    btn->set_main_bg_color(lv_color_hex(btn_info->bg_color),LV_PART_MAIN);
    btn->set_main_bg_opa(btn_info->value);

    btn_child = new LvcppButton(btn->myobj);
    btn_child->set_size(btn_info->w,btn_info->h);
    btn_child->center_align();
    btn_child->set_main_radius(0);
    btn_child->set_main_pad_all(0);
    btn_child->set_main_pad_row(0);
    btn_child->set_main_bg_color(lv_color_hex(btn_info->bg_color),LV_PART_MAIN);
    btn_child->set_main_bg_opa(LV_OPA_0);
    btn_child->txt_long_mode(LV_LABEL_LONG_WRAP);
    btn_child->txt_align(LV_ALIGN_CENTER,icon_info->w*3/5,0);
    btn_child->txt_color(lv_color_hex(txt_color));
    btn_child->add_flag(LV_OBJ_FLAG_EVENT_BUBBLE);

    mainframe = btn_child->myobj;
    icon = new LvcppImageButton(mainframe);
    icon->set_size(icon_info->w,icon_info->h);
    icon->set_main_radius(0);
    icon->add_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
}

frameListIconCenter::~frameListIconCenter(void)
{
    if(icon != NULL)
    {
        delete icon;
        icon = NULL;
    }
	if(btn_child != NULL)
    {
        delete btn_child;
        btn_child = NULL;
    }
    if(btn != NULL)
    {
        delete btn;
        btn = NULL;
    }
}
void frameListIconCenter::set_IconName(void)
{
    btn_child->add_txt(IconName);
}

int frameListIconCenter::set_IconPtch( int icon_w, void * iconPatch)
{
    icon->set_main_bg_img_src(iconPatch);
    icon->align_to(btn_child->get_label(),LV_ALIGN_OUT_LEFT_MID,-icon_w*2/5,0);
    return 0;
}
