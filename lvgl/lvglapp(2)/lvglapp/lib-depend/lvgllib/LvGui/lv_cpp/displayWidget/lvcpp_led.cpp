#include "lvcpp_led.h"

LvcppLED::LvcppLED(lv_obj_t* parent)
{
    myobj = lv_led_create(parent);
}

LvcppLED::~LvcppLED(void)
{

}

//set
int LvcppLED::set_color(lv_color_t color)
{
    lv_led_set_color(myobj, color);
    return 0;
}

int LvcppLED::set_brightness(uint8_t bright)
{
    lv_led_set_brightness(myobj, bright);
    return 0;
}

int LvcppLED::on(void)
{
    lv_led_on(myobj);
    return 0;
}

int LvcppLED::off(void)
{
    lv_led_off(myobj);
    return 0;
}

int LvcppLED::toggle(void)
{
    lv_led_toggle(myobj);
    return 0;
}


//get
int LvcppLED::get_brightness(void)
{

    return lv_led_get_brightness(myobj);;
}
