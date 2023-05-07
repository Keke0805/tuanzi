#ifndef WIFI_H
#define WIFI_H

#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/customer_config.h"

class Wifi: public LvcppTimerTask
{
public:
    int choose=0;
    Wifi(lv_obj_t* parent=nullptr);
    ~Wifi();
 void sendcb(void (*callback)(void));
private:
    LvcppScreen* mscreen=nullptr;
    lv_obj_t* m_parent=nullptr;
    void initial(void);
    LvcppLabel* current_icon = nullptr;
    LvcppButton* back_icon = nullptr;
    LvcppButton* on_and_off = nullptr;
    void ui_image_decode(void);
    void*  SETTING_WIFI_PNG=NULL;
    void*  SETTING_BACK_PNG=NULL;
    void*  SETTING_ON_PNG=NULL;
    void*  SETTING_OFF_PNG=NULL;
    static void btn_event_hander(lv_event_t *event);
    static void clicked_event_handler(lv_event_t *event);
    lv_timer_t* maintimer=nullptr;
    void TimerCB(lv_timer_t * tmr);
    void (*volume_callback)(void);
};

#endif // WIFI_H
