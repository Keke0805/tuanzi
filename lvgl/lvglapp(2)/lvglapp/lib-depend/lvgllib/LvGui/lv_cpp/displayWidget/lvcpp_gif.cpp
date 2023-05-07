#include "lvcpp_gif.h"

LvcppGif::LvcppGif(lv_obj_t* parent)
{
    myobj = lv_gif_create(parent);
}

LvcppGif::~LvcppGif(void)
{
    lv_obj_del(myobj);
}

int LvcppGif::set_src(const void * src)
{
    lv_gif_set_src(myobj, src);
    return 0;
}

int LvcppGif::restart(void)
{
    lv_gif_restart(myobj);
    return 0;
}

