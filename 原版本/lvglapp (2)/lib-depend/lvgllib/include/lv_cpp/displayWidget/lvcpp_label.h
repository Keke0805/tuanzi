#ifndef LVCPP_LABEL_H
#define LVCPP_LABEL_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"
#include  "lv_cpp/font/lvcpp_freetypefont.h"

class LvcppLabel : public LvcppObject
{
public:
    LvcppLabel(lv_obj_t* parent = nullptr);
    ~LvcppLabel(void);

    //set
    int set_txt(const char* str);
    int txt_font_size(uint16_t weight, uint16_t font_type);
    int txt_align(lv_text_align_t);
    int txt_center(void);
    int txt_color(lv_color_t, lv_style_selector_t);
    int txt_long_mode(lv_label_long_mode_t mode);
    int txt_recolor(bool en);

    //get
    const char* get_txt(void);
    lv_text_align_t get_txt_align(void);
    lv_color_t get_txt_color(void);
    int get_txt_long_mode(void);

private:
    LvcppFreeTypeFont* fontsize=nullptr;
};

#endif // LVCPP_LABEL_H
