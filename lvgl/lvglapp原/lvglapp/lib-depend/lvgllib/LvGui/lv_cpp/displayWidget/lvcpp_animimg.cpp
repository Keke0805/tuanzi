#include "lvcpp_animimg.h"

LvcppAnimimg::LvcppAnimimg(lv_obj_t* parent)
{
    myobj = lv_animimg_create(parent);
}

LvcppAnimimg::~LvcppAnimimg(void)
{

}

//set
int LvcppAnimimg::start(void)
{
    lv_animimg_start(myobj);
    return 0;
}

int LvcppAnimimg::set_src(lv_img_dsc_t * dsc[], uint8_t num)
{
    lv_animimg_set_src(myobj, dsc, num);
    return 0;
}

int LvcppAnimimg::set_duration(uint32_t duration)
{
    lv_animimg_set_duration(myobj, duration);
    return 0;
}

int LvcppAnimimg::set_repeat_count(uint16_t count)
{
    lv_animimg_set_repeat_count(myobj, count);
    return 0;
}

//get
