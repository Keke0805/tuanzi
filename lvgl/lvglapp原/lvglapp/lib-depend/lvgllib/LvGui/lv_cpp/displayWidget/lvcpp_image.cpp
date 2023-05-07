#include "lvcpp_image.h"

LvcppImage::LvcppImage(lv_obj_t* parent)
{
    myobj = lv_img_create(parent);
}

LvcppImage::~LvcppImage(void)
{

}

//set
int LvcppImage::set_src(const void * src)
{
    lv_img_set_src(myobj, src);
    return 0;
}

int LvcppImage::set_offset_x(lv_coord_t x)
{
    lv_img_set_offset_x(myobj, x);
    return 0;
}

int LvcppImage::set_offset_y(lv_coord_t y)
{
    lv_img_set_offset_y(myobj, y);
    return 0;
}

int LvcppImage::set_angle(int16_t angle)
{
    lv_img_set_angle(myobj, angle);
    return 0;
}

int LvcppImage::set_pivot(lv_coord_t x, lv_coord_t y)
{
    lv_img_set_pivot(myobj, x, y);
    return 0;
}

int LvcppImage::set_zoom(uint16_t zoom)
{
    lv_img_set_zoom(myobj, zoom);
    return 0;
}

int LvcppImage::set_antialias(bool antialias)
{
    lv_img_set_antialias(myobj, antialias);
    return 0;
}

int LvcppImage::set_size_mode(lv_img_size_mode_t mode)
{
    lv_img_set_size_mode(myobj, mode);
    return 0;
}


//get
const void * LvcppImage::get_src(void)
{
    return lv_img_get_src(myobj);
}

int LvcppImage::get_offset_x(void)
{

    return lv_img_get_offset_x(myobj);
}

int LvcppImage::get_offset_y(void)
{

    return lv_img_get_offset_y(myobj);
}

int LvcppImage::get_angle(void)
{

    return lv_img_get_angle(myobj);
}

int LvcppImage::get_pivot(lv_point_t * pivot)
{
    lv_img_get_pivot(myobj, pivot);
    return 0;
}

int LvcppImage::get_zoom(void)
{

    return lv_img_get_zoom(myobj);
}

bool LvcppImage::get_antialias(void)
{

    return lv_img_get_antialias(myobj);
}

int LvcppImage::get_size_mode(void)
{

    return lv_img_get_size_mode(myobj);
}
