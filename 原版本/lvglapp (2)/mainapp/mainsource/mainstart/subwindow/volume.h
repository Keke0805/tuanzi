#ifndef VOLUME_H
#define VOLUME_H

#include  "lv_cpp/lvcpp_class.h"
#include  "mainstart/customer_config.h"


class Volume: public LvcppTimerTask
{
public:
    Volume(lv_obj_t* parent=nullptr);
    ~Volume();
    void update_volume(int eq_tmp);
    void initial(int eq_tmp,char *value);


private:
    void ui_image_decode(void);
    void ui_image_free(void);
    void*  Volume_PNG = NULL;
    void*  EQ_B_PNG = NULL;
    void*  EQ_S_PNG = NULL;
    void*  Volume_B_PNG = NULL;
    void*  Volume_S_PNG = NULL;
    void*  BACK_PNG = NULL;
    void*  BAR_PNG = NULL;
    void*  BAR_PNG1 = NULL;
    void*  VOLUME_B_ICON = NULL;
    bool StartTimerShow =false;
    LvcppScreen* mscreen=nullptr;
    lv_obj_t* m_parent=nullptr;
    LvcppLabel* current_icon = nullptr;
    LvcppLabel* EQ_icon = nullptr;
    LvcppLabel* EQ_bar = nullptr;


    LvcppLabel* VOLUME_icon = nullptr;
    LvcppSlider* VOLUME_slider = nullptr;
    LvcppButton* back_icon = nullptr;

    LvcppLabel* EQ_VALUE = nullptr;
    LvcppLabel* VOLUME_VALUE = nullptr;
    LvcppLabel* VOLUME_B_bar = nullptr;
    LvcppSlider* VOLUME_B_slider = nullptr;
    LvcppLabel* VOLUME_B_VALUE = nullptr;
    static void btn_event_hander(lv_event_t *event);
    void deinitial(void);
    lv_timer_t* maintimer=nullptr;
    //
    /*
    lvcpp_sys_datetime_t sys_datetime;
    lvcpp_sys_datetime_t user_time;

    void deinitial(void);
    bool clockList_show =false;
    int timecntback = 0;
    lv_timer_t* maintimer=nullptr;
    int update_current(void);
    //
    */
    void TimerCB(lv_timer_t * tmr);

};

#endif // VOLUME_H
