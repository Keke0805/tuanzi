#ifndef LVCPP_METER_H
#define LVCPP_METER_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

class LvcppMeter : public LvcppObject
{
public:
    LvcppMeter(lv_obj_t* parent = nullptr);
    ~LvcppMeter(void);

    lv_meter_scale_t* add_scale(void);

    //set scale
    int set_scale_ticks(lv_meter_scale_t * scale, uint16_t cnt, uint16_t width, uint16_t len,lv_color_t color);
    int set_scale_major_ticks(lv_meter_scale_t * scale, uint16_t nth, uint16_t width, uint16_t len, lv_color_t color, int16_t label_gap);
    int set_scale_range(lv_meter_scale_t * scale, int32_t min, int32_t max, uint32_t angle_range, uint32_t rotation);


    lv_meter_indicator_t * add_needle_line(lv_meter_scale_t * scale, uint16_t width,
                                                    lv_color_t color, int16_t r_mod);
    lv_meter_indicator_t * add_needle_img(lv_meter_scale_t * scale, const void * src,
                                                   lv_coord_t pivot_x, lv_coord_t pivot_y);
    lv_meter_indicator_t * add_arc(lv_meter_scale_t * scale, uint16_t width, lv_color_t color,
                                            int16_t r_mod);
    lv_meter_indicator_t * add_scale_lines(lv_meter_scale_t * scale, lv_color_t color_start,
                                                    lv_color_t color_end, bool local, int16_t width_mod);
    //set indicator
    int set_indicator_value(lv_meter_indicator_t* indic, int32_t value);
    int set_indicator_start_value(lv_meter_indicator_t* indic, int32_t value);
    int set_indicator_end_value(lv_meter_indicator_t* indic, int32_t value);

private:
    lv_meter_scale_t* scale;
    lv_meter_indicator_t* indic;
};

#endif // LVCPP_METER_H
