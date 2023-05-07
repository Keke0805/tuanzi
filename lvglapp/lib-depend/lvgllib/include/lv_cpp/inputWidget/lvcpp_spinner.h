#ifndef LVCPP_SPINNER_H
#define LVCPP_SPINNER_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

#define  DEFAULT_TIME_CYCLE  60
#define  DEFAULT_ARC_LENGTH  100

class LvcppSpinner : public LvcppObject
{
public:
    LvcppSpinner(lv_obj_t* parent = nullptr);
    ~LvcppSpinner(void);
};

#endif // LVCPP_SPINNER_H
