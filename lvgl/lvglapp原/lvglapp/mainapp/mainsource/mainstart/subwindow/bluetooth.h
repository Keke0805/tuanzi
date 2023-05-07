#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/customer_config.h"


class Bluetooth: public LvcppTimerTask
{
public:
    Bluetooth(lv_obj_t* parent=nullptr);
    ~Bluetooth();

protected:
    void ui_image_decode(void);
    void ui_image_free(void);

    void*  BLUETOOTH_PNG = NULL;
    void*  OTHER_GOBACK1_PNG = NULL;
    void*  OTHER_GOBACK2_PNG = NULL;
private:

    LvcppScreen* mscreen=nullptr;
    lv_obj_t* m_parent=nullptr;

    void initial(void);
    void deinitial(void);
    LvcppLabel* current_icon = nullptr;
    LvcppLabel* back_icon = nullptr;
    LvcppLabel* txt_tip = nullptr;
    LvcppLabel* txt_s_tip = nullptr;
    lv_timer_t* maintimer=nullptr;
    void TimerCB(lv_timer_t * tmr);
};

#endif // BLUETOOTH_H
