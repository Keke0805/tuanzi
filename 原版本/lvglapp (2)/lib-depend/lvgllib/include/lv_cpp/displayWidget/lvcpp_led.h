#ifndef LVCPP_LED_H
#define LVCPP_LED_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

class LvcppLED : public LvcppObject
{
public:
    LvcppLED(lv_obj_t* parent = nullptr);
    ~LvcppLED(void);

    //set
    int set_color(lv_color_t color);
    int set_brightness(uint8_t bright);
    int on(void);
    int off(void);
    int toggle(void);

    //get
    int get_brightness(void);


};

#endif // LVCPP_LED_H
