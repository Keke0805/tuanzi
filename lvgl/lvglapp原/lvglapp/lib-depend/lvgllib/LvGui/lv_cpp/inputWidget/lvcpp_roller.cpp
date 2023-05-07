#include "lvcpp_roller.h"

LvcppRoller::LvcppRoller(lv_obj_t* parent)
{
    myobj = lv_roller_create(parent);
}

LvcppRoller::~LvcppRoller(void)
{

}

int LvcppRoller::set_options(const char * options, lv_roller_mode_t mode)
{
    lv_roller_set_options(myobj, options, mode);
    return 0;
}

int LvcppRoller::set_selected(uint16_t sel_opt, lv_anim_enable_t anim)
{
    lv_roller_set_selected(myobj, sel_opt, anim);
    return 0;
}

int LvcppRoller::set_visible_row_count(uint8_t row_cnt)
{
    lv_roller_set_visible_row_count(myobj, row_cnt);
    return 0;
}

uint16_t LvcppRoller::get_selected()
{
    return lv_roller_get_selected(myobj);
}

int LvcppRoller::get_selected_str(char * buf, uint32_t buf_size)
{

    lv_roller_get_selected_str(myobj, buf, buf_size);
    return 0;
}

const char * LvcppRoller::get_options()
{
    return lv_roller_get_options(myobj);

}

uint16_t LvcppRoller::get_option_cnt()
{
    return lv_roller_get_option_cnt(myobj);
}
