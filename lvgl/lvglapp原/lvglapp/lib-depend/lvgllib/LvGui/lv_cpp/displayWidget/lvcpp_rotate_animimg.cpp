#include "lvcpp_rotate_animimg.h"

LvcppRotateAnimimg::LvcppRotateAnimimg(lv_obj_t* parent)
{
    myobj = lv_animimg_create(parent);
    lv_anim_init(&anim);
    lv_anim_set_var(&anim, myobj);
    lv_anim_set_exec_cb(&anim, set_angle);
}

LvcppRotateAnimimg::~LvcppRotateAnimimg(void)
{
    lv_anim_del(&anim,set_angle);
}

//set
int LvcppRotateAnimimg::set_var(void * var)
{
    lv_anim_set_var(&anim,var);
    return 0;
}

int LvcppRotateAnimimg::set_exec_cb( lv_anim_exec_xcb_t exec_cb)
{
    lv_anim_set_exec_cb(&anim,exec_cb);
    return 0;
}


int LvcppRotateAnimimg::set_time(uint32_t duration)
{
    lv_anim_set_time(&anim, duration);
    return 0;
}

int LvcppRotateAnimimg::set_delay( uint32_t delay)
{
    lv_anim_set_delay(&anim,delay);
    return 0;
}

int LvcppRotateAnimimg::set_custom_exec_cb( lv_anim_custom_exec_cb_t exec_cb)
{
    lv_anim_set_custom_exec_cb(&anim,exec_cb);
    return 0;
}

int LvcppRotateAnimimg::set_path_cb( lv_anim_path_cb_t path_cb)
{
    lv_anim_set_path_cb(&anim,path_cb);
    return 0;
}

int LvcppRotateAnimimg::set_start_cb( lv_anim_start_cb_t start_cb)
{
    lv_anim_set_start_cb(&anim,start_cb);
    return 0;
}

int LvcppRotateAnimimg::set_get_value_cb( lv_anim_get_value_cb_t get_value_cb)
{
    lv_anim_set_get_value_cb(&anim,get_value_cb);
    return 0;
}

int LvcppRotateAnimimg::set_ready_cb( lv_anim_ready_cb_t ready_cb)
{
    lv_anim_set_ready_cb(&anim, ready_cb);
    return 0;
}

int LvcppRotateAnimimg::set_playback_time( uint32_t time)
{
    lv_anim_set_playback_time(&anim,time);
    return 0;
}

int LvcppRotateAnimimg::set_playback_delay( uint32_t delay)
{
    lv_anim_set_playback_delay(&anim,delay);
    return 0;
}


int LvcppRotateAnimimg::set_repeat_count(uint16_t cnt)
{
    lv_anim_set_repeat_count(&anim, cnt);
    return 0;
}

int LvcppRotateAnimimg::set_early_apply( bool en)
{
    lv_anim_set_early_apply(&anim,en);
    return 0;
}

int LvcppRotateAnimimg::set_user_data( void * user_data)
{
    lv_anim_set_user_data(&anim,user_data);
    return 0;
}


int LvcppRotateAnimimg::set_animimg_src(const void * src)
{
    lv_img_set_src(myobj, src);
    return 0;
}

int LvcppRotateAnimimg::set_pivot(lv_coord_t x, lv_coord_t y)
{
    lv_img_set_pivot(myobj, x, y);
    return 0;
}
int LvcppRotateAnimimg::set_values(int32_t start, int32_t end)
{
    lv_anim_set_values(&anim, start, end);
    return 0;
}

int LvcppRotateAnimimg::start(void)
{
    lv_anim_start(&anim);
    return 0;
}

bool del(void * var, lv_anim_exec_xcb_t exec_cb)
{
   return lv_anim_del(var,exec_cb);
}

void del_all(void)
{
    lv_anim_del_all();
}

//get
int LvcppRotateAnimimg::get_delay(void)
{
    return lv_anim_get_delay(&anim);
}

int LvcppRotateAnimimg::get_playtime(void)
{
    return lv_anim_get_playtime(&anim);
}

int LvcppRotateAnimimg::path_linear(void)
{
    return lv_anim_path_linear(&anim);
}

int LvcppRotateAnimimg::path_ease_in(void)
{
    return lv_anim_get_delay(&anim);
}

int LvcppRotateAnimimg::path_ease_out(void)
{
    return lv_anim_path_ease_out(&anim);
}

int LvcppRotateAnimimg::path_ease_in_out(void)
{
    return lv_anim_path_ease_in_out(&anim);
}

int LvcppRotateAnimimg::path_overshoot(void)
{
    return lv_anim_path_overshoot(&anim);
}

int LvcppRotateAnimimg::path_bounce(void)
{
    return lv_anim_path_bounce(&anim);
}

int LvcppRotateAnimimg::path_step(void)
{
    return lv_anim_path_step(&anim);
}

int LvcppRotateAnimimg::count_running(void)
{
    return lv_anim_count_running();
}

int LvcppRotateAnimimg::speed_to_time(uint32_t speed, int32_t start, int32_t end)
{
    return lv_anim_speed_to_time(speed,start,end);
}

int LvcppRotateAnimimg::refresh(void)
{
    lv_anim_refr_now();
    return 0;
}

//private:
void LvcppRotateAnimimg::set_angle(void* img, int32_t v)
{
    if(img !=NULL)
    {
        lv_img_set_angle((lv_obj_t *)img, v);
    }
}

