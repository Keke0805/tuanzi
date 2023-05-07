#ifndef LVCPP_BAR_H
#define LVCPP_BAR_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

class LvcppBar : public LvcppObject
{
public:
    LvcppBar(lv_obj_t* parent = nullptr);
    ~LvcppBar(void);

    //set
    int set_value(int32_t value, lv_anim_enable_t anim);
    int set_start_value(int32_t value, lv_anim_enable_t anim);
    int set_range(int32_t min, int32_t max);
    int set_mode(lv_bar_mode_t mode);

    //get
    int get_value(void);
    int get_start_value(void);
    int get_min_value(void);
    int get_max_value(void);
    lv_bar_mode_t get_mode(void);
};

#endif // LVCPP_BAR_H
