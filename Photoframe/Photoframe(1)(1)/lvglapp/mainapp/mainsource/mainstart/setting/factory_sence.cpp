#include "factory_sence.h"
#include "mainstart/include/ui_config.h"
#include "mainstart/include/str_config.h"
#include "mainstart/include/configCustom.h"
#include "mainstart/customer_config.h"
#include  "common/common.h"


#ifdef IMAGE_DECODE
#else
static const void *dotPatch[2]={LIST_UNSEL_PNG,LIST_SEL_PNG};
#endif
void factorySence::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    LIST_UNSEL_PNG=(void*)parse_image_from_file(LIST_UNSEL_PNG_PATH);
    LIST_SEL_PNG=(void*)parse_image_from_file(LIST_SEL_PNG_PATH);
#endif
}

void factorySence::ui_image_free(void)
{
#ifdef IMAGE_DECODE
    free_image(LIST_UNSEL_PNG);
    free_image(LIST_SEL_PNG);
#endif
}
factorySence::factorySence(lv_obj_t* parent)
{
    ui_image_decode();
#ifdef IMAGE_DECODE
    void *dotPatch[2]={LIST_UNSEL_PNG,LIST_SEL_PNG};
#endif
    factoryList = new LvcppLabel(parent);
    factoryList->set_size(850,500);
    factoryList->set_main_bg_opa(LV_OPA_0);
    factoryList->set_txt("");

    factoryListOne = new LvcppLabel(factoryList->myobj);
    factoryListOne->set_size(830,70);
    factoryListOne->align(LV_ALIGN_TOP_LEFT,20,20);
    factoryListOne->set_main_border_width(0);
    factoryListOne->set_main_bg_opa(LV_OPA_0);
    factoryListOne->txt_color(lv_color_white(),LV_PART_MAIN);
    factoryListOne->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    factoryListOne->txt_align(LV_TEXT_ALIGN_LEFT);
    factoryListOne->txt_long_mode(LV_LABEL_LONG_WRAP);
    factoryListOne->set_txt(STR_FACTORYONE);

    factoryListTow = new LvcppLabel(factoryList->myobj);
    factoryListTow->set_size(830,32);
    factoryListTow->align(LV_ALIGN_TOP_LEFT,20,110);
    factoryListTow->set_main_border_width(0);
    factoryListTow->set_main_bg_opa(LV_OPA_0);
    factoryListTow->txt_color(lv_color_white(),LV_PART_MAIN);
    factoryListTow->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    factoryListTow->txt_align(LV_TEXT_ALIGN_LEFT);
    factoryListTow->txt_long_mode(LV_LABEL_LONG_WRAP);
    factoryListTow->set_txt(STR_FACTORYTOW);

    factoryListThree = new LvcppLabel(factoryList->myobj);
    factoryListThree->set_size(830,32);
    factoryListThree->align(LV_ALIGN_TOP_LEFT,20,142);
    factoryListThree->set_main_border_width(0);
    factoryListThree->set_main_bg_opa(LV_OPA_0);
    factoryListThree->txt_color(lv_color_white(),LV_PART_MAIN);
    factoryListThree->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    factoryListThree->txt_align(LV_TEXT_ALIGN_LEFT);
    factoryListThree->txt_long_mode(LV_LABEL_LONG_WRAP);
    factoryListThree->set_txt(STR_FACTORYTHREE);

    factoryListFour = new LvcppLabel(factoryList->myobj);
    factoryListFour->set_size(830,32);
    factoryListFour->align(LV_ALIGN_TOP_LEFT,20,174);
    factoryListFour->set_main_border_width(0);
    factoryListFour->set_main_bg_opa(LV_OPA_0);
    factoryListFour->txt_color(lv_color_white(),LV_PART_MAIN);
    factoryListFour->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    factoryListFour->txt_align(LV_TEXT_ALIGN_LEFT);
    factoryListFour->txt_long_mode(LV_LABEL_LONG_WRAP);
    factoryListFour->set_txt(STR_FACTORYFOUR);

    factoryListFive = new LvcppLabel(factoryList->myobj);
    factoryListFive->set_size(830,32);
    factoryListFive->align(LV_ALIGN_TOP_LEFT,20,206);
    factoryListFive->set_main_border_width(0);
    factoryListFive->set_main_bg_opa(LV_OPA_0);
    factoryListFive->txt_color(lv_color_white(),LV_PART_MAIN);
    factoryListFive->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    factoryListFive->txt_align(LV_TEXT_ALIGN_LEFT);
    factoryListFive->txt_long_mode(LV_LABEL_LONG_WRAP);
    factoryListFive->set_txt(STR_FACTORYFIVE);

    factoryListSix = new LvcppLabel(factoryList->myobj);
    factoryListSix->set_size(830,32);
    factoryListSix->align(LV_ALIGN_TOP_LEFT,20,270);
    factoryListSix->set_main_border_width(0);
    factoryListSix->set_main_bg_opa(LV_OPA_0);
    factoryListSix->txt_color(lv_color_white(),LV_PART_MAIN);
    factoryListSix->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    factoryListSix->txt_align(LV_TEXT_ALIGN_LEFT);
    factoryListSix->txt_long_mode(LV_LABEL_LONG_WRAP);
    factoryListSix->set_txt(STR_FACTORYSIX);

    factoryListSeven = new LvcppButton(factoryList->myobj);
    factoryListSeven->set_size(830,80);
    factoryListSeven->align(LV_ALIGN_TOP_LEFT,20,320);
    factoryListSeven->set_main_radius(0);
    factoryListSeven->set_main_pad_all(0);
    factoryListSeven->set_main_border_width(0);
    factoryListSeven->set_main_bg_color(lv_color_hex(0x0499c3),LV_OPA_100);
    factoryListSeven->txt_color(lv_color_white());
    factoryListSeven->txt_size(780, 32, LV_LABEL_LONG_WRAP);
    factoryListSeven->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    factoryListSeven->txt_align(LV_ALIGN_LEFT_MID,0,0);
    factoryListSeven->add_txt(STR_FACTORYSEVEN);
    factoryListSeven->add_event_cb(factory_list_event_handler,LV_EVENT_CLICKED,this);

    lineList = new LvcppLabel(factoryListSeven->myobj);
    lineList->set_size(830,1);
    lineList->set_main_bg_color(MENU_BTN_COLOR,LV_OPA_100);
    lineList->align(LV_ALIGN_BOTTOM_MID,0,0);
    lineList->set_txt("");

    datList = new LvcppLabel(factoryListSeven->myobj);
    datList->set_size(32,32);
    datList->set_main_bg_opa(LV_OPA_0);
    datList->set_main_bg_img_src(dotPatch[selStatus]);
    datList->align(LV_ALIGN_RIGHT_MID,0,0);
    datList->set_txt("");

    resetDevice = new LvcppButton(factoryList->myobj);
    resetDevice->set_size(250,50);
    resetDevice->align(LV_ALIGN_BOTTOM_MID,0,0);
    resetDevice->set_main_radius(10);
    resetDevice->set_main_pad_all(0);
    resetDevice->set_main_border_width(0);
    resetDevice->set_main_bg_color(lv_color_hex(0x0084e1),LV_OPA_100);
    resetDevice->txt_color(lv_color_white());
    resetDevice->txt_size(180, 32, LV_LABEL_LONG_WRAP);
    resetDevice->txt_font_size(28, FT_FONT_STYLE_NORMAL);
    resetDevice->txt_center();
    resetDevice->add_txt(STR_RESETDEVICE);
    resetDevice->add_event_cb(factory_list_event_handler,LV_EVENT_CLICKED,this);
}

