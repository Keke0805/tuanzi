#ifndef LVCPP_LINE_H
#define LVCPP_LINE_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

class LvcppLine : public LvcppObject
{
public:
    LvcppLine(lv_obj_t* parent = nullptr);
    ~LvcppLine(void);

    //set
    int set_points(const lv_point_t points[], uint16_t point_num);
    int set_y_invert(bool en);

    //get
    bool get_y_invert(void);

};

#endif // LVCPP_LINE_H
