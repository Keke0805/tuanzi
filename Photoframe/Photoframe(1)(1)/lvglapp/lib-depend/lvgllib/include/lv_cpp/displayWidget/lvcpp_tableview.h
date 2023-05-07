#ifndef LVCPP_TABLEVIEW_H
#define LVCPP_TABLEVIEW_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

#define  DEFAULT_TAB_POSITION  LV_DIR_TOP
#define  DEFAULT_TAB_SIZE  100

class LvcppTableView : public LvcppObject
{
public:
    LvcppTableView(lv_obj_t* parent = nullptr);
    ~LvcppTableView(void);

    //set
    lv_obj_t * add_tab(const char * name);
    int set_act(uint32_t id, lv_anim_enable_t anim_en);


    //get
    int get_tab_act(void);
    lv_obj_t * get_content(void);
    lv_obj_t * get_tab_btns(void);

};

#endif // LVCPP_TABLEVIEW_H
