#ifndef LVCPP_TABELFLEX_H
#define LVCPP_TABELFLEX_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_object.h"

class LvcppTableFlex : public LvcppObject
{
public:
    LvcppTableFlex(lv_obj_t* parent = nullptr);
    ~LvcppTableFlex();

    //set
    int set_tabel_flex(lv_flex_flow_t);
    int add_object(lv_obj_t*);
	int move_to_index(lv_obj_t * object, int32_t index);
	int swap_index(lv_obj_t * obj1, lv_obj_t * obj2);

    //get
	int get_index(const lv_obj_t * object);

};

#endif // LVCPP_TABELFLEX_H
