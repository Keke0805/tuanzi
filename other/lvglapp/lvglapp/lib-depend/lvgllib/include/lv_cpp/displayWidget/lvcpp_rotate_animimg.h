#ifndef LVCPP_ROTATE_ANIMIMG_H
#define LVCPP_ROTATE_ANIMIMG_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"


class LvcppRotateAnimimg : public LvcppObject
{
public:
    LvcppRotateAnimimg(lv_obj_t* parent=nullptr);
    ~LvcppRotateAnimimg(void);

    //set
    int set_var(void * var);
    int set_exec_cb( lv_anim_exec_xcb_t exec_cb);
    int set_time(uint32_t duration);
    int set_delay( uint32_t delay);
    int set_custom_exec_cb( lv_anim_custom_exec_cb_t exec_cb);
    int set_path_cb( lv_anim_path_cb_t path_cb);
    int set_start_cb( lv_anim_start_cb_t start_cb);
    int set_get_value_cb( lv_anim_get_value_cb_t get_value_cb);
    int set_ready_cb( lv_anim_ready_cb_t ready_cb);
    int set_playback_time( uint32_t time);
    int set_playback_delay( uint32_t delay);
    int set_repeat_count(uint16_t cnt);
    int set_early_apply( bool en);
    int set_user_data( void * user_data);
    int set_animimg_src(const void * src);
    int set_pivot(lv_coord_t x, lv_coord_t y);
    int set_values(int32_t start, int32_t end);
    int start(void);
    bool del(void * var, lv_anim_exec_xcb_t exec_cb);
    void del_all(void);

    //get
    int get_delay(void);
    int get_playtime(void);
    int path_linear(void);
    int path_ease_in(void);
    int path_ease_out(void);
    int path_ease_in_out(void);
    int path_overshoot(void);
    int path_bounce(void);
    int path_step(void);
    int count_running(void);
    int speed_to_time(uint32_t speed, int32_t start, int32_t end);
    int refresh(void);
private:
    lv_anim_t anim;

    static void set_angle(void* img, int32_t v);
};

#endif // LVCPP_ROTATE_ANIMIMG_H
