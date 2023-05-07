#include "medialist.h"

medialist::medialist(lv_obj_t* praent)
{
    me_screen = new LvcppScreen(praent);
    me_screen->set_size(478,80);
    me_screen->set_main_radius(0);
    me_screen->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_0);
    me_parent = me_screen->get_screen();
    me_screen->set_main_pad_all(0);
    initial();
}

medialist::~medialist()
{
    if(txt_list != nullptr)
    {
        delete txt_list;
        txt_list = nullptr;
    }
}


void medialist::initial(void)
{
    myfont = new LvcppFreeTypeFont(24,0);
    txt_list = new LvcppButton(me_parent);
    txt_list->set_size(478,80);
    txt_list->txt_align(LV_TEXT_ALIGN_CENTER,0,0);
    txt_list->txt_center();
    txt_list->txt_color(lv_color_hex(0xffffff));
    txt_list->txt_font_size(40,0);
    txt_list->set_main_pad_all(0);
    txt_list->set_main_border(1,lv_color_hex(0xffffff),LV_OPA_60);
    txt_list->center_align();
    txt_list->set_main_bg_color(lv_color_hex(0xffffff),LV_OPA_0);
}

void medialist::set_txt(const char * str)
{
    txt_list->add_txt(str);
    txt_list->set_style_text_font(myfont->font(),0);
}
