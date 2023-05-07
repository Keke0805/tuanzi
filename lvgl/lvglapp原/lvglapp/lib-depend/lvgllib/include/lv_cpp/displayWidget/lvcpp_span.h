#ifndef LVCPP_SPAN_H
#define LVCPP_SPAN_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

class LvcppSpan : public LvcppObject
{
public:
    LvcppSpan(lv_obj_t* parent = nullptr);
    ~LvcppSpan(void);

    //set
    lv_span_t * add_span(void);
    int del_span(lv_span_t * span);
    int set_text(lv_span_t * span, const char * text);
    int set_text_static(lv_span_t * span, const char * text);
    int set_align(lv_text_align_t align);
    int set_overflow(lv_span_overflow_t overflow);
    int set_indent(lv_coord_t indent);
    int set_mode(lv_span_mode_t mode);

    //get
    lv_span_t * get_child( int32_t id);
    int get_child_cnt(void);
    int get_align(void);
    int get_overflow(void);
    int get_indent(void);
    int get_mode(void);
    int refr_mode(void);
    int get_max_line_h(void);
    int get_expand_width(uint32_t max_width);
    int get_expand_height(lv_coord_t width);

private:
    lv_span_t* span;
};

#endif // LVCPP_SPAN_H
