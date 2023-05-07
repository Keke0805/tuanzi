#include "lvcpp_arc.h"

LvcppArcDrawing::LvcppArcDrawing(lv_obj_t* parent)
{
    myobj = lv_arc_create(parent);
}

LvcppArcDrawing::~LvcppArcDrawing(void)
{

}

//set
int LvcppArcDrawing::set_start_angle(uint16_t start)
{
    lv_arc_set_start_angle(myobj,start);
    return 0;
}

int LvcppArcDrawing::set_end_angle(uint16_t end)
{
    lv_arc_set_end_angle(myobj,end);
    return 0;
}


int LvcppArcDrawing::set_angles(uint16_t start, uint16_t end)
{
    lv_arc_set_angles(myobj,  start,  end);
    return 0;
}


int LvcppArcDrawing::set_bg_start_angle(uint16_t start)
{
    lv_arc_set_bg_start_angle(myobj,  start);
    return 0;
}


int LvcppArcDrawing::set_bg_end_angle(uint16_t end)
{
    lv_arc_set_bg_end_angle(myobj,  end);
    return 0;
}


int LvcppArcDrawing::set_bg_angles(uint16_t start, uint16_t end)
{
    if((end - start) >= 360 || (end - start) <= -360)
    {
        return -1;
    }
    lv_arc_set_bg_angles(myobj,  start,  end);
    return 0;
}


int LvcppArcDrawing::set_rotation(uint16_t rotation)
{
    lv_arc_set_rotation(myobj,  rotation);
    return 0;
}


int LvcppArcDrawing::set_mode(lv_arc_mode_t type)
{
    lv_arc_set_mode(myobj,  type);
    return 0;
}


int LvcppArcDrawing::set_value(int16_t value)
{
    lv_arc_set_value(myobj,  value);
    return 0;
}


int LvcppArcDrawing::set_range(int16_t min, int16_t max)
{
    lv_arc_set_range(myobj,  min,  max);
    return 0;
}


int LvcppArcDrawing::set_change_rate(uint16_t rate)
{
    lv_arc_set_change_rate(myobj,  rate);
    return 0;
}



//get
int LvcppArcDrawing::get_angle_start(void)
{

    return lv_arc_get_angle_start(myobj);
}


int LvcppArcDrawing::get_angle_end(void)
{

    return lv_arc_get_angle_end(myobj);
}


int LvcppArcDrawing::get_bg_angle_start(void)
{

    return lv_arc_get_bg_angle_start(myobj);
}


int LvcppArcDrawing::get_bg_angle_end(void)
{

    return lv_arc_get_bg_angle_end(myobj);
}


int LvcppArcDrawing::get_value(void)
{

    return lv_arc_get_value(myobj);
}


int LvcppArcDrawing::get_min_value(void)
{

    return lv_arc_get_min_value(myobj);
}


int LvcppArcDrawing::get_max_value(void)
{

    return lv_arc_get_max_value(myobj);
}


int LvcppArcDrawing::get_mode(void)
{

    return lv_arc_get_mode(myobj);
}

