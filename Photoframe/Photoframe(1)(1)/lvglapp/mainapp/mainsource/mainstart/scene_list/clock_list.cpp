#include "clock_list.h"

clockList::clockList(lv_obj_t* parent,void *patch)
{
    btn = new LvcppButton(parent);
    btn->set_size(284,284);
    btn->align(LV_ALIGN_TOP_LEFT,0,0);
    btn->set_main_radius(200);
    btn->set_main_pad_all(0);
    btn->set_main_pad_row(0);
    btn->set_main_bg_color(lv_color_hex(0x0a85a6), LV_OPA_100);
    btn->set_main_bg_img_src(patch);
}
clockList::~clockList(void)
{
    if(btn != NULL)
    {
        delete btn;
        btn = NULL;
    }
}
