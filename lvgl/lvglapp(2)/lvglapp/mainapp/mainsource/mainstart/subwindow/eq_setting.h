#ifndef EQ_SETTING_H
#define EQ_SETTING_H

#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/customer_config.h"

typedef struct
{
    void* big[EQ_IMAGE_NUM];
    void* small[EQ_IMAGE_NUM];
}EQimage_t;

class EQ_setting: public LvcppTimerTask
{
public:
    EQ_setting(lv_obj_t* parent=nullptr);
    ~EQ_setting();
    void switch_cartoon_left(void);
    void switch_cartoon_right(void);
    void*  EQ_CLASSICAL_B_PNG=NULL;
    void*  EQ_CLASSICAL_S_PNG=NULL;
    void*  EQ_JAZZ_B_PNG=NULL;
    void*  EQ_JAZZ_S_PNG=NULL;
    void*  EQ_ROCK_B_PNG=NULL;
    void*  EQ_ROCK_S_PNG=NULL;
    void*  EQ_STEREO_B_PNG=NULL;
    void*  EQ_STEREO_S_PNG=NULL;
    void*  EQ_VOCAL_B_PNG=NULL;
    void*  EQ_VOCAL_S_PNG=NULL;
private:
    void ui_image_decode(void);
    void ui_image_free(void);
    void ui_txt_decede(void);
    EQimage_t imagelist;
    char*  txtlist[EQ_IMAGE_NUM];
    LvcppScreen* mscreen=nullptr;
    lv_obj_t* m_parent=nullptr;
    LvcppLabel* current_position = nullptr;//ด๓
    LvcppLabel* current_function = nullptr;//ะก
    int scroll_flag=0;
    int cur_index=0;
    int cur_head=0;
    int cur_tail=EQ_IMAGE_NUM-1;
    int mid_image=EQ_IMAGE_NUM/2;
    int scroll_len=0;
    lv_point_t point[EQ_LIST_LEN+1];
    lv_point_t point_list[EQ_IMAGE_NUM];
    LvcppScreen* cont = nullptr;
    LvcppButton* menulist[EQ_IMAGE_NUM];
    void initial(void);
    void deinitial(void);
    void draw_point(void);
    void lvgl_scroll_anim(void);
    void imagelist_update(void);
    void scroll_anim_exe(int step);

    lv_timer_t* maintimer=nullptr;
    void TimerCB(lv_timer_t * tmr);
};

#endif // EQ_SETTING_H
