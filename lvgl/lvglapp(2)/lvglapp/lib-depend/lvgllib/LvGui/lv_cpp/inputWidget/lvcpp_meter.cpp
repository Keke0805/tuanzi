#include "lvcpp_meter.h"

LvcppMeter::LvcppMeter(lv_obj_t* parent)
{
    myobj = lv_meter_create(parent);
}

LvcppMeter::~LvcppMeter(void)
{

}

lv_meter_scale_t* LvcppMeter::add_scale(void)
{

    return lv_meter_add_scale(myobj);
}

//set scale
int LvcppMeter::set_scale_ticks(lv_meter_scale_t * scale, uint16_t cnt, uint16_t width, uint16_t len,lv_color_t color)
{
    lv_meter_set_scale_ticks(myobj, scale, cnt, width, len, color);
    return 0;
}

int LvcppMeter::set_scale_major_ticks(lv_meter_scale_t * scale, uint16_t nth, uint16_t width, uint16_t len, lv_color_t color, int16_t label_gap)

{
    lv_meter_set_scale_major_ticks(myobj, scale, nth,  width, len, color, label_gap);
    return 0;
}

int LvcppMeter::set_scale_range(lv_meter_scale_t * scale, int32_t min, int32_t max, uint32_t angle_range, uint32_t rotation)
{
    lv_meter_set_scale_range(myobj, scale, min, max, angle_range, rotation);
    return 0;
}


lv_meter_indicator_t * LvcppMeter::add_needle_line(lv_meter_scale_t * scale, uint16_t width,
                                                lv_color_t color, int16_t r_mod)
{
    lv_meter_add_needle_line(myobj, scale,  width, color, r_mod);
    return 0;
}

lv_meter_indicator_t * LvcppMeter::add_needle_img(lv_meter_scale_t * scale, const void * src,
                                               lv_coord_t pivot_x, lv_coord_t pivot_y)
{

    lv_meter_add_needle_img(myobj, scale, src, pivot_x, pivot_y);
    return 0;
}

lv_meter_indicator_t * LvcppMeter::add_arc(lv_meter_scale_t * scale, uint16_t width, lv_color_t color,
                                        int16_t r_mod)
{
    lv_meter_add_arc(myobj, scale, width, color, r_mod);
    return 0;
}

lv_meter_indicator_t * LvcppMeter::add_scale_lines(lv_meter_scale_t * scale, lv_color_t color_start,
                                                lv_color_t color_end, bool local, int16_t width_mod)
{
    lv_meter_add_scale_lines(myobj, scale, color_start, color_end, local, width_mod);
    return 0;
}


//set indicator
int LvcppMeter::set_indicator_value(lv_meter_indicator_t * indic, int32_t value)
{
    lv_meter_set_indicator_value(myobj, indic, value);
    return 0;
}

int LvcppMeter::set_indicator_start_value(lv_meter_indicator_t * indic, int32_t value)
{
    lv_meter_set_indicator_start_value(myobj, indic, value);
    return 0;
}

int LvcppMeter::set_indicator_end_value(lv_meter_indicator_t * indic, int32_t value)
{
    lv_meter_set_indicator_end_value(myobj, indic, value);
    return 0;
}
