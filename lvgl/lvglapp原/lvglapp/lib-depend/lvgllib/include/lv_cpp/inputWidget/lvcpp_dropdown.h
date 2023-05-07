#ifndef LVCPP_DROPDOWN_H
#define LVCPP_DROPDOWN_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"
#include  "lv_cpp/font/lvcpp_freetypefont.h"

class LvcppDropdown : public LvcppObject
{
public:
    LvcppDropdown(lv_obj_t* parent = nullptr);
    ~LvcppDropdown(void);

    //set
    int set_text(const char * txt);
    int set_options(const char * options);
    int set_options_static(const char * options);
    int add_option(const char * option, uint32_t pos);
    int clear_options(void);
    int set_selected(uint16_t sel_opt);
    int set_dir(lv_dir_t dir);
    int set_symbol(const void * symbol);
    int set_selected_highlight(bool en);

    int txt_font_size(uint16_t weight, uint16_t font_type);
    int txt_color(lv_color_t value);
    int txt_align(lv_text_align_t align);
    int txt_long_mode(lv_label_long_mode_t mode);

    //get
    lv_obj_t * get_list(void);
    const char * get_text(void);
    const char * get_options(void);
    int get_selected(void);
    int get_option_cnt(void);
    int get_selected_str(char * buf, uint32_t buf_size);
    const char * get_symbol(void);
    bool get_selected_highlight(void);
    int get_dir(void);

    lv_text_align_t get_txt_align(void);
    lv_color_t get_txt_color(void);
    int get_txt_long_mode(void);

private:
    LvcppFreeTypeFont* fontsize=nullptr;
    lv_obj_t* label = nullptr;

};

#endif // LVCPP_DROPDOWN_H
