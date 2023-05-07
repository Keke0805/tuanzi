#include  "lvcpp_freetypefont.h"


#if (LV_USE_FREETYPE == 1)
#if FT_FONT_CLASS
LvcppFreeTypeFont::LvcppFreeTypeFont(int size, int type)
{
    ft_font.name = DEFAULT_FONT_NAME;
    ft_font.weight = size;
    ft_font.style = type;
    ft_font.mem = nullptr;
    ft_font.mem_size = 0;
    lv_ft_font_init(&ft_font);
    myfont = ft_font.font;
}

LvcppFreeTypeFont::~LvcppFreeTypeFont(void)
{
    lv_ft_font_destroy(myfont);
}

lv_font_t* LvcppFreeTypeFont::font(void)
{
    return myfont;
}

lv_font_t* LvcppFreeTypeFont::resize(int size ,int type)
{
    lv_ft_font_destroy(myfont);
    ft_font.name = DEFAULT_FONT_NAME;
    ft_font.weight = size;
    ft_font.style = type;
    ft_font.mem = nullptr;
    ft_font.mem_size = 0;
    lv_ft_font_init(&ft_font);
    myfont = ft_font.font;
    return myfont;
}


#else
LvcppFreeTypeFont::LvcppFreeTypeFont()
{
    set_tft_path(DEFAULT_FONT_NAME);
    ftfont.weight = 24;
    ftfont.style = DEFAULT_FONT_TYPE;
    lv_ft_font_init(&ftfont);
    myfont = ftfont.font;
}


LvcppFreeTypeFont::~LvcppFreeTypeFont(void)
{
    font_destroy(myfont);
}

void LvcppFreeTypeFont::font_destroy(lv_font_t * font)
{
    lv_ft_font_destroy(font);
}

void LvcppFreeTypeFont::set_weight(uint16_t weight)
{
   ftfont.weight = weight;
}

void LvcppFreeTypeFont::set_style(uint16_t fontstyle)
{
   ftfont.style = fontstyle;
}

void LvcppFreeTypeFont::set_tft_path(const char* ttf_name)
{
    ftfont.name = ttf_name;
    LV_LOG_USER("user ttf type name=%s,-------",ftfont.name);
}

int LvcppFreeTypeFont::recreat(uint16_t weight, uint16_t font_type)
{
   font_destroy(ftfont.font);
   ftfont.weight = weight;
   ftfont.style = font_type;
   lv_ft_font_init(&ftfont);

   myfont = ftfont.font;
   return 0;
}

lv_font_t* LvcppFreeTypeFont::font_creat(uint16_t weight, uint16_t font_type)
{
    lv_ft_info_t font;
    font.weight = weight;
    font.style = font_type;
    font.name = ftfont.name;
    lv_ft_font_init(&font);

    return font.font;
}
#endif

#endif
