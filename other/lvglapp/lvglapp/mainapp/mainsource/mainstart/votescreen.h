#ifndef VOTESCREEN_H
#define VOTESCREEN_H

#include  "lv_cpp/lvcpp_class.h"
#include  "customer_config.h"

class votescreen
{
public:
    void sendcb(void (*callback)(void));
    votescreen(lv_obj_t *parent = nullptr);
    ~votescreen();
private:
    LvcppScreen* mscreen=nullptr;
    lv_obj_t* mparent=nullptr;
    void* bg = nullptr;
    LvcppButton *tip = nullptr;
    LvcppButton *back = nullptr;
    void initial(void);
    void (*vote_callback)(void);
    static void btn_event_hander(lv_event_t *event);
};

#endif // VOTESCREEN_H
