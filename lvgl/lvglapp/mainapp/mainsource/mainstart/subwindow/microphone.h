#ifndef MICROPHONE_H
#define MICROPHONE_H

#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/customer_config.h"

class Microphone: public LvcppTimerTask
{
public:
    Microphone(lv_obj_t* parent=nullptr);
    ~Microphone();
    void down_volume(int volume_tmp);
    void up_volume(int volume_tmp);
    void initial(int volume_tmp,char* value);
    LvcppLabel* VOLUME_VALUE = nullptr;
private:
    void ui_image_decode(void);
    void ui_image_free(void);
    void*  Volume_B_PNG = NULL;
    void*  BAR_PNG = NULL;
    void*  BAR_PNG1 = NULL;
    void*  VOLUME_S_ICON = NULL;
    LvcppScreen* mscreen=nullptr;
    lv_obj_t* m_parent=nullptr;

    LvcppLabel* VOLUME_icon = nullptr;
    LvcppSlider* VOLUME_slider= nullptr;
    static void btn_event_hander(lv_event_t *event);
    void deinitial(void);
    lv_timer_t* maintimer=nullptr;
    void TimerCB(lv_timer_t * tmr);
    void (*volume_callback)(void);
};

#endif // MICROPHONE_H
