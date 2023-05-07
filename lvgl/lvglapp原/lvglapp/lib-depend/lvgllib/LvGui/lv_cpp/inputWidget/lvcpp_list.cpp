#include "lvcpp_list.h"

LvcppList::LvcppList(lv_obj_t* parent)
{
    myobj = lv_list_create(parent);
    select_obj = 0;
}

LvcppList::~LvcppList(void)
{

}

int LvcppList::add_cell_txt(const char* str)
{
    lv_list_add_text(myobj, str);
    return 0;
}

int LvcppList::add_cell_btn(const char * icon, const char * str)
{
    lv_list_add_btn(myobj, icon, str);
    return 0;
}

int LvcppList::switch_select_state(int id, lv_color_t def_color, lv_color_t sel_color)
{
    if(id == select_obj) return 0;

    lv_obj_t * child = lv_obj_get_child(myobj, select_obj);
    lv_obj_set_style_bg_color(child,def_color,LV_PART_MAIN);

    child = lv_obj_get_child(myobj, id);
    lv_obj_set_style_bg_color(child,sel_color,LV_PART_MAIN);

    select_obj = id;

    return 0;
}


int LvcppList::move_to_index(lv_obj_t * object, int32_t index)
{
    lv_obj_move_to_index(object, index);
    return 0;
}


int LvcppList::swap_index(lv_obj_t * obj1, lv_obj_t * obj2)
{
    lv_obj_swap(obj1, obj2);
    return 0;
}

int LvcppList::set_select_state(int id, lv_color_t sel_color)
{
    lv_obj_t * child = lv_obj_get_child(myobj, id);
    lv_obj_set_style_bg_color(child,sel_color,LV_PART_MAIN);
    select_obj = id;

    return 0;
}

int LvcppList::clear_allobj_state(void)
{
    uint32_t i;
    for(i = 0; i < lv_obj_get_child_cnt(myobj); i++)
    {
        lv_obj_t * child = lv_obj_get_child(myobj, i);
        lv_obj_set_style_bg_color(child,lv_color_hex(0x5555df),LV_PART_MAIN);
    }

    return 0;
}

int LvcppList::get_select_state(void)
{
    return select_obj;
}

const char* LvcppList::get_btn_text(lv_obj_t * btn)
{
    return lv_list_get_btn_text(myobj,btn);
}

int LvcppList::get_index(const lv_obj_t * object)
{
    return lv_obj_get_index(object);
}
