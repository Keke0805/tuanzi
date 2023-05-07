#ifndef SETBRIGHSCREEN_H
#define SETBRIGHSCREEN_H

#include  "lv_cpp/lvcpp_class.h"
#include  "customer_config.h"

class setbrighscreen
{
public:
    setbrighscreen(lv_obj_t* parent = nullptr,void* bg_png=nullptr);
    void initial(void);
    void sendcb(void (*callback)(void));
    LvcppScreen* bri_screen;
    ~setbrighscreen();
private:
    lv_obj_t* bri_parent;
    LvcppLabel* max_value = nullptr;
    LvcppLabel* mix_value = nullptr;
    LvcppButton* go_back = nullptr;
    LvcppSlider *set_bri_slider =nullptr;
    void (*bri_callback)(void);
    static void btn_event_hander(lv_event_t *event);
};

#endif // SETBRIGHSCREEN_H
