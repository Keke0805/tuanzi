#include  "lvcpp_object.h"

LvcppObject::LvcppObject(void)
{
    myobj = NULL;
}

LvcppObject::~LvcppObject(void)
{
    lv_obj_del(myobj);
}

int LvcppObject::show(bool flag)
{
    if(flag)
    {
        clear_flag(LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        add_flag(LV_OBJ_FLAG_HIDDEN);
    }

    return 0;
}

int LvcppObject::clicked_enable(bool flag)
{
    if(flag)
    {
        clear_flag(LV_OBJ_FLAG_CLICKABLE);
    }
    else
    {
        add_flag(LV_OBJ_FLAG_CLICKABLE);
    }

    return 0;
}
int LvcppObject::scrollbar_enable(bool flag)
{
    if(flag)
    {
        clear_flag(LV_OBJ_FLAG_SCROLLABLE);
    }
    else
    {
        add_flag(LV_OBJ_FLAG_SCROLLABLE);
    }

    return 0;
}

int LvcppObject::delete_obj(lv_obj_t* target)
{
    lv_obj_del(target);
    return 0;
}

int LvcppObject::clean_obj(lv_obj_t* target)
{
    lv_obj_clean(target);
    return 0;
}

int LvcppObject::delete_myobj(void)
{
    lv_obj_del(myobj);
    return 0;
}

int LvcppObject::clean_myobj(void)
{
    lv_obj_clean(myobj);
    return 0;
}

int LvcppObject::move_foreground(void)
{
    lv_obj_move_foreground(myobj);
    return 0;
}

int LvcppObject::move_background(void)
{
    lv_obj_move_background(myobj);
    return 0;
}

int LvcppObject::set_userdata(void* obj_user_data)
{
    myobj->user_data = obj_user_data;

    return 0;
}

lv_obj_t* LvcppObject::get_child(int id)
{
    return lv_obj_get_child(myobj,id);
}

int LvcppObject::get_child_cnt(void)
{
    return lv_obj_get_child_cnt(myobj);
}

void* LvcppObject::get_userdata(void)
{
    if(myobj->user_data!=nullptr)
    {
        return myobj->user_data;
    }
    return nullptr;
}

int LvcppObject::set_width(int width)
{
    lv_obj_set_width(myobj, width);
    return 0;
}

int LvcppObject::set_height(int height)
{
    lv_obj_set_height(myobj, height);
    return 0;
}

int LvcppObject::set_size(int width, int height)
{
    lv_obj_set_size(myobj, width, height);
    return 0;
}

int LvcppObject::set_style_width_min(int min_width)
{
    lv_obj_set_style_min_width(myobj, min_width, LV_PART_MAIN);
    return 0;
}

int LvcppObject::set_style_width_max(int max_width)
{
    lv_obj_set_style_max_width(myobj, max_width, LV_PART_MAIN);
    return 0;
}

int LvcppObject::set_style_width(int def_width, int min_width, int max_width)
{
    lv_obj_set_width(myobj, def_width);
    if (min_width > 0) lv_obj_set_style_min_width(myobj, min_width, LV_PART_MAIN);
    if (max_width > 0) lv_obj_set_style_max_width(myobj, max_width, LV_PART_MAIN);

    return 0;
}

int LvcppObject::set_style_height_min(int min_height)
{
    lv_obj_set_style_min_height(myobj, min_height, LV_PART_MAIN);
    return 0;
}

int LvcppObject::set_style_height_max(int max_height)
{
    lv_obj_set_style_max_height(myobj, max_height, LV_PART_MAIN);
    return 0;
}
int LvcppObject::set_style_height(int def_height, int min_height, int max_height)
{
    lv_obj_set_height(myobj,def_height);
    if(min_height > 0) lv_obj_set_style_min_height(myobj, min_height, LV_PART_MAIN);
    if(max_height > 0) lv_obj_set_style_max_height(myobj, max_height, LV_PART_MAIN);

    return 0;
}

int LvcppObject::set_pos_x(int pos_x)
{
    lv_obj_set_x(myobj, pos_x);
    return 0;
}

int LvcppObject::set_pos_y(int pos_y)
{
    lv_obj_set_y(myobj, pos_y);
    return 0;
}

int LvcppObject::set_pos(int pos_x, int pos_y)
{
    lv_obj_set_pos(myobj, pos_x, pos_y);
    return 0;
}

int LvcppObject::center_align(void)
{
    lv_obj_center(myobj);
    return 0;
}

int LvcppObject::align(lv_align_t align, int x, int y)
{

    lv_obj_align(myobj, align,  x, y);
    return 0;
}

int LvcppObject::align_to(lv_obj_t* target, lv_align_t align, int offset_x, int offset_y)
{
    lv_obj_align_to(myobj, target, align, offset_x, offset_y);
    return 0;
}

int LvcppObject::clear_state(lv_state_t state)
{
    lv_obj_clear_state(myobj, state);
    return 0;
}

int LvcppObject::add_state(lv_state_t state)
{
    lv_obj_add_state(myobj, state);
    return 0;
}

lv_state_t LvcppObject::get_state(void)
{
    return lv_obj_get_state(myobj);
}
bool LvcppObject::has_state(lv_state_t state)
{
    return lv_obj_has_state(myobj,state);
}

int LvcppObject::add_flag(lv_obj_flag_t flag)
{
    lv_obj_add_flag(myobj, flag);
    return 0;
}

int LvcppObject::clear_flag(lv_obj_flag_t flag)
{
    lv_obj_clear_flag(myobj, flag);
    return 0;
}
bool LvcppObject::has_flag(lv_obj_flag_t flag)
{
    return lv_obj_has_flag(myobj, flag);
}
bool LvcppObject::has_flag_all(lv_obj_flag_t flag)
{
    return lv_obj_has_flag_any(myobj, flag);
}


int LvcppObject::set_scrollbar_mode(lv_scrollbar_mode_t scrollbar)
{
    lv_obj_set_scrollbar_mode(myobj,scrollbar);
    return 0;
}
int LvcppObject::set_scrollbar_dir(lv_dir_t dir)
{
    lv_obj_set_scroll_dir(myobj, dir);
    return 0;
}

int LvcppObject::set_scroll_to(lv_coord_t x, lv_coord_t y, lv_anim_enable_t anim_en)
{
    lv_obj_scroll_to(myobj, x, y, anim_en);
    return 0;
}

int LvcppObject::scroll_to_view(lv_obj_t * obj, lv_anim_enable_t anim_en)
{
    lv_obj_scroll_to_view(obj, anim_en);
    return 0;
}

int LvcppObject::set_scrollbar_snap_x(lv_scroll_snap_t align)
{
    lv_obj_set_scroll_snap_x(myobj, align);
    return 0;
}

int LvcppObject::set_scrollbar_snap_y(lv_scroll_snap_t align)
{
    lv_obj_set_scroll_snap_y(myobj, align);
    return 0;
}


bool LvcppObject::is_scrolling(void)
{
    return lv_obj_is_scrolling(myobj);
}

lv_scrollbar_mode_t LvcppObject::get_scrollbar_mode(void)
{
    return lv_obj_get_scrollbar_mode(myobj);
}

lv_dir_t LvcppObject::get_scroll_dir(void)
{
    return lv_obj_get_scroll_dir(myobj);
}

lv_scroll_snap_t LvcppObject::get_scroll_snap_x(void)
{
    return lv_obj_get_scroll_snap_x(myobj);
}

lv_scroll_snap_t LvcppObject::get_scroll_snap_y(void)
{
    return lv_obj_get_scroll_snap_y(myobj);
}

lv_coord_t LvcppObject::get_scroll_x(void)
{
    return lv_obj_get_scroll_x(myobj);
}

lv_coord_t LvcppObject::get_scroll_y(void)
{
    return lv_obj_get_scroll_y(myobj);
}

lv_coord_t LvcppObject::get_scroll_top(void)
{
    return lv_obj_get_scroll_top(myobj);
}

lv_coord_t LvcppObject::get_scroll_bottom(void)
{
    return lv_obj_get_scroll_bottom(myobj);
}

lv_coord_t LvcppObject::get_scroll_left(void)
{
    return lv_obj_get_scroll_left(myobj);
}

lv_coord_t LvcppObject::get_scroll_right(void)
{
    return lv_obj_get_scroll_right(myobj);
}



int LvcppObject::set_flex_align(lv_flex_align_t main_place, lv_flex_align_t cross_place, lv_flex_align_t track_place)
{
    lv_obj_set_flex_align(myobj, main_place, cross_place, track_place);
    return 0;
}

int LvcppObject::set_flex_flow(lv_flex_flow_t flow)
{
    lv_obj_set_flex_flow(myobj, flow);

    if((flow == LV_FLEX_FLOW_ROW_WRAP) || (flow == LV_FLEX_FLOW_ROW_REVERSE) || (flow == LV_FLEX_FLOW_ROW_WRAP_REVERSE) || (flow == LV_FLEX_FLOW_ROW))
    {
        lv_obj_set_style_pad_row(myobj, 1, LV_PART_MAIN);
    }
    else
    {
        lv_obj_set_style_pad_column(myobj, 1, LV_PART_MAIN);
    }
    return 0;
}

int LvcppObject::set_style_base_dir(lv_base_dir_t value, lv_style_selector_t selector)
{
    lv_obj_set_style_base_dir(myobj, value, selector);

    return 0;
}

int LvcppObject::set_align_mode(lv_align_t align)
{
    lv_obj_set_align(myobj, align);

    return 0;
}



int LvcppObject::set_style_radius(lv_coord_t value, lv_style_selector_t selector)
{
    lv_obj_set_style_radius(myobj, value, selector);

    return 0;
}

int LvcppObject::set_style_border_style(lv_coord_t width, lv_color_t color, lv_opa_t opa, lv_style_selector_t selector)
{
    lv_obj_set_style_border_width(myobj, width, selector);
    lv_obj_set_style_border_color(myobj, color, selector);
    lv_obj_set_style_border_opa(myobj, opa, selector);

    return 0;
}

int LvcppObject::set_style_shadow_width(lv_coord_t value, lv_style_selector_t selector)
{
    lv_obj_set_style_shadow_width(myobj, value, selector);

    return 0;
}

int LvcppObject::set_style_bg_img_src(const void * filepath, lv_style_selector_t selector)
{
    lv_obj_set_style_bg_img_src(myobj,filepath, selector);
    return 0;
}

int LvcppObject::set_style_bg_color(lv_color_t value, lv_opa_t opa, lv_style_selector_t selector)
{
    lv_obj_set_style_bg_color(myobj, value, selector);
    lv_obj_set_style_bg_opa(myobj, opa, selector);
    return 0;
}

int LvcppObject::set_style_pad_L_R(lv_coord_t left_value, lv_coord_t right_value, lv_style_selector_t selector)
{
    lv_obj_set_style_pad_left(myobj, left_value, selector);
    lv_obj_set_style_pad_right(myobj, right_value, selector);
    return 0;
}

int LvcppObject::set_style_pad_T_B(lv_coord_t top_value, lv_coord_t bottom_value, lv_style_selector_t selector)
{
    lv_obj_set_style_pad_top(myobj, top_value, selector);
    lv_obj_set_style_pad_bottom(myobj, bottom_value, selector);
    return 0;
}

int LvcppObject::set_style_pad_all(lv_coord_t value, lv_style_selector_t selector)
{
    lv_obj_set_style_pad_all(myobj, value, selector);
    return 0;
}

int LvcppObject::set_style_pad_column(lv_coord_t value, lv_style_selector_t selector)
{
    lv_obj_set_style_pad_column(myobj, value, selector);
    return 0;
}

int LvcppObject::set_style_pad_row(lv_coord_t value, lv_style_selector_t selector)
{
    lv_obj_set_style_pad_row(myobj, value, selector);
    return 0;
}

int LvcppObject::set_style(lv_style_t* style, lv_style_selector_t selector)
{
    lv_obj_add_style(myobj, style, selector);
    return 0;
}


/////////////////////////////////get balue main style/////////////////////////////////////////
lv_coord_t LvcppObject::pos_x(void)
{
    return lv_obj_get_x(myobj);
}

lv_coord_t LvcppObject::pos_y(void)
{
    return lv_obj_get_y(myobj);
}

lv_coord_t LvcppObject::width(void)
{
    return lv_obj_get_width(myobj);
}

lv_coord_t LvcppObject::height(void)
{
    return lv_obj_get_height(myobj);
}

lv_coord_t LvcppObject::get_main_pad_left(void)
{
    return lv_obj_get_style_pad_left(myobj, LV_PART_MAIN);
}

lv_coord_t LvcppObject::get_main_pad_right(void)
{
    return lv_obj_get_style_pad_right(myobj, LV_PART_MAIN);
}

lv_coord_t LvcppObject::get_main_pad_top(void)
{
    return lv_obj_get_style_pad_top(myobj, LV_PART_MAIN);
}

lv_coord_t LvcppObject::get_main_pad_bottom(void)
{
    return lv_obj_get_style_pad_bottom(myobj, LV_PART_MAIN);
}

lv_coord_t LvcppObject::get_main_text_letter_space(void)
{
    return lv_obj_get_style_text_letter_space(myobj, LV_PART_MAIN);
}

lv_coord_t LvcppObject::get_main_text_line_space(void)
{
    return lv_obj_get_style_text_line_space(myobj, LV_PART_MAIN);
}

const lv_font_t* LvcppObject::get_main_text_font(void)
{
    return lv_obj_get_style_text_font(myobj, LV_PART_MAIN);
}

lv_coord_t LvcppObject::get_main_min_height(void)
{
    return lv_obj_get_style_min_height(myobj, LV_PART_MAIN);
}

lv_coord_t LvcppObject::get_main_max_height(void)
{
    return lv_obj_get_style_max_height(myobj, LV_PART_MAIN);
}

lv_coord_t LvcppObject::get_main_min_width(void)
{
    return lv_obj_get_style_min_width(myobj, LV_PART_MAIN);
}

lv_coord_t LvcppObject::get_main_max_width(void)
{
    return lv_obj_get_style_max_width(myobj, LV_PART_MAIN);
}
lv_align_t LvcppObject::get_main_align(void)
{
    return lv_obj_get_style_align(myobj, LV_PART_MAIN);
}
int LvcppObject::set_main_align(lv_align_t align)
{
    lv_obj_set_style_align(myobj, align, LV_PART_MAIN);
    return 0;
}

int LvcppObject::set_style_prop(lv_part_t part, lv_style_prop_t prop, lv_style_value_t value)
{
   LV_UNUSED(part);
   lv_obj_set_local_style_prop(myobj, prop, value, _LV_STYLE_STATE_CMP_SAME);
   return 0;
}

lv_style_value_t LvcppObject::get_style_prop(lv_part_t part, lv_style_prop_t prop)
{
    return lv_obj_get_style_prop(myobj, part, prop);
}

////////////////////////////set main area////////////////////////////////
int LvcppObject::set_main_base_dir(lv_base_dir_t value)
{
    lv_obj_set_style_base_dir(myobj, value, LV_PART_MAIN);

    return 0;
}

int LvcppObject::set_main_pad_column(lv_coord_t value)
{
    lv_obj_set_style_pad_column(myobj, value, LV_PART_MAIN);
    return 0;
}
int LvcppObject::set_main_pad_row(lv_coord_t value)
{
    lv_obj_set_style_pad_row(myobj, value, LV_PART_MAIN);
    return 0;
}

int LvcppObject::set_main_pad_L_R(lv_coord_t left_value, lv_coord_t right_value)
{
    lv_obj_set_style_pad_left(myobj, left_value, LV_PART_MAIN);
    lv_obj_set_style_pad_right(myobj, right_value, LV_PART_MAIN);
    return 0;
}

int LvcppObject::set_main_pad_T_B(lv_coord_t top_value, lv_coord_t bottom_value)
{
    lv_obj_set_style_pad_top(myobj, top_value, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(myobj, bottom_value, LV_PART_MAIN);
    return 0;
}
int LvcppObject::set_main_pad_all(lv_coord_t value)
{
    lv_obj_set_style_pad_all(myobj, value, LV_PART_MAIN);
    return 0;
}
int LvcppObject::set_main_border(lv_coord_t width, lv_color_t color, lv_opa_t opa)
{
    lv_obj_set_style_border_width(myobj, width, LV_PART_MAIN);
    lv_obj_set_style_border_color(myobj, color, LV_PART_MAIN);
    lv_obj_set_style_border_opa(myobj, opa, LV_PART_MAIN);
    return 0;
}
int LvcppObject::set_main_border_width(lv_coord_t width)
{
    lv_obj_set_style_border_width(myobj, width, LV_PART_MAIN);
    return 0;
}
int LvcppObject::set_main_border_color(lv_color_t color)
{
    lv_obj_set_style_border_color(myobj, color, LV_PART_MAIN);
    return 0;
}
int LvcppObject::set_main_outline_width(lv_coord_t width)
{
    lv_obj_set_style_outline_width(myobj, width, LV_PART_MAIN);
    return 0;
}

int LvcppObject::set_main_background(lv_color_t color, lv_opa_t opa)
{
    lv_obj_set_style_bg_color(myobj, color, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(myobj, opa, LV_PART_MAIN);
    return 0;
}

int LvcppObject::set_main_radius(lv_coord_t value)
{
    lv_obj_set_style_radius(myobj, value, LV_PART_MAIN);
    return 0;
}

int LvcppObject::set_main_shadow_width(lv_coord_t value)
{
    lv_obj_set_style_shadow_width(myobj, value, LV_PART_MAIN);
    return 0;
}

int LvcppObject::set_main_bg_img_src(const void * filepath)
{
    lv_obj_set_style_bg_img_src(myobj, filepath, LV_PART_MAIN);
    return 0;
}

int LvcppObject::set_main_bg_color(lv_color_t value, lv_opa_t opa)
{
    lv_obj_set_style_bg_color(myobj, value, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(myobj, opa, LV_PART_MAIN);
    return 0;
}

int LvcppObject::set_main_bg_opa(lv_opa_t opa)
{
    lv_obj_set_style_bg_opa(myobj, opa, LV_PART_MAIN);
    return 0;
}

/////////////////////////////////get value////////////////////////////////////////////////////
lv_coord_t LvcppObject::get_style_pos_x(lv_style_selector_t selector)
{
    return lv_obj_get_style_x(myobj, selector);
}

lv_coord_t LvcppObject::get_style_pos_y(lv_style_selector_t selector)
{
    return lv_obj_get_style_y(myobj, selector);
}

lv_coord_t LvcppObject::get_style_pad_left(lv_style_selector_t selector)
{
    return lv_obj_get_style_pad_left(myobj, selector);
}

lv_coord_t LvcppObject::get_style_pad_right(lv_style_selector_t selector)
{
    return lv_obj_get_style_pad_right(myobj, selector);
}

lv_coord_t LvcppObject::get_style_pad_top(lv_style_selector_t selector)
{
    return lv_obj_get_style_pad_top(myobj, selector);
}

lv_coord_t LvcppObject::get_style_pad_bottom(lv_style_selector_t selector)
{
    return lv_obj_get_style_pad_bottom(myobj, selector);
}

lv_coord_t LvcppObject::get_style_text_letter_space(lv_style_selector_t selector)
{
    return lv_obj_get_style_text_letter_space(myobj, selector);
}

lv_coord_t LvcppObject::get_style_text_line_space(lv_style_selector_t selector)
{
    return lv_obj_get_style_text_line_space(myobj, selector);
}

const lv_font_t* LvcppObject::get_style_text_font(lv_style_selector_t selector)
{
    return lv_obj_get_style_text_font(myobj, selector);
}

lv_coord_t LvcppObject::get_style_min_height(lv_style_selector_t selector)
{
    return lv_obj_get_style_min_height(myobj, selector);
}

lv_coord_t LvcppObject::get_style_max_height(lv_style_selector_t selector)
{
    return lv_obj_get_style_max_height(myobj, selector);
}

lv_coord_t LvcppObject::get_style_min_width(lv_style_selector_t selector)
{
    return lv_obj_get_style_min_width(myobj, selector);
}

lv_coord_t LvcppObject::get_style_max_width(lv_style_selector_t selector)
{
    return lv_obj_get_style_max_width(myobj, selector);
}

int LvcppObject::set_style_text_font(lv_font_t* font,lv_style_selector_t selector)
{
    lv_obj_set_style_text_font(myobj, font, selector);
	return 0;
}


int LvcppObject::set_style_clip_corner(bool value, lv_style_selector_t selector)
{
    lv_obj_set_style_clip_corner(myobj, value, selector);
    return 0;
}

int LvcppObject::set_style_transform_width(lv_coord_t value, lv_style_selector_t selector)
{
    lv_obj_set_style_transform_width(myobj,value,selector);
    return 0;
}

int LvcppObject::set_style_transform_height(lv_coord_t value, lv_style_selector_t selector)
{
    lv_obj_set_style_transform_height(myobj,value,selector);
    return 0;
}

int LvcppObject::set_style_translate_x(lv_coord_t value, lv_style_selector_t selector)
{
    lv_obj_set_style_translate_x(myobj,value,selector);
    return 0;
}

int LvcppObject::set_style_translate_y(lv_coord_t value, lv_style_selector_t selector)
{
    lv_obj_set_style_translate_y(myobj,value,selector);
    return 0;
}

int LvcppObject::set_style_transform_zoom(lv_coord_t value, lv_style_selector_t selector)
{
    lv_obj_set_style_transform_zoom(myobj,value,selector);
    return 0;
}

int LvcppObject::set_style_transform_angle(lv_coord_t value, lv_style_selector_t selector)
{
    lv_obj_set_style_transform_angle(myobj,value,selector);
    return 0;
}

int LvcppObject::set_style_transform_pivot_x(lv_coord_t value, lv_style_selector_t selector)
{
    lv_obj_set_style_transform_pivot_x(myobj,value,selector);
    return 0;
}

int LvcppObject::set_style_transform_pivot_y(lv_coord_t value, lv_style_selector_t selector)
{
    lv_obj_set_style_transform_pivot_y(myobj,value,selector);
    return 0;
}


int LvcppObject::add_event_cb(lv_event_cb_t event_cb, lv_event_code_t filter, void * cb_user_data)
{
    lv_obj_add_event_cb(myobj, event_cb, filter, cb_user_data);
    return 0;
}

int LvcppObject::remove_event_cb(lv_event_cb_t event_cb)
{
    lv_obj_remove_event_cb(myobj, event_cb);
    return 0;
}

int LvcppObject::apply_theme(void)
{
    lv_theme_apply(myobj);
    return 0;
}

lv_theme_t * LvcppObject::get_theme(void)
{
    return lv_theme_get_from_obj(myobj);
}

int LvcppObject::invalidate(void)
{
    lv_obj_invalidate(myobj);
    return 0;
}
