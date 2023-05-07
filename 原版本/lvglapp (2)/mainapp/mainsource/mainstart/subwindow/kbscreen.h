#ifndef KBSCREEN_H
#define KBSCREEN_H

#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/customer_config.h"

class kbscreen
{
public:
    kbscreen(lv_obj_t* parent = nullptr);
    void initial(int type);
    void sendcb(void (*callback)(void));
    LvcppTextArea * input_box = nullptr;
    LvcppScreen* kb_screen= nullptr;
    ~kbscreen();
    void (*kb_callback)(void);
private:
    LvcppFreeTypeFont* myfont=nullptr;
    lv_obj_t* kb_parent= nullptr;
    LvcppKeyboard* kb = nullptr;
    int kb_type = 0;
    static void kb_textarea_event_hander(lv_event_t *event);
};

#endif // KBSCREEN_H
