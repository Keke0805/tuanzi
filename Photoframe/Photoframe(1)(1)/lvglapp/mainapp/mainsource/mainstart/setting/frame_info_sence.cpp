#include "frame_info_sence.h"
#include  "../include/ui_config.h"
#include  "../include/str_config.h"
#ifdef _UCHIP_T113
#include  "common/common.h"
#endif
void frameInfoSence::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    SETTING_FRAME_REFRESH_PNG=(void*)parse_image_from_file(SETTING_FRAME_REFRESH_PNG_PATH);
#endif
}

void frameInfoSence::ui_image_free(void)
{
#ifdef IMAGE_DECODE
    free_image(SETTING_FRAME_REFRESH_PNG);
#endif
}

frameInfoSence::frameInfoSence(lv_obj_t* parent)
{
    char devCode[24]={0};
    char iosinfo[512]={0};
    char androidinfo[512]={0};
    char emaillinfo[512]={0};
    char buff[24]={0};
    char buff1[4]={0};
    char buff2[4]={0};
    char buff3[4]={0};
	
	ui_image_decode();
#ifdef _UCHIP_T113
    read_string_type_param(WEATHER_SCENE, DEVCODE,devCode,sizeof(devCode));
    read_string_type_param(WEATHER_SCENE, IOSINFO,iosinfo,sizeof(iosinfo));
    read_string_type_param(WEATHER_SCENE, ANDROIDINFO,androidinfo,sizeof(androidinfo));
    read_string_type_param(WEATHER_SCENE, EMAILLINFO,emaillinfo,sizeof(emaillinfo));
#endif
    memcpy(buff1,devCode,3);
    memcpy(buff2,devCode+3,3);
    memcpy(buff3,devCode+6,3);
    sprintf(buff,"%s %s %s",buff1,buff2,buff3);

    frame = new LvcppLabel(parent);
    frame->set_size(880,850);
    frame->set_main_bg_opa(LV_OPA_0);
    frame->set_txt("");
    mainframe = frame->myobj;

    qrcodeLabel = new LvcppLabel(mainframe);
    qrcodeLabel->set_size(270,320);
    qrcodeLabel->align(LV_ALIGN_TOP_MID,0,10);
    qrcodeLabel->set_main_bg_color(lv_color_white(),LV_OPA_100);
    qrcodeLabel->set_main_radius(10);
    qrcodeLabel->set_txt("");

    qrcode = new LvcppQrcode(qrcodeLabel->myobj);
    qrcode->align(LV_ALIGN_TOP_MID,0,10);
    qrcode->set_size(250,250);
    qrcode->qrcode_creat(devCode,250,0);

    connectLabel = new LvcppLabel(qrcodeLabel->myobj);
    connectLabel->set_size(260,30);
    connectLabel->align(LV_ALIGN_TOP_MID,0,260);
    connectLabel->set_main_radius(0);
    connectLabel->set_main_pad_all(0);
    connectLabel->set_main_pad_row(0);
    connectLabel->set_main_border_width(0);
    connectLabel->txt_color(lv_color_hex(0x000000),LV_PART_MAIN);
    connectLabel->set_main_bg_opa(LV_OPA_0);
    connectLabel->txt_font_size(24, FT_FONT_STYLE_NORMAL);
    connectLabel->txt_align(LV_TEXT_ALIGN_CENTER);
    connectLabel->txt_long_mode(LV_LABEL_LONG_DOT);
    connectLabel->clear_flag(LV_OBJ_FLAG_CLICKABLE);
    connectLabel->set_txt(STR_CONNECTIONCODE);

    numberLabel = new LvcppLabel(qrcodeLabel->myobj);
    numberLabel->set_size(260,30);
    numberLabel->align(LV_ALIGN_TOP_MID,0,285);
    numberLabel->set_main_radius(0);
    numberLabel->set_main_pad_all(0);
    numberLabel->set_main_pad_row(0);
    numberLabel->set_main_border_width(0);
    numberLabel->txt_color(lv_color_hex(0xff0000),LV_PART_MAIN);
    numberLabel->set_main_bg_opa(LV_OPA_0);
    numberLabel->txt_font_size(26, FT_FONT_STYLE_NORMAL);
    numberLabel->txt_align(LV_TEXT_ALIGN_CENTER);
    numberLabel->txt_long_mode(LV_LABEL_LONG_DOT);
    numberLabel->clear_flag(LV_OBJ_FLAG_CLICKABLE);
    numberLabel->set_txt(buff);

    qrcodeButton = new LvcppButton(mainframe);
    qrcodeButton->set_size(50,50);
    qrcodeButton->set_main_bg_color(lv_color_white(),LV_OPA_0);
    qrcodeButton->set_main_bg_img_src(SETTING_FRAME_REFRESH_PNG);
    qrcodeButton->align_to(qrcodeLabel->myobj,LV_ALIGN_OUT_RIGHT_TOP,0,0);

    iosappLabel = new LvcppLabel(mainframe);
    iosappLabel->set_size(800,90);
    iosappLabel->align(LV_ALIGN_TOP_LEFT,30,340);
    iosappLabel->set_main_radius(0);
    iosappLabel->set_main_pad_all(0);
    iosappLabel->set_main_pad_row(0);
    iosappLabel->set_main_border_width(0);
    iosappLabel->txt_color(lv_color_hex(0xffffff),LV_PART_MAIN);
    iosappLabel->set_main_bg_opa(LV_OPA_0);
    iosappLabel->txt_font_size(30, FT_FONT_STYLE_NORMAL);
    iosappLabel->txt_align(LV_TEXT_ALIGN_LEFT);
    iosappLabel->txt_long_mode(LV_LABEL_LONG_DOT);
    iosappLabel->clear_flag(LV_OBJ_FLAG_CLICKABLE);
    iosappLabel->set_txt(iosinfo);

    andiorappLabel = new LvcppLabel(mainframe);
    andiorappLabel->set_size(800,90);
    andiorappLabel->align(LV_ALIGN_TOP_LEFT,30,430);
    andiorappLabel->set_main_radius(0);
    andiorappLabel->set_main_pad_all(0);
    andiorappLabel->set_main_pad_row(0);
    andiorappLabel->set_main_border_width(0);
    andiorappLabel->txt_color(lv_color_hex(0xffffff),LV_PART_MAIN);
    andiorappLabel->set_main_bg_opa(LV_OPA_0);
    andiorappLabel->txt_font_size(30, FT_FONT_STYLE_NORMAL);
    andiorappLabel->txt_align(LV_TEXT_ALIGN_LEFT);
    andiorappLabel->txt_long_mode(LV_LABEL_LONG_DOT);
    andiorappLabel->clear_flag(LV_OBJ_FLAG_CLICKABLE);
    andiorappLabel->set_txt(androidinfo);

    emailLabel = new LvcppLabel(mainframe);
    emailLabel->set_size(800,320);
    emailLabel->align(LV_ALIGN_TOP_LEFT,30,520);
    emailLabel->set_main_radius(0);
    emailLabel->set_main_pad_all(0);
    emailLabel->set_main_pad_row(0);
    emailLabel->set_main_border_width(0);
    emailLabel->txt_color(lv_color_hex(0xffffff),LV_PART_MAIN);
    emailLabel->set_main_bg_opa(LV_OPA_0);
    emailLabel->txt_font_size(30, FT_FONT_STYLE_NORMAL);
    emailLabel->txt_align(LV_TEXT_ALIGN_LEFT);
    emailLabel->txt_long_mode(LV_LABEL_LONG_DOT);
    emailLabel->clear_flag(LV_OBJ_FLAG_CLICKABLE);
    emailLabel->set_txt(emaillinfo);
}

