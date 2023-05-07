#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H

#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/customer_config.h"

typedef struct
{
    void* big[LIGHT_IMAGE_NUM];
    void* small[LIGHT_IMAGE_NUM];
}brightimage_t;

class Brightness: public LvcppTimerTask
{
public:
    Brightness(lv_obj_t* parent=nullptr);
    ~Brightness();
    void switch_cartoon_left(void);
    void switch_cartoon_right(void);
protected:
    void ui_image_decode(void);
    void ui_image_free(void);
    void ui_txt_decede(void);
    brightimage_t imagelist;
    char*  txtlist[LIGHT_IMAGE_NUM];
    void*  bright_blue_B_PNG=NULL;
    void*  bright_blue_S_PNG=NULL;
    void*  bright_green_B_PNG=NULL;
    void*  bright_green_S_PNG=NULL;
    void*  bright_lightoff_B_PNG=NULL;
    void*  bright_lightoff_S_PNG=NULL;
    void*  bright_lemon_B_PNG=NULL;
    void*  bright_lemon_S_PNG=NULL;
    void*  bright_orange_B_PNG=NULL;
    void*  bright_orange_S_PNG=NULL;
    void*  bright_pink_B_PNG=NULL;
    void*  bright_pink_S_PNG=NULL;
    void*  bright_purple_B_PNG=NULL;
    void*  bright_purple_S_PNG=NULL;
    void*  bright_red_B_PNG=NULL;
    void*  bright_red_S_PNG=NULL;
    void*  bright_RGB_B_PNG=NULL;
    void*  bright_RGB_S_PNG=NULL;
    void*  bright_yellow_B_PNG=NULL;
    void*  bright_yellow_S_PNG=NULL;
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
    int cur_tail=LIGHT_IMAGE_NUM-1;
    int mid_image=LIGHT_IMAGE_NUM/2;
    int scroll_len=0;

    lv_point_t point[LIGHT_LIST_LEN+1];
    lv_point_t point_list[LIGHT_IMAGE_NUM];
    LvcppScreen* cont = nullptr;
    LvcppButton* menulist[LIGHT_IMAGE_NUM];
    LvcppLabel* current_position = nullptr;//ด๓
    LvcppLabel* current_function = nullptr;//ะก
    void draw_point(void);
    void lvgl_scroll_anim(void);
    void imagelist_update(void);
    void scroll_anim_exe(int step);
};

#endif // BRIGHTNESS_H
