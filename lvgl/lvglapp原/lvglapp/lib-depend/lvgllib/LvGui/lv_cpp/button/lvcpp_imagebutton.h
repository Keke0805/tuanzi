#ifndef LVCPP_IMAGEBUTTON_H
#define LVCPP_IMAGEBUTTON_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

class LvcppImageButton : public LvcppObject
{
public:
    LvcppImageButton(lv_obj_t* parent = nullptr);
    ~LvcppImageButton();

    //set
    int set_imgbtn_src(lv_imgbtn_state_t, const char*, const char*,  const char* );
    int set_imgbtn_state(lv_imgbtn_state_t state);

    //get
    const void* get_src_left(lv_imgbtn_state_t);
    const void* get_src_right(lv_imgbtn_state_t);
    const void* get_src_mid(lv_imgbtn_state_t);
};

#endif // LVCPP_IMAGEBUTTON_H
