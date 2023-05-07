
#include "lvcpp_style.h"

LvcppStyle::LvcppStyle(void)
{
    mystyle = new lv_style_t;
    lv_style_init(mystyle);
	fontsize=nullptr;
}

LvcppStyle::~LvcppStyle(void)
{
    lv_style_reset(mystyle);
    delete mystyle;
    mystyle = NULL;
}

void LvcppStyle::reset(void)
{
    lv_style_reset(mystyle);
}

lv_style_prop_t LvcppStyle::register_prop(void)
{
    return lv_style_register_prop();
}

bool LvcppStyle::remove_prop(lv_style_prop_t prop)
{
    return lv_style_remove_prop(mystyle, prop);
}

void LvcppStyle::set_prop(lv_style_prop_t prop, lv_style_value_t value)
{
    lv_style_set_prop(mystyle, prop, value);
}

lv_res_t LvcppStyle::get_prop(lv_style_prop_t prop, lv_style_value_t * value)
{
    return lv_style_get_prop(mystyle, prop, value);
}

void LvcppStyle::transition_dsc_init(lv_style_transition_dsc_t * tr, const lv_style_prop_t props[],
                        lv_anim_path_cb_t path_cb, uint32_t time, uint32_t delay, void * user_data)
{
    lv_style_transition_dsc_init(tr,props,path_cb,time,delay,user_data);
}

lv_style_value_t LvcppStyle::prop_get_default(lv_style_prop_t prop)
{
    return lv_style_prop_get_default(prop);
}

bool LvcppStyle::is_empty()
{
    return lv_style_is_empty(mystyle);
}

void LvcppStyle::set_size(lv_size_t size)
{
    lv_style_set_width(mystyle, size.width);
    lv_style_set_height(mystyle, size.height);
}

void LvcppStyle::set_width(lv_coord_t width)
{
    lv_style_set_width(mystyle, width);
}

void LvcppStyle::set_height(lv_coord_t height)
{
    lv_style_set_height(mystyle, height);
}

void LvcppStyle::set_min_width(lv_coord_t value)
{
    lv_style_set_min_width(mystyle, value);
}

void LvcppStyle::set_max_width(lv_coord_t value)
{
    lv_style_set_max_width(mystyle, value);
}

void LvcppStyle::set_min_height(lv_coord_t value)
{
    lv_style_set_min_height(mystyle, value);
}

void LvcppStyle::set_max_height(lv_coord_t value)
{
    lv_style_set_max_height(mystyle, value);
}

void LvcppStyle::set_pos(lv_point_t value)
{
    lv_style_set_x(mystyle, value.x);
    lv_style_set_y(mystyle, value.y);
}

void LvcppStyle::set_x(lv_coord_t value)
{
    lv_style_set_x(mystyle, value);
}

void LvcppStyle::set_y(lv_coord_t value)
{
    lv_style_set_y(mystyle, value);
}

void LvcppStyle::set_align(lv_align_t value)
{
    lv_style_set_align(mystyle, value);
}

void LvcppStyle::set_transform_width(lv_coord_t value)
{
    lv_style_set_transform_width(mystyle, value);
}

void LvcppStyle::set_transform_height(lv_coord_t value)
{
    lv_style_set_transform_height(mystyle, value);
}

void LvcppStyle::set_translate_x(lv_coord_t value)
{
    lv_style_set_translate_x(mystyle, value);
}

void LvcppStyle::set_translate_y(lv_coord_t value)
{
    lv_style_set_translate_y(mystyle, value);
}

void LvcppStyle::set_transform_zoom(lv_coord_t value)
{
    lv_style_set_transform_zoom(mystyle, value);
}
void LvcppStyle::set_transform_angle(lv_coord_t value)
{
    lv_style_set_transform_angle(mystyle, value);
}

void LvcppStyle::set_pad_top(lv_coord_t value)
{
    lv_style_set_pad_top(mystyle, value);
}

void LvcppStyle::set_pad_bottom(lv_coord_t value)
{
    lv_style_set_pad_bottom(mystyle, value);
}

void LvcppStyle::set_pad_left(lv_coord_t value)
{
    lv_style_set_pad_left(mystyle, value);
}

void LvcppStyle::set_pad_right(lv_coord_t value)
{
    lv_style_set_pad_right(mystyle, value);
}

void LvcppStyle::set_pad_row(lv_coord_t value)
{
    lv_style_set_pad_row(mystyle, value);
}

void LvcppStyle::set_pad_column(lv_coord_t value)
{
    lv_style_set_pad_column(mystyle, value);
}

void LvcppStyle::set_pad_all(lv_coord_t value)
{
    lv_style_set_pad_all(mystyle, value);
}

void LvcppStyle::set_pad_hor(lv_coord_t value)
{
    lv_style_set_pad_hor(mystyle, value);
}

void LvcppStyle::set_pad_ver(lv_coord_t value)
{
    lv_style_set_pad_ver(mystyle, value);
}