void frameInfoSence::qrcode_updata(void)
{
    char devCode[24]={0};
    char buff[24]={0};
    char buff1[4]={0};
    char buff2[4]={0};
    char buff3[4]={0};
	
#ifdef _UCHIP_T113
    read_string_type_param(WEATHER_SCENE, DEVCODE,devCode,sizeof(devCode));
#endif
    memcpy(buff1,devCode,3);
    memcpy(buff2,devCode+3,3);
    memcpy(buff3,devCode+6,3);
    sprintf(buff,"%s %s %s",buff1,buff2,buff3);
    qrcode->update_data(devCode);
    numberLabel->set_txt(buff);
}

frameInfoSence::~frameInfoSence(void)
{
    if(iosappLabel != NULL)
    {
        delete iosappLabel;
        iosappLabel = NULL;
    }
    if(andiorappLabel != NULL)
    {
        delete andiorappLabel;
        andiorappLabel = NULL;
    }
    if(emailLabel != NULL)
    {
        delete emailLabel;
        emailLabel = NULL;
    }
    if(numberLabel != NULL)
    {
        delete numberLabel;
        numberLabel = NULL;
    }
    if(qrcodeButton != NULL)
    {
        delete qrcodeButton;
        qrcodeButton = NULL;
    }
    if(connectLabel != NULL)
    {
        delete connectLabel;
        connectLabel = NULL;
    }
    if(qrcode != NULL)
    {
        delete qrcode;
        qrcode = NULL;
    }
    if(qrcodeLabel != NULL)
    {
        delete qrcodeLabel;
        qrcodeLabel = NULL;
    }
    if(frame != NULL)
    {
        delete frame;
        frame = NULL;
    }
    ui_image_free();
}

