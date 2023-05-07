#include "lvcpp_canvas.h"

LvcppCanvas::LvcppCanvas(lv_obj_t* parent)
{
    myobj = lv_canvas_create(parent);
}

LvcppCanvas::~LvcppCanvas(void)
{

}

//set
int LvcppCanvas::set_buffer(void * buf, lv_coord_t w, lv_coord_t h, lv_img_cf_t cf)
{
    lv_canvas_set_buffer(myobj, buf, w, h, cf);
    return 0;
}

int LvcppCanvas::set_px_color(lv_coord_t x, lv_coord_t y, lv_color_t c)
{
    lv_canvas_set_px_color(myobj, x, y, c);
    return 0;
}


int LvcppCanvas::set_px_opa(lv_coord_t x, lv_coord_t y, lv_opa_t opa)
{
    lv_canvas_set_px_opa(myobj, x, y, opa);
    return 0;
}


int LvcppCanvas::set_palette(uint8_t id, lv_color_t c)
{
    lv_canvas_set_palette(myobj, id, c);
    return 0;
}


//
int LvcppCanvas::copy_buf(const void * to_copy, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h)
{
    lv_canvas_copy_buf(myobj,to_copy, x,  y,  w, h);
    return 0;
}

int LvcppCanvas::transform(lv_img_dsc_t * img, int16_t angle, uint16_t zoom, lv_coord_t offset_x,
                         lv_coord_t offset_y,int32_t pivot_x,
                         int32_t pivot_y, bool antialias)
{
    lv_canvas_transform(myobj,img,angle, zoom, offset_x,
                            offset_y, pivot_x,
                              pivot_y, antialias);
    return 0;
}

int LvcppCanvas::blur_hor(const lv_area_t * area, uint16_t r)
{
    lv_canvas_blur_hor(myobj, area, r);
    return 0;
}

int LvcppCanvas::blur_ver(const lv_area_t * area, uint16_t r)
{
    lv_canvas_blur_ver(myobj,area, r);
    return 0;
}

int LvcppCanvas::fill_bg(lv_color_t color, lv_opa_t opa)
{
    lv_canvas_fill_bg(myobj, color,  opa);
    return 0;
}

int LvcppCanvas::draw_rect(lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h,
                         const lv_draw_rect_dsc_t * draw_dsc)
{
    lv_canvas_draw_rect(myobj, x,  y,  w,  h,
                               draw_dsc);
    return 0;
}

int LvcppCanvas::draw_text(lv_coord_t x, lv_coord_t y, lv_coord_t max_w,
                         lv_draw_label_dsc_t * draw_dsc, const char * txt)
{
    lv_canvas_draw_text(myobj, x,  y,  max_w,
                              draw_dsc,  txt);
    return 0;
}

int LvcppCanvas::draw_img(lv_coord_t x, lv_coord_t y, const void * src,
                        const lv_draw_img_dsc_t * draw_dsc)
{
    lv_canvas_draw_img(myobj, x, y,  src,
                              draw_dsc);
    return 0;
}

int LvcppCanvas::draw_line(const lv_point_t points[], uint32_t point_cnt,
                         const lv_draw_line_dsc_t * draw_dsc)
{
    lv_canvas_draw_line(myobj,  points,  point_cnt,
                               draw_dsc);
    return 0;
}

int LvcppCanvas::draw_polygon(const lv_point_t points[], uint32_t point_cnt,
                            const lv_draw_rect_dsc_t * draw_dsc)
{
    lv_canvas_draw_polygon(myobj, points,  point_cnt,
                                  draw_dsc);
    return 0;
}

int LvcppCanvas::draw_arc(lv_coord_t x, lv_coord_t y, lv_coord_t r, int32_t start_angle,
                        int32_t end_angle, const lv_draw_arc_dsc_t * draw_dsc)
{
    lv_canvas_draw_arc(myobj, x,  y,  r,  start_angle,
                             end_angle,  draw_dsc);
    return 0;
}



//get
lv_color_t LvcppCanvas::get_px(lv_coord_t x, lv_coord_t y)
{

    return lv_canvas_get_px(myobj, x, y);
}


lv_img_dsc_t * LvcppCanvas::get_img(void)
{

    return lv_canvas_get_img(myobj);
}

