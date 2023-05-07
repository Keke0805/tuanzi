#ifndef LVCPP_IMAGE_H
#define LVCPP_IMAGE_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

class LvcppImage : public LvcppObject
{
public:
    LvcppImage(lv_obj_t* parent = nullptr);
    ~LvcppImage(void);

    //set
    int set_src(const void * src);
    int set_offset_x(lv_coord_t x);
    int set_offset_y(lv_coord_t y);
    int set_angle(int16_t angle);
    int set_pivot(lv_coord_t x, lv_coord_t y);
    int set_zoom(uint16_t zoom);
    int set_antialias(bool antialias);
    int set_size_mode(lv_img_size_mode_t mode);

    //get
    const void * get_src(void);
    int get_offset_x(void);
    int get_offset_y(void);
    int get_angle(void);
    int get_pivot(lv_point_t * pivot);
    int get_zoom(void);
    bool get_antialias(void);
    int  get_size_mode(void);

};

#endif // LVCPP_IMAGE_H
