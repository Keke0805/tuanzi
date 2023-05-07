#ifndef WIFI_H
#define WIFI_H

#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/customer_config.h"

class Wifi: public LvcppTimerTask
{
public:
    Wifi(lv_obj_t* parent=nullptr);
    ~Wifi();

private:
    LvcppScreen* mscreen=nullptr;
    lv_obj_t* m_parent=nullptr;
    void initial(void);
    LvcppLabel* current_icon = nullptr;
    LvcppLabel* back_icon = nullptr;
    LvcppButton* on_and_off = nullptr;
    void ui_image_decode(void);
    void*  SETTING_WIFI_PNG=NULL;
    void*  SETTING_BACK_PNG=NULL;
    void*  SETTING_ON_PNG=NULL;
    void*  SETTING_OFF_PNG=NULL;
    lv_timer_t* maintimer=nullptr;
    void TimerCB(lv_timer_t * tmr);
};

#endif // WIFI_H
