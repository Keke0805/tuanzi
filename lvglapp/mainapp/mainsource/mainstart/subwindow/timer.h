#ifndef TIMER_H
#define TIMER_H

#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/customer_config.h"
#include  "./kbscreen.h"

typedef struct _clock_img_t {
    int second;
    const void  *platePath;
    const void  *secondPath;
} clock_img_t;
class Timer: public LvcppTimerTask
{
public:
    Timer(lv_obj_t* parent=nullptr);
    ~Timer();
    int choose=0;
     void update_time(int Second);
void sendcb(void (*callback)(void));
private:
    LvcppScreen* mscreen=nullptr;
    lv_obj_t* m_parent=nullptr;
    void initial(void);
    void kb_create(void);
    static void kb_cb(void);
    kbscreen *input_kb = nullptr;
    void get_kbinput_text(int type);
    LvcppButton* current_icon = nullptr;
    LvcppButton* back_icon = nullptr;
    LvcppLabel* excircle_icon = nullptr;
    LvcppLabel* fillet_icon = nullptr;
    LvcppButton* on_and_off = nullptr;
    LvcppFreeTypeFont* myfont=nullptr;
    LvcppButton* time_value = nullptr;
    LvcppRoller *second = nullptr;
    LvcppImage* plate=nullptr;
    LvcppImage* zhizhen=nullptr;
    LvcppLabel* anim_number=nullptr;
    LvcppRotateAnimimg* anim=nullptr;
    void ui_image_decode(void);
    void*  SETTING_BACK_PNG=NULL;
    void*  SETTING_ON_PNG=NULL;
    void*  SETTING_OFF_PNG=NULL;
    void*  TIMER_EXCIRCLE_PNG=NULL;
    void*  TIMER_FILLET_PNG=NULL;
    void*  TIMER_PNG=NULL;
    void*  TIMER_ZHIZHEN_PNG=NULL;
    lv_timer_t* maintimer=nullptr;
    static void btn_event_hander(lv_event_t *event);
    static void btn_event_hander2(lv_event_t *event);
    static void textarea_event_hander(lv_event_t *event);
    void TimerCB(lv_timer_t * tmr);
    lvcpp_sys_time_t user_time1;
    lvcpp_sys_datetime_t user_time;
     void (*volume_callback)(void);
     void reset_param(void);
     void update_num_clickable();
     void time_split(int time);
};

#endif // TIMER_H
