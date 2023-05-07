#include "help_sence.h"
#include "mainstart/include/ui_config.h"
#include "mainstart/include/str_config.h"
#include "mainstart/include/configCustom.h"
#include "mainstart/customer_config.h"
#ifdef _UCHIP_T113
#include  "common/common.h"
#endif

void helpSence::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    HEAD_RETURN_PNG=(void*)parse_image_from_file(HEAD_RETURN_PNG_PATH);
    SETTING_ICON_SCENE1_PNG=(void*)parse_image_from_file(SETTING_ICON_SCENE1_PNG_PATH);
    SETTING_ICON_SCENE2_PNG=(void*)parse_image_from_file(SETTING_ICON_SCENE2_PNG_PATH);
    SETTING_ICON_SCENE3_PNG=(void*)parse_image_from_file(SETTING_ICON_SCENE3_PNG_PATH);
    SETTING_ICON_SCENE4_PNG=(void*)parse_image_from_file(SETTING_ICON_SCENE4_PNG_PATH);
    SETTING_ICON_SCENE5_PNG=(void*)parse_image_from_file(SETTING_ICON_SCENE5_PNG_PATH);
	SETTING_GOOGLE_PNG=(void*)parse_image_from_file(SETTING_GOOGLE_PNG_PATH);
	SETTING_IOSAPP_PNG=(void*)parse_image_from_file(SETTING_IOSAPP_PNG_PATH);
    SETTING_LEFT_PNG=(void*)parse_image_from_file(SETTING_LEFT_PNG_PATH);
    SETTING_RIGHT_PNG=(void*)parse_image_from_file(SETTING_RIGHT_PNG_PATH);
    SETTING_SCENE1_PNG=(void*)parse_image_from_file(SETTING_SCENE1_PNG_PATH);
    SETTING_SCENE2_PNG=(void*)parse_image_from_file(SETTING_SCENE2_PNG_PATH);
    SETTING_SCENE3_PNG=(void*)parse_image_from_file(SETTING_SCENE3_PNG_PATH);
    SETTING_SCENE4_PNG=(void*)parse_image_from_file(SETTING_SCENE4_PNG_PATH);
    SETTING_SCENE5_PNG=(void*)parse_image_from_file(SETTING_SCENE5_PNG_PATH);
    SETTING_SCENE6_PNG=(void*)parse_image_from_file(SETTING_SCENE6_PNG_PATH);
#endif
}

