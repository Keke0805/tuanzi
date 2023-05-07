#ifndef LVCPP_TEXTAREA_H
#define LVCPP_TEXTAREA_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

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

};

#endif // LVCPP_TEXTAREA_H
