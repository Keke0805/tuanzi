#include "lvcpp_colorwheel.h"

LvcppColorWheel::LvcppColorWheel(lv_obj_t* parent)
{
    myobj = lv_colorwheel_create(parent, DEFAULT_KNOB_RECOLOR);
}

LvcppColorWheel::~LvcppColorWheel(void)
{

}

//set
bool LvcppColorWheel::set_hsv(lv_color_hsv_t hsv)
{
    return lv_colorwheel_set_hsv(myobj, hsv);
}

bool LvcppColorWheel::set_rgb(lv_color_t color)
{

    return lv_colorwheel_set_rgb(myobj, color);
}

int LvcppColorWheel::set_mode(lv_colorwheel_mode_t mode)
{
    lv_colorwheel_set_mode(myobj, mode);
    return 0;
}

int LvcppColorWheel::set_mode_fixed(bool fixed)
{
    lv_colorwheel_set_mode_fixed(myobj, fixed);
    return 0;
}

//get
lv_color_hsv_t LvcppColorWheel::get_hsv(void)
{
    return lv_colorwheel_get_hsv(myobj);
}

lv_color_t LvcppColorWheel::get_rgb(void)
{

    return lv_colorwheel_get_rgb(myobj);
}

int LvcppColorWheel:: get_color_mode(void)
{

    return lv_colorwheel_get_color_mode(myobj);
}

bool LvcppColorWheel::get_color_mode_fixed(void)
{

    return lv_colorwheel_get_color_mode_fixed(myobj);
}
