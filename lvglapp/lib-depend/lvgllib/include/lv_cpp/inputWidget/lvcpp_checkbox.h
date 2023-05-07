#ifndef LVCPP_CHECKBOX_H
#define LVCPP_CHECKBOX_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

class LvcppCheckBox : public LvcppObject
{
public:
    LvcppCheckBox(lv_obj_t* parent = nullptr);
    ~LvcppCheckBox(void);

    //set
    int set_text(const char * txt);
    int set_text_static(const char * txt);

    //get
    const char * get_text(void);
};

#endif // LVCPP_CHECKBOX_H
