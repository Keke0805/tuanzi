#include "lvcpp_textarea.h"

LvcppTextArea::LvcppTextArea(lv_obj_t* parent)
{
    myobj = lv_textarea_create(parent);
    label = get_label();
    fontsize = nullptr;
}

LvcppTextArea::~LvcppTextArea()
{

}

int LvcppTextArea::set_text(const char* txt)
{
    lv_textarea_set_text(myobj, txt);
    return 0;
}

int LvcppTextArea::set_placeholder_text(const char * txt)
{
    lv_textarea_set_placeholder_text(myobj,txt);
    return 0;
}

int LvcppTextArea::set_password_mode(bool en)
{
    lv_textarea_set_password_mode(myobj,en);
    return 0;
}

int LvcppTextArea::set_one_line(bool en)
{
    lv_textarea_set_one_line(myobj,en);
    return 0;
}

int LvcppTextArea::set_accepted_chars(const char * list)
{
    lv_textarea_set_accepted_chars(myobj,list);
    return 0;
}

int LvcppTextArea::set_max_length(uint32_t length)
{
    lv_textarea_set_max_length(myobj,length);
    return 0;
}

int LvcppTextArea::set_align(lv_text_align_t align)
{
    lv_textarea_set_align(myobj, align);
    return 0;
}

int LvcppTextArea::txt_font_size(uint16_t weight, uint16_t font_type)
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
        label = get_label();
        lv_obj_set_style_text_font(label, fontsize->font(), LV_PART_MAIN);
    }
    return 0;
}

int LvcppTextArea::txt_color(lv_color_t value)
{
    if(label != nullptr)
    {
        lv_obj_set_style_text_color(label, value, LV_PART_MAIN);
        lv_obj_get_style_color_filter_dsc(label,LV_PART_MAIN);
    }
    else
    {
        label = get_label();
        lv_obj_set_style_text_color(label, value, LV_PART_MAIN);
        lv_obj_get_style_color_filter_dsc(label,LV_PART_MAIN);
    }
    return 0;
}


int LvcppTextArea::txt_long_mode(lv_label_long_mode_t mode)
{
    if(label != nullptr)
    {
        lv_label_set_long_mode(label,mode);
    }
    else
    {
        label = get_label();
        lv_label_set_long_mode(label,mode);
    }
    return 0;
}

int LvcppTextArea::txt_align(lv_text_align_t align)
{
    if(label != nullptr)
    {
        lv_obj_set_style_text_align(label,align,LV_PART_MAIN);
    }
    else
    {
        label = get_label();
        lv_obj_set_style_text_align(label,align,LV_PART_MAIN);
    }
    return 0;
}


int LvcppTextArea::get_text_align(void)
{
    lv_obj_get_style_text_align(myobj,0);
    return 0;
}

int LvcppTextArea::set_password_show_time(uint16_t time)
{
    lv_textarea_set_password_show_time(myobj, time);
    return 0;
}

int LvcppTextArea::set_cursor_pos(int32_t pos)
{
    lv_textarea_set_cursor_pos(myobj, pos);
    return 0;
}

int LvcppTextArea::set_cursor_click_pos(bool en)
{
    lv_textarea_set_cursor_click_pos(myobj, en);
    return 0;
}

int LvcppTextArea::set_cursor_flicker(bool en)
{
    if(en)
    {
        lv_event_send(myobj,LV_EVENT_FOCUSED,NULL);
    }
    else
    {
        lv_event_send(myobj,LV_EVENT_DEFOCUSED,NULL);
    }

}

lv_obj_t* LvcppTextArea::get_label(void)
{
    return lv_textarea_get_label(myobj);
}

const char* LvcppTextArea::get_text(void)
{
    return lv_textarea_get_text(myobj);
}


const char* LvcppTextArea::get_placeholder_text(void)
{
    return lv_textarea_get_placeholder_text(myobj);
}

bool LvcppTextArea::get_one_line(void)
{
    return lv_textarea_get_one_line(myobj);
}

const char* LvcppTextArea::get_accepted_chars(void)
{
    return lv_textarea_get_accepted_chars(myobj);
}

uint32_t LvcppTextArea::get_max_length(void)
{
    return lv_textarea_get_max_length(myobj);
}

bool LvcppTextArea::get_password_mode(void)
{
    return lv_textarea_get_password_mode(myobj);
}

uint16_t LvcppTextArea::get_password_show_time(void)
{
    return lv_textarea_get_password_show_time(myobj);
}

uint32_t LvcppTextArea::get_cursor_pos(void)
{
    return lv_textarea_get_cursor_pos(myobj);
}

bool LvcppTextArea::get_cursor_click_pos(void)
{

   return lv_textarea_get_cursor_click_pos(myobj);
}

lv_color_t LvcppTextArea::get_txt_color(void)
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

lv_text_align_t LvcppTextArea::get_txt_align(void)
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

int LvcppTextArea::get_txt_long_mode(void)
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
