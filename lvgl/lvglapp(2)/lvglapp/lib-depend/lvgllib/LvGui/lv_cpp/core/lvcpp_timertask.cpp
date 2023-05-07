#include "lvcpp_timertask.h"

LvcppTimerTask::LvcppTimerTask(void)
{
    timer_id = NULL;
}

LvcppTimerTask::~LvcppTimerTask(void)
{
    if(timer_id != NULL)
    {
        deltmr(timer_id);
        timer_id = NULL;
    }
}

lv_timer_t* LvcppTimerTask::creat_empty_timer(void)
{
   return lv_timer_create_basic();
}

lv_timer_t* LvcppTimerTask::startTimer(uint32_t period, void* arg)
{
    if(timer_id == NULL)
    {
        timer_id = lv_timer_create(TimerEvent, period, arg);
    }
    return timer_id;
}

void LvcppTimerTask::TimerEvent(lv_timer_t * tmr)
{
   LvcppTimerTask* opt = (LvcppTimerTask*)tmr->user_data;
   opt->TimerCB(tmr);
}

lv_timer_t* LvcppTimerTask::creatTimer(lv_timer_cb_t timer_xcb, uint32_t period, void* user_data)
{
    if(timer_id == NULL)
    {
        timer_id = lv_timer_create(timer_xcb, period, user_data);
    }
    return timer_id;
}

int LvcppTimerTask::deltmr(lv_timer_t * timer)
{
    lv_timer_del(timer);
    return 0;
}

int LvcppTimerTask::pause(lv_timer_t * timer)
{
    lv_timer_pause(timer);
    return 0;
}

int LvcppTimerTask::resume(lv_timer_t * timer)
{
    lv_timer_resume(timer);
    return 0;
}

int LvcppTimerTask::set_cb(lv_timer_t * timer, lv_timer_cb_t timer_cb)
{
    lv_timer_set_cb(timer, timer_cb);
    return 0;
}

int LvcppTimerTask::set_period(lv_timer_t * timer, uint32_t period)
{
    lv_timer_set_period( timer, period);
    return 0;
}

int LvcppTimerTask::ready(lv_timer_t * timer)
{
    lv_timer_ready(timer);
    return 0;
}

int LvcppTimerTask::set_repeat_count(lv_timer_t * timer, int32_t repeat_count)
{
    lv_timer_set_repeat_count(timer, repeat_count);
    return 0;
}

int LvcppTimerTask::reset(lv_timer_t * timer)
{
    lv_timer_reset(timer);
    return 0;
}
