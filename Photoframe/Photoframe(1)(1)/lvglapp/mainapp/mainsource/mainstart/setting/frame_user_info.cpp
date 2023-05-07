#include "frame_user_info.h"
#include "mainstart/include/ui_config.h"
#include "mainstart/include/str_config.h"
#include "mainstart/include/configCustom.h"
#include "mainstart/customer_config.h"

frameUserInfo::frameUserInfo(char *userName)
{
    UserInfoScreen = new LvcppScreen(lv_scr_act());
    UserInfoScreen->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    UserInfoScreen->set_main_bg_color(lv_color_black(),LV_OPA_60);

    headLabel = new LvcppLabel(UserInfoScreen->myobj);
    headLabel->set_size(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/2);
    headLabel->center_align();
    headLabel->set_main_radius(10);
    headLabel->set_main_pad_all(0);
    headLabel->set_main_pad_row(0);
    headLabel->set_main_bg_color(lv_color_white(),LV_OPA_100);
    headLabel->set_main_border_width(0);
    headLabel->set_txt("");
    headLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);

    headNameLabel = new LvcppLabel(headLabel->myobj);
    headNameLabel->set_size(SCREEN_HOR_SIZE/2,40);
    headNameLabel->align(LV_ALIGN_TOP_MID,0,(SCREEN_VER_SIZE/10 -40)/2);
    headNameLabel->set_main_bg_opa(LV_OPA_100);
    headNameLabel->txt_color(lv_color_black(),LV_PART_MAIN);
    headNameLabel->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    headNameLabel->txt_align(LV_TEXT_ALIGN_CENTER);
    headNameLabel->txt_long_mode(LV_LABEL_LONG_DOT);
    headNameLabel->set_txt(userName);

    lineLabel1 = new LvcppLabel(headLabel->myobj);
    lineLabel1->set_size(SCREEN_HOR_SIZE/2,2);
    lineLabel1->set_main_bg_color(MENU_BTN_COLOR,LV_OPA_100);
    lineLabel1->align(LV_ALIGN_TOP_MID,0,SCREEN_VER_SIZE/10-2);
    lineLabel1->set_txt("");

    ViewPhotos = new LvcppButton(headLabel->myobj);
    ViewPhotos->set_size(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/10);
    ViewPhotos->align(LV_ALIGN_TOP_MID,0,SCREEN_VER_SIZE/10);
    ViewPhotos->set_main_bg_opa(LV_OPA_0);
    ViewPhotos->set_main_radius(0);
    ViewPhotos->set_main_pad_all(0);
    ViewPhotos->set_main_border_width(0);
    ViewPhotos->set_main_bg_color(lv_color_white(),LV_OPA_100);
    ViewPhotos->txt_color(lv_color_black());
    ViewPhotos->txt_size(SCREEN_HOR_SIZE/2-10, 40, LV_LABEL_LONG_WRAP);
    ViewPhotos->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    ViewPhotos->txt_center();
    ViewPhotos->add_txt(STR_VIEWPHOTOS);

    lineLabel2 = new LvcppLabel(ViewPhotos->myobj);
    lineLabel2->set_size(SCREEN_HOR_SIZE/2,1);
    lineLabel2->set_main_bg_color(MENU_BTN_COLOR,LV_OPA_100);
    lineLabel2->align(LV_ALIGN_BOTTOM_MID,0,0);
    lineLabel2->set_txt("");

    remarkName = new LvcppButton(headLabel->myobj);
    remarkName->set_size(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/10);
    remarkName->align(LV_ALIGN_TOP_MID,0,SCREEN_VER_SIZE/5);
    remarkName->set_main_bg_opa(LV_OPA_0);
    remarkName->set_main_radius(0);
    remarkName->set_main_pad_all(0);
    remarkName->set_main_border_width(0);
    remarkName->set_main_bg_color(lv_color_white(),LV_OPA_100);
    remarkName->txt_color(lv_color_black());
    remarkName->txt_size(SCREEN_HOR_SIZE/2-10, 40, LV_LABEL_LONG_WRAP);
    remarkName->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    remarkName->txt_center();
    remarkName->add_txt(STR_REMARKNAME);

    lineLabel3 = new LvcppLabel(remarkName->myobj);
    lineLabel3->set_size(SCREEN_HOR_SIZE/2,1);
    lineLabel3->set_main_bg_color(MENU_BTN_COLOR,LV_OPA_100);
    lineLabel3->align(LV_ALIGN_BOTTOM_MID,0,0);
    lineLabel3->set_txt("");

    delUser = new LvcppButton(headLabel->myobj);
    delUser->set_size(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/10);
    delUser->align(LV_ALIGN_BOTTOM_MID,0,-SCREEN_VER_SIZE/10);
    delUser->set_main_bg_opa(LV_OPA_0);
    delUser->set_main_radius(0);
    delUser->set_main_pad_all(0);
    delUser->set_main_border_width(0);
    delUser->set_main_bg_color(lv_color_white(),LV_OPA_100);
    delUser->txt_color(lv_color_black());
    delUser->txt_size(SCREEN_HOR_SIZE/2-10, 40, LV_LABEL_LONG_WRAP);
    delUser->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    delUser->txt_center();
    delUser->add_txt(STR_DELUSER);

    lineLabel4 = new LvcppLabel(delUser->myobj);
    lineLabel4->set_size(SCREEN_HOR_SIZE/2,1);
    lineLabel4->set_main_bg_color(MENU_BTN_COLOR,LV_OPA_100);
    lineLabel4->align(LV_ALIGN_BOTTOM_MID,0,0);
    lineLabel4->set_txt("");

    delUserPhoto = new LvcppButton(headLabel->myobj);
    delUserPhoto->set_size(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/10);
    delUserPhoto->align(LV_ALIGN_BOTTOM_MID,0,0);
    delUserPhoto->set_main_bg_opa(LV_OPA_0);
    delUserPhoto->set_main_radius(10);
    delUserPhoto->set_main_pad_all(0);
    delUserPhoto->set_main_border_width(0);
    delUserPhoto->set_main_bg_color(lv_color_white(),LV_OPA_100);
    delUserPhoto->txt_color(lv_color_black());
    delUserPhoto->txt_size(SCREEN_HOR_SIZE/2-10, 40, LV_LABEL_LONG_WRAP);
    delUserPhoto->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    delUserPhoto->txt_center();
    delUserPhoto->add_txt(STR_DELUSERPHOTOS);
}
frameUserInfo::~frameUserInfo(void)
{
    if(lineLabel4 != NULL)
    {
        delete lineLabel4;
        lineLabel4 = NULL;
    }
    if(lineLabel3 != NULL)
    {
        delete lineLabel3;
        lineLabel3 = NULL;
    }
    if(lineLabel2 != NULL)
    {
        delete lineLabel2;
        lineLabel2 = NULL;
    }
    if(lineLabel1 != NULL)
    {
        delete lineLabel1;
        lineLabel1 = NULL;
    }
    if(ViewPhotos != NULL)
    {
        delete ViewPhotos;
        ViewPhotos = NULL;
    }
    if(remarkName != NULL)
    {
        delete remarkName;
        remarkName = NULL;
    }
    if(delUser != NULL)
    {
        delete delUser;
        delUser = NULL;
    }
    if(delUserPhoto != NULL)
    {
        delete delUserPhoto;
        delUserPhoto = NULL;
    }
    if(headNameLabel != NULL)
    {
        delete headNameLabel;
        headNameLabel = NULL;
    }
    if(headLabel != NULL)
    {
        delete headLabel;
        headLabel = NULL;
    }
    if(UserInfoScreen != NULL)
    {
        delete UserInfoScreen;
        UserInfoScreen = NULL;
    }
}
