#ifndef ALARM_H
#define ALARM_H

#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/customer_config.h"



class Alarm : public LvcppTimerTask
{
public:
    Alarm(lv_obj_t* parent=nullptr);
    ~Alarm();

private:
    LvcppScreen* mscreen=nullptr;
    lv_obj_t* m_parent=nullptr;
    void initial(void);
    LvcppButton* current_icon = nullptr;
    LvcppLabel* back_icon = nullptr;
    LvcppButton* on_and_off = nullptr;
    LvcppButton* time = nullptr;
    LvcppLabel* colon = nullptr;
    LvcppButton* minute = nullptr;
    LvcppButton* Alarm_num = nullptr;
    LvcppButton* Alarm_one = nullptr;


    LvcppButton* on_and_off1 = nullptr;
    LvcppButton* time1 = nullptr;
    LvcppLabel* colon1 = nullptr;
    LvcppButton* minute1 = nullptr;
    LvcppButton* Alarm_num1 = nullptr;
    LvcppButton* Alarm_one1 = nullptr;

    void ui_image_decode(void);
    void*  SETTING_BACK_PNG=NULL;
    void*  SETTING_ON_PNG=NULL;
    void*  SETTING_OFF_PNG=NULL;
    lv_timer_t* maintimer=nullptr;
    void TimerCB(lv_timer_t * tmr);
};

#endif // ALARM_H
