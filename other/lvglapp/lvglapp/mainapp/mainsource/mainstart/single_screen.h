#ifndef SINGLE_SCREEN_H
#define SINGLE_SCREEN_H

#include  "lv_cpp/lvcpp_class.h"
#include  "customer_config.h"
#include  "singlelist.h"
#include  "renamescreen.h"
#include  "idcardscreen.h"
#include  "settingscreen.h"
#include  "service.h"
#include  "sginscreen.h"
#include  "votescreen.h"
#include  "meetingscreen.h"
#include  "speech.h"
#include  "messagescreen.h"
#include  "wifiscreen.h"
#define   SETTING_LIST_ITEM  8

#define  apapa  "单机改名"
//"单机改名","呼叫服务","会议签到","投票表决","会议内容","发言计时","短信接收","系统设置"
typedef struct{
    int count;
    singlelist* item[SETTING_LIST_ITEM];
}btn_list_t1;

class single_screen : public LvcppTimerTask
{
public:
    single_screen(lv_obj_t* parent);
    ~single_screen();

    void initial(void);
    void deinitial(void);
private:
    //LvcppFreeTypeFont* myfont=nullptr;
    void TimerCB(lv_timer_t * tmr);
    void* bg = nullptr;
    lv_timer_t* singletimer=nullptr;
    LvcppScreen* mscreen=nullptr;
    lv_obj_t* mparent=nullptr;
    LvcppList* settingview = nullptr;
    btn_list_t1 btnlist;

    //lv_obj_t* idcard=nullptr;
    //lv_obj_t* rename=nullptr;
    //lv_obj_t* setting=nullptr;
    IdcardScreen* idcard_screen=nullptr;
    RenameScreen* rename_screen=nullptr;
    service* ser_screen = nullptr;
    sginscreen* sgin_screen = nullptr;
    votescreen* vote_screen = nullptr;
    meetingscreen* meet_sceen = nullptr;
    SettingScreen* setting_screen=nullptr;
    speech* speech_screen=nullptr;
    messagescreen* message_screen=nullptr;
    IdcardScreen* incard_screen = nullptr;
    wifiscreen* wifi_screen=nullptr;
    LvcppButton* idcard =nullptr;
    void create_renamewindow(void);
    static void re_cb(void);

    void create_servicewindow(void);
    static void ser_cb(void);

    void create_sginwindow(void);
    static void sgin_cb(void);

    void create_votewindow(void);
    static void vote_cb(void);

    void create_meetingwindow(void);
    static void meet_cb(void);

    void create_speechwindow(void);
    static void speech_cb(void);

    void create_messagewindow(void);
    static void message_cb(void);

    void create_wifiwindow(void);
    static void wifi_cb(void);

    void create_incardwindow(void);
    static void incard_cb(void);
    static void btn_event_hander(lv_event_t *event);
};

#endif // SINGLE_SCREEN_H
