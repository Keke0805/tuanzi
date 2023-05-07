#include "lvcpp_keyboard.h"
#include "src/custom/chinese_ime/chinese_ime.h"

LvcppKeyboard::LvcppKeyboard(lv_obj_t* parent)
{
    //myobj = lv_keyboard_create(parent);
    myobj = lv_chinese_ime_create(parent);
}

LvcppKeyboard::~LvcppKeyboard(void)
{
    lv_chinese_ime_del();
}

int LvcppKeyboard::set_dict(const char * dict)
{
    lv_chinese_ime_set_dict(dict);
    return 0;
}

int LvcppKeyboard::set_text_font(const lv_font_t * value, lv_style_selector_t selector)
{
    lv_chinese_ime_set_text_font(value, selector);
    return 0;
}

int LvcppKeyboard::set_textarea(lv_obj_t * ta)
{
    lv_keyboard_set_textarea(myobj,ta);
    return 0;
}

int LvcppKeyboard::set_mode(uint8_t mode)
{
    lv_keyboard_set_mode(myobj,mode);
    return 0;
}

int LvcppKeyboard::set_popovers(bool en)
{
    lv_keyboard_set_popovers(myobj,en);
    return 0;
}

lv_obj_t * LvcppKeyboard::get_textarea(void)
{
    return lv_keyboard_get_textarea(myobj);
}


bool LvcppKeyboard::get_mode(void)
{
    return lv_keyboard_get_mode(myobj);
}

bool LvcppKeyboard::get_popovers(void)
{
    return lv_btnmatrix_get_popovers(myobj);
}
