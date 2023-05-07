#include "lvcpp_bar.h"

LvcppBar::LvcppBar(lv_obj_t* parent)
{
    myobj = lv_bar_create(parent);
}

LvcppBar::~LvcppBar(void)
{

}

int LvcppBar::set_value(int32_t value, lv_anim_enable_t anim)
{
    lv_bar_set_value(myobj, value, anim);
    return 0;
}

int LvcppBar::set_start_value(int32_t value, lv_anim_enable_t anim)
{
    lv_bar_set_start_value(myobj, value, anim);
    return 0;
}

int LvcppBar::set_range(int32_t min, int32_t max)
{
    lv_bar_set_range(myobj, min, max);
    return 0;
}

int LvcppBar::set_mode(lv_bar_mode_t mode)
{
    lv_bar_set_mode(myobj, mode);
    return 0;
}

int32_t LvcppBar::get_value()
{
    return lv_bar_get_value(myobj);
}

int32_t LvcppBar::get_start_value()
{
    return lv_bar_get_start_value(myobj);
}

int32_t LvcppBar::get_min_value()
{
    return lv_bar_get_min_value(myobj);
}

int32_t LvcppBar::get_max_value()
{
    return lv_bar_get_max_value(myobj);
}

lv_bar_mode_t LvcppBar::get_mode()
{
    return lv_bar_get_mode(myobj);
}


