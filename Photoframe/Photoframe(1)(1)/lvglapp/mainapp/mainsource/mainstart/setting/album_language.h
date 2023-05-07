#ifndef ALBUM_LANGUAGE_H
#define ALBUM_LANGUAGE_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "album_language_list.h"

class albumLanguage
{
public:
    albumLanguage();
    ~albumLanguage(void);
    LvcppScreen* LanguageScreen=NULL;
    albumLanguageList* LanList1 =NULL;
    albumLanguageList* LanList2 =NULL;
    albumLanguageList* LanList3 =NULL;
    albumLanguageList* LanList4 =NULL;
    albumLanguageList* LanList5 =NULL;
    albumLanguageList* LanList6 =NULL;
    albumLanguageList* LanList7 =NULL;
    albumLanguageList* LanList8 =NULL;
private:
    LvcppList* LanguageList=NULL;
    static void albumLanguage_event_handler(lv_event_t *event);
    void albumLanguage_SelIndex(int index,int saveIndex);
    int lauIndex =0;
};

#endif // ALBUM_LANGUAGE_H
