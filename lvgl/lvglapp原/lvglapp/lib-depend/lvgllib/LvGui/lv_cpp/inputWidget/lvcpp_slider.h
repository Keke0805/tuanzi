#ifndef LVCPP_SLIDER_H
#define LVCPP_SLIDER_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

class LvcppSlider : public LvcppObject
{
public:
    LvcppSlider(lv_obj_t* parent = nullptr);
    ~LvcppSlider(void);

    //set
    int set_value(int32_t value, lv_anim_enable_t anim);
    int set_left_value(int32_t value, lv_anim_enable_t anim);
    int set_range(int32_t min, int32_t max);
    int set_mode(lv_slider_mode_t mode);

    //get
    int get_value(void);
    int get_left_value(void);
    int get_min_value(void);
    int get_max_value(void);
    int get_mode(void);
    bool is_dragged(void);
};

#endif // LVCPP_SLIDER_H
