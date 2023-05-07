#ifndef SGINSCREEN_H
#define SGINSCREEN_H

#include  "lv_cpp/lvcpp_class.h"
#include  "customer_config.h"
#include  "boxtipscreen.h"
class sginscreen
{
public:
    void sendcb(void (*callback)(void));
    sginscreen(lv_obj_t *parent = nullptr);
    ~sginscreen();
private:
    LvcppScreen* mscreen=nullptr;
    lv_obj_t* mparent=nullptr;
    void* bg = nullptr;
    LvcppButton *company = nullptr;
    LvcppButton *name = nullptr;
    LvcppButton *time = nullptr;
    LvcppButton *Sgin = nullptr;
    LvcppButton *back = nullptr;

    boxtipscreen* box_screen=nullptr;
    void create_boxwindow(void);
    static void box_cb(void);

    void initial(void);
    void (*sgin_callback)(void);
    static void btn_event_hander(lv_event_t *event);
};

#endif // SGINSCREEN_H