void helpSence::ui_image_free(void)
{
#ifdef IMAGE_DECODE
    free_image(HEAD_RETURN_PNG);
    free_image(SETTING_ICON_SCENE1_PNG);
    free_image(SETTING_ICON_SCENE2_PNG);
    free_image(SETTING_ICON_SCENE3_PNG);
    free_image(SETTING_ICON_SCENE4_PNG);
    free_image(SETTING_ICON_SCENE5_PNG);
	free_image(SETTING_GOOGLE_PNG);
	free_image(SETTING_IOSAPP_PNG);
    free_image(SETTING_LEFT_PNG);
    free_image(SETTING_RIGHT_PNG);
    free_image(SETTING_SCENE1_PNG);
    free_image(SETTING_SCENE2_PNG);
    free_image(SETTING_SCENE3_PNG);
    free_image(SETTING_SCENE4_PNG);
    free_image(SETTING_SCENE5_PNG);
    free_image(SETTING_SCENE6_PNG);
#endif
}
helpSence::helpSence(void)
{
    char googleLink[512]={0};
    char iosLink[512]={0};
    char devCode[24]={0};
    char buff[24]={0};
    char buff1[4]={0};
    char buff2[4]={0};
    char buff3[4]={0};

	ui_image_decode();
#ifdef _UCHIP_T113
    read_string_type_param(WEATHER_SCENE, GOOGLELINK, googleLink,sizeof(googleLink));
    read_string_type_param(WEATHER_SCENE, IOSLINK, iosLink,sizeof(iosLink));
    read_string_type_param(WEATHER_SCENE, DEVCODE,devCode,sizeof(devCode));
#endif
    memcpy(buff1,devCode,3);
    memcpy(buff2,devCode+3,3);
    memcpy(buff3,devCode+6,3);
    sprintf(buff,"%s %s %s",buff1,buff2,buff3);
    helpScreen = new LvcppScreen(lv_scr_act());
    helpScreen->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    helpScreen->set_main_bg_color(lv_color_hex(0x0499c3),LV_OPA_100);

    helpList = new LvcppList(helpScreen->myobj);
    helpList->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    helpList->center_align();
    helpList->set_main_bg_opa(LV_OPA_0);
    helpList->set_flex_flow(LV_FLEX_FLOW_ROW);
    helpList->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    helpList->set_scrollbar_snap_x(LV_SCROLL_SNAP_START);
    helpList->set_main_pad_all(0);
    helpList->set_main_pad_row(0);
    helpList->set_main_pad_column(0);
    helpList->set_main_border_width(0);
    helpList->set_main_radius(0);
    helpList->add_event_cb(helpSence_event_handler,LV_EVENT_SCROLL_END,this);

    helpSceneLabel1 = new LvcppLabel(helpList->myobj);
    helpSceneLabel1->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    helpSceneLabel1->set_main_bg_opa(LV_OPA_0);
    helpSceneLabel1->align(LV_ALIGN_TOP_LEFT,0,0);
    helpSceneLabel1->set_txt("");

    helpSceneLabel2 = new LvcppLabel(helpList->myobj);
    helpSceneLabel2->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    helpSceneLabel2->set_main_bg_opa(LV_OPA_0);
    helpSceneLabel2->align(LV_ALIGN_TOP_LEFT,0,0);
    helpSceneLabel2->set_txt("");

    helpSceneLabel3 = new LvcppLabel(helpList->myobj);
    helpSceneLabel3->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    helpSceneLabel3->set_main_bg_opa(LV_OPA_0);
    helpSceneLabel3->align(LV_ALIGN_TOP_LEFT,0,0);
    helpSceneLabel3->set_txt("");

    helpSceneLabel4 = new LvcppLabel(helpList->myobj);
    helpSceneLabel4->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    helpSceneLabel4->set_main_bg_opa(LV_OPA_0);
    helpSceneLabel4->align(LV_ALIGN_TOP_LEFT,0,0);
    helpSceneLabel4->set_txt("");

    helpSceneLabel5 = new LvcppLabel(helpList->myobj);
    helpSceneLabel5->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    helpSceneLabel5->set_main_bg_opa(LV_OPA_0);
    helpSceneLabel5->align(LV_ALIGN_TOP_LEFT,0,0);
    helpSceneLabel5->set_txt("");

    helpSceneLabel6 = new LvcppLabel(helpList->myobj);
    helpSceneLabel6->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    helpSceneLabel6->set_main_bg_opa(LV_OPA_0);
    helpSceneLabel6->align(LV_ALIGN_TOP_LEFT,0,0);
    helpSceneLabel6->set_txt("");

    helpHeadLabel1 = new LvcppLabel(helpSceneLabel1->myobj);
    helpHeadLabel1->set_size(600,80);
    helpHeadLabel1->align(LV_ALIGN_TOP_LEFT,40,260);
    helpHeadLabel1->set_main_border_width(0);
    helpHeadLabel1->set_main_bg_opa(LV_OPA_0);
    helpHeadLabel1->txt_color(lv_color_white(),LV_PART_MAIN);
    helpHeadLabel1->txt_font_size(34, FT_FONT_STYLE_BOLD);
    helpHeadLabel1->txt_align(LV_TEXT_ALIGN_CENTER);
    helpHeadLabel1->txt_long_mode(LV_LABEL_LONG_WRAP);
    helpHeadLabel1->set_txt(STR_HELPHEAD1);

    helpStrLabel1 = new LvcppLabel(helpSceneLabel1->myobj);
    helpStrLabel1->set_size(600,320);
    helpStrLabel1->align(LV_ALIGN_TOP_LEFT,40,350);
    helpStrLabel1->set_main_border_width(0);
    helpStrLabel1->set_main_bg_opa(LV_OPA_0);
    helpStrLabel1->txt_color(lv_color_white(),LV_PART_MAIN);
    helpStrLabel1->txt_font_size(34, FT_FONT_STYLE_NORMAL);
    helpStrLabel1->txt_align(LV_TEXT_ALIGN_CENTER);
    helpStrLabel1->txt_long_mode(LV_LABEL_LONG_WRAP);
    helpStrLabel1->set_txt(STR_HELPSTR1);

    helpIconLabel1 = new LvcppLabel(helpSceneLabel1->myobj);
    helpIconLabel1->set_size(500,500);
    helpIconLabel1->align(LV_ALIGN_TOP_LEFT,690,150);
    helpIconLabel1->set_main_bg_opa(LV_OPA_0);
    helpIconLabel1->set_main_bg_img_src(SETTING_ICON_SCENE1_PNG);
    helpIconLabel1->set_txt("");

    helpGoogleLabel1 = new LvcppLabel(helpIconLabel1->myobj);
    helpGoogleLabel1->set_size(100,30);
    helpGoogleLabel1->align(LV_ALIGN_TOP_LEFT,130,287);
    helpGoogleLabel1->set_main_bg_opa(LV_OPA_0);
    helpGoogleLabel1->set_main_bg_img_src(SETTING_GOOGLE_PNG);
    helpGoogleLabel1->set_txt("");

    helpIOSLabel1 = new LvcppLabel(helpIconLabel1->myobj);
    helpIOSLabel1->set_size(100,30);
    helpIOSLabel1->align(LV_ALIGN_TOP_LEFT,250,287);
    helpIOSLabel1->set_main_bg_opa(LV_OPA_0);
    helpIOSLabel1->set_main_bg_img_src(SETTING_IOSAPP_PNG);
    helpIOSLabel1->set_txt("");

    GoogleqrcodeLabel = new LvcppLabel(helpIconLabel1->myobj);
    GoogleqrcodeLabel->set_size(100,100);
    GoogleqrcodeLabel->align(LV_ALIGN_TOP_LEFT,130,182);
    GoogleqrcodeLabel->set_main_bg_color(lv_color_white(),LV_OPA_100);
    GoogleqrcodeLabel->set_main_radius(10);
    GoogleqrcodeLabel->set_txt("");

    IOSqrcodeLabel = new LvcppLabel(helpIconLabel1->myobj);
    IOSqrcodeLabel->set_size(100,100);
    IOSqrcodeLabel->align(LV_ALIGN_TOP_LEFT,250,182);
    IOSqrcodeLabel->set_main_bg_color(lv_color_white(),LV_OPA_100);
    IOSqrcodeLabel->set_main_radius(10);
    IOSqrcodeLabel->set_txt("");

    GoogleQrcode = new LvcppQrcode(GoogleqrcodeLabel->myobj);
    GoogleQrcode->center_align();
    GoogleQrcode->set_size(90,90);
    GoogleQrcode->set_main_border_width(0);
    GoogleQrcode->qrcode_creat(googleLink,90,0);

    IOSQrcode = new LvcppQrcode(IOSqrcodeLabel->myobj);
    IOSQrcode->center_align();
    IOSQrcode->set_size(90,90);
    IOSQrcode->set_main_border_width(0);
    IOSQrcode->qrcode_creat(iosLink,90,0);

    helpHeadLabel2 = new LvcppLabel(helpSceneLabel2->myobj);
    helpHeadLabel2->set_size(600,80);
    helpHeadLabel2->align(LV_ALIGN_TOP_LEFT,40,260);
    helpHeadLabel2->set_main_border_width(0);
    helpHeadLabel2->set_main_bg_opa(LV_OPA_0);
    helpHeadLabel2->txt_color(lv_color_white(),LV_PART_MAIN);
    helpHeadLabel2->txt_font_size(34, FT_FONT_STYLE_BOLD);
    helpHeadLabel2->txt_align(LV_TEXT_ALIGN_CENTER);
    helpHeadLabel2->txt_long_mode(LV_LABEL_LONG_WRAP);
    helpHeadLabel2->set_txt(STR_HELPHEAD2);

    helpStrLabel2 = new LvcppLabel(helpSceneLabel2->myobj);
    helpStrLabel2->set_size(600,320);
    helpStrLabel2->align(LV_ALIGN_TOP_LEFT,40,350);
    helpStrLabel2->set_main_border_width(0);
    helpStrLabel2->set_main_bg_opa(LV_OPA_0);
    helpStrLabel2->txt_color(lv_color_white(),LV_PART_MAIN);
    helpStrLabel2->txt_font_size(34, FT_FONT_STYLE_NORMAL);
    helpStrLabel2->txt_align(LV_TEXT_ALIGN_CENTER);
    helpStrLabel2->txt_long_mode(LV_LABEL_LONG_WRAP);
    helpStrLabel2->set_txt(STR_HELPSTR2);

    helpIconLabel2 = new LvcppLabel(helpSceneLabel2->myobj);
    helpIconLabel2->set_size(500,500);
    helpIconLabel2->align(LV_ALIGN_TOP_LEFT,690,150);
    helpIconLabel2->set_main_bg_opa(LV_OPA_0);
    helpIconLabel2->set_main_bg_img_src(SETTING_ICON_SCENE1_PNG);
    helpIconLabel2->set_txt("");

    DevqrcodeLabel = new LvcppLabel(helpIconLabel2->myobj);
    DevqrcodeLabel->set_size(220,180);
    DevqrcodeLabel->center_align();
    DevqrcodeLabel->set_main_bg_color(lv_color_white(),LV_OPA_100);
    DevqrcodeLabel->set_main_radius(10);
    DevqrcodeLabel->set_txt("");

    DevQrcode = new LvcppQrcode(DevqrcodeLabel->myobj);
    DevQrcode->align(LV_ALIGN_TOP_MID,0,0);
    DevQrcode->set_size(150,150);
    DevQrcode->set_main_border_width(0);
    DevQrcode->qrcode_creat(devCode,150,0);

    connectLabel = new LvcppLabel(DevqrcodeLabel->myobj);
    connectLabel->set_size(100,20);
    connectLabel->align(LV_ALIGN_BOTTOM_LEFT,5,-5);
    connectLabel->set_main_border_width(0);
    connectLabel->set_main_bg_opa(LV_OPA_0);
    connectLabel->txt_color(lv_color_black(),LV_PART_MAIN);
    connectLabel->txt_font_size(12, FT_FONT_STYLE_NORMAL);
    connectLabel->txt_align(LV_TEXT_ALIGN_LEFT);
    connectLabel->txt_long_mode(LV_LABEL_LONG_WRAP);
    connectLabel->set_txt(STR_CONNECTIONCODE);

    devIdLabel = new LvcppLabel(DevqrcodeLabel->myobj);
    devIdLabel->set_size(100,20);
    devIdLabel->align(LV_ALIGN_BOTTOM_LEFT,110,-10);
    devIdLabel->set_main_border_width(0);
    devIdLabel->set_main_bg_opa(LV_OPA_0);
    devIdLabel->txt_color(lv_color_hex(0xff0000),LV_PART_MAIN);
    devIdLabel->txt_font_size(18, FT_FONT_STYLE_NORMAL);
    devIdLabel->txt_align(LV_TEXT_ALIGN_LEFT);
    devIdLabel->txt_long_mode(LV_LABEL_LONG_WRAP);
    devIdLabel->set_txt(buff);

    helpHeadLabel3 = new LvcppLabel(helpSceneLabel3->myobj);
    helpHeadLabel3->set_size(600,80);
    helpHeadLabel3->align(LV_ALIGN_TOP_LEFT,40,260);
    helpHeadLabel3->set_main_border_width(0);
    helpHeadLabel3->set_main_bg_opa(LV_OPA_0);
    helpHeadLabel3->txt_color(lv_color_white(),LV_PART_MAIN);
    helpHeadLabel3->txt_font_size(34, FT_FONT_STYLE_BOLD);
    helpHeadLabel3->txt_align(LV_TEXT_ALIGN_CENTER);
    helpHeadLabel3->txt_long_mode(LV_LABEL_LONG_WRAP);
    helpHeadLabel3->set_txt(STR_HELPHEAD3);

    helpStrLabel3 = new LvcppLabel(helpSceneLabel3->myobj);
    helpStrLabel3->set_size(600,320);
    helpStrLabel3->align(LV_ALIGN_TOP_LEFT,40,350);
    helpStrLabel3->set_main_border_width(0);
    helpStrLabel3->set_main_bg_opa(LV_OPA_0);
    helpStrLabel3->txt_color(lv_color_white(),LV_PART_MAIN);
    helpStrLabel3->txt_font_size(34, FT_FONT_STYLE_NORMAL);
    helpStrLabel3->txt_align(LV_TEXT_ALIGN_CENTER);
    helpStrLabel3->txt_long_mode(LV_LABEL_LONG_WRAP);
    helpStrLabel3->set_txt(STR_HELPSTR3);

    helpIconLabel3 = new LvcppLabel(helpSceneLabel3->myobj);
    helpIconLabel3->set_size(500,500);
    helpIconLabel3->align(LV_ALIGN_TOP_LEFT,690,150);
    helpIconLabel3->set_main_bg_opa(LV_OPA_0);
    helpIconLabel3->set_main_bg_img_src(SETTING_ICON_SCENE2_PNG);
    helpIconLabel3->set_txt("");

    DevqrcodeLabel1 = new LvcppLabel(helpIconLabel3->myobj);
    DevqrcodeLabel1->set_size(220,130);
    DevqrcodeLabel1->align(LV_ALIGN_TOP_LEFT,220,105);
    DevqrcodeLabel1->set_main_bg_color(lv_color_white(),LV_OPA_100);
    DevqrcodeLabel1->set_main_radius(10);
    DevqrcodeLabel1->set_txt("");

    DevQrcode1 = new LvcppQrcode(DevqrcodeLabel1->myobj);
    DevQrcode1->align(LV_ALIGN_TOP_MID,0,0);
    DevQrcode1->set_size(100,100);
    DevQrcode1->set_main_border_width(0);
    DevQrcode1->qrcode_creat(devCode,100,0);

    connectLabel1 = new LvcppLabel(DevqrcodeLabel1->myobj);
    connectLabel1->set_size(100,20);
    connectLabel1->align(LV_ALIGN_BOTTOM_LEFT,5,-5);
    connectLabel1->set_main_border_width(0);
    connectLabel1->set_main_bg_opa(LV_OPA_0);
    connectLabel1->txt_color(lv_color_black(),LV_PART_MAIN);
    connectLabel1->txt_font_size(12, FT_FONT_STYLE_NORMAL);
    connectLabel1->txt_align(LV_TEXT_ALIGN_LEFT);
    connectLabel1->txt_long_mode(LV_LABEL_LONG_WRAP);
    connectLabel1->set_txt(STR_CONNECTIONCODE);

    devIdLabel1 = new LvcppLabel(DevqrcodeLabel1->myobj);
    devIdLabel1->set_size(100,20);
    devIdLabel1->align(LV_ALIGN_BOTTOM_LEFT,110,-10);
    devIdLabel1->set_main_border_width(0);
    devIdLabel1->set_main_bg_opa(LV_OPA_0);
    devIdLabel1->txt_color(lv_color_hex(0xff0000),LV_PART_MAIN);
    devIdLabel1->txt_font_size(18, FT_FONT_STYLE_NORMAL);
    devIdLabel1->txt_align(LV_TEXT_ALIGN_LEFT);
    devIdLabel1->txt_long_mode(LV_LABEL_LONG_WRAP);
    devIdLabel1->set_txt(buff);

    helpHeadLabel4 = new LvcppLabel(helpSceneLabel4->myobj);
    helpHeadLabel4->set_size(600,80);
    helpHeadLabel4->align(LV_ALIGN_TOP_LEFT,40,260);
    helpHeadLabel4->set_main_border_width(0);
    helpHeadLabel4->set_main_bg_opa(LV_OPA_0);
    helpHeadLabel4->txt_color(lv_color_white(),LV_PART_MAIN);
    helpHeadLabel4->txt_font_size(34, FT_FONT_STYLE_BOLD);
    helpHeadLabel4->txt_align(LV_TEXT_ALIGN_LEFT);
    helpHeadLabel4->txt_long_mode(LV_LABEL_LONG_WRAP);
    helpHeadLabel4->set_txt(STR_HELPHEAD4);

    helpStrLabel4 = new LvcppLabel(helpSceneLabel4->myobj);
    helpStrLabel4->set_size(600,320);
    helpStrLabel4->align(LV_ALIGN_TOP_LEFT,40,350);
    helpStrLabel4->set_main_border_width(0);
    helpStrLabel4->set_main_bg_opa(LV_OPA_0);
    helpStrLabel4->txt_color(lv_color_white(),LV_PART_MAIN);
    helpStrLabel4->txt_font_size(34, FT_FONT_STYLE_NORMAL);
    helpStrLabel4->txt_align(LV_TEXT_ALIGN_CENTER);
    helpStrLabel4->txt_long_mode(LV_LABEL_LONG_WRAP);
    helpStrLabel4->set_txt(STR_HELPSTR4);

    helpIconLabel4 = new LvcppLabel(helpSceneLabel4->myobj);
    helpIconLabel4->set_size(500,500);
    helpIconLabel4->align(LV_ALIGN_TOP_LEFT,690,150);
    helpIconLabel4->set_main_bg_opa(LV_OPA_0);
    helpIconLabel4->set_main_bg_img_src(SETTING_ICON_SCENE3_PNG);
    helpIconLabel4->set_txt("");

    helpHeadLabel5 = new LvcppLabel(helpSceneLabel5->myobj);
    helpHeadLabel5->set_size(600,80);
    helpHeadLabel5->align(LV_ALIGN_TOP_LEFT,40,260);
    helpHeadLabel5->set_main_border_width(0);
    helpHeadLabel5->set_main_bg_opa(LV_OPA_0);
    helpHeadLabel5->txt_color(lv_color_white(),LV_PART_MAIN);
    helpHeadLabel5->txt_font_size(34, FT_FONT_STYLE_BOLD);
    helpHeadLabel5->txt_align(LV_TEXT_ALIGN_CENTER);
    helpHeadLabel5->txt_long_mode(LV_LABEL_LONG_WRAP);
    helpHeadLabel5->set_txt(STR_HELPHEAD5);

    helpStrLabel5 = new LvcppLabel(helpSceneLabel5->myobj);
    helpStrLabel5->set_size(600,320);
    helpStrLabel5->align(LV_ALIGN_TOP_LEFT,40,350);
    helpStrLabel5->set_main_border_width(0);
    helpStrLabel5->set_main_bg_opa(LV_OPA_0);
    helpStrLabel5->txt_color(lv_color_white(),LV_PART_MAIN);
    helpStrLabel5->txt_font_size(34, FT_FONT_STYLE_NORMAL);
    helpStrLabel5->txt_align(LV_TEXT_ALIGN_CENTER);
    helpStrLabel5->txt_long_mode(LV_LABEL_LONG_WRAP);
    helpStrLabel5->set_txt(STR_HELPSTR5);

    helpIconLabel5 = new LvcppLabel(helpSceneLabel5->myobj);
    helpIconLabel5->set_size(500,500);
    helpIconLabel5->align(LV_ALIGN_TOP_LEFT,690,150);
    helpIconLabel5->set_main_bg_opa(LV_OPA_0);
    helpIconLabel5->set_main_bg_img_src(SETTING_ICON_SCENE4_PNG);
    helpIconLabel5->set_txt("");

    helpHeadLabel6 = new LvcppLabel(helpSceneLabel6->myobj);
    helpHeadLabel6->set_size(600,80);
    helpHeadLabel6->align(LV_ALIGN_TOP_LEFT,40,260);
    helpHeadLabel6->set_main_border_width(0);
    helpHeadLabel6->set_main_bg_opa(LV_OPA_0);
    helpHeadLabel6->txt_color(lv_color_white(),LV_PART_MAIN);
    helpHeadLabel6->txt_font_size(34, FT_FONT_STYLE_BOLD);
    helpHeadLabel6->txt_align(LV_TEXT_ALIGN_CENTER);
    helpHeadLabel6->txt_long_mode(LV_LABEL_LONG_WRAP);
    helpHeadLabel6->set_txt(STR_HELPHEAD6);

    helpHeadLabel6 = new LvcppLabel(helpSceneLabel6->myobj);
    helpHeadLabel6->set_size(600,320);
    helpHeadLabel6->align(LV_ALIGN_TOP_LEFT,40,350);
    helpHeadLabel6->set_main_border_width(0);
    helpHeadLabel6->set_main_bg_opa(LV_OPA_0);
    helpHeadLabel6->txt_color(lv_color_white(),LV_PART_MAIN);
    helpHeadLabel6->txt_font_size(34, FT_FONT_STYLE_NORMAL);
    helpHeadLabel6->txt_align(LV_TEXT_ALIGN_CENTER);
    helpHeadLabel6->txt_long_mode(LV_LABEL_LONG_WRAP);
    helpHeadLabel6->set_txt(STR_HELPSTR6);

    helpIconLabel6 = new LvcppLabel(helpSceneLabel6->myobj);
    helpIconLabel6->set_size(500,500);
    helpIconLabel6->align(LV_ALIGN_TOP_LEFT,690,150);
    helpIconLabel6->set_main_bg_opa(LV_OPA_0);
    helpIconLabel6->set_main_bg_img_src(SETTING_ICON_SCENE5_PNG);
    helpIconLabel6->set_txt("");

    helpLeft = new LvcppButton(helpScreen->myobj);
    helpLeft->set_size(70,70);
    helpLeft->align(LV_ALIGN_BOTTOM_LEFT,450,-30);
    helpLeft->set_main_bg_color(lv_color_hex(0x0499c3),LV_OPA_100);
    helpLeft->set_main_radius(35);
    helpLeft->set_main_pad_all(0);
    helpLeft->set_main_border_width(0);
    helpLeft->set_main_bg_img_src(SETTING_LEFT_PNG);
    helpLeft->add_event_cb(helpSence_event_handler,LV_EVENT_RELEASED,this);

    helpRight = new LvcppButton(helpScreen->myobj);
    helpRight->set_size(70,70);
    helpRight->align(LV_ALIGN_BOTTOM_RIGHT,-450,-30);
    helpRight->set_main_bg_color(lv_color_hex(0x0499c3),LV_OPA_100);
    helpRight->set_main_radius(35);
    helpRight->set_main_pad_all(0);
    helpRight->set_main_border_width(0);
    helpRight->set_main_bg_img_src(SETTING_RIGHT_PNG);
    helpRight->add_event_cb(helpSence_event_handler,LV_EVENT_RELEASED,this);
    helpLeft->show(false);
    show_scene_num(curScene);
}
void helpSence::show_scene_num(int type)
{
#ifdef IMAGE_DECODE
    void *scenePatch[6]={SETTING_SCENE1_PNG,SETTING_SCENE2_PNG,SETTING_SCENE3_PNG,
                        SETTING_SCENE4_PNG,SETTING_SCENE5_PNG,SETTING_SCENE6_PNG};
#endif
    if(senceLabel ==NULL)
    {
        senceLabel = new LvcppLabel(helpScreen->myobj);
        senceLabel->set_size(85,12);
        senceLabel->align(LV_ALIGN_BOTTOM_MID,0,-59);
        senceLabel->set_main_bg_opa(LV_OPA_0);
        senceLabel->set_txt("");
    }
    senceLabel->set_main_bg_img_src(scenePatch[type]);
}
helpSence::~helpSence(void)
{
	if(senceLabel !=NULL)
    {
        delete senceLabel;
        senceLabel = NULL;
    }
    if(helpRight !=NULL)
    {
        delete helpRight;
        helpRight = NULL;
    }
    if(helpLeft !=NULL)
    {
        delete helpLeft;
        helpLeft = NULL;
    }
    if(helpIconLabel6 !=NULL)
    {
        delete helpIconLabel6;
        helpIconLabel6 = NULL;
    }
    if(helpStrLabel6 !=NULL)
    {
        delete helpStrLabel6;
        helpStrLabel6 = NULL;
    }
    if(helpHeadLabel6 !=NULL)
    {
        delete helpHeadLabel6;
        helpHeadLabel6 = NULL;
    }
    if(helpIconLabel5 !=NULL)
    {
        delete helpIconLabel5;
        helpIconLabel5 = NULL;
    }
    if(helpStrLabel5 !=NULL)
    {
        delete helpStrLabel5;
        helpStrLabel5 = NULL;
    }
    if(helpHeadLabel5 !=NULL)
    {
        delete helpHeadLabel5;
        helpHeadLabel5 = NULL;
    }
    if(helpIconLabel4 !=NULL)
    {
        delete helpIconLabel4;
        helpIconLabel4 = NULL;
    }
    if(helpStrLabel4 !=NULL)
    {
        delete helpStrLabel4;
        helpStrLabel4 = NULL;
    }
    if(helpHeadLabel4 !=NULL)
    {
        delete helpHeadLabel4;
        helpHeadLabel4 = NULL;
    }
    if(devIdLabel1 !=NULL)
    {
        delete devIdLabel1;
        devIdLabel1 = NULL;
    }
    if(connectLabel1 !=NULL)
    {
        delete connectLabel1;
        connectLabel1 = NULL;
    }
    if(DevQrcode1 !=NULL)
    {
        delete DevQrcode1;
        DevQrcode1 = NULL;
    }
    if(DevqrcodeLabel1 !=NULL)
    {
        delete DevqrcodeLabel1;
        DevqrcodeLabel1 = NULL;
    }
    if(helpIconLabel3 !=NULL)
    {
        delete helpIconLabel3;
        helpIconLabel3 = NULL;
    }
    if(helpStrLabel3 !=NULL)
    {
        delete helpStrLabel3;
        helpStrLabel3 = NULL;
    }
    if(helpHeadLabel3 !=NULL)
    {
        delete helpHeadLabel3;
        helpHeadLabel3 = NULL;
    }
    if(devIdLabel !=NULL)
    {
        delete devIdLabel;
        devIdLabel = NULL;
    }
    if(connectLabel !=NULL)
    {
        delete connectLabel;
        connectLabel = NULL;
    }
    if(DevQrcode !=NULL)
    {
        delete DevQrcode;
        DevQrcode = NULL;
    }
    if(DevqrcodeLabel !=NULL)
    {
        delete DevqrcodeLabel;
        DevqrcodeLabel = NULL;
    }
    if(helpIconLabel2 !=NULL)
    {
        delete helpIconLabel2;
        helpIconLabel2 = NULL;
    }
    if(helpStrLabel2 !=NULL)
    {
        delete helpStrLabel2;
        helpStrLabel2 = NULL;
    }
    if(helpHeadLabel2 !=NULL)
    {
        delete helpHeadLabel2;
        helpHeadLabel2 = NULL;
    }
    if(GoogleQrcode !=NULL)
    {
        delete GoogleQrcode;
        GoogleQrcode = NULL;
    }
    if(IOSQrcode !=NULL)
    {
        delete IOSQrcode;
        IOSQrcode = NULL;
    }
    if(GoogleqrcodeLabel !=NULL)
    {
        delete GoogleqrcodeLabel;
        GoogleqrcodeLabel = NULL;
    }
    if(IOSqrcodeLabel !=NULL)
    {
        delete IOSqrcodeLabel;
        IOSqrcodeLabel = NULL;
    }
    if(helpGoogleLabel1 !=NULL)
    {
        delete helpGoogleLabel1;
        helpGoogleLabel1 = NULL;
    }
    if(helpIOSLabel1 !=NULL)
    {
        delete helpIOSLabel1;
        helpIOSLabel1 = NULL;
    }
    if(helpIconLabel1 !=NULL)
    {
        delete helpIconLabel1;
        helpIconLabel1 = NULL;
    }
    if(helpStrLabel1 !=NULL)
    {
        delete helpStrLabel1;
        helpStrLabel1 = NULL;
    }
    if(helpHeadLabel1 !=NULL)
    {
        delete helpHeadLabel1;
        helpHeadLabel1 = NULL;
    }
    if(helpSceneLabel6 !=NULL)
    {
        delete helpSceneLabel6;
        helpSceneLabel6 = NULL;
    }
    if(helpSceneLabel5 !=NULL)
    {
        delete helpSceneLabel5;
        helpSceneLabel5 = NULL;
    }
    if(helpSceneLabel4 !=NULL)
    {
        delete helpSceneLabel4;
        helpSceneLabel4 = NULL;
    }
    if(helpSceneLabel3 !=NULL)
    {
        delete helpSceneLabel3;
        helpSceneLabel3 = NULL;
    }
    if(helpSceneLabel2 !=NULL)
    {
        delete helpSceneLabel2;
        helpSceneLabel2 = NULL;
    }
    if(helpSceneLabel1 !=NULL)
    {
        delete helpSceneLabel1;
        helpSceneLabel1 = NULL;
    }
    if(helpList !=NULL)
    {
        delete helpList;
        helpList = NULL;
    }
    if(helpScreen !=NULL)
    {
        delete helpScreen;
        helpScreen = NULL;
    }
    ui_image_free();
}
void helpSence::helpSence_event_handler(lv_event_t *event)
{
    helpSence* opt = (helpSence*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if((opt->helpList !=NULL)&&(target ==opt->helpList->myobj))
    {
        if(event->code== LV_EVENT_SCROLL_END)
        {
            opt->curScene = opt->helpList->get_scroll_x()/SCREEN_HOR_SIZE;
            opt->show_scene_num(opt->curScene);
			if(opt->curScene ==0)
            {
                opt->helpLeft->show(false);
            }
			else if(opt->curScene ==5)
            {
                opt->helpRight->show(false);
            }
			else
			{
                opt->helpLeft->show(true);
				opt->helpRight->show(true);
			}

        }
    }
    else if((opt->helpLeft !=NULL)&&(target ==opt->helpLeft->myobj))
    {
        if(event->code== LV_EVENT_RELEASED)
        {
            opt->curScene --;
            if(opt->curScene<0)
            {
                opt->curScene =0;
            }
            else
            {
                if(opt->curScene ==0)
                {
                    opt->helpLeft->show(false);
                }
                opt->helpRight->show(true);
                opt->show_scene_num(opt->curScene);
                opt->helpList->set_scroll_to(opt->curScene*SCREEN_HOR_SIZE, 0, LV_ANIM_OFF);
            }
        }
    }
    else if((opt->helpRight !=NULL)&&(target ==opt->helpRight->myobj))
    {
        if(event->code== LV_EVENT_RELEASED)
        {
            opt->curScene ++;
            if(opt->curScene>5)
            {
                opt->curScene =5;
            }
            else
            {
                if(opt->curScene ==5)
                {
                    opt->helpRight->show(false);
                }
                opt->helpLeft->show(true);
                opt->show_scene_num(opt->curScene);
                opt->helpList->set_scroll_to(opt->curScene*SCREEN_HOR_SIZE, 0, LV_ANIM_OFF);
            }
        }
    }
}
