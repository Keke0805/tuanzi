#include "lvcpp_dropdown.h"

LvcppDropdown::LvcppDropdown(lv_obj_t* parent)
{
    myobj = lv_dropdown_create(parent);
    label = get_list();
    fontsize = nullptr;
}

LvcppDropdown::~LvcppDropdown(void)
{

}

//set
int LvcppDropdown::set_text(const char * txt)
{
    lv_dropdown_set_text(myobj, txt);
    return 0;
}

int LvcppDropdown::set_options(const char * options)
{
    lv_dropdown_set_options(myobj, options);
    return 0;
}

int LvcppDropdown::set_options_static(const char * options)
{
    lv_dropdown_set_options_static(myobj, options);
    return 0;
}

int LvcppDropdown::add_option(const char * option, uint32_t pos)
{
    lv_dropdown_add_option(myobj, option, pos);
    return 0;
}

int LvcppDropdown::clear_options(void)
{
    lv_dropdown_clear_options(myobj);
    return 0;
}

int LvcppDropdown::set_selected(uint16_t sel_opt)
{
    lv_dropdown_set_selected(myobj, sel_opt);
    return 0;
}

int LvcppDropdown::set_dir(lv_dir_t dir)
{
    lv_dropdown_set_dir(myobj, dir);
    return 0;
}

int LvcppDropdown::set_symbol(const void * symbol)
{
    lv_dropdown_set_symbol(myobj, symbol);
    return 0;
}

int LvcppDropdown::set_selected_highlight(bool en)
{
    lv_dropdown_set_selected_highlight(myobj, en);
    return 0;
}

int LvcppDropdown::txt_font_size(uint16_t weight, uint16_t font_type)
{
    (void) font_type;

    if(fontsize == nullptr)
    {
       fontsize = new LvcppFreeTypeFont(weight,font_type);
    }
    else
    {
        fontsize->resize(weight,font_type);
    }
    if(label != nullptr)
    {
        lv_obj_set_style_text_font(label, fontsize->font(), LV_PART_MAIN);
    }
    else
    {
        label = get_list();
        lv_obj_set_style_text_font(label, fontsize->font(), LV_PART_MAIN);
    }
    return 0;
}

int LvcppDropdown::txt_color(lv_color_t value)
{
    if(label != nullptr)
    {
        lv_obj_set_style_text_color(label, value, LV_PART_MAIN);
        lv_obj_get_style_color_filter_dsc(label,LV_PART_MAIN);
    }
    else
    {
        label = get_list();
        lv_obj_set_style_text_color(label, value, LV_PART_MAIN);
        lv_obj_get_style_color_filter_dsc(label,LV_PART_MAIN);
    }
    return 0;
}


int LvcppDropdown::txt_long_mode(lv_label_long_mode_t mode)
{
    if(label != nullptr)
    {
        lv_label_set_long_mode(label,mode);
    }
    else
    {
        label = get_list();
        lv_label_set_long_mode(label,mode);
    }
    return 0;
}

int LvcppDropdown::txt_align(lv_text_align_t align)
{
    if(label != nullptr)
    {
        lv_obj_set_style_text_align(label,align,LV_PART_MAIN);
    }
    else
    {
        label = get_list();
        lv_obj_set_style_text_align(label,align,LV_PART_MAIN);
    }
    return 0;
}


//get
lv_obj_t * LvcppDropdown::get_list(void)
{
    return lv_dropdown_get_list(myobj);
}

const char * LvcppDropdown::get_text(void)
{

    return lv_dropdown_get_text(myobj);
}

const char * LvcppDropdown::get_options(void)
{

    return lv_dropdown_get_options(myobj);
}

int LvcppDropdown::get_selected(void)
{

    return lv_dropdown_get_selected(myobj);
}

int LvcppDropdown::get_option_cnt(void)
{

    return lv_dropdown_get_option_cnt(myobj);
}

int LvcppDropdown::get_selected_str(char * buf, uint32_t buf_size)
{
    lv_dropdown_get_selected_str(myobj, buf, buf_size);
    return 0;
}

const char * LvcppDropdown::get_symbol(void)
{

    return lv_dropdown_get_symbol(myobj);
}

bool LvcppDropdown::get_selected_highlight(void)
{

    return lv_dropdown_get_selected_highlight(myobj);
}

int LvcppDropdown::get_dir(void)
{

    return lv_dropdown_get_dir(myobj);
}

lv_color_t LvcppDropdown::get_txt_color(void)
{
    if(label != nullptr)
    {
        return lv_obj_get_style_text_color(label,LV_PART_MAIN);
    }
    else
    {
        return lv_color_black();
    }
}

lv_text_align_t LvcppDropdown::get_txt_align(void)
{
    if(label != nullptr)
    {
        return lv_obj_get_style_text_align(label,LV_PART_MAIN);
    }
    else
    {
        return LV_TEXT_ALIGN_AUTO;
    }
}

int LvcppDropdown::get_txt_long_mode(void)
{
    if(label != nullptr)
    {
        lv_obj_set_size(label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        return lv_label_get_long_mode(label);
    }
    else
    {
        return LV_LABEL_LONG_WRAP;
    }
}
