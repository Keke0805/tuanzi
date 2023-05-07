#include "lvcpp_mainscreen.h"

LvcppMainScreen::LvcppMainScreen(lv_coord_t width, lv_coord_t height, lv_obj_t* parent)
{
    m_panel = lv_obj_create(parent);

    lv_obj_clear_flag(m_panel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_all(m_panel, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(m_panel, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(m_panel,0,LV_PART_MAIN);
    lv_obj_set_style_radius(m_panel,0,LV_PART_MAIN);
    lv_obj_set_style_border_width(m_panel,0,LV_PART_MAIN);
    lv_obj_set_style_shadow_width(m_panel,0,LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(m_panel,0);

    m_width = width;
    m_height = height;
    lv_obj_set_size(m_panel, m_width, m_height);

    imglogo = nullptr;
}

LvcppMainScreen::~LvcppMainScreen(void)
{
   lv_obj_del(m_panel);
}

void LvcppMainScreen::background_color(lv_color_t color)
{
    lv_obj_set_style_bg_color(m_panel, color, LV_PART_MAIN);
}
void LvcppMainScreen::transparent(bool flag)
{
    if(flag == true)
    {
       lv_obj_set_style_bg_opa(m_panel, LV_OPA_0, LV_PART_MAIN);
    }
    else
    {
      lv_obj_set_style_bg_opa(m_panel, LV_OPA_COVER, LV_PART_MAIN);
    }
}


void LvcppMainScreen::hide(bool flag)
{
    if(flag == true)
    {
       lv_obj_add_flag(m_panel, LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
      lv_obj_clear_flag(m_panel, LV_OBJ_FLAG_HIDDEN);
    }
}

lv_size_t LvcppMainScreen::get_size(void)
{
     lv_size_t size;
     size.width = m_width;
     size.height = m_height;

     return size;
}

int LvcppMainScreen::add_event_cb(lv_event_cb_t event_cb, lv_event_code_t filter, void * cb_user_data)
{
    lv_obj_add_event_cb(m_panel, event_cb, filter, cb_user_data);
    return 0;
}

int LvcppMainScreen::remove_event_cb(lv_event_cb_t event_cb)
{
    lv_obj_remove_event_cb(m_panel, event_cb);
    return 0;
}


int LvcppMainScreen::showlogo(const void* pic, int pic_width, int pic_height, bool zoom)
{
    // png file
    if(imglogo != NULL) lv_obj_del(imglogo);

    imglogo = lv_img_create(m_panel);
    lv_img_set_src(imglogo, pic);
    lv_obj_align(imglogo, LV_ALIGN_TOP_LEFT, 0, 0);

    if(zoom == 0)
    {
       lv_img_set_zoom(imglogo, LV_IMG_ZOOM_NONE);
    }
    else
    {
        int scr_w = lv_obj_get_width(m_panel);
        int scr_h = lv_obj_get_height(m_panel);
        float scale_s = (float)pic_width/(float)pic_height;
        float scale_p = (float)scr_w/(float)scr_h;
        if(scale_s > scale_p)
        {
            int zoom = (float)scr_w/(float)pic_width * 256;
            lv_img_set_zoom(imglogo, zoom);
        }
        else
        {
            int zoom = (float)scr_h/(float)pic_height * 256;
            lv_img_set_zoom(imglogo, zoom);
        }
    }

    return 0;
}
