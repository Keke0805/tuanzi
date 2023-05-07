#ifndef SETVERSION_H
#define SETVERSION_H

#include  "lv_cpp/lvcpp_class.h"
#include  "customer_config.h"

class setversion
{
public:
    setversion(lv_obj_t *parent=nullptr);
    ~setversion();

    void initial(void);
    void sendcb(void (*callback)(void));

private:
    LvcppScreen* ver_screen;
    lv_obj_t* ver_parent;
    LvcppLabel* bglabel = nullptr;
    LvcppLabel* hard = nullptr;
    LvcppLabel* soft =nullptr;
    LvcppLabel* hardversion = nullptr;
    LvcppLabel* softversion =nullptr;
    void (*ver_callback)(void);
    static void btn_event_hander(lv_event_t *event);
};

#endif // SETVERSION_H
