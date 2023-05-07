#include "lvcpp_span.h"

LvcppSpan::LvcppSpan(lv_obj_t* parent)
{
    myobj = lv_spangroup_create(parent);
}

LvcppSpan::~LvcppSpan(void)
{

}

//set
lv_span_t * LvcppSpan::add_span(void)
{
    return lv_spangroup_new_span(myobj);
}

int LvcppSpan::del_span(lv_span_t * span)
{
    lv_spangroup_del_span(myobj, span);
    return 0;
}

int LvcppSpan::set_text(lv_span_t * span, const char * text)
{
    lv_span_set_text(span, text);
    return 0;
}

int LvcppSpan::set_text_static(lv_span_t * span, const char * text)
{
    lv_span_set_text_static(span, text);
    return 0;
}

int LvcppSpan::set_align(lv_text_align_t align)
{
    lv_spangroup_set_align(myobj, align);
    return 0;
}

int LvcppSpan::set_overflow(lv_span_overflow_t overflow)
{
    lv_spangroup_set_overflow(myobj, overflow);
    return 0;
}

int LvcppSpan::set_indent(lv_coord_t indent)
{
    lv_spangroup_set_indent(myobj, indent);
    return 0;
}

int LvcppSpan::set_mode(lv_span_mode_t mode)
{
    lv_spangroup_set_mode(myobj, mode);
    return 0;
}


//get
lv_span_t * LvcppSpan::get_child( int32_t id)
{
    return lv_spangroup_get_child(myobj, id);
}

int LvcppSpan::get_child_cnt(void)
{
    return lv_spangroup_get_child_cnt(myobj);
}

int LvcppSpan::get_align(void)
{
    return lv_spangroup_get_align(myobj);
}

int LvcppSpan::get_overflow(void)
{
    return lv_spangroup_get_overflow(myobj);
}

int LvcppSpan::get_indent(void)
{
    return lv_spangroup_get_indent(myobj);
}

int LvcppSpan::get_mode(void)
{
    return lv_spangroup_get_mode(myobj);
}

int LvcppSpan::refr_mode(void)
{
    lv_spangroup_refr_mode(myobj);
    return 0;
}

int LvcppSpan::get_max_line_h(void)
{
    return lv_spangroup_get_max_line_h(myobj);
}

int LvcppSpan::get_expand_width(uint32_t max_width)
{
    return lv_spangroup_get_expand_width(myobj, max_width);
}

int LvcppSpan::get_expand_height(lv_coord_t width)
{
    return lv_spangroup_get_expand_height(myobj, width);
}

