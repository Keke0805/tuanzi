#ifndef LVCPP_SWITCH_H
#define LVCPP_SWITCH_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

class LvcppSwitch : public LvcppObject
{
public:
    LvcppSwitch(lv_obj_t* parent = nullptr);
    ~LvcppSwitch(void);
};

#endif // LVCPP_SWITCH_H
