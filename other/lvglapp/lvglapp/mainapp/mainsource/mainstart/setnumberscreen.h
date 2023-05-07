#ifndef SETNUMBERSCREEN_H
#define SETNUMBERSCREEN_H

#include  "lv_cpp/lvcpp_class.h"
#include  "customer_config.h"
#include  "kbscreen.h"


#if (QTSIM_PLATFORM==0)
#ifdef __cplusplus
extern "C" {
#endif

#include  "dl_service.h"
#include  "mainstart/zpclient/zpclient.h"
#include  "mainstart/hotplugdetect/hotplugdetect.h"
#include  "mainstart/hotplugdetect/common/applib/applib.h"
#include  "mainstart/hotplugdetect/common/applib/app_config.h"

#ifdef __cplusplus
} /*extern "C"*/
#endif
#endif

class setnumberscreen
{
public:
    setnumberscreen(lv_obj_t* parent = nullptr,void* bg_png=nullptr);
    void initial(void);
    LvcppScreen* num_screen;
    void sendcb(void (*callback)(void));
    ~setnumberscreen();
private:
    lv_obj_t* num_parent;
    LvcppLabel* input_tip = nullptr;
    LvcppLabel* Table_number = nullptr;
    LvcppButton* input_txt = nullptr;
    LvcppButton* home_server = nullptr;
    LvcppButton* cloud_server = nullptr;
    LvcppButton* go_back = nullptr;
    LvcppKeyboard* kb = nullptr;
    void kb_create(void);
    static void kb_cb(void);
    kbscreen *input_kb = nullptr;
    void (*num_callback)(void);
    void get_kbinput_text(void);
    static void btn_event_hander(lv_event_t *event);
};

#endif // SETNUMBERSCREEN_H
