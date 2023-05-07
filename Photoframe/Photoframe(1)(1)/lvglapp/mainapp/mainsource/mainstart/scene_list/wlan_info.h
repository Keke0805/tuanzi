#ifndef WLAN_INFO_H
#define WLAN_INFO_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "../include/configCustom.h"
#include  "../include/str_config.h"
#include  "../include/ui_config.h"

#ifdef _UCHIP_T113
#include  "common/common.h"
#else
    #include  "driver/va_wifi.h"
#endif

class Wlaninfo
{
public:
    Wlaninfo(lv_obj_t* parent = nullptr);
    ~Wlaninfo();

    void init_parament(net_wifi_scan_info_t wifi,wmgState status);
	
    LvcppScreen* wlan_frame=nullptr;
    lv_obj_t*  wlanscreen=nullptr;
    LvcppButton* wlan_info=nullptr;

	LvcppButton* connect_btn=nullptr;
	LvcppButton* cancel_btn=nullptr;

    LvcppLabel* wlan_label=nullptr;
    LvcppLabel* password_label=nullptr;

    LvcppCheckBox* password_mode=nullptr;

    LvcppLabel* wrong_label=nullptr;

    LvcppKeyboard* kb=nullptr;
    LvcppTextArea* textarea=nullptr;

private:
    void show_keyboard(void);
    void hide_keyboard(void);

    static int wlan_password_mode;
    static void checkbox_event_handler(lv_event_t *event);
    static void textarea_event_handler(lv_event_t *event);
    static void keyboard_event_handler(lv_event_t *event);


};

#endif // WLAN_INFO_H



