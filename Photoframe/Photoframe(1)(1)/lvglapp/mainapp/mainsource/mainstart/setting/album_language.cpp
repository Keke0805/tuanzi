#include "album_language.h"
#include "mainstart/include/ui_config.h"
#include "mainstart/include/str_config.h"
#include "mainstart/include/configCustom.h"
#include "mainstart/customer_config.h"
#ifdef _UCHIP_T113
#include  "common/common.h"
#endif


albumLanguage::albumLanguage(void)
{
#ifdef _UCHIP_T113
    read_int_type_param(PUBLIC_SCENE, LANGUAGE, &lauIndex);
#endif
    LanguageScreen = new LvcppScreen(lv_scr_act());
    LanguageScreen->set_size(880,700);
    LanguageScreen->align(LV_ALIGN_TOP_LEFT,390,90);
    LanguageScreen->set_main_bg_color(lv_color_hex(0x0499c3),LV_OPA_100);

    LanguageList = new LvcppList(LanguageScreen->myobj);
    LanguageList->set_size(880,700);
    LanguageList->center_align();
    LanguageList->set_main_bg_color(lv_color_hex(0x0499c3),LV_OPA_100);
    LanguageList->set_flex_flow(LV_FLEX_FLOW_COLUMN);
    LanguageList->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    LanguageList->set_main_pad_all(0);
    LanguageList->set_main_pad_row(0);
    LanguageList->set_main_pad_column(0);
    LanguageList->set_main_border_width(0);
    LanguageList->set_main_radius(0);

    LanList1 =new albumLanguageList(LanguageList->myobj);
    LanList1->nameLabel->set_txt(STR_LAU_EN);
    LanList1->headLabel->add_event_cb(albumLanguage_event_handler,LV_EVENT_CLICKED,this);

    LanList2 =new albumLanguageList(LanguageList->myobj);
    LanList2->nameLabel->set_txt(STR_LAU_FR);
    LanList2->headLabel->add_event_cb(albumLanguage_event_handler,LV_EVENT_CLICKED,this);

    LanList3 =new albumLanguageList(LanguageList->myobj);
    LanList3->nameLabel->set_txt(STR_LAU_GE);
    LanList3->headLabel->add_event_cb(albumLanguage_event_handler,LV_EVENT_CLICKED,this);

    LanList4 =new albumLanguageList(LanguageList->myobj);
    LanList4->nameLabel->set_txt(STR_LAU_IT);
    LanList4->headLabel->add_event_cb(albumLanguage_event_handler,LV_EVENT_CLICKED,this);

    LanList5 =new albumLanguageList(LanguageList->myobj);
    LanList5->nameLabel->set_txt(STR_LAU_PE);
    LanList5->headLabel->add_event_cb(albumLanguage_event_handler,LV_EVENT_CLICKED,this);

    LanList6 =new albumLanguageList(LanguageList->myobj);
    LanList6->nameLabel->set_txt(STR_LAU_RU);
    LanList6->headLabel->add_event_cb(albumLanguage_event_handler,LV_EVENT_CLICKED,this);

    LanList7 =new albumLanguageList(LanguageList->myobj);
    LanList7->nameLabel->set_txt(STR_LAU_JP);
    LanList7->headLabel->add_event_cb(albumLanguage_event_handler,LV_EVENT_CLICKED,this);

    LanList8 =new albumLanguageList(LanguageList->myobj);
    LanList8->nameLabel->set_txt(STR_LAU_CN);
    LanList8->headLabel->add_event_cb(albumLanguage_event_handler,LV_EVENT_CLICKED,this);
    albumLanguage_SelIndex(lauIndex,lauIndex);
}
albumLanguage::~albumLanguage(void)
{
    if(LanList1 != NULL)
    {
        delete LanList1;
        LanList1 = NULL;
    }
    if(LanList2 != NULL)
    {
        delete LanList2;
        LanList2 = NULL;
    }
    if(LanList3 != NULL)
    {
        delete LanList3;
        LanList3 = NULL;
    }
    if(LanList4 != NULL)
    {
        delete LanList4;
        LanList4 = NULL;
    }
    if(LanList5 != NULL)
    {
        delete LanList5;
        LanList5 = NULL;
    }
    if(LanList6 != NULL)
    {
        delete LanList6;
        LanList6 = NULL;
    }
    if(LanList7 != NULL)
    {
        delete LanList7;
        LanList7 = NULL;
    }
    if(LanList8 != NULL)
    {
        delete LanList8;
        LanList8 = NULL;
    }
    if(LanguageList != NULL)
    {
        delete LanguageList;
        LanguageList = NULL;
    }
    if(LanguageScreen != NULL)
    {
        delete LanguageScreen;
        LanguageScreen = NULL;
    }
}
void albumLanguage::albumLanguage_SelIndex(int index,int saveIndex)
{
    switch(saveIndex)
    {
        case 0:
            LanList1->iconLabel->show(false);
            break;
        case 1:
            LanList2->iconLabel->show(false);
            break;
        case 2:
            LanList3->iconLabel->show(false);
            break;
        case 3:
            LanList4->iconLabel->show(false);
            break;
        case 4:
            LanList5->iconLabel->show(false);
            break;
        case 5:
            LanList6->iconLabel->show(false);
            break;
        case 6:
            LanList7->iconLabel->show(false);
            break;
        case 7:
            LanList8->iconLabel->show(false);
            break;
        default:
            break;
    }

    switch(index)
    {
        case 0:
            LanList1->iconLabel->show(true);
            break;
        case 1:
            LanList2->iconLabel->show(true);
            break;
        case 2:
            LanList3->iconLabel->show(true);
            break;
        case 3:
            LanList4->iconLabel->show(true);
            break;
        case 4:
            LanList5->iconLabel->show(true);
            break;
        case 5:
            LanList6->iconLabel->show(true);
            break;
        case 6:
            LanList7->iconLabel->show(true);
            break;
        case 7:
            LanList8->iconLabel->show(true);
            break;
        default:
            break;
    }
    lauIndex = index;
#ifdef _UCHIP_T113
    write_int_type_param(PUBLIC_SCENE, LANGUAGE, lauIndex);
#endif
}
void albumLanguage::albumLanguage_event_handler(lv_event_t *event)
{
    albumLanguage* opt = (albumLanguage*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    int lauIndex =0;

    if((opt->LanList1 !=NULL)&&(target ==opt->LanList1->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            lauIndex =0;
            opt->albumLanguage_SelIndex(lauIndex,opt->lauIndex);
        }
    }
    else if((opt->LanList2 !=NULL)&&(target ==opt->LanList2->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            lauIndex =1;
            opt->albumLanguage_SelIndex(lauIndex,opt->lauIndex);
        }
    }
    else if((opt->LanList3 !=NULL)&&(target ==opt->LanList3->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            lauIndex =2;
            opt->albumLanguage_SelIndex(lauIndex,opt->lauIndex);
        }
    }
    else if((opt->LanList4 !=NULL)&&(target ==opt->LanList4->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            lauIndex =3;
            opt->albumLanguage_SelIndex(lauIndex,opt->lauIndex);
        }
    }
    else if((opt->LanList5 !=NULL)&&(target ==opt->LanList5->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            lauIndex =4;
            opt->albumLanguage_SelIndex(lauIndex,opt->lauIndex);
        }
    }
    else if((opt->LanList6 !=NULL)&&(target ==opt->LanList6->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            lauIndex =5;
            opt->albumLanguage_SelIndex(lauIndex,opt->lauIndex);
        }
    }
    else if((opt->LanList7 !=NULL)&&(target ==opt->LanList7->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            lauIndex =6;
            opt->albumLanguage_SelIndex(lauIndex,opt->lauIndex);
        }
    }
    else if((opt->LanList8 !=NULL)&&(target ==opt->LanList8->headLabel->myobj))
    {
        if(event->code== LV_EVENT_CLICKED)
        {
            lauIndex =7;
            opt->albumLanguage_SelIndex(lauIndex,opt->lauIndex);
        }
    }
}
