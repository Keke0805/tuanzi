#ifndef LVCPP_DOTARRAY_FONT_TTF_H
#define LVCPP_DOTARRAY_FONT_TTF_H

#include  "lvgl/src/font/lv_font.h"
#include  "../include/lvcpp_sysconfig.h"

class LvcppDotArrayFont
{
public:
    LvcppDotArrayFont(DOTARRAY_FONT_T type);
    ~LvcppDotArrayFont();

    lv_font_t* init_dotarray_font(DOTARRAY_FONT_T type);
    lv_font_t* get_font(void);

private:
    lv_font_t font;
};

#endif // LVCPP_FONT_TTF_H
