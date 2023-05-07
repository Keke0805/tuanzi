/**
 * @file lv_font_freetype_default.c
 */

/*********************
 *      INCLUDES
 *********************/

#include "lvgl/lvgl.h"

lv_font_t dotarray_font;

lv_font_t* get_dotarray_font(void)
{
    return &dotarray_font;
}

lv_font_t* init_dotarray_font(DOTARRAY_FONT_T type)
{
    switch(type)
    {
#if LV_FONT_MONTSERRAT_8
       case DOTARRAY_MONTSERRAT_8:
            dotarray_font = lv_font_montserrat_8;
            break;
#endif

#if LV_FONT_MONTSERRAT_10
    case DOTARRAY_MONTSERRAT_10:
         dotarray_font = lv_font_montserrat_10;
         break;
#endif

#if LV_FONT_MONTSERRAT_12
    case DOTARRAY_MONTSERRAT_12:
         dotarray_font = lv_font_montserrat_12;
         break;
#endif

#if LV_FONT_MONTSERRAT_14
    case  DOTARRAY_MONTSERRAT_14:
         dotarray_font = lv_font_montserrat_14;
         break;
#endif

#if LV_FONT_MONTSERRAT_16
    case DOTARRAY_MONTSERRAT_16:
         dotarray_font = lv_font_montserrat_16;
         break;
#endif

#if LV_FONT_MONTSERRAT_18
    case DOTARRAY_MONTSERRAT_18:
         dotarray_font = lv_font_montserrat_18;
         break;
#endif

#if LV_FONT_MONTSERRAT_20
    case DOTARRAY_MONTSERRAT_20:
         dotarray_font = lv_font_montserrat_20;
         break;
#endif

#if LV_FONT_MONTSERRAT_22
    case DOTARRAY_MONTSERRAT_22:
         dotarray_font = lv_font_montserrat_22;
         break;
#endif

#if LV_FONT_MONTSERRAT_24
    case DOTARRAY_MONTSERRAT_24:
         dotarray_font = lv_font_montserrat_24;
         break;
#endif

#if LV_FONT_MONTSERRAT_26
    case DOTARRAY_MONTSERRAT_26:
         dotarray_font = lv_font_montserrat_26;
         break;
#endif

#if LV_FONT_MONTSERRAT_28
    case DOTARRAY_MONTSERRAT_28:
         dotarray_font = lv_font_montserrat_28;
         break;
#endif

#if LV_FONT_MONTSERRAT_30
    case DOTARRAY_MONTSERRAT_30:
         dotarray_font = lv_font_montserrat_30;
         break;
#endif

#if LV_FONT_MONTSERRAT_32
    case DOTARRAY_MONTSERRAT_32:
         dotarray_font = lv_font_montserrat_32;
         break;
#endif

#if LV_FONT_MONTSERRAT_34
    case DOTARRAY_MONTSERRAT_34:
         dotarray_font = lv_font_montserrat_34;
         break;
#endif

#if LV_FONT_MONTSERRAT_36
    case DOTARRAY_MONTSERRAT_36:
         dotarray_font = lv_font_montserrat_36;
         break;
#endif

#if LV_FONT_MONTSERRAT_38
    case DOTARRAY_MONTSERRAT_38:
         dotarray_font = lv_font_montserrat_38;
         break;
#endif

#if LV_FONT_MONTSERRAT_40
    case DOTARRAY_MONTSERRAT_40:
         dotarray_font = lv_font_montserrat_40;
         break;
#endif

#if LV_FONT_MONTSERRAT_42
    case DOTARRAY_MONTSERRAT_42:
         dotarray_font = lv_font_montserrat_42;
         break;
#endif

#if LV_FONT_MONTSERRAT_44
    case DOTARRAY_MONTSERRAT_44:
         dotarray_font = lv_font_montserrat_44;
         break;
#endif

#if LV_FONT_MONTSERRAT_46
    case DOTARRAY_MONTSERRAT_46:
         dotarray_font = lv_font_montserrat_46;
         break;
#endif

#if LV_FONT_MONTSERRAT_48
    case DOTARRAY_MONTSERRAT_48:
         dotarray_font = lv_font_montserrat_48;
         break;
#endif

#if LV_FONT_MONTSERRAT_12_SUBPX
    case DOTARRAY_MONTSERRAT_12_SUBPX:
         dotarray_font = lv_font_montserrat_12_subpx;
         break;
#endif

#if LV_FONT_MONTSERRAT_28_COMPRESSED
    case DOTARRAY_MONTSERRAT_28_COMPRESSED:
         dotarray_font = lv_font_montserrat_28_compressed;
         break;
#endif

#if LV_FONT_DEJAVU_16_PERSIAN_HEBREW
    case DOTARRAY_DEJAVU_16_PERSIAN_HEBREW:
         dotarray_font = lv_font_dejavu_16_persian_hebrew;
         break;
#endif

#if LV_FONT_SIMSUN_16_CJK
    case DOTARRAY_SIMSUN_16_CJK:
         dotarray_font = lv_font_simsun_16_cjk;
         break;
#endif

#if LV_FONT_UNSCII_8
    case DOTARRAY_UNSCII_8:
         dotarray_font = lv_font_unscii_8;
         break;
#endif

#if LV_FONT_UNSCII_16
    case DOTARRAY_UNSCII_16:
         dotarray_font = lv_font_unscii_16;
         break;
#endif

    default:
        dotarray_font = lv_font_montserrat_24;
        break;
    }

    return &dotarray_font;
}

