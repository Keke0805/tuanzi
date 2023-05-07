#ifndef LVCPP_OBJECT_H
#define LVCPP_OBJECT_H

#include  "lvgl/lvgl.h"

namespace LvglCppOperator {

 class LvcppObject;
}

class LvcppObject
{
public:
    LvcppObject(void);
    ~LvcppObject(void);

    //obj
    int show(bool flag);
    int clicked_enable(bool flag);
    int scrollbar_enable(bool flag);
    int delete_myobj(void);
    int clean_myobj(void);
    int delete_obj(lv_obj_t* target_obj);
    int clean_obj(lv_obj_t* target_obj);
    int move_foreground(void);
    int move_background(void);
    int set_userdata(void* obj_user_data);

    lv_obj_t* get_child(int id);
    int get_child_cnt(void);
    void* get_userdata(void);

    //pos
    int set_pos_x(int pos_x);
    int set_pos_y(int pos_y);
    int set_pos(int pos_x, int pos_y);
    int set_width(int width);
    int set_height(int height);
    int set_size(int width, int height);
    int set_style_width_min(int min_width);
    int set_style_width_max(int max_width);
    int set_style_width(int def_width, int min_width, int max_width);
    int set_style_height_min(int min_height);
    int set_style_height_max(int max_height);
    int set_style_height(int def_height, int min_height, int max_height);
    int center_align(void);
    int align(lv_align_t align, int offset_x, int offset_y);
    int align_to(lv_obj_t* target, lv_align_t align, int offset_x, int offset_y);
    int set_align_mode(lv_align_t align);
    int set_flex_flow(lv_flex_flow_t flow);
    int set_flex_align(lv_flex_align_t main_place, lv_flex_align_t cross_place, lv_flex_align_t track_place);

    lv_coord_t pos_x(void);
    lv_coord_t pos_y(void);
    lv_coord_t width(void);
    lv_coord_t height(void);
    lv_coord_t get_main_pad_left(void);
    lv_coord_t get_main_pad_right(void);
    lv_coord_t get_main_pad_top(void);
    lv_coord_t get_main_pad_bottom(void);
    lv_coord_t get_main_text_letter_space(void);
    lv_coord_t get_main_text_line_space(void);
    const lv_font_t* get_main_text_font(void);
    lv_coord_t get_main_min_height(void);
    lv_coord_t get_main_max_height(void);
    lv_coord_t get_main_min_width(void);
    lv_coord_t get_main_max_width(void);
    lv_align_t get_main_align(void);
    int set_main_align(lv_align_t value);

    //scroll
    int set_scrollbar_mode(lv_scrollbar_mode_t scroll_mode);
    int set_scrollbar_dir(lv_dir_t dir);
    int set_scrollbar_snap_x(lv_scroll_snap_t align);
    int set_scrollbar_snap_y(lv_scroll_snap_t align);
    int set_scroll_to(lv_coord_t x, lv_coord_t y, lv_anim_enable_t anim_en);
    int scroll_to_view(lv_obj_t * obj, lv_anim_enable_t anim_en);

    bool is_scrolling(void);
    lv_scrollbar_mode_t get_scrollbar_mode(void);
    lv_dir_t get_scroll_dir(void);
    lv_scroll_snap_t get_scroll_snap_x(void);
    lv_scroll_snap_t get_scroll_snap_y(void);
    lv_coord_t get_scroll_x(void);
    lv_coord_t get_scroll_y(void);
    lv_coord_t get_scroll_top(void);
    lv_coord_t get_scroll_bottom(void);
    lv_coord_t get_scroll_left(void);
    lv_coord_t get_scroll_right(void);

    //state
    lv_state_t get_state(void);
    int add_state(lv_state_t state);
    int clear_state(lv_state_t state);
    bool has_state(lv_state_t state);

    //flag
    int add_flag(lv_obj_flag_t flag);
    int clear_flag(lv_obj_flag_t flag);
    bool has_flag(lv_obj_flag_t flag);
    bool has_flag_all(lv_obj_flag_t flag);

