#ifndef LVCPP_STYLE_H
#define LVCPP_STYLE_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/font/lvcpp_freetypefont.h" 

class LvcppStyle
{
public:
    LvcppStyle(void);
    ~LvcppStyle(void);

	lv_style_t* getstyle(){return   mystyle;};
	
    void reset(void);
    lv_style_prop_t register_prop(void);
    bool remove_prop(lv_style_prop_t prop);
    void set_prop(lv_style_prop_t prop, lv_style_value_t value);
    lv_res_t get_prop(lv_style_prop_t prop, lv_style_value_t * value);
    void transition_dsc_init(lv_style_transition_dsc_t * tr, const lv_style_prop_t props[],lv_anim_path_cb_t path_cb,
                                                                    uint32_t time, uint32_t delay, void * user_data);
    lv_style_value_t prop_get_default(lv_style_prop_t prop);
    bool is_empty();

    void set_size(lv_size_t size);
    void set_width(lv_coord_t width);
    void set_height(lv_coord_t height);
    void set_min_width(lv_coord_t value);
    void set_max_width(lv_coord_t value);
    void set_min_height(lv_coord_t value);
    void set_max_height(lv_coord_t value);
    void set_pos(lv_point_t value);
    void set_x(lv_coord_t value);
    void set_y(lv_coord_t value);

    void set_align(lv_align_t value);
    void set_transform_width(lv_coord_t value);
    void set_transform_height(lv_coord_t value);
    void set_translate_x(lv_coord_t value);
    void set_translate_y(lv_coord_t value);
    void set_transform_zoom(lv_coord_t value);
    void set_transform_angle(lv_coord_t value);

    void set_pad_top(lv_coord_t value);
    void set_pad_bottom(lv_coord_t value);
    void set_pad_left(lv_coord_t value);
    void set_pad_right(lv_coord_t value);
    void set_pad_row(lv_coord_t value);
    void set_pad_column(lv_coord_t value);
    void set_pad_all(lv_coord_t value);
    void set_pad_hor(lv_coord_t value);
    void set_pad_ver(lv_coord_t value);
    void set_pad_gap(lv_coord_t value);

    void set_bg_color(lv_color_t value);
    void set_bg_color_filtered(lv_color_t value);
    void set_bg_opa(lv_opa_t value);
    void set_bg_grad_color(lv_color_t value);
    void set_bg_grad_color_filtered(lv_color_t value);
    void set_bg_grad_dir(lv_grad_dir_t value);
    void set_bg_main_stop(lv_coord_t value);
    void set_bg_grad_stop(lv_coord_t value);
    void set_bg_grad(lv_grad_dsc_t * value);
    void set_bg_dither_mode(lv_dither_mode_t value);
    void set_bg_img_src(const void * value);
    void set_bg_img_opa(lv_opa_t value);
    void set_bg_img_recolor(lv_color_t value);
    void set_bg_img_recolor_filtered(lv_color_t value);
    void set_bg_img_recolor_opa(lv_opa_t value);
    void set_bg_img_tiled(bool value);

    void set_border_color(lv_color_t value);
    void set_border_color_filtered(lv_color_t value);
    void set_border_opa(lv_opa_t value);
    void set_border_width(lv_coord_t value);
    void set_border_side(lv_border_side_t value);
    void set_border_post(bool value);

    void set_outline_width(lv_coord_t value);
    void set_outline_color(lv_color_t value);
    void set_outline_color_filtered(lv_color_t value);
    void set_outline_opa(lv_opa_t value);
    void set_outline_pad(lv_coord_t value);

    void set_shadow_width( lv_coord_t value);
    void set_shadow_ofs_x(lv_coord_t value);
    void set_shadow_ofs_y(lv_coord_t value);
    void set_shadow_spread(lv_coord_t value);
    void set_shadow_color(lv_color_t value);
    void set_shadow_color_filtered(lv_color_t value);
    void set_shadow_opa(lv_opa_t value);

    void set_img_opa(lv_opa_t value);
    void set_img_recolor(lv_color_t value);
    void set_img_recolor_filtered(lv_color_t value);
    void set_img_recolor_opa(lv_opa_t value);

    void set_line_width(lv_coord_t value);
    void set_line_dash_width(lv_coord_t value);
    void set_line_dash_gap(lv_coord_t value);
    void set_line_rounded(bool value);
    void set_line_color(lv_color_t value);
    void set_line_color_filtered(lv_color_t value);
    void set_line_opa(lv_opa_t value);

    void set_arc_width(lv_coord_t value);
    void set_arc_rounded(bool value);
    void set_arc_color(lv_color_t value);
    void set_arc_color_filtered(lv_color_t value);
    void set_arc_opa(lv_opa_t value);
    void set_arc_img_src(const void * value);

    void set_text_color(lv_color_t value);
    void set_text_color_filtered(lv_color_t value);
    void set_text_opa(lv_opa_t value);
    void set_text_font(const lv_font_t * value);
	void set_text_fontsize(uint16_t weight,uint16_t font_type);
    void set_text_letter_space(lv_coord_t value);
    void set_text_line_space(lv_coord_t value);
    void set_text_decor(lv_text_decor_t value);
    void set_text_align(lv_text_align_t value);

    void set_radius(lv_coord_t value);
    void set_clip_corner(bool value);
    void set_opa(lv_opa_t value);
    void set_color_filter_dsc(const lv_color_filter_dsc_t * value);
    void set_color_filter_opa(lv_opa_t value);
    void set_anim_time(uint32_t value);
    void set_anim_speed(uint32_t value);
    void set_transition(const lv_style_transition_dsc_t * value);
    void set_blend_mode(lv_blend_mode_t value);
    void set_layout(uint16_t value);
    void set_base_dir(lv_base_dir_t value);


protected:
    lv_style_t* mystyle;
private:
	LvcppFreeTypeFont* fontsize=nullptr; 

};

#endif // LVCPP_STYLE_H