factorySence::~factorySence(void)
{
    if(resetDevice !=NULL)
    {
        delete resetDevice;
        resetDevice = NULL;
    }
    if(datList !=NULL)
    {
        delete datList;
        datList = NULL;
    }
    if(lineList !=NULL)
    {
        delete lineList;
        lineList = NULL;
    }
    if(factoryListOne !=NULL)
    {
        delete factoryListOne;
        factoryListOne = NULL;
    }
    if(factoryListTow !=NULL)
    {
        delete factoryListTow;
        factoryListTow = NULL;
    }
    if(factoryListThree !=NULL)
    {
        delete factoryListThree;
        factoryListThree = NULL;
    }
    if(factoryListFour !=NULL)
    {
        delete factoryListFour;
        factoryListFour = NULL;
    }
    if(factoryListFive !=NULL)
    {
        delete factoryListFive;
        factoryListFive = NULL;
    }
    if(factoryListSix !=NULL)
    {
        delete factoryListSix;
        factoryListSix = NULL;
    }
    if(factoryListSeven !=NULL)
    {
        delete factoryListSeven;
        factoryListSeven = NULL;
    }
    if(factoryList !=NULL)
    {
        delete factoryList;
        factoryList = NULL;
    }
    ui_image_free();
}

void factorySence::factory_list_event_handler(lv_event_t *event)
{
    factorySence* opt = (factorySence*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
#ifdef IMAGE_DECODE
    void *dotPatch[2]={opt->LIST_UNSEL_PNG,opt->LIST_SEL_PNG};
#endif

    if((opt->factoryListSeven !=NULL)&&(target ==opt->factoryListSeven->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            opt->selStatus =!opt->selStatus;
            if(opt->datList !=NULL)
                opt->datList->set_main_bg_img_src(dotPatch[opt->selStatus]);
        }
    }
    else if((opt->resetDevice !=NULL)&&(target ==opt->resetDevice->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
           LV_LOG_USER("resetDevice");
        }
    }
}
