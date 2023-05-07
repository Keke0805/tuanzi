#include "lvcpp_tabelflex.h"

LvcppTableFlex::LvcppTableFlex(lv_obj_t* parent)
{
    myobj = lv_obj_create(parent);
    set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
}

LvcppTableFlex::~LvcppTableFlex()
{

}

int LvcppTableFlex::set_tabel_flex(lv_flex_flow_t flex)
{
    lv_obj_set_flex_flow(myobj,flex);
    return 0;
}


int LvcppTableFlex::add_object(lv_obj_t* object)
{
    lv_obj_set_parent(object, myobj);
    return 0;
}


int LvcppTableFlex::move_to_index(lv_obj_t * object, int32_t index)
{
    lv_obj_move_to_index(object, index);
    return 0;
}

int LvcppTableFlex::swap_index(lv_obj_t * obj1, lv_obj_t * obj2)
{
    lv_obj_swap(obj1, obj2);
    return 0;
}


int LvcppTableFlex::get_index(const lv_obj_t * object)
{
    return lv_obj_get_index(object);
}




