#include "album_language_list.h"
#include "mainstart/include/ui_config.h"
#include "mainstart/include/str_config.h"
#include "mainstart/include/configCustom.h"
#include "mainstart/customer_config.h"
#include  "common/common.h"


void albumLanguageList::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    SETTING_ALBUM_TURE_PNG=(void*)parse_image_from_file(SETTING_ALBUM_TURE_PNG_PATH);
#endif
}

void albumLanguageList::ui_image_free(void)
{
#ifdef IMAGE_DECODE
    free_image(SETTING_ALBUM_TURE_PNG);
#endif
}
albumLanguageList::albumLanguageList(lv_obj_t* parent)
{
    ui_image_decode();
    headLabel = new LvcppButton(parent);
    headLabel->set_size(880,100);
    headLabel->set_main_bg_color(lv_color_hex(0x0499c3),LV_OPA_100);
    headLabel->set_main_radius(0);
    headLabel->set_main_pad_all(0);
    headLabel->set_main_border_width(0);

    iconLabel = new LvcppLabel(headLabel->myobj);
    iconLabel->set_size(30,30);
    iconLabel->set_main_bg_opa(LV_OPA_0);
    iconLabel->set_main_bg_img_src(SETTING_ALBUM_TURE_PNG);
    iconLabel->align(LV_ALIGN_RIGHT_MID,-10,0);
    iconLabel->set_txt("");

    nameLabel = new LvcppLabel(headLabel->myobj);
    nameLabel->set_size(250,30);
    nameLabel->set_main_bg_opa(LV_OPA_0);
    nameLabel->align(LV_ALIGN_LEFT_MID,20,0);
    nameLabel->txt_color(lv_color_white(),LV_PART_MAIN);
    nameLabel->txt_font_size(24, FT_FONT_STYLE_NORMAL);
    nameLabel->txt_align(LV_TEXT_ALIGN_LEFT);
    nameLabel->txt_long_mode(LV_LABEL_LONG_WRAP);
    nameLabel->set_txt("");

    lineLabel = new LvcppLabel(headLabel->myobj);
    lineLabel->set_size(880,1);
    lineLabel->set_main_bg_color(MENU_BTN_COLOR,LV_OPA_100);
    lineLabel->align(LV_ALIGN_BOTTOM_MID,0,0);
    lineLabel->set_txt("");

    iconLabel->show(false);
}
albumLanguageList::~albumLanguageList(void)
{
    if(iconLabel != NULL)
    {
        delete iconLabel;
        iconLabel = NULL;
    }
    if(nameLabel != NULL)
    {
        delete nameLabel;
        nameLabel = NULL;
    }
    if(lineLabel != NULL)
    {
        delete lineLabel;
        lineLabel = NULL;
    }
    if(headLabel != NULL)
    {
        delete headLabel;
        headLabel = NULL;
    }
    ui_image_free();
}
