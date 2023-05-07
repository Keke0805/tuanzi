#include "frame_change_str.h"
#include "mainstart/include/ui_config.h"
#include "mainstart/include/str_config.h"
#include "mainstart/include/configCustom.h"
#include "mainstart/customer_config.h"

frameChangeStr::frameChangeStr(char *headStr,char *dataStr)
{
    StrScreen = new LvcppScreen(lv_scr_act());
    StrScreen->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    StrScreen->set_main_bg_color(lv_color_black(),LV_OPA_60);

    headLabel = new LvcppLabel(StrScreen->myobj);
    headLabel->set_size(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/4+20);
    headLabel->align(LV_ALIGN_TOP_MID,0,SCREEN_VER_SIZE/10);
    headLabel->set_main_radius(10);
    headLabel->set_main_pad_all(0);
    headLabel->set_main_pad_row(0);
    headLabel->set_main_bg_color(lv_color_white(),LV_OPA_100);
    headLabel->set_main_border_width(0);
    headLabel->set_txt("");
    headLabel->add_flag(LV_OBJ_FLAG_CLICKABLE);

    headNameLabel = new LvcppLabel(headLabel->myobj);
    headNameLabel->set_size(SCREEN_HOR_SIZE/2,40);
    headNameLabel->align(LV_ALIGN_TOP_MID,0,(SCREEN_VER_SIZE/12 -40)/2);
    headNameLabel->set_main_bg_opa(LV_OPA_100);
    headNameLabel->txt_color(lv_color_black(),LV_PART_MAIN);
    headNameLabel->txt_font_size(32, FT_FONT_STYLE_NORMAL);
    headNameLabel->txt_align(LV_TEXT_ALIGN_CENTER);
    headNameLabel->txt_long_mode(LV_LABEL_LONG_DOT);
    headNameLabel->set_txt(headStr);

    lineLabel1 = new LvcppLabel(headLabel->myobj);
    lineLabel1->set_size(SCREEN_HOR_SIZE/2,2);
    lineLabel1->set_main_bg_color(MENU_BTN_COLOR,LV_OPA_100);
    lineLabel1->align(LV_ALIGN_TOP_MID,0,SCREEN_VER_SIZE/12);
    lineLabel1->set_txt("");

    lineLabel2 = new LvcppLabel(headLabel->myobj);
    lineLabel2->set_size(SCREEN_HOR_SIZE/2,2);
    lineLabel2->set_main_bg_color(TABLE_SETTING_COLOR,LV_OPA_100);
    lineLabel2->align(LV_ALIGN_TOP_MID,0,SCREEN_VER_SIZE/6);
    lineLabel2->set_txt("");

    CancelLabel = new LvcppButton(headLabel->myobj);
    CancelLabel->set_size(SCREEN_HOR_SIZE/4-20,SCREEN_VER_SIZE/12-10);
    CancelLabel->set_main_radius(10);
    CancelLabel->align(LV_ALIGN_BOTTOM_LEFT,10,-10);
    CancelLabel->set_main_bg_color(lv_color_hex(0x00a7d4),LV_OPA_100);
    CancelLabel->txt_color(lv_color_white());
    CancelLabel->txt_font_size(32, FT_FONT_STYLE_BOLD);
    CancelLabel->txt_center();
    CancelLabel->txt_long_mode(LV_LABEL_LONG_DOT);
    CancelLabel->add_txt(STR_CANCEL);

    OKLabel = new LvcppButton(headLabel->myobj);
    OKLabel->set_size(SCREEN_HOR_SIZE/4-20,SCREEN_VER_SIZE/12-10);
    OKLabel->set_main_radius(10);
    OKLabel->align(LV_ALIGN_BOTTOM_RIGHT,-10,-10);
    OKLabel->set_main_bg_color(lv_color_hex(0x00a7d4),LV_OPA_100);
    OKLabel->txt_color(lv_color_white());
    OKLabel->txt_font_size(32, FT_FONT_STYLE_BOLD);
    OKLabel->txt_center();
    OKLabel->txt_long_mode(LV_LABEL_LONG_DOT);
    OKLabel->add_txt(STR_OK);

    textarea = new LvcppTextArea(headLabel->myobj);
    textarea->set_size(SCREEN_HOR_SIZE/2-40,40);
    textarea->align(LV_ALIGN_TOP_MID,0,(SCREEN_VER_SIZE/6 -55));
    textarea->set_main_bg_color(lv_color_white(),LV_OPA_100);
    textarea->set_max_length(48);
    textarea->set_one_line(true);
    textarea->set_scrollbar_mode(0);
    textarea->set_password_mode(false);
    textarea->set_main_border_width(0);
    textarea->set_text(dataStr);

    Keyboard = new LvcppKeyboard(StrScreen->myobj);
    Keyboard->set_textarea(textarea->myobj);
    Keyboard->show(true);
}
frameChangeStr::~frameChangeStr(void)
{
    if(Keyboard != NULL)
    {
        delete Keyboard;
        Keyboard = NULL;
    }
    if(textarea != NULL)
    {
        delete textarea;
        textarea = NULL;
    }
    if(CancelLabel != NULL)
    {
        delete CancelLabel;
        CancelLabel = NULL;
    }
    if(OKLabel != NULL)
    {
        delete OKLabel;
        OKLabel = NULL;
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
    if(StrScreen != NULL)
    {
        delete StrScreen;
        StrScreen = NULL;
    }
}
