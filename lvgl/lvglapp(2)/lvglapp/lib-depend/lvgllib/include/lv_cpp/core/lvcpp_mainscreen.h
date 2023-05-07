#ifndef LVCPPMAINSCREEN_H
#define LVCPPMAINSCREEN_H

#include  "lvgl/lvgl.h"

class LvcppMainScreen
{
public:
    LvcppMainScreen(lv_coord_t width, lv_coord_t height, lv_obj_t* parent = nullptr);
    ~LvcppMainScreen(void);

    void background_color(lv_color_t color);
    void transparent(bool flag);
    int showlogo(const void* pic, int pic_width, int pic_height, bool zoom);
    lv_obj_t* get_obj(void) {return m_panel;}
    lv_size_t get_size(void);
	int add_event_cb(lv_event_cb_t event_cb, lv_event_code_t filter, void *);
    int remove_event_cb(lv_event_cb_t event_cb);
    void hide(bool flag);

private:
    lv_obj_t* m_panel;
    lv_obj_t* imglogo;
    lv_coord_t m_width, m_height;
};

#endif // LVCPPMAINSCREEN_H
