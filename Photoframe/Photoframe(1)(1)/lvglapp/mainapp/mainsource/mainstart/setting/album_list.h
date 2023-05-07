#ifndef ALBUM_LIST_H
#define ALBUM_LIST_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"

class albumList
{
public:
    albumList(bool sliderStr,bool childStr,bool nextStr,bool switchStr,lv_obj_t* parent = nullptr);
    ~albumList(void);
    LvcppLabel* headLabel =NULL;
    LvcppLabel* iconLabel =NULL;
    LvcppLabel* nameLabel =NULL;
    LvcppLabel* childLabel =NULL;
    LvcppLabel* dataLabel =NULL;
    LvcppLabel* switchLabel =NULL;
    LvcppSlider* albumSlider =NULL;
private:
    LvcppLabel* lineLabel =NULL;
};

#endif // ALBUM_LIST_H
