#ifndef LVCPP_PUSHBUTTON_H
#define LVCPP_PUSHBUTTON_H

#include  "lvgl/lvgl.h"
#include  "../core/lvcpp_object.h"
#include  "lv_cpp/font/lvcpp_freetypefont.h"

class LvcppButton : public LvcppObject
{
public:
    LvcppButton(lv_obj_t* parent = nullptr);
    ~LvcppButton();

    //set
    int set_auto_src(const void * src);
    int add_txt(const char* str);
    int clear_txt(void);
    int txt_size(lv_coord_t width, lv_coord_t height, lv_label_long_mode_t mode);
    int txt_font_size(uint16_t weight, uint16_t font_type);
    int txt_color(lv_color_t value);
    int txt_align(lv_align_t,int offset_x,int offset_y);
    int txt_long_mode(lv_label_long_mode_t mode);
    int txt_center(void);

    //get
    const void* get_main_src(void);
    lv_obj_t* get_label(void);
    const char* get_txt(void);
    lv_align_t get_txt_align(void);
    lv_color_t get_txt_color(void);
    int get_txt_long_mode(void);

protected:

private:

    LvcppFreeTypeFont* fontsize;
    lv_obj_t* label = nullptr;
};


#endif // LVCPP_PUSHBUTTON_H
