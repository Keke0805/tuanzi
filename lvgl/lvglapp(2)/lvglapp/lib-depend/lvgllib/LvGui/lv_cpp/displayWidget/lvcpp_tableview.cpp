#include "lvcpp_tableview.h"

LvcppTableView::LvcppTableView(lv_obj_t* parent)
{
    myobj = lv_tabview_create(parent, DEFAULT_TAB_POSITION, DEFAULT_TAB_SIZE);
}

LvcppTableView::~LvcppTableView(void)
{

}

//set
lv_obj_t * LvcppTableView::add_tab(const char * name)
{
    return lv_tabview_add_tab(myobj,  name);
}

int LvcppTableView::set_act(uint32_t id, lv_anim_enable_t anim_en)
{
    lv_tabview_set_act(myobj, id, anim_en);
    return 0;
}


//get
int LvcppTableView::get_tab_act(void)
{

    return lv_tabview_get_tab_act(myobj);
}

lv_obj_t * LvcppTableView::get_content(void)
{

    return lv_tabview_get_content(myobj);
}

lv_obj_t * LvcppTableView::get_tab_btns(void)
{

    return lv_tabview_get_tab_btns(myobj);
}
