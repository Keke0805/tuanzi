#ifndef MESSAGESCREEN_H
#define MESSAGESCREEN_H

#include  "lv_cpp/lvcpp_class.h"
#include  "customer_config.h"

class messagescreen
{
public:
    void sendcb(void (*callback)(void));
    messagescreen(lv_obj_t *parent = nullptr);
    ~messagescreen();
private:
    LvcppScreen* mscreen=nullptr;
    lv_obj_t* mparent=nullptr;
    void* bg = nullptr;
    LvcppLabel *head = nullptr;
    LvcppLabel *Frame = nullptr;
    LvcppButton *back = nullptr;
    void initial(void);
    void (*messagescreen_callback)(void);
    static void btn_event_hander(lv_event_t *event);
};


#endif // MESSAGESCREEN_H
