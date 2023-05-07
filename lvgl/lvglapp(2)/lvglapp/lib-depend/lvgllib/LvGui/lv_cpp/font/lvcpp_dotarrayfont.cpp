#include   "lvcpp_dotarrayfont.h"
#include   "lvgl/src/misc/lv_types.h"

LvcppDotArrayFont::LvcppDotArrayFont(DOTARRAY_FONT_T type)
{
    init_dotarray_font(type);
}

LvcppDotArrayFont::~LvcppDotArrayFont()
{

}

lv_font_t* LvcppDotArrayFont::init_dotarray_font(DOTARRAY_FONT_T type)
{
    switch(type)
    {
#if LV_FONT_MONTSERRAT_8
       case DOTARRAY_MONTSERRAT_8:
            font = lv_font_montserrat_8;
            break;
#endif

#if LV_FONT_MONTSERRAT_10
    case DOTARRAY_MONTSERRAT_10:
         font = lv_font_montserrat_10;
         break;
#endif

#if LV_FONT_MONTSERRAT_12
    case DOTARRAY_MONTSERRAT_12:
         font = lv_font_montserrat_12;
         break;
#endif

#if LV_FONT_MONTSERRAT_14
    case DOTARRAY_MONTSERRAT_14:
         font = lv_font_montserrat_14;
         break;
#endif

#if LV_FONT_MONTSERRAT_16
    case DOTARRAY_MONTSERRAT_16:
         font = lv_font_montserrat_16;
         break;
#endif

#if LV_FONT_MONTSERRAT_18
    case DOTARRAY_MONTSERRAT_18:
         font = lv_font_montserrat_18;
         break;
#endif

#if LV_FONT_MONTSERRAT_20
    case DOTARRAY_MONTSERRAT_20:
         font = lv_font_montserrat_20;
         break;
#endif

#if LV_FONT_MONTSERRAT_22
    case DOTARRAY_MONTSERRAT_22:
         font = lv_font_montserrat_22;
         break;
#endif

#if LV_FONT_MONTSERRAT_24
    case DOTARRAY_MONTSERRAT_24:
         font = lv_font_montserrat_24;
         break;
#endif

#if LV_FONT_MONTSERRAT_26
    case DOTARRAY_MONTSERRAT_26:
         font = lv_font_montserrat_26;
         break;
#endif

#if LV_FONT_MONTSERRAT_28
    case DOTARRAY_MONTSERRAT_28:
         font = lv_font_montserrat_28;
         break;
#endif

#if LV_FONT_MONTSERRAT_30
    case DOTARRAY_MONTSERRAT_30:
         font = lv_font_montserrat_30;
         break;
#endif

#if LV_FONT_MONTSERRAT_32
    case DOTARRAY_MONTSERRAT_32:
         font = lv_font_montserrat_32;
         break;
#endif

#if LV_FONT_MONTSERRAT_34
    case DOTARRAY_MONTSERRAT_34:
         font = lv_font_montserrat_34;
         break;
#endif

#if LV_FONT_MONTSERRAT_36
    case DOTARRAY_MONTSERRAT_36:
         font = lv_font_montserrat_36;
         break;
#endif

#if LV_FONT_MONTSERRAT_38
    case DOTARRAY_MONTSERRAT_38:
         font = lv_font_montserrat_38;
         break;
#endif

#if LV_FONT_MONTSERRAT_40
    case DOTARRAY_MONTSERRAT_40:
         font = lv_font_montserrat_40;
         break;
#endif

#if LV_FONT_MONTSERRAT_42
    case DOTARRAY_MONTSERRAT_42:
         font = lv_font_montserrat_42;
         break;
#endif

#if LV_FONT_MONTSERRAT_44
    case DOTARRAY_MONTSERRAT_44:
         font = lv_font_montserrat_44;
         break;
#endif

#if LV_FONT_MONTSERRAT_46
    case DOTARRAY_MONTSERRAT_46:
         font = lv_font_montserrat_46;
         break;
#endif

#if LV_FONT_MONTSERRAT_48
    case DOTARRAY_MONTSERRAT_48:
         font = lv_font_montserrat_48;
         break;
#endif

#if LV_FONT_MONTSERRAT_12_SUBPX
    case DOTARRAY_MONTSERRAT_12_SUBPX:
         font = lv_font_montserrat_12_subpx;
         break;
#endif

#if LV_FONT_MONTSERRAT_28_COMPRESSED
    case DOTARRAY_MONTSERRAT_28_COMPRESSED:
         font = lv_font_montserrat_28_compressed;
         break;
#endif

#if LV_FONT_DEJAVU_16_PERSIAN_HEBREW
    case DOTARRAY_DEJAVU_16_PERSIAN_HEBREW:
         font = lv_font_dejavu_16_persian_hebrew;
         break;
#endif

#if LV_FONT_SIMSUN_16_CJK
    case DOTARRAY_SIMSUN_16_CJK:
         font = lv_font_simsun_16_cjk;
         break;
#endif

#if LV_FONT_UNSCII_8
    case DOTARRAY_UNSCII_8:
         font = lv_font_unscii_8;
         break;
#endif

#if LV_FONT_UNSCII_16
    case DOTARRAY_UNSCII_16:
         font = lv_font_unscii_16;
         break;
#endif

    default:
        font = lv_font_montserrat_24;
        break;
    }

    return &font;
}

lv_font_t* LvcppDotArrayFont::get_font(void)
{
    return &font;
}
