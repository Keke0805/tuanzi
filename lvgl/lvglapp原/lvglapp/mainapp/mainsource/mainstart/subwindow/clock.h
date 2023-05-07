#ifndef CLOCK_H
#define CLOCK_H

#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/customer_config.h"

class Clock: public LvcppTimerTask
{
public:
    Clock(lv_obj_t* parent=nullptr);
    ~Clock();
protected:
    void ui_image_decode(void);
    void ui_image_free(void);

    void*  SAVE_PNG = NULL;
    void*  SAVE1_PNG = NULL;
    void*  OTHER_GOBACK1_PNG = NULL;

private:
    LvcppScreen* mscreen=nullptr;
    lv_obj_t* m_parent=nullptr;

    void initial(void);
    void deinitial(void);
    LvcppLabel* current_icon = nullptr;
    LvcppLabel* back_icon = nullptr;
    LvcppLabel* txt_tip = nullptr;

    LvcppButton* time = nullptr;
    LvcppLabel* colon = nullptr;
    LvcppButton* minute = nullptr;
    LvcppButton* year = nullptr;
    LvcppButton* month = nullptr;
    LvcppButton*  day = nullptr;

    lv_timer_t* maintimer=nullptr;
    void TimerCB(lv_timer_t * tmr);
};

#endif // CLOCK_H
