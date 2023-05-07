#include  "lvcpp_pushbutton.h"


LvcppButton::LvcppButton(lv_obj_t* parent)
{
    myobj = lv_btn_create(parent);
    set_style_border_style(0, lv_color_hex(0xffffff),LV_OPA_0, 0);
    set_style_shadow_width(0,0);
    set_style_pad_all(5,0);
    set_style_radius(0,0);
    clear_state(LV_STATE_ANY);
    label = nullptr;
    fontsize = nullptr;
}

LvcppButton::~LvcppButton()
{
   if(label != nullptr)
   {
       lv_obj_del(label);
       label = nullptr;
   }

   if(fontsize != nullptr)
   {
       delete fontsize;
       fontsize = nullptr;
   }
}

int LvcppButton::set_auto_src(const void * src)
{
    uint32_t obj_width = 0,obj_height = 0;

    obj_width = lv_obj_get_width(myobj);
    obj_height = lv_obj_get_height(myobj);

    lv_obj_set_style_bg_img_src(myobj, src, LV_PART_MAIN);

    if (myobj == NULL || src == NULL)
    {
        return -1;
    }

    if (obj_width == 0 || obj_height == 0)
    {
        return -1;
    }

    uint32_t img_width = 0, img_height = 0, zoom_factor = 0;

    lv_img_header_t header;
    if (lv_img_decoder_get_info(src, &header) != LV_RES_OK)
    {
        return -1;
    }

    img_width = header.w;
    img_height = header.h;

    lv_obj_set_width(myobj,img_width);
    lv_obj_set_height(myobj,img_height);

    if (img_width != 0 && img_height != 0)
    {
        uint32_t y_a= obj_height * img_width;
        uint32_t x_b= obj_width * img_height;

        if (x_b >= y_a)
        {
            if (img_height >= obj_height)
            {
                uint32_t x = obj_height * 256;
                zoom_factor = x / img_height;
                lv_img_set_zoom(myobj, zoom_factor);
            }
        }
        else
        {
            if (img_width > obj_width)
            {
                uint32_t x = obj_width * 256;
                zoom_factor = x / img_width;
                lv_img_set_zoom(myobj, zoom_factor);
            }
        }
    }

    return 0;
}

const void* LvcppButton::get_main_src(void)
{
    return lv_obj_get_style_bg_img_src(myobj,LV_PART_MAIN);
}


lv_obj_t* LvcppButton::get_label(void)
{
    return label;
}

int LvcppButton::add_txt(const char* str)
{
    if(label==nullptr)
    {
        label = lv_label_create(myobj);
        lv_label_set_text(label, str);
    }
    else
    {
        lv_label_set_text(label, str);
    }
    return 0;
}

int LvcppButton::clear_txt(void)
{
    if(label!=nullptr)
    {
        delete label;
        label = nullptr;
    }
    if(fontsize != nullptr)
    {
        delete fontsize;
        fontsize = nullptr;
    }
    return 0;
}

int LvcppButton::txt_size(lv_coord_t width, lv_coord_t height, lv_label_long_mode_t mode)
{
    if(label == nullptr)
    {
        label = lv_label_create(myobj);
        lv_obj_set_size(label, width, height);
        lv_label_set_long_mode(label,mode);
    }
    else
    {
        lv_obj_set_size(label, width, height);
        lv_label_set_long_mode(label,mode);
    }
    return 0;
}

int LvcppButton::txt_font_size(uint16_t weight, uint16_t font_type)
{
    (void) font_type;

    if(fontsize == nullptr)
    {
       fontsize = new LvcppFreeTypeFont(weight,font_type);
    }
    else
    {
        fontsize->resize(weight,font_type);
    }
    if(label != nullptr)
    {
        lv_obj_set_style_text_font(label, fontsize->font(), LV_PART_MAIN);
    }
    else
    {
        label = lv_label_create(myobj);
        lv_obj_set_style_text_font(label, fontsize->font(), LV_PART_MAIN);
    }
    return 0;
}

int LvcppButton::txt_color(lv_color_t value)
{
    if(label != nullptr)
    {
        lv_obj_set_style_text_color(label, value, LV_PART_MAIN);
        lv_obj_get_style_color_filter_dsc(label,LV_PART_MAIN);
    }
    else
    {
        label = lv_label_create(myobj);
        lv_obj_set_style_text_color(label, value, LV_PART_MAIN);
        lv_obj_get_style_color_filter_dsc(label,LV_PART_MAIN);
    }
    return 0;
}


int LvcppButton::txt_long_mode(lv_label_long_mode_t mode)
{
    if(label != nullptr)
    {
        lv_label_set_long_mode(label,mode);
    }
    else
    {
        label = lv_label_create(myobj);
        lv_label_set_long_mode(label,mode);
    }
    return 0;
}

int LvcppButton::txt_align(lv_align_t align,int offset_x,int offset_y)
{
    if(label != nullptr)
    {
        lv_obj_align(label, align, offset_x, offset_y);
    }
    else
    {
        label = lv_label_create(myobj);
        lv_obj_align(label, align, offset_x, offset_y);
    }
    return 0;
}


int LvcppButton::txt_center(void)
{
    if(label != nullptr)
    {
        lv_obj_set_size(label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_center(label);
    }
    else
    {
        label = lv_label_create(myobj);
        lv_obj_set_size(label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_center(label);
    }
    return 0;
}

const char* LvcppButton::get_txt(void)
{
    if(label != nullptr)
    {
        return lv_label_get_text(label);
    }
    else
    {
        return "";
    }
}


lv_color_t LvcppButton::get_txt_color(void)
{
    if(label != nullptr)
    {
        return lv_obj_get_style_text_color(label,LV_PART_MAIN);
    }
    else
    {
        return lv_color_black();
    }
}

lv_align_t LvcppButton::get_txt_align(void)
{
    if(label != nullptr)
    {
        return lv_obj_get_style_align(label,LV_PART_MAIN);
    }
    else
    {
        return LV_ALIGN_DEFAULT;
    }
}

int LvcppButton::get_txt_long_mode(void)
{
    if(label != nullptr)
    {
        lv_obj_set_size(label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        return lv_label_get_long_mode(label);
    }
    else
    {
        return LV_LABEL_LONG_WRAP;
    }
}



