/**
 * @file lv_font_freetype_default.c
 */

/*********************
 *      INCLUDES
 *********************/

#include "lvgl/lvgl.h"

#if (LV_USE_FREETYPE == 1)

lv_ft_info_t ftfont_info;
const char* fontname;

LV_FT_FONT_STYLE check_font_type(int value)
{
    LV_FT_FONT_STYLE style;
    style = FT_FONT_STYLE_NORMAL;
    if(value == FT_FONT_STYLE_ITALIC) style = FT_FONT_STYLE_ITALIC;
    else if(value == FT_FONT_STYLE_BOLD) style = FT_FONT_STYLE_BOLD;


    return style;
}
lv_font_t* init_default_ttf(const char* path, lv_coord_t size, int type)
{
   fontname = path;
   ftfont_info.name = fontname;
   ftfont_info.weight = size;
   ftfont_info.style = check_font_type(type);
   lv_ft_font_init(&ftfont_info);

   return ftfont_info.font;
}

lv_font_t* get_freetype_font(void)
{
    return ftfont_info.font;
}

lv_font_t* change_font_size(lv_coord_t size, int type)
{
    lv_ft_font_destroy(ftfont_info.font);

    ftfont_info.name = fontname;
    ftfont_info.weight = size;
    ftfont_info.style = check_font_type(type);
    lv_ft_font_init(&ftfont_info);

    return ftfont_info.font;
}

#endif
