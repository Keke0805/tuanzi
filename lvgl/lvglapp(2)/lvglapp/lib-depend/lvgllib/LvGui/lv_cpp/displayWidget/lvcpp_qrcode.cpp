#include "lvcpp_qrcode.h"

LvcppQrcode::LvcppQrcode(lv_obj_t* parent)
{
   myobj = lv_obj_create(parent);
   qrcode = nullptr;
}

LvcppQrcode::~LvcppQrcode(void)
{
    if(qrcode != nullptr)
    {
       lv_obj_del(qrcode);
    }
}

int LvcppQrcode::update_data(const char* data)
{
    if(qrcode != nullptr)
    {
        lv_qrcode_update(qrcode, data, strlen(data));
    }
    else
    {
        int width,height,size;
        width = lv_obj_get_width(myobj);
        height = lv_obj_get_height(myobj);
        if(width>=height)
        {
            size = height;
        }
        else
        {
            size = width;
        }
        qrcode = lv_qrcode_create(myobj, size, DARKED_COLOR, LIGHT_COLOR);
        lv_qrcode_update(qrcode, data, strlen(data));
    }
    return 0;
}

int LvcppQrcode::qrcode_creat(const char* data, int size, int pad)
{
    lv_obj_set_size(myobj, size+pad, size+pad);
    lv_obj_set_style_pad_all(myobj, pad, 0);
    lv_obj_set_scrollbar_mode(myobj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(myobj, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_bg_color(myobj, BACKGD_COLOR, 0);
    if(qrcode == nullptr)
    {
        qrcode = lv_qrcode_create(myobj, size, DARKED_COLOR, LIGHT_COLOR);
        lv_obj_center(qrcode);
        lv_qrcode_update(qrcode, data, strlen(data));
    }
    else
    {
        lv_obj_center(qrcode);
        lv_qrcode_update(qrcode, data, strlen(data));
    }

    return 0;
}
