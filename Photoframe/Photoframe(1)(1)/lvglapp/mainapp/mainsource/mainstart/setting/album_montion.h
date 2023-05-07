#ifndef ALBUM_MONTION_H
#define ALBUM_MONTION_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include "setting_mute_list.h"


class albumMontion
{
public:
    albumMontion(int curIndex);
    ~albumMontion(void);
    int get_Montion_cur(void);
    void set_Montion_cur(int curIndex);
    LvcppScreen* MontionScreen=NULL;
    LvcppLabel* headLabel=NULL;
    LvcppButton* CancelButton=NULL;
    LvcppButton* OKButton=NULL;
    settingMuteList* TimeList0=NULL;
    settingMuteList* TimeList1=NULL;
    settingMuteList* TimeList2=NULL;
    settingMuteList* TimeList3=NULL;
    settingMuteList* TimeList4=NULL;
protected:
	void*  LIST_CIRCLE_PNG=NULL;
	void*  LIST_CIRCLESEL_PNG=NULL;
    void ui_image_decode(void);
    void ui_image_free(void);

private:
    LvcppList* MontionList=NULL;
    LvcppLabel* headNameLabel=NULL;
    LvcppLabel* lineLabel=NULL;
    int index =0;
};

#endif // ALBUM_MONTION_H
