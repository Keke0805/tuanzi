#ifndef LVCPP_LIST_H
#define LVCPP_LIST_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

class LvcppList : public LvcppObject
{
public:
    LvcppList(lv_obj_t* parent = nullptr);
    ~LvcppList(void);

    //set
    int add_cell_txt(const char*);
    int add_cell_btn(const char*, const char*);

    int switch_select_state(int,lv_color_t,lv_color_t);
    int move_to_index(lv_obj_t * object, int32_t index);
    int swap_index(lv_obj_t * obj1, lv_obj_t * obj2);
    int set_select_state(int,lv_color_t);
    int clear_allobj_state(void);

    //get
    const char* get_btn_text(lv_obj_t * btn);

    int get_select_state(void);
    int get_index(const lv_obj_t * object);


private:
    int select_obj;
};

#endif // LVCPP_LIST_H
