#include "album_list.h"
#include "mainstart/include/configCustom.h"
#include "mainstart/customer_config.h"

albumList::albumList(bool sliderStr,bool childStr,bool nextStr,bool switchStr,lv_obj_t* parent)
{
    headLabel = new LvcppLabel(parent);
    headLabel->set_size(880,100);
    headLabel->set_main_bg_opa(LV_OPA_0);
    headLabel->set_txt("");

    iconLabel = new LvcppLabel(headLabel->myobj);
    iconLabel->set_size(58,58);
    iconLabel->set_main_bg_opa(LV_OPA_0);
    iconLabel->align(LV_ALIGN_TOP_LEFT,20,21);
    iconLabel->set_txt("");

    nameLabel = new LvcppLabel(headLabel->myobj);
    nameLabel->set_size(250,30);
    nameLabel->set_main_bg_opa(LV_OPA_0);
    nameLabel->align(LV_ALIGN_TOP_LEFT,90,35);
    nameLabel->txt_color(lv_color_white(),LV_PART_MAIN);
    nameLabel->txt_font_size(24, FT_FONT_STYLE_NORMAL);
    nameLabel->txt_align(LV_TEXT_ALIGN_LEFT);
    nameLabel->txt_long_mode(LV_LABEL_LONG_WRAP);
    nameLabel->set_txt("");
    if(sliderStr ==true)
    {
        albumSlider = new LvcppSlider(headLabel->myobj);
        albumSlider->set_size(500, 12);
        albumSlider->align(LV_ALIGN_RIGHT_MID, -30, 0);
        albumSlider->set_mode(LV_BAR_MODE_NORMAL);
        albumSlider->set_main_radius(0);
        albumSlider->set_style_radius(0, LV_PART_INDICATOR);
        albumSlider->set_style_pad_all(0,0);
        albumSlider->set_main_border_width(0);
        albumSlider->set_style_bg_color(lv_color_hex(0x74dafa),LV_OPA_100,LV_PART_MAIN);
        albumSlider->set_style_bg_color(lv_color_hex(0xffffff),LV_OPA_100,LV_PART_INDICATOR);
        albumSlider->set_style_bg_color(lv_color_hex(0xffffff),LV_OPA_100,LV_PART_KNOB);
        albumSlider->set_left_value(0, LV_ANIM_ON);
    }
    if(childStr ==true)
    {
        dataLabel = new LvcppLabel(headLabel->myobj);
        dataLabel->set_size(250,30);
        dataLabel->set_main_bg_opa(LV_OPA_0);
        dataLabel->align(LV_ALIGN_TOP_RIGHT,-40,35);
        dataLabel->txt_color(lv_color_white(),LV_PART_MAIN);
        dataLabel->txt_font_size(24, FT_FONT_STYLE_NORMAL);
        dataLabel->txt_align(LV_TEXT_ALIGN_RIGHT);
        dataLabel->txt_long_mode(LV_LABEL_LONG_WRAP);
        dataLabel->set_txt("");
    }

    if(nextStr ==true)
    {
        childLabel = new LvcppLabel(headLabel->myobj);
        childLabel->set_size(10,40);
        childLabel->set_main_bg_opa(LV_OPA_0);
        childLabel->align(LV_ALIGN_TOP_RIGHT,-20,23);
        childLabel->txt_color(lv_color_white(),LV_PART_MAIN);
        childLabel->txt_font_size(40, FT_FONT_STYLE_NORMAL);
        childLabel->txt_align(LV_TEXT_ALIGN_CENTER);
        childLabel->txt_long_mode(LV_LABEL_LONG_DOT);
        childLabel->set_txt(">");
    }

    if(switchStr ==true)
    {
        switchLabel = new LvcppLabel(headLabel->myobj);
        switchLabel->set_size(87,45);
        switchLabel->set_main_bg_opa(LV_OPA_0);
        switchLabel->align(LV_ALIGN_TOP_RIGHT,-20,27);
        switchLabel->set_txt("");
    }

    lineLabel = new LvcppLabel(headLabel->myobj);
    lineLabel->set_size(880,1);
    lineLabel->set_main_bg_color(MENU_BTN_COLOR,LV_OPA_100);
    lineLabel->align(LV_ALIGN_BOTTOM_MID,0,0);
    lineLabel->set_txt("");
}

albumList::~albumList(void)
{
    if(albumSlider !=NULL)
    {
        delete albumSlider;
        albumSlider = NULL;
    }
    if(iconLabel !=NULL)
    {
        delete iconLabel;
        iconLabel = NULL;
    }
    if(nameLabel !=NULL)
    {
        delete nameLabel;
        nameLabel = NULL;
    }
    if(childLabel !=NULL)
    {
        delete childLabel;
        childLabel = NULL;
    }
    if(dataLabel !=NULL)
    {
        delete dataLabel;
        dataLabel = NULL;
    }
    if(switchLabel !=NULL)
    {
        delete switchLabel;
        switchLabel = NULL;
    }
    if(lineLabel !=NULL)
    {
        delete lineLabel;
        lineLabel = NULL;
    }
    if(headLabel !=NULL)
    {
        delete headLabel;
        headLabel = NULL;
    }
}
