#include  "lvcpp_screen.h"

LvcppScreen::LvcppScreen(lv_obj_t* parent)
{
    myobj = lv_obj_create(parent);

    int scr_w = lv_obj_get_width(parent);
    int scr_h = lv_obj_get_height(parent);
    lv_obj_set_size(myobj,scr_w,scr_h);
    lv_obj_set_style_pad_all(myobj,0,LV_PART_MAIN);
    lv_obj_set_style_radius(myobj,0,LV_PART_MAIN);
    lv_obj_set_style_border_width(myobj,0,LV_PART_MAIN);
    lv_obj_set_style_shadow_width(myobj,0,LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(myobj,0);

    lv_obj_clear_flag(myobj,LV_OBJ_FLAG_SCROLLABLE);
}

LvcppScreen::~LvcppScreen(void)
{
    if(logo != NULL)
    {
        lv_obj_del(logo);
        logo = NULL;
    }
}

lv_obj_t* LvcppScreen::get_screen(void)
{
    return myobj;
}

int LvcppScreen::set_bg_color(lv_color_t color, lv_opa_t opa)
{
    lv_obj_set_style_bg_color(myobj, color, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(myobj, opa, LV_PART_MAIN);
    return 0;
}

int LvcppScreen::showlogo(const char* pic, int pic_width, int pic_height, bool zoom)
{
    // png file
    if(logo != NULL) lv_obj_del(logo);
    logo = lv_img_create(myobj);
    lv_img_set_src(logo, pic);
    lv_obj_align(logo, LV_ALIGN_TOP_LEFT, 0, 0);

    if(zoom == 0)
    {
       lv_img_set_zoom(logo, LV_IMG_ZOOM_NONE);
    }
    else
    {
        int scr_w = lv_obj_get_width(myobj);
        int scr_h = lv_obj_get_height(myobj);
        if (pic_width != 0 && pic_height != 0)
        {
            uint32_t y_a= scr_h * pic_width;
            uint32_t x_b= scr_w * pic_height;

            if (x_b >= y_a)
            {
                if (pic_height >= scr_h)
                {
                    uint32_t x = scr_h * 256;
                    zoom = x / pic_height;
                    lv_img_set_zoom(myobj, zoom);
                }
            }
            else
            {
                if (pic_width > scr_w)
                {
                    uint32_t x = scr_w * 256;
                    zoom = x / pic_width;
                    lv_img_set_zoom(myobj, zoom);
                }
            }
        }
    }

    return 0;
}
