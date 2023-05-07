#ifndef WLAN_LIST_H
#define WLAN_LIST_H

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

class Wlanlist
{
public:
    Wlanlist(lv_obj_t* parent = nullptr);
    ~Wlanlist();

    int update_frame(net_wifi_scan_info_t wifi,wmgState status);
    LvcppButton* frame=nullptr;
    LvcppLabel* label_ssid=nullptr;
    LvcppLabel* label_encrypt=nullptr;
    LvcppLabel* signal=nullptr;

protected:
	void*  HEAD_WIFI0_PNG=NULL;               
	void*  HEAD_WIFI1_PNG=NULL;               
	void*  HEAD_WIFI2_PNG=NULL;               
	void*  HEAD_WIFI3_PNG=NULL;               
	void*  HEAD_WIFI4_PNG=NULL;               
	void*  HEAD_WIFINO_PNG=NULL;            
    void ui_image_decode(void);
    void ui_image_free(void);

private:

	lv_obj_t* mainframe=nullptr;
};

#endif // WLAN_LIST_H


