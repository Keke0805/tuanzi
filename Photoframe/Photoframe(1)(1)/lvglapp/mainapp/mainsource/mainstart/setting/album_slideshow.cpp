#include "album_slideshow.h"
#include "mainstart/include/ui_config.h"
#include "mainstart/include/str_config.h"
#include "mainstart/include/configCustom.h"
#include "mainstart/customer_config.h"
#include  "common/common.h"

void albumSlideShow::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    LIST_CIRCLE_PNG=(void*)parse_image_from_file(LIST_CIRCLE_PNG_PATH);
    LIST_CIRCLESEL_PNG=(void*)parse_image_from_file(LIST_CIRCLESEL_PNG_PATH);
#endif
}
void albumSlideShow::ui_image_free(void)
{
#ifdef IMAGE_DECODE
    free_image(LIST_CIRCLE_PNG);
    free_image(LIST_CIRCLESEL_PNG);
#endif
}
albumSlideShow::albumSlideShow(int curIndex)
{
    ui_image_decode();
    SlideshowScreen = new LvcppScreen(lv_scr_act());
    SlideshowScreen->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    SlideshowScreen->center_align();
    SlideshowScreen->set_main_bg_color(lv_color_black(),LV_OPA_60);

    headLabel = new LvcppLabel(SlideshowScreen->myobj);
    headLabel->set_size(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/10*7);
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
    headNameLabel->set_txt(STR_SLIDESHOW);

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

    SlideShowList = new LvcppList(headLabel->myobj);
    SlideShowList->set_size(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/2-10);
    SlideShowList->align(LV_ALIGN_TOP_LEFT,0,SCREEN_VER_SIZE/10);
    SlideShowList->set_main_bg_color(lv_color_white(),LV_OPA_100);
    SlideShowList->set_flex_flow(LV_FLEX_FLOW_COLUMN);
    SlideShowList->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    SlideShowList->set_main_pad_all(0);
    SlideShowList->set_main_pad_row(0);
    SlideShowList->set_main_pad_column(0);
    SlideShowList->set_main_border_width(0);
    SlideShowList->set_main_radius(0);

    TimeList0 =new settingMuteList(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/10,SlideShowList->myobj);
    TimeList0->nameLabel->set_txt(STR_15S);

    TimeList1 =new settingMuteList(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/10,SlideShowList->myobj);
    TimeList1->nameLabel->set_txt(STR_30S);

    TimeList2 =new settingMuteList(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/10,SlideShowList->myobj);
    TimeList2->nameLabel->set_txt(STR_1M);

    TimeList3 =new settingMuteList(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/10,SlideShowList->myobj);
    TimeList3->nameLabel->set_txt(STR_2M);

    TimeList4 =new settingMuteList(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/10,SlideShowList->myobj);
    TimeList4->nameLabel->set_txt(STR_5M);

    TimeList5 =new settingMuteList(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/10,SlideShowList->myobj);
    TimeList5->nameLabel->set_txt(STR_10M);

    TimeList6 =new settingMuteList(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/10,SlideShowList->myobj);
    TimeList6->nameLabel->set_txt(STR_30M);

    TimeList7 =new settingMuteList(SCREEN_HOR_SIZE/2,SCREEN_VER_SIZE/10,SlideShowList->myobj);
    TimeList7->nameLabel->set_txt(STR_NEVER);
    set_SlideShow_cur(curIndex);
}
albumSlideShow::~albumSlideShow(void)
{
    if(TimeList7 !=NULL)
    {
        delete TimeList7;
        TimeList7 = NULL;
    }
    if(TimeList6 !=NULL)
    {
        delete TimeList6;
        TimeList6 = NULL;
    }
    if(TimeList5 !=NULL)
    {
        delete TimeList5;
        TimeList5 = NULL;
    }
    if(TimeList4 !=NULL)
    {
        delete TimeList4;
        TimeList4 = NULL;
    }
    if(TimeList3 !=NULL)
    {
        delete TimeList3;
        TimeList3 = NULL;
    }
    if(TimeList2 !=NULL)
    {
        delete TimeList2;
        TimeList2 = NULL;
    }
    if(TimeList1 !=NULL)
    {
        delete TimeList1;
        TimeList1 = NULL;
    }
    if(TimeList0 !=NULL)
    {
        delete TimeList0;
        TimeList0 = NULL;
    }
    if(SlideShowList !=NULL)
    {
        delete SlideShowList;
        SlideShowList = NULL;
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
    if(SlideshowScreen !=NULL)
    {
        delete SlideshowScreen;
        SlideshowScreen = NULL;
    }
    ui_image_free();
}
int albumSlideShow::get_SlideShow_cur(void)
{
    return index;
}

void albumSlideShow::set_SlideShow_cur(int curIndex)
{
    if(curIndex !=index)
    {
        switch(index)
        {
            case 0:
                TimeList0->iconLabel->set_main_bg_img_src(LIST_CIRCLE_PNG);
                break;
            case 1:
                TimeList1->iconLabel->set_main_bg_img_src(LIST_CIRCLE_PNG);
                break;
            case 2:
                TimeList2->iconLabel->set_main_bg_img_src(LIST_CIRCLE_PNG);
                break;
            case 3:
                TimeList3->iconLabel->set_main_bg_img_src(LIST_CIRCLE_PNG);
                break;
            case 4:
                TimeList4->iconLabel->set_main_bg_img_src(LIST_CIRCLE_PNG);
                break;
            case 5:
                TimeList5->iconLabel->set_main_bg_img_src(LIST_CIRCLE_PNG);
                break;
            case 6:
                TimeList6->iconLabel->set_main_bg_img_src(LIST_CIRCLE_PNG);
                break;
            case 7:
                TimeList7->iconLabel->set_main_bg_img_src(LIST_CIRCLE_PNG);
                break;
            default:
                break;
        }
    }
    index = curIndex;
    switch(index)
    {
        case 0:
            TimeList0->iconLabel->set_main_bg_img_src(LIST_CIRCLESEL_PNG);
            break;
        case 1:
            TimeList1->iconLabel->set_main_bg_img_src(LIST_CIRCLESEL_PNG);
            break;
        case 2:
            TimeList2->iconLabel->set_main_bg_img_src(LIST_CIRCLESEL_PNG);
            break;
        case 3:
            TimeList3->iconLabel->set_main_bg_img_src(LIST_CIRCLESEL_PNG);
            break;
        case 4:
            TimeList4->iconLabel->set_main_bg_img_src(LIST_CIRCLESEL_PNG);
            break;
        case 5:
            TimeList5->iconLabel->set_main_bg_img_src(LIST_CIRCLESEL_PNG);
            break;
        case 6:
            TimeList6->iconLabel->set_main_bg_img_src(LIST_CIRCLESEL_PNG);
            break;
        case 7:
            TimeList7->iconLabel->set_main_bg_img_src(LIST_CIRCLESEL_PNG);
            break;
        default:
            break;
    }
}
