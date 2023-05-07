#ifndef DYNAMIC_H
#define DYNAMIC_H

#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/customer_config.h"

typedef struct
{
    void* big[DYNAMIC_IMAGE_NUM];
    void* small[DYNAMIC_IMAGE_NUM];
}Dynamicimage_t;

class Dynamic: public LvcppTimerTask
{
public:
    Dynamic(lv_obj_t* parent=nullptr);
    ~Dynamic();
    void switch_cartoon_left(void);
    void switch_cartoon_right(void);

    void wallpaper_initial(int cur_type);

protected:
    void ui_image_decode(void);
    void ui_image_free(void);
    void ui_txt_decede(void);
    Dynamicimage_t imagelist;
    char*  txtlist[DYNAMIC_IMAGE_NUM];
    void*  Dynamic_Beat_B_PNG=NULL;
    void*  Dynamic_Beat_S_PNG=NULL;
    void*  Dynamic_City_B_PNG=NULL;
    void*  Dynamic_City_S_PNG=NULL;
    void*  Dynamic_Fireplace_B_PNG=NULL;
    void*  Dynamic_Fireplace_S_PNG=NULL;
    void*  Dynamic_Fireworks_B_PNG=NULL;
    void*  Dynamic_Fireworks_S_PNG=NULL;
    void*  Dynamic_Jellyfish_B_PNG=NULL;
    void*  Dynamic_Jellyfish_S_PNG=NULL;
    void*  Dynamic_Rain_B_PNG=NULL;
    void*  Dynamic_Rain_S_PNG=NULL;
    void*  Dynamic_Seabed_B_PNG=NULL;
    void*  Dynamic_Seabed_S_PNG=NULL;
    void*  Dynamic_Snow_B_PNG=NULL;
    void*  Dynamic_Snow_S_PNG=NULL;
    void*  Dynamic_Space_B_PNG=NULL;
    void*  Dynamic_Space_S_PNG=NULL;
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
    int cur_tail=DYNAMIC_IMAGE_NUM-1;
    int mid_image=DYNAMIC_IMAGE_NUM/2;
    int scroll_len=0;

    lv_point_t point[DYNAMIC_LIST_LEN+1];
    lv_point_t point_list[DYNAMIC_IMAGE_NUM];
    LvcppScreen* cont = nullptr;
    LvcppButton* menulist[DYNAMIC_IMAGE_NUM];
    LvcppLabel* current_position = nullptr;//ด๓
    LvcppLabel* current_function = nullptr;//ะก
    void draw_point(void);
    void lvgl_scroll_anim(void);
    void imagelist_update(void);
    void scroll_anim_exe(int step);

    //player


    void media_player_initial(void);
    void media_player_deinitial(void);
    void media_player_to_play(const char* url);
};

#endif // DYNAMIC_H
