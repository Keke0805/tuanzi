#ifndef LVCPP_COLORWHEEL_H
#define LVCPP_COLORWHEEL_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

#define  DEFAULT_KNOB_RECOLOR   0

class LvcppColorWheel : public LvcppObject
{
public:
    LvcppColorWheel(lv_obj_t* parent = nullptr);
    ~LvcppColorWheel();

    //set
    bool set_hsv(lv_color_hsv_t hsv);
    bool set_rgb(lv_color_t color);
    int set_mode(lv_colorwheel_mode_t mode);
    int set_mode_fixed(bool fixed);

    //get
    lv_color_hsv_t get_hsv(void);
    lv_color_t get_rgb(void);
    int get_color_mode(void);
    bool get_color_mode_fixed(void);

};

#endif // LVCPP_COLORWHEEL_H
