#ifndef LVCPP_BMP_H
#define LVCPP_BMP_H

#include  "lv_code/lvgl/lvgl.h"

namespace LVGLIMAGE
{
    class lvcpp_bmp
    {
        public:
        static int encode(const uint8_t* rgbBytes, uint32_t width, uint32_t height, const char *filePath);
    };
}

#endif // LVCPP_BMP_H
