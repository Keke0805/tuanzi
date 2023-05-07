#ifndef VERSION_H
#define VERSION_H

#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/customer_config.h"

class Version: public LvcppTimerTask
{
public:
    Version(lv_obj_t* parent=nullptr);
    ~Version();

protected:
    void ui_image_decode(void);
    void ui_image_free(void);

    void*  BACK_PNG = NULL;
    void*  VERSION_PNG = NULL;

private:
    LvcppScreen* mscreen=nullptr;
    lv_obj_t* m_parent=nullptr;
    void deinitial(void);
    void initial(void);
    LvcppButton* current_icon = nullptr;
    LvcppButton* back_icon = nullptr;
    LvcppLabel* txt_tip = nullptr;
    LvcppLabel* txt_s_tip = nullptr;
    lv_timer_t* maintimer=nullptr;
    void TimerCB(lv_timer_t * tmr);
};

#endif // VERSION_H
