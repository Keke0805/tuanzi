#ifndef SETTINGSCREEN_H
#define SETTINGSCREEN_H

#include  "lv_cpp/lvcpp_class.h"
#include  "customer_config.h"
#include  "medialist.h"
#include  "setbrighscreen.h"
#include  "setlanguagescreen.h"
#include  "setnumberscreen.h"
#include  "setnetwork.h"
#include  "setversion.h"

#define   SETTING_LIST_ITEM  6

typedef struct{
    int count;
    medialist* item[SETTING_LIST_ITEM];
}btn_list_t;


class SettingScreen
{
public:
    SettingScreen(lv_obj_t* parent=nullptr);
    ~SettingScreen();

    void initial(void);
    void deinitial(void);

private:

    void* bg = nullptr;

    LvcppScreen* mscreen=nullptr;
    lv_obj_t* mparent=nullptr;
    LvcppFreeTypeFont* myfont=nullptr;
    LvcppList* settingview = nullptr;
    LvcppLabel* set_tip = nullptr;
    btn_list_t btnlist;
    void setting_window(void);

    static void kb_cb(void);

    void zp_param_clear(void);

    void networkscreen_creat(void);
    SettingNet* networkscreen = nullptr;
    static void networkscreen_cb(void);

    void briscreen_creat(void);
    setbrighscreen* briscreen = nullptr;
    static void briscreen_cb(void);

    void numscreen_creat(void);
    setnumberscreen* numscreen = nullptr;
    static void numscreen_cb(void);

    void languagescreen_creat(void);
    setlanguagescreen* languagesereen = nullptr;
     static void languagesereen_cb(void);

     void version_creat(void);
     setversion* setversionscreen = nullptr;
      static void setversionscreen_cb(void);

    static void btn_event_hander(lv_event_t *event);

};

#endif // SETTINGSCREEN_H
