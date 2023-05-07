#ifndef USER_H
#define USER_H

#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/customer_config.h"
#include  "./kbscreen.h"

class User: public LvcppTimerTask
{
public:
    User(lv_obj_t* parent=nullptr);
    ~User();
    void sendcb(void (*callback)(void));
protected:
    void ui_image_decode(void);
    void ui_image_free(void);

    void*  BACK_PNG = NULL;
private:
    LvcppScreen* mscreen=nullptr;
    lv_obj_t* m_parent=nullptr;
    void deinitial(void);
    void initial(void);

    void kb_create(void);
    static void kb_cb(void);
    kbscreen *input_kb = nullptr;
    void get_kbinput_text(int type);

    LvcppLabel* txt_tip = nullptr;
    LvcppButton* back_icon = nullptr;
    LvcppButton* user_name = nullptr;
    LvcppButton* user_pass = nullptr;
    lv_timer_t* maintimer=nullptr;
    void TimerCB(lv_timer_t * tmr);
    static void textarea_event_hander(lv_event_t *event);
    static void btn_event_hander(lv_event_t *event);
    void (*volume_callback)(void);
};

#endif // USER_H
