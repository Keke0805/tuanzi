#ifndef WIFISCREEN_H
#define WIFISCREEN_H

#include  "lv_cpp/lvcpp_class.h"
#include  "customer_config.h"

class wifiscreen
{
public:
    void sendcb(void (*callback)(void));
    wifiscreen(lv_obj_t *parent = nullptr);
    ~wifiscreen();
private:
    LvcppScreen* mscreen=nullptr;
    lv_obj_t* mparent=nullptr;
    void* bg = nullptr;
    LvcppLabel *head = nullptr;
    LvcppLabel *Frame = nullptr;
    LvcppButton *back = nullptr;
    void initial(void);
    void (*wifiscreen_callback)(void);
    static void btn_event_hander(lv_event_t *event);
};


#endif // WIFISCREEN_H
