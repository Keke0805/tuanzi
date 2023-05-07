#ifndef ALARM_H
#define ALARM_H

#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/customer_config.h"



class Alarm : public LvcppTimerTask
{
public:
    int choose=0;
    Alarm(lv_obj_t* parent=nullptr);
    ~Alarm();
void sendcb(void (*callback)(void));
private:
    LvcppScreen* mscreen=nullptr;
    lv_obj_t* m_parent=nullptr;
    void initial(void);
    LvcppButton* current_icon = nullptr;
    LvcppButton* back_icon = nullptr;
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
    LvcppLabel* alarm_on_1=nullptr;
    LvcppLabel* alarm_off_1=nullptr;
    LvcppLabel* alarm_on_2=nullptr;
    LvcppLabel* alarm_off_2=nullptr;
    LvcppRoller*  hour1=nullptr;
    LvcppRoller*  minute_1=nullptr;
    LvcppRoller*  hour2=nullptr;
    LvcppRoller*  minute1_1=nullptr;
    LvcppRoller*  cycle1=nullptr;
    LvcppRoller*  cycle2=nullptr;
    LvcppRoller* bell1=nullptr;
    LvcppRoller* bell2=nullptr;
    LvcppFreeTypeFont* myfont=nullptr;

    int get_info(void);
    void ui_image_decode(void);
    void*  SETTING_BACK_PNG=NULL;
    void*  SETTING_ON_PNG=NULL;
    void*  SETTING_OFF_PNG=NULL;
    void*  SETTING_ALARM_1_1_PNG=NULL;
    void*  SETTING_ALARM_1_2_PNG=NULL;
    void*  SETTING_ALARM_2_1_PNG=NULL;
    void*  SETTING_ALARM_2_2_PNG=NULL;
    lv_timer_t* maintimer=nullptr;
     static void btn_event_hander(lv_event_t *event);
     static void clicked_event_handler(lv_event_t *event);
     static void clicked_event_handler2(lv_event_t *event);
     static void clicked_event_handler3(lv_event_t *event);
    void TimerCB(lv_timer_t * tmr);
    void (*volume_callback)(void);
    void (*alarm1_switch)(void);
    void (*alarm2_switch)(void);
};

#endif // ALARM_H
