#ifndef SETNETWORK_H
#define SETNETWORK_H

#include  "lv_cpp/lvcpp_class.h"
#include  "customer_config.h"
#if (QTSIM_PLATFORM==0)
#ifdef __cplusplus
extern "C" {
#endif

#include  "dl_service.h"
#include  "mainstart/hotplugdetect/hotplugdetect.h"
#include  "mainstart/hotplugdetect/common/applib/applib.h"
#include  "mainstart/hotplugdetect/common/applib/app_config.h"

#ifdef __cplusplus
} /*extern "C"*/
#endif

#else
typedef struct{
    int static_ip;
    char mac[20];
    char ip[16];
    char gateway[16];
    char netmask[16];
    char dns1[16];
    char dns2[16];
}NetConfig_t;
#endif

class SettingNet : public LvcppTimerTask
{
public:
    SettingNet(lv_obj_t* parent = nullptr);
    ~SettingNet();

    void sendcb(void (*callback)(void));

private:

    void (*net_callback)(void);

	void TimerCB(lv_timer_t * tmr);

    void initial(void);
    void deinitial(void);

    void network_initial(void);
	void network_config_update(void);
    void network_deinitial(void);

    void keyboard_create(void);
    void keyboard_delete(void);
    void ip_textedit_create(void);
    void ip_textedit_delete(void);
    void mask_textedit_create(void);
    void mask_textedit_delete(void);
    void gateway_textedit_create(void);
    void gateway_textedit_delete(void);

    static void keyboard_event_hander(lv_event_t* event);
    static void dhcp_sw_event_hander(lv_event_t* event);
    static void ip_textedit_event_hander(lv_event_t* event);
    static void mask_textedit_event_hander(lv_event_t* event);
    static void gateway_textedit_event_hander(lv_event_t* event);

    static void go_back_btn_event_hander(lv_event_t *event);

    void textarea_pos_move_last(lv_obj_t* obj);

    LvcppScreen* mscreen=nullptr;
    lv_obj_t* mparent=nullptr;

	lv_timer_t* settimer=nullptr;

    LvcppButton* go_back = nullptr;

    LvcppSwitch* dhcpsw = nullptr;
    LvcppScreen* dhcp_win = nullptr;

    LvcppLabel* label_ip=nullptr;
    LvcppLabel* label_mask=nullptr;
    LvcppLabel* label_gateway=nullptr;

    LvcppKeyboard* keyboard = nullptr;

    LvcppTextArea* input_ip1=nullptr;
    LvcppTextArea* input_ip2=nullptr;
    LvcppTextArea* input_ip3=nullptr;
    LvcppTextArea* input_ip4=nullptr;

    LvcppTextArea* input_mask1=nullptr;
    LvcppTextArea* input_mask2=nullptr;
    LvcppTextArea* input_mask3=nullptr;
    LvcppTextArea* input_mask4=nullptr;

    LvcppTextArea* input_gw1=nullptr;
    LvcppTextArea* input_gw2=nullptr;
    LvcppTextArea* input_gw3=nullptr;
    LvcppTextArea* input_gw4=nullptr;

	int eth_state = 0;
	NetConfig_t eth_info;
};

#endif // SETNETWORK_H