void LvcppStyle::set_pad_gap(lv_coord_t value)
{
    lv_style_set_pad_gap(mystyle, value);
}

void LvcppStyle::set_bg_color(lv_color_t value)
{
    lv_style_set_bg_color(mystyle, value);
}

void LvcppStyle::set_bg_color_filtered(lv_color_t value)
{
    lv_style_set_bg_color_filtered(mystyle, value);
}

void LvcppStyle::set_bg_opa(lv_opa_t value)
{
    lv_style_set_bg_opa(mystyle, value);
}

void LvcppStyle::set_bg_grad_color(lv_color_t value)
{
    lv_style_set_bg_grad_color(mystyle, value);
}

void LvcppStyle::set_bg_grad_color_filtered(lv_color_t value)
{
    lv_style_set_bg_grad_color_filtered(mystyle, value);
}

void LvcppStyle::set_bg_grad_dir(lv_grad_dir_t value)
{
    lv_style_set_bg_grad_dir(mystyle, value);
}

void LvcppStyle::set_bg_main_stop(lv_coord_t value)
{
    lv_style_set_bg_main_stop(mystyle, value);
}

void LvcppStyle::set_bg_grad_stop(lv_coord_t value)
{
    lv_style_set_bg_grad_stop(mystyle, value);
}

void LvcppStyle::set_bg_grad(lv_grad_dsc_t * value)
{
    lv_style_set_bg_grad(mystyle, value);
}

void LvcppStyle::set_bg_dither_mode(lv_dither_mode_t value)
{
    lv_style_set_bg_dither_mode(mystyle, value);
}

void LvcppStyle::set_bg_img_src(const void * value)
{
    lv_style_set_bg_img_src(mystyle, value);
}

void LvcppStyle::set_bg_img_opa(lv_opa_t value)
{
    lv_style_set_bg_img_opa(mystyle, value);
}

void LvcppStyle::set_bg_img_recolor(lv_color_t value)
{
    lv_style_set_bg_img_recolor(mystyle, value);
}

void LvcppStyle::set_bg_img_recolor_filtered(lv_color_t value)
{
    lv_style_set_bg_img_recolor_filtered(mystyle, value);
}

void LvcppStyle::set_bg_img_recolor_opa(lv_opa_t value)
{
    lv_style_set_bg_img_recolor_opa(mystyle, value);
}

void LvcppStyle::set_bg_img_tiled(bool value)
{
    lv_style_set_bg_img_tiled(mystyle, value);
}

void LvcppStyle::set_border_color(lv_color_t value)
{
    lv_style_set_border_color(mystyle, value);
}

void LvcppStyle::set_border_color_filtered(lv_color_t value)
{
    lv_style_set_border_color(mystyle, value);
}

void LvcppStyle::set_border_opa(lv_opa_t value)
{
    lv_style_set_border_opa(mystyle, value);
}

void LvcppStyle::set_border_width(lv_coord_t value)
{
    lv_style_set_border_width(mystyle, value);
}

void LvcppStyle::set_border_side(lv_border_side_t value)
{
    lv_style_set_border_side(mystyle, value);
}

void LvcppStyle::set_border_post(bool value)
{
    lv_style_set_border_post(mystyle, value);
}

void LvcppStyle::set_outline_width(lv_coord_t value)
{
    lv_style_set_outline_width(mystyle, value);
}

void LvcppStyle::set_outline_color(lv_color_t value)
{
    lv_style_set_outline_color(mystyle, value);
}

void LvcppStyle::set_outline_color_filtered(lv_color_t value)
{
    lv_style_set_outline_color_filtered(mystyle, value);
}

void LvcppStyle::set_outline_opa(lv_opa_t value)
{
    lv_style_set_outline_opa(mystyle, value);
}

void LvcppStyle::set_outline_pad(lv_coord_t value)
{
    lv_style_set_outline_pad(mystyle, value);
}

void LvcppStyle::set_shadow_width( lv_coord_t value)
{
    lv_style_set_shadow_width(mystyle, value);
}

void LvcppStyle::set_shadow_ofs_x(lv_coord_t value)
{
    lv_style_set_shadow_ofs_x(mystyle, value);
}

void LvcppStyle::set_shadow_ofs_y(lv_coord_t value)
{
    lv_style_set_shadow_ofs_y(mystyle, value);
}

void LvcppStyle::set_shadow_spread(lv_coord_t value)
{
    lv_style_set_shadow_spread(mystyle, value);
}

void LvcppStyle::set_shadow_color(lv_color_t value)
{
    lv_style_set_shadow_color(mystyle, value);
}

void LvcppStyle::set_shadow_color_filtered(lv_color_t value)
{
    lv_style_set_shadow_color_filtered(mystyle, value);
}

void LvcppStyle::set_shadow_opa(lv_opa_t value)
{
    lv_style_set_shadow_opa(mystyle, value);
}

void LvcppStyle::set_img_opa(lv_opa_t value)
{
    lv_style_set_img_opa(mystyle, value);
}

