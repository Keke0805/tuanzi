/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --no-compress --no-prefilter --bpp 1 --size 16 --font unscii-8.ttf -r 0x20-0x7F --format lvgl -o lv_font_unscii_16.c --force-fast-kern-format
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif

#ifndef LV_FONT_UNSCII_16
    #define LV_FONT_UNSCII_16 1
#endif

#if LV_FONT_UNSCII_16

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0x0, 0xff,

    /* U+0022 "\"" */
    0xf0, 0xff, 0xf, 0xf0, 0xff, 0xf, 0xf0, 0xff,
    0xf,

    /* U+0023 "#" */
    0x3c, 0xf0, 0xf3, 0xc3, 0xcf, 0xf, 0x3c, 0xff,
    0xff, 0xff, 0xf3, 0xcf, 0xf, 0x3c, 0xff, 0xff,
    0xff, 0xf3, 0xcf, 0xf, 0x3c, 0x3c, 0xf0, 0xf3,
    0xc0,

    /* U+0024 "$" */
    0xf, 0x0, 0xf0, 0x3f, 0xf3, 0xff, 0xf0, 0xf,
    0x0, 0x3f, 0xc3, 0xfc, 0x0, 0xf0, 0xf, 0xff,
    0xcf, 0xfc, 0xf, 0x0, 0xf0,

    /* U+0025 "%" */
    0xf0, 0x3f, 0xc0, 0xff, 0xf, 0x3c, 0x3c, 0x3,
    0xc0, 0xf, 0x0, 0xf0, 0x3, 0xc0, 0x3c, 0x3c,
    0xf0, 0xff, 0x3, 0xfc, 0xf,

    /* U+0026 "&" */
    0xf, 0xc0, 0x3f, 0x3, 0xcf, 0xf, 0x3c, 0xf,
    0xc0, 0x3f, 0x3, 0xf3, 0xcf, 0xcf, 0xf3, 0xf3,
    0xcf, 0xcf, 0xf, 0x3c, 0x3c, 0x3f, 0x3c, 0xfc,
    0xf0,

    /* U+0027 "'" */
    0x3c, 0xf3, 0xcf, 0xf3, 0xc0,

    /* U+0028 "(" */
    0xf, 0xf, 0x3c, 0x3c, 0xf0, 0xf0, 0xf0, 0xf0,
    0xf0, 0xf0, 0x3c, 0x3c, 0xf, 0xf,

    /* U+0029 ")" */
    0xf0, 0xf0, 0x3c, 0x3c, 0xf, 0xf, 0xf, 0xf,
    0xf, 0xf, 0x3c, 0x3c, 0xf0, 0xf0,

    /* U+002A "*" */
    0x3c, 0x3c, 0x3c, 0x3c, 0xf, 0xf0, 0xf, 0xf0,
    0xff, 0xff, 0xff, 0xff, 0xf, 0xf0, 0xf, 0xf0,
    0x3c, 0x3c, 0x3c, 0x3c,

    /* U+002B "+" */
    0xf, 0x0, 0xf0, 0xf, 0x0, 0xf0, 0xff, 0xff,
    0xff, 0xf, 0x0, 0xf0, 0xf, 0x0, 0xf0,

    /* U+002C "," */
    0x3c, 0xf3, 0xcf, 0xf3, 0xc0,

    /* U+002D "-" */
    0xff, 0xff, 0xff,

    /* U+002E "." */
    0xff, 0xff,

    /* U+002F "/" */
    0x0, 0xf, 0x0, 0xf, 0x0, 0x3c, 0x0, 0x3c,
    0x0, 0xf0, 0x0, 0xf0, 0x3, 0xc0, 0x3, 0xc0,
    0xf, 0x0, 0xf, 0x0, 0x3c, 0x0, 0x3c, 0x0,
    0xf0, 0x0, 0xf0, 0x0,

    /* U+0030 "0" */
    0x3f, 0xc3, 0xfc, 0xf0, 0xff, 0xf, 0xf3, 0xff,
    0x3f, 0xfc, 0xff, 0xcf, 0xf0, 0xff, 0xf, 0xf0,
    0xff, 0xf, 0x3f, 0xc3, 0xfc,

    /* U+0031 "1" */
    0xf, 0x0, 0xf0, 0x3f, 0x3, 0xf0, 0xf, 0x0,
    0xf0, 0xf, 0x0, 0xf0, 0xf, 0x0, 0xf0, 0xf,
    0x0, 0xf0, 0xff, 0xff, 0xff,

    /* U+0032 "2" */
    0x3f, 0xc3, 0xfc, 0xf0, 0xff, 0xf, 0x3, 0xc0,
    0x3c, 0xf, 0x0, 0xf0, 0x3c, 0x3, 0xc0, 0xf0,
    0xf, 0x0, 0xff, 0xff, 0xff,

    /* U+0033 "3" */
    0x3f, 0xc3, 0xfc, 0xf0, 0xff, 0xf, 0x0, 0xf0,
    0xf, 0xf, 0xc0, 0xfc, 0x0, 0xf0, 0xf, 0xf0,
    0xff, 0xf, 0x3f, 0xc3, 0xfc,

    /* U+0034 "4" */
    0x3, 0xf0, 0xf, 0xc0, 0xff, 0x3, 0xfc, 0x3c,
    0xf0, 0xf3, 0xcf, 0xf, 0x3c, 0x3c, 0xff, 0xff,
    0xff, 0xf0, 0xf, 0x0, 0x3c, 0x0, 0xf0, 0x3,
    0xc0,

    /* U+0035 "5" */
    0xff, 0xff, 0xff, 0xf0, 0xf, 0x0, 0xff, 0xcf,
    0xfc, 0x0, 0xf0, 0xf, 0x0, 0xf0, 0xf, 0xf0,
    0xff, 0xf, 0x3f, 0xc3, 0xfc,

    /* U+0036 "6" */
    0xf, 0xc0, 0xfc, 0x3c, 0x3, 0xc0, 0xf0, 0xf,
    0x0, 0xff, 0xcf, 0xfc, 0xf0, 0xff, 0xf, 0xf0,
    0xff, 0xf, 0x3f, 0xc3, 0xfc,

    /* U+0037 "7" */
    0xff, 0xff, 0xff, 0x0, 0xf0, 0xf, 0x0, 0xf0,
    0xf, 0x3, 0xc0, 0x3c, 0xf, 0x0, 0xf0, 0xf,
    0x0, 0xf0, 0xf, 0x0, 0xf0,

    /* U+0038 "8" */
    0x3f, 0xc3, 0xfc, 0xf0, 0xff, 0xf, 0xf0, 0xff,
    0xf, 0x3f, 0xc3, 0xfc, 0xf0, 0xff, 0xf, 0xf0,
    0xff, 0xf, 0x3f, 0xc3, 0xfc,

    /* U+0039 "9" */
    0x3f, 0xc3, 0xfc, 0xf0, 0xff, 0xf, 0xf0, 0xff,
    0xf, 0x3f, 0xf3, 0xff, 0x0, 0xf0, 0xf, 0x3,
    0xc0, 0x3c, 0x3f, 0x3, 0xf0,

    /* U+003A ":" */
    0xff, 0xff, 0x0, 0x0, 0xff, 0xff,

    /* U+003B ";" */
    0x3c, 0xf3, 0xcf, 0x0, 0x0, 0x0, 0x3c, 0xf3,
    0xcf, 0xf3, 0xc0,

    /* U+003C "<" */
    0x3, 0xc0, 0xf0, 0xf0, 0x3c, 0x3c, 0xf, 0xf,
    0x3, 0xc0, 0x3c, 0xf, 0x0, 0xf0, 0x3c, 0x3,
    0xc0, 0xf0,

    /* U+003D "=" */
    0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0xff, 0xff,
    0xff,

    /* U+003E ">" */
    0xf0, 0x3c, 0x3, 0xc0, 0xf0, 0xf, 0x3, 0xc0,
    0x3c, 0xf, 0xf, 0x3, 0xc3, 0xc0, 0xf0, 0xf0,
    0x3c, 0x0,

    /* U+003F "?" */
    0x3f, 0xc3, 0xfc, 0xf0, 0xff, 0xf, 0x0, 0xf0,
    0xf, 0x3, 0xc0, 0x3c, 0xf, 0x0, 0xf0, 0x0,
    0x0, 0x0, 0xf, 0x0, 0xf0,

    /* U+0040 "@" */
    0x3f, 0xf0, 0xff, 0xcf, 0x3, 0xfc, 0xf, 0xf3,
    0xff, 0xcf, 0xff, 0x3f, 0xfc, 0xff, 0xf3, 0xff,
    0xcf, 0xff, 0x0, 0x3c, 0x0, 0x3f, 0xf0, 0xff,
    0xc0,

    /* U+0041 "A" */
    0xf, 0x0, 0xf0, 0x3f, 0xc3, 0xfc, 0xf0, 0xff,
    0xf, 0xf0, 0xff, 0xf, 0xff, 0xff, 0xff, 0xf0,
    0xff, 0xf, 0xf0, 0xff, 0xf,

    /* U+0042 "B" */
    0xff, 0xcf, 0xfc, 0xf0, 0xff, 0xf, 0xf0, 0xff,
    0xf, 0xff, 0xcf, 0xfc, 0xf0, 0xff, 0xf, 0xf0,
    0xff, 0xf, 0xff, 0xcf, 0xfc,

    /* U+0043 "C" */
    0x3f, 0xc3, 0xfc, 0xf0, 0xff, 0xf, 0xf0, 0xf,
    0x0, 0xf0, 0xf, 0x0, 0xf0, 0xf, 0x0, 0xf0,
    0xff, 0xf, 0x3f, 0xc3, 0xfc,

    /* U+0044 "D" */
    0xff, 0xf, 0xf0, 0xf3, 0xcf, 0x3c, 0xf0, 0xff,
    0xf, 0xf0, 0xff, 0xf, 0xf0, 0xff, 0xf, 0xf3,
    0xcf, 0x3c, 0xff, 0xf, 0xf0,

    /* U+0045 "E" */
    0xff, 0xff, 0xff, 0xf0, 0xf, 0x0, 0xf0, 0xf,
    0x0, 0xff, 0xcf, 0xfc, 0xf0, 0xf, 0x0, 0xf0,
    0xf, 0x0, 0xff, 0xff, 0xff,

    /* U+0046 "F" */
    0xff, 0xff, 0xff, 0xf0, 0xf, 0x0, 0xf0, 0xf,
    0x0, 0xff, 0xcf, 0xfc, 0xf0, 0xf, 0x0, 0xf0,
    0xf, 0x0, 0xf0, 0xf, 0x0,

    /* U+0047 "G" */
    0x3f, 0xc3, 0xfc, 0xf0, 0xff, 0xf, 0xf0, 0xf,
    0x0, 0xf3, 0xff, 0x3f, 0xf0, 0xff, 0xf, 0xf0,
    0xff, 0xf, 0x3f, 0xf3, 0xff,

    /* U+0048 "H" */
    0xf0, 0xff, 0xf, 0xf0, 0xff, 0xf, 0xf0, 0xff,
    0xf, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xf, 0xf0,
    0xff, 0xf, 0xf0, 0xff, 0xf,

    /* U+0049 "I" */
    0xff, 0xff, 0xff, 0xf, 0x0, 0xf0, 0xf, 0x0,
    0xf0, 0xf, 0x0, 0xf0, 0xf, 0x0, 0xf0, 0xf,
    0x0, 0xf0, 0xff, 0xff, 0xff,

    /* U+004A "J" */
    0x0, 0xf0, 0xf, 0x0, 0xf0, 0xf, 0x0, 0xf0,
    0xf, 0x0, 0xf0, 0xf, 0x0, 0xf0, 0xf, 0xf0,
    0xff, 0xf, 0x3f, 0xc3, 0xfc,

    /* U+004B "K" */
    0xf0, 0x3f, 0xc0, 0xff, 0xf, 0x3c, 0x3c, 0xf3,
    0xc3, 0xcf, 0xf, 0xf0, 0x3f, 0xc0, 0xf3, 0xc3,
    0xcf, 0xf, 0xf, 0x3c, 0x3c, 0xf0, 0x3f, 0xc0,
    0xf0,

    /* U+004C "L" */
    0xf0, 0xf, 0x0, 0xf0, 0xf, 0x0, 0xf0, 0xf,
    0x0, 0xf0, 0xf, 0x0, 0xf0, 0xf, 0x0, 0xf0,
    0xf, 0x0, 0xff, 0xff, 0xff,

    /* U+004D "M" */
    0xf0, 0x3f, 0xc0, 0xff, 0xcf, 0xff, 0x3f, 0xff,
    0xff, 0xff, 0xff, 0x33, 0xfc, 0xcf, 0xf0, 0x3f,
    0xc0, 0xff, 0x3, 0xfc, 0xf, 0xf0, 0x3f, 0xc0,
    0xf0,

    /* U+004E "N" */
    0xf0, 0x3f, 0xc0, 0xff, 0xc3, 0xff, 0xf, 0xff,
    0x3f, 0xfc, 0xff, 0x3f, 0xfc, 0xff, 0xf0, 0xff,
    0xc3, 0xff, 0x3, 0xfc, 0xf, 0xf0, 0x3f, 0xc0,
    0xf0,

    /* U+004F "O" */
    0x3f, 0xc3, 0xfc, 0xf0, 0xff, 0xf, 0xf0, 0xff,
    0xf, 0xf0, 0xff, 0xf, 0xf0, 0xff, 0xf, 0xf0,
    0xff, 0xf, 0x3f, 0xc3, 0xfc,

    /* U+0050 "P" */
    0xff, 0xcf, 0xfc, 0xf0, 0xff, 0xf, 0xf0, 0xff,
    0xf, 0xff, 0xcf, 0xfc, 0xf0, 0xf, 0x0, 0xf0,
    0xf, 0x0, 0xf0, 0xf, 0x0,

    /* U+0051 "Q" */
    0x3f, 0xc3, 0xfc, 0xf0, 0xff, 0xf, 0xf0, 0xff,
    0xf, 0xf0, 0xff, 0xf, 0xf0, 0xff, 0xf, 0xf3,
    0xcf, 0x3c, 0x3c, 0xf3, 0xcf,

    /* U+0052 "R" */
    0xff, 0xcf, 0xfc, 0xf0, 0xff, 0xf, 0xf0, 0xff,
    0xf, 0xff, 0xcf, 0xfc, 0xf3, 0xcf, 0x3c, 0xf0,
    0xff, 0xf, 0xf0, 0xff, 0xf,

    /* U+0053 "S" */
    0x3f, 0xc3, 0xfc, 0xf0, 0xff, 0xf, 0xf0, 0xf,
    0x0, 0x3f, 0xc3, 0xfc, 0x0, 0xf0, 0xf, 0xf0,
    0xff, 0xf, 0x3f, 0xc3, 0xfc,

    /* U+0054 "T" */
    0xff, 0xff, 0xff, 0xf, 0x0, 0xf0, 0xf, 0x0,
    0xf0, 0xf, 0x0, 0xf0, 0xf, 0x0, 0xf0, 0xf,
    0x0, 0xf0, 0xf, 0x0, 0xf0,

    /* U+0055 "U" */
    0xf0, 0xff, 0xf, 0xf0, 0xff, 0xf, 0xf0, 0xff,
    0xf, 0xf0, 0xff, 0xf, 0xf0, 0xff, 0xf, 0xf0,
    0xff, 0xf, 0x3f, 0xc3, 0xfc,

    /* U+0056 "V" */
    0xf0, 0xff, 0xf, 0xf0, 0xff, 0xf, 0xf0, 0xff,
    0xf, 0xf0, 0xff, 0xf, 0xf0, 0xff, 0xf, 0x3f,
    0xc3, 0xfc, 0xf, 0x0, 0xf0,

    /* U+0057 "W" */
    0xf0, 0x3f, 0xc0, 0xff, 0x3, 0xfc, 0xf, 0xf0,
    0x3f, 0xc0, 0xff, 0x33, 0xfc, 0xcf, 0xff, 0xff,
    0xff, 0xff, 0xcf, 0xff, 0x3f, 0xf0, 0x3f, 0xc0,
    0xf0,

    /* U+0058 "X" */
    0xf0, 0xf, 0xf0, 0xf, 0x3c, 0x3c, 0x3c, 0x3c,
    0xf, 0xf0, 0xf, 0xf0, 0x3, 0xc0, 0x3, 0xc0,
    0xf, 0xf0, 0xf, 0xf0, 0x3c, 0x3c, 0x3c, 0x3c,
    0xf0, 0xf, 0xf0, 0xf,

    /* U+0059 "Y" */
    0xf0, 0xf, 0xf0, 0xf, 0x3c, 0x3c, 0x3c, 0x3c,
    0xf, 0xf0, 0xf, 0xf0, 0x3, 0xc0, 0x3, 0xc0,
    0x3, 0xc0, 0x3, 0xc0, 0x3, 0xc0, 0x3, 0xc0,
    0x3, 0xc0, 0x3, 0xc0,

    /* U+005A "Z" */
    0xff, 0xff, 0xff, 0x0, 0xf0, 0xf, 0x3, 0xc0,
    0x3c, 0xf, 0x0, 0xf0, 0x3c, 0x3, 0xc0, 0xf0,
    0xf, 0x0, 0xff, 0xff, 0xff,

    /* U+005B "[" */
    0xff, 0xff, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
    0xf0, 0xf0, 0xf0, 0xf0, 0xff, 0xff,

    /* U+005C "\\" */
    0xf0, 0x0, 0xf0, 0x0, 0x3c, 0x0, 0x3c, 0x0,
    0xf, 0x0, 0xf, 0x0, 0x3, 0xc0, 0x3, 0xc0,
    0x0, 0xf0, 0x0, 0xf0, 0x0, 0x3c, 0x0, 0x3c,
    0x0, 0xf, 0x0, 0xf,

    /* U+005D "]" */
    0xff, 0xff, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf,
    0xf, 0xf, 0xf, 0xf, 0xff, 0xff,

    /* U+005E "^" */
    0x3, 0x0, 0xc, 0x0, 0xfc, 0x3, 0xf0, 0x3c,
    0xf0, 0xf3, 0xcf, 0x3, 0xfc, 0xf,

    /* U+005F "_" */
    0xff, 0xff, 0xff, 0xff,

    /* U+0060 "`" */
    0xf0, 0xf0, 0x3c, 0x3c, 0xf, 0xf,

    /* U+0061 "a" */
    0x3f, 0xc3, 0xfc, 0x0, 0xf0, 0xf, 0x3f, 0xf3,
    0xff, 0xf0, 0xff, 0xf, 0x3f, 0xf3, 0xff,

    /* U+0062 "b" */
    0xf0, 0xf, 0x0, 0xf0, 0xf, 0x0, 0xff, 0xcf,
    0xfc, 0xf0, 0xff, 0xf, 0xf0, 0xff, 0xf, 0xf0,
    0xff, 0xf, 0xff, 0xcf, 0xfc,

    /* U+0063 "c" */
    0x3f, 0xcf, 0xff, 0x3, 0xc0, 0xf0, 0x3c, 0xf,
    0x3, 0xc0, 0x3f, 0xcf, 0xf0,

    /* U+0064 "d" */
    0x0, 0xf0, 0xf, 0x0, 0xf0, 0xf, 0x3f, 0xf3,
    0xff, 0xf0, 0xff, 0xf, 0xf0, 0xff, 0xf, 0xf0,
    0xff, 0xf, 0x3f, 0xf3, 0xff,

    /* U+0065 "e" */
    0x3f, 0xc3, 0xfc, 0xf0, 0xff, 0xf, 0xff, 0xff,
    0xff, 0xf0, 0xf, 0x0, 0x3f, 0xc3, 0xfc,

    /* U+0066 "f" */
    0xf, 0xc3, 0xf3, 0xc0, 0xf0, 0xff, 0xff, 0xf3,
    0xc0, 0xf0, 0x3c, 0xf, 0x3, 0xc0, 0xf0, 0x3c,
    0xf, 0x0,

    /* U+0067 "g" */
    0x3f, 0xf3, 0xff, 0xf0, 0xff, 0xf, 0xf0, 0xff,
    0xf, 0x3f, 0xf3, 0xff, 0x0, 0xf0, 0xf, 0xff,
    0xcf, 0xfc,

    /* U+0068 "h" */
    0xf0, 0xf, 0x0, 0xf0, 0xf, 0x0, 0xff, 0xcf,
    0xfc, 0xf0, 0xff, 0xf, 0xf0, 0xff, 0xf, 0xf0,
    0xff, 0xf, 0xf0, 0xff, 0xf,

    /* U+0069 "i" */
    0x3c, 0xf, 0x0, 0x0, 0x0, 0xfc, 0x3f, 0x3,
    0xc0, 0xf0, 0x3c, 0xf, 0x3, 0xc0, 0xf0, 0x3f,
    0xcf, 0xf0,

    /* U+006A "j" */
    0x3, 0xc0, 0xf0, 0x0, 0x0, 0x3, 0xc0, 0xf0,
    0x3c, 0xf, 0x3, 0xc0, 0xf0, 0x3c, 0xf, 0x3,
    0xc0, 0xff, 0xf3, 0xfc,

    /* U+006B "k" */
    0xf0, 0xf, 0x0, 0xf0, 0xf, 0x0, 0xf0, 0xff,
    0xf, 0xf3, 0xcf, 0x3c, 0xff, 0xf, 0xf0, 0xf3,
    0xcf, 0x3c, 0xf0, 0xff, 0xf,

    /* U+006C "l" */
    0xfc, 0x3f, 0x3, 0xc0, 0xf0, 0x3c, 0xf, 0x3,
    0xc0, 0xf0, 0x3c, 0xf, 0x3, 0xc0, 0xf0, 0x3f,
    0xcf, 0xf0,

    /* U+006D "m" */
    0xf0, 0xf3, 0xc3, 0xcf, 0xff, 0xff, 0xff, 0xf3,
    0x3f, 0xcc, 0xff, 0x33, 0xfc, 0xcf, 0xf0, 0x3f,
    0xc0, 0xf0,

    /* U+006E "n" */
    0xff, 0xcf, 0xfc, 0xf0, 0xff, 0xf, 0xf0, 0xff,
    0xf, 0xf0, 0xff, 0xf, 0xf0, 0xff, 0xf,

    /* U+006F "o" */
    0x3f, 0xc3, 0xfc, 0xf0, 0xff, 0xf, 0xf0, 0xff,
    0xf, 0xf0, 0xff, 0xf, 0x3f, 0xc3, 0xfc,

    /* U+0070 "p" */
    0xff, 0xcf, 0xfc, 0xf0, 0xff, 0xf, 0xf0, 0xff,
    0xf, 0xff, 0xcf, 0xfc, 0xf0, 0xf, 0x0, 0xf0,
    0xf, 0x0,

    /* U+0071 "q" */
    0x3f, 0xf3, 0xff, 0xf0, 0xff, 0xf, 0xf0, 0xff,
    0xf, 0x3f, 0xf3, 0xff, 0x0, 0xf0, 0xf, 0x0,
    0xf0, 0xf,

    /* U+0072 "r" */
    0xff, 0xcf, 0xfc, 0xf0, 0xff, 0xf, 0xf0, 0xf,
    0x0, 0xf0, 0xf, 0x0, 0xf0, 0xf, 0x0,

    /* U+0073 "s" */
    0x3f, 0xf3, 0xff, 0xf0, 0xf, 0x0, 0x3f, 0xc3,
    0xfc, 0x0, 0xf0, 0xf, 0xff, 0xcf, 0xfc,

    /* U+0074 "t" */
    0x3c, 0x3, 0xc0, 0x3c, 0x3, 0xc0, 0xff, 0xff,
    0xff, 0x3c, 0x3, 0xc0, 0x3c, 0x3, 0xc0, 0x3c,
    0x3, 0xc0, 0xf, 0xf0, 0xff,

    /* U+0075 "u" */
    0xf0, 0xff, 0xf, 0xf0, 0xff, 0xf, 0xf0, 0xff,
    0xf, 0xf0, 0xff, 0xf, 0x3f, 0xf3, 0xff,

    /* U+0076 "v" */
    0xf0, 0xff, 0xf, 0xf0, 0xff, 0xf, 0xf0, 0xff,
    0xf, 0x3f, 0xc3, 0xfc, 0xf, 0x0, 0xf0,

    /* U+0077 "w" */
    0xf0, 0x3f, 0xc0, 0xff, 0x3, 0xfc, 0xf, 0xf3,
    0x3f, 0xcc, 0xf3, 0xff, 0xf, 0xfc, 0x3c, 0xf0,
    0xf3, 0xc0,

    /* U+0078 "x" */
    0xf0, 0x3f, 0xc0, 0xf3, 0xcf, 0xf, 0x3c, 0xf,
    0xc0, 0x3f, 0x3, 0xcf, 0xf, 0x3c, 0xf0, 0x3f,
    0xc0, 0xf0,

    /* U+0079 "y" */
    0xf0, 0xff, 0xf, 0xf0, 0xff, 0xf, 0xf0, 0xff,
    0xf, 0x3f, 0xf3, 0xff, 0x0, 0xf0, 0xf, 0x3f,
    0xc3, 0xfc,

    /* U+007A "z" */
    0xff, 0xff, 0xff, 0x3, 0xc0, 0x3c, 0xf, 0x0,
    0xf0, 0x3c, 0x3, 0xc0, 0xff, 0xff, 0xff,

    /* U+007B "{" */
    0x3, 0xf0, 0x3f, 0xf, 0x0, 0xf0, 0xf, 0x0,
    0xf0, 0xfc, 0xf, 0xc0, 0xf, 0x0, 0xf0, 0xf,
    0x0, 0xf0, 0x3, 0xf0, 0x3f,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,

    /* U+007D "}" */
    0xfc, 0xf, 0xc0, 0xf, 0x0, 0xf0, 0xf, 0x0,
    0xf0, 0x3, 0xf0, 0x3f, 0xf, 0x0, 0xf0, 0xf,
    0x0, 0xf0, 0xfc, 0xf, 0xc0,

    /* U+007E "~" */
    0x3f, 0x3c, 0xfc, 0xff, 0x3f, 0x3c, 0xfc,

    /* U+007F "" */
    0xf0, 0x3, 0xc0, 0xc, 0xc0, 0x33, 0x0, 0xcc,
    0xff, 0x33, 0xfc, 0xc3, 0x33, 0xc, 0xf0, 0x33,
    0xc0, 0xc0, 0x3, 0x0, 0xc, 0x0, 0x30, 0x0,
    0xc0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 256, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 16},
    {.bitmap_index = 1, .adv_w = 256, .box_w = 4, .box_h = 14, .ofs_x = 6, .ofs_y = 2},
    {.bitmap_index = 8, .adv_w = 256, .box_w = 12, .box_h = 6, .ofs_x = 2, .ofs_y = 10},
    {.bitmap_index = 17, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 42, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 63, .adv_w = 256, .box_w = 14, .box_h = 12, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 84, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 109, .adv_w = 256, .box_w = 6, .box_h = 6, .ofs_x = 4, .ofs_y = 10},
    {.bitmap_index = 114, .adv_w = 256, .box_w = 8, .box_h = 14, .ofs_x = 4, .ofs_y = 2},
    {.bitmap_index = 128, .adv_w = 256, .box_w = 8, .box_h = 14, .ofs_x = 4, .ofs_y = 2},
    {.bitmap_index = 142, .adv_w = 256, .box_w = 16, .box_h = 10, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 162, .adv_w = 256, .box_w = 12, .box_h = 10, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 177, .adv_w = 256, .box_w = 6, .box_h = 6, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 182, .adv_w = 256, .box_w = 12, .box_h = 2, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 185, .adv_w = 256, .box_w = 4, .box_h = 4, .ofs_x = 6, .ofs_y = 2},
    {.bitmap_index = 187, .adv_w = 256, .box_w = 16, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 215, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 236, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 257, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 278, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 299, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 324, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 345, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 366, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 387, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 408, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 429, .adv_w = 256, .box_w = 4, .box_h = 12, .ofs_x = 6, .ofs_y = 2},
    {.bitmap_index = 435, .adv_w = 256, .box_w = 6, .box_h = 14, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 446, .adv_w = 256, .box_w = 10, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 464, .adv_w = 256, .box_w = 12, .box_h = 6, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 473, .adv_w = 256, .box_w = 10, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 491, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 512, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 537, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 558, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 579, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 600, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 621, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 642, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 663, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 684, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 705, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 726, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 747, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 772, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 793, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 818, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 843, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 864, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 885, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 906, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 927, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 948, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 969, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 990, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1011, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1036, .adv_w = 256, .box_w = 16, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1064, .adv_w = 256, .box_w = 16, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1092, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1113, .adv_w = 256, .box_w = 8, .box_h = 14, .ofs_x = 4, .ofs_y = 2},
    {.bitmap_index = 1127, .adv_w = 256, .box_w = 16, .box_h = 14, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1155, .adv_w = 256, .box_w = 8, .box_h = 14, .ofs_x = 4, .ofs_y = 2},
    {.bitmap_index = 1169, .adv_w = 256, .box_w = 14, .box_h = 8, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 1183, .adv_w = 256, .box_w = 16, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1187, .adv_w = 256, .box_w = 8, .box_h = 6, .ofs_x = 6, .ofs_y = 10},
    {.bitmap_index = 1193, .adv_w = 256, .box_w = 12, .box_h = 10, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1208, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1229, .adv_w = 256, .box_w = 10, .box_h = 10, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1242, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1263, .adv_w = 256, .box_w = 12, .box_h = 10, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1278, .adv_w = 256, .box_w = 10, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1296, .adv_w = 256, .box_w = 12, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1314, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1335, .adv_w = 256, .box_w = 10, .box_h = 14, .ofs_x = 4, .ofs_y = 2},
    {.bitmap_index = 1353, .adv_w = 256, .box_w = 10, .box_h = 16, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1373, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1394, .adv_w = 256, .box_w = 10, .box_h = 14, .ofs_x = 4, .ofs_y = 2},
    {.bitmap_index = 1412, .adv_w = 256, .box_w = 14, .box_h = 10, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1430, .adv_w = 256, .box_w = 12, .box_h = 10, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1445, .adv_w = 256, .box_w = 12, .box_h = 10, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1460, .adv_w = 256, .box_w = 12, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1478, .adv_w = 256, .box_w = 12, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1496, .adv_w = 256, .box_w = 12, .box_h = 10, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1511, .adv_w = 256, .box_w = 12, .box_h = 10, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1526, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1547, .adv_w = 256, .box_w = 12, .box_h = 10, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1562, .adv_w = 256, .box_w = 12, .box_h = 10, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1577, .adv_w = 256, .box_w = 14, .box_h = 10, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1595, .adv_w = 256, .box_w = 14, .box_h = 10, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1613, .adv_w = 256, .box_w = 12, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1631, .adv_w = 256, .box_w = 12, .box_h = 10, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1646, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1667, .adv_w = 256, .box_w = 4, .box_h = 14, .ofs_x = 6, .ofs_y = 2},
    {.bitmap_index = 1674, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1695, .adv_w = 256, .box_w = 14, .box_h = 4, .ofs_x = 0, .ofs_y = 12},
    {.bitmap_index = 1702, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = 2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] = {
    {
        .range_start = 32, .range_length = 96, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t lv_font_unscii_16 = {
#else
lv_font_t lv_font_unscii_16 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 17,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if LV_FONT_UNSCII_16*/

