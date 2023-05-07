#ifndef LVCPP_ARC_H
#define LVCPP_ARC_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

class LvcppArcDrawing : public LvcppObject
{
public:
    LvcppArcDrawing(lv_obj_t* parent=nullptr);
    ~LvcppArcDrawing(void);

    //set
    int set_start_angle(uint16_t start);
    int set_end_angle(uint16_t end);
    int set_angles(uint16_t start, uint16_t end);
    int set_bg_start_angle(uint16_t start);
    int set_bg_end_angle(uint16_t end);
    int set_bg_angles(uint16_t start, uint16_t end);
    int set_rotation(uint16_t rotation);
    int set_mode(lv_arc_mode_t type);
    int set_value(int16_t value);
    int set_range(int16_t min, int16_t max);
    int set_change_rate(uint16_t rate);

    //get
    int get_angle_start(void);
    int get_angle_end(void);
    int get_bg_angle_start(void);
    int get_bg_angle_end(void);
    int get_value(void);
    int get_min_value(void);
    int get_max_value(void);
    int get_mode(void);

};

#endif // LVCPP_ARC_H