    //style
    int set_main_base_dir(lv_base_dir_t value);
    int set_main_pad_column(lv_coord_t value);
    int set_main_pad_row(lv_coord_t value);
    int set_main_pad_L_R(lv_coord_t left_value, lv_coord_t right_value);
    int set_main_pad_T_B(lv_coord_t top_value, lv_coord_t bottom_value);
    int set_main_pad_all(lv_coord_t value);
    int set_main_border(lv_coord_t width, lv_color_t color, lv_opa_t opa);
    int set_main_border_width(lv_coord_t width);
    int set_main_border_color(lv_color_t color);
    int set_main_outline_width(lv_coord_t width);
    int set_main_background(lv_color_t color, lv_opa_t opa);
    int set_main_radius(lv_coord_t value);
    int set_main_bg_color(lv_color_t color, lv_opa_t opa);
    int set_main_bg_opa(lv_opa_t opa);
    int set_main_bg_img_src(const void * filepath);
    int set_main_shadow_width(lv_coord_t value);

    lv_coord_t get_style_pos_x(lv_style_selector_t selector);
    lv_coord_t get_style_pos_y(lv_style_selector_t selector);
    lv_coord_t get_style_pad_left(lv_style_selector_t selector);
    lv_coord_t get_style_pad_right(lv_style_selector_t selector);
    lv_coord_t get_style_pad_top(lv_style_selector_t selector);
    lv_coord_t get_style_pad_bottom(lv_style_selector_t selector);
    lv_coord_t get_style_text_letter_space(lv_style_selector_t selector);
    lv_coord_t get_style_text_line_space(lv_style_selector_t selector);
    const lv_font_t* get_style_text_font(lv_style_selector_t selector);
    lv_coord_t get_style_min_height(lv_style_selector_t selector);
    lv_coord_t get_style_max_height(lv_style_selector_t selector);
    lv_coord_t get_style_min_width(lv_style_selector_t selector);
    lv_coord_t get_style_max_width(lv_style_selector_t selector);

    int set_style_bg_color(lv_color_t color, lv_opa_t opa, lv_style_selector_t selector);
    int set_style_bg_img_src(const void * filepath, lv_style_selector_t selector);
    int set_style_radius(lv_coord_t value, lv_style_selector_t selector);
    int set_style_border_style(lv_coord_t width, lv_color_t color, lv_opa_t opa, lv_style_selector_t selector);
    int set_style_shadow_width(lv_coord_t value, lv_style_selector_t selector);
    int set_style_pad_L_R(lv_coord_t left_value, lv_coord_t right_value, lv_style_selector_t selector);
    int set_style_pad_T_B(lv_coord_t top_value, lv_coord_t bottom_value, lv_style_selector_t selector);
    int set_style_pad_all(lv_coord_t value, lv_style_selector_t selector);
    int set_style_pad_column(lv_coord_t value, lv_style_selector_t selector);
    int set_style_pad_row(lv_coord_t value, lv_style_selector_t selector);
    int set_style(lv_style_t* style, lv_style_selector_t selector);
    int set_style_text_font(lv_font_t* font,lv_style_selector_t selector);
    int set_style_clip_corner(bool value, lv_style_selector_t selector);
    int set_style_transform_width(lv_coord_t value, lv_style_selector_t selector);
    int set_style_transform_height(lv_coord_t value, lv_style_selector_t selector);
    int set_style_translate_x(lv_coord_t value, lv_style_selector_t selector);
    int set_style_translate_y(lv_coord_t value, lv_style_selector_t selector);
    int set_style_transform_zoom(lv_coord_t value, lv_style_selector_t selector);
    int set_style_transform_angle(lv_coord_t value, lv_style_selector_t selector);
    int set_style_transform_pivot_x(lv_coord_t value, lv_style_selector_t selector);
    int set_style_transform_pivot_y(lv_coord_t value, lv_style_selector_t selector);
    int set_style_base_dir(lv_base_dir_t value, lv_style_selector_t selector);
    int set_style_prop(lv_part_t part, lv_style_prop_t prop, lv_style_value_t value);
    lv_style_value_t get_style_prop(lv_part_t part, lv_style_prop_t prop);

    //events
    int add_event_cb(lv_event_cb_t event_cb, lv_event_code_t filter, void *);
    int remove_event_cb(lv_event_cb_t event_cb);

    //theme
    int apply_theme(void);
    lv_theme_t * get_theme(void);

    //refresh
    int invalidate(void);

    lv_obj_t* myobj;
private:

};

#endif // LVCPP_OBJECT_H
