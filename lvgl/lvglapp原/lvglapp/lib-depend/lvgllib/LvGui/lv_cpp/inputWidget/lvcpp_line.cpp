#include "lvcpp_line.h"

LvcppLine::LvcppLine(lv_obj_t* parent)
{
    myobj = lv_line_create(parent);
}

LvcppLine::~LvcppLine(void)
{

}

//set
int LvcppLine::set_points(const lv_point_t points[], uint16_t point_num)
{
    lv_line_set_points(myobj,points,point_num);
    return 0;
}

int LvcppLine::set_y_invert(bool en)
{
    lv_line_set_y_invert(myobj,en);
    return 0;
}

//get
bool LvcppLine::get_y_invert(void)
{

    return lv_line_get_y_invert(myobj);
}
