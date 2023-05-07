#ifndef LYRICS_H
#define LYRICS_H

#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/customer_config.h"
#include <fstream>
#include <iostream>

class Lyrics: public LvcppTimerTask
{
public:
    Lyrics(lv_obj_t* parent=nullptr);
    ~Lyrics();

    void switch_cartoon_up(char* old_lyrics);
    void switch_cartoon_down(char* new_lyrics);

    void show(bool flag);

private:
    LvcppScreen* mscreen=nullptr;
    lv_obj_t* m_parent=nullptr;

    void initial(void);
    void deinitial(void);

    lv_timer_t* maintimer=nullptr;
    void TimerCB(lv_timer_t * tmr);

    int center_flag=0;

    int scroll_flag=0;
    int cur_index=0;
    int cur_head=0;
    int cur_tail=LYRICS_NUM-1;
    int mid_image=LYRICS_NUM/2;
    int scroll_len=0;

    lv_point_t point[LYRICS_LIST_HIGH*LYRICS_NUM+1];
    lv_point_t point_list[LYRICS_NUM];
    LvcppScreen* cont = nullptr;
    LvcppButton* menulist[LYRICS_NUM];
    void draw_point(void);
    void lvgl_scroll_anim(void);
    void imagelist_update(void);
    void scroll_anim_exe(int step);

    ifstream lyrics_fd;
    void read_lyrics_flie(const char * name);
};

#endif // LYRICS_H
