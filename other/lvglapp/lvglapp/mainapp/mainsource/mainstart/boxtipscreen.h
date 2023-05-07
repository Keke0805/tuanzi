#ifndef boxtipscreen_H
#define boxtipscreen_H

#include  "lv_cpp/lvcpp_class.h"
#include  "customer_config.h"

class boxtipscreen
{
public:
    void sendcb(void (*callback)(void));
    boxtipscreen(lv_obj_t *parent = nullptr);
    ~boxtipscreen();
private:
    LvcppScreen* mscreen=nullptr;
    lv_obj_t* mparent=nullptr;
    void* bg = nullptr;
    LvcppLabel *tips = nullptr;
    LvcppButton *back = nullptr;
    void initial(void);
    void (*ser_callback)(void);


    static void btn_event_hander(lv_event_t *event);
};


#endif // BOXTIPSCREEN_H
