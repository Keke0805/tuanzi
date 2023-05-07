#include "main_icon_list.h"

mainIconList::mainIconList(lv_obj_t* parent)
{
    frame = new LvcppButton(parent);
    frame->set_size(370,85);
    frame->set_style_radius(8,0);
    frame->set_style_pad_all(0,0);
    frame->set_style_pad_row(0,0);
    frame->set_style_radius(0,0);
    frame->set_main_bg_color(lv_color_hex(0x0a85a6),LV_OPA_100);
    mainframe = frame->myobj;

    icon = new LvcppLabel(mainframe);
    icon->set_size(85,85);
    icon->set_style_radius(0,0);
    icon->align(LV_ALIGN_TOP_LEFT,0,0);
    icon->set_main_bg_opa(LV_OPA_0);
    icon->set_txt("");

    item = new LvcppLabel(mainframe);
    item->set_size(285,40);
    item->align_to(icon->myobj,LV_ALIGN_OUT_RIGHT_MID,0,0);
    item->set_main_radius(0);
    item->set_main_pad_all(0);
    item->set_main_pad_row(0);
    item->set_main_border_width(0);
    item->txt_color(lv_color_hex(0xffffff),LV_PART_MAIN);
    item->set_main_bg_opa(LV_OPA_0);
    item->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    item->txt_align(LV_TEXT_ALIGN_LEFT);

    line = new LvcppLabel(mainframe);
    line->set_size(370,1);
    line->align(LV_ALIGN_BOTTOM_MID,0,0);
    line->set_main_bg_color(lv_color_hex(0xc0c0c0),LV_OPA_100);
    line->set_txt("");
}
mainIconList::~mainIconList(void)
{
    if(line != NULL)
    {
        delete line;
        line = NULL;
    }

    if(item != NULL)
    {
        delete item;
        item = NULL;
    }
    if(icon != NULL)
    {
        delete icon;
        icon = NULL;
    }
    if(frame != NULL)
    {
        delete frame;
        frame = NULL;
    }
}

void mainIconList::updata_icon_name(void *path, char *str_name)
{
    if(icon !=NULL)
        icon->set_main_bg_img_src(path);
    if(item !=NULL)
        item->set_txt(str_name);
}
