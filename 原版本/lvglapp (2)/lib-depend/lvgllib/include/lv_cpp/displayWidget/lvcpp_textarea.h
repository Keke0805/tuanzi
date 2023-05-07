#ifndef LVCPP_TEXTAREA_H
#define LVCPP_TEXTAREA_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"
#include  "lv_cpp/font/lvcpp_freetypefont.h"

class LvcppTextArea : public LvcppObject
{
public:
    LvcppTextArea(lv_obj_t* parent = nullptr);
    ~LvcppTextArea(void);

    //set
    int set_text(const char* txt);
    int set_placeholder_text(const char * txt);
    int set_password_mode(bool en);
    int set_one_line(bool en);
    int set_accepted_chars(const char * list);
    int set_max_length(uint32_t length);
    int set_password_show_time(uint16_t time);
    int set_align(lv_text_align_t align);
    int set_cursor_pos(int32_t pos);
    int set_cursor_click_pos(bool en);
    int set_cursor_flicker(bool en);

    int txt_font_size(uint16_t weight, uint16_t font_type);
    int txt_color(lv_color_t value);
    int txt_align(lv_text_align_t align);
    int txt_long_mode(lv_label_long_mode_t mode);

    //get
    lv_obj_t* get_label(void);
    const char* get_text(void);
    int get_text_align(void);
    const char* get_placeholder_text(void);
    bool get_password_mode(void);
    bool get_one_line(void);
    const char* get_accepted_chars(void);
    uint32_t get_max_length(void);
    uint16_t get_password_show_time(void);
    uint32_t get_cursor_pos(void);
    bool get_cursor_click_pos(void);

    lv_text_align_t get_txt_align(void);
    lv_color_t get_txt_color(void);
    int get_txt_long_mode(void);

private:
    LvcppFreeTypeFont* fontsize=nullptr;
    lv_obj_t* label = nullptr;
};

#endif // LVCPP_TEXTAREA_H
