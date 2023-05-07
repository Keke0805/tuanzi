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
    LvcppLabel* VOLUME_bar = nullptr;
    void deinitial(void);
    lv_timer_t* maintimer=nullptr;
    void TimerCB(lv_timer_t * tmr);

};

#endif // MICROPHONE_H
