#include "lvcpp_spinbox.h"

LvcppSpinBox::LvcppSpinBox(lv_obj_t* parent)
{
    myobj = lv_spinbox_create(parent);
}

LvcppSpinBox::~LvcppSpinBox(void)
{

}

//set
int LvcppSpinBox::set_value(int32_t i)
{
    lv_spinbox_set_value(myobj, i);
    return 0;
}

int LvcppSpinBox::set_rollover(bool b)
{
    lv_spinbox_set_rollover(myobj, b);
    return 0;
}

int LvcppSpinBox::set_digit_format(uint8_t digit_count, uint8_t separator_position)
{
    lv_spinbox_set_digit_format(myobj, digit_count, separator_position);
    return 0;
}

int LvcppSpinBox::set_step(uint32_t step)
{
    lv_spinbox_set_step(myobj, step);
    return 0;
}

int LvcppSpinBox::set_range(int32_t range_min, int32_t range_max)
{
    lv_spinbox_set_range(myobj, range_min, range_max);
    return 0;
}

int LvcppSpinBox::set_pos(uint8_t pos)
{
    lv_spinbox_set_pos(myobj, pos);
    return 0;
}

int LvcppSpinBox::set_digit_step_direction(lv_dir_t direction)
{
    lv_spinbox_set_digit_step_direction(myobj, direction);
    return 0;
}


//get

bool LvcppSpinBox::get_rollover(void)
{

    return lv_spinbox_get_rollover(myobj);
}

int LvcppSpinBox::get_value(void)
{

    return lv_spinbox_get_value(myobj);
}

int LvcppSpinBox::get_step(void)
{

    return lv_spinbox_get_step(myobj);
}
