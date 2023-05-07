#ifndef TIMER_H
#define TIMER_H

#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/customer_config.h"

class Timer: public LvcppTimerTask
{
public:
    Timer(lv_obj_t* parent=nullptr);
    ~Timer();

private:
    LvcppScreen* mscreen=nullptr;
    lv_obj_t* m_parent=nullptr;
    void initial(void);
    LvcppButton* current_icon = nullptr;
    LvcppLabel* back_icon = nullptr;
    LvcppLabel* excircle_icon = nullptr;
    LvcppLabel* fillet_icon = nullptr;
    LvcppButton* on_and_off = nullptr;
    LvcppButton* time_value = nullptr;
    void ui_image_decode(void);
    void*  SETTING_BACK_PNG=NULL;
    void*  SETTING_ON_PNG=NULL;
    void*  SETTING_OFF_PNG=NULL;
    void*  TIMER_EXCIRCLE_PNG=NULL;
    void*  TIMER_FILLET_PNG=NULL;
    lv_timer_t* maintimer=nullptr;
    void TimerCB(lv_timer_t * tmr);

};

#endif // TIMER_H
