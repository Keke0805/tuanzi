#ifndef SOUNDS_H
#define SOUNDS_H

#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/customer_config.h"

typedef struct
{
    void* big[SOUNDS_IMAGE_NUM];
    void* small[SOUNDS_IMAGE_NUM];
}soundsimage_t;


class Sounds: public LvcppTimerTask
{
public:
    Sounds(lv_obj_t* parent=nullptr);
    ~Sounds();
    void switch_cartoon_left(void);
    void switch_cartoon_right(void);
protected:
    void ui_image_decode(void);
    void ui_image_free(void);
    void ui_txt_decede(void);
    soundsimage_t imagelist;
    char*  txtlist[SOUNDS_IMAGE_NUM];
    void*  SOUNDS_BIRD_B_PNG=NULL;
    void*  SOUNDS_BIRD_S_PNG=NULL;
    void*  SOUNDS_BONFIRE_B_PNG=NULL;
    void*  SOUNDS_BONFIRE_S_PNG=NULL;
    void*  SOUNDS_FAN_B_PNG=NULL;
    void*  SOUNDS_FAN_S_PNG=NULL;
    void*  SOUNDS_LULLABY_B_PNG=NULL;
    void*  SOUNDS_LULLABY_S_PNG=NULL;
    void*  SOUNDS_MUSICBOX_B_PNG=NULL;
    void*  SOUNDS_MUSICBOX_S_PNG=NULL;
    void*  SOUNDS_OCEAN_B_PNG=NULL;
    void*  SOUNDS_OCEAN_S_PNG=NULL;
    void*  SOUNDS_PENDULUM_B_PNG=NULL;
    void*  SOUNDS_PENDULUM_S_PNG=NULL;
    void*  SOUNDS_RAIN_B_PNG=NULL;
    void*  SOUNDS_RAIN_S_PNG=NULL;
    void*  SOUNDS_STREAM_B_PNG=NULL;
    void*  SOUNDS_STREAM_S_PNG=NULL;
    void*  SOUNDS_SUMMERNIGHT_B_PNG=NULL;
    void*  SOUNDS_SUMMERNIGHT_S_PNG=NULL;
    void*  SOUNDS_THUNDERSTORM_B_PNG=NULL;
    void*  SOUNDS_THUNDERSTORM_S_PNG=NULL;
    void*  SOUNDS_TRAIN_B_PNG=NULL;
    void*  SOUNDS_TRAIN_S_PNG=NULL;

    void*  SOUNDS_TV_B_PNG=NULL;
    void*  SOUNDS_TV_S_PNG=NULL;

    void*  SOUNDS_WAVE_B_PNG=NULL;
    void*  SOUNDS_WAVE_S_PNG=NULL;

    void*  SOUNDS_WIND_B_PNG=NULL;
    void*  SOUNDS_WIND_S_PNG=NULL;

private:
    LvcppScreen* mscreen=nullptr;
    lv_obj_t* m_parent=nullptr;

    void initial(void);
    void deinitial(void);

    lv_timer_t* maintimer=nullptr;
    void TimerCB(lv_timer_t * tmr);

    int scroll_flag=0;
    int cur_index=0;
    int cur_head=0;
    int cur_tail=SOUNDS_IMAGE_NUM-1;
    int mid_image=SOUNDS_IMAGE_NUM/2;
    int scroll_len=0;

    lv_point_t point[SOUNDS_LIST_LEN+1];
    lv_point_t point_list[SOUNDS_IMAGE_NUM];
    LvcppScreen* cont = nullptr;
    LvcppButton* menulist[SOUNDS_IMAGE_NUM];
    LvcppLabel* current_position = nullptr;//ด๓
    LvcppLabel* current_function = nullptr;//ะก
    void draw_point(void);
    void lvgl_scroll_anim(void);
    void imagelist_update(void);
    void scroll_anim_exe(int step);


};

#endif // SOUNDS_H
