#ifndef NET_RADIO_H
#define NET_RADIO_H

#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/customer_config.h"

class Net_radio: public LvcppTimerTask
{
public:
    Net_radio(lv_obj_t* parent=nullptr);
    ~Net_radio();

private:
    void ui_image_decode(void);
    void ui_image_free(void);
    void*  RADIO_PNG = NULL;
    LvcppScreen* mscreen=nullptr;
    lv_obj_t* m_parent=nullptr;
    LvcppLabel* current_icon = nullptr;
    void initial(void);
    void deinitial(void);
    lv_timer_t* maintimer=nullptr;
    void TimerCB(lv_timer_t * tmr);
};

#endif // NET_RADIO_H
