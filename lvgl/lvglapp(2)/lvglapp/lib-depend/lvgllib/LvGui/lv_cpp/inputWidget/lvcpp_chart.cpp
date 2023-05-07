#include "lvcpp_chart.h"

LvcppChart::LvcppChart(lv_obj_t* parent)
{
    myobj = lv_chart_create(parent);
}

LvcppChart::~LvcppChart(void)
{

}

//set
int LvcppChart::set_type(lv_chart_type_t type)
{
    lv_chart_set_type(myobj, type);
    return 0;
}

int LvcppChart::set_point_count(uint16_t cnt)
{
    lv_chart_set_point_count(myobj, cnt);
    return 0;
}

int LvcppChart::set_range(lv_chart_axis_t axis, lv_coord_t min, lv_coord_t max)
{
    lv_chart_set_range(myobj, axis, min, max);
    return 0;
}

int LvcppChart::set_update_mode(lv_chart_update_mode_t update_mode)
{
    lv_chart_set_update_mode(myobj, update_mode);
    return 0;
}

int LvcppChart::set_div_line_count(uint8_t hdiv, uint8_t vdiv)
{
    lv_chart_set_div_line_count(myobj, hdiv, vdiv);
    return 0;
}

int LvcppChart::set_zoom_x(uint16_t zoom_x)
{
    lv_chart_set_zoom_x(myobj, zoom_x);
    return 0;
}

int LvcppChart::set_zoom_y(uint16_t zoom_y)
{
    lv_chart_set_zoom_y(myobj, zoom_y);
    return 0;
}


//get
int LvcppChart::get_zoom_x(void)
{

    return lv_chart_get_zoom_x(myobj);
}

int LvcppChart::get_zoom_y(void)
{

    return lv_chart_get_zoom_y(myobj);
}

int LvcppChart::get_type(void)
{

    return lv_chart_get_type(myobj);
}

int LvcppChart::get_point_count(void)
{

    return lv_chart_get_point_count(myobj);
}

int LvcppChart::refresh(void)
{
    lv_chart_refresh(myobj);
    return 0;
}
