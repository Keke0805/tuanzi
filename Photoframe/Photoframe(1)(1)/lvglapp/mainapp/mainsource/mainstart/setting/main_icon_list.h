#ifndef MAIN_ICON_LIST_H
#define MAIN_ICON_LIST_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"

class mainIconList
{
public:
    mainIconList(lv_obj_t* parent = nullptr);
    ~mainIconList(void);
    void updata_icon_name(void *path, char*str_name);
    LvcppButton* frame=NULL;

private:
    lv_obj_t* mainframe=NULL;
    LvcppLabel* icon=NULL;
    LvcppLabel* item=NULL;
    LvcppLabel* line =NULL;
};

#endif // MAIN_ICON_LIST_H
