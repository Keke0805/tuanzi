#include "lvcpp_label.h"

LvcppLabel::LvcppLabel(lv_obj_t* parent)
{
    myobj = lv_label_create(parent);
    fontsize = nullptr;
}

LvcppLabel::~LvcppLabel(void)
{
    if(fontsize != nullptr)
    {
        delete fontsize;
        fontsize = NULL;
    }
}

int LvcppLabel::txt_font_size(uint16_t weight, uint16_t font_type)
{
    (void) font_type;
    //change_font_size(weight,font_type);
    if(fontsize == nullptr)
    {
        fontsize = new LvcppFreeTypeFont(weight,font_type);
    }
    else
    {
        fontsize->resize(weight,font_type);
    }

    lv_obj_set_style_text_font(myobj, fontsize->font(), LV_PART_MAIN);

    return 0;
}

int LvcppLabel::txt_long_mode(lv_label_long_mode_t mode)
{
    lv_label_set_long_mode(myobj,mode);
    return 0;
}

int LvcppLabel::txt_color(lv_color_t value, lv_style_selector_t selector)
{
    lv_obj_set_style_text_color(myobj,value,selector);

    return 0;
}

int LvcppLabel::txt_recolor(bool en)
{
    lv_label_set_recolor(myobj,en);

    return 0;
}

int LvcppLabel::set_txt(const char *str)
{

    lv_label_set_text(myobj, str);
   return 0;
}

int LvcppLabel::txt_center(void)
{
    lv_obj_center(myobj);

    return 0;
}

int LvcppLabel::txt_align(lv_text_align_t align)
{
    lv_obj_set_style_text_align(myobj,align,LV_PART_MAIN);
    return 0;
}

const char* LvcppLabel::get_txt(void)
{
    return lv_label_get_text(myobj);
}

lv_color_t LvcppLabel::get_txt_color(void)
{
    return lv_obj_get_style_text_color(myobj,LV_PART_MAIN);
}

lv_text_align_t LvcppLabel::get_txt_align(void)
{

    return lv_obj_get_style_text_align(myobj,LV_PART_MAIN);
}

int LvcppLabel::get_txt_long_mode(void)
{
    return lv_label_get_long_mode(myobj);
}
