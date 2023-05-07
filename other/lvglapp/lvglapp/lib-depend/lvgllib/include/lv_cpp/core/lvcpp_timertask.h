#ifndef LVCPP_TIMERTASK_H
#define LVCPP_TIMERTASK_H

#include  "lvgl/lvgl.h"

class LvcppTimerTask
{
public:
    LvcppTimerTask(void);
    virtual ~LvcppTimerTask(void);

    lv_timer_t* creatTimer(lv_timer_cb_t timer_xcb, uint32_t period, void * user_data);

    int pause(lv_timer_t * timer);
    int resume(lv_timer_t * timer);
    int set_cb(lv_timer_t * timer, lv_timer_cb_t timer_cb);
    int set_period(lv_timer_t * timer, uint32_t period);
    int ready(lv_timer_t * timer);
    int set_repeat_count(lv_timer_t * timer, int32_t repeat_count);
    int reset(lv_timer_t * timer);

protected:
    lv_timer_t* startTimer(uint32_t period, void* arg);
    int deltmr(lv_timer_t * timer);
    virtual void TimerCB(lv_timer_t * tmr) = 0;

private:
    lv_timer_t* timer_id;
    lv_timer_t* creat_empty_timer(void);


    static void TimerEvent(lv_timer_t * tmr);
};

#endif // LVCPP_TIMERTASK_H
