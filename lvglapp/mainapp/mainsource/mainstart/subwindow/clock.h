#ifndef CLOCK_H
#define CLOCK_H

#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/customer_config.h"

class Clock: public LvcppTimerTask
{
public:
    Clock(lv_obj_t* parent=nullptr);
    ~Clock();
     void sendcb(void (*callback)(void));
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
    LvcppButton* current_icon = nullptr;
    LvcppButton* back_icon = nullptr;
    LvcppLabel* txt_tip = nullptr;

    LvcppButton* time = nullptr;
    LvcppLabel* colon = nullptr;
    LvcppButton* minute = nullptr;
    LvcppButton* year = nullptr;
    LvcppButton* month = nullptr;
    LvcppButton*  day = nullptr;
    LvcppRoller* hour=nullptr;
    LvcppRoller* minute1=nullptr;
    LvcppRoller* year1=nullptr;
    LvcppRoller* mouth1=nullptr;
    LvcppRoller* day1=nullptr;

static void btn_event_hander(lv_event_t *event);
    lv_timer_t* maintimer=nullptr;
    void TimerCB(lv_timer_t * tmr);
    void (*volume_callback)(void);
    void (*save_callback)(void);
};

#endif // CLOCK_H