void LvcppStyle::set_img_recolor(lv_color_t value)
{
    lv_style_set_img_recolor(mystyle, value);
}

void LvcppStyle::set_img_recolor_filtered(lv_color_t value)
{
    lv_style_set_img_recolor_filtered(mystyle, value);
}

void LvcppStyle::set_img_recolor_opa(lv_opa_t value)
{
    lv_style_set_img_recolor_opa(mystyle, value);
}

void LvcppStyle::set_line_width(lv_coord_t value)
{
    lv_style_set_line_width(mystyle, value);
}

void LvcppStyle::set_line_dash_width(lv_coord_t value)
{
    lv_style_set_line_dash_width(mystyle, value);
}

void LvcppStyle::set_line_dash_gap(lv_coord_t value)
{
    lv_style_set_line_dash_gap(mystyle, value);
}

void LvcppStyle::set_line_rounded(bool value)
{
    lv_style_set_line_rounded(mystyle, value);
}

void LvcppStyle::set_line_color(lv_color_t value)
{
    lv_style_set_line_color(mystyle, value);
}

void LvcppStyle::set_line_color_filtered(lv_color_t value)
{
    lv_style_set_line_color_filtered(mystyle, value);
}

void LvcppStyle::set_line_opa(lv_opa_t value)
{
    lv_style_set_line_opa(mystyle, value);
}

void LvcppStyle::set_arc_width(lv_coord_t value)
{
    lv_style_set_arc_width(mystyle, value);
}

void LvcppStyle::set_arc_rounded(bool value)
{
    lv_style_set_arc_rounded(mystyle, value);
}

void LvcppStyle::set_arc_color(lv_color_t value)
{
    lv_style_set_arc_color(mystyle, value);
}

void LvcppStyle::set_arc_color_filtered(lv_color_t value)
{
    lv_style_set_arc_color_filtered(mystyle, value);
}

void LvcppStyle::set_arc_opa(lv_opa_t value)
{
    lv_style_set_arc_opa(mystyle, value);
}

void LvcppStyle::set_arc_img_src(const void * value)
{
    lv_style_set_arc_img_src(mystyle, value);
}

void LvcppStyle::set_text_color(lv_color_t value)
{
    lv_style_set_text_color(mystyle, value);
}

void LvcppStyle::set_text_color_filtered(lv_color_t value)
{
    lv_style_set_text_color_filtered(mystyle, value);
}

void LvcppStyle::set_text_opa(lv_opa_t value)
{
    lv_style_set_text_opa(mystyle, value);
}

void LvcppStyle::set_text_font(const lv_font_t * value)
{
    lv_style_set_text_font(mystyle, value);
}

void LvcppStyle::set_text_fontsize(uint16_t weight,uint16_t font_type)
{
	if(fontsize == nullptr)
    {
       fontsize = new LvcppFreeTypeFont(weight,font_type);
    }
    else
    {
        fontsize->resize(weight,font_type);
    }
    lv_style_set_text_font(mystyle, fontsize->font());
}


void LvcppStyle::set_text_letter_space(lv_coord_t value)
{
    lv_style_set_text_letter_space(mystyle, value);
}

void LvcppStyle::set_text_line_space(lv_coord_t value)
{
    lv_style_set_text_line_space(mystyle, value);
}

void LvcppStyle::set_text_decor(lv_text_decor_t value)
{
    lv_style_set_text_decor(mystyle, value);
}

void LvcppStyle::set_text_align(lv_text_align_t value)
{
    lv_style_set_text_align(mystyle, value);
}

void LvcppStyle::set_radius(lv_coord_t value)
{
    lv_style_set_radius(mystyle, value);
}

void LvcppStyle::set_clip_corner(bool value)
{
    lv_style_set_clip_corner(mystyle, value);
}

void LvcppStyle::set_opa(lv_opa_t value)
{
    lv_style_set_opa(mystyle, value);
}

void LvcppStyle::set_color_filter_dsc(const lv_color_filter_dsc_t * value)
{
    lv_style_set_color_filter_dsc(mystyle, value);
}

void LvcppStyle::set_color_filter_opa(lv_opa_t value)
{
    lv_style_set_color_filter_opa(mystyle, value);
}

void LvcppStyle::set_anim_time(uint32_t value)
{
    lv_style_set_anim_time(mystyle, value);
}

void LvcppStyle::set_anim_speed(uint32_t value)
{
    lv_style_set_anim_speed(mystyle, value);
}

void LvcppStyle::set_transition(const lv_style_transition_dsc_t * value)
{
    lv_style_set_transition(mystyle, value);
}

void LvcppStyle::set_blend_mode(lv_blend_mode_t value)
{
    lv_style_set_blend_mode(mystyle, value);
}

void LvcppStyle::set_layout(uint16_t value)
{
    lv_style_set_radius(mystyle, value);
}

void LvcppStyle::set_base_dir(lv_base_dir_t value)
{
    lv_style_set_base_dir(mystyle, value);
}
