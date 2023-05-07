#include "frame_list.h"

frameList::frameList(lv_obj_t* parent,frameList_btn_t* btn_info,frameList_txt_t* txt_info,frameList_iconLine_t* iconLine_info)
{
    btn = new LvcppButton(parent);
    btn->set_size(btn_info->w,btn_info->h);
    btn->align(btn_info->align,btn_info->x,btn_info->y);
    btn->set_main_radius(8);
    btn->set_main_pad_all(0);
    btn->set_main_pad_row(3);
    btn->set_main_bg_color(lv_color_hex(btn_info->bg_color),LV_PART_MAIN);
    btn->set_main_bg_opa(btn_info->value);
    btn->txt_size(txt_info->w, txt_info->h, LV_LABEL_LONG_WRAP);
    btn->txt_font_size(txt_info->font_size, FT_FONT_STYLE_NORMAL);
    btn->txt_align(txt_info->align,txt_info->x,txt_info->y);
    mainframe = btn->myobj;

    iconLine = new LvcppImageButton(mainframe);
    iconLine->set_size(iconLine_info->w,iconLine_info->h);
    iconLine->set_main_radius(0);
    iconLine->align(iconLine_info->align,iconLine_info->x,iconLine_info->y);
    iconLine->add_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
}

frameList::~frameList(void)
{
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

int frameList::update_frameList(char* name, int str_color,char* iconLinePatch)
{
    btn->txt_color(lv_color_hex(str_color));
    btn->add_txt(name);
    btn->txt_color(lv_color_white());
    iconLine->set_main_bg_img_src(iconLinePatch);
    return 0;
}
