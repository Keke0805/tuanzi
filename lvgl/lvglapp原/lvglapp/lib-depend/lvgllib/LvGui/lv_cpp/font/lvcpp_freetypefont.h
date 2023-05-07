#ifndef LVCPP_FREETYPEFONT_H
#define LVCPP_FREETYPEFONT_H

#include  "lv_code/lvgl/lv_conf.h"
#include  "lv_cpp/include/lvcpp_sysconfig.h"
#include  "lv_code/lvgl/lvgl.h"
#include  "lv_code/lvgl/src/extra/libs/freetype/lv_freetype.h"

#define FT_FONT_CLASS  1

#if (LV_USE_FREETYPE == 1)
#if FT_FONT_CLASS
class LvcppFreeTypeFont
{
public:
    LvcppFreeTypeFont(int size ,int type);
    ~LvcppFreeTypeFont(void);

    lv_font_t* font(void);
    lv_font_t* resize(int size ,int type);

private:
    lv_font_t* myfont=nullptr;
    lv_ft_info_t ft_font;
};

#else
class LvcppFreeTypeFont
{
public:
     LvcppFreeTypeFont(void);
     ~LvcppFreeTypeFont(void);

    void font_destroy(lv_font_t * font);
    void set_weight(uint16_t weight);
    void set_style(uint16_t fontstyle);
    void set_tft_path(const char* ttf_path);
    int recreat(uint16_t weight,uint16_t type);
    lv_font_t* font_creat(uint16_t weight, uint16_t font_type);

    lv_font_t* myfont;

private:
    lv_ft_info_t ftfont;

};
#endif
#endif
#endif // LVCPP_FREETYPEFONT_H
