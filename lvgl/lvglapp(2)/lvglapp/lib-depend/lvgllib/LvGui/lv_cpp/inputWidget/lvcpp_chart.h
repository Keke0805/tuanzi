#ifndef LVCPP_CHART_H
#define LVCPP_CHART_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

class LvcppChart : public LvcppObject
{
public:
    LvcppChart(lv_obj_t* parent = nullptr);
    ~LvcppChart(void);

    //set
    int set_type(lv_chart_type_t type);
    int set_point_count(uint16_t cnt);
    int set_range(lv_chart_axis_t axis, lv_coord_t min, lv_coord_t max);
    int set_update_mode(lv_chart_update_mode_t update_mode);
    int set_div_line_count(uint8_t hdiv, uint8_t vdiv);
    int set_zoom_x(uint16_t zoom_x);
    int set_zoom_y(uint16_t zoom_y);

    //get
    int get_zoom_x(void);
    int get_zoom_y(void);
    int get_type(void);
    int get_point_count(void);

    int refresh(void);
};

#endif // LVCPP_CHART_H
