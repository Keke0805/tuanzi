#ifndef MEETINGSCREEN_H
#define MEETINGSCREEN_H

#include  "lv_cpp/lvcpp_class.h"
#include  "customer_config.h"
#include  "boxtipscreen.h"

class meetingscreen
{
public:
    void sendcb(void (*callback)(void));
    meetingscreen(lv_obj_t *parent = nullptr);
    ~meetingscreen();
private:
    LvcppScreen* mscreen=nullptr;
    lv_obj_t* mparent=nullptr;
    void* bg = nullptr;
    LvcppButton *conference_agenda = nullptr;
    LvcppButton *content_of_meeting = nullptr;
    LvcppButton *back = nullptr;

    boxtipscreen* box_screen=nullptr;
    void create_boxwindow(void);
    static void box_cb(void);

    void initial(void);
    void (*meeting_callback)(void);
    static void btn_event_hander(lv_event_t *event);
};


#endif // MEETINGSCREEN_H
