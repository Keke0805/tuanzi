#ifndef LIGHT_H
#define LIGHT_H

#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/customer_config.h"

#define MIN_BRIGHTNESS 0 // 最小亮度值
#define MAX_BRIGHTNESS 70 // 最大亮度值
#define DEFAULT_BRIGHTNESS 40 // 默认亮度值
#define STEP_SIZE 10 // 每次旋转步进的亮度值
typedef struct
{
    void* big[LIGHT_IMAGE_NUM];
    void* small[LIGHT_IMAGE_NUM];
}lightimage_t;

class Light: public LvcppTimerTask
{
public:
    Light(lv_obj_t* parent=nullptr);
    ~Light();
    void ui_image_decode(void);
    void ui_image_free(void);
    void initial(int light_tmp,char *value);
    void update_light(int light_tmp);
    void*  Light_PNG=NULL;
    void* CLASSIC_JPG=NULL;
private:
    LvcppScreen* mscreen=nullptr;
    lv_obj_t* m_parent=nullptr;
    LvcppLabel* light_icon = nullptr;
    LvcppSlider* light_slider = nullptr;
    LvcppLabel* light_VALUE=nullptr;
    void deinitial(void);
static void btn_event_hander(lv_event_t *event);
    lv_timer_t* maintimer=nullptr;
    void TimerCB(lv_timer_t * tmr);



};

#endif // LIGHT_H
