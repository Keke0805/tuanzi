#ifndef IDCARDSCREEN_H
#define IDCARDSCREEN_H

#include  "lv_cpp/lvcpp_class.h"
#include  "customer_config.h"

#if (QTSIM_PLATFORM==0)
#ifdef __cplusplus
extern "C" {
#endif
#include "dl_service.h"
#include  "mainstart/zpclient/zpclient.h"
#include  "mainstart/hotplugdetect/hotplugdetect.h"
#include  "mainstart/hotplugdetect/common/applib/applib.h"
#include  "mainstart/hotplugdetect/common/applib/app_config.h"

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif

class IdcardScreen : public LvcppTimerTask
{
public:
    void sendcb(void (*callback)(void));
    IdcardScreen(lv_obj_t* parent=nullptr);
    ~IdcardScreen();
    void initial(void);
    void deinitial(void);

    LvcppScreen* mscreen=nullptr;
private:
    void TimerCB(lv_timer_t * tmr);

    lv_timer_t* idcardtimer=nullptr;


    lv_obj_t* mparent=nullptr;

    void zp_param_initial(void);

    mThread* decode_thread = nullptr;
    static void* thread_decode_image(void* arg);

    pthread_t m_tid;
    pthread_attr_t pthread_attr;
    void decode_thread_start(void);

    LvcppCanvas* canvas=nullptr;
    lv_color_t* cbuf=nullptr;
    lv_font_t* myfont0=nullptr;
    lv_font_t* myfont1=nullptr;
    lv_font_t* myfont2=nullptr;
    lv_font_t* myfont3=nullptr;
    lv_draw_label_dsc_t label_dsc0;
    lv_draw_label_dsc_t label_dsc1;
    lv_draw_label_dsc_t label_dsc2;
    lv_draw_label_dsc_t label_dsc3;
    lv_draw_img_dsc_t img_draw_dsc;
    LvcppButton* back =nullptr;
    void canvas_initial(void);
    lv_color_t* create_canvas(void);
    void repaint_canvas(void);
    void repaint_idcard(void);
    void canvas_to_img(void);
    void clear_canvas(void);
    void delete_canvas(void);

    void font_initial(void);
    void font_destroy(void);
    void font_reset(void);
    void font_scan_file_path(char* name,const char** font);
    uint8_t toByte(char c);
    void hexStringToByte(uint8_t *dstByte,const char *srcHexString ,int len);
    void BgraToRgb(uint8_t *bgraData,int width,int height,uint8_t*rgbData);

    char url[1024]={0};
    int hv_http_request(void);
    void ReqStringtoJsonParse(std::string data);
    static void btn_event_hander(lv_event_t *event);
    void (*incard_callback)(void);
    #if (QTSIM_PLATFORM==0)
    static void idcard_sys_proc(msg_apps_t *msg);
    #endif
};

#endif // IDCARDSCREEN_H
