#ifndef SPEECH_H
#define SPEECH_H
#include  "lv_cpp/lvcpp_class.h"
#include  "customer_config.h"

class speech : public LvcppTimerTask
{
public:
    void sendcb(void (*callback)(void));
    speech(lv_obj_t *parent = nullptr);
    LvcppScreen* mscreen=nullptr;
    ~speech();
private:

    lv_obj_t* mparent=nullptr;
    void* bg = nullptr;
    void* num0 = nullptr;
    void* num1 = nullptr;
    void* num2 = nullptr;
    void* num3 = nullptr;
    void* num4 = nullptr;
    void* num5 = nullptr;
    void* num6 = nullptr;
    void* num7 = nullptr;
    void* num8 = nullptr;
    void* num9 = nullptr;
    LvcppRoller *hour = nullptr;
    LvcppRoller *hour1 = nullptr;
    LvcppRoller *minute = nullptr;
    LvcppRoller *minute1 = nullptr;
    LvcppRoller *second = nullptr;
    LvcppRoller *second1 = nullptr;
    LvcppButton *time = nullptr;
    LvcppButton *paly_stop = nullptr;
    LvcppButton *resetbuttton = nullptr;
    LvcppLabel *time_tip = nullptr;
    LvcppLabel *play_stop_tip = nullptr;
    LvcppLabel *resetbuttton_tip = nullptr;
    LvcppLabel *dot = nullptr;
    LvcppLabel *dot1 = nullptr;
    LvcppButton *back = nullptr;
    lv_timer_t* speechimer=nullptr;
    LvcppFreeTypeFont* myfont=nullptr;
    void TimerCB(lv_timer_t * tmr);
    void reset_param(void);
    void clean_num_clickable();
    void update_num_clickable();
    void time_split(int time);
    void initial(void);
    void (*sp_callback)(void);
    static void btn_event_hander(lv_event_t *event);
};


#endif // SPEECH_H
