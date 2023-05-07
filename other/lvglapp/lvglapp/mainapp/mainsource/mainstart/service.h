#ifndef SERVICE_H
#define SERVICE_H

#include  "lv_cpp/lvcpp_class.h"
#include  "customer_config.h"
#include  "boxtipscreen.h"
#include  "kbscreen.h"

class service
{
public:
    void sendcb(void (*callback)(void));
    service(lv_obj_t *parent = nullptr);
    ~service();
private:
    LvcppScreen* mscreen=nullptr;
    lv_obj_t* mparent=nullptr;
    void* bg = nullptr;
    LvcppButton *tea = nullptr;
    LvcppButton *paper_and_pen = nullptr;
    LvcppButton *microphone = nullptr;
    LvcppButton *waiter = nullptr;
    LvcppButton *Other_requests = nullptr;
    LvcppButton *back = nullptr;

    void kb_create(void);
    static void kb_cb(void);
    kbscreen *input_kb = nullptr;

    boxtipscreen* box_screen=nullptr;
    void create_boxwindow(void);
    static void box_cb(void);

    void initial(void);
    void (*ser_callback)(void);
    static void btn_event_hander(lv_event_t *event);
};

#endif // SERVICE_H
