#ifndef STATICAL_H
#define STATICAL_H

#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/customer_config.h"

typedef struct
{
    void* big[STATIC_IMAGE_NUM];
    void* small[STATIC_IMAGE_NUM];
}staticimage_t;

class Statical: public LvcppTimerTask
{
public:
    Statical(lv_obj_t* parent=nullptr);
    ~Statical();
    void switch_cartoon_left(void);
    void switch_cartoon_right(void);

    void wallpaper_initial(int cur_type);

protected:
    void ui_image_decode(void);
    void ui_image_free(void);
    void ui_txt_decede(void);
    staticimage_t imagelist;
    char*  txtlist[STATIC_IMAGE_NUM];
    void*  Statical_Butter_B_PNG=NULL;
    void*  Statical_Butter_S_PNG=NULL;
    void*  Statical_Christmas_B_PNG=NULL;
    void*  Statical_Christmas_S_PNG=NULL;
    void*  Statical_Classic_B_PNG=NULL;
    void*  Statical_Classic_S_PNG=NULL;
    void*  Statical_Disco_B_PNG=NULL;
    void*  Statical_Disco_S_PNG=NULL;
    void*  Statical_Game_B_PNG=NULL;
    void*  Statical_Game_S_PNG=NULL;
    void*  Statical_Halloween_B_PNG=NULL;
    void*  Statical_Halloween_S_PNG=NULL;
    void*  Statical_Space_B_PNG=NULL;
    void*  Statical_Space_S_PNG=NULL;
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
    int cur_tail=STATIC_IMAGE_NUM-1;
    int mid_image=STATIC_IMAGE_NUM/2;
    int scroll_len=0;

    lv_point_t point[STATICAL_LIST_LEN+1];
    lv_point_t point_list[STATIC_IMAGE_NUM];
    LvcppScreen* cont = nullptr;
    LvcppButton* menulist[STATIC_IMAGE_NUM];
    LvcppLabel* current_position = nullptr;//ด๓
    LvcppLabel* current_function = nullptr;//ะก
    void draw_point(void);
    void lvgl_scroll_anim(void);
    void imagelist_update(void);
    void scroll_anim_exe(int step);

    //player


    void image_player_initial(void);
    void image_player_deinitial(void);
    void image_player_to_play(const char* path);

};

#endif // STATICAL_H
