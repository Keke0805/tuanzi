#ifndef CLOCK_LIST_H
#define CLOCK_LIST_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "../include/configCustom.h"

class clockList
{
public:
    clockList(lv_obj_t* parent,void *patch);
    ~clockList(void);
    LvcppButton* btn=NULL;  
private:
};

#endif // CLOCK_LIST_H
