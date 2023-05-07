#ifndef LVCPP_WINDOW_H
#define LVCPP_WINDOW_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

#define  DEFAULT_HEADER_HEIGHT  35

class LvcppWindow : public LvcppObject
{
public:
    LvcppWindow(lv_obj_t* parent = nullptr);
    ~LvcppWindow(void);

    //set
    lv_obj_t * add_title(const char * txt);
    lv_obj_t * add_btn(const void * icon, lv_coord_t btn_w);


    //get
    lv_obj_t * get_header(void);
    lv_obj_t * get_content(void);

};

#endif // LVCPP_WINDOW_H
