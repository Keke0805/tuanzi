#include "lvcpp_imagebutton.h"

LvcppImageButton::LvcppImageButton(lv_obj_t* parent)
{
    myobj = lv_imgbtn_create(parent);
}

LvcppImageButton::~LvcppImageButton()
{

}

int LvcppImageButton::set_imgbtn_src(lv_imgbtn_state_t state, const char* left_img, const char* mid_img,  const char* right_img)
{
    lv_imgbtn_set_src(myobj, state, left_img, mid_img, right_img);
    return 0;
}

int LvcppImageButton::set_imgbtn_state(lv_imgbtn_state_t state)
{
    lv_imgbtn_set_state(myobj, state);
    return 0;
}

const void* LvcppImageButton::get_src_left(lv_imgbtn_state_t state)
{

    return lv_imgbtn_get_src_left(myobj, state);
}

const void* LvcppImageButton::get_src_mid(lv_imgbtn_state_t state)
{

    return lv_imgbtn_get_src_middle(myobj, state);
}

const void* LvcppImageButton::get_src_right(lv_imgbtn_state_t state)
{

    return lv_imgbtn_get_src_right(myobj, state);
}

