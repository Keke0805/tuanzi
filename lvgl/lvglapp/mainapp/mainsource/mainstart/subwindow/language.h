#ifndef LANGUAGE_H
#define LANGUAGE_H

#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/customer_config.h"
#include  "./kbscreen.h"
class Language: public LvcppTimerTask
{
public:
    Language(lv_obj_t* parent=nullptr);
    ~Language();

private:
    LvcppScreen* mscreen=nullptr;
    lv_obj_t* m_parent=nullptr;
    void deinitial(void);
    void initial(void);
    LvcppLabel* txt_tip = nullptr;
    LvcppButton* language_tip = nullptr;
    lv_timer_t* maintimer=nullptr;
    void TimerCB(lv_timer_t * tmr);
    static void textarea_event_hander(lv_event_t *event);
};

#endif // LANGUAGE_H
