#ifndef ALBUM_SLIDESHOW_MODE_H
#define ALBUM_SLIDESHOW_MODE_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include "setting_mute_list.h"


class albumSlideShowMode
{
public:
    albumSlideShowMode(int curIndex);
    ~albumSlideShowMode(void);
    int get_SlideShowMode_cur(void);
    void set_SlideShowMode_cur(int curIndex);
    LvcppScreen* SlideshowModeScreen=NULL;
    LvcppLabel* headLabel=NULL;
    LvcppButton* CancelButton=NULL;
    LvcppButton* OKButton=NULL;
    settingMuteList* ModeList0=NULL;
    settingMuteList* ModeList1=NULL;
protected:
	void*  LIST_CIRCLE_PNG=NULL;
	void*  LIST_CIRCLESEL_PNG=NULL;
    void ui_image_decode(void);
    void ui_image_free(void);

private:
    LvcppList* SlideShowModeList=NULL;
    LvcppLabel* headNameLabel=NULL;
    LvcppLabel* lineLabel=NULL;
    int index =0;
};

#endif // ALBUM_SLIDESHOW_MODE_H
