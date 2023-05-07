#include "album_slideshow_mode.h"
#include "mainstart/include/ui_config.h"
#include "mainstart/include/str_config.h"
#include "mainstart/include/configCustom.h"
#include "mainstart/customer_config.h"
#include  "common/common.h"


void albumSlideShowMode::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    LIST_CIRCLE_PNG=(void*)parse_image_from_file(LIST_CIRCLE_PNG_PATH);
    LIST_CIRCLESEL_PNG=(void*)parse_image_from_file(LIST_CIRCLESEL_PNG_PATH);
#endif
}
void albumSlideShowMode::ui_image_free(void)
{
#ifdef IMAGE_DECODE
    free_image(LIST_CIRCLE_PNG);
    free_image(LIST_CIRCLESEL_PNG);
#endif
}
albumSlideShowMode::albumSlideShowMode(int curIndex)
{
    ui_image_decode();
    SlideshowModeScreen = new LvcppScreen(lv_scr_act());
    SlideshowModeScreen->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    SlideshowModeScreen->center_align();
    SlideshowModeScreen->set_main_bg_color(lv_color_black(),LV_OPA_60);

    headLabel = new LvcppLabel(SlideshowModeScreen->myobj);
    headLabel->set_size(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/5*2);
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
    headNameLabel->set_txt(STR_SLIDESHOWMODE);

    lineLabel = new LvcppLabel(headLabel->myobj);
    lineLabel->set_size(SCREEN_HOR_SIZE/2,2);
    lineLabel->set_main_bg_color(MENU_BTN_COLOR,LV_OPA_100);
    lineLabel->align(LV_ALIGN_TOP_MID,0,SCREEN_VER_SIZE/10-2);
    lineLabel->set_txt("");

    CancelButton = new LvcppButton(headLabel->myobj);
    CancelButton->set_size(SCREEN_HOR_SIZE/4-20,SCREEN_VER_SIZE/10-20);
    CancelButton->align(LV_ALIGN_BOTTOM_LEFT,10,-10);
    CancelButton->set_main_radius(10);
    CancelButton->set_main_pad_all(0);
    CancelButton->set_main_border_width(0);
    CancelButton->set_main_bg_color(lv_color_hex(0x0499c3),LV_OPA_100);
    CancelButton->txt_color(lv_color_white());
    CancelButton->txt_size(SCREEN_HOR_SIZE/4-20, 32, LV_LABEL_LONG_WRAP);
    CancelButton->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    CancelButton->txt_center();
    CancelButton->add_txt(STR_CANCEL);

    OKButton = new LvcppButton(headLabel->myobj);
    OKButton->set_size(SCREEN_HOR_SIZE/4-20,SCREEN_VER_SIZE/10-20);
    OKButton->align(LV_ALIGN_BOTTOM_RIGHT,-10,-10);
    OKButton->set_main_radius(10);
    OKButton->set_main_pad_all(0);
    OKButton->set_main_border_width(0);
    OKButton->set_main_bg_color(lv_color_hex(0x0499c3),LV_OPA_100);
    OKButton->txt_color(lv_color_white());
    OKButton->txt_size(SCREEN_HOR_SIZE/4-20, 32, LV_LABEL_LONG_WRAP);
    OKButton->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    OKButton->txt_center();
    OKButton->add_txt(STR_OK);

    SlideShowModeList = new LvcppList(headLabel->myobj);
    SlideShowModeList->set_size(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/5);
    SlideShowModeList->align(LV_ALIGN_TOP_LEFT,0,SCREEN_VER_SIZE/10);
    SlideShowModeList->set_main_bg_color(lv_color_white(),LV_OPA_100);
    SlideShowModeList->set_flex_flow(LV_FLEX_FLOW_COLUMN);
    SlideShowModeList->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    SlideShowModeList->set_main_pad_all(0);
    SlideShowModeList->set_main_pad_row(0);
    SlideShowModeList->set_main_pad_column(0);
    SlideShowModeList->set_main_border_width(0);
    SlideShowModeList->set_main_radius(0);

    ModeList0 =new settingMuteList(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/10,SlideShowModeList->myobj);
    ModeList0->nameLabel->set_txt(STR_SEQUENTIAL);

    ModeList1 =new settingMuteList(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/10,SlideShowModeList->myobj);
    ModeList1->nameLabel->set_txt(STR_RANDOMS);
    set_SlideShowMode_cur(curIndex);
}

albumSlideShowMode::~albumSlideShowMode(void)
{
    if(ModeList1 !=NULL)
    {
        delete ModeList1;
        ModeList1 = NULL;
    }
    if(ModeList0 !=NULL)
    {
        delete ModeList0;
        ModeList0 = NULL;
    }
    if(SlideShowModeList !=NULL)
    {
        delete SlideShowModeList;
        SlideShowModeList = NULL;
    }
    if(OKButton !=NULL)
    {
        delete OKButton;
        OKButton = NULL;
    }
    if(CancelButton !=NULL)
    {
        delete CancelButton;
        CancelButton = NULL;
    }
    if(headNameLabel !=NULL)
    {
        delete headNameLabel;
        headNameLabel = NULL;
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
    if(SlideshowModeScreen !=NULL)
    {
        delete SlideshowModeScreen;
        SlideshowModeScreen = NULL;
    }
    ui_image_free();
}
void albumSlideShowMode::set_SlideShowMode_cur(int curIndex)
{
    if(curIndex ==1)
    {
        ModeList0->iconLabel->set_main_bg_img_src(LIST_CIRCLE_PNG);
        ModeList1->iconLabel->set_main_bg_img_src(LIST_CIRCLESEL_PNG);
    }
    else
    {
        ModeList0->iconLabel->set_main_bg_img_src(LIST_CIRCLESEL_PNG);
        ModeList1->iconLabel->set_main_bg_img_src(LIST_CIRCLE_PNG);
    }
    index = curIndex;
}
int albumSlideShowMode::get_SlideShowMode_cur(void)
{
    return index;
}
