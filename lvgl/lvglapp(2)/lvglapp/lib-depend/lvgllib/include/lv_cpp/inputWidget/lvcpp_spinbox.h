#ifndef LVCPP_SPINBOX_H
#define LVCPP_SPINBOX_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

class LvcppSpinBox : public LvcppObject
{
public:
    LvcppSpinBox(lv_obj_t* parent = nullptr);
    ~LvcppSpinBox(void);

    //set
    int set_value(int32_t i);
    int set_rollover(bool b);
    int set_digit_format(uint8_t digit_count, uint8_t separator_position);
    int set_step(uint32_t step);
    int set_range(int32_t range_min, int32_t range_max);
    int set_pos(uint8_t pos);
    int set_digit_step_direction(lv_dir_t direction);

    //get
    bool get_rollover(void);
    int get_value(void);
    int get_step(void);


};

#endif // LVCPP_SPINBOX_H
