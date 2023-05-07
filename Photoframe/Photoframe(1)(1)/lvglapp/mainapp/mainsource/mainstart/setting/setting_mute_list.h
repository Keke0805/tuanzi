#ifndef SETTING_MUTE_LIST_H
#define SETTING_MUTE_LIST_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"


class settingMuteList
{
public:
    settingMuteList(int size_w,int size_h,lv_obj_t* parent = nullptr);
    ~settingMuteList(void);
    LvcppLabel* headLabel =NULL;
    LvcppLabel* nameLabel =NULL;
    LvcppLabel* iconLabel =NULL;
protected:
	void*  LIST_CIRCLE_PNG=NULL;
	void*  LIST_CIRCLESEL_PNG=NULL;
    void ui_image_decode(void);
    void ui_image_free(void);

private:
    LvcppLabel* lineLabel =NULL;
};

#endif // SETTING_MUTE_LIST_H
