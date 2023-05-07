#ifndef LVCPP_ROLLER_H
#define LVCPP_ROLLER_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

class LvcppRoller : public LvcppObject
{
public:
    LvcppRoller(lv_obj_t* parent = nullptr);
    ~LvcppRoller(void);

    //set
    int set_options(const char * options, lv_roller_mode_t mode);
    int set_selected(uint16_t sel_opt, lv_anim_enable_t anim);
    int set_visible_row_count(uint8_t row_cnt);

    //get
    uint16_t get_selected(void);
    int get_selected_str(char * buf, uint32_t buf_size);
    const char * get_options(void);
    uint16_t get_option_cnt(void);
};

#endif // LVCPP_ROLLER_H
