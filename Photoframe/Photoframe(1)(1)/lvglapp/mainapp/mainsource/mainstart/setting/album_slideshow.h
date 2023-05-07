#ifndef ALBUM_SLIDESHOW_H
#define ALBUM_SLIDESHOW_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include "setting_mute_list.h"

class albumSlideShow
{
public:
    albumSlideShow(int curIndex);
    ~albumSlideShow(void);
    int get_SlideShow_cur(void);
    void set_SlideShow_cur(int curIndex);
    LvcppScreen* SlideshowScreen=NULL;
    LvcppLabel* headLabel=NULL;
    LvcppButton* CancelButton=NULL;
    LvcppButton* OKButton=NULL;
    settingMuteList* TimeList0=NULL;
    settingMuteList* TimeList1=NULL;
    settingMuteList* TimeList2=NULL;
    settingMuteList* TimeList3=NULL;
    settingMuteList* TimeList4=NULL;
    settingMuteList* TimeList5=NULL;
    settingMuteList* TimeList6=NULL;
    settingMuteList* TimeList7=NULL;
protected:
	void*  LIST_CIRCLE_PNG=NULL;
	void*  LIST_CIRCLESEL_PNG=NULL;
    void ui_image_decode(void);
    void ui_image_free(void);

private:
    LvcppList* SlideShowList=NULL;
    LvcppLabel* headNameLabel=NULL;
    LvcppLabel* lineLabel=NULL;
    int index =0;
};

#endif // ALBUM_SLIDESHOW_H
