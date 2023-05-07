#include "wlan_list.h"
#include  "common/common.h"

void Wlanlist::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    HEAD_WIFI0_PNG=(void*)parse_image_from_file(HEAD_WIFI0_PNG_PATH);
    HEAD_WIFI1_PNG=(void*)parse_image_from_file(HEAD_WIFI1_PNG_PATH);
	HEAD_WIFI2_PNG=(void*)parse_image_from_file(HEAD_WIFI2_PNG_PATH);
    HEAD_WIFI3_PNG=(void*)parse_image_from_file(HEAD_WIFI3_PNG_PATH);
	HEAD_WIFI4_PNG=(void*)parse_image_from_file(HEAD_WIFI4_PNG_PATH);
	HEAD_WIFINO_PNG=(void*)parse_image_from_file(HEAD_WIFINO_PNG_PATH);
#endif
}

void Wlanlist::ui_image_free(void)
{
#ifdef IMAGE_DECODE
    free_image(HEAD_WIFI0_PNG);
    free_image(HEAD_WIFI1_PNG);
	free_image(HEAD_WIFI2_PNG);
    free_image(HEAD_WIFI3_PNG);
	free_image(HEAD_WIFI4_PNG);
	free_image(HEAD_WIFINO_PNG);
#endif
}


Wlanlist::Wlanlist(lv_obj_t* parent)
{
	ui_image_decode();
    frame = new LvcppButton(parent);
    frame->set_size(880,70);
    frame->align(LV_ALIGN_TOP_LEFT,0,0);
    frame->set_style_radius(8,0);
    frame->set_style_pad_all(0,0);
    frame->set_style_radius(0,0);
    frame->set_main_border_width(1);
    frame->set_main_border_color(lv_color_hex(0x0063c1));
    frame->set_main_bg_color(lv_color_hex(0x00a7d4),LV_OPA_100);
    mainframe = frame->myobj;
	
    label_ssid = new LvcppLabel(mainframe);
    label_ssid->set_size(800,40);
    label_ssid->align(LV_ALIGN_TOP_LEFT,10,0);
    label_ssid->set_main_radius(0);
    label_ssid->set_main_pad_all(0);
    label_ssid->set_main_border_width(0);
    label_ssid->set_main_bg_opa(LV_OPA_0);
    label_ssid->txt_color(lv_color_hex(0xffffff),LV_PART_MAIN);
    label_ssid->txt_font_size(36, FT_FONT_STYLE_NORMAL);
    label_ssid->txt_align(LV_TEXT_ALIGN_LEFT);
    label_ssid->set_txt("ssid");

    label_encrypt = new LvcppLabel(mainframe);
    label_encrypt->set_size(800,30);
    label_encrypt->align_to(label_ssid->myobj,LV_ALIGN_OUT_BOTTOM_LEFT,0,0);
    label_encrypt->set_style_radius(0,0);
    label_encrypt->set_main_pad_all(0);
    label_encrypt->set_main_border_width(0);
    label_encrypt->set_main_bg_opa(LV_OPA_0);
    label_encrypt->txt_color(lv_color_hex(0xcccccc),LV_PART_MAIN);
    label_encrypt->txt_font_size(24, FT_FONT_STYLE_NORMAL);
    label_encrypt->txt_align(LV_TEXT_ALIGN_LEFT);
    label_encrypt->set_txt("Not connected");

    signal = new LvcppLabel(mainframe);
    signal->set_size(58,58);
    signal->align(LV_ALIGN_RIGHT_MID,0,0);
    signal->set_style_radius(0,0);
    signal->txt_align(LV_TEXT_ALIGN_CENTER);
    signal->set_txt("");
    signal->set_main_bg_img_src(HEAD_WIFINO_PNG);
    
}

Wlanlist::~Wlanlist(void)
{
    if(signal != NULL)
    {
        delete signal;
        signal = nullptr;
    }
    if(label_encrypt != NULL)
	{
        delete label_encrypt;
        label_encrypt = nullptr;
	}
    if(label_ssid != NULL)
	{
        delete label_ssid;
        label_ssid = nullptr;
	}
    if(frame != NULL)
	{
        delete frame;
        frame = nullptr;
	}
	ui_image_free();
}

int Wlanlist::update_frame(net_wifi_scan_info_t wifi,wmgState status)
{
    label_ssid->set_txt(wifi.ssid);
    if(status==CONNECTED)
	{
        frame->set_main_bg_opa(LV_OPA_100);
        label_encrypt->set_txt("Connected");
	}
	else
	{
        frame->set_main_bg_opa(LV_OPA_50);
        label_encrypt->set_txt("Not connected");
	}
    if(wifi.level>=75)
    {
        signal->set_main_bg_img_src(HEAD_WIFI4_PNG);
    }
    else if(wifi.level>=50)
    {
        signal->set_main_bg_img_src(HEAD_WIFI3_PNG);
    }
    else if(wifi.level>=25)
    {
        signal->set_main_bg_img_src(HEAD_WIFI2_PNG);
    }
    else if(wifi.level==-1)
    {
        signal->set_main_bg_img_src(HEAD_WIFINO_PNG);
    }
    else
    {
        signal->set_main_bg_img_src(HEAD_WIFI1_PNG);
    }
	return 0;
}





