#ifndef LVCPP_QRCODE_H
#define LVCPP_QRCODE_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

#define  DARKED_COLOR    lv_color_hex3(0x000)
#define  LIGHT_COLOR     lv_color_hex3(0xfff)
#define  BACKGD_COLOR    lv_color_hex(0xffffff)

class LvcppQrcode : public LvcppObject
{
public:
    LvcppQrcode(lv_obj_t*);
    ~LvcppQrcode();

    //set
    int qrcode_creat(const char* data, int size,int pad);
    int update_data(const char* data);

private:
    lv_obj_t* qrcode;
};

#endif // LVCPP_QRCODE_H
