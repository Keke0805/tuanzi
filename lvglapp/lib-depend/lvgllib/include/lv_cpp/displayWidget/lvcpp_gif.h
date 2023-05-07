#ifndef LVCPP_GIF_H
#define LVCPP_GIF_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

class LvcppGif : public LvcppObject
{
public:
    LvcppGif(lv_obj_t* parent = nullptr);
    ~LvcppGif(void);

    //set
    int set_src(const void * src);
    int restart(void);

};

#endif // LVCPP_GIF_H
