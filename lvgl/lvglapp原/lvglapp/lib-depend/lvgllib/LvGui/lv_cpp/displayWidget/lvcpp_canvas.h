#ifndef LVCPP_CANVAS_H
#define LVCPP_CANVAS_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

class LvcppCanvas : public LvcppObject
{
public:
    LvcppCanvas(lv_obj_t* parent = nullptr);
    ~LvcppCanvas(void);

    //set
    int set_buffer(void * buf, lv_coord_t w, lv_coord_t h, lv_img_cf_t cf);
    int set_px_color(lv_coord_t x, lv_coord_t y, lv_color_t c);
    int set_px_opa(lv_coord_t x, lv_coord_t y, lv_opa_t opa);
    int set_palette(uint8_t id, lv_color_t c);

    int copy_buf(const void * to_copy, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h);
    int transform(lv_img_dsc_t * img, int16_t angle, uint16_t zoom, lv_coord_t offset_x,
                             lv_coord_t offset_y,int32_t pivot_x,
                             int32_t pivot_y, bool antialias);
    int blur_hor(const lv_area_t * area, uint16_t r);
    int blur_ver(const lv_area_t * area, uint16_t r);
    int fill_bg(lv_color_t color, lv_opa_t opa);
    int draw_rect(lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h,
                             const lv_draw_rect_dsc_t * draw_dsc);
    int draw_text(lv_coord_t x, lv_coord_t y, lv_coord_t max_w,
                             lv_draw_label_dsc_t * draw_dsc, const char * txt);
    int draw_img(lv_coord_t x, lv_coord_t y, const void * src,
                            const lv_draw_img_dsc_t * draw_dsc);
    int draw_line(const lv_point_t points[], uint32_t point_cnt,
                             const lv_draw_line_dsc_t * draw_dsc);
    int draw_polygon(const lv_point_t points[], uint32_t point_cnt,
                                const lv_draw_rect_dsc_t * draw_dsc);
    int draw_arc(lv_coord_t x, lv_coord_t y, lv_coord_t r, int32_t start_angle,
                            int32_t end_angle, const lv_draw_arc_dsc_t * draw_dsc);

    //get
    lv_color_t get_px(lv_coord_t x, lv_coord_t y);
    lv_img_dsc_t * get_img(void);

private:
    lv_img_dsc_t img_dsc;
};

#endif // LVCPP_CANVAS_H
