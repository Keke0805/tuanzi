#ifndef LVCPP_SCREEN_H
#define LVCPP_SCREEN_H

#include  "lvgl/lvgl.h"
#include  "lvcpp_object.h"

class LvcppScreen : public LvcppObject
{
public:
    LvcppScreen(lv_obj_t* parent = nullptr);
    ~LvcppScreen(void);

    int set_bg_color(lv_color_t color, lv_opa_t opa);
    int showlogo(const char* pic, int pic_width, int pic_height, bool zoom);
    lv_obj_t* get_screen(void);

private:

    lv_obj_t* logo = NULL;

};

#endif // LVCPP_SCREEN_H
