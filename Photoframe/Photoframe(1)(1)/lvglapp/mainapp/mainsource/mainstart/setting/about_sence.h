#ifndef ABOUT_SENCE_H
#define ABOUT_SENCE_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
typedef struct storage_info
{
    off64_t total_size;
    off64_t free_size;
    char total_str[32];
    char free_str[32];
}storage_info_t;

class aboutSence
{
public:
    aboutSence(lv_obj_t* parent = nullptr);
    ~aboutSence(void);
private:
    static void aboutSence_event_handler(lv_event_t *event);
    LvcppButton* versionButton =NULL;
    LvcppButton* frameIdButton =NULL;
    LvcppButton* serialNumButton =NULL;
    LvcppButton* wifiMACButton =NULL;
    LvcppButton* modelButton =NULL;
    LvcppButton* buildNumButton =NULL;
    LvcppButton* storageButton =NULL;
    LvcppLabel* versionLabel =NULL;
    LvcppLabel* versionChildLabel =NULL;
    LvcppLabel* frameIdLabel =NULL;
    LvcppLabel* serialNumLabel =NULL;
    LvcppLabel* wifiMACLabel =NULL;
    LvcppLabel* modelLabel =NULL;
    LvcppLabel* buildNumLabel =NULL;
    LvcppLabel* storageLabel =NULL;
    LvcppLabel* storageChildLabel =NULL;
    LvcppLabel* versionline =NULL;
    LvcppLabel* frameIdline =NULL;
    LvcppLabel* serialNumline =NULL;
    LvcppLabel* wifiMACline =NULL;
    LvcppLabel* modelline =NULL;
    LvcppLabel* buildNumline =NULL;
    LvcppLabel* storageline =NULL;
};

#endif // ABOUT_SENCE_H
