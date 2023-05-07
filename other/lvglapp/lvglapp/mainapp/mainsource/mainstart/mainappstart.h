#ifndef MAINAPPSTART_H
#define MAINAPPSTART_H

#include  "lv_cpp/lvcpp_class.h"
#include  "customer_config.h"
#include  "renamescreen.h"
#include  "idcardscreen.h"
#include  "settingscreen.h"
#include  "single_screen.h"
#if (QTSIM_PLATFORM==0)
#ifdef __cplusplus
extern "C" {
#endif

#include  "dl_service.h"
#include  "mainstart/zpclient/zpclient.h"
#include  "mainstart/hotplugdetect/hotplugdetect.h"
#include  "mainstart/hotplugdetect/common/applib/applib.h"
#include  "mainstart/hotplugdetect/common/applib/app_config.h"

#ifdef __cplusplus
} /*extern "C"*/
#endif
#include  "machine/httpserver.h"
#else
#include  "simulator/Qhttpserver.h"
#endif


class MainAPPStart : public LvcppTimerTask
{
public:
    MainAPPStart(LvcppMainScreen* parent = nullptr);
    ~MainAPPStart(void);

private:
    void initial(void);
    void deinitial(void);

    void zp_param_initial(void);

    void start_httpserver(void);
    void stop_httpserver(void);

	int read_battery_value(void);
	int read_power_state(void);
	void screen_standby(void);
	void screen_resume(void);
    LvcppMainScreen* m_screen;
    lv_obj_t* m_parent;

    httpserver* m_pHttpServer=nullptr;

    lv_timer_t* maintimer=nullptr;
    void TimerCB(lv_timer_t * tmr);

    LvcppTileView* tileview = nullptr;
    lv_obj_t* idcard=nullptr;
    lv_obj_t* singlescreen=nullptr;
    lv_obj_t* rename=nullptr;
    lv_obj_t* setting=nullptr;
    IdcardScreen* idcardscreen=nullptr;
    RenameScreen* renamescreen=nullptr;
    SettingScreen* settingscreen=nullptr;
    single_screen* Single_screen=nullptr;

    LvcppFreeTypeFont* myfont = nullptr;
    LvcppKeyboard* kb = nullptr;
    LvcppTextArea* textarea = nullptr;

    static void btn_event_hander(lv_event_t *event);

    #if (QTSIM_PLATFORM==0)
	static void networkpolicy_proc(NetPolicy_cbmsg_t *msg);
	static void urdevhotplug_proc(msg_apps_t *msg);
    static void usbhotplug_proc(UsbParam_t *pUsbParam);
    static void backlight_enable(int enable);
    #endif
};

#endif // MAINAPPSTART_H
