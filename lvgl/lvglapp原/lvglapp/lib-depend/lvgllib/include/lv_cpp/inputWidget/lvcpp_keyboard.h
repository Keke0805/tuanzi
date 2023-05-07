#ifndef LVCPP_KEYBOARD_H
#define LVCPP_KEYBOARD_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

class LvcppKeyboard : public LvcppObject
{
public:
    LvcppKeyboard(lv_obj_t* parent = nullptr);
    ~LvcppKeyboard(void);

    //set
    int set_textarea(lv_obj_t * ta);
    int set_mode(uint8_t mode);
    int set_popovers(bool en);
    int set_dict(const char * dict);
    int set_text_font(const lv_font_t * value, lv_style_selector_t selector);

    //get
    bool get_mode(void);
    bool get_popovers(void);
    lv_obj_t * get_textarea(void);

};

#endif // LVCPP_KEYBOARD_H
