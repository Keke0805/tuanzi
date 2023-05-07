#ifndef LVCPP_ANIMIMG_H
#define LVCPP_ANIMIMG_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

class LvcppAnimimg : public LvcppObject
{
public:
    LvcppAnimimg(lv_obj_t* parent=nullptr);
    ~LvcppAnimimg(void);

    //set
    int start(void);
    int set_src(lv_img_dsc_t * dsc[], uint8_t num);
    int set_duration(uint32_t duration);
    int set_repeat_count(uint16_t count);

    //get

};

#endif // LVCPP_ANIMIMG_H
