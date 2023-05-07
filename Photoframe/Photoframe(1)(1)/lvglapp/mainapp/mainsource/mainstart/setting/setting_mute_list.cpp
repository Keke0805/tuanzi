#include "setting_mute_list.h"
#include "mainstart/include/ui_config.h"
#include "mainstart/include/str_config.h"
#include "mainstart/include/configCustom.h"
#include "mainstart/customer_config.h"
#include  "common/common.h"


void settingMuteList::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    LIST_CIRCLE_PNG=(void*)parse_image_from_file(LIST_CIRCLE_PNG_PATH);
    LIST_CIRCLESEL_PNG=(void*)parse_image_from_file(LIST_CIRCLESEL_PNG_PATH);
#endif
}
void settingMuteList::ui_image_free(void)
{
#ifdef IMAGE_DECODE
    free_image(LIST_CIRCLE_PNG);
    free_image(LIST_CIRCLESEL_PNG);
#endif
}
settingMuteList::settingMuteList(int size_w,int size_h,lv_obj_t* parent)
{
    ui_image_decode();
    headLabel = new LvcppLabel(parent);
    headLabel->set_size(size_w,size_h);
    headLabel->set_main_bg_opa(LV_OPA_0);
    headLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);
    headLabel->set_txt("");

    iconLabel = new LvcppLabel(headLabel->myobj);
    iconLabel->set_size(32,32);
    iconLabel->set_main_bg_opa(LV_OPA_0);
    iconLabel->set_main_bg_img_src(LIST_CIRCLE_PNG);
    iconLabel->align(LV_ALIGN_RIGHT_MID,-10,0);
    iconLabel->set_txt("");

    nameLabel = new LvcppLabel(headLabel->myobj);
    nameLabel->set_size(size_w/3*2,30);
    nameLabel->set_main_bg_opa(LV_OPA_0);
    nameLabel->align(LV_ALIGN_LEFT_MID,20,0);
    nameLabel->txt_color(lv_color_black(),LV_PART_MAIN);
    nameLabel->txt_font_size(24, FT_FONT_STYLE_NORMAL);
    nameLabel->txt_align(LV_TEXT_ALIGN_LEFT);
    nameLabel->txt_long_mode(LV_LABEL_LONG_WRAP);
    nameLabel->set_txt("");

    lineLabel = new LvcppLabel(headLabel->myobj);
    lineLabel->set_size(size_w,1);
    lineLabel->set_main_bg_color(MENU_BTN_COLOR,LV_OPA_100);
    lineLabel->align(LV_ALIGN_BOTTOM_MID,0,0);
    lineLabel->set_txt("");
}
settingMuteList::~settingMuteList(void)
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
