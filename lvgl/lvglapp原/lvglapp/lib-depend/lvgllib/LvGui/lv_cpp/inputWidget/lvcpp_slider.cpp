#include "lvcpp_slider.h"

LvcppSlider::LvcppSlider(lv_obj_t* parent)
{
    myobj = lv_slider_create(parent);
}

LvcppSlider::~LvcppSlider(void)
{

}

int LvcppSlider::set_value(int32_t value, lv_anim_enable_t anim)
{
    lv_slider_set_value(myobj, value, anim);
    return 0;
}

int LvcppSlider::set_left_value(int32_t value, lv_anim_enable_t anim)
{
    lv_slider_set_left_value(myobj, value, anim);
    return 0;
}

int LvcppSlider::set_range(int32_t min, int32_t max)
{
    lv_slider_set_range(myobj, min, max);
    return 0;
}

int LvcppSlider::set_mode( lv_slider_mode_t mode)
{
    lv_slider_set_mode(myobj, mode);
    return 0;
}

int32_t LvcppSlider::get_value()
{
    return lv_slider_get_value(myobj);
}

int32_t LvcppSlider::get_left_value()
{
    return lv_slider_get_left_value(myobj);
}

int32_t LvcppSlider::get_min_value()
{
    return lv_slider_get_min_value(myobj);
}

int32_t LvcppSlider::get_max_value()
{
    return lv_slider_get_max_value(myobj);
}

bool LvcppSlider::is_dragged()
{
    return lv_slider_is_dragged(myobj);
}

int LvcppSlider::get_mode()
{
    return lv_slider_get_mode(myobj);
}
