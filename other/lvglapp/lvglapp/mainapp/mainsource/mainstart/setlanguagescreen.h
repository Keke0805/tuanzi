#ifndef SETLANGUAGESCREEN_H
#define SETLANGUAGESCREEN_H

#include  "lv_cpp/lvcpp_class.h"
#include  "customer_config.h"

class setlanguagescreen
{
public:
    setlanguagescreen(lv_obj_t* parent = nullptr,void* bg_png=nullptr);
    void initial(void);
    void sendcb(void (*callback)(void));
    LvcppScreen* la_screen;
    ~setlanguagescreen();
private:
    lv_obj_t* la_parent;
    LvcppButton* Chinese = nullptr;
    LvcppButton* English =nullptr;
    LvcppButton* go_back = nullptr;
    void (*la_callback)(void);
    static void btn_event_hander(lv_event_t *event);
};

#endif // SETLANGUAGESCREEN_H
