#ifndef MENU_LIST_H
#define MENU_LIST_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "../include/configCustom.h"

class menuList
{
public:
    menuList(lv_obj_t* parent);
    ~menuList(void);
    LvcppLabel* Label=NULL;
    LvcppImageButton* chelImage=NULL;
    LvcppLabel* LineLabel=NULL;

private:

};
#endif // MENU_LIST_H
